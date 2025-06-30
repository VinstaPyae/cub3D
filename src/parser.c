#include "cub3D.h"

/*
 * Helper function to find the next newline character or end of string
 */

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
