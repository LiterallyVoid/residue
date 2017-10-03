#version 130

in vec4 color;
in vec2 uv;
in float fog;
uniform sampler2D texture;
in vec4 pos;

void main(void) {
  vec4 fogC = vec4(0.3, 0.6, 1.0, 1.0);

  gl_FragColor = mix(color * texture2D(texture, uv), fogC, min(1.0, max(fog, 0.0)));
};
