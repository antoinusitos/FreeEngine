#version 110

uniform vec4 vColor;
uniform vec2 vTexCoord;

uniform sampler2D uTexture;
uniform vec2 uTextureSize;
uniform float uPixelSize;

void main()
{
	vec2 pixelSizeNorm = uPixelSize / uTextureSize;
	vec2 textCoord = vTexCoord - mod(vTexCoord, pixelSizeNorm);
	gl_FragColor = vColor * texture2D(uTexture, textCoord);
};