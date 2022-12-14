#include <QApplication>
#include <iostream>

#include "core/logger.h"
#include "ui/main_window.h"

int main(int argc, char **argv) {
  try {
    Core::Logger::Enable(true);
    QApplication app(argc, argv);

    UI::MainWindow main_window;
    main_window.Init();

    return app.exec();
  } catch (...) {
    Core::Logger::Log("Unhandled exception", Core::Logger::Level::kFatal);
    return 1;
  }

  return 0;
}

