#ifndef SOURCEFILES_UI_MAIN_WINDOW_H_
#define SOURCEFILES_UI_MAIN_WINDOW_H_

#include <QMainWindow>

class QVBoxLayout;

namespace UI {

class MainWindow : public QMainWindow {
 public:
  explicit MainWindow(QWidget *parent = nullptr,
                      Qt::WindowFlags flags = Qt::WindowFlags());

  MainWindow(const MainWindow &) = delete;
  MainWindow(MainWindow &&) = delete;
  MainWindow &operator=(const MainWindow &) = delete;
  MainWindow &operator=(MainWindow &&) = delete;

  void Init();

 private:
  QWidget *centralWidget_{nullptr};
  QVBoxLayout *centralWidgetLayout_{nullptr};
};

};  // namespace UI

#endif  // SOURCEFILES_UI_MAIN_WINDOW_H_
