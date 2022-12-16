#include "ui/glview.h"

#include <string>

#include "core/logger.h"

namespace RCube {
namespace UI {

GLView::GLView(QWidget *parent, Qt::WindowFlags flags)
    : QOpenGLWidget(parent, flags) {}

void GLView::initializeGL() {
  std::string msg;
  msg.reserve(64);

  msg += "GL_RENDERER: \"";
  msg += reinterpret_cast<const char*>(glGetString(GL_RENDERER));
  msg += "\"";
  Core::Logger::Log(msg);
}

void GLView::paintGL() {}

void GLView::resizeGL(int w, int h) {}

};  // namespace UI
};  // namespace RCube
