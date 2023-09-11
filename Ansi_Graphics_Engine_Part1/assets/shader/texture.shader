# shader_vertex
# version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

uniform mat4 u_MVP;

uniform float u_textureScale;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);
	v_texCoord = texCoord * u_textureScale;
}


# shader_fragment
# version 460 core

layout(location = 0) out vec4 FragColor;

in vec2 v_texCoord;

uniform sampler2D u_diffuseMap;

void main()
{
	FragColor = texture(u_diffuseMap, v_texCoord);
}
