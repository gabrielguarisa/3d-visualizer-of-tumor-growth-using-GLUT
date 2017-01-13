#pragma once

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