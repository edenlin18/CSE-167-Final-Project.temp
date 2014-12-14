#pragma once

#include "MatrixTransform.h"
#include "BuildingConstructor.h"
#include "Quad.h"
#include "SOIL.h"

const double MEDIUM_BUILDING_MAX_HEIGHT = 5.0;
const double MEDIUM_BUILDING_MIN_HEIGHT = 3.0;

class City {
	public:
	City();
	void init();
	MatrixTransform* getRoot();
	~City();
	
	protected:
	MatrixTransform* root;
};

