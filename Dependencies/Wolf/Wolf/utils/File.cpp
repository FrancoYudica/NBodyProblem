#include "File.h"
#include <fstream>


string Wolf::File::read() const
{
    std::ifstream file(_fpath);
    string data;

    // Read position to end of file
    file.seekg(0, std::ios::end);

    // Allocates the requiered space
    data.reserve(file.tellg());

    // And sets back the pos to the start
    file.seekg(0, std::ios::beg);

    data.assign(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );
    file.close();
    return data;
}

void Wolf::File::write(const string& data)
{
    std::ofstream file(_fpath);
    file << data;
    file.close();
}
