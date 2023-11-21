#version 460

layout (location = 0) in vec3 position;

uniform mat4 mMat;
uniform mat4 vMat;
uniform mat4 pMat;

out vec4 varyingColor;

void main(void) {
    gl_Position = pMat * vMat * mMat * vec4(position, 1.0);
    varyingColor = vec4(position, 1.0) * 0.5 + vec4(0.5, 0.5, 0.5, 0.5);
}