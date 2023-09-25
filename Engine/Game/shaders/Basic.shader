#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 inColor;

out vec3 outColor;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * position;
    outColor = inColor;
};

#shader fragment
#version 330 core

out vec4 fragColor;

in vec3 outColor;

uniform vec3 color;

void main()
{
    fragColor = vec4(color * outColor, 1.0);
};