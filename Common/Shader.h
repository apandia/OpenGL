#ifndef Shader_H
#define Shader_H

#include <string>

#include <GL/glew.h>

using namespace std;

class Shader {
public:

	GLuint loadShader(const char* vsPath, const char* fsPath);

private:
	bool readShaderFile(const char* vsPath, string& vsCode);
	GLuint compileShader(const char* shaderCode, GLenum shaderType);

private:
	GLuint mProgramId;
};

#endif //Shader_H