#ifndef _imap_mock_h_
#define _imap_mock_h_

#include "imap.h"

//
// a mock of iMap, for use in testing shadow casting (FOV)
//
class iMapMock : public iMap
{
private:
    struct MapEntry
    {
        MapEntry() : visible(false), opaque(false) {}
        ~MapEntry() {}

        bool visible;
        bool opaque;
    };

public:
    iMapMock(uint width, uint height) :
        map(std::vector<std::vector<MapEntry>>(height, std::vector<MapEntry>(width)))
    {}
    virtual ~iMapMock() {}

    // Set the visibility of the cell at the given position.
    virtual void set_visible(uint cell, uint row, bool visible) { this->map[row][cell].visible = visible; }

    // Return whether the given position is visible
    bool is_visible(uint cell, uint row) { return this->map[row][cell].visible; }
    
    // iMap: Return the width of the map.
    virtual uint get_width() const { return this->map[0].size(); }

    // iMap: Return the height of the map.
    virtual uint get_height() const { return this->map.size(); }

    // set a position to opaque
    void set_opaque(uint cell, uint row, bool opaque) { this->map[row][cell].opaque = opaque; }

    // iMap: Return whether the given position holds an opaque cell.
    virtual bool is_opaque(uint cell, uint row) const { return this->map[row][cell].opaque; }

private:
    std::vector<std::vector<MapEntry>> map;   
};

#endif // _imap_mock_h_