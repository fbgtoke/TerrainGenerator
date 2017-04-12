#ifndef GAME_HPP
#define GAME_HPP

#include "utils.hpp"
#include "shaderloader.hpp"
#include "camera.hpp"
#include "terrain.hpp"

class Game {
private:
	Game();
	Game(Game&);
	Game& operator=(Game& g) { return *this; };
	static Game* instance;

	GLuint program;
	GLuint vertex, fragment;
	
	GLuint transform_matrix;
	GLuint view_matrix;
	GLuint project_matrix;

	float scale;

	Camera* camera;
	Terrain* terrain;

	void setupGlut(int argc, char** argv);
	void bindGlutFunctions();
	void setupGlew();
	void setupShaders();

	void modelTransform();
	void viewTransform();
	void projectTransform();

	static void draw();
	static void event(unsigned char key, int x, int y);
	static void resize(int w, int h);

public:
	static Game* get();
	void run(int argc, char** argv);
};

#endif