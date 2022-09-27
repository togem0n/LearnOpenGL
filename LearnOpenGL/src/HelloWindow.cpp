#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// setttings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\n";

const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
	"}\n\0";

int main()
{
	// glfw initialize and configure
	// -----------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation 
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Fail to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: laod all function pointers for OpenGL
	// -------------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fail to Initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile shader program
	// --------------------------------
	// vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check if vertexShader compile successfully
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPLICATION_FAILED\n" << infoLog << std::endl;
	}

	// orange fragment shader
	unsigned int fragmentOrangeShader;
	fragmentOrangeShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentOrangeShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentOrangeShader);

	// yellow fragment shader	
	unsigned int fragmentYellowShader;
	fragmentYellowShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentYellowShader, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentYellowShader);

	// check if fragmentShader compile successfully
	glGetShaderiv(fragmentOrangeShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPLICATION_FAILED\n" << infoLog << std::endl;
	}

	// organge fragment shader program
	unsigned int orangeShaderProgram;
	orangeShaderProgram = glCreateProgram();

	glAttachShader(orangeShaderProgram, vertexShader);
	glAttachShader(orangeShaderProgram, fragmentOrangeShader);
	glLinkProgram(orangeShaderProgram);

	// yellow fragment shader program
	unsigned int yellowShaderProgram;
	yellowShaderProgram = glCreateProgram();

	glAttachShader(yellowShaderProgram, vertexShader);
	glAttachShader(yellowShaderProgram, fragmentYellowShader);
	glLinkProgram(yellowShaderProgram);
	// check linkinng errors
	glGetProgramiv(orangeShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(orangeShaderProgram, 512, NULL, infoLog);
	}
	
	// set up vertex data and buffers and configure vertex attributes
	// --------------------------------------------------------------
	float firstTriangle[] = {
		  0.3f, 0.3f, 0.0f,
		 -0.3f, 0.3f, 0.0f,
		  0.0f, 0.9f, 0.0f,
	};

	float secondTriangle[] = {
		  0.3f, -0.3f, 0.0f,
		  -0.3f, -0.3f, 0.0f,
		  0.0f, -0.9f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};


	// 1. generate vertex array and buffer (VAO and VBO)
	// 2. bind vertex array
	// 3. bind buffer and pass data in
	// 4. map pointer vertex array and buffer
	// 5. enable vertex array

	unsigned int VBOs[2], VAOs[2], EBO;
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs); 

	// bind first triangle vao and vbo
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW); 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// bind second triangle vao and vbo
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// rendering commands here
		// -----------------------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw first triangle ^^
		glUseProgram(orangeShaderProgram);

		glBindVertexArray(VAOs[0]);
	    glDrawArrays(GL_TRIANGLES, 0, 3);

		// draw second triangle ^^
		glUseProgram(yellowShaderProgram);

		glBindVertexArray(VAOs[1]);
	    glDrawArrays(GL_TRIANGLES, 0, 3);

		// check and call events and swap the buffers
		// ------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(orangeShaderProgram);

	glfwTerminate();
	return 0;
}

// glfw: whenever the window size chnaged(by OS or user resize) this callback function executes
// --------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and height
	// will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// process all input: query GLFW whether relevant kets are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE == GLFW_PRESS))
	{
		glfwSetWindowShouldClose(window, true);
	}
}
