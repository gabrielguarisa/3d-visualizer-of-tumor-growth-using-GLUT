#ifndef CELL_FACTORY
#define CELL_FACTORY

#include <fstream>
#include <cmath>
#include <string>
#include "CellFrame.h"

/*
** CELL FACTORY
*/
class CellFactory
{
public:
    static CellFrame* makeFrame(std::string fileName)
    {
    	// FILE
    	std::ifstream file;
    	//

    	// CellFrame stuff
    	GLfloat	outCells = 0.0,
    			tumCells = 0.0,
    			time = 0.0;

    	GLint numCells = 0;

    	Vector3	domain;

    	std::vector<Cell> cells;
    	//

    	// Cell stuff
    	GLfloat radius = 0.0f,
    			calcification = 0.0f,
    			nucleusRadius = 0.0f,
                actionRadius = 0.0f,
                lifetime = 0.0f,
                previousState = 0.0f,
                oConsumption = 0.0f,
                egfConsumption = 0.0f;

    	GLint 	type = 0;

    	Vector3 coord,
    			speed;
    	//

    	file.open(fileName.c_str());

    	file >> domain.x >> domain.y >> domain.z;
    	file >> numCells >> time;
    	file >> outCells >> tumCells;

    	// Reading all cells
    	for (int i = 0; i < numCells; i++) {
    		file >> type;
    		file >> coord.x >> coord.y >> coord.z ;
    		file >> nucleusRadius >> radius >> actionRadius;
            file >> lifetime >> previousState >> oConsumption >> egfConsumption >> calcification;
    		file >> speed.x >> speed.y >> speed.z;

    		cells.push_back(Cell(   (CellType)type, coord, nucleusRadius, radius, actionRadius,
                                    lifetime, previousState, oConsumption, egfConsumption, calcification, speed));


    	}
    	//
    	file.close();
    	return new CellFrame(time, domain, outCells, tumCells, numCells, cells);
    }


    static std::vector<CellFrame*> makeListFrames(std::vector<std::string> fileNames)
    {
        std::vector<CellFrame*> frames;
        for (int i = 2; i < fileNames.size(); i++)
    	{
            frames.push_back(CellFactory::makeFrame(fileNames[i]));
            std::cout << fileNames[i] << std::endl;
        }
        return frames;
    }

};

#endif /* end of include guard: CELL_FACTORY */
