# shader_vertex
# version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

/* Output - Light */
out vec4 v_lightClipPosition;

/* Output - Object */
out vec3 v_worldPosition;
out vec3 v_worldNormal;

/* Uniform - Light */
uniform mat4 u_lightMVP;

/* Uniform - Object */
uniform mat4 u_MVP;
uniform mat4 u_worldMatrix;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);

	v_lightClipPosition = u_lightMVP * vec4(position, 1.0);
	v_worldPosition = (u_worldMatrix * vec4(position, 1.0)).xyz;
	v_worldNormal = normalize(mat3(u_worldMatrix) * normal);
}


# shader_fragment
# version 460 core

layout(location = 0) out vec4 FragColor;

/* Input - Light */
in vec4 v_lightClipPosition;

/* Input - Object */
in vec3 v_worldPosition;
in vec3 v_worldNormal;

/* Uniform - Camera */
uniform vec3 u_cameraPosition;

/* Uniform - Light */
uniform vec3 u_lightColor;
uniform vec3 u_lightDirection;

/* Uniform - Material */
uniform float u_specularIntensity;
uniform float u_specularPower;

/* Uniform - Texture */
uniform sampler2D u_depthMap;

void main()
{
	/* Diffuse Light - Directional */
	float diffuse = max(dot(v_worldNormal, -u_lightDirection), 0.0);

	/* Specular Light - Directional */
	vec3 dirToCamera = normalize(u_cameraPosition - v_worldPosition);
	vec3 halfWay = normalize(dirToCamera - u_lightDirection);
	float specular = pow(max(dot(halfWay, v_worldNormal), 0.0), u_specularPower) * u_specularIntensity;

	/* Shadow */
	vec3 lightPosition = v_lightClipPosition.xyz / v_lightClipPosition.w;
	float depthBias = tan(acos(diffuse)) * 0.005;
	depthBias = clamp(depthBias, 0.0, 0.001);
	float depthMapDepth = texture(u_depthMap, lightPosition.xy * 0.5 + 0.5).x + depthBias;
	float shadow = (lightPosition.z > depthMapDepth) ? 0.2 : 1.0;

	/* Combine Lights */
	vec3 totalLight = u_lightColor * (diffuse + specular) * shadow;
	totalLight = pow(totalLight, vec3(1.0 / 2.2));

	FragColor = vec4(totalLight, 1.0);
}
