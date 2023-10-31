/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:02:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/31 14:13:52 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	ctrlc_handler(int sign)
{
	(void)sign;
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
	write(1, "\033[K\n", 5);
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line("", 0);
} */

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
	int		j;

	ft_printf("\n");
	ft_printf("PARSER:\n");
	ft_printf("\n");
	while (tmp)
	{
		ft_printf("node %i\n", i);
		j = 0;
		while (tmp->cmd[j])
		{
			ft_printf("cont %i: %s\n", j, tmp->cmd[j]);
			j++;
		}
		ft_printf("redir in: %i\n", tmp->redir_in);
		ft_printf("redir out: %i\n", tmp->redir_out);
		if (tmp->pipe)
			ft_printf("is pipe\n");
		ft_printf("\n");
		tmp = tmp->next;
		i++;
	}
}

void	do_stuff(char *str, t_info *info)
{
	info->utils = ft_utils_init(info);
	if (!str)
		ft_exit(ft_split("exit", ' '), info);
	else if (!(ft_strncmp(str, "\0", 1) == 0))
	{
		ft_lexer(str, info);
		if (!g_signals.error)
			ft_parser(info);
		if (!g_signals.error)
			ft_executer(info);
		if (!g_signals.error)
			ft_free_utils(info, false);
	}
}
// LA FUNCION DE ABAJO SOLO SIRVE CON EL MAIN DE DEBUGGEO
void	shownodes(char *str, t_info *info)
{
	info->utils = ft_utils_init(info);
	if (!str || ft_strcmp(str, "exit") == 0)
		ft_exit(ft_split("exit", ' '), info);
	else if (!(ft_strncmp(str, "\0", 1) == 0))
	{
		ft_lexer(str, info);
		if (g_signals.error)
		{
	//		ft_free_utils(info, false);
			return ;
		}
		ft_parser(info);
		ft_printlx(info->utils->lexer_root);
		ft_printparser(info->utils->parser_root);
		ft_free_utils(info, false);
	}
}

t_info	*ft_init_info(char **envp)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->env_root = save_envp(envp);
	info->exit_status = 0;
	return (info);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_info	*info;
	int		mode;

	(void)argc;
	if (argv[1] && ft_strcmp(argv[1], "-n") == 0)
		mode = 1;
	else
		mode = 0;
	signal(SIGINT, ctrlc_handler);
	signal(SIGQUIT, SIG_IGN);
	info = ft_init_info(envp);
	g_signals.heredoc = false;
	g_signals.builtin = true;
	while (1)
	{
		str = readline("\033[0;32mconchita$ \033[0m");
		if (mode == 0)
			do_stuff(str, info);
		else if (mode == 1)
			shownodes(str, info);
		add_history(str);
		free(str);
	}
	return (0);
}

// EL MAIN DE ABAJO ES EL ORIGINAL
/* 
int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_info	*info;
	int		mode;

	 if (argc != 1 || argv[1])
		exit(0); 
	signal(SIGINT, ctrlc_handler);
	signal(SIGQUIT, SIG_IGN);
	info = ft_init_info(envp);
	g_signals.heredoc = false;
	while (1)
	{
		str = readline("\033[0;32mconchita$ \033[0m");
		do_stuff(str, info);
		add_history(str);
		free(str);
	}
	return (0);
}

// test cmd: cat Makefile | wc -l >outfile
 */