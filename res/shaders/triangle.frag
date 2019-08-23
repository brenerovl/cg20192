#version 330 core

in vec3 C;

void main() {

    vec3 l1 = vec3(-1.0f, -1.0f, 0.0f);
    float dl1 = clamp(dot(C, l1), 0.0f, 1.0f);

    vec3 l2 = -1 * l1;
    float dl2 = clamp(dot(C, l2), 0.0f, 1.0f);

    vec3 c_orange = vec3(0.98f, 0.65f, 0.0f);
    vec3 c_blue = 1 - c_orange;

    vec3 c_gi = vec3(1,1,1);

    vec3 fc = c_blue * dl1 + c_orange * dl2 + c_gi*0.2;

    gl_FragColor = vec4(fc, 1.0f);
}
