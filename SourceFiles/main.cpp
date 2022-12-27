#include <QApplication>
#include <QSurfaceFormat>
#include <iostream>

#include "core/logger.h"
#include "ui/main_window.h"

using Logger = RCube::Core::Logger;

int main(int argc, char** argv) {
  auto gl_format = QSurfaceFormat::defaultFormat();
  gl_format.setMajorVersion(4);
  gl_format.setMinorVersion(1);
  gl_format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(gl_format);

  try {
    Logger::Enable(true);
    QApplication app(argc, argv);

    RCube::UI::MainWindow main_window;
    main_window.Init();

    return app.exec();
  } catch (...) {
    Logger::Log("Unhandled exception", Logger::Level::kFatal);
    return 1;
  }

  return 0;
}
