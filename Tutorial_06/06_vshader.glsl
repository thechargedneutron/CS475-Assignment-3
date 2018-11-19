#version 330

in vec4 vPosition;
in vec4 vColor;
in vec3 vNormal;

in vec2 texCoord;

out vec3 normal;
out vec4 eye;
out vec4 COLOR;
out vec2 TEX;

uniform mat4 uModelViewMatrix;
uniform mat3 normalMatrix;
uniform mat4 viewMatrix;

void main (void)
{
  gl_Position = uModelViewMatrix * vPosition;
  normal = (normalMatrix * normalize(vNormal));
  eye = - (gl_Position);
  TEX = texCoord;
  COLOR = vColor;
}
