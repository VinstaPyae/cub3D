#ifndef UTILS_H
# define UTILS_H

# include "parser.h"

int starts_with(const char *str, const char *prefix);
void	ft_free_strs(char **strs);
void    ft_clean_up(t_config *cfg);

#endif