#include "core/glbuffer.h"

#include <cassert>
#include <string>
#include <vector>

#include "core/glerror.h"
#include "core/logger.h"

namespace RCube {
namespace Core {

static void LogBindFailed(std::string &&prefix) {
  prefix += "failed: Bind() had error";
  Logger::Log(prefix, Logger::Level::kError);
}

GLBuffer::GLBuffer(GLBuffer &&x)
    : handle_(x.handle_),
      dataComponents_(x.dataComponents_),
      dataType_(x.dataType_),
      needNormalize_(x.needNormalize_),
      dataStride_(x.dataStride_) {
  x.handle_ = 0;
  x.dataComponents_ = 0;
  x.dataType_ = 0;
  x.needNormalize_ = false;
  x.dataStride_ = 0;
}

GLBuffer &GLBuffer::operator=(GLBuffer &&x) {
  Delete();
  handle_ = x.handle_;
  dataComponents_ = x.dataComponents_;
  dataType_ = x.dataType_;
  needNormalize_ = x.needNormalize_;
  dataStride_ = x.dataStride_;

  x.handle_ = 0;
  x.dataComponents_ = 0;
  x.dataType_ = 0;
  x.needNormalize_ = false;
  x.dataStride_ = 0;
  return *this;
}

GLBuffer::~GLBuffer() { Delete(); }

void GLBuffer::Delete() {
  dataStride_ = 0;
  needNormalize_ = false;
  dataType_ = 0;
  dataComponents_ = 0;

  glDeleteBuffers(1, &handle_);
  handle_ = 0;
}

bool GLBuffer::Generate() {
  GLuint new_handle = 0;

  auto err = GLError::Call([&new_handle]() { glGenBuffers(1, &new_handle); });
  if (err) {
    err.Log(Logger::ToPrefix({__FUNCTION__, "glGenBuffers"}));
    return false;
  }

  Delete();
  handle_ = new_handle;
  return true;
}

bool GLBuffer::IsGenerated() const { return handle_ != 0; }

bool GLBuffer::Bind() {
  if (!IsGenerated()) {
    auto msg = Logger::ToPrefix({__FUNCTION__});
    msg += "failed: buffer isn't generated";
    Logger::Log(msg, Logger::Level::kError);
    return false;
  }

  auto err =
      GLError::Call([this]() { glBindBuffer(GL_ARRAY_BUFFER, handle_); });

  if (err) {
    err.Log(Logger::ToPrefix({__FUNCTION__, "glBindBuffer"}));
    return false;
  }

  return true;
}

void GLBuffer::Unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

bool GLBuffer::Fill(const GLvoid *data, GLsizeiptr bytes, GLint components,
                    GLenum type, GLenum usage, GLboolean need_normalize,
                    GLsizei stride) {
  if (!Bind()) {
    LogBindFailed(__FUNCTION__);
    return false;
  }

  auto err = GLError::Call([this, data, bytes, usage]() {
    glBufferData(GL_ARRAY_BUFFER, bytes, data, usage);
  });

  Unbind();

  if (err) {
    err.Log(Logger::ToPrefix({__FUNCTION__, "glBufferData"}));
    return false;
  }

  dataComponents_ = components;
  dataType_ = type;
  needNormalize_ = need_normalize;
  dataStride_ = stride;
  return true;
}

GLint GLBuffer::Size() {
  if (!Bind()) {
    return 0;
  }

  GLint size = 0;
  auto err = GLError::Call([&size]() {
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  });

  Unbind();

  if (err) {
    err.Log(Logger::ToPrefix({__FUNCTION__, "glGetBufferParameteriv"}));
    return 0;
  }

  return size;
}

GLint GLBuffer::Components() const { return dataComponents_; }

bool GLBuffer::DataType(GLenum *out_type) {
  auto size = Size();

  if (size == 0) {
    return false;
  }

  assert(out_type);
  *out_type = dataType_;
  return true;
}

GLboolean GLBuffer::NeedNormalize() const { return needNormalize_; }

GLsizei GLBuffer::Stride() const { return dataStride_; }

};  // namespace Core
};  // namespace RCube
