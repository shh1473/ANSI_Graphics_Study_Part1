# shader_vertex
# version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec3 v_worldPosition;
out vec2 v_texCoord;
out vec3 v_worldNormal;

uniform mat4 u_MVP;
uniform mat4 u_worldMatrix;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);

	v_worldPosition = (u_worldMatrix * vec4(position, 1.0)).xyz;
	v_texCoord = texCoord * 5.0;
	v_worldNormal = normalize(mat3(u_worldMatrix) * normalize(normal));
}


# shader_fragment
# version 460 core

layout(location = 0) out vec4 FragColor;

in vec3 v_worldPosition;
in vec2 v_texCoord;
in vec3 v_worldNormal;

uniform vec3 u_cameraPosition;

uniform vec3 u_lightColor;
uniform vec3 u_lightDirection;

uniform float u_specularIntensity;
uniform float u_specularPower;

uniform sampler2D u_diffuseMap;

void main()
{
	/* Albedo */
	vec4 albedo = texture(u_diffuseMap, v_texCoord);
	albedo.rgb = pow(albedo.rgb, vec3(2.2));

	/* Diffuse Light - Directional */
	float diffuse = max(dot(v_worldNormal, -u_lightDirection), 0.0);

	/* Specular Light - Directional */
	vec3 dirToCamera = normalize(u_cameraPosition - v_worldPosition);
	vec3 halfWay = normalize(dirToCamera - u_lightDirection);
	float specular = pow(max(dot(halfWay, v_worldNormal), 0.0), u_specularPower) * u_specularIntensity;
	
	/* Combine Lights */
	vec3 totalLight = u_lightColor * (diffuse + specular);

	/* Final Color */
	vec3 finalColor = albedo.rgb * totalLight;
	finalColor = pow(finalColor, vec3(1.0 / 2.2));

	FragColor = vec4(finalColor, albedo.a);
}
