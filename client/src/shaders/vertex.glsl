#version 460 core
layout (location = 0) in vec3 aPos;
uniform int rotation;

void main() {
    float rads = radians(rotation);
    mat3 rotationMat = mat3(
        cos(rads), 0, sin(rads),
        0, 1, 0,
        -sin(rads), 0, cos(rads)
    );
    vec3 newPos = aPos * rotationMat;
    gl_Position = vec4(newPos.x, newPos.y, newPos.z, 1.0);
}