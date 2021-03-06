#ifndef _ithing_mock_h_
#define _ithing_mock_h_
#include "ithing.h"

class iThingMock : public iThing
{
public:
    iThingMock(
        TokenType token_type,
        std::shared_ptr<Tile> tile,
        ContentSize size = ContentSize::small,
        bool center = false,
        unsigned int move_time = 1) 
    : 
        token_type_(token_type), tile_(tile), content_size_(size), center_(center), move_time_(move_time)
    {}
    virtual ~iThingMock() = default;

    // iThing
    virtual TokenType token_type() const override {return this->token_type_; }
    virtual UIToken token() const override
    {
        if (this->token_type_ == TokenType::wall)
        {
            return UIToken(WallType::pillar,true,true,false);
        }
        return UIToken(this->token_type_,true,true,false); 
    }
    virtual std::shared_ptr<Tile> tile() const override { return this->tile_; }
    virtual ContentSize content_size() const override { return this->content_size_; }
    virtual bool is_center() const override { return this->center_; }
    virtual unsigned int move() { return this->move_time_; }
    virtual bool place(std::shared_ptr<Tile> tile) override { this->tile_ = tile; return true; }
    virtual bool remove() override { this->tile_ = nullptr; return true; }

private:
    TokenType token_type_;
    std::shared_ptr<Tile> tile_;
    ContentSize content_size_;
    bool center_;
    unsigned int move_time_;
};

#endif // _ithing_mock_h_