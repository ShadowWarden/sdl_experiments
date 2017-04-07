/* triangle.h
*
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*  
*  Simple rotating triangle
*/
#include <cstdio>

class Triangle{
	public:
		Triangle(float vertex[18]);
		Triangle();
		void render();
		void print();
	private:
		float vertex[3][3];
		float color[3][3];
};
