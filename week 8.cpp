// PHYS 30762 Programming in C++
// Assignment 8
// Shapes
// Write a class hierarchy to describe the properties of 2D and 3D shapes

#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<iomanip>
#include<string>
using namespace std;
double pi = 3.14159265;

// Abstract shape class -- base class
class Shapes {
public:
	// Define pure virtual functions
	virtual double get_area() = 0;
	virtual double get_volume() = 0;
	// Destructor
	virtual ~Shapes() { cout << "Base class destructor called" << endl; }
};

// Derived 2D class
class Shapes_2D : public Shapes {
protected:
	string name;
	double area;
	double volume;
public:
	~Shapes_2D(){ cout << "Base 2D class destructor called" << endl; }
	double get_volume() { return 0; } // 2D shapes have volume of zero
	void info() { cout << "2D shape information:" << endl;
	cout << name << ", " << "Area = " << area << " Volume = " << volume << endl;
	}
};

// Derived 3D class
class Shapes_3D : public Shapes {
protected:
	string name;
	double volume;
public:
	~Shapes_3D() { cout << "Base 3D class destructor called" << endl; }
	void info() {
		cout << "3D shape information:" << endl;
		cout << name << ", "  << " Volume = " << volume << endl;
	}
};

// Derived 2D classes for different shapes
class Circles : public Shapes_2D {
private:
	double radius;
public:
	Circles() {};
	Circles(double r) { r = radius; }
	double get_area()const { return 2 * pi*radius; }
};

class Rectangles : public Shapes_2D {
private:
	double width, length;
public:
	Rectangles() {};
	Rectangles(double x, double y) { x = width, y = length; }
	double get_area() const { return width*length; }
};

class Squares : public Shapes_2D {
private:
	double width;
public:
	Squares() {};
	Squares(double wid) { wid = width; }
	double get_area() const { return width*width; }
};

class Ellipses : public Shapes_2D {
private:
	double semi_major, semi_minor;
public:
	Ellipses() {};
	Ellipses(double major_axis, double minor_axis) { major_axis = semi_major, minor_axis = semi_minor; }
	double get_area() const { return pi*semi_major*semi_minor; }
};

// Derived 3D classes for different shapes

int main(){
	return 0;
}