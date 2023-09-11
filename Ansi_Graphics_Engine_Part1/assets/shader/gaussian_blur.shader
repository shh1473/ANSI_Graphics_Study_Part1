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

uniform int u_radius;

uniform sampler2D u_srcTexture;

void main()
{
	vec4 src = texture(u_srcTexture, v_texCoord);

    vec2 texelSize = 1.0 / textureSize(u_srcTexture, 0);
    vec3 colorSum = vec3(0.0);
    float weightSum = 0.0;

    for (int x = -u_radius; x <= u_radius; ++x)
    {
        for (int y = -u_radius; y <= u_radius; ++y)
        {
            vec2 offset = vec2(float(x), float(y)) * texelSize;
            float weight = exp(-(offset.x * offset.x + offset.y * offset.y) / (2.0 * float(u_radius * u_radius)));

            colorSum += texture(u_srcTexture, v_texCoord + offset).rgb * weight;
            weightSum += weight;
        }
    }

    FragColor = vec4(colorSum / weightSum, 1.0);
}
