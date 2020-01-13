#ifndef _uitoken_h_
#define _uitoken_h_

//
// Base type of this thing
//
enum class TokenType
{
    none = 0,
    test,
    floor,
    wall,
    hero,
    rat,
    bee,
    dog,
    num_tokens // must be last!!!
};

//
// The wall shape
//
enum class WallType
{
    pillar = 0,
    n,
    e,
    ne,
    s,
    ns,
    se,
    nse,
    w,
    nw,
    we,
    nwe,
    sw,
    nsw,
    swe,
    nswe,
    count // must be last
};

//
// The thing that is visible at a given spot
//
class UIToken final
{
public:
    // wall constructor
    UIToken( WallType wall_type, bool visible, bool remembered, bool lit);

    // default wall constructor
    UIToken(WallType wall_type);

    // type constructor
    UIToken(TokenType token_type, bool visible, bool remembered, bool lit);

    // default type constructor
    UIToken(TokenType token_type);

    // default constructor
    UIToken();

    // The base type
    TokenType token_type() const { return this->token_type_; }

    // This is visible
    bool is_visible() const { return this->visible_; }

    // This has been seen and the hero remembers it
    bool is_remembered() const { return this->remembered_; }

    // This is currently lit from the hero's point of view
    bool is_lit() const { return this->lit_; }

    // The specific wall type (directions)
    WallType wall_type() { return this->wall_type_; }

private:
    void verify_visible_seen() const;
    void verify_non_wall() const;

private:
    static const bool DefaultVisible = false;
    static const bool DefaultLit = false;
    static const bool DefaultRemembered = false;

private:
    TokenType token_type_;
    bool visible_;
    bool remembered_;
    bool lit_;
    WallType wall_type_;
};

#endif // _uitoken_h_