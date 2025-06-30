#include "cub3D.h"

char *find_next_newline(char *str)
{
    if (!str)
        return (NULL);
    while (*str && *str != '\n')
        str++;
    return (str);
}

char *allocate_line(size_t len)
{
    char *line;
    
    line = malloc(len + 1);
    if (!line)
    {
        perror("Error\nMalloc failed");
        exit(1);
    }
    return line;
}

void copy_line_content(char *line, char *start, size_t len)
{
    size_t i;
    
    i = 0;
    while (i < len)
    {
        line[i] = start[i];
        i++;
    }
    line[i] = '\0';
}

char *get_next_line(char **pos)
{
    char    *start;
    char    *end;
    char    *line;
    size_t  len;

    if (!pos || !*pos || !**pos)
        return (NULL);
    
    start = *pos;
    end = find_next_newline(start);
    
    /* Calculate length of the line (excluding newline) */
    len = end - start;
    
    /* Allocate and fill the line */
    line = allocate_line(len);
    copy_line_content(line, start, len);
    
    /* Update position for next call */
    *pos = (*end == '\n') ? end + 1 : end;
    
    return (line);
}

size_t count_lines(char *content)
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