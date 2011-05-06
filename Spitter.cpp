#include "Splitter.h"
#include <cstring>
#include <cstdlib>

#define DIR_SEP '/'

Splitter::Splitter( char *filename, bool verbose,  char *logOutput , char *outputPath,  char *chapterSign )

{
    title_ = NULL;
    chapterSign_ = NULL;
    log_=NULL;

    filename_= new char[strlen(filename)];
    strcpy(filename_,filename);

    outputPath_ = new char [strlen(filename)+strlen(outputPath)+1];
    strcpy (outputPath_,outputPath);
    outputPath_[strlen(outputPath_)]=DIR_SEP;
    strcat (outputPath_,filename);


    if (logOutput ==0 ||strlen(logOutput)==0) verbScreen_ = true;
    else
    {
        verbScreen_=false;
        log_ = fopen (logOutput,"a");
        if (!log_)
        {
            printf ("ERR_INIT:Can't create log file ('%s')\n",logOutput);
        }
    }

    verbose_=verbose;

    if (chapterSign!=NULL)
    {
        chapterSign_ = new char [strlen (chapterSign)];
        strcpy (chapterSign_,chapterSign);
    }
}

Splitter::~Splitter()
{
	delete [] title_;
	delete [] chapterSign_;
	delete [] filename_;
	delete [] outputPath_;
	if (log_!=NULL) fclose (log_);
}


int Splitter::getFileSize (char *filename)
{
    int size =-1;
    FILE* file = fopen (filename,"r");
    if (!file)
    {
        size=ftell (file);
        fclose (file);
    }
    else
    {
       printf ("ERR_INIT: Can't open file '%s'.\n",filename);
       exit (100);
    }

    return size;
}

char* Splitter::genNoteName ()
{
    char* piece = numToText (curPiece_);
    char* result = new char [NUMSIZE+5];
    strcpy (result,"PAGE");
    strcat (result,piece);
    result[NUMSIZE+4]='\0';
    delete [] piece;

    return result;
}


char* Splitter::numToText (int x)
{
	char* res = new char[NUMSIZE];
	for (int i=0;i<NUMSIZE;i++)
		res[i]=0;
	int i=NUMSIZE-1;
	while (x!=0)
	{
		res[i--]=x%10;
		x/=10;
	}
	return res;
}
