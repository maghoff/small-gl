int init_x11();
int init_egl();
int init_gl_resources();

void loop();

int main()
{
	if (init_x11() != 0) return 1;
	if (init_egl() != 0) return 2;
	if (init_gl_resources() != 0) return 3;

	loop();

	return 0;
}
