#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 outColor;
out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    outColor = inColor;
    TexCoord = aTexCoord;
};

#shader fragment
#version 330 core

out vec4 fragColor;

in vec3 outColor;
in vec2 TexCoord;

uniform vec3 color;
uniform sampler2D ourTexture;

void main()
{
    fragColor = texture(ourTexture, TexCoord) * vec4(color * outColor, 1.0);
};