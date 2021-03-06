#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"


ShaderProgram::ShaderProgram()
{
	programId = 0;
	linked = false;
}

ShaderProgram* ShaderProgram::loadFromFile(const std::string& name) {
	ShaderProgram* shaderProgram = new ShaderProgram();
  Shader vShader, fShader;

  vShader.initFromFile(VERTEX_SHADER, "shaders/" + name + ".vert");
  if(!vShader.isCompiled())
  {
    std::cout << "3D Vertex Shader Error" << std::endl;
    std::cout << "" << vShader.log() << std::endl << std::endl;
  }
  fShader.initFromFile(FRAGMENT_SHADER, "shaders/" + name + ".frag");
  if(!fShader.isCompiled())
  {
    std::cout << "3D Fragment Shader Error" << std::endl;
    std::cout << "" << fShader.log() << std::endl << std::endl;
  }
  shaderProgram->init();
  shaderProgram->addShader(vShader);
  shaderProgram->addShader(fShader);
  shaderProgram->link();
  if(!shaderProgram->isLinked())
  {
    std::cout << "3D Shader Linking Error" << std::endl;
    std::cout << "" << shaderProgram->log() << std::endl << std::endl;
  }
  shaderProgram->bindFragmentOutput("outColor");
  vShader.free();
  fShader.free();

  return shaderProgram;
}

void ShaderProgram::init()
{
	programId = glCreateProgram();
}

void ShaderProgram::addShader(const Shader &shader)
{
	glAttachShader(programId, shader.getId());
}

void ShaderProgram::bindFragmentOutput(const string &outputName)
{
	glBindAttribLocation(programId, 0, outputName.c_str());
}

GLint ShaderProgram::bindVertexAttribute(const string &attribName, GLint size, GLsizei stride, GLvoid *firstPointer)
{
	GLint attribPos;

	attribPos = glGetAttribLocation(programId, attribName.c_str());
	glVertexAttribPointer(attribPos, size, GL_FLOAT, GL_FALSE, stride, firstPointer);

	return attribPos;
}

void ShaderProgram::link()
{
	GLint status;
	char buffer[512];

	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &status);
	linked = (status == GL_TRUE);
	glGetProgramInfoLog(programId, 512, NULL, buffer);
	errorLog.assign(buffer);
}

void ShaderProgram::free()
{
	glDeleteProgram(programId);
}

void ShaderProgram::use()
{
	glUseProgram(programId);
}

bool ShaderProgram::isLinked()
{
	return linked;
}

const string &ShaderProgram::log() const
{
	return errorLog;
}

void ShaderProgram::setUniform1i(const string &uniformName, GLuint v)
{
	GLint location = glGetUniformLocation(programId, uniformName.c_str());

	if(location != -1)
		glUniform1i(location, v);	
}

void ShaderProgram::setUniform1f(const string &uniformName, float v)
{
	GLint location = glGetUniformLocation(programId, uniformName.c_str());

	if(location != -1)
		glUniform1f(location, v);
}

void ShaderProgram::setUniform2f(const string &uniformName, float v0, float v1)
{
	GLint location = glGetUniformLocation(programId, uniformName.c_str());

	if(location != -1)
		glUniform2f(location, v0, v1);
}

void ShaderProgram::setUniform2f(const string &uniformName, const glm::vec2& v)
{
	GLint location = glGetUniformLocation(programId, uniformName.c_str());

	if(location != -1)
		glUniform2f(location, v.x, v.y);
}

void ShaderProgram::setUniform3f(const string &uniformName, float v0, float v1, float v2)
{
	GLint location = glGetUniformLocation(programId, uniformName.c_str());

	if(location != -1)
		glUniform3f(location, v0, v1, v2);
}

void ShaderProgram::setUniform3f(const string &uniformName, const glm::vec3& v)
{
	GLint location = glGetUniformLocation(programId, uniformName.c_str());

	if(location != -1)
		glUniform3f(location, v.x, v.y, v.z);
}

void ShaderProgram::setUniform4f(const string &uniformName, float v0, float v1, float v2, float v3)
{
	GLint location = glGetUniformLocation(programId, uniformName.c_str());

	if(location != -1)
		glUniform4f(location, v0, v1, v2, v3);
}

void ShaderProgram::setUniformMatrix4f(const string &uniformName, glm::mat4 &mat)
{
	GLint location = glGetUniformLocation(programId, uniformName.c_str());

	if(location != -1)
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void ShaderProgram::setUniformBool(const string &uniformName, bool v) {
	GLint location = glGetUniformLocation(programId, uniformName.c_str());

	if(location != -1)
		glUniform1i(location, v);
}

