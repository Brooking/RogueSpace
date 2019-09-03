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
        MapEntry() : range_squared(INT_MAX), opaque(false) {}
        ~MapEntry() {}

        uint range_squared;
        bool opaque;
    };

public:
    iMapMock(uint width, uint height) :
        map(std::vector<std::vector<MapEntry>>(height, std::vector<MapEntry>(width)))
    {}
    virtual ~iMapMock() = default;

    // Set the los of the cell at the given position.
    virtual void set_los(uint cell, uint row, uint range_squared) 
    {
        assert(row < this->map.size());
        assert(cell < this->map[0].size());
        this->map[row][cell].range_squared = range_squared;
    }

    // Return whether the given position is in los
    uint has_los(uint cell, uint row)
    {
        uint range_squared = this->map[row][cell].range_squared;
        if (range_squared == INT_MAX)
        {
            return INT_MAX;
        }
        return static_cast<uint>(sqrt(range_squared));
    }
    
    // iMap: Return the width of the map.
    virtual uint get_width() const { return static_cast<uint>(this->map[0].size()); }

    // iMap: Return the height of the map.
    virtual uint get_height() const { return static_cast<uint>(this->map.size()); }

    // set a position to opaque
    void set_opaque(uint cell, uint row, bool opaque) { this->map[row][cell].opaque = opaque; }

    // iMap: Return whether the given position holds an opaque cell.
    virtual bool is_opaque(uint cell, uint row) const { return this->map[row][cell].opaque; }

private:
    std::vector<std::vector<MapEntry>> map;   
};

#endif // _imap_mock_h_