#include <iostream>
#include <vector>
#include <random>
#include "cpp/include/MathUtils.h"
#include "cpp/include/RK_Timer.h"

//stretch goals to test for - normalize(), dot()

/*******************************
	masm function prototypes

********************************/
extern "C" void _asmSetData(float a, float b, float c, float x, float y, float z);
extern "C" void _asmMagnitude();
extern "C" void _asmCross();
extern "C" void _asmPrintMagnitude();
extern "C" void _asmPrintCross();
extern "C" void _printVector3(float x, float y, float z) 
{
	std::cout << "Vector: (" << x << ", " << y << ", " << z << ")" << std::endl;
}
extern "C" void _printMagnitude(float magnitude) 
{
	std::cout << "Magnitude: " << magnitude << std::endl;
}


/*******************************
	Vector3 Functionality Demo

********************************/
/*void Vector3TestOperations()
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
	
	cout << "Length of vector a" << a << " is:" << endl;
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
	
	cout << "Cross Product: " << endl;
	cout << "v1 is " << v1 << " v2 is " << v2 << endl;
	cout << "cross product is " << rkm::Vector3::cross(v1, v2) << endl;

	cout << "Utility Vectors" << endl;
	cout << "Back: " << rkm::Vector3::back << endl;
	cout << "Forward: " << rkm::Vector3::forward<< endl;
	cout << "Left: " << rkm::Vector3::left << endl;
	cout << "Right: " << rkm::Vector3::right << endl;
	cout << "Up: " << rkm::Vector3::up << endl;
	cout << "Down: " << rkm::Vector3::down << endl;
	cout << "Zero: " << rkm::Vector3::zero << endl;
	cout << "One: " << rkm::Vector3::one << endl;
}*/

/*******************************
	Mat4 Functionality Demo

********************************/
/*void Mat4TestOperations()
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
}*/


/*******************************
	MASM/CPP Vector3 Testing

********************************/
void testTimer()
{
	RK_Timer tmr;
	tmr.start();
	double t;

	for (size_t i = 0; i < 10000; i++)
	{
		std::cout << "~ TESTING TIMER ~" << std::endl;
	}

	std::cout << "~|| SLEEPING ||~" << std::endl;
	
	tmr.sleepUntilElapsed(3000);
	t = tmr.getTimeElapsedMs();
	std::cout << t << "ms" << std::endl;
	
	t = tmr.getTimeElapsedInSeconds();
	std::cout << t << "sec" << std::endl;
}

//Benchmarking data
std::vector<double> masmTimeList;
std::vector<double> cppTimeList;
const int NUM_TEST_RUNS = 1000000; //1 million test runs
const float MIN_FLOAT = -1000;
const float MAX_FLOAT = 1000;

//CPP Test data
rkm::Vector3 vectorA(0.6f, -0.8f, 0.0f), vectorB(2.0f, -4.0f, 1.0f);
rkm::Vector3 crossVec;
float magnitudeResult;


void Vec3CppMagnitude()
{
	magnitudeResult = vectorB.getMagnitude();
}

void Vec3CppCross()
{
	crossVec = rkm::Vector3::cross(vectorA, vectorB);
}

//Display time results for MASM and CPP function calls
void calculateAndDisplayResults(bool isMASM)
{
	double total = 0;

	if (isMASM)
	{
		for each (double value in masmTimeList)
		{
			total += value;
		}

		total /= masmTimeList.size();
		std::cout << std::endl << ">>--- MASM Results ---<< " << std::endl
			<< NUM_TEST_RUNS << " tests run" << std::endl
			<< "Average Time: " << total << "ms" << std::endl << std::endl;

		masmTimeList.clear();
	}
	else
	{
		for each (double value in cppTimeList)
		{
			total += value;
		}

		total /= cppTimeList.size();
		std::cout << std::endl << ">>--- CPP Results ---<< " << std::endl
			<< NUM_TEST_RUNS << " tests run" << std::endl
			<< "Average Time: " << total << "ms" << std::endl << std::endl;

		cppTimeList.clear();
	}
}


//randomize vector data
void setBenchmarkData()
{
	std::random_device rd;
	std::uniform_real_distribution<float> realDist(MIN_FLOAT, MAX_FLOAT);

	float a = realDist(rd);
	float b = realDist(rd);
	float c = realDist(rd);
	vectorA = rkm::Vector3(a, b, c);

	float x = realDist(rd);
	float y = realDist(rd);
	float z = realDist(rd);
	vectorB = rkm::Vector3(x, y, z);

	_asmSetData(a, b, c, x, y, z);
}


void runAsmCppBenchmark()
{
	RK_Timer timer;
	std::cout << std::endl << "------- Beginning Test - MASM 1st, CPP 2nd -------" << std::endl << std::endl;

	/***************************

		GET MAGNITUDE TEST

	*****************************/
	std::cout << std::endl << "------- Test #1 Vector3::getMagnitude() -------" << std::endl << std::endl;

	for (size_t i = 0; i < NUM_TEST_RUNS; i++)
	{
		setBenchmarkData();

		timer.start();
		_asmMagnitude();
		masmTimeList.push_back(timer.getTimeElapsedMs());

		timer.start();
		Vec3CppMagnitude();
		cppTimeList.push_back(timer.getTimeElapsedMs());
	}

	calculateAndDisplayResults(true);
	calculateAndDisplayResults(false);

	/****************************

		CROSS PRODUCT TEST

	****************************/
	std::cout << std::endl << "------- Test #2 Vector3::cross() -------" << std::endl << std::endl;
	for (size_t i = 0; i < NUM_TEST_RUNS; i++)
	{
		setBenchmarkData();

		timer.start();
		_asmCross();
		masmTimeList.push_back(timer.getTimeElapsedMs());

		timer.start();
		Vec3CppCross();
		cppTimeList.push_back(timer.getTimeElapsedMs());
	}

	calculateAndDisplayResults(true);
	calculateAndDisplayResults(false);
}

// Execute masm vector3 functions and display results, 
void testMASMImplementation()
{
	_asmMagnitude();
	_asmCross();

	std::cout << "Magnitude of " << vectorB << " -- ";
	_asmPrintMagnitude();
	std::cout << "Cross product of " << vectorA  << " x " << vectorB << " -- ";
	_asmPrintCross();
}

// Taking notes on matrix and vector math from LearnOpenGL https://learnopengl.com/Getting-started/Transformations
int main()
{
	testMASMImplementation();
	runAsmCppBenchmark();

	//testTimer();

    return 0;
}