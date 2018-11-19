/*
  CSX75 Tutorial 6 Texturing a Cube


  Modified from An Introduction to OpenGL Programming,
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  Written by Aditya Prakash, 2015
*/
//////////// LOAD TEXTURES
///////// DEBUG

#include "06_texturing.hpp"
#include "texture.hpp"

GLuint shaderProgram;
GLuint tex;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;
glm::mat3 normal_matrix;

GLuint viewMatrix;
GLuint normalMatrix;

GLuint test;
//-----------------------------------------------------------------

int number_of_vao = 20;
GLuint vbo[20], vao[20];

//6 faces, 2 triangles/face, 3 vertices/triangle
const int num_vertices = 36;

glm::vec4 texCoordinates[8];
//Eight vertices in homogenous coordinates

float s = 16.0;

void get_vec4(glm::vec4 bottom_left, float xspan, float yspan, float zspan, glm::vec4* positions){
  /*
  Takes the bottom left vec4 as input, along with the dimensions of the cube. Make the rest of the
  coordinates accordingly.
  */
  positions[0] = bottom_left;
  positions[1] = bottom_left + glm::vec4(xspan, 0.0, 0.0, 0.0);
  positions[2] = bottom_left + glm::vec4(xspan, yspan, 0.0, 0.0);
  positions[3] = bottom_left + glm::vec4(0.0, yspan, 0.0, 0.0);

  positions[4] = bottom_left + glm::vec4(0.0, 0.0, -zspan, 0.0);
  positions[5] = bottom_left + glm::vec4(xspan, 0.0, -zspan, 0.0);
  positions[6] = bottom_left + glm::vec4(xspan, yspan, -zspan, 0.0);
  positions[7] = bottom_left + glm::vec4(0.0, yspan, -zspan, 0.0);
}

glm::vec4 room_top[8];
glm::vec4 room_bottom[8];
glm::vec4 room_right[8];
glm::vec4 room_left[8];
glm::vec4 room_front[8];
glm::vec4 room_back[8];

glm::vec4 tv_table[8];
glm::vec4 tv_screen[8];
glm::vec4 tv_stand[8];

glm::vec4 center_table[8];

glm::vec4 wall_light_top[8];
glm::vec4 wall_light_left[8];
glm::vec4 wall_light_right[8];
glm::vec4 wall_light_front[8];

