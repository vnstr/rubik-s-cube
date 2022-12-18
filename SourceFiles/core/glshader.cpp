#include "core/glshader.h"

#include <cassert>
#include <vector>

#include "core/glerror.h"
#include "core/logger.h"

namespace RCube {
namespace Core {

static void LogFailedShaderNotCreated(std::string &&prefix) {
  prefix += ": failed: shader isn't created";
  Logger::Log(prefix, Logger::Level::kError);
}

GLShader::GLShader(GLShader &&x) {
  handle_ = x.handle_;
  x.handle_ = 0;
}

GLShader &GLShader::operator=(GLShader &&x) {
  Delete();
  handle_ = x.handle_;
  x.handle_ = 0;
  return *this;
}

GLShader::~GLShader() { Delete(); }

void GLShader::Delete() {
  glDeleteShader(handle_);
  handle_ = 0;
}

bool GLShader::Create(GLenum type) {
  GLuint new_handle = 0;

  auto err = GLError::Call(
      [&new_handle, type]() { new_handle = glCreateShader(type); });

  if (err) {
    err.Log(Logger::ToPrefix({__FUNCTION__, "glCreateShader"}));
    return false;
  }

  Delete();
  handle_ = new_handle;
  return true;
}

bool GLShader::IsCreated() const { return handle_ != 0; }

bool GLShader::SetSourceCode(const std::string &code) {
  if (!IsCreated()) {
    LogFailedShaderNotCreated(__FUNCTION__);
    return false;
  }

  auto c_str = code.c_str();

  auto err = GLError::Call(
      [this, c_str]() { glShaderSource(handle_, 1, &c_str, nullptr); });

  if (err) {
    std::string msg;
    msg.reserve(64);
    msg = __FUNCTION__;
    msg += ": \n<\n";
    msg += code;
    msg += "\n>: glShaderSource: ";
    err.Log(msg);
    return false;
  }

  return true;
}

bool GLShader::Compile() {
  if (!IsCreated()) {
    LogFailedShaderNotCreated(__FUNCTION__);
    return false;
  }

  glCompileShader(handle_);

  GLint compile_status = 0;
  glGetShaderiv(handle_, GL_COMPILE_STATUS, &compile_status);
  if (compile_status == GL_TRUE) {
    return true;
  }

  GLint info_len = 0;
  glGetShaderiv(handle_, GL_INFO_LOG_LENGTH, &info_len);

  std::vector<GLchar> info(static_cast<size_t>(info_len));
  GLint actuall_len = 0;
  glGetShaderInfoLog(handle_, info_len, &actuall_len, info.data());
  assert(actuall_len + 1 == info_len);

  std::string msg;
  msg.reserve(256);
  msg = __FUNCTION__;
  msg += ": failed: glCompileShader:\n<\n";
  msg += reinterpret_cast<const char *>(info.data());
  msg += ">";
  Logger::Log(msg, Logger::Level::kError);

  return false;
}

};  // namespace Core
};  // namespace RCube
