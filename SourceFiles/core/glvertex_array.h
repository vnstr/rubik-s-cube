#ifndef SOURCEFILES_CORE_GLVERTEX_ARRAY_H_
#define SOURCEFILES_CORE_GLVERTEX_ARRAY_H_

#include <QOpenGLFunctions_4_1_Compatibility>

#include <memory>
#include <set>
#include <map>

#include "core/glbuffer.h"

namespace RCube {
namespace Core {

class GLVertexArray final {
 public:
  GLVertexArray() = default;
  GLVertexArray(const GLVertexArray &) = delete;
  GLVertexArray(GLVertexArray &&);
  GLVertexArray &operator=(const GLVertexArray &) = delete;
  GLVertexArray &operator=(GLVertexArray &&);
  ~GLVertexArray();

  void Delete();
  bool Generate();
  bool IsGenerated() const;

  bool Bind();
  void Unbind();

  bool AddBuffer(GLuint location, std::shared_ptr<GLBuffer>);
  bool RemoveBuffer(GLuint location);

 private:
  GLuint handle_{0};
  std::map<GLuint /*location*/, std::shared_ptr<GLBuffer>> buffers_;
};

};  // namespace Core
};  // namespace RCube

#endif  // SOURCEFILES_CORE_GLVERTEX_ARRAY_H_
