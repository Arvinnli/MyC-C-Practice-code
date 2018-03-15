#ifndef __CONTENT_TYPE_H
#define __CONTENT_TYPE_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

struct mimetype
{
    public:
    char *postfix;
    char *type;
    private:
};



const mimetype mimetable[128] = {
    /*Text*/
    {(char*)".txt", (char*)"text/plain"},
    {(char*)".css", (char*)"text/css"},
    {(char*)".js", (char*)"text/javascript"},
    {(char*)".xsl", (char*)"text/xml"},
    {(char*)".xsl", (char*)"text/xml"},
    {(char*)".xhtm", (char*)"text/html"},
    {(char*)".xht", (char*)"application/xhtml+xml"},
    {(char*)".xhtml", (char*)"application/xhtml+xml"},
    {(char*)".hts", (char*)"text/html"},
    {(char*)".shtml", (char*)"text/html"},
    {(char*)".htm", (char*)"text/html"},
    {(char*)".html", (char*)"text/html"},
    /*Images*/
    {(char*)".gif", (char*)"image/gif"},
    {(char*)".png", (char*)"image/png"},
    {(char*)".bmp", (char*)"application/x-MS-bmp"},
    {(char*)".jpz", (char*)"image/jpeg"},
    {(char*)".jpe", (char*)"image/jpeg"},
    {(char*)".jpeg", (char*)"image/jpeg"},
    {(char*)".jpg", (char*)"image/jpeg"},
    /*Audio&Video*/
    {(char*)".wav", (char*)"audio/wav"},
    {(char*)".wma", (char*)"audio/x-ms-wma"},
    {(char*)".wmv", (char*)"audio/x-ms-wmv"},
    {(char*)".snd", (char*)"audio/basic"},
    {(char*)".au", (char*)"audio/basic"},
    {(char*)".mid", (char*)"audio/midi"},
    {(char*)".midi", (char*)"audio/midi"},
    {(char*)".mp2", (char*)"audio/x-mpeg"},
    {(char*)".mp3", (char*)"audio/x-mpeg"},
    {(char*)".rmm", (char*)"audio/x-pn-realaudio"},
    {(char*)".rmvb", (char*)"audio/x-pn-realaudio"},
    {(char*)".rm", (char*)"audio/x-pn-realaudio"},
    {(char*)".avi", (char*)"video/x-msvideo"},
    {(char*)".3gp", (char*)"video/3gpp"},
    {(char*)".mov", (char*)"video/quicktime"},
    {(char*)".wmx", (char*)"video/x-ms-wmx"},
    {(char*)".asx", (char*)"video/x-ms-asf"},
    {(char*)".asf", (char*)"video/x-ms-asf"},
    {(char*)".mpg4", (char*)"video/mp4"},
    {(char*)".mp4", (char*)"video/mp4"},
    {(char*)".mpga", (char*)"video/mpeg"},
    {(char*)".mpg", (char*)"video/mpeg"},
    {(char*)".mpeg", (char*)"video/mpeg"},
    {(char*)".mpe", (char*)"video/mpeg"},
    /*Documents*/
    {(char*)".pdf", (char*)"application/pdf"},
    {(char*)".rtf", (char*)"application/rtf"},
    {(char*)".dot", (char*)"application/msword"},
    {(char*)".doc", (char*)"application/msword"},
    {(char*)".xla", (char*)"application/msexcel"},
    {(char*)".xls", (char*)"application/msexcel"},
    {(char*)".chm", (char*)"application/mshelp"},
    {(char*)".hlp", (char*)"application/mshelp"},
    {(char*)".cab", (char*)"application/x-shockwave-flash"},
    {(char*)".swfl", (char*)"application/x-shockwave-flash"},
    {(char*)".swf", (char*)"application/x-shockwave-flash"},
    {(char*)".pot", (char*)"application/mspowerpoint"},
    {(char*)".pps", (char*)"application/mspowerpoint"},
    {(char*)".ppz", (char*)"application/mspowerpoint"},
    {(char*)".ppt", (char*)"application/mspowerpoint"},
    /*Binary&Packages*/

    {(char*)".zip", (char*)"application/zip"},
    {(char*)".rar", (char*)"application/x-rar-compressed"},
    {(char*)".gz", (char*)"application/x-gzip"},
    {(char*)".jar", (char*)"application/java-archive"},
    {(char*)".tar", (char*)"application/x-tar"},
    {(char*)".tgz", (char*)"application/x-tar"},

    {(char*)".json",(char*)"application/json"},
    //end of array
    {NULL,NULL},
};


struct ContentType{
    public:
        static char* getfilename(char* path,char* filename);
        static char* gettype(char* filename,char* type);
        static char* getpostfix(char* path,char* postfix);
    private:
        static mimetype* table ;
    protected:
};


#ifdef __cplusplus
}
#endif

#endif // end of file