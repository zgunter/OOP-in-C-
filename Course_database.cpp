// Simple code to store courses using vectors and strings

#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>

using namespace std;

int main(void)
{
	const string prefix("PHYS ");
	// Gather list of courses and their codes from user,
	// storing data as a vector of strings
	bool not_finished(true);
	//create vector to store string types
	vector<string> courses;
	do
	{	//declare variables
		string degreecode; 
		cout << "Please enter a course name (or press x if you have finished entering courses): \n";
		//store input in the vector of strings
		getline(cin, degreecode);
		courses.push_back(degreecode);
		//stop loop if user inputs x
		if (degreecode == "x"){
			courses.pop_back();//delete the last element
			not_finished = false;
			break;
		}
		cout << degreecode << " have been stored. \n";
	} while (not_finished);

	// Print out full list of courses
	//create iterators
	vector<string>::iterator begin_all{ courses.begin() }, end_all{ courses.end() };
	//de-reference iterators
	vector<string>::iterator courses_unsorted;
	cout << "courses you have entered are: " << endl;
	for (courses_unsorted = begin_all; courses_unsorted < end_all; ++courses_unsorted) {
		//use string stream to combine prefix and input string
		ostringstream output;
		output << prefix << *courses_unsorted;
		string course_entered{ output.str() };
		cout << course_entered << endl;
		output.str("");//clear output content
	}

	// Extract courses belonging to a certain year
	string yearChoice;
	cout << "Please enter year: 1, 2, 3 or 4 " << endl;
	cin >> yearChoice;
	//prevent error inputs
	if (yearChoice != "1" && yearChoice != "2" && yearChoice != "3" && yearChoice != "4") {
		cin.clear();
		cout << "that's not a valid year!" << endl;
		cout << "Please enter year: 1, 2, 3 or 4 " << endl;
		cin >> yearChoice;
	}
	//New vector to store course from a specific year
	vector<string> courses_by_year;
		for (size_t i{ 0 }; i < courses.size(); ++i) {
			if (courses[i].substr(0, 1) == yearChoice) {
				//store into the year vector
				courses_by_year.push_back(courses[i]);
			}
		}
	//output all courses available in the users input year
	cout << "List of courses available in year "<<yearChoice<< " are:" << endl;
	//create iterators
	vector<string>::iterator begin_year{ courses_by_year.begin() }, end_year{ courses_by_year.end() };
	vector<string>::iterator year;
	for (year = begin_year; year < end_year; ++year) {
		cout << prefix << *year << endl;
	}
	
	//Ask the user for sort options
	string sortOption;
	cout << "Sort by course code or name: ";
	cin >> sortOption;
	//prevent error inputs
	if (sortOption != "code" && sortOption != "name") {
		cin.clear();
		cout << "Please enter either 'code' or 'name' " << endl;
		cin >> sortOption;
	}
	//declare vector and itterator
	if (sortOption == "code") {
		//declare itterator for sorted by course code
		vector<string>::iterator begin_code{ courses_by_year.begin() }, end_code{ courses_by_year.end() };
		sort(begin_code, end_code);
		vector<string>::iterator code;
		cout << "year " << yearChoice << " courses sorted by course code are: " << endl;
		//output data
		for (code = begin_code; code < end_code; ++code) {
			cout <<prefix<< *code << endl;
		}
	}
	else if (sortOption == "name"){
		//extract name of the courses and store in separate vector
		vector<string> coursename_presort;
		for (size_t j{ 0 }; j < courses_by_year.size(); ++j) {
			//store everything from after the course number till the end of the string
			string coursenames = courses_by_year[j].substr(5, string::npos);
			coursename_presort.push_back(coursenames);
		}
		//sort just the coure names by introducing iterators
		vector<string>::iterator begin_name{ coursename_presort.begin() }, end_name{ coursename_presort.end() };
		sort(begin_name, end_name);
		vector<string>::iterator name;
		for (name = begin_name; name < end_name; ++name) {
			//use string stream to access iterator
			ostringstream output_sorted;
			output_sorted <<*name;
			string course_sorted{ output_sorted.str() };
			//look through the list and find the course which contains the course name
			for (size_t k{ 0 }; k < courses_by_year.size(); ++k) {
				if (courses_by_year[k].find(course_sorted) != std::string::npos) {
					cout << prefix << courses_by_year[k] << endl;
				}
			}
			output_sorted.str("");//clear output content
		}
	}
	
	//Umpty vectors
	courses.clear();
	courses_by_year.clear();

	return 0;
}
