/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:02:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/05 15:35:09 by ealgar-c         ###   ########.fr       */
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

void	do_stuff(char *str, t_info *info)
{
	if (!str)
		ft_exit(ft_split("exit", ' '), info);
	else if (!(ft_strncmp(str, "\0", 1) == 0))
	{
		info->utils = ft_utils_init();
		ft_lexer(str, info);
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
