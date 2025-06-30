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
static char *allocate_line(size_t len)
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

static void copy_line_content(char *line, char *start, size_t len)
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

static char *get_next_line(char **pos)
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

static char *append_buffer_to_content(char *content, char *buffer)
{
    char *tmp = ft_strjoin(content, buffer);
    if (!tmp)
    {
        free(content);
        perror("Error\nMalloc failed");
        exit(1);
    }
    free(content);
    return tmp;
}

static char *read_whole_file(int fd)
{
    char    buffer[1025];
    char    *content = ft_strdup("");
    ssize_t bytes;

    if (!content)
        perror("Error\nMalloc failed"), exit(1);
    
    while ((bytes = read(fd, buffer, 1024)) > 0)
    {
        buffer[bytes] = '\0';
        content = append_buffer_to_content(content, buffer);
    }
    
    if (bytes < 0)
    {
        free(content);
        perror("Error\nFailed to read file");
        exit(1);
    }
    return (content);
}

static char **allocate_lines_array(size_t line_count)
{
    char **lines = malloc(sizeof(char *) * (line_count + 1));
    if (!lines)
    {
        perror("Error\nMalloc failed");
        exit(1);
    }
    return lines;
}

static void extract_lines(char **lines, char *content, size_t line_count)
{
    char    *pos;
    size_t  i;
    
    i = 0;
    pos  = content;
    while (i < line_count)
    {
        lines[i] = get_next_line(&pos);
        if (!lines[i])
            break;
        i++;
    }
    lines[i] = NULL;  /* NULL terminate the array */
}

char **read_file_lines(int fd)
{
    char    *whole;
    char    **lines;
    size_t  line_count;

    whole = read_whole_file(fd);
    line_count = count_lines(whole);
    lines = allocate_lines_array(line_count);
    
    extract_lines(lines, whole, line_count);
    
    free(whole);
    return (lines);
}
