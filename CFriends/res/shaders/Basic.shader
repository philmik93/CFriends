#shader vertex
#version 330 core
layout(location = 0) in vec2 position;
layout(location = 1) in float rotation;
layout(location = 2) in vec2 translation;
layout(location = 3) in vec4 colorIn;
layout(location = 4) in vec2 texCoords;
out vec4 vertexColor;
out vec2 v_texCoords;

float a;
float b;
vec4 colorTrans;

uniform vec4 u_color;

void main() {

	a = position[0] / 600.0 * 2.0 - 1.0;
	b = position.y / 400.0 * -2.0 + 1.0;



	gl_Position = vec4(a, b, 0.0, 1);

	colorTrans[0] = colorIn[0] / 255.0;
	colorTrans[1] = colorIn[1] / 255.0;
	colorTrans[2] = colorIn[2] / 255.0;
	colorTrans[3] = colorIn[3] / 255.0;

	vertexColor = colorTrans;
	v_texCoords = texCoords;
}





#shader fragment
#version 330 core

out vec4 color;
in vec4 vertexColor;
in vec2 v_texCoords;

uniform int DRAW;
uniform sampler2D u_texture;

void main() {
	if (DRAW == 1)
	{
		color = texture(u_texture, v_texCoords);
	}
	else if (DRAW == 0)
	{
		color = vertexColor;
	}
}