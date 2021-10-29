attribute vec2 in_texcoor;
attribute vec3 in_normal;
attribute vec4 in_vertex;
attribute vec4 in_color;
uniform vec3 in_light;
uniform mat4 in_modelToWorldMatrix;
uniform mat4 in_modelToWorldMatrixIT;
uniform mat4 in_lightModelToWorldMatrix;
uniform mat4 in_viewMatrix;
uniform mat4 in_projMatrix;
varying vec2 vTexcoor;
varying vec3 normal;
varying vec3 light;
varying vec4 color;

void main()
{
  light = vec3(in_lightModelToWorldMatrix * vec4(in_light, 0));
  normal = vec3(in_modelToWorldMatrixIT * vec4(in_normal, 0));
  vTexcoor = in_texcoor;
  gl_Position = in_projMatrix * in_viewMatrix * in_modelToWorldMatrix  * in_vertex;
  color = in_color;
}
