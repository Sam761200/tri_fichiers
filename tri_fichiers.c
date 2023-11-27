#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_FILES 100
#define MAX_FILENAME_LEN 256

int compare(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

int main()
{
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile("*", &findFileData);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        printf("Could not open current directory");
        return 0;
    }

    char *filenames[MAX_FILES];
    int count = 0;

    do
    {
        if (count >= MAX_FILES)
            break;
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            filenames[count] = strdup(findFileData.cFileName);
            count++;
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);

    qsort(filenames, count, sizeof(char *), compare);

    printf("Fichiers triés :\n");
    for (int i = 0; i < count; i++)
    {
        printf("%s\n", filenames[i]);
        free(filenames[i]);
    }

    return 0;
}
