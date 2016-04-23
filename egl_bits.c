#include <EGL/egl.h>

extern EGLNativeDisplayType display;
extern EGLNativeWindowType win;

static EGLDisplay egl_display;
static EGLContext egl_context;
static EGLSurface egl_surface;

int init_egl() {
	egl_display = eglGetDisplay(display);
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

	egl_surface = eglCreateWindowSurface(egl_display, ecfg, win, NULL);
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

	return 0;
}

void flip() {
	eglSwapBuffers(egl_display, egl_surface);
}
