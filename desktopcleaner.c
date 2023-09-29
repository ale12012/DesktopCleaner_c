#include <stdio.h>
#include <stdlib.h>
#include <fileapi.h>
#include <string.h>
#include <dirent.h>
#include <windows.h>
#include <errhandlingapi.h>


char* getProgramFilesPath()
{
    // Returns the location of the programfies environment variable
    // @ param: NONE
    // @ return: char* path
    char* path = getenv("programfiles");
    return path;
}

char* getDesktopPath()
{
    // Returns the location of the desktop environment variable
    // @ param: NONE
    // @ return: char* path
    char* path = malloc(255 * sizeof(char));
    strcpy(path, getenv("userprofile"));
    strcat(path, "\\Desktop");
    return path;
}

int setAttribHidden(char* file)
{
    // Sets the file attribute to hidden
    // @ param: char* file
    // @ return: int
    int result = SetFileAttributes(file, FILE_ATTRIBUTE_HIDDEN);
    if (result == 0)
    {
        printf("Error: %d\n", GetLastError());
        return 0;
    }
    else
    {
        return 1;
    }
}

int removeAttribHidden(char* file)
{
    // Removes the file attribute to hidden
    // @ param: char* file
    // @ return: int
    int result = SetFileAttributes(file, FILE_ATTRIBUTE_NORMAL);
    if (result == 0)
    {
        printf("Error: %d\n", GetLastError());
        return 0;
    }
    else
    {
        return 1;
    }
}

char* getStatus() 
{
    // Returns the status of the program
    // @ param: NONE
    // @ return: char* 
    char* statusFile = malloc(255 * sizeof(char));
    strcpy(statusFile, getProgramFilesPath());
    strcat(statusFile, "\\desktopcleaner_c\\status.txt");
    FILE* statusFiles = fopen(statusFile, "r");
    char* status = malloc(10 * sizeof(char));
    if (statusFiles == NULL)
    {
        printf("Error opening file\n");
        return NULL;
    }
    else
    {
        fgets(status, 10, statusFiles);
        fclose(statusFiles);
        return status;
    }
}

void changeStatus()
{
    //
    // Changes the status in the status file.
    // Used for the program to know wheter to set or remove the hidden attribute
    // @param NONE
    // @return NONE
    //
    char* statusPath = malloc(255 * sizeof(char));
    strcpy(statusPath, getProgramFilesPath());
    strcat(statusPath, "\\desktopcleaner_c\\status.txt");
    FILE* statusFile = fopen(statusPath, "r");
    char* status = getStatus();
    if (strcmp(status, "0") == 0)
    {
        statusFile = fopen(statusPath, "w");
        fprintf(statusFile, "1");
        fclose(statusFile);
    }
    if (strcmp(status, "1") == 0)
    {
        statusFile = fopen(statusPath, "w");
        fprintf(statusFile, "0");
        fclose(statusFile);
    }
}
void logFiles()
{
    // Logs the files in the desktop to a file
    // @ param: NONE
    // @ return: Void
    char* desktopPath = malloc(255 * sizeof(char));
    strcpy(desktopPath, getDesktopPath());
    strcat(desktopPath, "\\");
    char* logPath = malloc(255 * sizeof(char));
    strcpy(logPath, getProgramFilesPath());
    strcat(logPath, "\\desktopcleaner_c\\files.txt");
    FILE* logFile = fopen(logPath, "w");
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(desktopPath)) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            {
                continue;
            }
            else
            {
                fprintf(logFile, "%s\n", ent->d_name);
            }
        }
        fclose(logFile);
        closedir(dir);
    }
    else
    {
        printf("Error opening directory\n");
    }
}

char** getFiles()
{
    // Returns a list of files in the desktop
    // @ param: NONE
    // @ return: char** files
    char* logPath = malloc(255 * sizeof(char));
    strcpy(logPath, getProgramFilesPath());
    logPath = strcat(logPath, "\\desktopcleaner_c\\files.txt");
    FILE* logFile = fopen(logPath, "r");
    char line[255];
    char** files = malloc(100 * sizeof(line));
    int i = 0;
     while (fgets(line, 255, logFile) != NULL) {
        files[i] = malloc(255 * sizeof(char));
        strcpy(files[i], line);
        i++;
    }
    fclose(logFile);
    files[i+1] = malloc(2*sizeof(char));
    files[i+1] = "\0";
    return files;
}


int main(int argc, char* argv[])
{

    char** files = getFiles();
    char* s = malloc(10 * sizeof(char));
    strcpy(s, getStatus());
    char* desktopPath = malloc(255 * sizeof(char));
    if (strcmp(s, "0") == 0)
    {
        printf("Setting hidden attribute\n");
        for (int i = 0; i < 100; i++)
        {
            if (files[i] == NULL)
            {
                break;
            }
            else
            {
                strcpy(desktopPath, getDesktopPath());
                strcat(desktopPath, "\\");
                strcat(desktopPath, files[i]);
                for (int j = 0; j < strlen(desktopPath); j++)
                {
                    if (desktopPath[j] == '\n')
                    {
                        desktopPath[j] = '\0';
                    }
                }
                setAttribHidden(desktopPath);
            }
        }
        changeStatus();
        logFiles();
    }
    else
    {
        printf("Removing hidden attribute\n");
        for (int i = 0; i < 100; i++)
        {
            if (files[i] == NULL)
            {
                break;
            }
            else
            {
                strcpy(desktopPath, getDesktopPath());
                strcat(desktopPath, "\\");
                strcat(desktopPath, files[i]);
                for (int j = 0; j < strlen(desktopPath); j++)
                {
                    if (desktopPath[j] == '\n')
                    {
                        desktopPath[j] = '\0';
                    }
                }

                if (strcmp(&desktopPath[0], ".") == 0 || strcmp(&desktopPath[0], "~") == 0 || strcmp(&desktopPath[0], "$") == 0 
                || strstr(desktopPath, ".lnk") != NULL || strstr(desktopPath, ".ini") != NULL)
                {
                    continue;
                }
                removeAttribHidden(desktopPath);
            }
        }
        changeStatus();
    }

}