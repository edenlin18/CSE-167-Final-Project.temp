#pragma once

#include <time.h>
#include "MatrixTransform.h"
#include "Building.h"

class BuildingConstructor {
	public:
	BuildingConstructor(Matrix4d, GLdouble, GLdouble, int, int);
	void construct();
	void update();
	MatrixTransform* getRoot();
	~BuildingConstructor();

	protected:
	MatrixTransform* root;
	GLdouble maxH;
	GLdouble minH;
	int layerCount;
	int choice;
	
};