///////////////////////Lower Box/////////////////////////////////
glm::vec4 b_lower_front[8] = {
  glm::vec4(-7.5, -8.0, 3.0, 1.0),
  glm::vec4(7.5, -8.0, 3.0, 1.0),
  glm::vec4(7.5, 0.0, 3.0, 1.0),
  glm::vec4(-7.5, 0.0, 3.0, 1.0),
  glm::vec4(-7.5, -8.0, 2.5, 1.0),
  glm::vec4(7.5, -8.0, 2.5, 1.0),
  glm::vec4(7.5, 0.0, 2.5, 1.0),
  glm::vec4(-7.5, 0.0, 2.5, 1.0)
};
glm::vec4 b_lower_back[8] = {
  glm::vec4(-7.5, -8.0, -3.0, 1.0),
  glm::vec4(7.5, -8.0, -3.0, 1.0),
  glm::vec4(7.5, 0.0, -3.0, 1.0),
  glm::vec4(-7.5, 0.0, -3.0, 1.0),
  glm::vec4(-7.5, -8.0, -2.5, 1.0),
  glm::vec4(7.5, -8.0, -2.5, 1.0),
  glm::vec4(7.5, 0.0, -2.5, 1.0),
  glm::vec4(-7.5, 0.0, -2.5, 1.0)
};
glm::vec4 b_lower_lower[8] = {
  glm::vec4(-7.5, -8.0, 2.5, 1.0),
  glm::vec4(7.5, -8.0, 2.5, 1.0),
  glm::vec4(7.5, -7.5, 2.5, 1.0),
  glm::vec4(-7.5, -7.5, 2.5, 1.0),
  glm::vec4(-7.5, -8.0, -2.5, 1.0),
  glm::vec4(7.5, -8.0, -2.5, 1.0),
  glm::vec4(7.5, -7.5, -2.5, 1.0),
  glm::vec4(-7.5, -7.5, -2.5, 1.0)
};
glm::vec4 b_lower_left[8] = {
  glm::vec4(-8.0, -8.0, 3.0, 1.0),
  glm::vec4(-7.5, -8.0, 3.0, 1.0),
  glm::vec4(-7.5, 0.0, 3.0, 1.0),
  glm::vec4(-8.0, 0.0, 3.0, 1.0),
  glm::vec4(-8.0, -8.0, -3.0, 1.0),
  glm::vec4(-7.5, -8.0, -3.0, 1.0),
  glm::vec4(-7.5, 0.0, -3.0, 1.0),
  glm::vec4(-8.0, 0.0, -3.0, 1.0)
};
glm::vec4 b_lower_right[8] = {
  glm::vec4(8.0, -8.0, 3.0, 1.0),
  glm::vec4(7.5, -8.0, 3.0, 1.0),
  glm::vec4(7.5, 0.0, 3.0, 1.0),
  glm::vec4(8.0, 0.0, 3.0, 1.0),
  glm::vec4(8.0, -8.0, -3.0, 1.0),
  glm::vec4(7.5, -8.0, -3.0, 1.0),
  glm::vec4(7.5, 0.0, -3.0, 1.0),
  glm::vec4(8.0, 0.0, -3.0, 1.0)
};
///////////////////////Upper Box/////////////////////////////////
glm::vec4 b_upper_front[8] = {
  glm::vec4(-7.5, 8.0, 0.5, 1.0),
  glm::vec4(7.5, 8.0, 0.5, 1.0),
  glm::vec4(7.5, 0.0, 0.5, 1.0),
  glm::vec4(-7.5, 0.0, 0.5, 1.0),
  glm::vec4(-7.5, 8.0, 0.0, 1.0),
  glm::vec4(7.5, 8.0, 0.0, 1.0),
  glm::vec4(7.5, 0.0, 0.0, 1.0),
  glm::vec4(-7.5, 0.0, 0.0, 1.0)
};
glm::vec4 b_upper_back[8] = {
  glm::vec4(-7.5, 8.0, -0.5, 1.0),
  glm::vec4(7.5, 8.0, -0.5, 1.0),
  glm::vec4(7.5, 0.0, -0.5, 1.0),
  glm::vec4(-7.5, 0.0, -0.5, 1.0),
  glm::vec4(-7.5, 8.0, 0.0, 1.0),
  glm::vec4(7.5, 8.0, 0.0, 1.0),
  glm::vec4(7.5, 0.0, 0.0, 1.0),
  glm::vec4(-7.5, 0.0, 0.0, 1.0)
};
glm::vec4 b_upper_lower[8] = {
  glm::vec4(-8.0, 0.5, 3.0, 1.0),
  glm::vec4(8.0, 0.5, 3.0, 1.0),
  glm::vec4(8.0, 0.0, 3.0, 1.0),
  glm::vec4(-8.0, 0.0, 3.0, 1.0),
  glm::vec4(-8.0, 0.5, -3.0, 1.0),
  glm::vec4(8.0, 0.5, -3.0, 1.0),
  glm::vec4(8.0, 0.0, -3.0, 1.0),
  glm::vec4(-8.0, 0.0, -3.0, 1.0)
};
glm::vec4 b_upper_left[8] = {
  glm::vec4(-0.5, 8.0, 3.0, 1.0),
  glm::vec4(0.0, 8.0, 3.0, 1.0),
  glm::vec4(0.0, 0.0, 3.0, 1.0),
  glm::vec4(-0.5, 0.0, 3.0, 1.0),
  glm::vec4(-0.5, 8.0, -3.0, 1.0),
  glm::vec4(0.0, 8.0, -3.0, 1.0),
  glm::vec4(0.0, 0.0, -3.0, 1.0),
  glm::vec4(-0.5, 0.0, -3.0, 1.0)
};
glm::vec4 b_upper_right[8] = {
  glm::vec4(0.5, 8.0, 3.0, 1.0),
  glm::vec4(0.0, 8.0, 3.0, 1.0),
  glm::vec4(0.0, 0.0, 3.0, 1.0),
  glm::vec4(0.5, 0.0, 3.0, 1.0),
  glm::vec4(0.5, 8.0, -3.0, 1.0),
  glm::vec4(0.0, 8.0, -3.0, 1.0),
  glm::vec4(0.0, 0.0, -3.0, 1.0),
  glm::vec4(0.5, 0.0, -3.0, 1.0)
};
/////////////////////////////////////////////////////////////



void initialize_coordinates() {
  get_vec4(glm::vec4(-2*s, -s+2*s, 1.5*s, 1.0), 4*s, 2*s, 3*s, room_top);
  get_vec4(glm::vec4(-2*s, -s-2*s, 1.5*s, 1.0), 4*s, 2*s, 3*s, room_bottom);
  get_vec4(glm::vec4(-2*s+4*s, -s, 1.5*s, 1.0), 4*s, 2*s, 3*s, room_right);
  get_vec4(glm::vec4(-2*s-4*s, -s, 1.5*s, 1.0), 4*s, 2*s, 3*s, room_left);
  get_vec4(glm::vec4(-2*s, -s, 1.5*s-3*s, 1.0), 4*s, 2*s, 3*s, room_front);
  get_vec4(glm::vec4(-2*s, -s, 1.5*s+3*s, 1.0), 4*s, 2*s, 3*s, room_back);

  get_vec4(glm::vec4(-22.0, -14.0, -19.0, 1.0), 32.0, 5.0, 5.0, tv_table);
  get_vec4(glm::vec4(-12.0, -8.0, -21.0, 1.0), 14.0, 7.0, 1.0, tv_screen);
  get_vec4(glm::vec4(-8.5, -9.0, -21.0, 1.0), 7.0, 1.0, 1.0, tv_stand);

  get_vec4(glm::vec4(-6.0, -15.0, -11.0, 1.0), 12.0, 1.5, 8, center_table);

  get_vec4(glm::vec4(-2.0, 10.0, -21.0, 1.0), 4.0, 1.0, 3.0, wall_light_top);
  get_vec4(glm::vec4(-3.0, 7.0, -20.0, 1.0), 1.0, 4.0, 4.0, wall_light_left);
  get_vec4(glm::vec4(2.0, 7.0, -20.0, 1.0), 1.0, 4.0, 4.0, wall_light_right);
  get_vec4(glm::vec4(-2.0, 7.0, -20.0, 1.0), 4.0, 4.0, 1.0, wall_light_front);

  get_vec4(glm::vec4(-6.0, -10.0, -11.0, 1.0), 5.0, 1.5, 8, b_lower_back);

}


