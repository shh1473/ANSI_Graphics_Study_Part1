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

uniform sampler2D u_srcTexture;
uniform sampler2D u_luminanceTexture;

void main()
{
	vec4 src = texture(u_srcTexture, v_texCoord);
	vec3 luminance = texture(u_luminanceTexture, v_texCoord).rgb;

	FragColor = vec4(src.rgb + (luminance * 1.25), src.a);
}
