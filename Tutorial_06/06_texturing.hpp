/*
  A program which opens a window and draws the "color cube."

  Use the arrow keys and PgUp,PgDn,
  keys to make the cube move.

  Written by -
               Parag Chaudhuri
*/
#ifndef _COLORCUBE_HPP_
#define _COLORCUBE_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

GLuint vPosition, vColor, vNormal;
std::vector<glm::mat4> matrixStack;

GLuint uModelViewMatrix;

class HNode {
  //glm::vec4 * vertices;
  //glm::vec4 * colors;
  GLfloat tx,ty,tz,rx,ry,rz;
  GLfloat max_rx, max_ry, max_rz;
  GLfloat min_rx, min_ry, min_rz;

  std::size_t vertex_buffer_size;
  std::size_t color_buffer_size;

  GLuint num_vertices;
  GLuint vao,vbo;

  glm::mat4 rotation;
  glm::mat4 translation;

  std::vector<HNode*> children;
  HNode* parent;
  std::string NodeName;

  void update_matrices();

  public:
  HNode (HNode*, GLuint, glm::vec4*,  glm::vec4*, glm::vec4*, std::size_t, std::size_t, std::size_t, std::string);
  HNode (HNode*, GLuint, glm::vec4*,  glm::vec4*, std::size_t, std::size_t, std::string, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
  //HNode (HNode* , glm::vec4*,  glm::vec4*,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);

  void add_child(HNode*);
  void render();
  void change_parameters(GLfloat,GLfloat,GLfloat,GLfloat,GLfloat,GLfloat);
  void render_tree();
  void inc_rx();
  void inc_ry();
  void inc_rz();
  void dec_rx();
  void dec_ry();
  void dec_rz();
  std::string get_node_name();
};

glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
  glm::mat4* mult;
  mult = new glm::mat4(1.0f);

  for(int i=0;i<matStack.size();i++){
    *mult = (*mult) * matStack[i];
  }

  return mult;
}


HNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_colours, glm::vec4* a_normals, std::size_t v_size, std::size_t c_size, std::size_t n_size, std::string name){

  num_vertices = num_v;
  vertex_buffer_size = v_size;
  color_buffer_size = c_size;
  NodeName = name;
  // initialize vao and vbo of the object;

  min_rx = 0.0;
  max_rx = 0.0;

  min_ry = 0.0;
  max_ry = 0.0;

  min_rz = 0.0;
  max_rz = 0.0;


  //Ask GL for a Vertex Attribute Objects (vao)
  glGenVertexArrays (1, &vao);
  //Ask GL for aVertex Buffer Object (vbo)
  glGenBuffers (1, &vbo);

  //bind them
  glBindVertexArray (vao);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);


  glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size + n_size, NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
  glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, a_colours );
  glBufferSubData( GL_ARRAY_BUFFER, color_buffer_size + vertex_buffer_size, n_size, a_normals );

  //setup the vertex array as per the shader
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

  glEnableVertexAttribArray( vNormal );
  glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size + color_buffer_size));


  // set parent

  if(a_parent == NULL){
    parent = NULL;
  }
  else{
    parent = a_parent;
    parent->add_child(this);
  }

  //initial parameters are set to 0;

  tx=ty=tz=rx=ry=rz=0;

  update_matrices();
}


HNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_colours, std::size_t v_size, std::size_t c_size, std::string name, GLfloat a, GLfloat b, GLfloat c, GLfloat d, GLfloat e, GLfloat f){

  num_vertices = num_v;
  vertex_buffer_size = v_size;
  color_buffer_size = c_size;
  NodeName = name;

  min_rx = a;
  max_rx = b;

  min_ry = c;
  max_ry = d;

  min_rz = e;
  max_rz = f;

  // initialize vao and vbo of the object;


  //Ask GL for a Vertex Attribute Objects (vao)
  glGenVertexArrays (1, &vao);
  //Ask GL for aVertex Buffer Object (vbo)
  glGenBuffers (1, &vbo);

  //bind them
  glBindVertexArray (vao);
  glBindBuffer (GL_ARRAY_BUFFER, vbo);


  glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size, NULL, GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
  glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, a_colours );

  //setup the vertex array as per the shader
  glEnableVertexAttribArray( vPosition );
  glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

  glEnableVertexAttribArray( vColor );
  glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));


  // set parent

  if(a_parent == NULL){
    parent = NULL;
  }
  else{
    parent = a_parent;
    parent->add_child(this);
  }

  //initial parameters are set to 0;

  tx=ty=tz=rx=ry=rz=0;

  update_matrices();
}

void HNode::update_matrices(){

  rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
  rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
  rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

  translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));


}

void HNode::add_child(HNode* a_child){
  children.push_back(a_child);

}

void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz){
  tx = atx;
  ty = aty;
  tz = atz;
  rx = arx;
  ry = ary;
  rz = arz;

  update_matrices();
}

void HNode::render(){

  //matrixStack multiply
  glm::mat4* ms_mult = multiply_stack(matrixStack);

  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
  glBindVertexArray (vao);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  // for memory
  delete ms_mult;

}

void HNode::render_tree(){

  matrixStack.push_back(translation);
  matrixStack.push_back(rotation);

  render();
  for(int i=0;i<children.size();i++){
    children[i]->render_tree();
  }
  matrixStack.pop_back();
  matrixStack.pop_back();

}

void HNode::inc_rx(){
  if (rx < max_rx){
  rx++;
  update_matrices();
}
}


void HNode::inc_ry(){
  if (ry < max_ry){
  ry++;
  update_matrices();
}
}

void HNode::inc_rz(){
  if (rz < max_rz){
  rz++;
  update_matrices();
}
}

void HNode::dec_rx(){
  if (rx > min_rx){
  rx--;
  update_matrices();
}
}

void HNode::dec_ry(){
  if (ry > min_ry){
  ry--;
  update_matrices();
}
}

void HNode::dec_rz(){
  if (rz > min_rz){
  rz--;
  update_matrices();
}
}

std::string HNode::get_node_name(){
  return NodeName;
}




// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;
// Camera position and rotation Parameters
GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = 6.0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;
//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=false;

//-----------BOX-----------------------------
HNode* root_node;
HNode* curr_node;
HNode* b_lower_front_node;
HNode* b_lower_lower_node;
HNode* b_lower_right_node;
HNode* b_lower_left_node;
HNode* b_lower_back_node;
HNode* b_upper_front_node;
HNode* b_upper_lower_node;
HNode* b_upper_right_node;
HNode* b_upper_left_node;
HNode* b_upper_back_node;
//-------------------------------------------------------------------------


//-------------------------------------------------------------------------

#endif
