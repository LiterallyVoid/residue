#version 130

in vec4 color;
in vec2 uv;
in float fog;
uniform sampler2D texture;

void main(void) {
  gl_FragColor = mix(color * texture2D(texture, uv), vec4(0.3, 0.7, 1.0, 1), min(1.0, max(fog, 0.0)));
};
