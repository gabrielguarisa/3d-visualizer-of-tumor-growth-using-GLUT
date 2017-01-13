#include "FileReader.h"

FileReader::FileReader(std::string path)
{
    dpdf_ = opendir(path.c_str());
    if (dpdf_ != NULL){
        std::string temp;
        while (epdf_ = readdir(dpdf_)){
            //std::cout << epdf->d_name << std::endl;
            temp = path + "/" + epdf_->d_name;
            result.push_back(temp);
        }
        std::sort(result.begin(), result.end());
    }
}
