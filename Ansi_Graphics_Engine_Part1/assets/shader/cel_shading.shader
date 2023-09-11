# shader_vertex
# version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 v_worldPosition;
out vec3 v_worldNormal;

uniform mat4 u_MVP;
uniform mat4 u_worldMatrix;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);

	v_worldPosition = (u_worldMatrix * vec4(position, 1.0)).xyz;
	v_worldNormal = normalize(mat3(u_worldMatrix) * normalize(normal));
}


# shader_fragment
# version 460 core

layout(location = 0) out vec4 FragColor;

in vec3 v_worldPosition;
in vec3 v_worldNormal;

uniform vec3 u_cameraPosition;

uniform vec3 u_lightColor;
uniform vec3 u_lightDirection;

uniform float u_specularIntensity;
uniform float u_specularPower;

uniform float u_celLevel;

void main()
{
	/* Diffuse Light - Directional */
	float diffuse = max(dot(v_worldNormal, -u_lightDirection), 0.0);
	diffuse = max(round(diffuse * u_celLevel) / u_celLevel, 1.0 / u_celLevel); // Cel Shading

	/* Specular Light - Directional */
	vec3 dirToCamera = normalize(u_cameraPosition - v_worldPosition);
	vec3 halfWay = normalize(dirToCamera - u_lightDirection);
	float specular = pow(max(dot(halfWay, v_worldNormal), 0.0), u_specularPower) * u_specularIntensity;
	specular = ceil(specular - 0.3); // Cel Shading

	/* Combine Lights */
	vec3 totalLight = u_lightColor * (diffuse + specular);
	totalLight = pow(totalLight, vec3(1.0 / 2.2));

	FragColor = vec4(totalLight, 1.0);
}
