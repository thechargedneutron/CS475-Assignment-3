#include "gl_framework.hpp"

extern GLfloat xrot,yrot,zrot,c_xrot,c_yrot,c_zrot,c_xpos,c_ypos,c_zpos;
extern bool enable_perspective, move_left;
extern glm::vec3 move_pointer;
extern bool mouse_clicked;
extern glm::mat4 projection_matrix;
extern glm::mat4 view_matrix;
extern glm::mat4 modelview_matrix;

extern std::vector<float> bezier_x;
extern std::vector<float> bezier_y;
extern std::vector<float> bezier_z;

namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
      move_left=true;
    else if (key == GLFW_KEY_RIGHT )
      yrot += 1.0;
    else if (key == GLFW_KEY_UP )
      xrot -= 1.0;
    else if (key == GLFW_KEY_DOWN )
      xrot += 1.0;
    else if (key == GLFW_KEY_PAGE_UP )
      zrot -= 1.0;
    else if (key == GLFW_KEY_PAGE_DOWN)
      zrot += 1.0;
    else if (key == GLFW_KEY_A  )
      c_yrot -= 1.0;
    else if (key == GLFW_KEY_D  )
      c_yrot += 1.0;
    else if (key == GLFW_KEY_W  )
      c_xrot -= 1.0;
    else if (key == GLFW_KEY_S  )
      c_xrot += 1.0;        
    else if (key == GLFW_KEY_Q  )
      c_zrot -= 1.0;
    else if (key == GLFW_KEY_E  )
      c_zrot += 0.5;   
    else if (key == GLFW_KEY_J  )
      c_ypos -= 0.5;
    else if (key == GLFW_KEY_L  )
      c_ypos += 0.5;
    else if (key == GLFW_KEY_I  )
      c_xpos -= 0.5;
    else if (key == GLFW_KEY_K  )
      c_xpos += 0.5;        
    else if (key == GLFW_KEY_U  )
      c_zpos -= 0.5;
    else if (key == GLFW_KEY_O  )
      c_zpos += 0.5; 
  }

  void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
  {
    if(action == GLFW_PRESS){
    double xpos, ypos;
    glm::mat4 matrix;
    glm::vec4 source;
    glm::vec4 ans;
    glm::vec4 pos3d;
    float a;
    glfwGetCursorPos(window, &xpos, &ypos);
    GLint m_viewport[4];
    glGetIntegerv(GL_VIEWPORT, m_viewport);

    matrix = glm::inverse(modelview_matrix*projection_matrix);
    source[0] = ((c_xpos - xpos)/m_viewport[2])*2.0 - 1.0;
    source[1] = -((c_ypos - ypos)/m_viewport[3])*2.0 - 1.0;
    source[2] = (c_zpos - 1)/(54);
    source[3] = 1.0;
    a = source[0] * matrix[0][3] + source[1] * matrix[1][3] + source[2] * matrix[2][3] + matrix[3][3]; 
    ans = matrix*source;

    std::cout<<a<<" "<<ans[0]/a<<" "<<ans[1]/a<<" "<<ans[2]/a<<std::endl;

    move_pointer[0] = ans[0]/a;
    move_pointer[1] = ans[1]/a;
    move_pointer[2] = ans[2]/a;
    bezier_x.append(move_pointer[0]);
    bezier_y.append(move_pointer[1]);
    bezier_z.append(move_pointer[2]);
    mouse_clicked=true;

  }

    // GLdouble x, y, z;
    // gluUnProject(xpos, ypos, 0.0, view_matrix, projection_matrix, glGetIntegerv(GL_VIEWPORT, m_viewport), x, y, z);
    // std::cout<<x<<" "<<y<<" "<<z<<std::endl;
  }
};