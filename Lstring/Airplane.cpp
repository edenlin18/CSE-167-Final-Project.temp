#include "Airplane.h"

Airplane::Airplane() {
	init();
}

void Airplane::init() {
	root = new MatrixTransform(Matrix4d());
	root->addChild(Parser::parse_object("BiPlaneObject.obj"));
	Matrix4d temp;
	Matrix4d rootC;
	temp.makeScale(0.01, 0.01, 0.01);
	rootC = temp * rootC;
	temp.makeTranslate(0.0, 10.0, 0.0);
	rootC = temp * rootC;

	root->setMatrix(rootC);
}

void Airplane::draw() {

}

void Airplane::setMatrixTransformMatrix(Matrix4d& C) {
	root->setMatrix(C);
}

Matrix4d Airplane::getMatrixTransformMatrix() {
	return root->getMatrix();
}

MatrixTransform* Airplane::getRoot() {
	return root;
}

Airplane::~Airplane() {
}
