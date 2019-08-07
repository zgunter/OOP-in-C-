// PHYS 30762 Programming in C++
// Assignment 8
// Shapes
// Write a class hierarchy to describe the properties of 2D and 3D shapes

#include<iostream>
#include<stdlib.h>
#include<cmath>
#include<iomanip>
#include<string>
#include<vector>
using namespace std;
double pi = 3.1415;

// Abstract shape class -- base class
class Shapes {
public:
	// Define pure virtual functions
	virtual void info()=0;
	// Destructor
	virtual ~Shapes() { //cout << "Base class destructor called" << endl;
	}
};

// Derived 2D class
class Shapes_2D : public Shapes {
public:
	~Shapes_2D() { //cout << "Base 2D class destructor called" << endl; 
	}
	double get_volume() const { return 0; } // 2D shapes have volume of zero
	// Pure virtual functions
	virtual double get_area() const = 0;
	virtual void info() = 0;
};

// Derived 3D class
class Shapes_3D : public Shapes {
public:
	~Shapes_3D() { //cout << "Base 3D class destructor called" << endl;
	}
	// Pure virtual functions
	virtual double get_area() const = 0;
	virtual double get_volume() const = 0;
	virtual void info() = 0;
};

// Derived 2D classes for different shapes
class Rectangles : public Shapes_2D {
protected:
	double width, length;
public:
	Rectangles() {};
	Rectangles(double x, double y) { width = x, length = y; }
	~Rectangles() {// cout << "Rectangles destructor called" << endl; 
	}
	double get_area() const { return width*length; }
	virtual void info() {
		cout << "2D shape information:" << endl;
		cout << "Rectangle, " << "Area = " << get_area() << endl;
	}
};

class Squares : public Rectangles {
	// Square is a type of reatangles
public:
	Squares() {};
	Squares(double side) { width = side; length = side;}
	~Squares() {// cout << "Squares destructor called" << endl; 
	}
	double get_side() { return width; }
	void info() {
		cout << "2D shape information:" << endl;
		cout << "Square, " << "Area = " << get_area() << endl;
	}
};

class Ellipses : public Shapes_2D {
protected:
	double semi_major, semi_minor;
public:
	Ellipses() {};
	Ellipses(double major_axis, double minor_axis) { 
		semi_major = major_axis, semi_minor = minor_axis;}
	~Ellipses() {// cout << "Ellipses destructor called" << endl; 
	}
	double get_area() const { return pi*semi_major*semi_minor; }
	virtual void info() {
		cout << "2D shape information:" << endl;
		cout << "Ellipse, " << "Area = " << get_area() << endl;
	}
};

class Circles : public Ellipses {
	// Circle is a type of ellipse
public:
	Circles() {};
	Circles(double r) { semi_major = semi_minor = r; }
	double get_area() const { return pi*semi_major*semi_minor; }
	~Circles() {// cout << "Circles destructor called" << endl; 
	}
	void info() {
		cout << "2D shape information:" << endl;
		cout << "Circle, " << "Area = " << get_area() << endl;
	}
};

// Derived 3D classes for different shapes
class Cuboid : public Shapes_3D {
protected:
	double width, length, height;
public:
	Cuboid() {};
	Cuboid(double x, double y, double z) { width = x, length = y, height = z; }
	~Cuboid() {// cout << "Cuboid destructor called" << endl; 
	}
	double get_volume() const { return width*height*length; }
	double get_area() const { return 2 * width*height + 2 * width*length + 2 * length*height; }
	virtual void info() {
		cout << "3D structure information:" << endl;
		cout << "Cuboid, " << "Surface Area = " << get_area() << "  Volume = " << get_volume() << endl;
	}
};

class Cube : public Cuboid {
	// Cube is an inherient class of Cuboid
public:
	Cube() {};
	Cube(double side) { width = length = height = side;}
	~Cube() {// cout << "Cube destructor called" << endl; 
	}
	virtual void info() {
		cout << "3D structure information:" << endl;
		cout << "Cube, " << "Surface Area = " << get_area() << "  Volume = " << get_volume() << endl;
	}
};

class Ellipsoids : public Shapes_3D {
protected:
	double semi_axis1, semi_axis2, semi_axis3;
public:
	Ellipsoids() {};
	Ellipsoids(double a, double b, double c) { semi_axis1 = a, semi_axis2 = b, semi_axis3 = c; }
	~Ellipsoids() {// cout << "Ellipsoids destructor called" << endl; 
	}
	virtual double get_area() const { 
	return 4 * pi*pow((pow(semi_axis1*semi_axis2, 1.6) + pow(semi_axis1*semi_axis3, 1.6) + pow(semi_axis2*semi_axis3, 1.6)) / 3, 1 / 1.6); }
	double get_volume() const { return pi*(4 / 3)*semi_axis1*semi_axis2*semi_axis3; }
	virtual void info() {
		cout << "3D structure information:" << endl;
		cout << "Ellipsoids, Surface area = " << get_area() << "  Volume = " << get_volume() << endl;
	}
};

class Spheres : public Ellipsoids {
	// Spheres is an inherient class of ellipsoids
public:
	Spheres() {};
	Spheres(double r) { semi_axis1 = semi_axis2 = semi_axis3 = r; }
	~Spheres() {// cout << "Spheres destructor called" << endl; 
	}
	double get_area() { return 4*pi*pow(semi_axis1, 2); }
	virtual void info() {
		cout << "3D structure information:" << endl;
		cout << "Sphere, Surface Area = " << get_area() << "  Volume = " << get_volume() << endl;
	}
};

// Prism class 
class Prisms : public Shapes {
private:
	double height; double area; string name;
public:
	Prisms() {};
	// Constructors for all 2D shapes
	Prisms(Circles a, double h) { height = h; name = "Cylinder"; area = a.get_area(); }
	Prisms(Squares a, double h) { height = h; area = a.get_area();
		if (a.get_side() == height){name = "Cube";}
		else {name = "Rectangular Prism";}
	}
	Prisms(Ellipses a, double h) { height = h; name = "Cylinder"; area = a.get_area(); }
	Prisms(Rectangles a, double h) { height = h; name = "Rectangular Prism"; area = a.get_area();}
	~Prisms() { //cout << "Prisms destructor called" << endl; 
	}
	double get_volume() { return area*height; }
	void info() {
		cout << "3D Prism structure information:" << endl;
		cout << "Prism is a "<< name << ", Volume = " << get_volume() << endl;
	}
};

int main() {
	cout << setprecision(4) << endl;
	// Vector of base class pointers
	vector<Shapes*> shape_vector;
	shape_vector.push_back(new Circles(5));
	shape_vector.push_back(new Rectangles(3,4));
	shape_vector.push_back(new Squares(2));
	shape_vector.push_back(new Ellipses(3,4));
	shape_vector.push_back(new Cuboid(3, 4, 5));
	shape_vector.push_back(new Cube(4));
	shape_vector.push_back(new Spheres(5));
	shape_vector.push_back(new Ellipsoids(3, 4 ,5));
	shape_vector.push_back(new Prisms(Squares(4), 4));
	shape_vector.push_back(new Prisms(Circles(2), 6));
	// Display relavent info
	for (size_t i = 0; i < shape_vector.size(); i++) {
		shape_vector[i]->info();
	}
	cout << "shape vector has size of " << shape_vector.size() << endl;
	// Delete vectors
	for (auto i = shape_vector.begin(); i < shape_vector.end(); i++) {
		delete *i;
	}
	shape_vector.clear();
	cout << "shape vector now has size of " << shape_vector.size() << endl;

	return 0;
}
