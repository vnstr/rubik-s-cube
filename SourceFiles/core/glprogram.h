#ifndef SOURCEFILES_CORE_GLPROGRAM_H_
#define SOURCEFILES_CORE_GLPROGRAM_H_

#include <QOpenGLFunctions_4_1_Compatibility>

#include "core/glshader.h"

namespace RCube {
namespace Core {

class GLProgram final {
 public:
  GLProgram() = default;
  GLProgram(const GLProgram &) = delete;
  GLProgram(GLProgram &&);
  GLProgram &operator=(const GLProgram &) = delete;
  GLProgram &operator=(GLProgram &&);
  ~GLProgram();

  void Delete();
  bool Create();
  bool IsCreated() const;
  bool AttachShader(const GLShader &);
  bool Link();

 private:
  GLuint handle_{0};
};

};  // namespace Core
};  // namespace RCube

#endif  // SOURCEFILES_CORE_GLPROGRAM_H_
