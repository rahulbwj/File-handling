#ifndef LISTFILES_H
#define LISTFILES_H
#include <FS.h>

void listFiles(fs::FS &fs, const char * dirname, uint8_t levels);

#endif