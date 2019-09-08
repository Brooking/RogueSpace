#ifndef _iactor_mock_h_
#define _iactor_mock_h_
#include "iactor.h"

class iActorMock : public iActor
{
public:
    iActorMock(unsigned int move_time) : move_time_(move_time) {}
    virtual ~iActorMock() = default;

    virtual unsigned int move() { return this->move_time_; }

private:
    unsigned int move_time_;
};

#endif // _iactor_mock_h_