glm::vec4 bookshelf[8] = {
  glm::vec4(14.0, 0.0, 24.0, 1.0),
  glm::vec4(28.0, 0.0, 24.0, 1.0),
  glm::vec4(28.0, 12.0, 24.0, 1.0),
  glm::vec4(14.0, 12.0, 24.0, 1.0),
  glm::vec4(14.0, 0.0, 16.0, 1.0),
  glm::vec4(28.0, 0.0, 16.0, 1.0),
  glm::vec4(28.0, 12.0, 16.0, 1.0),
  glm::vec4(14.0, 12.0, 16.0, 1.0),
};


glm::vec4 normals[8];
//RGBA colors
glm::vec4 colors[8] = {
  glm::vec4(0.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 0.0, 0.0, 1.0),
  glm::vec4(1.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 1.0, 0.0, 1.0),
  glm::vec4(0.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 0.0, 1.0, 1.0),
  glm::vec4(1.0, 1.0, 1.0, 1.0),
  glm::vec4(0.0, 1.0, 1.0, 1.0)
};

glm::vec2 t_coords[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 1.0),
  glm::vec2( 1.0, 0.0),
  glm::vec2( 1.0, 1.0)
};

glm::vec4 color(0.6, 0.6, 0.6, 1.0);
glm::vec4 black(0.1, 0.1, 0.1, 1.0);
glm::vec4 white(0.2, 0.7, 0.7, 1.0);
glm::vec4 red(1.0, 0.2, 0.2, 1.0);
glm::vec4 yellow(0.8, 0.8, 0.0, 1.0);
glm::vec4 green(0.2, 0.7, 0.2, 1.0);
glm::vec4 blue(0.2, 0.2, 0.7, 1.0);

int tri_idx=0;
int ind = 0;

glm::vec4 v_room_front[num_vertices];
glm::vec4 v_room_back[num_vertices];
glm::vec4 v_room_right[num_vertices];
glm::vec4 v_room_left[num_vertices];
glm::vec4 v_room_top[num_vertices];
glm::vec4 v_room_bottom[num_vertices];

glm::vec4 v_bookshelf[num_vertices];
glm::vec4 v_tv_table[num_vertices];
glm::vec4 v_tv_screen[num_vertices];
glm::vec4 v_tv_stand[num_vertices];

glm::vec4 v_center_table[num_vertices];

glm::vec4 v_wall_light_top[num_vertices];
glm::vec4 v_wall_light_left[num_vertices];
glm::vec4 v_wall_light_right[num_vertices];
glm::vec4 v_wall_light_front[num_vertices];


/******************BOX DEFINITIONS**********************/

/********************ALIEN COLORS*****************************/

glm::vec4 grey(0.5, 0.5, 0.5, 1.0);
glm::vec4 brown(0.0, 0.5, 1.0, 1.0);
glm::vec4 pastel_red(1.0, 0.4, 0.4, 1.0);
glm::vec4 dark_red(0.545, 0.0, 0.0, 1.0);

/*************************************************************/


/*********************Lower Box***************/
glm::vec4 v_b_lower_front[num_vertices];
glm::vec4 v_b_lower_back[num_vertices];
glm::vec4 v_b_lower_right[num_vertices];
glm::vec4 v_b_lower_left[num_vertices];
glm::vec4 v_b_lower_lower[num_vertices];
/*********************************************/
/*********************Upper Box***************/
glm::vec4 v_b_upper_front[num_vertices];
glm::vec4 v_b_upper_back[num_vertices];
glm::vec4 v_b_upper_right[num_vertices];
glm::vec4 v_b_upper_left[num_vertices];
glm::vec4 v_b_upper_lower[num_vertices];
/*********************************************/

glm::vec4 v_colors_grey[num_vertices];
glm::vec4 v_colors_red[num_vertices];
glm::vec4 v_colors_dark_red[num_vertices];
glm::vec4 v_colors_pastel_red[num_vertices];
glm::vec4 v_colors_brown[num_vertices];




