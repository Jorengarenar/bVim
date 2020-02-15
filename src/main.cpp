#include <ncurses.h>
#include <vector>

#include "buffer.hpp"
#include "editor.hpp"
#include "window.hpp"

void init_curses()
{
    initscr();

    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();
    raw();
}

int main(int argc, char* argv[])
{
    std::vector<Buffer> buf;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            buf.push_back(Buffer(argv[i]));
        }
    }
    else {
        buf.push_back(Buffer());
    }

    wchar_t c;

    init_curses();

    Window w(LINES, COLS, buf[0]);
    refresh();

    w.fill();

    do {
        c = getch();
        while (c == KEY_RESIZE) {
            w.fill();
            c = getch();
        }

        if (c == 't') {
            w.buf(buf[1]);
        }
    } while (c != 'q');
    endwin();
}
