#ifndef CONFIG_FILES_HANDLER
#define CONFIG_FILES_HANDLER

#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <libconfig.h++>
#include <string>
#include "Util.h"
using namespace libconfig;

class ConfigFileHandler
{
private:
    Config cfg_;
    bool created_;

    void getPathsValues_()
    {
        const Setting& root = this->cfg_.getRoot();

        try
        {
            const Setting &paths = root["viewer"]["paths"];
            int count = paths.getLength();

            for(int i = 0; i < count; ++i)
            {
                const Setting &pathsConf = paths[i];

                // Only output the record if all of the expected fields are present.
                std::string  agents,
                        nut,
                        egf,
                        output;

                pathsConf.lookupValue("agents", this->paths.agents);
                pathsConf.lookupValue("nut", this->paths.nut);
                pathsConf.lookupValue("egf", this->paths.egf);
                pathsConf.lookupValue("output", this->paths.output);

            }
        }
        catch(const SettingNotFoundException &nfex)
        {
            this->created_ = false;
            std::cerr << "Paths Settings Not Found!" << std::endl;
        }
    }

    void getWindowValues_()
    {
        const Setting& root = this->cfg_.getRoot();

        try
        {
            const Setting &window = root["viewer"]["window"];
            int count = window.getLength();

            for(int i = 0; i < count; ++i)
            {
                const Setting &windowConf = window[i];

                // Only output the record if all of the expected fields are present.
                std::string title;
                int width,
                    height;

                windowConf.lookupValue("title", this->window.title);
                windowConf.lookupValue("width", this->window.width);
                windowConf.lookupValue("height", this->window.height);

            }
        }
        catch(const SettingNotFoundException &nfex)
        {
            this->created_ = false;
            std::cerr << "Window Settings Not Found!" << std::endl;
        }
    }
public:
    ConfigFileHandler (std::string configFile = "config.cfg")
    {
        this->created_ = false;
        try
        {
            this->cfg_.readFile(configFile.c_str());
            this->created_ = true;
        }
        catch(const FileIOException &fioex)
        {
            std::cerr << "I/O error while reading file." << std::endl;
        }
        catch(const ParseException &pex)
        {
            std::cerr   << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                        << " - " << pex.getError() << std::endl;
        }

        this->getPathsValues_();
        this->getWindowValues_();
    }

    bool created(){
        return created_;
    }

    struct
    {
        std::string title;
        int width,
            height;
    } window;

    struct
    {
        std::string agents,
                    nut,
                    egf,
                    output;
    } paths;
};

#endif /* end of include guard: CONFIG_FILES_HANDLER */
