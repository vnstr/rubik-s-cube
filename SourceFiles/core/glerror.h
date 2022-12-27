#ifndef SOURCEFILES_CORE_GLERROR_H_
#define SOURCEFILES_CORE_GLERROR_H_

#include <QOpenGLFunctions_4_1_Compatibility>
#include <cassert>
#include <functional>
#include <string>
#include <vector>

namespace RCube {
namespace Core {

class GLError final {
 public:
  using ErrorList = std::vector<GLenum>;

  static void ClearErrorList();
  static ErrorList GetErrorList();
  static std::string ToString(GLenum);

  static GLError Call(const std::function<void()> &func);

  GLError() = default;
  GLError(const ErrorList &);
  GLError(const GLError &) = default;
  GLError(GLError &&) = default;
  GLError &operator=(const GLError &) = default;
  GLError &operator=(GLError &&) = default;

  operator bool() const;
  void Log(const std::string_view &prefix = {}) const;

 private:
  ErrorList glErrorCodes_;
};

};  // namespace Core
};  // namespace RCube

#endif  // SOURCEFILES_CORE_GLERROR_H_
