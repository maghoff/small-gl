#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

int init_x11(Display **x_display, Window *win) {
	*x_display = XOpenDisplay(NULL);   // open the standard display (the primary screen)
	if (*x_display == NULL) {
		return 1;
	}

	Window root  =  DefaultRootWindow( *x_display );   // get the root *window (usually the whole screen)

	XSetWindowAttributes  swa;
	swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask;

	*win  =  XCreateWindow(   // create a *window with the provided parameters
		*x_display, root,
		0, 0, 800, 480,   0,
		CopyFromParent, InputOutput,
		CopyFromParent, CWEventMask,
		&swa
	);

	XSetWindowAttributes  xattr;

	xattr.override_redirect = False;
	XChangeWindowAttributes ( *x_display, *win, CWOverrideRedirect, &xattr );

	XWMHints hints;
	hints.input = True;
	hints.flags = InputHint;
	XSetWMHints(*x_display, *win, &hints);

	XMapWindow ( *x_display , *win );             // make the *window visible on the screen
	XStoreName ( *x_display , *win , "GL test" ); // give the *window a name

	//// get identifiers for the provided atom name strings
	Atom wm_state   = XInternAtom ( *x_display, "_NET_WM_STATE", False );
	Atom fullscreen = XInternAtom ( *x_display, "_NET_WM_STATE_FULLSCREEN", False );

	XEvent xev;
	xev.type                 = ClientMessage;
	xev.xclient.window       = *win;
	xev.xclient.message_type = wm_state;
	xev.xclient.format       = 32;
	xev.xclient.data.l[0]    = 1;
	xev.xclient.data.l[1]    = fullscreen;
	XSendEvent (                // send an event mask to the X-server
		*x_display,
		DefaultRootWindow ( *x_display ),
		False,
		SubstructureNotifyMask,
		&xev );

	return 0;
}
