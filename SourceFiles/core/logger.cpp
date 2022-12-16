#include "core/logger.h"

namespace RCube {
namespace Core {

std::string Logger::ToPrefix(const std::vector<std::string> &names) {
  std::string prefix;
  prefix.reserve(64);

  for (const auto &it : names) {
    prefix += it;
    prefix += ": ";
  }

  return prefix;
}

bool Logger::Enable(bool enable) {
  const char *kFilename = "rubik-s-cube-log.txt";
  const auto kFileFlags = std::fstream::out | std::fstream::trunc;

  if (!enable) {
    std::scoped_lock access(Instance().fileAccess_);
    Instance().file_.close();
    return true;
  }

  std::scoped_lock access(Instance().fileAccess_);
  Instance().file_.open(kFilename, kFileFlags);

  return Instance().file_.is_open();
}

bool Logger::Log(const std::string_view &msg, Level level) {
  auto &inst = Instance();

  std::string prefix;
  prefix.reserve(16);

  prefix += "[";
  switch (level) {
    case Level::kTrace: {
      prefix += "TRACE";
      break;
    }
    case Level::kDebug: {
      prefix += "DEBUG";
      break;
    }
    case Level::kInfo: {
      prefix += "INFO";
      break;
    }
    case Level::kWarn: {
      prefix += "WARN";
      break;
    }
    case Level::kError: {
      prefix += "ERROR";
      break;
    }
    case Level::kFatal: {
      prefix += "FATAL";
      break;
    }
    default: {
      break;
    }
  }
  prefix += "] ";

  {
    std::scoped_lock access(inst.fileAccess_);
    if (!inst.file_.is_open()) {
      return false;
    }

    inst.file_ << prefix << msg << std::endl;
  }

  return true;
}

Logger &Logger::Instance() {
  static Logger instance;
  return instance;
}

};  // namespace Core
};  // namespace RCube
