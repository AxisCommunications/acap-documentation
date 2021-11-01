
uniform sampler2D in_sampler;
uniform float in_alpha;
uniform vec4 lightColor;

varying vec3 light;
varying vec3 normal;
varying vec2 vTexcoor;

void main() {
  float cosTheta = clamp(dot(normalize(light), normalize(normal)), 0.0,1.0);
  vec4 color = vec4(0.5,0.5,0.5,1.0) + lightColor*cosTheta;
  gl_FragColor = vec4(texture2D(in_sampler, vTexcoor).rgb, in_alpha)*color;
}
