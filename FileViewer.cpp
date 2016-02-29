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
    cout << "  next  previous  open  quit\n";
    cout << short_separator << endl;
}

void FileViewer::run()
{
    cout << "Window height? ";
    cin >> window_height;
    cin.get();  // '\n'
    cout << '\n';
    buffer.set_window_height(window_height);

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
        };
        cout << endl;
    } // while

    return;
}


