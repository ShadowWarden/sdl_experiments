/* camera.h
*
*  Omkar H. Ramachandran
*  omkar.ramachandran@colorado.edu
*  
*  Simple rotating triangle
*/

class Camera{
	public:
		Camera();

		void Move(int dir);
		float Getth();
		float Getph();
		void print();
		void Zoom(float dr);
		float Getr();
	private:
		float th;
		float ph;
		float r;
};
