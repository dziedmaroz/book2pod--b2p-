#ifndef BUFFER_H
#define BUFFER_H

#include "PodExceptions.h"
#define BUFFSIZE 4096
class Buffer
{
    char buffer_ [4096];
    int textBeg_;
    int textEnd_;


public:
    Buffer(){};
    bool writeTagTitle (char* title);
    bool writeTagPrev (char* filename);
    bool writeTagNext (char* filename);
    bool flushText (FILE* fin);
    bool writeBuffer (char* foutName);
};

#endif // BUFFER_H
