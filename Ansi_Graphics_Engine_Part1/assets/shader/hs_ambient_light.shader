# shader_vertex
# version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_texCoord;
out vec3 v_worldNormal;

uniform mat4 u_MVP;
uniform mat4 u_worldMatrix;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);

	v_texCoord = texCoord * 5.0;
	v_worldNormal = normalize(mat3(u_worldMatrix) * normal);
}


# shader_fragment
# version 460 core

layout(location = 0) out vec4 FragColor;

in vec2 v_texCoord;
in vec3 v_worldNormal;

uniform vec3 u_downColor;
uniform vec3 u_colorRange;

uniform sampler2D u_diffuseMap;

void main()
{
	/* Albedo */
	vec4 albedo = texture(u_diffuseMap, v_texCoord);
	albedo.rgb = pow(albedo.rgb, vec3(2.2));

	/* Diffuse Light - Ambient */
	float upNormal = (v_worldNormal.y * 0.5) + 0.5;
	vec3 ambientColor = u_downColor + (upNormal * u_colorRange);

	/* Final Color */
	vec3 finalColor = albedo.rgb * ambientColor;
	finalColor = pow(finalColor, vec3(1.0 / 2.2));

	FragColor = vec4(finalColor, albedo.a);
}
