// Gabriel Clark

#include <iostream>
#include <vector>
#include <sstream> // used for converting input into usable data

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;

vector<int> Str_To_Vec(string input_str);
void display_slot_map(vector<int> base_loc_vec, vector<int> max_disp_vec);

int main() 
{
	// ---------------------
	// VARIABLE DECLARATIONS
	// ---------------------
	string base_loc_str; // user input for base locations
	string max_disp_str; // user input for maximum displacements from base locations
	string proc_size_str; // user input for process sizes
	
	vector<int> base_loc_vec; // vector of base locations
	vector<int> max_disp_vec; // vector of maximum displacements from base locations
	vector<int> proc_size_vec; // vector of process sizes
	// ---------------------
	
	// ------------------------------------------------
	// GET USER INPUT FOR base_loc_str, max_disp_str, AND proc_size_str
	// ------------------------------------------------
	cout << "This memory manager program allocates slots to processes using the First Fit Dynamic Relocation." << endl;
	cout << endl;
	cout << "Please enter the base locations of the slots: "; getline(cin, base_loc_str);
	//base_loc_str = "1200 1700 2550 3220 4225 6450";
	cout << endl;
	cout << "Please enter the displacements for the base locations previously entered by you: "; getline(cin, max_disp_str);
	//max_disp_str = "100 300 50 200 150 250";
	cout << endl;
	cout << "Please enter the list of process sizes: "; getline(cin, proc_size_str);
	//proc_size_str = "40 150 50 200 260 20 10 150";
	cout << endl;
	// ------------------------------------------------
	
	// ---------------------------------------
	// CONVERT INPUT STRINGS INTO DATA VECTORS
	// ---------------------------------------
	base_loc_vec = Str_To_Vec(base_loc_str);
	max_disp_vec = Str_To_Vec(max_disp_str);
	proc_size_vec = Str_To_Vec(proc_size_str);
	// ---------------------------------------
	
	// ---------------------------------
	// DISPLAY THE DATA BACK TO THE USER
	// ---------------------------------
	display_slot_map(base_loc_vec, max_disp_vec);
	cout << "Processes:" << endl;
	for(unsigned int i = 0; i < proc_size_vec.size(); ++i) // display the alphabetic names of the processes based on their order separated by tab characters
	{
		char name = 'A' + i; // i=0 will be 'A', i=1 will be 'B', i=2 will be 'C', etc
		cout << name << '\t';
	}
	cout << endl;
	for(unsigned int i = 0; i < proc_size_vec.size(); ++i) // display the contents of proc_size_vec separated by tab characters
	{
		cout << proc_size_vec[i] << '\t';
	}
	cout << endl;
	cout << endl;
	// ---------------------------------
	
	// ------------------------------------
	// ALLOCATE PROCESSES A PLACE IN MEMORY
	// ------------------------------------
	for(unsigned int i = 0; i < proc_size_vec.size(); ++i) // make an allocation run for each process in proc_size_vec
	{
		char proc_name = 'A' + i;
		cout << "Taking up Process " << proc_name << endl;
		
		// step through max_disp_vec and check to see if there is enough memory at max_disp_vec[j] to give to the process at proc_size_vec[j]
		// SHOULD terminate loop before reaching the end of the vector
		for(unsigned int j = 0; true; ++j) 
		{
			if(proc_size_vec[i] <= max_disp_vec[j]) // if there is enough memory at this index for this process...
			{
				cout << "Slot assignment successful. " << proc_name << " - Base location " << base_loc_vec[j] << "." << endl;
				
				base_loc_vec[j] += proc_size_vec[i]; // increase the base location for this slot by the size of the process you put in it
				max_disp_vec[j] -= proc_size_vec[i]; // decrease the available space in this slot by the size of the process you put in it
				
				if(max_disp_vec[j] == 0) // if the slot is empty, remove the base location and max displacement values from their respective vectors
				{
					base_loc_vec.erase(base_loc_vec.begin() + j);
					max_disp_vec.erase(max_disp_vec.begin() + j);
				}
				
				break; // get out of this loop
			}
			
			if(j == ( max_disp_vec.size() - 1) ) // if we're at the end of the vector and we couldn't allocate the process, tell the user and end the program
			{
				cout << "Slot assignment NOT successful for " << proc_name << "." << endl;
				cout << "Allocation cannot proceed further." << endl;
				cout << "Ending the program now..." << endl;
				return(1);
			}
		}
		
		display_slot_map(base_loc_vec, max_disp_vec);
	}
	
	
	return 0;
}

vector<int> Str_To_Vec(string input_str)
{
	vector<int> output_vec;
	std::stringstream ss(input_str);
	
	int num;
	while(ss >> num)
	{
		output_vec.push_back(num);
	}
	
	return output_vec;
}

void display_slot_map(vector<int> base_loc_vec, vector<int> max_disp_vec)
{
	cout << "Current slot map:" << endl;
	for(unsigned int i = 0; i < base_loc_vec.size(); ++i) // display the contents of base_loc_vec separated by tab characters
	{
		cout << base_loc_vec[i] << '\t';
	}
	cout << endl;
	for(unsigned int i = 0; i < max_disp_vec.size(); ++i) // display the contents of max_disp_vec separated by tab characters
	{
		cout << max_disp_vec[i] << '\t';
	}
	cout << endl;
	cout << endl;
}










