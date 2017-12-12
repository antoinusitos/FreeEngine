uniform sampler2D texture;

void main()
{
	vec4 pixel = gl_Color;
	float color = pixel.x + pixel.y + pixel.z;
	color = color / 3.0;
	pixel.x = color;
	pixel.y = color;
	pixel.z = color;
	pixel.a = 255;
    gl_FragColor = pixel;
}