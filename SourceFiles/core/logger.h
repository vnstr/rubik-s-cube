#ifndef SOURCEFILES_CORE_LOGGER_H_
#define SOURCEFILES_CORE_LOGGER_H_

#include <fstream>
#include <mutex>
#include <string>
#include <vector>

namespace Core {

class Logger final {
 public:
  enum class Level { kTrace, kDebug, kInfo, kWarn, kError, kFatal };

  static std::string ToPrefix(const std::vector<std::string> &);

  static bool Enable(bool enable);
  static bool Log(const std::string_view &, Level = Level::kTrace);

 private:
  Logger() = default;
  static Logger &Instance();

 public:
  Logger(const Logger &x) = delete;
  Logger(Logger &&x) = delete;
  Logger &operator=(const Logger &x) = delete;
  Logger &operator=(Logger &&) = delete;

 private:
  std::mutex fileAccess_;
  std::ofstream file_;
};

};  // namespace Core

#endif  // SOURCEFILES_CORE_LOGGER_H_
