#pragma warning(disable:4996)
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "CloughTocher.h"


#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void onKey(GLFWwindow * window, int glfwKey, int glfwAction);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Model Viewer", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, (GLFWkeyfun)onKey);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}



	// build and compile our shader program
	// ------------------------------------
	Shader ourShader("3.3.shader.vs", "3.3.shader.fs"); // you can name your shader files however you like

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	CloughTocher model;
	GLdouble* vertices = new GLdouble[model.getVertex().size()];
	for (size_t i = 0; i < model.getVertex().rows(); i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			vertices[i * 3 + j] = model.getVertex().coeff(i, j);
		}
	}
	GLint* faces = new GLint[model.getFace().size()];
	for (size_t i = 0; i < model.getFace().rows(); i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			vertices[i * 3 + j] = model.getFace().coeff(i, j);
		}
	}
	/*{
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};*/
	//std::cout << model.getFace();
	unsigned int VBO, VAO;
	//glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	//glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, model.getVertex().size() * sizeof(GLdouble), vertices, GL_DYNAMIC_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 8 * num_geometry, geometry);

	// position attribute

	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, (void*)0);
	//glEnableVertexAttribArray(0);					 0-> 3 * sizeof(GLdouble)
	// color attribute
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	// Generate a buffer for the indices
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.getFace().size() * sizeof(GLint), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLuint)*model.getFace().size(), faces);

	
	
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			model.getFace().size()/ sizeof(GLuint),    // count
			GL_INT,   // type
			(void*)0           // element array buffer offset
			);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//glBindBuffer(GL_ARRAY_BUFFER, geometry_array);
		// Index buffer
		
		// render the triangle
		ourShader.use();
		//glBindVertexArray(VAO);
		
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		

		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	//glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &elementbuffer);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwDestroyWindow(window);
	glfwTerminate();
	delete vertices;
	delete faces;
	return 0;
}

// Callback function called by GLFW on key event
void onKey(GLFWwindow * window, int glfwKey, int glfwAction)
{
	if (glfwKey == GLFW_KEY_ESCAPE && glfwAction == GLFW_PRESS) // Want to quit?
		glfwSetWindowShouldClose(window, true);
	else if (glfwKey == GLFW_KEY_O & GLFW_KEY_LEFT_CONTROL)
	{
		glfwSetWindowShouldClose(window, true);
		// Event has not been handled
		// Do something if needed.
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}