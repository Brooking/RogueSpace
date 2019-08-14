#ifndef _imap_h_
#define _imap_h_

typedef unsigned int uint;

class iMap {
    public:
        // Set the visibility of the cell at the given position.
        virtual void set_visible(uint x, uint y, bool visible) = 0;

        // Return the width of the map.
        virtual uint get_width() const = 0;

        // Return the height of the map.
        virtual uint get_height() const = 0;

        // Return whether the given position holds an opaque cell.
        virtual bool is_opaque(uint x, uint y) const = 0;
};

#endif // _imap_h_
