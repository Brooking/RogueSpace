#ifndef _rect_h_
#define _rect_h_

#include <memory>
#include "ipane.h"

//
// Holder for a rectangle
//
class Rect
{
public:
    // sides constructor
    Rect(unsigned int left, unsigned int right, unsigned int top, unsigned int bottom);

    // pane constructor
    Rect(std::shared_ptr<iPane> pane);

    // copy constructor
    Rect(Rect& that);

    // the rects are identical
    bool operator==(const Rect& that) const;

    // assign one rect to another
    Rect& operator=(const Rect& that);

    // remove a rect from this one, IFF it leaves a rect or exactly nothing
    std::shared_ptr<Rect> subtract(const Rect& that, bool& valid) const;

    // the rectangle is collapsed (horizontally, vertically, or both)
    bool collapsed() const;

    // the given rect fits inside this one
    bool contains(const Rect& that) const;

    // spot+size accessors
    unsigned int screen_cell() const { return this->left_; }
    unsigned int screen_row() const { return this->top_; }
    unsigned int height() const { return this->bottom_ - this->top_; }
    unsigned int width() const { return this->right_ - this->left_; }

    // sides accessors
    unsigned int left() const { return this->left_; }
    unsigned int right() const { return this->right_; }
    unsigned int top() const { return this->top_; }
    unsigned int bottom() const { return this->left_; }

private:
    unsigned int left_;
    unsigned int right_;
    unsigned int top_;
    unsigned int bottom_;
};

#endif // _rect_h_