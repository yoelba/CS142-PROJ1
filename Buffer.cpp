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
    string shorty;
    string longus;
    int terminator; //I'll be back
    int printed_lines = 0;
    int ix_stop_line = ix_top_line + window_height;
    for (int i = ix_top_line; (i < ix_stop_line) && (printed_lines<window_height); ++i) {
        if (i < v_lines.size()){ //Abandon all hope ye who enter here:


	    if(v_lines[i].size() <= line_length){
		cout << std::setw(6) << i+1 << "  ";
		cout<<v_lines[i]<<endl;
		printed_lines++;
	    }else{
		if(v_lines[i].size() == 0){
		  cout<<"NOTICE THIS! Zero if detected!" << endl;
		}else{
		    terminator = v_lines[i].rfind(" ", line_length);
		    if(terminator == string::npos){
                        cout<<"     ERROR TIME! A line here began with a word longer than the specified line length!"<<endl<<"       We're just gonna vomit out the entire thing:"<<endl;
			terminator = v_lines[i].size();
		    }
	 	    shorty = v_lines[i].substr (0, terminator);
		    longus = v_lines[i].substr (terminator, v_lines[i].size()-terminator);
		    cout << std::setw(6) << i+1 <<" "; //Only the first line of a line has it's number printed next to it RN
		    cout << shorty << endl;
		    printed_lines++;
		    while(longus.size() > line_length && terminator != 0){
		       terminator = longus.rfind(" ", line_length);
		       if(terminator == string::npos){
			    terminator = longus.size();
			    cout<<"	ERROR TIME! A line here began with a word longer than the specified line length!"<<endl<<"	     We're just gonna vomit out the entire thing:"<<endl;
			}
		       shorty = longus.substr(0, terminator);
		       longus = longus.substr(shorty.size(), longus.size()-terminator);
		       if(shorty.size() != 0){
			cout << std::setw(6) << i+1 << " ";
			cout << shorty << endl; //HERE!
			printed_lines++;
		       }
		    }
		    cout << std::setw(6) << i+1 << " ";
		    cout << longus << endl;
		    printed_lines++;

		}

	    }

	}else{
	    cout << '\n';
	}
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

