#include "Buffer.h"

#include <cstdlib>

Buffer::Buffer (int inFileSize)
{
    textBeg_=0;
    textEnd_=BUFF_SIZE;
    bufferEnd_=BUFF_SIZE;

    for (int i=0;i<BUFF_SIZE;i++)
    {
        buffer_[i]='0';
    }
    inFileSize_=inFileSize;

}
bool Buffer::writeTagTitle (char *title)
{
    if (title!=NULL)
    {
        char tagBeg [] = "<TITLE>";
        char tagEnd [] = "</TITLE>";

        for (int i=0;i<strlen(tagBeg);i++)
        {
            buffer_[textBeg_++]=tagBeg[i];
            if (textBeg_>textEnd_) return false;
        }
        for (int i=0;i<strlen(title);i++)
        {
            buffer_[textBeg_++]=title[i];
            if (textBeg_>textEnd_) return false;
        }
        for (int i=0;i<strlen(tagEnd);i++)
        {
            buffer_[textBeg_++]=tagEnd[i];
            if (textBeg_>textEnd_) return false;
        }
    }
    return true;
}

bool Buffer::writeTagPrev (char *filename)
{
    if (filename!=NULL)
    {
        char tagBeg [] = "<A HREF=\"";
        char tagEnd [] = "\"> <- </A>";

        for (int i=0;i<strlen(tagBeg);i++)
        {
            buffer_[textBeg_++]=tagBeg[i];
            if (textBeg_>textEnd_) return false;
        }
        for (int i=0;i<strlen(filename);i++)
        {
            buffer_[textBeg_++]=filename[i];
            if (textBeg_>textEnd_) return false;
        }
        for (int i=0;i<strlen(tagEnd);i++)
        {
            buffer_[textBeg_++]=tagEnd[i];
            if (textBeg_>textEnd_) return false;
        }
    }
   return true;
}

bool Buffer::writeTagNext (char *filename)
{
    if (filename!=NULL)
    {
        char tagBeg [] = "<A HREF=\"";
        char tagEnd [] = "\"> -> </A>";
        textEnd_=BUFF_SIZE-1;

        for(int i=strlen(tagEnd);i>0;i--)
        {
            buffer_[textEnd_]=tagEnd[i-1];
            textEnd_--;
            if (textBeg_>textEnd_) return false;
        }

        for (int i=strlen(filename);i>0;i--)
        {
            buffer_[textEnd_--]=filename[i-1];
            if (textBeg_>textEnd_) return false;
        }

        for (int i=strlen(tagBeg);i>0;i--)
        {
            buffer_[textEnd_--]=tagBeg[i-1];
            if (textBeg_>textEnd_) return false;
        }
        textEnd_++;
    }
    return true;
}

bool Buffer::writeBuffer (char *foutName)
{
    FILE* fout = fopen (foutName,"w");
    if (!fout) return false;
    int i=0;
    while (buffer_[i]!='\0' && i<BUFF_SIZE)
        fprintf (fout,"%c",buffer_[i++]);
    fclose (fout);
    return true;
}

bool Buffer::fillBuffer (FILE *fin)
{     
     int puntcuationMarkPos = BUFF_SIZE;
     fpos_t fpunctuationMarkPos; 
     fgetpos(fin,&fpunctuationMarkPos);
     bool shift = true;
     for (int i=textBeg_;i<textEnd_;i++)
     {
         buffer_[i]=fgetc(fin);
         if (buffer_[i+1]=='.' || buffer_[i+1]==' ' || buffer_[i+1]==',' || buffer_[i+1]=='!' ||
                buffer_[i+1]=='?' || buffer_[i+1]==';' || buffer_[i+1]=='\n' || buffer_[i+1]=='-' )
         {
             fgetpos (fin,&fpunctuationMarkPos);
             puntcuationMarkPos = i;
         }
         if (feof(fin))
         {
             shift = false;
             break;
         }
     }      

     if (puntcuationMarkPos!=BUFF_SIZE && shift)
     {
         fsetpos (fin,&fpunctuationMarkPos);
         shiftTextEndLeft (textEnd_-puntcuationMarkPos+1);
     }


     for (int i=SCREEN_SIZE;i<textEnd_;i++)
     {
         if (buffer_[i]!=' ')
         {
             for (int j=i;j>i-SCREEN_SIZE;j--)
                 if (buffer_[j]==' ')
                 {
                     buffer_[j]='\n';
                     break;
                 }
         }
         else
         {
             buffer_[i]='\n';
         }
     }
     for (int i=0;i<bufferEnd_;i++)
         if (buffer_[i]=='\0') buffer_[i]=' ';
     return true;
}

void Buffer::terminateBuffer (int pos)
{
    buffer_[pos]='\0';
    bufferEnd_=pos;
}

bool Buffer::prepareBuffer (char *nxtFilename, char *prevFilename, char *title)
{
    if (writeTagTitle (title))
    {
        if (writeTagPrev (prevFilename))
        {
            if (writeTagNext (nxtFilename))
            {
                // nothing to do
            }
        }
    }
    return false;
}

bool Buffer::shiftTextEndLeft (int count)
{
    count;
    for (int i=textEnd_;i<bufferEnd_;i++)
    {
        buffer_[i-count]=buffer_[i];
    }
    textEnd_-=count;
    terminateBuffer (bufferEnd_-count);
    return textEnd_>textBeg_;
}

void Buffer::writeStat (FILE *fout)
{
    fprintf (fout,"textBeg_                 : %d\n",textBeg_);
    fprintf (fout,"textEnd_                 : %d\n",textEnd_);
    fprintf (fout,"buffer[textBeg_]         : %c   %d\n",buffer_[textBeg_],buffer_[textBeg_]);
    fprintf (fout,"buffer[textEnd_]         : %c   %d\n",buffer_[textEnd_],buffer_[textEnd_]);
    fprintf (fout,"textEnd_-textBeg_ (mod 4): %d\n",(textEnd_-textBeg_)%4);
}

int Buffer::getDiff (FILE *file)
{
    fpos_t pos;
    fgetpos (file,&pos);
    int f_this = fseek (file,0,SEEK_CUR);
    fseek(file,0,SEEK_END);
    int f_end = ftell (file);
    fsetpos (file,&pos);
    return f_end-f_this;
}
