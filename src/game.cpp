#include "game.hpp"

Game* Game::instance = NULL;

Game::Game() {}

Game* Game::get() {
	if (Game::instance == NULL)
		Game::instance = new Game();

	return Game::instance;
}

void Game::run(int argc, char** argv) {
	setupGlut(argc, argv);
	setupGlew();
	setupShaders();

	scale = 0.07f;
	camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT);

	uint32_t seed = (uint32_t) atoi(argv[1]);
	terrain = new Terrain(seed);

	glutMainLoop();
}

void Game::setupGlut(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow(WINDOW_TITLE);

	glutDisplayFunc(draw);
	glutIdleFunc(draw);
	glutReshapeFunc(resize);
	glutKeyboardFunc(event);
}

void Game::setupGlew() {
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		
		return;
	}
}

void Game::setupShaders() {
	vertex   = ShaderLoader::load("vertex.vert",   GL_VERTEX_SHADER);
	fragment = ShaderLoader::load("fragment.frag", GL_FRAGMENT_SHADER);

	program = glCreateProgram();

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);
	glUseProgram(program);

	transform_matrix = glGetUniformLocation(program, "TG");
	view_matrix      = glGetUniformLocation(program, "VM");
	project_matrix   = glGetUniformLocation(program, "PM");

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Game::modelTransform() {
	glm::mat4 TG(1.f);
	
	TG = glm::scale(TG, glm::vec3(scale));
	
	glUniformMatrix4fv(transform_matrix, 1, GL_FALSE, &TG[0][0]);
}

void Game::viewTransform() {
	glm::mat4 VM = camera->getViewMatrix();
	glUniformMatrix4fv(view_matrix, 1, GL_FALSE, &VM[0][0]);
}

void Game::projectTransform() {
	glm::mat4 PM = camera->getProjectMatrix();
	glUniformMatrix4fv(project_matrix, 1, GL_FALSE, &PM[0][0]);
}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT);

	Game::get()->modelTransform();
	Game::get()->viewTransform();
	Game::get()->projectTransform();

	Game::get()->terrain->draw();

    glBindVertexArray(0);

    glutSwapBuffers();
}

void Game::event(unsigned char key, int x, int y) {
	Game::get()->camera->event(key, x, y);
	Game::get()->terrain->event(key, x, y);
}

void Game::resize(int w, int h) {
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	Game::get()->camera->resize(w, h);
}