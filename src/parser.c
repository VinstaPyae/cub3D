#include "cub3D.h"

/*
 * Helper function to find the next newline character or end of string
 */
static char *find_next_newline(char *str)
{
    if (!str)
        return (NULL);
    while (*str && *str != '\n')
        str++;
    return (str);
}

/*
 * Extract one line from the content starting at *pos.
 * Updates *pos to point to the start of the next line.
 * Returns malloc'd string containing the line (without '\n'), or NULL if end.
 */
static char *get_next_line(char **pos)
{
    char    *start;
    char    *end;
    char    *line;
    size_t  len;
    size_t  i;

    if (!pos || !*pos || !**pos)
        return (NULL);
    
    start = *pos;
    end = find_next_newline(start);
    
    /* Calculate length of the line (excluding newline) */
    len = end - start;
    
    /* Allocate memory for the line */
    line = malloc(len + 1);
    if (!line)
    {
        perror("Error\nMalloc failed");
        exit(1);
    }
    
    /* Copy the line content */
    i = 0;
    while (i < len)
    {
        line[i] = start[i];
        i++;
    }
    line[i] = '\0';
    
    /* Update position for next call */
    if (*end == '\n')
        *pos = end + 1;  /* Skip the newline */
    else
        *pos = end;      /* At end of string */
    
    return (line);
}

/*
 * Count the number of lines in the content (including empty lines)
 */
static size_t count_lines(char *content)
{
    size_t  count;
    char    *pos;

    if (!content || !*content)
        return (0);
    
    count = 0;
    pos = content;
    
    while (*pos)
    {
        count++;
        pos = find_next_newline(pos);
        if (*pos == '\n')
            pos++;
        else
            break;
    }
    
    return (count);
}

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
            free(content), perror("Error\nMalloc failed");
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
 * Preserves empty lines, unlike ft_split.
 * Exits on any error.
 */
char **read_file_lines(int fd)
{
    char    *whole;
    char    **lines;
    char    *pos;
    size_t  line_count;
    size_t  i;

    whole = read_whole_file(fd);
    
    /* Count total lines including empty ones */
    line_count = count_lines(whole);
    
    /* Allocate array for line pointers + NULL terminator */
    lines = malloc(sizeof(char *) * (line_count + 1));
    if (!lines)
    {
        free(whole);
        perror("Error\nMalloc failed");
        exit(1);
    }
    
    /* Extract each line using get_next_line */
    pos = whole;
    i = 0;
    while (i < line_count)
    {
        lines[i] = get_next_line(&pos);
        if (!lines[i])
            break;
        i++;
    }
    lines[i] = NULL;  /* NULL terminate the array */
    
    free(whole);
    return (lines);
}