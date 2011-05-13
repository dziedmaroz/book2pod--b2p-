#include "Buffer.h"

Buffer::Buffer ()
{
    textBeg_ = 0;
    textEnd_ = BUFF_SIZE;
}

bool Buffer::writeTagTitle (char *title)
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
    return true;
}

bool Buffer::writeTagPrev (char *filename)
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
    return true;
}

bool Buffer::writeTagNext (char *filename)
{
    char tagBeg [] = "<A HREF=\"";
    char tagEnd [] = "\"> -> </A>";
    textEnd_=BUFF_SIZE;

    for(int i=strlen(tagEnd);i>0;i--)
    {
        buffer_[textEnd_--]=tagEnd[i-1];
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

    return true;
}

bool Buffer::writeBuffer (char *foutName)
{
    FILE* fout = fopen (foutName,"w");
    if (!fout) return false;
    fprintf (fout,"%s",buffer_);
    fclose (fout);
    return true;
}

bool Buffer::fillBuffer (FILE *fin)
{
     while (textBeg_!=textEnd_ || !feof(fin))
     {
         buffer_[textBeg_++]=fgetc (fin);
     }

     for (int i=SCREEN_SIZE;i<BUFF_SIZE;i++)
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

     return true;
}
