#ifndef GRID_FACTORY
#define GRID_FACTORY

#include "Util.h"

class GridFactory{
public:
    static std::vector<std::vector<std::vector<double> > > makeGrid(std::string fileName, Vector3 dimension, float accuracy)
    {
        // FILE
    	std::ifstream _file;

        std::string _line;

        Vector3 _coordinates;

        std::vector<std::vector<std::vector<double> > > _grid;

        int _height = ((int)round(dimension.x/accuracy))+1,
            _width = ((int)round(dimension.y/accuracy))+1,
            _depth = ((int)round(dimension.z/accuracy))+1;

        _grid.resize(_height);
        for (int i = 0; i < _height; ++i) {
            _grid[i].resize(_width);

            for (int j = 0; j < _width; ++j)
                _grid[i][j].resize(_depth);
        }


    	_file.open(fileName.c_str());

        while(getline(_file, _line)) {
            if (!_line.length() || _line[0] == '#')
                continue;
            std::istringstream iss(_line);
            iss >> _coordinates.x >> _coordinates.y >> _coordinates.z >> _grid[(int)round(_coordinates.x/accuracy)][(int)round(_coordinates.y/accuracy)][(int)round(_coordinates.z/accuracy)];
        }
    	_file.close();
    	return _grid;
    }

    static std::vector<std::vector<std::vector<std::vector<double> > > > makeListGrids(std::vector<std::string> fileNames, Vector3 dimension, float accuracy)
    {
        std::vector<std::vector<std::vector<std::vector<double> > > > grids;
        for (int i = 0; i < fileNames.size(); i++)
    	{
            grids.push_back(GridFactory::makeGrid(fileNames[i], dimension, accuracy));
            std::cout << fileNames[i] << std::endl;
        }
        return grids;
    }
};

#endif /* end of include guard: GRID_FACTORY */
