#include "BuildingConstructor.h"

BuildingConstructor::BuildingConstructor(GLuint* texture, Matrix4d rootC, GLdouble maxH, GLdouble minH, int layerCount, int choice) {
	this->texture = texture;
	this->maxH = maxH;
	this->minH = minH;
	this->layerCount = layerCount;
	this->choice = choice;
	// root = new MatrixTransform();
	// root->setMatrix(rootC);
	root = new MatrixTransform(rootC);
	// root->setMatrix(rootC);
	construct();
}

void BuildingConstructor::construct() {
	GLdouble currentMaxH = maxH;
	GLdouble currentMinH = minH;
	GLdouble xTranslation = ((double) rand() * 0.5) / (double) RAND_MAX;
	GLdouble zTranslation = ((double) rand() * 0.5) / (double) RAND_MAX;
	GLdouble xScaling = 2.0;
	GLdouble zScaling = 2.0;
	GLdouble rotationAngle = 90.0;
	GLdouble lotBias = 0.02;
	Matrix4d translation;
	Matrix4d scaling;
	Matrix4d rotation;
	Matrix4d rotation90;
	Building* building = NULL;
	
	GLdouble scaleMax = 0.90;
	GLdouble scaleMin = 0.5;
	double colorH = 1.0;
	double colorL = 0.90;
	double r = (double) rand() * (colorH + 1.0 - colorL) / (double) RAND_MAX + colorL;
	double g = (double) rand() * (colorH + 1.0 - colorL) / (double) RAND_MAX + colorL;
	double b = (double) rand() * (colorH + 1.0 - colorL) / (double) RAND_MAX + colorL;

	GLuint buildingChoice = rand() * (3 + 1) / RAND_MAX;
	GLuint roofChoice = rand() * (5 - 4 + 1) / RAND_MAX + 4;

	std::cerr << "buildingChoice: " << buildingChoice << "  roofChoice: " << roofChoice << std::endl;

	rotation.identity();
	rotation90.makeRotateY(rotationAngle);

	// base
	if (choice == 2) {
		scaling.makeScale(3.0, 1.0, 3.0);
		buildingChoice = rand() * (3 + 1 - 1) / RAND_MAX + 1;
		building = new Building(buildingChoice, roofChoice, r, g, b, texture, 3.0, 1.0, 3.0, scaling);
		root->addChild(building->getRoot());
	}
	else while (buildingChoice == 1) {
		buildingChoice = rand() * (3 + 1) / RAND_MAX;
	}

	translation.makeTranslate(xTranslation, 0.0, zTranslation);
	scaling.makeScale(xScaling, currentMaxH, zScaling);
	building = new Building(buildingChoice, roofChoice, r, g, b, texture, xScaling, currentMaxH, zScaling, translation * scaling);
	root->addChild(building->getRoot());
	
	//t s m
	xTranslation = 0.5 - lotBias;
	zTranslation = 0.0;
	zScaling = ((double) rand() * (currentMaxH - currentMinH)) / (double) RAND_MAX + currentMinH;

	for (int count = 0; count < layerCount - 1; ++count) {
		currentMaxH -= ((double) rand() * (scaleMax - scaleMin)) / (double) RAND_MAX + scaleMin;;
		rotation = rotation90 * rotation;
		
		zScaling = ((double) rand() * (scaleMax - scaleMin)) / (double) RAND_MAX + scaleMin;
		// std::cerr << "zScaling: " << zScaling << std::endl;
		scaling.makeScale(xScaling, currentMaxH, zScaling);

		translation.makeTranslate(xTranslation, 0.0, 0.0);

		building = new Building(buildingChoice, roofChoice, r, g, b, texture, xScaling, currentMaxH, zScaling, rotation * translation * scaling);
		root->addChild(building->getRoot());
	}
}

void BuildingConstructor::update() {

}

MatrixTransform* BuildingConstructor::getRoot() {
	return this->root;
}

BuildingConstructor::~BuildingConstructor() {
}
