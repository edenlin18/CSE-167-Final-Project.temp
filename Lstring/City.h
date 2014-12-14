#pragma once

#include "MatrixTransform.h"
#include "BuildingConstructor.h"
#include "Quad.h"

const double MEDIUM_BUILDING_MAX_HEIGHT = 5.0;
const double MEDIUM_BUILDING_MIN_HEIGHT = 3.0;

class City {
	public:
	City();
	MatrixTransform* getRoot();
	~City();
	
	protected:
	MatrixTransform* root;
};

