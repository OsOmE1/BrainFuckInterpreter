#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv) {
    FILE* f = fopen(argv[1], "rb");
    fseek(f, 0, SEEK_END);
    long length = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* buffer = malloc(length);
    fread(buffer, 1, length, f);
    int i = 0, seekClosing = 0, direction = 0, currentcell = 0, cellcount = 1;
    unsigned char* cells = (unsigned char*)malloc(sizeof(unsigned char));
    while (i < length) {
        if (seekClosing != 0) {
            if (buffer[i] == (direction ? ']' : '[')) seekClosing++, direction ? i-- : i++;
            if (buffer[i] == (direction ? ']' : '[')) continue;
            if (buffer[i] == (direction ? '[' : ']')) seekClosing--;
            if (buffer[i] == (direction ? '[' : ']') && !seekClosing) continue;
            if (direction) i--;  continue;
        } if (direction == 1 && seekClosing == 0) direction = 0;
        switch (buffer[i]) {
        case '>':
            if (currentcell < cellcount - 1) {
                currentcell++; break;
            } cells = realloc(cells, sizeof(unsigned char) * cellcount++), cells[cellcount - 1] = 0, currentcell++; break;
        case '<': if (currentcell) currentcell--; break;
        case '+': cells[currentcell] == 0xFF ? cells[currentcell] = 0 : cells[currentcell]++; break;
        case '-': !cells[currentcell] ? cells[currentcell] = 0xFF : cells[currentcell]--; break;
        case '.': printf("%c", cells[currentcell]);
        case '[': if (cells[currentcell] == 0) seekClosing = 1; break;
        case ']': if (!cells[currentcell]) break; direction = 1, seekClosing = 1;
        default: break;
        } direction ? i-- : i++;
    } return 0;
}
