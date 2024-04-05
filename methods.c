#ifdef _WIN32
#include <windows.h>
#define PROCCESS "./bin/ffplay.exe -nodisp -hide_banner -loglevel error "

STARTUPINFO si;
PROCESS_INFORMATION pi;

void play_song(char *path)
{
    char *cmd = (char *)malloc(sizeof(PROCCESS) + sizeof(path) + 3);
    strcpy(cmd, PROCCESS);
    strcat(cmd, "\"");
    strcat(cmd, path); // Asegúrate de que path tenga comillas alrededor
    strcat(cmd, "\"");

    Sleep(1000);
    if (pi.hProcess != NULL && pi.hThread != NULL)
    {
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    };


    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        fprintf(stderr, "Error al ejecutar el comando: %d\n", GetLastError());
    }
    
    // free(cmd);
};

void terminate()
{
    if (pi.hProcess != NULL && pi.hThread != NULL)
    {
        TerminateProcess(pi.hProcess, 0);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    };
};

#endif

#ifdef __linux__
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int play_song(char *path)
{
    char *command = (char *)malloc(sizeof("./bin/ffplay.exe -nodisp ") + sizeof(path) + sizeof(char));
    strcpy(command, ".\\bin\\ffplay.exe -nodisp ");
    strcat(command, path);

    return execl("./", command, NULL);
};
#endif

void show_albums(Album albums)
{
    int i = 0;
    while (albums.next != NULL)
    {
        printf("\n[%d] %s", i, albums.name);
        albums = *(albums.next);
        i++;
    };

    printf("\n[%d] %s", i, albums.name);
};