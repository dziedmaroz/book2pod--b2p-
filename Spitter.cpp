#include "Splitter.h"
#include <cstring>
#include <cstdlib>

#define DIR_SEP '/'

Splitter::Splitter( char *filename, bool verbose,  char *logOutput , char *outputPath,  char *chapterSign )

{
    title_ = NULL;
    chapterSign_ = NULL;
    log_=NULL;

    filename_= new char[strlen(filename)+1];
    strcpy(filename_,filename);
	filename_[strlen (filename)]='\0';
	filesize_ = getFileSize (filename_);

    outputPath_ = new char [strlen(filename)+strlen(outputPath)+1];
    strcpy (outputPath_,outputPath);
 //   outputPath_[strlen(outputPath_)]=DIR_SEP;
    strcat (outputPath_,filename);


    if (logOutput ==0 ||strlen(logOutput)==0) verbScreen_ = true;
    else
    {
        verbScreen_=false;
        log_ = fopen (logOutput,"w");
        if (!log_)
        {
            printf ("ERR_INIT:Can't create log file ('%s')\n",logOutput);
        }
    }

    verbose_=verbose;

    if (chapterSign!=NULL)
    {
		int tmp = strlen (chapterSign);
		chapterSign_ = new char [tmp];	 
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
    if (file!=NULL)
    {
		fseek (file,0,SEEK_END);
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
