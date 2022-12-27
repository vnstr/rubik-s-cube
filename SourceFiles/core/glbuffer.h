#ifndef SOURCEFILES_CORE_GLBUFFER_H_
#define SOURCEFILES_CORE_GLBUFFER_H_

#include <QOpenGLFunctions_4_1_Compatibility>

namespace RCube {
namespace Core {

class GLError;

class GLBuffer final {
 public:
  GLBuffer() = default;
  GLBuffer(const GLBuffer &) = delete;
  GLBuffer(GLBuffer &&);
  GLBuffer &operator=(const GLBuffer &) = delete;
  GLBuffer &operator=(GLBuffer &&);
  ~GLBuffer();

  void Delete();
  bool Generate();
  bool IsGenerated() const;

  bool Bind();
  void Unbind();

  /**
   * @param data Pointer to data that will be copied.
   * @param bytes Size in bytes of the buffer.
   * @param components Specifies the number of components per generic vertex
   * attribute. Must be 1, 2, 3, 4.
   * @param type Specifies the data type of each component in the array. The
   * symbolic constants:
   * GL_BYTE,
   * GL_UNSIGNED_BYTE,
   * GL_SHORT,
   * GL_UNSIGNED_SHORT,
   * GL_INT,
   * GL_UNSIGNED_INT
   * GL_HALF_FLOAT,
   * GL_FLOAT,
   * GL_DOUBLE,
   * GL_INT_2_10_10_10_REV
   * GL_UNSIGNED_INT_2_10_10_10_REV.
   * Reference "https://docs.gl/gl3/glVertexAttribPointer".
   * @param usage Specifies the expected usage pattern of the data store. The
   * symbolic constant must be:
   * GL_STREAM_DRAW,
   * GL_STREAM_READ,
   * GL_STREAM_COPY,
   * GL_STATIC_DRAW,
   * GL_STATIC_READ,
   * GL_STATIC_COPY,
   * GL_DYNAMIC_DRAW,
   * GL_DYNAMIC_READ,
   * GL_DYNAMIC_COPY.
   * Reference "https://docs.gl/gl2/glBufferData".
   * @param need_normalize Specifies whether fixed-point data values should be
   * normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE)
   * when they are accessed. The default value GL_FALSE.
   * @param stride Specifies the byte offset between consecutive generic vertex
   * attributes. If stride is 0, the generic vertex attributes are understood to
   * be tightly packed in the array. The default value is 0.
   * @return false if error.
   */
  bool Fill(const GLvoid *data, GLsizeiptr bytes, GLint components, GLenum type,
            GLenum usage, GLboolean need_normalize = GL_FALSE,
            GLsizei stride = 0);

  GLint Size();
  GLint Components() const;
  bool DataType(GLenum *out_type);
  GLboolean NeedNormalize() const;
  GLsizei Stride() const;


 private:
  GLuint handle_{0};
  GLint dataComponents_{0};
  GLenum dataType_{0};
  GLboolean needNormalize_{false};
  GLsizei dataStride_{0};
};

};  // namespace Core
};  // namespace RCube

#endif  // SOURCEFILES_CORE_GLBUFFER_H_
