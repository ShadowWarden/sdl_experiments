/* triangle.h
*
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*  
*  Simple rotating triangle
*/

#include "camera.h"

class Triangle{
	public:
		Triangle();

		bool init();
		void prepare(float dt);
		void render(Camera C);
		void shutdown();

		void onResize(int width, int height);
		void print();
		float GetAngle();
	private:
		float m_rotationAngle;
};

extern float speed;
