#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "CommonConfig.h"
#include "Shader.h"

using namespace std;

void windowSizeChanged(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	//Initialise GLFW
	if (!glfwInit())
	{
		cout << " Failed to initialise GLFW !!!" << endl;
		return -1;
	}

	//Configure GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create GLFW Window
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLTriangle", NULL, NULL);
	if (window == nullptr)
	{
		cout << " Failed to create GLFW window !!!" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, windowSizeChanged);

	glewExperimental = true; //Needed for core profile

	//Initialise GLEW
	if (glewInit() != GLEW_OK)
	{
		cout << "Failed to initialise GLEW !!!" << endl;
		glfwTerminate();
		return -1;
	}

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLfloat vertexBufferData[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);

	Shader shaderProgram;
	GLuint programId = shaderProgram.loadShader("VertexShader.vs", "FragmentShader.fs");

	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

	while ((glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) &&
		(glfwWindowShouldClose(window) == 0))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programId);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(programId);

	glfwTerminate();

	return 0;
}