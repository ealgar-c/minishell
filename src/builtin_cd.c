/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:13:34 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/20 13:27:56 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_check_cd_error(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_printf("cd: %s: No such file or directory\n", path);
	else
		ft_printf("cd: %s: Not a directory\n", path);
	close(fd);
}

void	ft_cd(t_parser *parser_node, t_info *info)
{
	char	*path;
	bool	to_free;

	to_free = false;
	if (!parser_node->cmd[1])
		path = ft_strdup(getenv("HOME"));
	else if (parser_node->cmd[1][ft_strlen(parser_node->cmd[1] - 1)] == ' ')
		path = ft_strtrim(parser_node->cmd[1], "    ");
	else
		path = ft_strdup(parser_node->cmd[1]);
	if (chdir((const char *)(path)) == -1)
	{
		ft_check_cd_error(path);
		info->exit_status = 1;
	}
	else
		info->exit_status = 0;
	free(path);
}
