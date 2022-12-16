#include "core/glerror.h"

#include "core/logger.h"

namespace RCube {
namespace Core {

void GLError::ClearErrorList() {
  while (glGetError() != GL_NO_ERROR) {
  }
}

GLError::ErrorList GLError::GetErrorList() {
  ErrorList errors;

  while (true) {
    auto code = glGetError();
    if (code == GL_NO_ERROR) {
      return errors;
    }
    errors.emplace_back(code);
  }

  return errors;
}

std::string GLError::ToString(GLenum code) {
  switch (code) {
    case GL_NO_ERROR: {
      return "GL_NO_ERROR";
    }
    case GL_INVALID_ENUM: {
      return "GL_INVALID_ENUM";
    }
    case GL_INVALID_VALUE: {
      return "GL_INVALID_VALUE";
    }
    case GL_INVALID_OPERATION: {
      return "GL_INVALID_OPERATION";
    }
    case GL_OUT_OF_MEMORY: {
      return "GL_OUT_OF_MEMORY";
    }
  }

  return "unknown";
}

GLError GLError::Call(const std::function<void()> &func) {
  ClearErrorList();

  if (!func) {
    assert(false);
    return {};
  }

  func();
  return GLError(GetErrorList());
}

GLError::GLError(const ErrorList &errors) : glErrorCodes_(errors) {}

GLError::operator bool() const { return !glErrorCodes_.empty(); }

void GLError::Log(const std::string_view &prefix) const {
  std::string msg;
  msg.reserve(64);

  msg += prefix;
  msg += "GLError: ";

  if (glErrorCodes_.empty()) {
    msg += "\"";
    msg += ToString(GL_NO_ERROR);
    msg += "\"";
    Logger::Log(msg);
    return;
  }

  for (auto it = glErrorCodes_.cbegin();;) {
    msg += "\"";
    msg += ToString(*it++);
    msg += "\"";

    if (it == glErrorCodes_.cend()) {
      break;
    }

    msg += ", ";
  }

  Logger::Log(msg, Logger::Level::kError);
}

};  // namespace Core
};  // namespace RCube
