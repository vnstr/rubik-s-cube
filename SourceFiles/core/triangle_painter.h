#ifndef SOURCEFILES_CORE_TRIANGLE_PAINTER_H_
#define SOURCEFILES_CORE_TRIANGLE_PAINTER_H_

#include <memory>

#include "glm/mat4x4.hpp"

namespace RCube {
namespace Core {

class GLProgram;
class GLVertexArray;

class TrianglePainter final {
 public:
  TrianglePainter();
  TrianglePainter(const TrianglePainter &) = delete;
  TrianglePainter(TrianglePainter &&) = default;
  TrianglePainter &operator=(const TrianglePainter &) = delete;
  TrianglePainter &operator=(TrianglePainter &&) = default;
  ~TrianglePainter();

  bool Init();
  bool Draw(int width, int height);

 private:
  std::unique_ptr<GLProgram> program_;
  std::unique_ptr<GLVertexArray> vertexArray_;
  glm::mat4x4 modelMat1_{1.0f};
  glm::mat4x4 modelMat2_{1.0f};
};

};  // namespace Core
};  // namespace RCube

#endif  // SOURCEFILES_CORE_TRIANGLE_PAINTER_H_
