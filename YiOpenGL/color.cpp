
#include "wintools.h"
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>

#include <iostream>
#include "cube.h"

//ÑÕÉ«
int main_color()
{
	GLFWwindow* window = initWin();
	if (window == NULL)
	{
		return -1;
	}

	Shader ourShader("shaders/simplecube.vs", "shaders/simplecube.fs");
	Shader lampShader("shaders/lamp.vs", "shaders/lamp.fs");

	Cube cube;
	glm::vec3 cubePos = glm::vec3(0.0f, 0.5f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);

	unsigned int CUBE_VAO, CUBE_VBO;
	glGenVertexArrays(1, &CUBE_VAO);
	glGenBuffers(1, &CUBE_VBO);

	glBindBuffer(GL_ARRAY_BUFFER, CUBE_VBO);
	glBufferData(GL_ARRAY_BUFFER, cube.verticesSize, cube.vertices, GL_STATIC_DRAW);

	glBindVertexArray(CUBE_VAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int lampVAO;
	glGenVertexArrays(1, &lampVAO);
	glBindVertexArray(lampVAO);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// activate shader
		ourShader.use();
		ourShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
		ourShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);

		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);

		// render boxes
		glBindVertexArray(CUBE_VAO);

		glm::mat4 model;
		model = glm::translate(model, cubePos);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		ourShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		lampShader.use();
		lampShader.setMat4("projection", projection);
		lampShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lampShader.setMat4("model", model);
		glBindVertexArray(lampVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &CUBE_VAO);
	glDeleteBuffers(1, &CUBE_VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}