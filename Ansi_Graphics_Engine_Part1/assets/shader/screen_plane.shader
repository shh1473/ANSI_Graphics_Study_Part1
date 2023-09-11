# shader_vertex
# version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 o_texCoord;

uniform mat4 u_worldMatrix;

void main()
{
	gl_Position = u_worldMatrix * vec4(position, 1.0);
	gl_Position.z = 1.0;
	o_texCoord = texCoord;
}


# shader_fragment
# version 460 core

layout(location = 0) out vec4 FragColor;

in vec2 o_texCoord;

uniform vec4 u_diffuseColor;

uniform sampler2D u_diffuseMap;

void main()
{
	FragColor = u_diffuseColor * texture(u_diffuseMap, o_texCoord);
}
