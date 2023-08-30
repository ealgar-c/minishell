/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:02:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/08/30 13:28:51 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_array_len(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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

t_ast	*tree(char *fullcmd)
{
	char	**cmd;
	t_ast	*ast;

	ast = ast_init(fullcmd);
	cmd = ft_split(fullcmd, '|');
	return (ast);
}
void	do_stuff(char *str, char **envp)
{
	t_ast	*ast;
	ast = tree(str);
	(void)envp;
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	atexit(ft_leakss);
	if (argc != 1 || argv[1])
		exit(0);
	while (1)
	{
		str = readline(get_prompt());
		//do_stuff(str, envp);
		ft_filter(ft_split(str, ' '), envp);
		free(str);
	}
	return (0);
}
