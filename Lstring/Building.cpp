#include "Building.h"


Building::Building(Matrix4d rootC) {
	Matrix4d initT;

	initT.makeTranslate(0.0, HALF_BUILDING_SIZE, 0.0);
	rootC = rootC * initT;
	root = new MatrixTransform(rootC);
	root->addChild(new Cube(rootC, BUILDING_SIZE, Vector3d(1.0, 1.0, 1.0), draw::SOLID));

}

MatrixTransform* Building::getRoot() {
	return this->root;
}

Building::~Building() {
}
