#pragma once

#include "MatrixTransform.h"
#include "BuildingConstructor.h"
#include "Quad.h"
#include "SOIL.h"

class City {
	public:
	City();
	void init();
	MatrixTransform* getRoot();
	~City();
	
	protected:
	MatrixTransform* root;
	GLuint texture[6];
};

