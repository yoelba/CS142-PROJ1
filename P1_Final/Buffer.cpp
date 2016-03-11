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
	if (i < c_lines.size())
	    cout << std::setw(6) << i+1 << "  " << c_lines[i];
	cout << '\n';
    }
}


bool Buffer::open(const string & new_file_name)
{
    std::ifstream file(new_file_name);
    if (!file) return false;
    
    v_lines.clear();
    c_lines.clear(); // for when we are opening new files;  
    links.clear();
    link_count = 1;
    // Note: the vector is cleared only after we know the file
    // opened successfully.
    
    string line;
    while (getline(file, line)){
	reformat(line);
	v_lines.push_back(line);
    }
    trim(v_lines);
    file_name = new_file_name;
    ix_top_line = 0;
    return true;

}

void Buffer::reformat(string & thisline){ // changes v_lines to have pretty anchors
        
	while(true){
		string t = "<a "; //"Target" defines what we're searching for.		
		string e = " "; //"End" defines the end of search.
		string f = ">"; //find the > character to end our anchor text.

		int start = thisline.find(t);
		if(start != string::npos){ //true if find() found '<a'
					
			int end = thisline.find(e,start+3); // look for first space after "<a "
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

void Buffer::trim( vector<std::string> & v_lines ){ // converts pretty v_lines into c_lines
   
    string shorty = "";
    string longus;
    int terminator;

    for (int i = 0; i < v_lines.size() ; i++) { // for each line in v_lines, cut it up into c_lines
	longus = v_lines[i]; // start cutting from the whole line
	if (longus.size() == 0) c_lines.push_back(""); // if the line is empty, push it back before cutting
	do{	
	    if (longus.size() > line_length) 
		terminator = longus.rfind(" ", line_length); // look back from line_length to find a space
	    else
		terminator = longus.size(); // if the line is short, don't cut it
	
	    if(terminator == string::npos){ // only one word on this line, longer than limit
		terminator = longus.size(); 
	    }

	    shorty = longus.substr( 0, terminator); // cut first part of string
	    longus = longus.substr( terminator, longus.size()-terminator); //remaining part will cycle through again
	    if(shorty.size() != 0){ // add the new shorty
		c_lines.push_back( shorty ); 
	    } 
	}while(longus.size() > 1 && !longus.empty()); //cycle as long as there is string left to cut
    }
} 
 
bool Buffer::go(const int & line){ 
    int index = line - 1;
    if (!open(links.at(index)) ) return false;
    return true;
}

