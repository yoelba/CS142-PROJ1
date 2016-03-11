// FileViewer.cpp

#include "FileViewer.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

void FileViewer::display()
{
    const string long_separator(50, '-');
    const string short_separator(8, '-');

    if (!error_message.empty()) {
        cout << "ERROR: " + error_message << endl;
        error_message.clear();
    }

    string file_name = buffer.get_file_name();
    if (file_name.empty())
        cout << "<no file opened>\n";
    else
        cout << file_name << endl;

    cout << long_separator << endl;
    buffer.display();
    cout << long_separator << endl;
    cout << "  next  previous  open  quit  go\n";
    cout << short_separator << endl;
}

void FileViewer::run()
{
    cout << "Window height? ";
    cin >> window_height;
    cin.get();  // '\n'
    cout << '\n';
    buffer.set_window_height(window_height);
    do{
	cout << "Line Length? (must be greater than 28) ";
	cin >> line_length;   
    }while(line_length < 29);

    cin.get();
    buffer.set_line_length(line_length);
    

    bool done = false;
    while (!done) {
        display();

        cout << "choice: ";
        char command;
        cin >> command;
        cin.get(); // '\n'

        switch (command) {
            case 'n': {
                buffer.move_to_next_page();
                break;
             }

            case 'o': {
                cout << "file name: ";
                string file_name;
                getline(cin, file_name);
                if (!buffer.open(file_name))
                    error_message = "Could not open " + file_name;
                break;
            }

            case 'p': {
                buffer.move_to_previous_page();
                break;
            }

            case 'q': {
                done = true;
                break;
            }

            case 'g': {
                cout << "link number: ";
                int link_number;
                cin >> link_number;
		if (link_number > buffer.links.size() && link_number > 0) {
		    error_message = link_number + "is not a valid link number.";
		    break;
		}
		if (!buffer.go(link_number) )
		    error_message = "Could not open " + buffer.links.at(link_number-1);
		break;
            }

        };
        cout << endl;
    } // while

    return;
}
