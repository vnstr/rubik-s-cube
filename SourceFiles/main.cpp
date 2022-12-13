#include <QApplication>
#include <iostream>

#include "ui/main_window.h"

int main(int argc, char **argv) {
  try {
    QApplication app(argc, argv);

    UI::MainWindow main_window;
    main_window.Init();

    return app.exec();
  } catch (...) {
    std::cout << "Unhandled exception" << std::endl;
    return 1;
  }

  return 0;
}