glm::vec4 v_colors[num_vertices];
glm::vec4 v_normals[num_vertices];
glm::vec2 tex_coords[num_vertices];
// quad generates two triangles for each face and assigns colors to the vertices
void quad(int a, int b, int c, int d, glm::vec4 color)
{
  ind = a;             //<-------------------------------a
  v_room_top[tri_idx] = room_top[ind];
  v_room_bottom[tri_idx] = room_bottom[ind];
  v_room_left[tri_idx] = room_left[ind];
  v_room_right[tri_idx] = room_right[ind];
  v_room_front[tri_idx] = room_front[ind];
  v_room_back[tri_idx] = room_back[ind];
  v_bookshelf[tri_idx] = bookshelf[ind];
  v_tv_table[tri_idx] = tv_table[ind];
  v_tv_screen[tri_idx] = tv_screen[ind];
  v_tv_stand[tri_idx] = tv_stand[ind];
  v_center_table[tri_idx] = center_table[ind];

  v_wall_light_top[tri_idx] = wall_light_top[ind];
  v_wall_light_left[tri_idx] = wall_light_left[ind];
  v_wall_light_right[tri_idx] = wall_light_right[ind];
  v_wall_light_front[tri_idx] = wall_light_front[ind];

  v_colors[tri_idx] = color;
  tex_coords[tri_idx] = t_coords[1];


    /************BOX********************************/
  v_b_lower_front[tri_idx] = b_lower_front[ind];
  v_b_lower_right[tri_idx] = b_lower_right[ind];
  v_b_lower_left[tri_idx] = b_lower_left[ind];
  v_b_lower_lower[tri_idx] = b_lower_lower[ind];
  v_b_lower_back[tri_idx] = b_lower_back[ind];
  v_b_upper_front[tri_idx] = b_upper_front[ind];
  v_b_upper_right[tri_idx] = b_upper_right[ind];
  v_b_upper_left[tri_idx] = b_upper_left[ind];
  v_b_upper_lower[tri_idx] = b_upper_lower[ind];
  v_b_upper_back[tri_idx] = b_upper_back[ind];

  v_colors_grey[tri_idx] = grey;
  v_colors_red[tri_idx] = red;
  v_colors_dark_red[tri_idx] = dark_red;
  v_colors_pastel_red[tri_idx] = pastel_red;
  v_colors_brown[tri_idx] = brown;




  tri_idx++;

  ind = b;             //<-------------------------------b
  v_room_top[tri_idx] = room_top[ind];
  v_room_bottom[tri_idx] = room_bottom[ind];
  v_room_left[tri_idx] = room_left[ind];
  v_room_right[tri_idx] = room_right[ind];
  v_room_front[tri_idx] = room_front[ind];
  v_room_back[tri_idx] = room_back[ind];
  v_bookshelf[tri_idx] = bookshelf[ind];
  v_tv_table[tri_idx] = tv_table[ind];
  v_tv_screen[tri_idx] = tv_screen[ind];
  v_tv_stand[tri_idx] = tv_stand[ind];
  v_center_table[tri_idx] = center_table[ind];

  v_wall_light_top[tri_idx] = wall_light_top[ind];
  v_wall_light_left[tri_idx] = wall_light_left[ind];
  v_wall_light_right[tri_idx] = wall_light_right[ind];
  v_wall_light_front[tri_idx] = wall_light_front[ind];

  v_colors[tri_idx] = color;
  tex_coords[tri_idx] = t_coords[0];

      /************BOX********************************/
  v_b_lower_front[tri_idx] = b_lower_front[ind];
  v_b_lower_right[tri_idx] = b_lower_right[ind];
  v_b_lower_left[tri_idx] = b_lower_left[ind];
  v_b_lower_lower[tri_idx] = b_lower_lower[ind];
  v_b_lower_back[tri_idx] = b_lower_back[ind];
  v_b_upper_front[tri_idx] = b_upper_front[ind];
  v_b_upper_right[tri_idx] = b_upper_right[ind];
  v_b_upper_left[tri_idx] = b_upper_left[ind];
  v_b_upper_lower[tri_idx] = b_upper_lower[ind];
  v_b_upper_back[tri_idx] = b_upper_back[ind];

  v_colors_grey[tri_idx] = grey;
  v_colors_red[tri_idx] = red;
  v_colors_dark_red[tri_idx] = dark_red;
  v_colors_pastel_red[tri_idx] = pastel_red;
  v_colors_brown[tri_idx] = brown;



  tri_idx++;

  ind = c;             //<-------------------------------c
  v_room_top[tri_idx] = room_top[ind];
  v_room_bottom[tri_idx] = room_bottom[ind];
  v_room_left[tri_idx] = room_left[ind];
  v_room_right[tri_idx] = room_right[ind];
  v_room_front[tri_idx] = room_front[ind];
  v_room_back[tri_idx] = room_back[ind];
  v_bookshelf[tri_idx] = bookshelf[ind];
  v_tv_table[tri_idx] = tv_table[ind];
  v_tv_screen[tri_idx] = tv_screen[ind];
  v_tv_stand[tri_idx] = tv_stand[ind];
  v_center_table[tri_idx] = center_table[ind];

  v_wall_light_top[tri_idx] = wall_light_top[ind];
  v_wall_light_left[tri_idx] = wall_light_left[ind];
  v_wall_light_right[tri_idx] = wall_light_right[ind];
  v_wall_light_front[tri_idx] = wall_light_front[ind];

  v_colors[tri_idx] = color;
  tex_coords[tri_idx] = t_coords[2];

      /************BOX********************************/
  v_b_lower_front[tri_idx] = b_lower_front[ind];
  v_b_lower_right[tri_idx] = b_lower_right[ind];
  v_b_lower_left[tri_idx] = b_lower_left[ind];
  v_b_lower_lower[tri_idx] = b_lower_lower[ind];
  v_b_lower_back[tri_idx] = b_lower_back[ind];
  v_b_upper_front[tri_idx] = b_upper_front[ind];
  v_b_upper_right[tri_idx] = b_upper_right[ind];
  v_b_upper_left[tri_idx] = b_upper_left[ind];
  v_b_upper_lower[tri_idx] = b_upper_lower[ind];
  v_b_upper_back[tri_idx] = b_upper_back[ind];

  v_colors_grey[tri_idx] = grey;
  v_colors_red[tri_idx] = red;
  v_colors_dark_red[tri_idx] = dark_red;
  v_colors_pastel_red[tri_idx] = pastel_red;
  v_colors_brown[tri_idx] = brown;



  tri_idx++;

  ind = a;             //<-------------------------------a
  v_room_top[tri_idx] = room_top[ind];
  v_room_bottom[tri_idx] = room_bottom[ind];
  v_room_left[tri_idx] = room_left[ind];
  v_room_right[tri_idx] = room_right[ind];
  v_room_front[tri_idx] = room_front[ind];
  v_room_back[tri_idx] = room_back[ind];
  v_bookshelf[tri_idx] = bookshelf[ind];
  v_tv_table[tri_idx] = tv_table[ind];
  v_tv_screen[tri_idx] = tv_screen[ind];
  v_tv_stand[tri_idx] = tv_stand[ind];
  v_center_table[tri_idx] = center_table[ind];

  v_wall_light_top[tri_idx] = wall_light_top[ind];
  v_wall_light_left[tri_idx] = wall_light_left[ind];
  v_wall_light_right[tri_idx] = wall_light_right[ind];
  v_wall_light_front[tri_idx] = wall_light_front[ind];

  v_colors[tri_idx] = color;
  tex_coords[tri_idx] = t_coords[1];

      /************BOX********************************/
  v_b_lower_front[tri_idx] = b_lower_front[ind];
  v_b_lower_right[tri_idx] = b_lower_right[ind];
  v_b_lower_left[tri_idx] = b_lower_left[ind];
  v_b_lower_lower[tri_idx] = b_lower_lower[ind];
  v_b_lower_back[tri_idx] = b_lower_back[ind];
  v_b_upper_front[tri_idx] = b_upper_front[ind];
  v_b_upper_right[tri_idx] = b_upper_right[ind];
  v_b_upper_left[tri_idx] = b_upper_left[ind];
  v_b_upper_lower[tri_idx] = b_upper_lower[ind];
  v_b_upper_back[tri_idx] = b_upper_back[ind];

  v_colors_grey[tri_idx] = grey;
  v_colors_red[tri_idx] = red;
  v_colors_dark_red[tri_idx] = dark_red;
  v_colors_pastel_red[tri_idx] = pastel_red;
  v_colors_brown[tri_idx] = brown;



  tri_idx++;


  ind = c;             //<-------------------------------c
  v_room_top[tri_idx] = room_top[ind];
  v_room_bottom[tri_idx] = room_bottom[ind];
  v_room_left[tri_idx] = room_left[ind];
  v_room_right[tri_idx] = room_right[ind];
  v_room_front[tri_idx] = room_front[ind];
  v_room_back[tri_idx] = room_back[ind];
  v_bookshelf[tri_idx] = bookshelf[ind];
  v_tv_table[tri_idx] = tv_table[ind];
  v_tv_screen[tri_idx] = tv_screen[ind];
  v_tv_stand[tri_idx] = tv_stand[ind];
  v_center_table[tri_idx] = center_table[ind];

  v_wall_light_top[tri_idx] = wall_light_top[ind];
  v_wall_light_left[tri_idx] = wall_light_left[ind];
  v_wall_light_right[tri_idx] = wall_light_right[ind];
  v_wall_light_front[tri_idx] = wall_light_front[ind];

  v_colors[tri_idx] = color;
  tex_coords[tri_idx] = t_coords[2];

      /************BOX********************************/
  v_b_lower_front[tri_idx] = b_lower_front[ind];
  v_b_lower_right[tri_idx] = b_lower_right[ind];
  v_b_lower_left[tri_idx] = b_lower_left[ind];
  v_b_lower_lower[tri_idx] = b_lower_lower[ind];
  v_b_lower_back[tri_idx] = b_lower_back[ind];
  v_b_upper_front[tri_idx] = b_upper_front[ind];
  v_b_upper_right[tri_idx] = b_upper_right[ind];
  v_b_upper_left[tri_idx] = b_upper_left[ind];
  v_b_upper_lower[tri_idx] = b_upper_lower[ind];
  v_b_upper_back[tri_idx] = b_upper_back[ind];

  v_colors_grey[tri_idx] = grey;
  v_colors_red[tri_idx] = red;
  v_colors_dark_red[tri_idx] = dark_red;
  v_colors_pastel_red[tri_idx] = pastel_red;
  v_colors_brown[tri_idx] = brown;



  tri_idx++;

  ind = d;             //<-------------------------------d
  v_room_top[tri_idx] = room_top[ind];
  v_room_bottom[tri_idx] = room_bottom[ind];
  v_room_left[tri_idx] = room_left[ind];
  v_room_right[tri_idx] = room_right[ind];
  v_room_front[tri_idx] = room_front[ind];
  v_room_back[tri_idx] = room_back[ind];
  v_bookshelf[tri_idx] = bookshelf[ind];
  v_tv_table[tri_idx] = tv_table[ind];
  v_tv_screen[tri_idx] = tv_screen[ind];
  v_tv_stand[tri_idx] = tv_stand[ind];
  v_center_table[tri_idx] = center_table[ind];

  v_wall_light_top[tri_idx] = wall_light_top[ind];
  v_wall_light_left[tri_idx] = wall_light_left[ind];
  v_wall_light_right[tri_idx] = wall_light_right[ind];
  v_wall_light_front[tri_idx] = wall_light_front[ind];

  v_colors[tri_idx] = color;
  tex_coords[tri_idx] = t_coords[3];

      /************BOX********************************/
  v_b_lower_front[tri_idx] = b_lower_front[ind];
  v_b_lower_right[tri_idx] = b_lower_right[ind];
  v_b_lower_left[tri_idx] = b_lower_left[ind];
  v_b_lower_lower[tri_idx] = b_lower_lower[ind];
  v_b_lower_back[tri_idx] = b_lower_back[ind];
  v_b_upper_front[tri_idx] = b_upper_front[ind];
  v_b_upper_right[tri_idx] = b_upper_right[ind];
  v_b_upper_left[tri_idx] = b_upper_left[ind];
  v_b_upper_lower[tri_idx] = b_upper_lower[ind];
  v_b_upper_back[tri_idx] = b_upper_back[ind];

  v_colors_grey[tri_idx] = grey;
  v_colors_red[tri_idx] = red;
  v_colors_dark_red[tri_idx] = dark_red;
  v_colors_pastel_red[tri_idx] = pastel_red;
  v_colors_brown[tri_idx] = brown;



  tri_idx++;
 }

