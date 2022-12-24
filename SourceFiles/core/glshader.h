#ifndef SOURCEFILES_CORE_GLSHADER_H_
#define SOURCEFILES_CORE_GLSHADER_H_

#include <glfw/glfw3.h>
#include <string>

namespace RCube {
namespace Core {

class GLShader final {
 public:
  GLShader() = default;
  GLShader(const GLShader &) = delete;
  GLShader(GLShader &&);
  GLShader &operator=(const GLShader &) = delete;
  GLShader &operator=(GLShader &&);
  ~GLShader();

  GLuint GetHandle() const;

  void Delete();

  /**
   * @param type Must be either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER.
   * @return false if error.
   */
  bool Create(GLenum type);
  bool IsCreated() const;

  bool SetSourceCode(const std::string &);
  bool Compile();

 private:
  GLuint handle_{0};
};

};  // namespace Core
};  // namespace RCube

#endif  // SOURCEFILES_CORE_GLSHADER_H_
