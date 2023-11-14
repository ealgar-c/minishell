/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:13:34 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/14 13:44:56 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	ft_check_home(t_info *info)
{
	t_env	*tmp_env;

	tmp_env = info->env_root;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->name, "HOME") == 0)
			return (true);
		tmp_env = tmp_env->next;
	}
	return (false);
}

static char	*get_path(t_parser *parser_node, t_info *info)
{
	char	*path;

	if (!parser_node->cmd[1])
	{
		if (ft_check_home(info))
			path = get_env(ft_strdup("HOME"), info);
		else
		{
			ft_printf("\033[0;33m cd: HOME not set\n\033[0m");
			return (NULL);
		}
	}
	else if (ft_strcmp(parser_node->cmd[1], "-") == 0)
	{
		path = get_env(ft_strdup("OLDPWD"), info);
		ft_printf("%s\n", path);
	}
	else
		path = ft_strdup(parser_node->cmd[1]);
	return (path);
}

void	ft_cd(t_parser *parser_node, t_info *info)
{
	char	*path;

	info->exit_status = 1;
	path = get_path(parser_node, info);
	if (!path)
		return ;
	ft_change_oldpwd_env(info);
	if (chdir((const char *)(path)) == -1)
		ft_check_cd_error(path);
	else
		info->exit_status = 0;
	ft_change_pwd_env(info);
	free(path);
}
