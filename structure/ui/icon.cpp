#include "icon.h"

Icon::Icon(UIToken token, unsigned int adjacency) : token_(token)
{
    if ((long unsigned int)token >= (long unsigned int)UIToken::num_tokens)
    {
        throw std::invalid_argument("token too large");
    }

    this->color_pair_ = IconList[(long unsigned int)token].color_pair;
    if (token != UIToken::wall)
    {
        this->symbol_ = IconList[(long unsigned int)token].symbol;
    }
    else
    {
        if (adjacency >= 16) 
        {
            throw std::invalid_argument("adjacency too large");
        }

        // todo: this should be in a table, but the curses library macros screw it up        
        switch(adjacency)
        {
            case /* none*/ 0:
                this->symbol_ = '+';
                break;

            case /* N   */ 1:
            case /* S   */ 4:
            case /* NS  */ 5:
                this->symbol_ = ACS_VLINE;
                break;

            case /* E   */ 2:            
            case /* W   */ 8:
            case /* EW  */ 10:
                this->symbol_ = ACS_HLINE;
                break;

            case /* NE  */ 3:
                this->symbol_ = ACS_LLCORNER;
                break;

            case /* ES  */ 6:
                this->symbol_ = ACS_ULCORNER;
                break;

            case /* NES */ 7:
                this->symbol_ = ACS_LTEE;
                break;

            case /* NW  */ 9:
                this->symbol_ = ACS_LRCORNER;
                break;

            case /* NEW */ 11:
                this->symbol_ = ACS_BTEE;
                break;

            case /* SW  */ 12:
                this->symbol_ = ACS_URCORNER;
                break;

            case /* NSW */ 13:
                this->symbol_ = ACS_RTEE;
                break;

            case /* ESW */ 14:
                this->symbol_ = ACS_TTEE;
                break;

            case /* NESW*/ 15:
                this->symbol_ = ACS_PLUS;
                break;

            default:
                this->symbol_ = '?';
                break;
        }
    }
}
