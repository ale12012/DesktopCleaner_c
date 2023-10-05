#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/cleanerfuncs.h"


int main(int argc, char* argv[])
{
    logFiles();
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
                || strstr(desktopPath, ".ini") != NULL)
                {
                    continue;
                }
                removeAttribHidden(desktopPath);
            }
        }
        changeStatus();
    }

}