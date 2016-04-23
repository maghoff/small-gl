#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

void render(int width, int height);
void flip();

Display *display;
Window win;

int init_x11() {
	display = XOpenDisplay(NULL);   // open the standard display (the primary screen)
	if (display == NULL) {
		return 1;
	}

	Window root  =  DefaultRootWindow( display );   // get the root window (usually the whole screen)

	XSetWindowAttributes  swa;
	swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask;

	win  =  XCreateWindow(   // create a window with the provided parameters
		display, root,
		0, 0, 800, 480,   0,
		CopyFromParent, InputOutput,
		CopyFromParent, CWEventMask,
		&swa
	);

	XSetWindowAttributes  xattr;

	xattr.override_redirect = False;
	XChangeWindowAttributes ( display, win, CWOverrideRedirect, &xattr );

	XWMHints hints;
	hints.input = True;
	hints.flags = InputHint;
	XSetWMHints(display, win, &hints);

	XMapWindow ( display , win );             // make the window visible on the screen
	XStoreName ( display , win , "GL test" ); // give the window a name

	//// get identifiers for the provided atom name strings
	Atom wm_state   = XInternAtom ( display, "_NET_WM_STATE", False );
	Atom fullscreen = XInternAtom ( display, "_NET_WM_STATE_FULLSCREEN", False );

	XEvent xev;
	xev.type                 = ClientMessage;
	xev.xclient.window       = win;
	xev.xclient.message_type = wm_state;
	xev.xclient.format       = 32;
	xev.xclient.data.l[0]    = 1;
	xev.xclient.data.l[1]    = fullscreen;
	XSendEvent (                // send an event mask to the X-server
		display,
		DefaultRootWindow ( display ),
		False,
		SubstructureNotifyMask,
		&xev );

	return 0;
}

void loop() {
	XWindowAttributes gwa;
	XGetWindowAttributes(display, win, &gwa);

	for (;;) {
		while (XPending(display)) {
			XEvent xev;
			XNextEvent(display, &xev);
			if (xev.type == KeyPress) return;
		}

		render(gwa.width, gwa.height);
		flip();
	}
}
