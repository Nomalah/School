#shader vertex

#version 330 core

layout(location = 0) in vec2 u_Position;


void main(){
    gl_Position = vec4(u_Position, 0.0, 1.0);   
}

#shader fragment

#version 330 core

//layout(location = 0) in vec4 u_Color

layout(location = 0) out vec4 color;

void main(){
    color = vec4(1.0, 0.0, 0.0, 1.0);
}