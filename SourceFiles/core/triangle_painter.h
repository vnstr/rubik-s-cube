#ifndef SOURCEFILES_CORE_TRIANGLE_PAINTER_H_
#define SOURCEFILES_CORE_TRIANGLE_PAINTER_H_

#include <memory>

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
  bool Draw();

 private:
  std::unique_ptr<GLProgram> program_;
  std::unique_ptr<GLVertexArray> vertexArray_;
};

};  // namespace Core
};  // namespace RCube

#endif  // SOURCEFILES_CORE_TRIANGLE_PAINTER_H_
