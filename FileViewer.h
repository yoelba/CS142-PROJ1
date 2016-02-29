// FileViewer.h

#include <string>

#include "Buffer.h"

class FileViewer
{
public:
    void run();

private:
    void display();

    Buffer buffer;
    int window_height;
    std::string error_message;
};
