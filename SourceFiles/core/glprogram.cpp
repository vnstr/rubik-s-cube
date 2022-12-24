#include "core/glprogram.h"

#include <string>
#include <vector>

#include "core/glerror.h"
#include "core/logger.h"

namespace RCube {
namespace Core {

static void LogFailedProgramNotCreated(std::string &&prefix) {
  prefix += ": failed: program isn't created";
  Logger::Log(prefix, Logger::Level::kError);
}

GLProgram::GLProgram(GLProgram &&x) {
  handle_ = x.handle_;
  x.handle_ = 0;
}

GLProgram &GLProgram::operator=(GLProgram &&x) {
  Delete();
  handle_ = x.handle_;
  x.handle_ = 0;
  return *this;
}

GLProgram::~GLProgram() { Delete(); }

void GLProgram::Delete() {
  glDeleteProgram(handle_);
  handle_ = 0;
}

bool GLProgram::Create() {
  GLuint new_handle = 0;

  auto err = GLError::Call([&new_handle]() { new_handle = glCreateProgram(); });
  if (err) {
    err.Log(Logger::ToPrefix({__FUNCTION__, "glCreateProgram"}));
    return false;
  }

  Delete();
  handle_ = new_handle;
  return true;
}

bool GLProgram::IsCreated() const { return handle_ != 0; }

bool GLProgram::AttachShader(const GLShader &shader) {
  if (!IsCreated()) {
    LogFailedProgramNotCreated(__FUNCTION__);
    return false;
  }

  auto err = GLError::Call([this, sh_handle = shader.GetHandle()]() {
    glAttachShader(handle_, sh_handle);
  });

  if (err) {
    err.Log(Logger::ToPrefix({__FUNCTION__, "glAttachShader"}));
    return false;
  }

  return true;
}

bool GLProgram::Link() {
  if (!IsCreated()) {
    LogFailedProgramNotCreated(__FUNCTION__);
    return false;
  }

  glLinkProgram(handle_);

  GLint link_status = 0;
  glGetProgramiv(handle_, GL_LINK_STATUS, &link_status);
  if (link_status == GL_TRUE) {
    return true;
  }

  GLint info_len = 0;
  glGetProgramiv(handle_, GL_INFO_LOG_LENGTH, &info_len);

  std::vector<GLchar> info(static_cast<size_t>(info_len));
  GLint actuall_len = 0;
  glGetProgramInfoLog(handle_, info_len, &actuall_len, info.data());
  assert(actuall_len + 1 == info_len);

  std::string msg;
  msg.reserve(256);
  msg = __FUNCTION__;
  msg += ": failed: glLinkProgram:\n<\n";
  msg += reinterpret_cast<const char *>(info.data());
  msg += ">";
  Logger::Log(msg, Logger::Level::kError);

  return false;
}

};  // namespace Core
};  // namespace RCube
