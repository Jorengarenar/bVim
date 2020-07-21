#include "util.hpp"

#include <cctype>

EnableCursor::EnableCursor()
{
    curs_set(TRUE);
    echo();
}

EnableCursor::~EnableCursor()
{
    curs_set(FALSE);
    noecho();
}

char toPrintable(int x)
{
    if (isprint(x)) {
        return x;
    }
    else {
        return ' ';
    }
}
