#ifndef FRAME_FACTORY
#define FRAME_FACTORY

#include <fstream>
#include <cmath>
#include <string>
#include "Frame.h"

class FrameFactory
{
public:
    static Frame* makeFrame(std::string fileName)
    {
    	// FILE
    	std::ifstream file;

        // FRAME
        Frame frame;

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
    	return new Frame(frame);
    }


    static std::vector<Frame*> makeListFrames(std::vector<std::string> files)
    {
        std::vector<Frame*> frames;

        for (std::size_t i = 0; i < files.size(); i++)
    	{
            frames.push_back(FrameFactory::makeFrame(files[i]));
            std::cout << files[i] << std::endl;
        }

        return frames;
    }

};

#endif /* end of include guard: FRAME_FACTORY */
