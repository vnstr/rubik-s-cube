#ifndef SOURCEFILES_UI_GLVIEW_H_
#define SOURCEFILES_UI_GLVIEW_H_

#include <QOpenGLFunctions_4_1_Compatibility>
#include <QOpenGLWidget>
#include <memory>

namespace RCube {

namespace Core {
class TrianglePainter;
};

namespace UI {

class GLView : public QOpenGLWidget {
 public:
  explicit GLView(QWidget *parent = nullptr,
                  Qt::WindowFlags f = Qt::WindowFlags());

  GLView(const GLView &) = delete;
  GLView(GLView &&) = delete;
  GLView &operator=(const GLView &) = delete;
  GLView &operator=(GLView &&) = delete;
  ~GLView();

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

 private:
  std::unique_ptr<Core::TrianglePainter> trianglePainter_;
};

};  // namespace UI
};  // namespace RCube

#endif  // SOURCEFILES_UI_GLVIEW_H_
