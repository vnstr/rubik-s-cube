#include "core/glshader.h"

#include "core/glerror.h"
#include "core/logger.h"

namespace RCube {
namespace Core {

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

  auto error = GLError::Call(
      [&new_handle, type]() { new_handle = glCreateShader(type); });

  if (error) {
    error.Log(Logger::ToPrefix({__FUNCTION__, "glCreateShader"}));
    return false;
  }

  Delete();
  handle_ = new_handle;
  return true;
}

bool GLShader::IsCreated() const { return handle_ != 0; }

};  // namespace Core
};  // namespace RCube
