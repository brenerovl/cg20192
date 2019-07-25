#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

void loop()
{
	glClearColor(1.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwPollEvents();
}


int main(int argc, char** argv) {
	// Initialize glfw
	if(!glfwInit())
	{
		return -1;
	}
	
	// Setup OpenGL context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	GLFWwindow * window = glfwCreateWindow(800,600,"test",nullptr,nullptr);

	// if failed to initialize
	if(window == nullptr)
	{
		// terminate glfw and quit
		glfwTerminate();
		return -1;
	}

	// Setup window context
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		// terminate glfw and quit
		glfwTerminate();
		return -1;
	}

	while(!glfwWindowShouldClose(window))
	{
		loop();
	}
	glfwTerminate();
	
	return 0;
}
