#include "ui/main_window.h"

#include <QBoxLayout>

#include "ui/glview.h"

namespace RCube {
namespace UI {

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags) {}

void MainWindow::Init() {
  const char *kTitle = "Rubik's cube";
  const int kWidth = 600;
  const int kHeight = 400;

  setWindowTitle(kTitle);
  resize(kWidth, kHeight);

  centralWidgetLayout_ = new QVBoxLayout;
  centralWidgetLayout_->setContentsMargins(0, 0, 0, 0);

  centralWidget_ = new QWidget(this);
  centralWidget_->setLayout(centralWidgetLayout_);

  auto glview = new GLView(centralWidget_);
  centralWidgetLayout_->addWidget(glview);

  setCentralWidget(centralWidget_);
  show();
}

};  // namespace UI
};  // namespace RCube
