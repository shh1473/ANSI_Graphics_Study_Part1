# shader_vertex
# version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

/* Output - Light */
out vec4 v_lightClipPosition;

/* Output - Object */
out vec3 v_position;
out vec2 v_texCoord;
out vec3 v_normal;

/* Uniform - Light */
uniform mat4 u_directionalLightMVP;

/* Uniform - Object */
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);

	v_lightClipPosition = u_directionalLightMVP * vec4(position, 1.0);
	v_position = position;
	v_texCoord = texCoord * 5.0;
	v_normal = normal;
}


# shader_fragment
# version 460 core

layout(location = 0) out vec4 FragColor;

/* Input - Light */
in vec4 v_lightClipPosition;

/* Input - Object */
in vec3 v_position;
in vec2 v_texCoord;
in vec3 v_normal;

/* Uniform - Matrix */
uniform mat4 u_worldMatrix;

/* Uniform - Camera */
uniform vec3 u_cameraPosition;

/* Uniform - Ambient Light */
uniform vec3 u_ambientLightDownColor;
uniform vec3 u_ambientLightColorRange;

/* Uniform - Directional Light */
uniform vec3 u_directionalLightColor;
uniform vec3 u_directionalLightDirection;

/* Uniform - Material */
uniform float u_specularIntensity;
uniform float u_specularPower;

/* Uniform - Texture */
uniform sampler2D u_depthMap;
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
	vec3 ambientLight = vec3(0.0);
	vec3 directionalLight = vec3(0.0);

	/* Tangent Normal */
	mat3 tbn = ComputeTBN(v_normal, mat3(u_worldMatrix));
	vec3 tangentNormal = texture(u_normalMap, v_texCoord).rgb;
	tangentNormal = normalize(tangentNormal * 2.0 - 1.0);
	tangentNormal = normalize(tbn * tangentNormal);

	/* Albedo */
	vec4 albedo = texture(u_diffuseMap, v_texCoord);
	albedo.rgb = pow(albedo.rgb, vec3(2.2));

	/* Ambient Diffuse Light */
	float upNormal = (tangentNormal.y * 0.5) + 0.5;
	ambientLight = u_ambientLightDownColor + (upNormal * u_ambientLightColorRange);

	/* Directional Diffuse Light */
	float directionalDiffuse = max(dot(tangentNormal, -u_directionalLightDirection), 0.0);
	directionalLight += directionalDiffuse;

	/* Directional Specular Light */
	vec3 dirToCamera = normalize(u_cameraPosition - worldPosition);
	vec3 halfWay = normalize(dirToCamera - u_directionalLightDirection);
	directionalLight += pow(max(dot(halfWay, tangentNormal), 0.0), u_specularPower) * u_specularIntensity;

	/* Shadow */
	vec3 lightPosition = v_lightClipPosition.xyz / v_lightClipPosition.w;
	float depthBias = tan(acos(directionalDiffuse)) * 0.005;
	depthBias = clamp(depthBias, 0.0, 0.001);
	float depthMapDepth = texture(u_depthMap, lightPosition.xy * 0.5 + 0.5).x + depthBias;
	float shadow = (lightPosition.z > depthMapDepth) ? 0.2 : 1.0;

	/* Combine Lights */
	directionalLight *= u_directionalLightColor;
	vec3 totalLight = (ambientLight + directionalLight) * shadow;

	/* Final Color */
	vec3 finalColor = albedo.rgb * totalLight;
	finalColor = pow(finalColor, vec3(1.0 / 2.2));

	FragColor = vec4(finalColor, albedo.a);
}
