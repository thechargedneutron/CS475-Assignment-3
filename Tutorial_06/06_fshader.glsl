#version 330

in vec4 color;

uniform float thresh;

out vec4 frag_color;

uniform sampler2D texture;
in vec2 tex;
void main ()
{
    if(thresh > 0.5){
      frag_color = texture2D(texture, tex);
    }
    else {
      frag_color = color;
    }
}
