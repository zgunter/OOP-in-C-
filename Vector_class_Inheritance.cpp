// PHYS 30762 Programming in C++
// Assignment 7
// Vector class

#include<iostream>
#include<stdlib.h>
#include<cmath>
#include <iomanip>
using namespace std;

// Create matrix class
class vector
{
	// Friends
	friend ostream & operator<<(ostream &os, const vector &vec);
	friend istream & operator >> (istream &is, vector &vec);

protected:
	// Create an array of doubles to store vector data
	double *vector_data;
	int dimensions;//number of components in the vector == dimensions of vector

public:
	// Default constructor
	vector() {
		vector_data = nullptr;
		dimensions = 0;
	}

	// Parameterized constructor
	vector(const int dim) {
		dimensions = dim; vector_data = new double[dim];
		//fill all elements as zero
		for (int i = 0; i < dim; i++) {
			vector_data[i] = 0;
		}
	}

	// Deep copy constructor
	vector(vector const &vec) {
		//cout << "Copy destructor" << endl;
		dimensions = vec.getdim();
		vector_data = nullptr;//clear existing data
							  //create new vector and copy data
		vector_data = new double[dimensions];
		for (int i = 0; i < dimensions; i++) {
			vector_data[i] = vec.vector_data[i];
		}
	}

	// Move constructor
	vector(vector &&vec) {
		//cout << "Move constructor" << endl;
		// Steal data
		vector_data = vec.vector_data; dimensions = vec.dimensions;
		// Delete data
		vec.vector_data = nullptr; vec.vector_data = 0;
	}

	// Destructor
	~vector() {
		dimensions = 0; delete[] vector_data;//clear memory
	}

	// Access functions
	int getdim() const { return dimensions; } // Return dimension of vector
	int index(int n) const // Return nth component from vector
	{
		if (n > 0 && n <= dimensions) return (n - 1);
		else { cout << "Error: out of range 1" << endl; exit(1); }
	}
	double & operator()(int n) { return vector_data[index(n)]; }
	double & operator[](int n) const {
		if (n<1 || n > dimensions) { cerr << "out of range 2" << endl; exit(1); }
		else { return vector_data[n - 1]; }
	}

	// Define copy and assigment functions
	// Copy operator overloading
	vector& operator= (const vector &v) {
		//cout << "Copy operator" << endl;
		if (&v == this) return *this; //cannot self assign
									  //delete existing data
		delete[] vector_data; dimensions = 0;
		//declare new rows and columns
		dimensions = v.getdim();
		if (dimensions > 0) {
			vector_data = new double[dimensions];
			for (int i = 0; i < dimensions; i++) {
				vector_data[i] = v.vector_data[i];
			}
		}
		return *this;
	}

	// Assignment operator overloading
	vector& operator=(vector&& v) {
		//cout << "Move operator" << endl;
		swap(vector_data, v.vector_data);
		swap(dimensions, v.dimensions);
		return *this;
	}

	// Dot product
	double operator *(vector& v)const {
		double product = 0;
		if (dimensions != v.dimensions) { 
			cerr << "The dimensions of the vectors are not compatable! Please make sure they have same length!" << endl;
			exit(1); }
		for (int i{ 0 }; i < dimensions; i++)
			product += v.vector_data[i] * vector_data[i];
		return product;
	}

};

//Overloading istream and ostream for vector input and output
ostream & operator<<(ostream &os, const vector &v) {
	os << "Vector have " << v.dimensions << " components " << endl;
	if (v.dimensions == 0) {
		return os;
	}
	// Print out components
	os << "( ";
	for (int i = 0; i < v.dimensions; i++) {

		os << v.vector_data[i] << " ";
		}
	os << ")" << endl;
	cout << endl;
	return os;
}

istream & operator >> (istream &is, vector &v) {
	// Ask user for dimension of vector
	cout << "Please enter the number of components for this vector" << endl;
	cin >> v.dimensions;
	v.vector_data = new double[v.dimensions];
	// Ask user for matrix elements
	cout << "Please enter all components of the vector, hitting enter after each number" << endl;
	for (int i = 0; i < v.dimensions; i++) {
		cin >> v.vector_data[i];
		cin.clear();
	}
	// Output final matrix
	cout << v << endl;

	return is;
}

// Derivec 4-vector class using vector class as its base class
class Minkowski : public vector {


public:

	//Default constructor
	Minkowski() {}

