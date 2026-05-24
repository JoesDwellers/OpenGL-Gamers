#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform float rotation;

out vec3 ourColor; // What we pass to fragment shader

void main() {
    mat3 rotationMat = mat3(
        1/2.0f * (1 + cos(rotation)), 1/2.0f * (1 - cos(rotation)), 1/sqrt(2) * (sin(rotation)),
        1/2.0f * (1 - cos(rotation)), 1/2.0f * (1 + cos(rotation)), -1/sqrt(2) * (sin(rotation)),
        -1/sqrt(2) * (sin(rotation)), 1/sqrt(2) * (sin(rotation)), cos(rotation)
    );
    vec3 newPos = aPos * rotationMat;
    gl_Position = vec4(newPos.x, newPos.y, newPos.z, 1.0);
    ourColor = aColor;
}