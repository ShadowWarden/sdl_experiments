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
		void ChangeSpeed(float);
		float GetAngle();
	private:
		float m_rotationAngle;
		float speed;
		bool flag;
};

extern float speed;
