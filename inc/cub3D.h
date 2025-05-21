#ifndef CUB3D_H
# define CUB3D_H

/* buffer size for simple reader */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/* system headers */
# include <unistd.h>   /* read, write, close */
# include <fcntl.h>    /* open flags */
# include <stdlib.h>   /* malloc, free, exit */
# include <stdio.h>    /* perror */
# include "libft.h"    /* your libft functions */

/*
 * Configuration structure: holds all parsed .cub data
 * (we'll fill it out more as you implement parsing)
 */
typedef struct s_config
{
    char    *texture_no;
    char    *texture_so;
    char    *texture_we;
    char    *texture_ea;
    int      floor_color;
    int      ceiling_color;
    char   **map;
    int      map_width;
    int      map_height;
}   t_config;

typedef struct s_file
{
    char **lines;  // Array of strings (each line in the .cub file)
    int count;     // Number of lines
} t_file;

/* Read all lines from fd into a NULL-terminated array; exit on error */
char    **read_file_lines(int fd);


#endif /* CUB3D_H */
