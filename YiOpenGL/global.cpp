#include "global.h"

_Light Light;

void initGlobal() {
	Light.pos = glm::vec3(-0.5f, 1.0f, 2.0f);
	Light.ambientColor = glm::vec3(0.5f, 0.5f, 0.5f);
	Light.diffuseColor = glm::vec3(0.2f, 0.2f, 0.2f);
	Light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
}