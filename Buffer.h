// Buffer.h

#include <vector>
#include <string>

class Buffer
{
public:
    void display() const;
    const std::string & get_file_name() const { return file_name; }
    void move_to_next_page();
    void move_to_previous_page();
    bool open(const std::string & file_name);
    void set_window_height(int h) { window_height = h; }
    void set_line_length(int l) {line_length = l; }
    void reformat(std::string & thisline);
    bool doneReformatting = false;
    bool go(int linum);
    
    std::vector<std::string> links;

private:
    std::vector<std::string> v_lines;
    int ix_top_line = 0;
    int vectors_vomited = 0; //Best variable names
    std::string file_name;
    int window_height;
    int line_length;
    int link_count = 1;
};

inline void Buffer::move_to_next_page()
{
    if (ix_top_line + vectors_vomited < v_lines.size())
        ix_top_line += vectors_vomited;
}

inline void Buffer::move_to_previous_page()
{
    if (ix_top_line > 0) ix_top_line -= vectors_vomited;
}

