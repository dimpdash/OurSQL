#include "Field.h"

bool Field::equals(Field const& field) const {
	return false;
}

bool operator==(Field const& lhs, Field const& rhs)
{
	return lhs.equals(rhs);
}
// http://en.wikipedia.org/wiki/Barton-Nackman_trick
// used in a simplified form here

