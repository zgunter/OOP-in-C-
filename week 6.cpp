// PHYS 30762 Programming in C++
// Assignment 6
// A matrix class

#include<iostream>
#include<stdlib.h>
#include<cmath>
using namespace std;

// Create matrix class
class matrix
{
	// Friends
	friend ostream & operator<<(ostream &os, const matrix &mat);
	friend istream & operator>>(istream &is, matrix &mat);

private:
	// Create an array of doubles to store matrix data
	double *m_data;
	int m_rows, m_columns;

public:
	// Default constructor
	matrix() { m_data = nullptr;//assign data as zero using null pointer 
	m_rows = m_columns = 0; }

	// Parameterized constructor
	matrix(int rows, int cols) { 
		m_rows = rows; m_columns = cols; m_data = new double[rows*cols];
		//fill all elements as zero
		for (int i = 0; i < cols*rows; i++) {
			m_data[i] = 0;}
	}

	// Deep copy constructor
	matrix(matrix const &m) {
		cout << "Copy destructor" << endl;
		m_rows = m.getrows(); m_columns = m.getcols();
		m_data = nullptr;//clear existing data
		//create new matrix and copy data
		m_data = new double[m.m_rows*m.m_columns];
		for (int i = 0; i < m_rows*m_columns; i++) {
			m_data[i] = m.m_data[i];
		}
	}

	// Move constructor
	matrix(matrix &&m) {
		//cout << "Move constructor" << endl;
		// Steal data
		m_data = m.m_data; m_rows = m.m_rows; m_columns = m.m_columns;
		// Delete data
		m.m_data = nullptr; m.m_rows = m.m_columns = 0;
	}

	// Destructor
	~matrix() { //cout << "destructor called" << endl;
	m_rows = 0; m_columns = 0; delete[] m_data;}//clear memory

	// Access functions
	int getrows() const { return m_rows; } // Return number of rows
	int getcols() const { return m_columns; } // Return number of columns
	int index(int m, int n) const // Return position in array of element (m,n)
	{	if (m>0 && m <= m_rows && n>0 && n <= m_columns) return (n - 1) + (m - 1)*m_columns;
	else {
			cout << "Error: out of range" << endl; exit(1); }
	}
	double & operator()(int m, int n) { return m_data[index(m, n)]; }

	// Define copy and assigment functions
	// Copy operator overloading
	matrix& operator= (const matrix &m) {
		//cout << "Copy operator" << endl;
		if (&m == this) return *this; //cannot self assign
		//delete existing data
		delete[] m_data; m_rows = m_columns = 0;
		//declare new rows and columns
		m_rows = m.getrows(), m_columns = m.getcols();
		if (m_rows > 0 || m_columns > 0) {
			m_data = new double[m_rows*m_columns];
			for (int i = 0; i < m_rows*m_columns; i++) {
				m_data[i] = m.m_data[i];
			}
		}
		return *this;
	}

	// Assignment operator overloading
	matrix& operator=(matrix&& m) {
		//cout << "Move operator" << endl;
		swap(m_data, m.m_data);
		swap(m_rows, m.m_rows);
		swap(m_columns, m.m_columns);
		return *this;
	}
	
	// Matrix calculation operators

	// Addition
	matrix operator+ ( const matrix &m) const {
		if (m.m_rows == this->m_rows && m.m_columns == this->m_columns) {
			// Create matrix of sum
			matrix sum = m;
			for (int i = 0; i < m.m_rows*m.m_columns; i++) {
				sum.m_data[i] += this->m_data[i];
			}
			return sum;
		}
		else {
			cerr << "The dimensions of matrices entered are not compatible for addition!";
			exit(1);
		}
	}

	// Subtraction
	matrix operator- (const matrix &m) const {
		// Create matrix of difference
		if (m.m_rows == this->m_rows && m.m_columns == this->m_columns) {
			matrix diff = m;
			for (int i = 0; i < m.m_rows*m.m_columns; i++) {
				diff.m_data[i] -= this->m_data[i];
			}
			return diff;
		}
		else {
			cerr << "The dimensions of matrices entered are not compatible for subtraction!";
			exit(1);
		}
	}

