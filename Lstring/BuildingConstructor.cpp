#include "BuildingConstructor.h"

BuildingConstructor::BuildingConstructor(Matrix4d rootC,  GLdouble maxH, GLdouble minH, int layerCount, int choice) {
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
	Building* b = NULL;
	
	GLdouble scaleMax = 0.90;
	GLdouble scaleMin = 0.5;

	rotation.identity();
	rotation90.makeRotateY(rotationAngle);


	// base
	if (choice == 2) {
		scaling.makeScale(3.0, 1.0, 3.0);
		b = new Building(scaling);
		root->addChild(b->getRoot());
	}

	translation.makeTranslate(xTranslation, 0.0, zTranslation);
	scaling.makeScale(xScaling, currentMaxH, zScaling);
	b = new Building(translation * scaling);
	root->addChild(b->getRoot());
	
	//t s m
	xTranslation = 0.0;
	zTranslation = 0.0;
	zScaling = ((double) rand() * (scaleMax - scaleMin)) / (double) RAND_MAX + scaleMin;

	for (int count = 0; count < layerCount - 1; ++count) {
		currentMaxH -= 0.5;
		rotation = rotation90 * rotation;
		
		zScaling = ((double) rand() * (scaleMax - scaleMin)) / (double) RAND_MAX + scaleMin;
		// std::cerr << "zScaling: " << zScaling << std::endl;
		scaling.makeScale(xScaling, currentMaxH, zScaling);

		xTranslation = 0.5 - lotBias;

		translation.makeTranslate(xTranslation, 0.0, 0.0);
		b = new Building(rotation * translation * scaling);
		root->addChild(b->getRoot());

	}
}

void BuildingConstructor::update() {

}

MatrixTransform* BuildingConstructor::getRoot() {
	return this->root;
}

BuildingConstructor::~BuildingConstructor() {
}
