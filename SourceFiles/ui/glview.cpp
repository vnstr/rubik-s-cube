#include "ui/glview.h"

namespace UI {

GLView::GLView(QWidget *parent, Qt::WindowFlags flags)
    : QOpenGLWidget(parent, flags) {}

void GLView::initializeGL() { QOpenGLWidget::initializeGL(); }

void GLView::paintGL() { QOpenGLWidget::paintGL(); }

void GLView::resizeGL(int w, int h) { QOpenGLWidget::resizeGL(w, h); }

};  // namespace UI
