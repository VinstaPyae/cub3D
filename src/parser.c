#include "cub3D.h"

/*
 * Read the entire contents of fd into one big string.
 * Returns malloc'd buffer, or exits on error.
 */
static char *read_whole_file(int fd)
{
    char    buffer[1025];
    char    *content = ft_strdup("");  /* start with empty string */
    char    *tmp;
    ssize_t bytes;

    if (!content)
        perror("Error\nMalloc failed"), exit(1);

    while ((bytes = read(fd, buffer, 1024)) > 0)
    {
        buffer[bytes] = '\0';
        tmp = ft_strjoin(content, buffer);
        if (!tmp)
        {
            free(content);
            perror("Error\nMalloc failed");
            exit(1);
        }
        free(content);
        content = tmp;
    }
    if (bytes < 0)
    {
        free(content);
        perror("Error\nFailed to read file");
        exit(1);
    }
    return (content);
}

/*
 * Reads all lines from fd and returns an array of strings (NULL-terminated).
 * Exits on any error.
 */
char **read_file_lines(int fd)
{
    char    *whole;
    char    **lines;

    whole = read_whole_file(fd);
    /* ft_split will split on '\n' and produce NULL-terminated array */
    lines = ft_split(whole, '\n');
    free(whole);
    if (!lines)
    {
        perror("Error\nFailed to split file into lines");
        exit(1);
    }
    return (lines);
}
