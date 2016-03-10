// Buffer.cpp

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

void Buffer::reformat(string & thisline){ //Alright Tom, have at it.

	while(true){
		string t = "<a "; //T for "Target". This defines the target that I'm searching for. Initially, I'm looking for the beginning of an anchor.		
		string e = " "; //E for "End". This defines the end of what I'm searching for initially.
		string f = ">"; //Let's find the > character to end our anchor text.
	
		int start = thisline.find(t);
		
		if(start != string::npos){ //This is true if the find function DID find some <a character. Otherwise, we end the loop and go to the next line if there is one.
		
			int end = thisline.find(e,start+3);
			links.push_back( thisline.substr(start+3, end) );
			thisline.replace(start, end-start+1, "<<");//Begin printing the reformatted text: we begin with a <<
			
			int finalPart = thisline.find(f, start); //It's important to begin this search at "start" so that if there's an anchor earlier in the line we will skip it's ">>" characters.
			thisline.replace(finalPart, 1, ">> [" + to_my_string(link_count) + "]"); 
			link_count++;

		}
		else{
			break;
		}
	
	}
}

void Buffer::go(int linum){
    //linum is the link they want
    //vecnum is the index of the link
    int vecnum = linum - 1;
    Buffer::open(links.at(vecnum));
}

