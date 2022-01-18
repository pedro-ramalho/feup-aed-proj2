#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <fstream>

#define MAX_CHARS_IGNORE std::numeric_limits <std::streamsize>::max()

void clear_screen();
std::vector<std::string> read_file(std::string filename);