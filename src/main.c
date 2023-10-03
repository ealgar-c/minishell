/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:02:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/03 15:37:59 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ctrlc_handler(int sign)
{
	(void)sign;
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
	write(1, "\033[K\n", 5);
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
}

t_ast_utils	*ft_init_utils(void)
{
	t_ast_utils	*utils;

	utils = malloc(sizeof(t_ast_utils));
	if (!utils)
		return (NULL);
	utils->pipes = 0;
	utils->lexer_len = 0;
	return (utils);
}

void	do_stuff(char *str, t_info *info)
{
	if (!str)
		ft_exit(ft_split("exit", ' '), info);
	else if (!(ft_strncmp(str, "\0", 1) == 0))
	{
		info->utils = ft_init_utils();
		ft_lexer(ft_split(str, ' '), info);
		ft_parser(info);
		ft_executer(info);
		ft_free_utils(info->utils);
	}
}

t_info	*ft_init_info(char **envp)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->envp = envp;
	info->last_exit = 0;
	return (info);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_info	*info;

	if (argc != 1 || argv[1])
		exit(0);
	signal(SIGINT, ctrlc_handler);
	signal(SIGQUIT, SIG_IGN);
	info = ft_init_info(envp);
	while (1)
	{
		str = readline("conchita$ ");
		do_stuff(str, info);
		add_history(str);
		free(str);
	}
	return (0);
}
