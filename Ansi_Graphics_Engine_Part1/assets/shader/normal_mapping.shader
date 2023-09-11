# shader_vertex
# version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec3 v_position;
out vec2 v_texCoord;
out vec3 v_normal;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);

	v_position = position;
	v_texCoord = texCoord * 5.0;
	v_normal = normal;
}


# shader_fragment
# version 460 core

layout(location = 0) out vec4 FragColor;

in vec3 v_position;
in vec2 v_texCoord;
in vec3 v_normal;

uniform mat4 u_worldMatrix;

uniform vec3 u_cameraPosition;

uniform vec3 u_lightColor;
uniform vec3 u_lightDirection;

uniform float u_specularIntensity;
uniform float u_specularPower;

uniform sampler2D u_diffuseMap;
uniform sampler2D u_normalMap;

mat3 ComputeTBN(vec3 n, mat3 worldMatrix)
{
	vec3 p_dx = dFdx(v_position.xyz);
	vec3 p_dy = dFdy(v_position.xyz);
	vec2 uv_dx = dFdx(v_texCoord);
	vec2 uv_dy = dFdy(v_texCoord);

	vec3 t = normalize((p_dx * uv_dy.t) - (p_dy * uv_dx.t));
	vec3 b = normalize((p_dx * uv_dy.s) - (p_dy * uv_dx.s));

	t = normalize(worldMatrix * t);
	b = normalize(worldMatrix * b);
	n = normalize(worldMatrix * n);

	return mat3(t, b, n);
}

void main()
{
	vec3 worldPosition = (u_worldMatrix * vec4(v_position, 1.0)).xyz;

	/* Tangent Normal */
	mat3 tbn = ComputeTBN(v_normal, mat3(u_worldMatrix));
	vec3 tangentNormal = texture(u_normalMap, v_texCoord).rgb;
	tangentNormal = normalize(tangentNormal * 2.0 - 1.0);
	tangentNormal = normalize(tbn * tangentNormal);

	/* Albedo */
	vec4 albedo = texture(u_diffuseMap, v_texCoord);
	albedo.rgb = pow(albedo.rgb, vec3(2.2));

	/* Diffuse Light - Directional */
	float diffuse = max(dot(tangentNormal, -u_lightDirection), 0.0);

	/* Specular Light - Directional */
	vec3 dirToCamera = normalize(u_cameraPosition - worldPosition);
	vec3 halfWay = normalize(dirToCamera - u_lightDirection);
	float specular = pow(max(dot(halfWay, tangentNormal), 0.0), u_specularPower) * u_specularIntensity;

	/* Combine Lights */
	vec3 totalLight = u_lightColor * (diffuse + specular);

	/* Final Color */
	vec3 finalColor = albedo.rgb * totalLight;
	finalColor = pow(finalColor, vec3(1.0 / 2.2));

	FragColor = vec4(finalColor, albedo.a);
}
