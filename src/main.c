/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:02:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/28 16:51:32 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* int	ft_array_len(char **str)
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
} */

void	ft_leakss(void)
{
	system("leaks -q minishell");
}

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

void	do_stuff(char *str, char **envp)
{
	t_lexer	*root;

	if (!str)
		ft_exit(ft_split("exit", ' '));
	else if (!(ft_strncmp(str, "\0", 1) == 0))
	{
		root = ft_lexer(ft_split(str, ' '));
		ft_parser(root->utils);
		executer(root->utils, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	(void)envp;
	if (argc != 1 || argv[1])
		exit(0);
	signal(SIGINT, ctrlc_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		str = readline("conchita$ ");
		do_stuff(str, envp);
		free(str);
	}
	return (0);
}

/* 		t_ast *tree = create_tree(str);
		(void)tree;
		//do_stuff(str, envp); */