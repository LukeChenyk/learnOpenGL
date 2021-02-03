#include "global.h"
#include "cube.h"

int main_shaders_class();
int main_textures();
int main_transformations();
int main_coordinate_systems_depth();
int main_camera_circle();
int main_camera_class();
int main_light();
int main_model_loading();
int main_depth_testing();
int main_lighting_texture();

int main() {
	//initGlobal();
	main_lighting_texture();
	return 0;
}

void createCube(const Cube& cu) 
{
	int verticesSize = cu.verticesSize;
}

const Cube& createCube() {
	Cube cube;
	return cube;
}