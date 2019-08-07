// PHYS 30762 Programming in C++
// Assignment 2 

// Program to compute mean, standard deviation and standard
// error of the mean electronic charge. Data is read from file

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<sstream>

using namespace std;

// Functions to compute mean given N data points
double Mean(const int N, double *array) {
	double sum = 0; double mean; int i = 0;
	while (i<N) {
		sum += array[i];
		i++;
	}
	mean = sum / N;
	return mean;
}
//function to compute standard deviation
double SD(const int N, double *array, double mean) {
	double diff = 0; double sd;
	for (int i = 0; i < N; i++) {
		diff = diff + pow((array[i] - mean), 2);
	}
	sd = pow((diff / (N - 1)), 0.5);
	return sd;
}
//function to check if the line read out from file can be casted as a double
bool convert_double(string line) {
	stringstream s(line);
	double number;
	s >> number;
	if (s.fail()) {
		s.clear();
		return false;//not a double
	}
	else {
		s.clear();
		return true;// is a double
	}
}

// Main function
int main()
{

	// Ask user to enter filename	
	string filename;
	cout << "Please enter the name of the file you wish to open, including the file extension .dat \n";
	cin >> filename;
	//define a file for writing and reading
	//find files located in the temp folder in C drive
	fstream inputfile("C:\\Temp\\" + filename);
	
	// Open file and check if successful
	if (!inputfile.good()) {
		//print out error message and exit programme
		cerr << "This file does not exist in the given directory, please double check the file name and its extension" << endl;
	}
	//count the number of doubles in the file
	if (inputfile.is_open()) {
		//define variables used in loop
		string line; int i = 0;
		while (getline(inputfile, line)) {
			if (convert_double(line)) {//if the line can be converted as a double, count as a line
				i++;
			}
			else {//display error message when line cannot be converted
				  //i+1 as integer i starts from zero but conventionally start counting at 1
				cerr << "line " << i + 1 << " contains non double type variables, which have been ignored in calculations \n";
			}
		}
		cout << "Number of doubles in the file is " << i << '\n';

		//return to the top of the file so data can be stored
		inputfile.clear();
		//Sets the position of the next character to be extracted at the beginning of the stream
		inputfile.seekg(0, ios_base::beg);
	
		// Allocate memory for data 
		int N = i;
		double *data = new double[N];
		// Read data from file, ignoring any additional bad data
		int j = 0;
		while (getline(inputfile, line)) {
			//need if loop to exclude the error line
			if (convert_double(line)) {
				stringstream ss(line);
				double charge;
				ss >> charge;
				data[j] = charge;
				j++;
			}
		}
		
		// Compute mean, standard deviation and standard error of mean
		double mean = Mean(N, data);
		double sd = SD(N, data, mean);
		double mean_error = sd / sqrt(N);
		//output calculations
		cout << "the average charge on an electron is found to be " << setprecision(6) << mean << "+/- " << setprecision(4) << mean_error << "e-19 Coulombs" << endl;
		cout << "the standard deviation of the data set is found to be " << setprecision(4) << sd << "e-19 Coulombs" << endl;

		// Close file
		inputfile.close();
		// Free memory
		delete[] data;
	}
	return 0;
}
