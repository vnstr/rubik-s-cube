#include "core/triangle_painter.h"

#include <utility>

#include "core/glbuffer.h"
#include "core/glerror.h"
#include "core/glprogram.h"
#include "core/glshader.h"
#include "core/glvertex_array.h"
#include "core/logger.h"

namespace RCube {
namespace Core {

const size_t kPointsSize = 9;
const GLint kPointsComponents = 3;
const GLfloat kPoints[kPointsSize] = {0.0f, 0.5f,  0.0f,  0.5f, -0.5f,
                                      0.0f, -0.5f, -0.5f, 0.0f};

const size_t kColorsSize = 9;
const GLint kColorsComponents = 3;
GLfloat kColors[kColorsSize] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                                0.0f, 0.0f, 0.0f, 1.0f};

const char* kVertexShaderCode =
    "#version 410\n"
    "layout(location = 0) in vec3 vertex_position;"
    "layout(location = 1) in vec3 vertex_color;"
    "out vec3 color;"
    "void main() {"
    "   color = vertex_color;"
    "   gl_Position = vec4(vertex_position, 1.0);"
    "}";

const char* kFragmentShader =
    "#version 410\n"
    "in vec3 color;"
    "out vec4 frag_color;"
    "void main() {"
    "   frag_color = vec4(color, 1.0);"
    "}";

static void OnFuncFailed(const char* name, const char* what) {
  auto msg = Logger::ToPrefix({name, "failed"});
  msg += what;
  Logger::Log(msg, Logger::Level::kError);
}

TrianglePainter::TrianglePainter() {}

TrianglePainter::~TrianglePainter() {}

bool TrianglePainter::Init() {
  auto vertex_shader = std::make_unique<GLShader>();
  if (!vertex_shader->Create(GL_VERTEX_SHADER)) {
    OnFuncFailed(__PRETTY_FUNCTION__, "unable to create a vertex shader");
    return false;
  }

  if (!vertex_shader->SetSourceCode(kVertexShaderCode)) {
    OnFuncFailed(__PRETTY_FUNCTION__,
                 "unable to set source code to the vertex shader");
    return false;
  }

  if (!vertex_shader->Compile()) {
    OnFuncFailed(__PRETTY_FUNCTION__, "unable to compile the vertex shader");
    return false;
  }

  auto fragment_shader = std::make_unique<GLShader>();
  if (!fragment_shader->Create(GL_FRAGMENT_SHADER)) {
    OnFuncFailed(__PRETTY_FUNCTION__, "unable to create a fragment shader");
    return false;
  }

  if (!fragment_shader->SetSourceCode(kFragmentShader)) {
    OnFuncFailed(__PRETTY_FUNCTION__,
                 "unable to set source code to the fragment shader");
    return false;
  }

  if (!fragment_shader->Compile()) {
    OnFuncFailed(__PRETTY_FUNCTION__, "unable to compile the fragment shader");
    return false;
  }

  auto program = std::make_unique<GLProgram>();
  if (!program->Create()) {
    OnFuncFailed(__PRETTY_FUNCTION__, "unable to create a program");
    return false;
  }

  if (!program->AttachShader(*vertex_shader) ||
      !program->AttachShader(*fragment_shader)) {
    OnFuncFailed(__PRETTY_FUNCTION__,
                 "unable to attach shaders to the program");
    return false;
  }

  if (!program->Link()) {
    OnFuncFailed(__PRETTY_FUNCTION__, "unable to link the program");
    return false;
  }

  auto points_buff = std::make_shared<GLBuffer>();
  if (!points_buff->Generate()) {
    OnFuncFailed(__PRETTY_FUNCTION__, "unable to generate a points buffer");
    return false;
  }

  if (!points_buff->Fill(kPoints, sizeof(GLfloat) * kPointsSize,
                         kPointsComponents, GL_FLOAT, GL_STATIC_DRAW)) {
    OnFuncFailed(__PRETTY_FUNCTION__, "unable to fill the points buffer");
    return false;
  }

  auto colors_buff = std::make_shared<GLBuffer>();
  if (!colors_buff->Generate()) {
    OnFuncFailed(__PRETTY_FUNCTION__, "unable to generate a colors buffer");
    return false;
  }

  if (!colors_buff->Fill(kColors, sizeof(GLfloat) * kColorsSize,
                         kColorsComponents, GL_FLOAT, GL_STATIC_DRAW)) {
    OnFuncFailed(__PRETTY_FUNCTION__, "unable to fill the colors buffer");
    return false;
  }

  auto vertex_array = std::make_unique<GLVertexArray>();
  if (!vertex_array->Generate()) {
    OnFuncFailed(__PRETTY_FUNCTION__, "unable to generate the vertex array");
    return false;
  }

  if (!vertex_array->AddBuffer(0, points_buff) ||
      !vertex_array->AddBuffer(1, colors_buff)) {
    OnFuncFailed(__PRETTY_FUNCTION__,
                 "unable to add buffer to the vertex array");
    return false;
  }

  program_ = std::move(program);
  vertexArray_ = std::move(vertex_array);

  return true;
}

bool TrianglePainter::Draw() {
  if (!program_ || !vertexArray_) {
    OnFuncFailed(__PRETTY_FUNCTION__, "program or vertex array doesn't exist");
    return false;
  }

  if (!program_->Use()) {
    OnFuncFailed(__PRETTY_FUNCTION__, "unable to use the program");
    return false;
  }

  if (!vertexArray_->Bind()) {
    OnFuncFailed(__PRETTY_FUNCTION__, "unable to bind the vertex array");
    return false;
  }

  auto err = GLError::Call([]() { glDrawArrays(GL_TRIANGLES, 0, 3); });
  if (err) {
    err.Log(Logger::ToPrefix({__PRETTY_FUNCTION__, "glDrawArrays"}));
    return false;
  }

  return true;
}

};  // namespace Core
};  // namespace RCube
