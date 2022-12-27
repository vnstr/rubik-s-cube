#include "ui/glview.h"

#include <string>
#include <utility>

#include "core/glerror.h"
#include "core/logger.h"
#include "core/triangle_painter.h"

namespace RCube {
namespace UI {

GLView::GLView(QWidget *parent, Qt::WindowFlags flags)
    : QOpenGLWidget(parent, flags) {}

GLView::~GLView() {}

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

  auto error = Core::GLError::Call([]() { glClearColor(1, 1, 1, 0); });
  if (error) {
    error.Log(Core::Logger::ToPrefix({__PRETTY_FUNCTION__, "glClearColor"}));
  }

  auto triangle_painter = std::make_unique<Core::TrianglePainter>();
  if (!triangle_painter->Init()) {
    msg = Core::Logger::ToPrefix({__PRETTY_FUNCTION__, "failed"});
    msg += "TrianglePainter: Init() had error";
    Core::Logger::Log(msg, Core::Logger::Level::kError);
    return;
  }

  trianglePainter_ = std::move(triangle_painter);
}

void GLView::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT);

  if (!trianglePainter_) {
    return;
  }

  if (!trianglePainter_->Draw()) {
    auto msg = Core::Logger::ToPrefix({__PRETTY_FUNCTION__, "failed"});
    msg += "TrianglePainter: Draw() had error";
    Core::Logger::Log(msg, Core::Logger::Level::kError);
  }
}

void GLView::resizeGL(int w, int h) {}

};  // namespace UI
};  // namespace RCube
