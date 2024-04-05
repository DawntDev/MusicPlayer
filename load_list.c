#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <dirent.h>
#include <regex.h>

char *join_path(char *destination, char *file)
{
    int len = strlen(destination) + strlen(file) + 2;
    char *buffer = (char *)malloc(len * sizeof(char));

    strcpy(buffer, destination);
    strcat(buffer, "\\");
    strcat(buffer, file);

    return buffer;
};

int is_album(char *name)
{
    return strcmp("..", name) != 0 && strcmp(".", name) != 0;
};

int is_music(char *name)
{
    regex_t re;
    if (regcomp(&re, "\\.(mp3|wav|flac|m4a)$", REG_EXTENDED) != 0)
        return 0;

    return regexec(&re, name, 0, 0, 0) == 0;
};

Node *load_songs(char *path)
{
    Node *head = NULL;
    Node *last;

    DIR *dp;
    struct dirent *ep;

    dp = opendir(path);
    if (dp != NULL)
    {
        while ((ep = readdir(dp)) != NULL)
        {
            if (is_music(ep->d_name))
            {
                Node *song = (Node *)malloc(sizeof(Node));

                song->name = malloc(strlen(ep->d_name) + 1);
                strcpy(song->name, ep->d_name);

                char *song_path = join_path(path, ep->d_name);
                song->path = malloc(strlen(song_path) + 1);
                strcpy(song->path, song_path);

                if (head == NULL)
                {
                    // Primer nodo
                    song->prev = NULL;
                    head = song;
                    last = head;
                }
                else
                {
                    // Enlazar el ultimo nodo con el nuevo nodo
                    song->prev = last;
                    last->next = song;
                    last = last->next;
                };
            };
        };

        last->next = NULL;
        closedir(dp);
        return head;
    };

    return NULL;
};

Album *load_albums(char *path)
{
    Album *head = NULL;
    Album *last;

    DIR *dp;
    struct dirent *ep;

    dp = opendir(path);
    if (dp != NULL)
    {
        while ((ep = readdir(dp)) != NULL)
        {
            if (is_album(ep->d_name))
            {
                Album *album = (Album *)malloc(sizeof(Album));
                album->name = malloc(strlen(ep->d_name) + 1);
                strcpy(album->name, ep->d_name);

                album->head = load_songs(join_path(path, ep->d_name));

                if (head == NULL)
                {
                    // Primer nodo
                    head = album;
                    last = head;
                }
                else
                {
                    // Enlazar el ultimo nodo con el nuevo nodo
                    last->next = album;
                    last = last->next;
                };
            };
        };

        last->next = NULL;
        closedir(dp);
        return head;
    }
    else
    {
        printf("\nMusic Folder not found ❌");
        return NULL;
    }
};
