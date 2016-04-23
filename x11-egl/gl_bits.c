#include <math.h>
#include <stdbool.h>
#include <GLES2/gl2.h>

#include "vertex_glsl.h"
#include "fragment_glsl.h"

static GLuint load_shader(const char *shader_source, GLenum type) {
   GLuint  shader = glCreateShader(type);
   glShaderSource(shader, 1, &shader_source, 0);
   glCompileShader(shader);
   return shader;
}

static GLint phase_loc, position_loc;

static const float vertexArray[] = {
   0.0,  0.5,  0.0,
  -0.5,  0.0,  0.0,
   0.0, -0.5,  0.0,
   0.5,  0.0,  0.0,
   0.0,  0.5,  0.0
};

static const float TAU = 2.f * M_PI;

void render(int width, int height) {
   static float phase = 0;

   glViewport(0 , 0 , width , height);
   glClearColor(0.08 , 0.06 , 0.07 , 1.);
   glClear(GL_COLOR_BUFFER_BIT);

   glUniform1f(phase_loc, phase);
   phase += 0.25f;
   if (phase > TAU) phase -= TAU;

   glVertexAttribPointer(position_loc, 3, GL_FLOAT, false, 0, vertexArray);
   glEnableVertexAttribArray(position_loc);
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 5);
}

int init_gl_resources() {
   GLuint vertexShader   = load_shader(vertex_glsl  , GL_VERTEX_SHADER  );
   GLuint fragmentShader = load_shader(fragment_glsl, GL_FRAGMENT_SHADER);

   GLuint shaderProgram  = glCreateProgram();
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);

   glLinkProgram(shaderProgram);
   glUseProgram(shaderProgram);

   phase_loc = glGetUniformLocation(shaderProgram , "phase");
   if (phase_loc < 0) {
	   return 1;
   }

   return 0;
}
