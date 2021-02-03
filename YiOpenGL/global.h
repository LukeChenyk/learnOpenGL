#ifndef _GLOBAL_H_
#define _GLOBAL_H_
#include <glm/glm.hpp>

struct _Light
{
	glm::vec3 pos;
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specular;
};

struct Material
{
	glm::vec3 color;
	glm::vec3 diffuse;
	//glm::vec3 specular;
	float shininess;
};

extern _Light Light;

void initGlobal();

#endif // !_GLOBAL_H_