	// Multiplication
	matrix operator* (const matrix &m) const {
		// Make sure multiplication can be carried out
		if (m.m_rows != this->m_columns) {
			cerr << "The dimensions of matrices entered are not compatible for multiplication!" << endl;
			exit(1);
		}
		// Create matrix of product
		else{
			matrix product(this->m_rows, m.m_columns);
			// Run through the 1st matrix row by row
			for (int i = 1 ; i <= this->m_rows; i++) {
				// Run through the 2nd one column by column
				for (int j = 1; j <= m.m_columns; j++) {
					double temp = 0;
					// Run through the 2nd one row by row and sum up the products
					for (int k = 1; k <= m.m_rows; k++) {
						temp += this->m_data[index(i,k)] * m.m_data[index(k,j)];
					}
					product.m_data[index(i,j)] = temp;//assign to product matrix
				}
			}
			return product;
		}
	}

	// More complex functions defined outside the class
	// minor
	matrix Minor(int removed_row, int removed_col);
	// determinant
	double Determininat();
};

// Member functions defined outside class

// Function to return minors
matrix matrix::Minor(int removed_row, int removed_col) {
	// Remove one row and one column from matrix calling this function
	// Create temp data matrix of the right size
	matrix data((this->m_rows) - 1, (this->m_columns) - 1);
	int data_loc = 0; // Location of data being operated on
	for (int i = 1; i <= this->m_rows; i++) {
		for (int j = 1; j <= this->m_columns; j++) {
			if (i != (removed_row+1) && j != (removed_col+1)) {
				// Read in data from the undeleted rows and columns
				data.m_data[data_loc] = this->m_data[index(i,j)];
				data_loc++;
			}
		}
	}
	return data;
}

// Function to return the Determiniant matrix
double matrix::Determininat() {
	double Det = 0;
	if (this->m_rows != this->m_columns) {
		cerr << "To calculate the determininat a square matrix need to be used" << endl;
		exit(1);
	}
	else if (this->m_rows == 2 && this->m_columns ==2) {
		Det = m_data[0] * m_data[3] - m_data[2] * m_data[1];
		return Det;
	}
	matrix minor;
	// Run through the matrix to find all minors
	for (int i = 0; i < this->m_columns; i++) {
		minor = this->Minor(0, i);
		// Multiply the 2X2 determininats by their cofactor
		Det += pow(-1,i)*m_data[index(1,i+1)]*minor.Determininat();
	}
	return Det;
}

// Overload insertion to output stream for matrices
ostream & operator<<(ostream &os, const matrix &mat){
	os << "Matrix is of dimensions " << mat.m_rows << " X " << mat.m_columns << endl;
	// Print out elements row by row
	for (int i = 0; i < mat.m_rows; i++) {
		for (int j = 0; j < mat.m_columns; j++) {
			int index = i*mat.m_rows + j;
			os << mat.m_data[index]<<"  ";
		}
		cout << endl; // Switch to the next row
	}
	cout << endl;
	return os;
}

// Overload istream for matrix class inputs
istream & operator >> (istream &is, matrix &mat) {
	// Ask user for dimension of matrix
	cout << "Please enter the number of rows for this matrix" << endl;
	cin >> mat.m_rows;
	cout << "Please enter the number of columns for this matrix" << endl;
	cin >> mat.m_columns;
	
	mat.m_data = new double[mat.m_columns*mat.m_rows];
	// Ask user for matrix elements
	cout << "Please enter all elements of the matrix, row by row" << endl;
	for (int i = 0; i < mat.m_columns*mat.m_rows; i++) {
		cin >> mat.m_data[i];
		cin.clear();
	}
	// Output final matrix
	cout << mat << endl;

	return is;
}