// generate 12 triangles: 36 vertices and 36 colors
void colorcube(void)
{
  quad( 1, 0, 3, 2, red);  //normal   +z
  quad( 2, 3, 7, 6, green); // normal +y
  quad( 3, 0, 4, 7, white); // normal -x
  quad( 6, 5, 1, 2, yellow); //normal +x
  quad( 4, 5, 6, 7, black); //normal -z
  quad( 5, 4, 0, 1, blue);  //normal -y
}

void setnormal(void){
  v_normals[0] = glm::vec4(0.0, 0.0, 1.0, 1.0);
  v_normals[1] = glm::vec4(0.0, 0.0, 1.0, 1.0);
  v_normals[2] = glm::vec4(0.0, 0.0, 1.0, 1.0);
  v_normals[3] = glm::vec4(0.0, 0.0, 1.0, 1.0);
  v_normals[4] = glm::vec4(0.0, 0.0, 1.0, 1.0);
  v_normals[5] = glm::vec4(0.0, 0.0, 1.0, 1.0);

  v_normals[6] = glm::vec4(0.0, 1.0, 0.0, 1.0);
  v_normals[7] = glm::vec4(0.0, 1.0, 0.0, 1.0);
  v_normals[8] = glm::vec4(0.0, 1.0, 0.0, 1.0);
  v_normals[9] = glm::vec4(0.0, 1.0, 0.0, 1.0);
  v_normals[10] = glm::vec4(0.0, 1.0, 0.0, 1.0);
  v_normals[11] = glm::vec4(0.0, 1.0, 0.0, 1.0);

  v_normals[12] = glm::vec4(-1.0, 0.0, 0.0, 1.0);
  v_normals[13] = glm::vec4(-1.0, 0.0, 0.0, 1.0);
  v_normals[14] = glm::vec4(-1.0, 0.0, 0.0, 1.0);
  v_normals[15] = glm::vec4(-1.0, 0.0, 0.0, 1.0);
  v_normals[16] = glm::vec4(-1.0, 0.0, 0.0, 1.0);
  v_normals[17] = glm::vec4(-1.0, 0.0, 0.0, 1.0);

  v_normals[18] = glm::vec4(1.0, 0.0, 0.0, 1.0);
  v_normals[19] = glm::vec4(1.0, 0.0, 0.0, 1.0);
  v_normals[20] = glm::vec4(1.0, 0.0, 0.0, 1.0);
  v_normals[21] = glm::vec4(1.0, 0.0, 0.0, 1.0);
  v_normals[22] = glm::vec4(1.0, 0.0, 0.0, 1.0);
  v_normals[23] = glm::vec4(1.0, 0.0, 0.0, 1.0);

  v_normals[24] = glm::vec4(0.0, 0.0, -1.0, 1.0);
  v_normals[25] = glm::vec4(0.0, 0.0, -1.0, 1.0);
  v_normals[26] = glm::vec4(0.0, 0.0, -1.0, 1.0);
  v_normals[27] = glm::vec4(0.0, 0.0, -1.0, 1.0);
  v_normals[28] = glm::vec4(0.0, 0.0, -1.0, 1.0);
  v_normals[29] = glm::vec4(0.0, 0.0, -1.0, 1.0);

  v_normals[30] = glm::vec4(0.0, -1.0, 0.0, 1.0);
  v_normals[31] = glm::vec4(0.0, -1.0, 0.0, 1.0);
  v_normals[32] = glm::vec4(0.0, -1.0, 0.0, 1.0);
  v_normals[33] = glm::vec4(0.0, -1.0, 0.0, 1.0);
  v_normals[34] = glm::vec4(0.0, -1.0, 0.0, 1.0);
  v_normals[35] = glm::vec4(0.0, -1.0, 0.0, 1.0);

}



