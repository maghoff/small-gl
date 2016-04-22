#include <stdbool.h>

#include <GLES2/gl2.h>
#include <EGL/egl.h>

int init_x11(Display**, Window*);

void init_gl_resources();
void render(int width, int height);

int main()
{
	Display *x_display;
	Window win;
	if (init_x11(&x_display, &win) != 0) return 1;

	///////  the egl part  //////////////////////////////////////////////////////////////////
   //  egl provides an interface to connect the graphics related functionality of openGL ES
   //  with the windowing interface and functionality of the native operation system (X11
   //  in our case.

	EGLDisplay  egl_display;
	EGLContext  egl_context;
	EGLSurface  egl_surface;

   egl_display  =  eglGetDisplay( (EGLNativeDisplayType) x_display );
   if ( egl_display == EGL_NO_DISPLAY ) {
      return 1;
   }

   if ( !eglInitialize( egl_display, NULL, NULL ) ) {
      return 1;
   }

   EGLint attr[] = {       // some attributes to set up our egl-interface
      EGL_BUFFER_SIZE, 16,
      EGL_RENDERABLE_TYPE,
      EGL_OPENGL_ES2_BIT,
      EGL_NONE
   };

   EGLConfig  ecfg;
   EGLint     num_config;
   if ( !eglChooseConfig( egl_display, attr, &ecfg, 1, &num_config ) ) {
      return 1;
   }

   if ( num_config != 1 ) {
      return 1;
   }

   egl_surface = eglCreateWindowSurface ( egl_display, ecfg, win, NULL );
   if ( egl_surface == EGL_NO_SURFACE ) {
      return 1;
   }

   //// egl-contexts collect all state descriptions needed required for operation
   EGLint ctxattr[] = {
      EGL_CONTEXT_CLIENT_VERSION, 2,
      EGL_NONE
   };
   egl_context = eglCreateContext ( egl_display, ecfg, EGL_NO_CONTEXT, ctxattr );
   if ( egl_context == EGL_NO_CONTEXT ) {
      return 1;
   }

   //// associate the egl-context with the egl-surface
   eglMakeCurrent( egl_display, egl_surface, egl_surface, egl_context );


   init_gl_resources();

	XWindowAttributes  gwa;
	XGetWindowAttributes ( x_display , win , &gwa );

   bool quit = false;
   while ( !quit ) {    // the main loop

      while ( XPending ( x_display ) ) {   // check for events from the x-server

         XEvent  xev;
         XNextEvent( x_display, &xev );
         if ( xev.type == KeyPress )   quit = true;
      }

      render(gwa.width, gwa.height);   // now we finally put something on the screen
   eglSwapBuffers ( egl_display, egl_surface );  // get the rendered buffer to the screen
   }


   ////  cleaning up...
   eglDestroyContext ( egl_display, egl_context );
   eglDestroySurface ( egl_display, egl_surface );
   eglTerminate      ( egl_display );
   XDestroyWindow    ( x_display, win );
   XCloseDisplay     ( x_display );

   return 0;
}
