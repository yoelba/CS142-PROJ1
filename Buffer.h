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
    void reformat(std::string & thisline);
    bool doneReformatting = false;


private:
    std::vector<std::string> v_lines;
    int ix_top_line = 0;
    std::string file_name;
    int window_height;
};

inline void Buffer::move_to_next_page()
{
    if (ix_top_line + window_height < v_lines.size())
        ix_top_line += window_height;
}

inline void Buffer::move_to_previous_page()
{
    if (ix_top_line > 0) ix_top_line -= window_height;
}

