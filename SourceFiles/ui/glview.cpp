#include "ui/glview.h"

#include <string>

#include "core/glerror.h"
#include "core/logger.h"

namespace RCube {
namespace UI {

GLView::GLView(QWidget *parent, Qt::WindowFlags flags)
    : QOpenGLWidget(parent, flags) {}

void GLView::initializeGL() {
  std::string msg;
  msg.reserve(64);

  msg += "\nGL_VERSION: \"";
  msg += reinterpret_cast<const char *>(glGetString(GL_VERSION));
  msg += "\"";

  msg += "\nGL_RENDERER: \"";
  msg += reinterpret_cast<const char *>(glGetString(GL_RENDERER));
  msg += "\" ";

  msg += "\nGL_SHADING_LANGUAGE_VERSION: \"";
  msg +=
      reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
  msg += "\"";
  Core::Logger::Log(msg);

  auto error = Core::GLError::Call([]() { glClearColor(0, 1, 0, 0); });
  if (error) {
    error.Log(Core::Logger::ToPrefix({__FUNCTION__, "glClearColor"}));
  }
}

void GLView::paintGL() { glClear(GL_COLOR_BUFFER_BIT); }

void GLView::resizeGL(int w, int h) {}

};  // namespace UI
};  // namespace RCube
