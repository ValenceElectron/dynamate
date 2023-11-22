#version 460

in vec4 varyingColor;

out vec4 fragColor;

uniform mat4 mMat;
uniform mat4 vMat;
uniform mat4 pMat;

void main(void) {
    fragColor = varyingColor;
}