	//Parameterized constructor 1 - taking in 4 doubles
	Minkowski(const double ct, const double x, const double y, const double z) {
		dimensions = 4; vector_data = new double[dimensions]; //vector of length 4 for 4-vectors
		vector_data[0] = ct; vector_data[1] = x, vector_data[2] = y; vector_data[3] = z;
	}

	//Parameterized constructor 2 - taking in a vector and a double
	Minkowski(const double ct, vector position_vector) {
		dimensions = 4; vector_data = new double[dimensions];
		vector_data[1] = ct; 
		for (int i = 1; i <= 3; i++) {
			vector_data[i + 1] = position_vector[i];
		}
	}

	// Copy constructor
	Minkowski(Minkowski const &vec) {
		dimensions = vec.getdim();
		vector_data = nullptr;
		vector_data = new double[dimensions];
		for (int i = 0; i < dimensions; i++) {
			vector_data[i] = vec.vector_data[i];
		}
	}

	// Move constructor
	Minkowski(Minkowski &&vec) {
		vector_data = vec.vector_data; dimensions = vec.dimensions;
		vec.vector_data = nullptr; vec.vector_data = 0;
	}

	// Destructor
	~Minkowski() {
	}

	// Copy operator overloading
	Minkowski& operator= (const Minkowski &m) {
		//cout << "Copy operator" << endl;
		if (&m == this) return *this;
		delete[] vector_data; dimensions = 0;
		//declare new rows and columns
		dimensions = m.getdim();
		if (dimensions > 0) {
			vector_data = new double[dimensions];
			for (int i = 0; i < dimensions; i++) {
				vector_data[i] = m.vector_data[i];
			}
		}
		return *this;
	}

	// Assignment operator overloading
	Minkowski& operator=(Minkowski&& m) {
		//cout << "Move operator" << endl;
		swap(vector_data, m.vector_data);
		swap(dimensions, m.dimensions);
		return *this;
	}

	// Overriding dot product for Minkowski 4 vectors
	double operator *(Minkowski a)const {
		double product = 0; double position_product = 0;
		if (dimensions != a.dimensions) {
			cerr << "The dimensions of the vectors are not compatable! Please make sure they have same length!" << endl;
			exit(1);
		}
		for (int i = 1; i < dimensions; i++) {
			position_product += a.vector_data[i] * vector_data[i];
		}
		product = a.vector_data[0] * vector_data[0]-position_product;
		return product;
	}


	// Functions for Lorentz boost
	// Function to return gamma
	double Get_gamma(vector beta) {
		double beta_absolute = 0; double gamma = 0;
		beta_absolute = beta*beta;
		if (beta_absolute > 1) { cerr << "Beta values cannot exceed 1!, double check the beta vector" << endl; exit(2); }
		gamma = 1 / sqrt(1 - pow(beta_absolute, 2));
		return gamma;
	}

	// Separate functions for time component and positions
	// Function to return boosted time component
	double Boost_time(vector beta, Minkowski a) {
		double gamma = Get_gamma(beta);
		// Set temporary vector to store protected data
		vector position_data(3); 
		for (int i = 1; i <= position_data.getdim(); i++) {
			position_data[i] = a.vector_data[i];
		}
		// Calculate the boosted time
		double component = position_data*beta;
		double time_boosted = gamma*(a.vector_data[0] - component);
		return time_boosted;
	}

	// Function to return boosted Minkowski 4 vector
	Minkowski Boosted_vec(vector beta, Minkowski a) {
		// Get time component
		double gamma = Get_gamma(beta); double boosted_time = Boost_time(beta,a);
		// Set temporary vector to store protected data
		vector position_data(3); 
		for (int i = 1; i <= position_data.getdim(); i++) {
			position_data[i] = a.vector_data[i];
		}
		// Get dot product of position and beta vectors
		double dot_rb = position_data*beta;
		cout << dot_rb << endl;
		// Create temp position vector
		vector position_boosted(3);
		for (int i = 1; i <= position_boosted.getdim(); i++) {
			position_boosted[i] = vector_data[i] + ((gamma - 1)*(dot_rb / pow(gamma, 2)) - gamma*vector_data[0]);
		}
		// Return boosted Minkowski 4-vector
		Minkowski boosted_vector(boosted_time, position_boosted[1], position_boosted[2], position_boosted[3]);
		return boosted_vector;
	}
};

// Particle class
class Particle : public Minkowski
{
private:

	Minkowski position_4vector;
	double particle_mass; vector beta_3vector;

public:

	// Default constructor
	Particle() :
		position_4vector(), beta_3vector(), particle_mass(0) {}

