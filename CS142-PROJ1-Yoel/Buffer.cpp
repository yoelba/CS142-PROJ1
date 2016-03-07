// Buffer.cpp

#include "Buffer.h"

#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

void Buffer::display() const
{
    int ix_stop_line = ix_top_line + window_height;
    for (int i = ix_top_line; i < ix_stop_line; ++i) {
        if (i < v_lines.size())
            cout << std::setw(6) << i+1 << "  " << v_lines[i];
        cout << '\n';
    }
}

bool Buffer::open(const string & new_file_name)
{
    std::ifstream file(new_file_name);
    if (!file) return false;

    v_lines.clear();
    // Note: the vector is cleared only after we know the file
    // opened successfully.
    
    string line;
    while (getline(file, line)){
	reformat(line);
	v_lines.push_back(line);
        
    }
    file_name = new_file_name;
    ix_top_line = 0;
    return true;

}

void Buffer::reformat(string & thisline){

	doneReformatting = false;


	
	while(doneReformatting == false){
		string t = "<a"; //T for "Target". This defines the target that I'm searching for. I initialize it up here in case I want to modify it later.		
		string e = ">"; //E for "End". This defines the end of what I'm searching for.
		int start = thisline.find(t);
		
		if(start != thisline.length()){
			int end = thisline.find(t);
			thisline.replace(start+1, end-start+1, "PENIS");
			cout<<"You're stuck in a fucking loop. Thisline's length = "<<thisline.length()<<endl;	
		//	doneReformatting = true;
		}
		else{
			doneReformatting  = true;
		}
	
	}
}


