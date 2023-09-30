/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:24:18 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/30 16:11:48 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	check_quotes(char *str)
{	
	if ((str[0] == '"' && str[ft_strlen(str) - 1] != '"')
		|| (str[0] != '"' && str[ft_strlen(str) - 1] == '"'))
		return (false);
	return (true);
}

static void	child_creator(t_parser *parser_node, char *str, bool nl_flag)
{
	pid_t	pid;
	int		status;

	if (str[0] == '"' && str[ft_strlen(str) - 1] == '"')
		str = ft_substr(str, 1, ft_strlen(str) - 2);
	pid = fork();
	if (pid == -1)
		exit (0);
	else if (pid == 0)
	{
		ft_redirector(parser_node);
		ft_printf("%s", str);
		if (nl_flag == true)
			ft_printf("\n");
		exit(0);
	}
	else
		waitpid(-1, &status, 0);
}

void	ft_echo(t_parser *parser_node)
{
	int		i;
	char	*tmp;
	char	**cmd;

	cmd = ft_split(parser_node->cmd, ' ');
	i = 1;
	if (!ft_strncmp(cmd[i], "-n\0", 3))
		i++;
	tmp = cmd[i];
	while (cmd[++i])
		tmp = ft_strjoin(ft_strjoin(tmp, " "), cmd[i]);
	if (check_quotes(tmp))
	{
		if (ft_strncmp(cmd[1], "-n\0", 3))
			child_creator(parser_node, tmp, true);
		else
			child_creator(parser_node, tmp, false);
	}
	free(tmp);
	return ;
}