void make_cuboid(int index, glm::vec4* v_pos, glm::vec2* tex_pos, glm::vec4* norm_pos, std::size_t v_count, std::size_t tex_count, std::size_t norm_count, GLuint vPosition, GLuint texCoord, GLuint vNormal)
{
//Set 0 as the current array to be used by binding it
glBindVertexArray (vao[index]);
//Set 0 as the current buffer to be used by binding it
glBindBuffer (GL_ARRAY_BUFFER, vbo[index]);

//colorcube();

//Copy the points into the current buffer
glBufferData (GL_ARRAY_BUFFER, v_count + tex_count + norm_count, NULL, GL_STATIC_DRAW);
glBufferSubData( GL_ARRAY_BUFFER, 0, v_count, v_pos );
glBufferSubData( GL_ARRAY_BUFFER, v_count, tex_count, tex_pos);
glBufferSubData( GL_ARRAY_BUFFER, tex_count + v_count, norm_count, norm_pos );
// set up vertex array
//Position
glEnableVertexAttribArray( vPosition );
glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
//Textures
glEnableVertexAttribArray( texCoord );
glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(v_count) );

//Normal
glEnableVertexAttribArray( vNormal );
glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(v_count + tex_count) );



}

void make_cuboid(int index, glm::vec4* v_pos, glm::vec4* tex_pos, glm::vec4* norm_pos, std::size_t v_count, std::size_t tex_count, std::size_t norm_count, GLuint vPosition, GLuint vColor, GLuint vNormal)
{
//Set 0 as the current array to be used by binding it
glBindVertexArray (vao[index]);
//Set 0 as the current buffer to be used by binding it
glBindBuffer (GL_ARRAY_BUFFER, vbo[index]);

//colorcube();

//Copy the points into the current buffer
glBufferData (GL_ARRAY_BUFFER, v_count + tex_count + norm_count, NULL, GL_STATIC_DRAW);
glBufferSubData( GL_ARRAY_BUFFER, 0, v_count, v_pos );
glBufferSubData( GL_ARRAY_BUFFER, v_count, tex_count, tex_pos);
glBufferSubData( GL_ARRAY_BUFFER, tex_count + v_count, norm_count, norm_pos );
// set up vertex array
//Position
glEnableVertexAttribArray( vPosition );
glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
//Textures
glEnableVertexAttribArray( vColor );
glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(v_count) );

