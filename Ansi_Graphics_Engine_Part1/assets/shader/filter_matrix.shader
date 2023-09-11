# shader_vertex
# version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

void main()
{
	gl_Position = position;
	v_texCoord = texCoord;
}


# shader_fragment
# version 460 core

layout(location = 0) out vec4 FragColor;

in vec2 v_texCoord;

uniform mat4 u_filterMatrix;

uniform sampler2D u_srcTexture;

void main()
{
	vec4 src = texture(u_srcTexture, v_texCoord);

	FragColor = u_filterMatrix * src;
}
