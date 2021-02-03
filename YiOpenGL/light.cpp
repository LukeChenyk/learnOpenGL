
#include "wintools.h"
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/shader_m.h>

#include <iostream>
#include "cube.h"

//颜色
int main_light()
{
	GLFWwindow* window = initWin();
	if (window == NULL)
	{
		return -1;
	}

	Shader ourShader("shaders/simplecube.vs", "shaders/simplecube.fs");
	Shader lampShader("shaders/lamp.vs", "shaders/lamp.fs");

	Cube cube;
	cube.pos = glm::vec3(0.0f, -0.4f, 5.0f);
	cube.material->color = glm::vec3(0.7f, 0.5f, 0.0f);

	Cube blueCube;
	blueCube.pos = glm::vec3(-1.3f, -0.4f, 5.0f);
	blueCube.material->color = glm::vec3(0.1f, 0.2f, 1.0f);
	blueCube.material->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	blueCube.material->shininess = 86.0f;

	Cube texCube;
	texCube.pos = glm::vec3(0.0f, -0.4f, 0.0f);
	texCube.material->color = glm::vec3(1.0f, 0.2f, 1.0f);
	texCube.addTexture("res/textures/container2.png", true);

	Cube texSpecularCube;
	texSpecularCube.pos = glm::vec3(1.3f, -0.4f, 0.0f);
	texSpecularCube.material->color = glm::vec3(1.0f, 0.2f, 1.0f);
	texSpecularCube.addTexture("res/textures/container2.png", true);
	texSpecularCube.addTexture("res/textures/container2_specular.png", true);

	Cube lampCube;
	lampCube.pos = Light.pos;
	lampCube.scale = 0.2f;

	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);

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

		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);

		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // 降低影响
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响

		lampCube.draw();
		cube.draw();
		blueCube.draw();
		texCube.draw();
		texSpecularCube.draw();

		//lampShader.use();
		//lampShader.setMat4("projection", projection);
		//lampShader.setMat4("view", view);
		//model = glm::mat4(1.0f);
		//model = glm::translate(model, Light.pos);
		//model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		//lampShader.setMat4("model", model);
		//glBindVertexArray(lampVAO);
		//glDrawArrays(GL_TRIANGLES, 0, 36);//36:顶点的数量

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	/*glDeleteVertexArrays(1, &CUBE_VAO);
	glDeleteBuffers(1, &CUBE_VBO);*/

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}