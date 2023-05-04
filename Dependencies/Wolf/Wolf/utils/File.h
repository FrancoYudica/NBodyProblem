#ifndef WOLF_FILE
#define WOLF_FILE

#include <string>
#include <filesystem>

using std::string;

namespace Wolf
{
    class File
    {
        public:
        File(const string& path) : _fpath(path) {}

        string read() const;
        void write(const string&);
        private:
        string _fpath;

    };
}

#endif