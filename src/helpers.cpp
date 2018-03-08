#include <string>
#include <cstring>

using std::string;
using std::strcpy;

/* Converts a std::string to a char* */
char *convert(const std::string & s)
{
    char *pc = new char[s.size()+1];
    std::strcpy(pc, s.c_str());
    return pc;
}
