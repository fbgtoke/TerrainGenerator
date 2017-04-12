#ifndef SHADERLOADER_HPP
#define SHADERLOADER_HPP

#include "utils.hpp"

class ShaderLoader {
private:
	static const std::string SHADER_DIR;

	static std::string read(const std::string& filename);
	static long getFileLength(std::ifstream& file);

public:
	static GLuint load(const std::string& name, GLenum type);
};

#endif