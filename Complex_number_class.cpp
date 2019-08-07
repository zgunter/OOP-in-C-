// PHYS 30762 Programming in C++
// Assignment 5 - skeleton code

// Class for complex numbers

#include <iostream>
#include <cmath>
#include <math.h>
#include <string>

using namespace std;

class complex
{
	// Make function to overload operator<< a friend
	friend ostream & operator << (ostream &output, const complex &z);
	friend istream & operator >> (istream &input, complex &z);
private:
	double re, im;
public:

	// Constructors & destructor
	complex() { re = im = 0; }
	complex(double r, double i) { re = r; im = i; }
	~complex() {}
	void setr(double r) { re = r; }
	void seti(double i) { im = i; }

	// Return real component
	double getreal() const { return re; }

	// Return imaginary component
	double getimag() const { return im; }

	// Return modulus
	double getmod() { return sqrt(im*im + re*re); }

	// Return argument
	double const pi = 3.14159265;
	double getarg() {
		if (im < 0) { return 2 * pi + atan(im / re); }
		else { return atan(im / re); };
	}//in radians

	 // Return complex conjugate
	complex getcon() { return complex(re, (-1) * im); }

	// Overload + operator for addition 
	complex operator+(const complex a) const {
		complex sum(re + a.getreal(), im + a.getimag());
		return sum;
	}

	// Overload - operator for subtraction
	complex operator-(const complex a) const {
		complex sub(re - a.getreal(), im - a.getimag());
		return sub;
	}

	// Overload * operator for multiplication, z1*z2
	// Model in the form of (a+bi)*(c+di)=ac-bd+(cb+ad)i with(c+di) as the argument
	complex operator*(const complex a) const {
		complex mul_product(re*a.getreal() - im*a.getimag(), im*a.getreal() + re*a.getimag());
		return mul_product;
	}

	// Overload / operator for division, z1/z2
	// Divide by multiplying by the complex conjugate of the argument
	// Argument provided used as z2 and object calling this member function is z1
	complex operator/(const complex a) const {
		double denominator = a.getreal()*a.getreal() + a.getimag()*a.getimag();
		complex numerator(re*a.getreal() - im*a.getimag(), im*a.getreal() + re*a.getimag());
		complex div_product(numerator.getreal() / denominator, numerator.getimag() / denominator);
		return div_product;
	}
};

// Function to check for wrong input format
bool input_check(string inputstring) {
	//find any letters or symbols that are not included in the complex format
	const auto position = inputstring.find_first_not_of("1234567890i+-.", 0);
	if (position != string::npos){
		cout << "Format of input is incorrect, please try again in the format of a+bi!" << endl;
		cin.clear();
		return false;
	} 
	else {
		cout << "Your input has been accepted!" << endl;
		return true;
	}
}

// Function to overload << operator for complex numbers
ostream & operator << (ostream &output, const complex &z) {
	//Can access private parameters due to friend class
	output << z.re;
	if (z.im < 0) {
		output << z.im << "i" << endl;
		return output;
	}
	if (z.im > 0) {
		output << "+" << z.im << "i" << endl;
		return output;
	}
	else { return output; }
}

// Function to overload >> operator for complex numbers
istream & operator >> (istream &input, complex &z) {
	bool loop = 1;
	while (loop == 1) {
		cout << "Please enter a complex number in the form of a+/-bi" << endl;
		//Convert istream to string
		string user_input;
		cin >> user_input;
		bool check = input_check(user_input);
		//assign values to complex number when the input check has been passed
		if (check == 1) {
			loop = 0;
			//Parameters used in find
			string str("+"), str2("-");
			size_t found_plus = user_input.find(str), found_minus = user_input.find(str2);
			if (found_plus != string::npos) {
				//Convert from string to double with stod
				z.re = stod(user_input.substr(0, found_plus));
				z.im = stod(user_input.substr(found_plus + 1, string::npos - 1));}
			else if (found_minus != string::npos) {
				z.re = stod(user_input.substr(0, found_minus));
				z.im = stod(user_input.substr(found_minus, string::npos - 1));}
			}
		else if (check == 0) {
			//loop back to the start of the function
			loop == 1;
		}
	}
	return input;
}

int main()
{
	cout.precision(3);

	//Ask for complex inputs
	complex A, B;
	cin >> A;
	cout << "The 1st complex number A which you have entered is " << A << endl;
	cin >> B;
	cout << "The 2nd complex number B which you have entered is " << B << endl;

	// Get real and imaginary components, modulus, argument and conjugate for A
	cout << "For complex number A " << A << endl;
	cout << "Real component: " << A.getreal() << endl; cout << "Imaginary component: " << A.getimag() << "i" << endl;
	cout << "Modulus: " << A.getmod() << endl; cout << "Argument: " << A.getarg() << endl;
	cout << "Complex conjugate: " << A.getcon() << endl;

	//Do the same for B
	cout << "For complex number B " << B << endl;
	cout << "Real component: " << B.getreal() << endl; cout << "Imaginary component: " << B.getimag() << "i" << endl;
	cout << "Modulus: " << B.getmod() << endl; cout << "Argument: " << B.getarg() << endl;
	cout << "Complex conjugate: " << B.getcon() << endl;

	// Get sum, difference, product and quotient of a and b
	complex sum = A + B, diff = A - B, product = A*B, quotient = A / B;
	// Print out results, also demonstrating use of overloaded operator<<
	cout << "Results of calculations done using A and B" << endl;
	cout << "Sum: " << sum << endl;
	cout << "Difference: " << diff << endl;
	cout << "Product: " << product << endl;
	cout << "Quotient: " << quotient << endl;
	return 0;
}
