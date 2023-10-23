/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:24:18 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/23 17:34:36 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* char	*clean_quotes(char *content)
{
	return (ft_strtrim(content, "\"\'"));
} */

static void	child_creator(t_parser *parser_node, bool nl_flag, int i)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit (0);
	else if (pid == 0)
	{
		ft_redirector(parser_node);
		while (parser_node->cmd[i])
		{
			ft_printf("%s", parser_node->cmd[i]);
			i++;
		}
		if (nl_flag == true)
			ft_printf("\n");
		exit(0);
	}
	else
		waitpid(-1, &status, 0);
}

void	ft_echo(t_parser *parser_node, t_info *info)
{
	int		i;

	i = 1;
	if (!parser_node->cmd[i])
		return ;
	if (ft_strcmp(parser_node->cmd[i], "-n ") == 0)
		i++;
	if (ft_strcmp(parser_node->cmd[1], "-n " ) != 0)
		child_creator(parser_node, true, i);
	else
		child_creator(parser_node, false, i);
	info->exit_status = 0;
}
