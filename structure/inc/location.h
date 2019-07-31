#ifndef _location_h_
#define _location_h_

struct Location
{    
public:
    Location() : 
        row(0), cell(0)
    {}

    Location(int row, int cell) :
        row(row), cell(cell)
    {}

public:
    int row;
    int cell;
};

#endif // _location_h_