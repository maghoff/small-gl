#include <stdbool.h>

#include <GLES2/gl2.h>
#include <EGL/egl.h>

int init_x11(Display**, Window*);
int init_egl(EGLNativeDisplayType display, EGLNativeWindowType win);
void flip();
void init_gl_resources();
void render(int width, int height);

int main()
{
	Display *x_display;
	Window win;
	if (init_x11(&x_display, &win) != 0) return 1;
	if (init_egl(x_display, win) != 0) return 1;
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
		flip();
	}

	return 0;
}
