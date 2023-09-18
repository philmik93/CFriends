#shader vertex
#version 330 core
layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoords;
out vec4 vertexColor;
out vec2 v_texCoords;

void main() {
	gl_Position = vec4(position, 0.0, 1);
	vertexColor = color;
	v_texCoords = texCoords;
}





#shader fragment
#version 330 core

out vec4 color;
in vec4 vertexColor;
in vec2 v_texCoords;

uniform vec4 u_Color;
uniform sampler2D u_texture;

void main() {
	//color = texture(u_texture, v_texCoords);
	color = vec4(1.0f,1.0f,1.0f,1.0f);
}