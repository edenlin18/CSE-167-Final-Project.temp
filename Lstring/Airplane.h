#ifndef _AIRPLANE_H_
#define _AIRPLANE_H_

#include "MatrixTransform.h"
#include "Object.h"
#include "Parser.h"

class Airplane {
	public:
	Airplane();
	void init();
	void draw();
	void setMatrixTransformMatrix(Matrix4d&);
	Matrix4d getMatrixTransformMatrix();
	MatrixTransform* getRoot();
	~Airplane();

	private:
	MatrixTransform* root;
};

#endif