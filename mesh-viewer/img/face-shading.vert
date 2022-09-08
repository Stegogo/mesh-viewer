#version 330 core

out vec3 vViewPos;

in vec3 vertexPosition;
in vec3 vertexNormal;

uniform mat4 modelView;
uniform mat3 modelViewNormal;
uniform mat4 mvp;

void main()
{
    vec4 pos = vec4(vertexPosition, 1.0);
    vec4 mpos = modelView * pos;
    gl_Position = mvp * vec4(vertexPosition, 1.0);
    vViewPos = -mpos.xyz;
};