	// Parameterized constructor
	Particle(const Minkowski position, double mass, vector beta) :
		position_4vector(position), particle_mass(mass), beta_3vector(beta) {}

	// Destructor 
	~Particle() {}

	// Function to return gamma value included in Minkowski class, no need to re-define
	// Function to return the momentum of the particle
	vector Getmom() {
		vector momentum(3);
		double gamma = Get_gamma(beta_3vector);
		for (int i = 1; i <= 3; i++) {
			momentum[i] = gamma*particle_mass*beta_3vector[i];
		}
		return momentum;
	}

	// Function to return the energt of the particle
	double GetEngery() {
		double gamma = Get_gamma(beta_3vector);
		double energy = gamma*particle_mass;
		return energy;
	}
};


//main
int main()
{	
	// For vector class
	cout << "Demonstrating functions for the class VECTORS:" << endl;
	cout << setprecision(5) << endl;
	// Default constructor
	vector a;
	cout << "Vector A: " << a << endl;

	// Parametised constructor
	vector b(3);
	b[1] = 7; b[2] = 4; b(3) = 2;
	cout << "Vector B: " << b << endl;

	// Deep copy constructor
	vector c(3);
	cout << "Vector C: " << c << endl;
	c = b;
	cout << "Vector C after copy constructor have been called: " << c << endl;

	// Modify vector b and show vector c is unchanged
	b(1) = 2; b(2) = 6; b(3) = 0;
	cout << "Modified vector B: " << b << endl;
	cout << "Vector C after B has been modified: " << c << endl;

	// Demonstrate move function
	cout << "Assign values to vector A: " << endl;
	a = move(b);
	cout << "vector A:" << a << endl;
	cout << "vector B:" << b << endl;

	//Show vector dot product
	cout << "Get the dot product of vectors A and C:\n" << a*c << endl;




	// Minkowski 4-vectors
	cout << "Demonstrating functions for the class Minkowski:" << endl;
	// Default constructor
	Minkowski m1;
	cout << "Minkowski 4-vector m1: " << m1 << endl;

	// Parametised constructor 1
	Minkowski m2(4,3,2,1);
	cout << "Minkowski 4-vector m2 with 4 doubles as argument: " << m2 << endl;

	// Parametised constructor 2
	vector d(3); d[1] = 4; d[2] = 5; d[3] = 6;
	Minkowski m3(4, 4,5,6);
	cout << "Minkowski 4-vector m3 with 1 double and vector a as argument " << m3 << endl;

	// Deep copy constructor
	Minkowski m4;
	cout << "Minkowski 4-vector m4: " << c << endl;
	m4 = m3;
	cout << "m4 after copy constructor have been called: " << m4 << endl;

	// Modify m3 and show m4 is unchanged
	m3[1] = 7, m3[2] = 4, m3[3] = 5, m3[4] = 6;
	cout << "Modified m3: " << b << endl;
	cout << "m4 after m3 has been modified: " << m4 << endl;

	// Demonstrate move function
	cout << "Assign values to m1 from m2: " << endl;
	m1 = move(m2);
	cout << "Minkowski 4-vector m1:" << m1 << endl;
	cout << "Minkowski 4-vector m2:" << m2 << endl;

	// Show overridden function
	cout << "Get the dot product of m1 and m4:\n" << m1*m4 << endl;


	// Return a Lorentz boosted vector
	vector beta(3);
	beta(1) = 0.95; beta(2) = 0; beta(3) = 0;  // Particle travelling at 0.95c in x direction
	double gamma = m1.Get_gamma(beta);
	double time_component = m1.Boost_time(beta,m1);
	Minkowski boosted = m1.Boosted_vec(beta,m1);
	cout << "Minkowski 4-vector m1 before Lorentz boost:" << m1 << endl;
	cout << "Minkowski 4-vector m1 after Lorentz boost:" << boosted << endl;



	// Particle class
	cout << "Demonstrating functions for the class PARTICLES:" << endl;

	// Paramterised constructor
	Minkowski m5(7, 8, 9, 5); double mass = 5;
	Particle Particle(m5, mass, beta);

	// Get the gamma factor
	cout << "Particle has gamma factor of " << Particle.Get_gamma(beta) << endl;
	// Get the momentum of the particle
	cout << "Particle has momentum of " << endl;
	cout << Particle.Getmom() << " in units of MeV/c" << endl;
	// Get the energy of the particle
	cout << "Particle has total energy of " << Particle.GetEngery() <<"in units of Mev"<< endl;
}
