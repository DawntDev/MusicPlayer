#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "structures.h"
#include "load_list.c"
#include "methods.c"

void input(char *buffer, int length)
{
    scanf(" ");                   // Cleaning  the buffer
    fgets(buffer, length, stdin); // Getting input of user

    if ((strlen(buffer) > 0) && (buffer[strlen(buffer) - 1] == '\n'))
        buffer[strlen(buffer) - 1] = '\0'; // Cleaning line break
};

int main()
{
    char *music_path = (char *)malloc(100 * sizeof(char));

    printf("📁 Enter the address of your music folder: ");
    input(music_path, 100);

    printf("\nLoading albums... 🔃");
    Album *albums = load_albums(music_path);
    free(music_path);
    
    if (albums == NULL)
    {
        printf("\nLoading albums... ❌\nError loading your albums.");
        return 1;
    };
    printf("\nLoading albums... ✅\nAlbums loaded.");

    while (1)
    {
        int album;
        printf("\n\nPlease select an album");
        show_albums(*albums);
        printf("\n> ");
        scanf("%d", &album);

        Album *selected = albums;
        for (int i = 0; i < album; i++)
            selected = selected->next;

                Node *song = selected->head;
        int option = 0;
        while (option != 3)
        {
            play_song(song->path);
            printf("\033[H\033[J");
            printf("\x1b[1;30m%s\x1b[0m", selected->name);
            printf("\n\x1b[0;33mPlaying:\x1b[0m %s", song->name);
            printf("\n[1] Prev song\n[2] Next Song\n[3] Change List\n> ");
            scanf("%d", &option);

            switch (option)
            {
            case 1:
                if (song->prev != NULL)
                    song = song->prev;
                break;
            case 2:
                if (song->next != NULL)
                    song = song->next;
                break;
            case 3:
                terminate();
                break;
            default:
                break;
            };
        };
    };
};