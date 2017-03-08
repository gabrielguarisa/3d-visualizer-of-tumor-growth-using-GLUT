#ifndef CONFIG_HANDLER
#define CONFIG_HANDLER

#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <libconfig.h++>
#include <string>
#include "Util.h"
using namespace libconfig;

class ConfigHandler
{
private:
    Config cfg_;
    bool created_;



    void getPathsValues_()
    {
        const Setting& root = this->cfg_.getRoot();

        try
        {
            const Setting &pathsConf = root["viewer"]["paths"];

            pathsConf.lookupValue("agents", this->paths.agents);
            pathsConf.lookupValue("nut", this->paths.nut);
            pathsConf.lookupValue("egf", this->paths.egf);
            pathsConf.lookupValue("output", this->paths.output);

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
            const Setting &windowConf = root["viewer"]["window"];

            windowConf.lookupValue("title", this->window.title);
            windowConf.lookupValue("width", this->window.width);
            windowConf.lookupValue("height", this->window.height);
            windowConf.lookupValue("fullscreen", this->window.fullscreen);
        }
        catch(const SettingNotFoundException &nfex)
        {
            this->created_ = false;
            std::cerr << "Window Settings Not Found!" << std::endl;
        }
    }

    void getDisplayValues_()
    {
        const Setting& root = this->cfg_.getRoot();

        try
        {
            const Setting &windowConf = root["viewer"]["display"];

            windowConf.lookupValue("showLines", this->display.showLines);
            windowConf.lookupValue("showInfo", this->display.showInfo);
            int viewMode;

            windowConf.lookupValue("viewMode", viewMode);

            switch (viewMode) {
                case 0:
                    this->display.viewMode = STD;
                    break;
                case 1:
                    this->display.viewMode = NUT;
                    break;
                case 2:
                    this->display.viewMode = EGF;
                    break;
            }

            const Setting &cellsDisplayConf = root["viewer"]["display"]["cells"];

            cellsDisplayConf.lookupValue("showNEC", this->display.cells.NEC.visibility);
            cellsDisplayConf.lookupValue("showQUI", this->display.cells.QUI.visibility);
            cellsDisplayConf.lookupValue("showPRO", this->display.cells.PRO.visibility);
            cellsDisplayConf.lookupValue("showHIP", this->display.cells.HIP.visibility);
            cellsDisplayConf.lookupValue("showAPO", this->display.cells.APO.visibility);
            cellsDisplayConf.lookupValue("showNOR", this->display.cells.NOR.visibility);
            cellsDisplayConf.lookupValue("showG1", this->display.cells.G1.visibility);

        }
        catch(const SettingNotFoundException &nfex)
        {
            this->created_ = false;
            std::cerr << "Display Settings Not Found!" << std::endl;
        }
    }
public:
    ConfigHandler (std::string configFile = "config.cfg")
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
        this->getDisplayValues_();
    }

    bool created(){
        return created_;
    }

    struct
    {
        std::string title;
        int width,
            height;
        bool fullscreen;
    } window;

    struct
    {
        std::string agents,
                    nut,
                    egf,
                    output;
    } paths;

    struct
    {
        bool    showLines,
                showInfo;

        ViewMode viewMode;

        CellDisplayTypes cells;
    } display;
};

#endif /* end of include guard: CONFIG_HANDLER */
