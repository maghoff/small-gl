attribute vec4        position;
varying mediump vec2  pos;
uniform vec4          offset;

void main()
{
	gl_Position = position + offset;
	pos = position.xy;
}
