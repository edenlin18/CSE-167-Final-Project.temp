#include "Cube.h"

Cube::Cube(Matrix4d matrix, double s, Vector3d c, draw::mode m, Material * ma){
	this->matrix = matrix;
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
	double xScale = matrix.get(0, 0);
	double yScale = matrix.get(1, 1);
	double zScale = matrix.get(2, 2);

	for (i = 5; i >= 0; i--) {
		glBindTexture(GL_TEXTURE_2D, 0);
		glColor3d(color[0], color[1], color[2]);

		if (i == 1) {
			glBindTexture(GL_TEXTURE_2D, NULL);
			glColor3d(0.0, 0.0, 0.0);
		}

		glBegin(GL_QUADS);
		glNormal3fv(&n[i][0]);

		switch (i) {
			// right side
			case 0:
				glTexCoord2f(0, yScale * 0.1);  glVertex3fv(&v[faces[i][0]][0]);
				glTexCoord2f(zScale * 0.1, yScale * 0.1);  glVertex3fv(&v[faces[i][1]][0]);
				glTexCoord2f(zScale * 0.1, 0);  glVertex3fv(&v[faces[i][2]][0]);
				glTexCoord2f(0, 0);  glVertex3fv(&v[faces[i][3]][0]);
				break;
			// top
			case 1:
				glTexCoord2f(0, zScale * 0.1);  glVertex3fv(&v[faces[i][0]][0]);
				glTexCoord2f(xScale * 0.1, zScale * 0.1);    glVertex3fv(&v[faces[i][1]][0]);
				glTexCoord2f(xScale * 0.1, 0);  glVertex3fv(&v[faces[i][2]][0]);
				glTexCoord2f(0, 0);  glVertex3fv(&v[faces[i][3]][0]);
				break;
			// left
			case 2:
				glTexCoord2f(0, yScale * 0.1);  glVertex3fv(&v[faces[i][0]][0]);
				glTexCoord2f(zScale * 0.1, yScale * 0.1);  glVertex3fv(&v[faces[i][1]][0]);
				glTexCoord2f(zScale * 0.1, 0);  glVertex3fv(&v[faces[i][2]][0]);
				glTexCoord2f(0, 0);  glVertex3fv(&v[faces[i][3]][0]);
				break;
			// bottom
			case 3:
				glTexCoord2f(0, xScale * 0.1);  glVertex3fv(&v[faces[i][0]][0]);
				glTexCoord2f(xScale * 0.1, yScale * 0.1);  glVertex3fv(&v[faces[i][1]][0]);
				glTexCoord2f(yScale * 0.1, 0);  glVertex3fv(&v[faces[i][2]][0]);
				glTexCoord2f(0, 0);  glVertex3fv(&v[faces[i][3]][0]);
				break;
			// front
			case 4:
				glTexCoord2f(0, xScale * 0.1);  glVertex3fv(&v[faces[i][0]][0]);
				glTexCoord2f(yScale * 0.1, xScale * 0.1);  glVertex3fv(&v[faces[i][1]][0]);
				glTexCoord2f(yScale * 0.1, 0);  glVertex3fv(&v[faces[i][2]][0]);
				glTexCoord2f(0, 0);  glVertex3fv(&v[faces[i][3]][0]);
				break;
			// back
			case 5:
				glTexCoord2f(0, xScale * 0.1);  glVertex3fv(&v[faces[i][0]][0]);
				glTexCoord2f(yScale * 0.1, xScale * 0.1);  glVertex3fv(&v[faces[i][1]][0]);
				glTexCoord2f(yScale * 0.1, 0);  glVertex3fv(&v[faces[i][2]][0]);
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

