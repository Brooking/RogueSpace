#ifndef _original_shadow_cast_h_
#define _original_shadow_cast_h_

#include "imap.h"

//
// calculate a field of view, using the shadow casting algorithm
//

// calculate for the entire map
void do_fov(iMap& map, uint x, uint y);

// calculate only for a given radius around the origin
void do_fov(iMap& map, uint x, uint y, uint radius);

#endif // _original_shadow_cast_h_