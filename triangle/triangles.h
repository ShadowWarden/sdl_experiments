/* triangle.h
*
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*  
*  Simple rotating triangle
*/

class Triangle{
	public:
		Triangle();

		bool init();
		void prepare(float dt);
		void render();
		void shutdown();

		void onResize(int width, int height);
	
	private:
		float m_rotationAngle;
};
