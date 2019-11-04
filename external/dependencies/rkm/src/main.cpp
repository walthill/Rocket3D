using namespace std;

#include <iostream>
#include "include/MathUtils.h"

//Vector3 Demo
void Vector3TestOperations()
{
	rkm::Vector3 a(2, -4, 1), b(2, 4, 2);

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

	rkm::Vector3 v1(0.6f, -0.8f, 0.0f), v2(0, 1, 0);

	cout << "Dot Product: " << endl;
	cout << "v1 is " << v1 << " v2 is " << v2 << endl;
	float angleInRadians = rkm::Vector3::dot(v1, v2);
	float angleInDegrees = rkm::radToDeg(angleInRadians);
	cout << angleInDegrees << endl << endl;

	cout << "Utility Vectors" << endl;
	cout << "Back: " << rkm::Vector3::back << endl;
	cout << "Forward: " << rkm::Vector3::forward<< endl;
	cout << "Left: " << rkm::Vector3::left << endl;
	cout << "Right: " << rkm::Vector3::right << endl;
	cout << "Up: " << rkm::Vector3::up << endl;
	cout << "Down: " << rkm::Vector3::down << endl;
	cout << "Zero: " << rkm::Vector3::zero << endl;
	cout << "One: " << rkm::Vector3::one << endl;
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

	rkm::Mat4 a(val);
	rkm::Mat4 b(val2);

	cout << "Scalar Operations" << endl;
	cout << a + 10 << endl;
	cout << a - 10 << endl;
	cout << a * 2 << endl;

	cout << "Matrix Multiplication" << endl;
	cout << a * b << endl;

	rkm::Vector3 vec(1, 2, 3);
	cout << "Vector value is" << vec << endl;
	cout << "Identity transform applied to vector: " << rkm::Mat4::identity * vec << endl;
	cout << "Uniform 2x scale applied: " << endl << rkm::Mat4::scale(rkm::Mat4::identity, rkm::Vector3(2,2,2)) << endl;

}

void Mat4TestTransformations()
{
	rkm::Vector4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	rkm::Mat4 trans = rkm::Mat4::identity;

	cout << "Translate transformation" << endl;
	trans = rkm::Mat4::translate(trans, rkm::Vector3(1.0f, 1.0f, 0.0f));
	cout << trans << endl;
	vec = trans * vec;
	std::cout << vec << std::endl << endl;

	cout << "Scale and rotate transformation" << endl;
	rkm::Mat4 trans2 = rkm::Mat4(1.0f);
	trans2 = rkm::Mat4::rotate(trans2, rkm::degToRad(90.0f), rkm::Vector3(0.0f, 0.0f, 1.0f));
	trans2 = rkm::Mat4::scale(trans2, rkm::Vector3(0.5f, 0.5f, 0.5f));
	cout << trans2 << endl;
}

// Taking notes from Learn OpenGL https://learnopengl.com/Getting-started/Transformations
int main()
{

//	Vector3TestOperations();
//	Mat4TestOperations();
//  Mat4TestTransformations();
	
    return 0;
}