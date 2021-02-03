#pragma once
#ifndef CUBE_H_
#define CUBE_H_

#include <learnopengl/shader_m.h>
#include <glm/glm.hpp>

float CUBE_VERS[];

class Cube
{
public:
	Cube();
	~Cube();
	float* vertices;
	int verticesSize;
	//一个顶点的数据长度
	int oneVertLen;
	unsigned int VAO;
	unsigned int VBO;
	glm::vec3 pos;
	float scale = 1.0f;
	struct Material* material;

	void draw();
	void useTexture(const char* texPath, bool hasAlpha, unsigned int* tex);
	void addTexture(const char* texPath, bool hasAlpha);

private:
	Shader* shader;
	bool useTex0;
	bool useTex1;
	unsigned int texture0;
	unsigned int texture1;
};
#endif // !CUBE_H_

