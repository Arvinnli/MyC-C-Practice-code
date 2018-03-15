struct mimetype
{
    char *postfix;
    char *type;
};
//"application/octet-stream"
const static mimetype table[128] = {
    /*Text*/
    {".txt", "text/plain"},
    {".css", "text/css"},
    {".js", "text/javascript"},
    {".xsl", "text/xml"},
    {".xsl", "text/xml"},
    {".xhtm", "text/html"},
    {".xht", "application/xhtml+xml"},
    {".xhtml", "application/xhtml+xml"},
    {".hts", "text/html"},
    {".shtml", "text/html"},
    {".htm", "text/html"},
    {".html", "text/html"},
    /*Images*/
    {".gif", "image/gif"},
    {".png", "image/png"},
    {".bmp", "application/x-MS-bmp"},
    {".jpz", "image/jpeg"},
    {".jpe", "image/jpeg"},
    {".jpeg", "image/jpeg"},
    {".jpg", "image/jpeg"},
    /*Audio&Video*/
    {".wav", "audio/wav"},
    {".wma", "audio/x-ms-wma"},
    {".wmv", "audio/x-ms-wmv"},
    {".snd", "audio/basic"},
    {".au", "audio/basic"},
    {".mid", "audio/midi"},
    {".midi", "audio/midi"},
    {".mp2", "audio/x-mpeg"},
    {".mp3", "audio/x-mpeg"},
    {".rmm", "audio/x-pn-realaudio"},
    {".rmvb", "audio/x-pn-realaudio"},
    {".rm", "audio/x-pn-realaudio"},
    {".avi", "video/x-msvideo"},
    {".3gp", "video/3gpp"},
    {".mov", "video/quicktime"},
    {".wmx", "video/x-ms-wmx"},
    {".asx", "video/x-ms-asf"},
    {".asf", "video/x-ms-asf"},
    {".mpg4", "video/mp4"},
    {".mp4", "video/mp4"},
    {".mpga", "video/mpeg"},
    {".mpg", "video/mpeg"},
    {".mpeg", "video/mpeg"},
    {".mpe", "video/mpeg"},
    /*Documents*/

    {".pdf", "application/pdf"},
    {".rtf", "application/rtf"},
    {".dot", "application/msword"},
    {".doc", "application/msword"},
    {".xla", "application/msexcel"},
    {".xls", "application/msexcel"},
    {".chm", "application/mshelp"},
    {".hlp", "application/mshelp"},
    {".cab", "application/x-shockwave-flash"},
    {".swfl", "application/x-shockwave-flash"},
    {".swf", "application/x-shockwave-flash"},
    {".pot", "application/mspowerpoint"},
    {".pps", "application/mspowerpoint"},
    {".ppz", "application/mspowerpoint"},
    {".ppt", "application/mspowerpoint"},
    /*Binary&Packages*/
    {".zip", "application/zip"},
    {".rar", "application/x-rar-compressed"},
    {".gz", "application/x-gzip"},
    {".jar", "application/java-archive"},
    {".tar", "application/x-tar"},
    {".tgz", "application/x-tar"},

};
