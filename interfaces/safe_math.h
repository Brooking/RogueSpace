#ifndef _safe_math_h_
#define _safe_math_h_

class SafeMath
{
public:
    static unsigned int Add(unsigned int uint_value, int int_value)
    {
        // todo: check to ensure that the uint can fit in an int
        int uint_value_as_int = static_cast<int>(uint_value);

        // todo: check to ensure that the resultant int does not overflow
        int int_sum = uint_value_as_int + int_value;
        return static_cast<unsigned int>(int_sum);
    }

    static unsigned int Subtract(unsigned int uint_value, int int_value)
    {
        // todo: check to ensure that the uint can fit in an int
        int uint_value_as_int = static_cast<int>(uint_value);

        // todo: check to ensure that the resultant int does not underflow
        int int_sum = uint_value_as_int - int_value;
        return static_cast<unsigned int>(int_sum);
    }
};

#endif // _safe_math_h_