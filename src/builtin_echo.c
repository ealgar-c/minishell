/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:24:18 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/19 13:24:53 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*clean_quotes(char *str)
{
	char	*clean;

	if (str[0] == 34 || str[0] == 39)
	{
		clean = ft_substr(str, 1, ft_strlen(str) - 2);
		return (clean);
	}
	return (str);
}

/* char	*clean_quotes(char *content)
{
	return (ft_strtrim(content, "\"\'"));
} */

static void	child_creator(t_parser *parser_node, char *str, bool nl_flag)
{
	pid_t	pid;
	int		status;

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

void	ft_echo(t_parser *parser_node, t_info *info)
{
	int		i;
	char	*tmp;
	char	**cmd;

	cmd = parser_node->cmd;
	i = 1;
	if (!ft_strcmp(cmd[i], "-n"))
		i++;
	tmp = cmd[i];
	while (cmd[++i])
		tmp = ft_strjoin(ft_strjoin(tmp, " "), clean_quotes(cmd[i]));
	if (ft_strcmp(cmd[1], "-n\0"))
		child_creator(parser_node, tmp, true);
	else
		child_creator(parser_node, tmp, false);
	info->exit_status = 0;
	free(tmp);
}
