#ifndef CELL_FACTORY
#define CELL_FACTORY

#include <fstream>
#include <cmath>
#include <string>
#include "CellFrame.h"

class CellFactory
{
public:
    static CellFrame* makeFrame(std::string fileName)
    {
    	// FILE
    	std::ifstream file;

        // FRAME
        CellFrame frame;

        Cell c;
        int type;
        int numCells = 0;

    	file.open(fileName.c_str());

    	file >> frame.domain.x >> frame.domain.y >> frame.domain.z;
    	file >> numCells >> frame.time;
    	file >> frame.outCells >> frame.tumorCells;
        
    	// Reading all cells
    	for (std::size_t i = 0; i < numCells; i++) {
    		file >> type;
            c.type = (CellType)type;
    		file >> c.coordinates.x >> c.coordinates.y >> c.coordinates.z;
    		file >> c.nucleusRadius >> c.radius >> c.actionRadius >> c.lifetime >> c.previousState;
            file >> c.oConsumption >> c.egfConsumption >> c.calcification >> c.sigmaEGF >> c.sigmaO;
    		file >> c.speed.x >> c.speed.y >> c.speed.z;

    		frame.cells.push_back(c);
    	}

    	file.close();
    	return new CellFrame(frame);
    }


    static std::vector<CellFrame*> makeListFrames(std::vector<std::string> files)
    {
        std::vector<CellFrame*> frames;

        for (std::size_t i = 0; i < files.size(); i++)
    	{
            frames.push_back(CellFactory::makeFrame(files[i]));
            std::cout << files[i] << std::endl;
        }

        return frames;
    }

};

#endif /* end of include guard: CELL_FACTORY */
