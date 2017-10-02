#version 130

out vec4 color;
out vec2 uv;
out float fog;

void main(void) {
  vec4 cameraPos = vec4(0, 0, 0, 1) * gl_ModelViewProjectionMatrix;
  fog = distance(cameraPos, gl_Vertex) * 0.003;
  fog = fog * fog;
  vec4 vert = vec4(gl_Vertex.xyz, 1.0);
  gl_Position = gl_ModelViewProjectionMatrix * vert;
  color = gl_Color;
  uv = gl_MultiTexCoord0.st;
};
