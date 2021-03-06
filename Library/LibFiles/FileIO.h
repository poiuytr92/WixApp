// Simple file I/O using CFile from MFC


#pragma once


class FileIO {
String         path;
uint           openParms;
CFile          cfile;
ULONGLONG      pos;
CFileException err;

char*          pbuf;                // read buffer
char*          ebuf;
char           buf[1024];
bool           rtnSeen;

int            tabSize;
int            col;

public:

enum OpenParms {Read=1, Write=2, Create=4};

  FileIO();
 ~FileIO() {close();}

  bool open(String& filePath, OpenParms parms);
  void close();

  bool reOpen();

  bool isOpen() {return cfile.m_hFile != CFile::hFileNull;}

  bool getModifiedTime(CTime& time);

  bool write(String& s);                            // Writes a string (unicode or ansi)
  bool write(TCchar* s);                            // Writes a string of Tchars (unicod or ansi)
  bool write(Tchar   c);                            // Writes one character (unicode or ansi)
  bool write(void* blk, int n);                     // writes n bytes (not chars or Tchars) without
                                                    // interpretation of /n or /r
  bool write(Byte    v);                            // Writes one byte without interpretation of /n or /r

  bool read(String& s);                             // Reads a line terminated by _T("\n")
  bool read(String& s, int n);                      // Read n characters into a string
  bool read(Tchar&  c);                             // reads on char or wchar (i.e. a Tchar)
  bool read(void* blk, int n);                      // Read block of data from buffer without
                                                    // interpretation of /n or /r
  bool read(Byte&    v);                            // Reads one byte without interpretation of /n or /r

  void setTabSize(int nSpaces)                      // Set Tab Size for output, default is 2 spaces
              {if (nSpaces > 0) tabSize = nSpaces;}
  void tab(   int nTabs);                           // Tab every 2 spaces
  void spaces(int nSpaces);
  void crlf() {write(_T('\n'));}

  Tchar* getLastError();                            // Returns last error

private:

  bool fillBuf();
  void flush();
  void saveExcp(CFileException* e);
  };
