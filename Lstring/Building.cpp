#include "Building.h"


Building::Building(Matrix4d rootC) {
	Matrix4d initT;

	initT.makeTranslate(0.0, HALF_BUILDING_SIZE, 0.0);
	root = new MatrixTransform(rootC * initT);
	root->addChild(new Cube(BUILDING_SIZE, Vector3d(0.3, 0.3, 0.3), draw::SOLID));

}

MatrixTransform* Building::getRoot() {
	return this->root;
}

Building::~Building() {
}
