#include "core/glvertex_array.h"

#include <string>
#include <utility>
#include <vector>

#include "core/glerror.h"
#include "core/logger.h"

namespace RCube {
namespace Core {

static void LogBindFailed(std::string &&prefix) {
  prefix += ": failed: Bind() had error";
  Logger::Log(prefix, Logger::Level::kError);
}

GLVertexArray::GLVertexArray(GLVertexArray &&x)
    : handle_(x.handle_), buffers_(std::move(x.buffers_)) {
  x.handle_ = 0;
}

GLVertexArray &GLVertexArray::operator=(GLVertexArray &&x) {
  Delete();
  handle_ = x.handle_;
  x.buffers_ = std::move(x.buffers_);

  x.handle_ = 0;
  return *this;
}

GLVertexArray::~GLVertexArray() { Delete(); }

void GLVertexArray::Delete() {
  glDeleteVertexArrays(1, &handle_);
  handle_ = 0;
}

bool GLVertexArray::Generate() {
  GLuint new_handle = 0;

  auto err =
      GLError::Call([&new_handle]() { glGenVertexArrays(1, &new_handle); });

  if (err) {
    err.Log(Logger::ToPrefix({__PRETTY_FUNCTION__, "glGenVertexArrays"}));
    return false;
  }

  Delete();
  handle_ = new_handle;
  return true;
}

bool GLVertexArray::IsGenerated() const { return handle_ != 0; }

bool GLVertexArray::Bind() {
  if (!IsGenerated()) {
    auto msg = Logger::ToPrefix({__PRETTY_FUNCTION__});
    msg += "failed: buffer isn't generated";
    Logger::Log(msg, Logger::Level::kError);
    return false;
  }

  auto err = GLError::Call([this]() { glBindVertexArray(handle_); });

  if (err) {
    err.Log(Logger::ToPrefix({__PRETTY_FUNCTION__, "glBindVertexArray"}));
    return false;
  }

  return true;
}

void GLVertexArray::Unbind() { glBindVertexArray(0); }

bool GLVertexArray::AddBuffer(GLuint location, std::shared_ptr<GLBuffer> buff) {
  assert(buff);

  GLenum buff_data_type;
  if (!buff->DataType(&buff_data_type)) {
    auto msg = Logger::ToPrefix({__PRETTY_FUNCTION__});
    msg += "failed: buff doesn't have data type";
    Logger::Log(msg, Logger::Level::kError);
    return false;
  }

  if (!buff->Bind() || !Bind()) {
    LogBindFailed(__PRETTY_FUNCTION__);
    return false;
  }

  auto err =
      GLError::Call([location]() { glEnableVertexAttribArray(location); });

  if (err) {
    err.Log(
        Logger::ToPrefix({__PRETTY_FUNCTION__, "glEnableVertexAttribArray"}));
    buff->Unbind();
    Unbind();
    return false;
  }

  err = GLError::Call([location, buff, buff_data_type]() {
    glVertexAttribPointer(location, buff->Components(), buff_data_type,
                          buff->NeedNormalize(), buff->Stride(), nullptr);
  });

  buff->Unbind();
  Unbind();

  if (err) {
    err.Log(Logger::ToPrefix({__PRETTY_FUNCTION__, "glVertexAttribPointer"}));
    return false;
  }

  buffers_.insert_or_assign(location, std::move(buff));

  return true;
}

bool GLVertexArray::RemoveBuffer(GLuint location) {
  auto buff = buffers_.find(location);
  if (buff == buffers_.cend()) {
    return true;
  }

  if (!Bind()) {
    LogBindFailed(__PRETTY_FUNCTION__);
    return false;
  }

  auto err =
      GLError::Call([location]() { glDisableVertexAttribArray(location); });

  Unbind();

  if (err) {
    err.Log(
        Logger::ToPrefix({__PRETTY_FUNCTION__, "glDisableVertexAttribArray"}));
    return false;
  }

  buffers_.erase(buff);
  return true;
}

};  // namespace Core
};  // namespace RCube
