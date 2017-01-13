#ifndef FILEREADER_H
#define FILEREADER_H

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

#include <dirent.h>

class FileReader
{
private:
    DIR *dpdf_;
    struct dirent *epdf_;
public:
    FileReader(std::string path="files");
    std::vector<std::string> result;
};


#endif /* end of include guard: FILEREADER_H */
