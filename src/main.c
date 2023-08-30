/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:02:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/08/30 11:51:48 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_free_array(char **str)
{
	char	**ptr;

	if (!str)
		return ;
	ptr = str;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(str);
}

char	*take_usable_path(char *path)
{
	char	**path_split;
	char	*usable_path;
	int		i;

	i = 0;
	path_split = ft_split(path, '/');
	while (path_split[i])
		i++;
	usable_path = path_split[i - 1];
	ft_free_array(path_split);
	return (usable_path);
}

char	*get_prompt(void)
{
	char	*path;
	char	*prompt;
	char	*usable_path;

	path = malloc(sizeof(char) * 100);
	path = getcwd(path, 100);
	usable_path = take_usable_path(path);
	prompt = ft_strjoin(usable_path, ":conchita$ ");
	free(path);
	return (prompt);
}

void	ft_leakss(void)
{
	system("leaks -q minishell");
}

int	main(void)
{
	char	*str;

	atexit(ft_leakss);
	while (1)
	{
		str = readline(get_prompt());
		ft_printf("has dicho: %s\n", str);
		if (ft_strncmp(str, "exit", 4) == 0)
		{
			free(str);
			exit(0);
		}
		free(str);
	}
	return (0);
}
