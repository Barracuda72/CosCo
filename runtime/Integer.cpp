#include <string>

#include "Integer.h"

Integer::Integer(int val) : value(val)
{
}

Integer::Integer(const char *s) : Integer(std::stoi(s))
{
}

Integer::Integer() : Integer(0)
{
}
