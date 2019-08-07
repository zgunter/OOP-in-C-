// PHYS 30762 Programming in C++
// Assignment 4

// Simple demonstration of a C++ class

// Hubble types: E[0-7], S0, S[a-c], SB[a-c], Irr
// Redshift z in range [0,10]
// Total mass M_tot in range [1e7,1e12] M_sun
// Stellar mass fraction f_* in range [0,0.05]

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<string>
using namespace std;

class galaxy {

	//Private data
private:
	string Hubble_type;
	double Redshift;
	double Mass_total;
	double Stella_ratio;
	vector<string> Satellites;

	//Public data
public:

	//Default constructor - Setting all paramaters to zero
	galaxy() : Hubble_type{ "unknown" }, Redshift{ 0 }, Mass_total{ 0 }, Stella_ratio{ 0 } {}

	//Parameterized constructor
	galaxy(string type, double z, double M_tot, double Stella_r) :
		Hubble_type{ type }, Redshift{ z }, Mass_total{ M_tot }, Stella_ratio{ Stella_r } {}

	//Destructor
	~galaxy() {;}

	//Define member functions
	//function to check for valid inputs
	bool input_check();
	//Output functions to print out data
	void output_data();//define the function outside the class
	//Function to calculate the stella mass
	double Stellamass() { return Stella_ratio*Mass_total; }
	//Function to change the Hubble type
	void ChangeType(string type_new) {Hubble_type = type_new;}
	//Fuction to add satellite information to galaxies
	void Add_Sat(galaxy);
};

//Output function defined outside the class
void galaxy::output_data()
{	cout.precision(4);
	cout << "Galaxy is of type " << Hubble_type << ", with redshift (z) value of " << Redshift
		<< ", It has a total mass of " << Mass_total << " in units of solar mass, with a stella mass fraction of "
		<< Stella_ratio << "."<< endl;
}

//input checks
bool galaxy::input_check()
{
	if (Redshift < 0 || Redshift > 10) {
		cout << "Redshift value needs to be between 0-10!" << endl;
		cout<<"This galaxy of type "<<Hubble_type<< " will not be stored in the data vector"<<endl;
		return false;
	}
	else if (Mass_total<1e7 || Mass_total > 1e12) {
		cout << "Mass of the galaxy needs to be between 1e7-1e12!" << endl;
		cout << "This galaxy of type " << Hubble_type << " will not be stored in the data vector" << endl;
		return false;
	}
	else if (Stella_ratio < 0 || Stella_ratio > 0.05) {
		cout << "Ratio of stella mass needs to be between 0-0.05!" << endl;
		cout << "This galaxy of type " << Hubble_type << " will not be stored in the data vector" << endl;
		return false;
	}
	else return true;
}

//Function to add satellite info
void galaxy::Add_Sat(galaxy A) {

}

// End of class and associated member functions

//main programme

int main()
{	
	//Declare vectors and all galaxy types
	vector <galaxy> galaxy_data;
	
	string typeA{ "E[0-7]" }, typeB{ "S0" }, typeC{ "S[a-c]" }, typeD{ "SB[a-c]" }, typeE{ "Irr" };
	
	//example using the default constructor
	galaxy A; // declare object with no parameters, calling default constructor

	//example using the parameterized constructor
	galaxy B(typeA, 3, 1e12, 0.01);
	galaxy C(typeC, 1, 7e8, 0.1);
	galaxy D(typeD, 4, 8.5e11, 0.04);//The Milky Way
	galaxy E(typeE, 10, 7.8e11, 0.02);

	//create satellite galaxy for the Milky Way - Large Magelanic Cloud
	galaxy LMC(typeD, 2, 1e11, 0.005);
	D.Add_Sat(LMC);

	//change the type of galaxy B from Irr to S0
	B.ChangeType(typeB);
	galaxy f(B);

	//store data in vector
	galaxy_data.push_back(A);
	if(B.input_check()==true) galaxy_data.push_back(B);
	if(C.input_check() == true) galaxy_data.push_back(C);
	if (D.input_check() == true) galaxy_data.push_back(D);
	if (E.input_check() == true) galaxy_data.push_back(E);
	if (f.input_check() == true) galaxy_data.push_back(F);

	//print out data using iterator
	vector<galaxy>::iterator print_output;
	for (print_output = galaxy_data.begin(); print_output < galaxy_data.end(); ++print_output) {
		print_output->output_data();
		//calculate stella mass
		cout<< "Mass of the stars in the galaxy is " << print_output->Stellamass()
			<< " solar masses." << endl;
	}

}