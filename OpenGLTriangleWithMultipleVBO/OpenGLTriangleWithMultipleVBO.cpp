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
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGLTriangleWithMultipleVBO", NULL, NULL);
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

	GLfloat vertexPositionData[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	GLuint vboPosition;
	glGenBuffers(1, &vboPosition);
	glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositionData), vertexPositionData, GL_STATIC_DRAW);

	GLfloat vertexColorData[] = {
		1.0f, 1.0f, 0.0f, 0.5f,
		1.0f, 1.0f, 0.0f, 0.5f,
		1.0f, 1.0f, 0.0f, 0.5,
	};

	GLuint vboColor;
	glGenBuffers(1, &vboColor);
	glBindBuffer(GL_ARRAY_BUFFER, vboColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColorData), vertexColorData, GL_STATIC_DRAW);

	Shader shaderProgram;
	GLuint programId = shaderProgram.loadShader("OpenGLTriangleWithMultipleVBO.vs", "OpenGLTriangleWithMultipleVBO.fs");

	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

	while ((glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS) &&
		(glfwWindowShouldClose(window) == 0))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(programId);

		//Position VBO
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//Color VBO
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, vboColor);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteBuffers(1, &vboPosition);
	glDeleteBuffers(1, &vboColor);

	glDeleteVertexArrays(1, &VAO);
	glDeleteProgram(programId);

	glfwTerminate();

	return 0;
}