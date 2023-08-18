#include "Shader.h"

#include <iostream>
#include <fstream>
#include <vector>

GLuint Shader::loadShader(const char* vsPath, const char* fsPath)
{
	string vsCode, fsCode;

	bool result = readShaderFile(vsPath, vsCode);
	if (!result)
		return -1;
	
	cout << " Compiling Shader: " << vsPath << endl;
	GLuint vsId = compileShader(vsCode.c_str(), GL_VERTEX_SHADER);

	result = readShaderFile(fsPath, fsCode);
	if (!result)
		return -1;

	cout << " Compiling Shader: " << fsPath << endl;
	GLuint fsId = compileShader(fsCode.c_str(), GL_FRAGMENT_SHADER);

	//Link the program
	cout << "Linking Shader Program" << endl;
	mProgramId = glCreateProgram();
	glAttachShader(mProgramId, vsId);
	glAttachShader(mProgramId, fsId);
	glLinkProgram(mProgramId);

	//check for error
	GLint retValue = GL_FALSE;
	int infoLog;
	glGetProgramiv(mProgramId, GL_LINK_STATUS, &retValue);
	glGetProgramiv(mProgramId, GL_INFO_LOG_LENGTH, &infoLog);
	if (infoLog > 0)
	{
		vector<char> errorMessage(infoLog + 1);
		glGetProgramInfoLog(mProgramId, infoLog, NULL, &errorMessage[0]);
		cout << "Shader Program Error : " << &errorMessage << endl;
	}

	glDetachShader(mProgramId, vsId);
	glDetachShader(mProgramId, fsId);

	glDeleteShader(vsId);
	glDeleteShader(fsId);

	return mProgramId;
}

bool Shader::readShaderFile(const char* vsPath, string& vsCode)
{
	bool success = false;

	ifstream readStream(vsPath);

	if (readStream.is_open())
	{
		string line;
		while (getline(readStream, line))
		{
			vsCode.append(line);
			vsCode.append("\n");
		}

		readStream.close();
		success = true;
	}

	return success;
}

GLuint Shader::compileShader(const char* shaderCode, GLenum shaderType)
{
	GLuint shaderId = glCreateShader(shaderType);

	//Attach shader source code to shader object and compile the shader
	glShaderSource(shaderId, 1, &shaderCode, NULL);
	glCompileShader(shaderId);

	//check the shader for error
	GLint result = GL_FALSE;
	int infoLog;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLog);
	if (infoLog > 0)
	{
		vector<char> errorMessage(infoLog + 1);
		glGetShaderInfoLog(shaderId, infoLog, NULL, &errorMessage[0]);
		cout << "Error compiling shader type: " << shaderType << " Error Log: " << &errorMessage << endl;
		return shaderId;
	}

	return shaderId;
}
