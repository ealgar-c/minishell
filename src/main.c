/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:02:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/08 16:18:11 by ealgar-c         ###   ########.fr       */
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

void	ft_printlx(t_lexer *root)
{
	t_lexer *tmp = root;
	int		i = 0;

	while (tmp)
	{
		ft_printf("node %i\n", i);
		ft_printf("cont: %s\n", tmp->content);
		ft_printf("token: %i\n", tmp->token);
		ft_printf("\n");
		tmp = tmp->next;
		i++;
	}
}

void	ft_printparser(t_parser *root)
{
	t_parser *tmp = root;
	int		i = 0;

		ft_printf("\n");
		ft_printf("PARSER:\n");
		ft_printf("\n");
	while (tmp)
	{
		ft_printf("node %i\n", i);
		ft_printf("cont: %s\n", tmp->cmd);
		ft_printf("redir in: %i\n", tmp->redir_in);
		ft_printf("redir out: %i\n", tmp->redir_in);
		if (tmp->pipe)
			ft_printf("is pipe\n");
		ft_printf("\n");
		tmp = tmp->next;
		i++;
	}
}

void	do_stuff(char *str, t_info *info)
{
	if (!str)
		ft_exit(ft_split("exit", ' '), info);
	else if (!(ft_strncmp(str, "\0", 1) == 0))
	{
		info->utils = ft_utils_init();
		ft_lexer(str, info);
		ft_printlx(info->utils->lexer_root);
		ft_parser(info);
		ft_printparser(info->utils->parser_root);
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

// test cmd: cat Makefile | wc -l >outfile