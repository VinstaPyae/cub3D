#include "cub3D.h"

int	check_file_extension(char *filename)
{
	char	*dot;

	if (!filename)
		return (0);
	dot = ft_strrchr(filename, '.');
	if (!dot)
		return (0);
	return (ft_strncmp(dot, ".cub", 5) == 0);
}

void read_and_print_file(int fd)
{
    char *line = malloc(10000);  // Temporary large buffer
    if (!line)
    {
        ft_putstr_fd("Error\nMemory allocation failed\n", 2);
        exit(1);
    }
    int i = 0;
    char buf[1];
    int byts;

    while ((byts = read(fd, buf, BUFFER_SIZE)) > 0)
    {
        if (buf[0] == '\n')
        {
            line[i] = '\0';
            write(1, line, i);     // Print the line
            write(1, "\n", 1);     // Add newline
            i = 0;                 // Reset for next line
        }
        else
            line[i++] = buf[0];
    }
    if (i > 0) // Last line if not ending in '\n'
    {
        line[i] = '\0';
        write(1, line, i);
        write(1, "\n", 1);
    }
    free(line);
}


int	main(int ac, char *av[])
{
	int	fd;
	if (ac != 2)
		return (ft_putstr_fd("Error\nUsage: ./cub3D <file.cub>\n", 2), 1);
	if (!check_file_extension(av[1]))
		return (ft_putstr_fd("Error\nUsage: ./cub3D <file.cub>\n", 2), 1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\nFailed to open file\n"), 1);
	read_and_print_file(fd);
	close(fd);
	return (0);
}
