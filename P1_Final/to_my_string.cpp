#include <string>
#include <sstream>

inline std::string to_my_string(int x)
{
	std::ostringstream oss;
	oss << x;
	return oss.str();
}