//Normal
glEnableVertexAttribArray( vNormal );
glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(v_count + tex_count) );



}


//-----------------------------------------------------------------

void initBuffersGL(void)
{

  initialize_coordinates();

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("06_vshader.glsl");
  std::string fragment_shader_file("06_fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" );
  vNormal = glGetAttribLocation( shaderProgram, "vNormal" );
  GLuint texCoord = glGetAttribLocation( shaderProgram, "texCoord" );
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
  normalMatrix =  glGetUniformLocation( shaderProgram, "normalMatrix");
  viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");

  test = glGetUniformLocation(shaderProgram, "thresh");
  glUniform1f(test, 1.0);



  // Load Textures

  //Ask GL for two Vertex Attribute Objects (vao) , one for the sphere and one for the wireframe
  glGenVertexArrays (number_of_vao, vao);
  //Ask GL for two Vertex Buffer Object (vbo)
  glGenBuffers (number_of_vao, vbo);

  colorcube();
  setnormal();

  make_cuboid(0, v_room_top, tex_coords, v_normals, sizeof(v_room_top), sizeof(tex_coords), sizeof(v_normals), vPosition, texCoord, vNormal);
  make_cuboid(1, v_room_bottom, tex_coords, v_normals, sizeof(v_room_bottom), sizeof(tex_coords), sizeof(v_normals), vPosition, texCoord, vNormal);
  make_cuboid(2, v_room_front, tex_coords, v_normals, sizeof(v_room_front), sizeof(tex_coords), sizeof(v_normals), vPosition, texCoord, vNormal);
  make_cuboid(3, v_room_back, tex_coords, v_normals, sizeof(v_room_back), sizeof(tex_coords), sizeof(v_normals), vPosition, texCoord, vNormal);
  make_cuboid(4, v_room_right, tex_coords, v_normals, sizeof(v_room_right), sizeof(tex_coords), sizeof(v_normals), vPosition, texCoord, vNormal);
  make_cuboid(5, v_room_left, tex_coords, v_normals, sizeof(v_room_left), sizeof(tex_coords), sizeof(v_normals), vPosition, texCoord, vNormal);

  make_cuboid(6, v_bookshelf, tex_coords, v_normals, sizeof(v_bookshelf), sizeof(tex_coords), sizeof(v_normals), vPosition, texCoord, vNormal);
  make_cuboid(7, v_tv_table, tex_coords, v_normals, sizeof(v_tv_table), sizeof(tex_coords), sizeof(v_normals), vPosition, texCoord, vNormal);
  make_cuboid(8, v_tv_screen, tex_coords, v_normals, sizeof(v_tv_screen), sizeof(tex_coords), sizeof(v_normals), vPosition, texCoord, vNormal);
  make_cuboid(9, v_tv_stand, tex_coords, v_normals, sizeof(v_tv_stand), sizeof(tex_coords), sizeof(v_normals), vPosition, texCoord, vNormal);

  make_cuboid(10, v_center_table, tex_coords, v_normals, sizeof(v_center_table), sizeof(tex_coords), sizeof(v_normals), vPosition, texCoord, vNormal);


  make_cuboid(11, v_wall_light_top, tex_coords, v_normals, sizeof(v_wall_light_top), sizeof(tex_coords), sizeof(v_normals), vPosition, texCoord, vNormal);
  make_cuboid(12, v_wall_light_left, tex_coords, v_normals, sizeof(v_wall_light_left), sizeof(tex_coords), sizeof(v_normals), vPosition, texCoord, vNormal);
  make_cuboid(13, v_wall_light_right, tex_coords, v_normals, sizeof(v_wall_light_right), sizeof(tex_coords), sizeof(v_normals), vPosition, texCoord, vNormal);
  make_cuboid(14, v_wall_light_front, tex_coords, v_normals, sizeof(v_wall_light_front), sizeof(tex_coords), sizeof(v_normals), vPosition, texCoord, vNormal);

  //make_cuboid(11, v_b_lower_back, v_colors_red, v_normals, sizeof(v_b_lower_back), sizeof(v_colors_red), sizeof(v_normals), vPosition, vColor, vNormal);

  //
  b_lower_back_node = new HNode(NULL,num_vertices,v_b_lower_back,v_colors_red,v_normals, sizeof(v_b_lower_back),sizeof(v_colors), sizeof(v_normals), "None");
  b_lower_back_node->change_parameters(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

  root_node = curr_node = b_lower_back_node;

}


void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(xrot), glm::vec3(1.0f,0.0f,0.0f));
  rotation_matrix = glm::rotate(rotation_matrix, glm::radians(yrot), glm::vec3(0.0f,1.0f,0.0f));
  rotation_matrix = glm::rotate(rotation_matrix, glm::radians(zrot), glm::vec3(0.0f,0.0f,1.0f));
  model_matrix = rotation_matrix;

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

  //creating the projection matrix
  projection_matrix = glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 45.0);
