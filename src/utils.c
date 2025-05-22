#include "cub3D.h"

int starts_with(const char *str, const char *prefix)
{
    int i = 0;
    while (prefix[i])
    {
        if (str[i] != prefix[i])
            return (0);
        i++;
    }
    return (1);
}
void	ft_free_strs(char **strs)
{
	int	i = 0;

	if (!strs)
		return;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}
