#ifndef FILE_LIST
#define FILE_LIST

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

#include <dirent.h>

class FileList
{
public:
    static std::vector<std::string> getFileNames(std::string path="files"){
        if(path[path.size() - 1] != '/')
            path.push_back('/');
        std::vector<std::string> result;
        DIR *dpdf_;
        struct dirent *epdf_;
        dpdf_ = opendir(path.c_str());
        if (dpdf_ != NULL){
            std::string temp;
            while (epdf_ = readdir(dpdf_)){
                //std::cout << epdf->d_name << std::endl;
                temp = path + epdf_->d_name;
                result.push_back(temp);
            }
            std::sort(result.begin(), result.end());
        }
        return result;
    }
};


#endif /* end of include guard: FILE_LIST */
