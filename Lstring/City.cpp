#include "City.h"

City::City() {
	Matrix4d translationSetter;
	Matrix4d ScalingSetter;
	BuildingConstructor* bConstructor = NULL;
	GLdouble maxH = 0.0;
	GLdouble minH = 0.0;
	root = new MatrixTransform(Matrix4d());
	int layerCount = 0;
	int choice = 0;

	for (double z = -50.0; z < 50.0; z += 5.0) {
		for (double x = -50.0; x < 50.0; x += 5.0) {
			translationSetter.makeTranslate(x, 1.0, z);
			if (x < 0) {
				maxH = ((double) rand() * (MEDIUM_BUILDING_MAX_HEIGHT - MEDIUM_BUILDING_MIN_HEIGHT)) / (double) RAND_MAX + MEDIUM_BUILDING_MIN_HEIGHT;
				minH = ((double) rand() * (maxH - MEDIUM_BUILDING_MIN_HEIGHT)) / (double) RAND_MAX + MEDIUM_BUILDING_MIN_HEIGHT;
				layerCount = (rand() * (3 - 1)) / RAND_MAX + 1;
				choice = 0;
			}
			else {
				maxH = ((double) rand() * (TALL_BUILDING_MAX_HEIGHT - TALL_BUILDING_MIN_HEIGHT)) / (double) RAND_MAX + TALL_BUILDING_MIN_HEIGHT;
				minH = ((double) rand() * (maxH - TALL_BUILDING_MIN_HEIGHT)) / (double) RAND_MAX + TALL_BUILDING_MIN_HEIGHT;
				layerCount = (rand() * (5 - 3)) / RAND_MAX + 3;
				choice = 2;
			}

			bConstructor = new BuildingConstructor(translationSetter, maxH, minH, layerCount, choice);
			root->addChild(bConstructor->getRoot());
		}
	}

	ScalingSetter.makeScale(50.0, 0.0, 50.0);
	MatrixTransform* groundTransform = new MatrixTransform(ScalingSetter);
	root->addChild(groundTransform);
	groundTransform->addChild(new Quad());
	init();
}

void City::init() {

	// Create ID for texture
	glGenTextures(1, 0);

	int width, height;
	char* filenames = "pixelcity_windows7.jpg";
	unsigned char* image;

	glBindTexture(GL_TEXTURE_2D, 0);

	image = SOIL_load_image(filenames, &width, &height, 0, SOIL_LOAD_RGB);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
	GL_UNSIGNED_BYTE, image);

	// Make sure no bytes are padded:
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Select GL_MODULATE to mix texture with polygon color for shading:
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Use bilinear interpolation:
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
}

MatrixTransform* City::getRoot() {
	return this->root;
}

City::~City() {
}
