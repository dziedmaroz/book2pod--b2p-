#include "main.h"

int main (int argc, char** argv)
{
    Args* args= parseArgumets (argc,argv);

    Splitter split (args->filename_,args->verbose_,args->outLog_,args->outputPath_,args->chapterSign_);


    delete [] args->chapterSign_;
    delete [] args->filename_;
    delete [] args->outLog_;
    delete [] args->outputPath_;
    delete args;
    return 0;
}
Args* parseArgumets (int argc, char** argv)
{
    Args* args = new Args;

    args->chapterSign_=NULL;
    args->filename_=NULL;
    args->outLog_=NULL;
    args->outputPath_=NULL;
    args->verbose_=NULL;
    unsigned int pattern = 0;

    args->filename_ = new char [strlen (argv[argc-1])];
    strcpy ( args->filename_,argv[argc-1]);

    for (int i=1;i<argc-1;i++)
    {
        if (strcmp ("-o",argv[i]))
        {
            if (!(pattern && 16)) // 1 0 0 0 0
            {
                args->outputPath_ = new char [strlen (argv[i+1])];
                strcpy (args->outputPath_,argv[i+1]);
                i++;
                pattern|=16;
            }

        }
        if (strcmp ("-v",argv[i]))
        {
            if (!(pattern && 8)) // 0 1 0 0 0
            {
                args->verbose_=true;
                pattern|=8;
            }
        }
        if (strcmp ("-l",argv[i]))
        {
            if (! (pattern && 4)) // 0 0 1 0
            {
                args->outLog_ = new char [strlen(argv[i+1])];
                strcpy (args->outLog_,argv[i+1]);
                i++;
                pattern |= 4;
            }
        }
        if (strcmp ("-c",argv[i]))
        {
            if (! (pattern && 2))
            {
                args->chapterSign_ = new char [strlen(argv[i+1])];
                strcpy (args->chapterSign_,argv[i+1]);
                i++;
                pattern |=2;
            }
        }
    }
    return args;
}