//  projection_matrix = glm::frustum(-1.0, 1.0, -1.0, 1.0, 1.0, 5.0);

  view_matrix = projection_matrix*lookat_matrix;

  glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

 // Draw the sphere
  modelview_matrix = view_matrix*model_matrix;
  glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(modelview_matrix));
  normal_matrix = glm::transpose (glm::inverse(glm::mat3(modelview_matrix)));
  glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  //  glBindTexture(GL_TEXTURE_2D, tex);
  // for(int u = 0; u< number_of_vao; u++){
  // glBindVertexArray (vao[u]);
  // glDrawArrays(GL_TRIANGLES, 0, num_vertices);
  // }

  matrixStack.push_back(modelview_matrix);

  glUniform1f(test, 1.0);

  GLuint tex1 = LoadTexture("images/all.bmp",512,512);
  glBindTexture(GL_TEXTURE_2D, tex1);

  glBindVertexArray (vao[0]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  GLuint tex2 = LoadTexture("images/floor_tile.bmp",3000,2160);
  glBindTexture(GL_TEXTURE_2D, tex2);

  glBindVertexArray (vao[1]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  GLuint tex4 = LoadTexture("images/wall.bmp",550,364);
  glBindTexture(GL_TEXTURE_2D, tex4);

  glBindVertexArray (vao[2]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  glBindVertexArray (vao[3]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  glBindVertexArray (vao[4]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  glBindVertexArray (vao[5]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  glBindVertexArray (vao[6]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  GLuint tex3 = LoadTexture("images/tv_table.bmp",600,600);
  glBindTexture(GL_TEXTURE_2D, tex3);
  glBindVertexArray (vao[7]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);


  GLuint tex5 = LoadTexture("images/sony.bmp",2068,1180);
  glBindTexture(GL_TEXTURE_2D, tex5);
  glBindVertexArray (vao[8]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  GLuint tex6 = LoadTexture("images/ss.bmp",600, 400);
  glBindTexture(GL_TEXTURE_2D, tex6);
  glBindVertexArray (vao[9]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  GLuint tex7 = LoadTexture("images/ss.bmp",600, 400);
  glBindTexture(GL_TEXTURE_2D, tex7);
  glBindVertexArray (vao[10]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  glBindVertexArray (vao[11]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  glBindVertexArray (vao[12]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  glBindVertexArray (vao[13]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);

  glBindVertexArray (vao[14]);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices);


  glUniform1f(test, 0.4);

  b_lower_back_node->render_tree();

  // glBindVertexArray (vao[11]);
  // glDrawArrays(GL_TRIANGLES, 0, num_vertices);

}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;
  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  //We don't want the old OpenGL
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(1024, 1024, "CS475/CS675 Tutorial 6: Texturing a cube", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }

  //! Make the window's context current
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }
  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {

      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);

      // Poll for and process events
      glfwPollEvents();
    }

  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------
