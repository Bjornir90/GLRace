#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>



int loadShaderprograms(void);
void key_callback(GLFWwindow* window, int key, int scancode,
	int action, int mods);
void char_callback(GLFWwindow* window, unsigned int key);

extern bool perspective;

// texture
//extern cv::Mat image;
extern GLuint textureID;