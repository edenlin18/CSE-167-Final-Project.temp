#include "Cube.h"

Cube::Cube(const int& buildingChoice, const int& roofChoice, const GLdouble& xScaling, const GLdouble& yScaling, const GLdouble& zScaling, double s, Vector3d c, draw::mode m, Material * ma) {
	this->buildingChoice = buildingChoice;
	this->roofChoice = roofChoice;
	//std::cerr << "bChoice: " << buildingChoice << "rChoice: " << roofChoice << std::endl;
	this->xScaling = xScaling;
	this->yScaling = yScaling;
	this->zScaling = zScaling;
	size = s;
	color = c;
	mode = m;
	material = ma;
	bs.radius = size * cos(45 / 180 * M_PI);
	bs.center = Vector3d(0, 0, 0);
}

void Cube::render(){
	if (material != NULL){
		material->apply();
	}
	else
		glColor3d(color[0], color[1], color[2]);
	switch (mode){
	case draw::SOLID:
		drawBox(size);
		break;
	case draw::WIRE:
		glutWireCube(size);
		break; 
	}
}


void Cube::drawBox(GLfloat size) {
	static GLfloat n[6][3] =
	{
		{ -1.0, 0.0, 0.0 },
		{ 0.0, 1.0, 0.0 },
		{ 1.0, 0.0, 0.0 },
		{ 0.0, -1.0, 0.0 },
		{ 0.0, 0.0, 1.0 },
		{ 0.0, 0.0, -1.0 }
	};
	static GLint faces[6][4] =
	{
		{ 0, 1, 2, 3 },
		{ 3, 2, 6, 7 },
		{ 7, 6, 5, 4 },
		{ 4, 5, 1, 0 },
		{ 5, 6, 2, 1 },
		{ 7, 4, 0, 3 }
	};
	GLfloat v[8][3];
	GLint i;

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

	// Enable Culling
	//glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_TEXTURE_2D);

	//Matrix4d temp;
	//glGetDoublev(GL_MODELVIEW_MATRIX, temp.getPointer());

	for (i = 5; i >= 0; i--) {

		glColor3d(color[0], color[1], color[2]);

		if (i != 1 && i != 3) {
			glBindTexture(GL_TEXTURE_2D, 3);
		}
		else {
			glBindTexture(GL_TEXTURE_2D, 4);
		}

		glBegin(GL_QUADS);
		glNormal3fv(&n[i][0]);

		switch (i) {
			// right side
			case 0:
				glTexCoord2f(0, yScaling * SCALING_PROPORTION);  glVertex3fv(&v[faces[i][0]][0]);
				glTexCoord2f(zScaling * SCALING_PROPORTION, yScaling * SCALING_PROPORTION);  glVertex3fv(&v[faces[i][1]][0]);
				glTexCoord2f(zScaling * SCALING_PROPORTION, 0);  glVertex3fv(&v[faces[i][2]][0]);
				glTexCoord2f(0, 0);  glVertex3fv(&v[faces[i][3]][0]);
				break;
			// top
			case 1:
				glTexCoord2f(0, zScaling * SCALING_PROPORTION);  glVertex3fv(&v[faces[i][0]][0]);
				glTexCoord2f(xScaling * SCALING_PROPORTION, zScaling * SCALING_PROPORTION);    glVertex3fv(&v[faces[i][1]][0]);
				glTexCoord2f(xScaling * SCALING_PROPORTION, 0);  glVertex3fv(&v[faces[i][2]][0]);
				glTexCoord2f(0, 0);  glVertex3fv(&v[faces[i][3]][0]);
				break;
			// left
			case 2:
				glTexCoord2f(0, yScaling * SCALING_PROPORTION);  glVertex3fv(&v[faces[i][0]][0]);
				glTexCoord2f(zScaling * SCALING_PROPORTION, yScaling * SCALING_PROPORTION);  glVertex3fv(&v[faces[i][1]][0]);
				glTexCoord2f(zScaling * SCALING_PROPORTION, 0);  glVertex3fv(&v[faces[i][2]][0]);
				glTexCoord2f(0, 0);  glVertex3fv(&v[faces[i][3]][0]);
				break;
			// bottom
			case 3:
				glTexCoord2f(0, xScaling * SCALING_PROPORTION);  glVertex3fv(&v[faces[i][0]][0]);
				glTexCoord2f(xScaling * SCALING_PROPORTION, yScaling * SCALING_PROPORTION);  glVertex3fv(&v[faces[i][1]][0]);
				glTexCoord2f(yScaling * SCALING_PROPORTION, 0);  glVertex3fv(&v[faces[i][2]][0]);
				glTexCoord2f(0, 0);  glVertex3fv(&v[faces[i][3]][0]);
				break;
			// front
			case 4:
				glTexCoord2f(0, xScaling * SCALING_PROPORTION);  glVertex3fv(&v[faces[i][0]][0]);
				glTexCoord2f(yScaling * SCALING_PROPORTION, xScaling * SCALING_PROPORTION);  glVertex3fv(&v[faces[i][1]][0]);
				glTexCoord2f(yScaling * SCALING_PROPORTION, 0);  glVertex3fv(&v[faces[i][2]][0]);
				glTexCoord2f(0, 0);  glVertex3fv(&v[faces[i][3]][0]);
				break;
			// back
			case 5:
				glTexCoord2f(0, xScaling * SCALING_PROPORTION);  glVertex3fv(&v[faces[i][0]][0]);
				glTexCoord2f(yScaling * SCALING_PROPORTION, xScaling * SCALING_PROPORTION);  glVertex3fv(&v[faces[i][1]][0]);
				glTexCoord2f(yScaling * SCALING_PROPORTION, 0);  glVertex3fv(&v[faces[i][2]][0]);
				glTexCoord2f(0, 0);  glVertex3fv(&v[faces[i][3]][0]);
				break;
			default:
				break;
		}
		/*glTexCoord2f(0, 1.f);  glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2f(0.5f, 1);  glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(0.5f, 0);  glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(0, 0);  glVertex3fv(&v[faces[i][3]][0]);
		*/
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_CULL_FACE);
}


Bs Cube::update(){
	
	return bs;
}

