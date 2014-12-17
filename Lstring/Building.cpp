#include "Building.h"


Building::Building(GLdouble xScaling, GLdouble yScaling, GLdouble zScaling, Matrix4d rootC) {
	Matrix4d initT;

	initT.makeTranslate(0.0, HALF_BUILDING_SIZE, 0.0);
	rootC = rootC * initT;
	root = new MatrixTransform(rootC);
	root->addChild(new Cube((rand() * 4 / RAND_MAX), (rand() * (6 - 4) / RAND_MAX + 4), xScaling, yScaling, zScaling, BUILDING_SIZE, Vector3d(1.0, 1.0, 1.0), draw::SOLID));
}

MatrixTransform* Building::getRoot() {
	return this->root;
}

Building::~Building() {
}
