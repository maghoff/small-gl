#include <math.h>
#include <stdbool.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>

#include "vertex_glsl.h"
#include "fragment_glsl.h"

static GLuint load_shader(const char *shader_source, GLenum type)
{
   GLuint  shader = glCreateShader(type);
   glShaderSource(shader, 1, &shader_source, NULL);
   glCompileShader(shader);
   return shader;
}


GLfloat
   norm_x    =  0.0,
   norm_y    =  0.0,
   offset_x  =  0.0,
   offset_y  =  0.0,
   p1_pos_x  =  0.0,
   p1_pos_y  =  0.0;

GLint
   phase_loc,
   offset_loc,
   position_loc;


static bool update_pos = false;

static const float vertexArray[] = {
   0.0,  0.5,  0.0,
  -0.5,  0.0,  0.0,
   0.0, -0.5,  0.0,
   0.5,  0.0,  0.0,
   0.0,  0.5,  0.0
};

static const float TAU = 2.f * M_PI;

void render(int width, int height)
{
   static float  phase = 0;

   glViewport ( 0 , 0 , width , height );
   glClearColor ( 0.08 , 0.06 , 0.07 , 1.);    // background color
   glClear ( GL_COLOR_BUFFER_BIT );

   glUniform1f(phase_loc , phase);
   phase += 0.5f;
   if (phase > TAU) phase -= TAU;

   if ( update_pos ) {  // if the position of the texture has changed due to user action
      GLfloat old_offset_x  =  offset_x;
      GLfloat old_offset_y  =  offset_y;

      offset_x  =  norm_x - p1_pos_x;
      offset_y  =  norm_y - p1_pos_y;

      p1_pos_x  =  norm_x;
      p1_pos_y  =  norm_y;

      offset_x  +=  old_offset_x;
      offset_y  +=  old_offset_y;

      update_pos = false;
   }

   glUniform4f ( offset_loc  ,  offset_x , offset_y , 0.0 , 0.0 );

   glVertexAttribPointer ( position_loc, 3, GL_FLOAT, false, 0, vertexArray );
   glEnableVertexAttribArray ( position_loc );
   glDrawArrays ( GL_TRIANGLE_STRIP, 0, 5 );
}

int init_gl_resources() {
   GLuint vertexShader   = load_shader ( vertex_glsl , GL_VERTEX_SHADER  );     // load vertex shader
   GLuint fragmentShader = load_shader ( fragment_glsl , GL_FRAGMENT_SHADER );  // load fragment shader

   GLuint shaderProgram  = glCreateProgram ();                 // create program object
   glAttachShader ( shaderProgram, vertexShader );             // and attach both...
   glAttachShader ( shaderProgram, fragmentShader );           // ... shaders to it

   glLinkProgram ( shaderProgram );    // link the program
   glUseProgram  ( shaderProgram );    // and select it for usage

   //// now get the locations (kind of handle) of the shaders variables
   position_loc  = glGetAttribLocation  ( shaderProgram , "position" );
   phase_loc     = glGetUniformLocation ( shaderProgram , "phase"    );
   offset_loc    = glGetUniformLocation ( shaderProgram , "offset"   );
   if ( position_loc < 0  ||  phase_loc < 0  ||  offset_loc < 0 ) {
	   return 1;
   }

   return 0;
}
