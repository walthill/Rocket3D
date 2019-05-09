using namespace std;

#include <iostream>
#include "MathUtils.h"

//Vector3 Demo
void Vector3TestOperations()
{
	Vector3 a(2, -4, 1), b(2, 4, 2);

	//Vector to vector
	cout << "Vector to vector math" << endl;
	cout << "a is " << a << " b is " << b << endl;
	cout << (a + b) << endl;
	cout << (a / b) << endl;
	cout << (a - b) << endl << endl;

	//Scalar math
	cout << "Vector - scalar math" << endl;
	cout << "b is " << b << endl;
	cout << (b + 4) << endl;
	cout << (b / 2) << endl;
	cout << (b - 4) << endl;
	cout << (b * 2) << endl << endl;

	cout << "Negation" << endl;
	cout << "a is " << a << endl;
	cout << !a << endl;
	cout << !- a << endl << endl;

	cout << "Comparison" << endl;
	cout << (a == a) << endl;
	cout << (a == b) << endl;
	cout << (a != b) << endl << endl;

	cout << "Length of vector" << endl;
	cout << "a is " << a << endl;
	cout << a.getMagnitude() << endl << endl;

	cout << "Unit vector" << endl;
	cout << "a is " << a << endl;
	cout << "The length of a is " << a.getMagnitude() << endl;
	a = a.normalize();
	cout << a << endl;
	cout << a.getMagnitude() << endl << endl; //should be one

	Vector3 v1(0.6f, -0.8f, 0.0f), v2(0, 1, 0);

	cout << "Dot Product: " << endl;
	cout << "v1 is " << v1 << " v2 is " << v2 << endl;
	float angleInRadians = Vector3::dot(v1, v2);
	float angleInDegrees = RadToDeg(angleInRadians);
	cout << angleInDegrees << endl << endl;

	cout << "Utility Vectors" << endl;
	cout << "Back: " << Vector3::back << endl;
	cout << "Forward: " << Vector3::forward<< endl;
	cout << "Left: " << Vector3::left << endl;
	cout << "Right: " << Vector3::right << endl;
	cout << "Up: " << Vector3::up << endl;
	cout << "Down: " << Vector3::down << endl;
	cout << "Zero: " << Vector3::zero << endl;
	cout << "One: " << Vector3::one << endl;
}

void Mat4TestOperations()
{
	float val[16] = {
		1, 2, 0, 0,
		3, 4, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0 };
	float val2[16] = {
		5, 6, 0, 0,
		7, 8, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0 };

	Mat4 a(val);
	Mat4 b(val2);

	cout << "Scalar Operations" << endl;
	cout << a + 10 << endl;
	cout << a - 10 << endl;
	cout << a * 2 << endl;

	cout << "Matrix Multiplication" << endl;
	cout << a * b << endl;

	Vector3 vec(1, 2, 3);
	cout << "Vector value is" << vec << endl;
	cout << "Identity transform applied to vector: " << Mat4::identity * vec << endl;
	cout << "Uniform 2x scale applied: " << endl << Mat4::scale(Mat4::identity, Vector3(2,2,2)) << endl;

}

void Mat4TestTransformations()
{
	Vector4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	Mat4 trans = Mat4::identity;

	cout << "Translate transformation" << endl;
	trans = Mat4::translate(trans, Vector3(1.0f, 1.0f, 0.0f));
	cout << trans << endl;
	vec = trans * vec;
	std::cout << vec << std::endl << endl;

	cout << "Scale and rotate transformation" << endl;
	Mat4 trans2 = Mat4(1.0f);
	trans2 = Mat4::rotate(trans2, DegToRad(90.0f), Vector3(0.0f, 0.0f, 1.0f));
	trans2 = Mat4::scale(trans2, Vector3(0.5f, 0.5f, 0.5f));
	cout << trans2 << endl;
}

// Taking notes from Learn OpenGL https://learnopengl.com/Getting-started/Transformations
int main()
{

//	Vector3TestOperations();
//	Mat4TestOperations();
  Mat4TestTransformations();
	
    return 0;
}