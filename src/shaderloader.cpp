#include "shaderloader.hpp"

const std::string ShaderLoader::SHADER_DIR = "shaders/";

std::string ShaderLoader::read(const std::string& filename) {
    std::string content;
    std::ifstream fileStream(filename, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filename << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLuint ShaderLoader::load(const std::string& name, GLenum type) {
	std::string file = ShaderLoader::SHADER_DIR + name;
	
	std::string src  = ShaderLoader::read(file);
	const char* src_ = src.c_str();

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &src_, NULL);
	glCompileShader(shader);

    GLint compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        std::cout << "Failed to compile " << name << std::endl;

        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

        for (GLchar c : errorLog)
            std::cout << c;
        std::cout << std::endl;
    }   

	return shader;
}