#include "Splitter.h"
#include <cstring>
#include <cstdlib>
#include "Buffer.h"
#define DIR_SEP '/'

Splitter::Splitter( char *filename, bool verbose,  char *logOutput , char *outputPath,  char *chapterSign )

{
    title_ = NULL;
    chapterSign_ = NULL;
    log_=NULL;
    outputPath_=NULL;
    curTitle_ = NULL;
    filename_= new char[strlen(filename)+1];
    strcpy(filename_,filename);
    filename_[strlen (filename)]='\0';
    filesize_ = getFileSize (filename_);
    maxPieces_=filesize_/FILESIZE+filesize_/(FILESIZE*10);
    curPiece_=0;

    outputPath_ = new char [strlen(filename)+(outputPath!=NULL?strlen(outputPath):0)+1];
    if (outputPath!=NULL)
    {
         strcpy (outputPath_,outputPath);
    }
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
            exit (100);
        }
    }

    verbose_=verbose;

    if (chapterSign!=NULL)
    {
		int tmp = strlen (chapterSign);
		chapterSign_ = new char [tmp];	 
        strcpy (chapterSign_,chapterSign);
    }

    if (!openFile () || filesize_ == -1)
    {
        if (verbose_)
        {
            if (verbScreen_)
                printf ("ERR_INIT:Can't read file '%s'",filename_);
            else
                fprintf (log_,"ERR_INIT:Can't read file '%s'",filename_);
        }
        freeAll ();
        exit (100);
    }
}

Splitter::~Splitter()
{
	freeAll();
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
	char* res = new char[NUMSIZE+1];
	for (int i=0;i<NUMSIZE;i++)
		res[i]='0';
	int i=NUMSIZE-1;
	while (x!=0)
	{
		res[i--]='0'+x%10;
		x/=10;
	}
	res [NUMSIZE]='\0';
	return res;
}

void Splitter::findTitle (char* result)
{
    if (chapterSign_==NULL)
    {
        delete [] result;
        result= NULL;
    }
    fpos_t pos;
    fgetpos (f_input_,&pos);
    char* tmpStr = new char [FILESIZE];
    for (int i=0;i<FILESIZE;i++)
    {
        fgets (tmpStr,FILESIZE,f_input_);
    }
    fsetpos (f_input_,&pos);
    char* where = strstr (tmpStr,chapterSign_);    
    if (where == NULL) result=where;
    else
    {
        where [strchr(where,'\n')-where] = '\0';
        delete[] result;
        result = new char [strlen(where)];
        strcpy (result,where);
    }
    delete [] tmpStr;    
}

bool Splitter::openFile ()
{
    f_input_ = fopen (filename_,"r");
    return f_input_;
}

void Splitter::freeAll ()
{
    delete [] title_;
    delete [] chapterSign_;
    delete [] filename_;
    delete [] outputPath_;
    delete [] curTitle_;
}

bool Splitter::Split ()
{
    while (!feof(f_input_))
    {
        int diff = filesize_ - ftell (f_input_);

        findTitle (curTitle_);
        Buffer buffer ;
        buffer = Buffer ();         
        char* prevFile=NULL;
        if (curPiece_!=0)
        {
            prevFile= numToText (curPiece_-1);
        }

        char*   nxtFile=NULL;
        if (diff>FILESIZE)
        {
            nxtFile = numToText (curPiece_+1);
        }

        buffer.prepareBuffer (nxtFile,prevFile,curTitle_);
        buffer.fillBuffer (f_input_);
        if (diff<FILESIZE)
        {
           buffer.terminateBuffer (diff);
        }
        char* curFile = numToText (curPiece_);
        buffer.writeBuffer (curFile);
        delete [] prevFile;
        delete [] nxtFile;
        delete [] curFile;
        curPiece_++;
    }
    return true;
}
