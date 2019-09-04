#include <assert.h>
#include "rect.h"

Rect::Rect(
    unsigned int left, 
    unsigned int right, 
    unsigned int top, 
    unsigned int bottom)
:
    left_(left), right_(right), top_(top), bottom_(bottom)
{
    assert(left <= right);
    assert(top <= bottom);
}

Rect::Rect(std::shared_ptr<iPane> pane) :
    left_(pane->screen_cell()), 
    right_(pane->screen_cell() + pane->width()), 
    top_(pane->screen_row()), 
    bottom_(pane->screen_row() + pane->height())
{}

bool Rect::operator==(const Rect& that) const
{
    return 
        this->screen_row() == that.screen_row() &&
        this->screen_cell() == that.screen_cell() &&
        this->height() == that.height() &&
        this->width() == that.width();
}

Rect& Rect::operator=(const Rect& that)
{
    this->left_ = that.left();
    this->right_ = that.right();
    this->top_ = that.top();
    this->bottom_ = that.bottom();
    return *this;
}

std::shared_ptr<Rect> Rect::subtract(const Rect& that, bool& valid) const
{
    std::shared_ptr<Rect> result;
    valid = false;
    if (!this->contains(that))
    {
        return result;
    }

    // ensure that rect fits and touches on at least three sides
    unsigned int sides_touching = 0;
    unsigned int remainder_left = this->left();
    unsigned int remainder_right = this->right();
    unsigned int remainder_top = this->top();
    unsigned int remainder_bottom = this->bottom();

    // left
    if (this->left() < that.left())
    {
        remainder_right = that.left();
    }
    else
    {
        assert(this->left() == that.left());
        sides_touching++;
    }

    // right
    if (this->right() > that.right())
    {
        remainder_left = that.right();
    }
    else
    {
        assert(this->right() == that.right());
        sides_touching++;
    }

    // top
    if (this->top() < that.top())
    {
        remainder_bottom = that.top();
    }
    else
    {
        assert(this->top() == that.top());
        sides_touching++;
    }

    // bottom
    if (this->bottom() > that.bottom())
    {
        remainder_top = that.bottom();
    }
    else
    {
        assert(this->bottom() == that.bottom());
        sides_touching++;
    }

    if (sides_touching == 4)
    {
        // that rect takes up the whole of this rect
        valid = true;
        return result;
    }
    else if (sides_touching == 3)
    {
        // that rect touches on three sides, leaving a rectangle
        result = std::make_shared<Rect>(
            remainder_left,
            remainder_right,
            remainder_top,
            remainder_bottom);
        valid = true;
        return result;
    }

    // that rect touches on 2 or fewer sides
    return result;
}

bool Rect::collapsed() const
{
    return this->width() == 0 || this->height() == 0;
}

bool Rect::contains(const Rect& that) const
{
    return this->left() <= that.left() && 
        this->right() >= that.right() &&
        this->top() <= that.top() &&
        this->bottom() >= that.bottom();

}

