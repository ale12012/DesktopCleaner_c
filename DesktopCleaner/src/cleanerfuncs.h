#ifndef CLEANERFUNCS_H
#define CLEANERFUNCS_H

char* getProgramFilesPath();
char* getDesktopPath();
int setAttribHidden(char* file);
int removeAttribHidden(char* file);
char* getStatus();
void changeStatus();
void logFiles();
char** getFiles();

#endif // CLEANERFUNCS_H