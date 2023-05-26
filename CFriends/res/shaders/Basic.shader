#shader vertex
#version 330 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;

out vec4 vertexColor;

void main() {
	gl_Position = vec4(position, 0.0, 1.0);
	vertexColor = color;
}





#shader fragment
#version 330 core

out vec4 color;
in vec4 vertexColor;

uniform vec4 u_Color;

void main() {
	color = vertexColor;
}