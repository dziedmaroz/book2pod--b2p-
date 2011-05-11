#ifndef BUFFER_H
#define BUFFER_H

#include "PodExceptions.h"
#include <cstring>
#include <stdio.h>

#define BUFF_SIZE 4096
#define SCREEN_SIZE 4097
class Buffer
{
    char buffer_ [BUFF_SIZE];
    int textBeg_;
    int textEnd_;


public:
    Buffer() {textBeg_=0;textEnd_=BUFF_SIZE;};
    bool writeTagTitle (char* title);
    bool writeTagPrev (char* filename);
    bool writeTagNext (char* filename);
    bool fillBuffer (FILE* fin);
    bool writeBuffer (char* foutName);
};

#endif // BUFFER_H
