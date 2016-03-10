// buffer.cpp

#include "Buffer.h"
#include "to_my_string.cpp"

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
	links.clear();
	link_count = 1;
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
        
	while(true){
		string t = "<a "; //"Target" defines what we're searching for.		
		string e = " "; //"End" defines the end of search.
		string f = ">"; //find the > character to end our anchor text.
			
		int start = thisline.find(t);
		if(start != string::npos){ //true if find() found '<a'
					
			int end = thisline.find(e,start+3);
			links.push_back( thisline.substr(start+3, end-start-3) ); //add filename to vector of links
			thisline.replace(start, end-start+1, "<<");//printing part of the reformatted text
						
			int finalPart = thisline.find(f, start); 
				//important to begin this search at "start" so that if there's an 
				//anchor earlier in the line we will skip it's ">>" characters.
			thisline.replace(finalPart, 1, ">>[" + to_my_string(link_count) + "]"); 
			link_count++;
		}
		else{
			break;
		}
	}
}

bool Buffer::go(int line){ // Should this be inline in the header file?
    int index = line - 1;
    // cout << links.at(index);
    if (!open(links.at(index)) ) return false;
	return true;
}