// Main program
int main()
{	
	// First part of assignment: constructing and deep copying matrices
	// Demonstrate default constructor
	cout << "Demonstrating use of default constructor" << endl;
	matrix a1;
	cout << "Matrix a1:" << endl;
	cout << a1;

	// Parameterized constructor
	cout << "Demonstrating use of parameterized constructor" << endl;
	const int m(2), n(2);
	matrix a2(m, n);
	a2(1, 1) = 1; a2(1, 2) = 2; a2(2, 1) = 3; a2(2, 2) = 4;
	cout << "Matrix a2:" << endl;
	cout << a2;

	// Deep copy by assignment: define new matrix a3 then copy from a2 to a3
	cout << "Demonstrating use of parameterized constructor" << endl;
	matrix a3(m, n);
	cout << "Matrix a3:" << endl;
	cout << a3;// Show a3 is umpty
	// Assign values to a3
	a3 = a2;
	cout << "Assigning values to a3" << endl;
	cout << "Matrix a3:" << endl;
	cout << a3;

	// Modify contents of a2 and show a3 is unchanged
	cout << "Changing elements in a2" << endl;
	a2(1, 1) = 5; a2(1, 2) = 6; a2(2, 1) = 7; a2(2, 2) = 8;
	cout << "Matrix a2:" << endl;
	cout << a2;
	cout << "However a3 stays the same" << endl;
	cout << "Matrix a3:" << endl;
	cout << a3;

	// Deep copy using copy constructor 
	matrix a4(a2);
	cout << "Matrix a4:" << endl;
	cout << a4;
	// Modify contents of original matrix and show copied matrix is unchanged here
	cout << "Changing elements in a2" << endl;
	a2(1, 1) = 9; a2(1, 2) = 8; a2(2, 1) = 7; a2(2, 2) = 6;
	cout << "Matrix a2:" << endl;
	cout << a2;
	cout << "However a4 stays the same" << endl;
	cout << "Matrix a4:" << endl;
	cout << a4;

	// Move copy construction demonstration
	cout << "Demonstrating copy constructor and assigment using function move:" << endl;
	matrix a5;
	cout << "Matrix a5:" << endl;
	cout << a5;
	// Move a4 to a5
	cout << "Moving data in a4 to a5" << endl;
	a5 = move(a4);
	cout << "Matrix a5:" << endl;
	cout << a5;
	cout << "Matrix a4:" << endl;
	cout << a4;
	
	// Second part of assignment: matrix operations
	matrix a6, a7, a8;
	matrix sum, diff, product;
	cout << "Demonstrating addition, subtraction and multiplication functions" << endl;
	cout << "Please enter relevant information about 2 matrices, a6 and a7" << endl;
	cout << "For matrix a6:" << endl;
	cin >> a6;
	cout << "Now for matrix a7:" << endl;
	cin >> a7;
	// Addition, subtraction and multiplication
	sum = a6 + a7; 
	diff = a6 - a7; 
	product = a6*a7;
	cout << "The sum of a6 and a7 is" << sum;
	cout << "The difference of a6 and a7 is" << diff;
	cout << "The product of a6 and a7 is" << product;

	// Determinant
	cout << "Demonstrating the determinant and find minor function" << endl;
	cout << "Please enter relevant information about matrix a8" << endl;
	cout << "For matrix a8:" << endl;
	cin >> a8;
	double det = a8.Determininat();
	cout << "Matrix a8 has a determininat of " << det << endl;
	cout << det << endl;
	double col_removed, row_removed;
	cout << "Demonstrating the minor function, Please enter the nth column you wish to delete, starting at 1" << endl;
	cin >> col_removed;
	cout << "Now enter the nth row you wish to delete, also starting at 1" << endl;
	cin >> row_removed;
	matrix a9 = a8.Minor(row_removed-1, col_removed-1);
	cout << "The minor matrix:" << endl;
	cout << a9 << endl;

	return 0;
}