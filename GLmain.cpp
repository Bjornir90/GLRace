#include "stdafx.h"
#include "GLmain.h"
#include "td1_utils.h"
//#include "GeoObject.h"
#include "Car.h"

// perspective vs ortho projection
bool perspective = true;

//GeoObject object;

CarBody body;

Car car;

// shader variable pointers
GLint uniform_model;
GLint uniform_inverseModel;
GLint uniform_view;
GLint uniform_proj;
GLint uniform_texture;
GLint uniform_light;
GLint uniform_ambient;
GLint uniform_camera;

// rotation angle
GLfloat rotation_angle_z = 0.0f;
GLfloat rotation_angle_y = 0.0f;
GLfloat rotation_angle_x = 0.0f;
GLfloat translateY = 0.0f;


// light
float lightPosition[3] = { 0.0f , 15.0f , 18.0f };
float lightPos[3] = { 3.0f, 3.0f, 3.0f };
float ambientLight[3] = { 0.1f, 0.1f, 0.1f };
glm::vec3 carPosition = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraPosition = carPosition - glm::vec3(0.0f, -5.0f, 5.0f);
glm::vec3 cameraDirection = carPosition;

int screen_width = 1024;
int screen_height = 768;


GLuint textureID;


struct ShaderProgramSources
{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSources ParseShader(const std::string& filepath)
{

	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return{ ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	//pointer to the beginning of our data, source must exist
	const char* src = source.c_str();
	//(id of source code, number of shaders(strings), adress of source code, length assumes that each 
	//source code string is null terminated, can also get an array of length values)
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	//attach both shaders to our program
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	//delete intermediate shaders as they are now added to the program
	glDeleteShader(vs);
	glDeleteShader(fs);

	// shader parameeter bindings
	uniform_model = glGetUniformLocation(program, "modelMatrix");
	uniform_inverseModel = glGetUniformLocation(program, "inverseModelMatrix");
	uniform_view = glGetUniformLocation(program, "viewMatrix");
	uniform_proj = glGetUniformLocation(program, "projectionMatrix");
	uniform_texture = glGetUniformLocation(program, "mire");
	uniform_light = glGetUniformLocation(program, "light");
	uniform_ambient = glGetUniformLocation(program, "ambient");
	uniform_camera = glGetUniformLocation(program, "cameraDirection");

	if (uniform_model == -1)
		fprintf(stderr, "Could not bind uniform uniform_model\n");

	if (uniform_inverseModel == -1)
		fprintf(stderr, "Could not bind uniform uniform_inverseModel\n");

	if (uniform_view == -1)
		fprintf(stderr, "Could not bind uniform uniform_view\n");

	if (uniform_proj == -1)
		fprintf(stderr, "Could not bind uniform uniform_proj\n");

	if (uniform_texture == -1)
		fprintf(stderr, "Could not bind uniform uniform_texture\n");

	if (uniform_light == -1)
		fprintf(stderr, "Could not bind uniform uniform_light\n");

	return program;
}


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(screen_width, screen_height, "OpenGL Course", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Set key callback function
	//glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCharCallback(window, char_callback);

	//initialize glew AFTER bind to context
	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	glEnable(GL_DEPTH_TEST);

	//create object
	car.buildCar();

	ShaderProgramSources source = ParseShader("car.shader");
	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		// projection matrix
		glm::mat4 projectionMatrix; // Store the projection matrix
		glm::mat4 viewMatrix; // Store the view matrix
							  //glm::mat4 modelMatrix; // Store the model matrix

							  // Projection: Perspective or Ortho matrix
		if (perspective) {
			projectionMatrix
				= glm::perspective(45.0f, (float)screen_width / (float)screen_height, 1.0f, 200.0f);
		}
		else {
			projectionMatrix
				= glm::ortho(-2.0f*(float)screen_width / (float)screen_height,
					2.0f*(float)screen_width / (float)screen_height,
					-2.0f, 2.0f, -10.0f, 10.0f);
		}


		// Camera matrix
		viewMatrix
			= glm::lookAt(
				cameraPosition, // Camera is at (2,2,8), in World Space
				cameraDirection, // and looks in the direction
				glm::vec3(0, 0, 1)
			);

		// Model matrix : a varying rotation matrix (around Oz)


		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader);
		//glBindVertexArray(body._vao);
		glUniformMatrix4fv(uniform_proj, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(uniform_view, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(car.body->getModel()));
		glUniformMatrix4fv(uniform_inverseModel, 1, GL_FALSE, glm::value_ptr(glm::inverse(car.body->getModel())));
		glUniform3fv(uniform_light, 1, lightPosition);
		glUniform3fv(uniform_ambient, 1, ambientLight);
		glUniform3f(uniform_camera, cameraPosition[0], cameraPosition[1], cameraPosition[2]);

		glUniform1i(uniform_texture, 0); //Texture unit 0 is for base images.
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		// draw points from the currently bound VAO with current in-use shader
		glm::vec3 carSpeed = glm::vec3(0, 0, translateY);
		carPosition += glm::vec3(0, 0, translateY);
		printf("%f\n", carPosition[2]);
		car.move(carSpeed);
		car.rotate(rotation_angle_x, rotation_angle_y, rotation_angle_z);
		car.body->draw();

		//The car slows down because of friction forces
		if (translateY > 0.0f) {
			if (translateY < 0.05) {
				translateY -= 0.001*translateY;
			}
			else {
				translateY -= 10 * translateY*translateY;
			}
		}
		if (translateY > 10.0f) {
			translateY -= 0.01f;
		}

		if (translateY < 0.0f) {
			if (translateY > -0.05) {
				translateY -= 0.001*translateY;
			}
			else {
				translateY += 10 * translateY*translateY;
			}
		}
		if (translateY < -5.0f) {
			translateY += 0.01f;
		}

		cameraPosition = glm::vec3(glm::vec3(0.0, 3, -5) - carPosition);
		printf("Camera : %f\n", cameraPosition[2]);
		cameraDirection = carPosition;


		for (int i = 0; i < 4; i++) {
			glm::mat4 oldMatrix = car.wheels[i]->getModel(); //Backup physically correct matrix before modifying it for drawing
			car.wheels[i]->updatePosition(3.1415 / 2, 0, 3.1415 / 2, glm::vec3(0, 0, 0)); //Correct orientation of wheels just before drawing, so it doesn't affect calculations
			glUniformMatrix4fv(uniform_model, 1, GL_FALSE, glm::value_ptr(car.wheels[i]->getModel()));
			glUniformMatrix4fv(uniform_inverseModel, 1, GL_FALSE, glm::value_ptr(glm::inverse(car.wheels[i]->getModel())));
			car.wheels[i]->draw();
			car.wheels[i]->setModel(oldMatrix);//Put it back so it is ready for calculations
		}



		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode,
	int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void char_callback(GLFWwindow* window, unsigned int key)
{
	if (key == 'p' || key == 'P')
		perspective = true;
	if (key == 'o' || key == 'O')
		perspective = false;
	if (key == 'k') {
		rotation_angle_z += 0.01f;
	}

	if (key == 'l') {
		rotation_angle_z -= 0.01f;
	}

	if (key == 'u') {
		rotation_angle_y += 0.01f;
	}

	if (key == 'j') {
		rotation_angle_y -= 0.01f;
	}

	if (key == 'h') {
		rotation_angle_x += 0.01f;
	}

	if (key == 'n') {
		rotation_angle_x -= 0.01f;
	}

	if (key == 'f') {
		translateY -= 0.01f;
	}

	if (key == 'r') {
		translateY += 0.01f;
	}

	if (key == '5') {
		cameraPosition[0] += 0.1f;
	}

	if (key == '8') {
		cameraPosition[0] -= 0.1f;
	}

	if (key == '6') {
		cameraPosition[1] += 0.1f;
	}

	if (key == '4') {
		cameraPosition[1] -= 0.1f;
	}

	if (key == '9') {
		cameraPosition[2] += 0.1f;
	}

	if (key == '7') {
		cameraPosition[2] -= 0.1f;
	}
}