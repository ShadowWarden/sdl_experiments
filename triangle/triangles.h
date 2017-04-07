/* triangle.h
*
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*  
*  Simple rotating triangle
*/

class Triangle{
	public:
		Triangle(float vertex[18]);
		void render();
	private:
		float vertex[3][3];
		float color[3][3];
};
