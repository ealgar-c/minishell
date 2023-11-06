/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:13:34 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/06 17:26:35 by ealgar-c         ###   ########.fr       */
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

static void	ft_change_pwd_env(t_info *info)
{
	char	*to_send;
	char	*path;

	path = malloc(sizeof(char) * 100);
	path = getcwd(path, 100);
	to_send = ft_strjoin("PWD=", path);
	save_variable(to_send, info);
	free(to_send);
	free(path);
}

static void	ft_change_oldpwd_env(t_info *info)
{
	char	*to_send;
	char	*path;

	path = malloc(sizeof(char) * 100);
	path = getcwd(path, 100);
	to_send = ft_strjoin("OLDPWD=", path);
	save_variable(to_send, info);
	free(to_send);
	free(path);
}

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

void	ft_cd(t_parser *parser_node, t_info *info)
{
	char	*path;

	info->exit_status = 1;
	if (!parser_node->cmd[1])
	{
		if (ft_check_home(info))
			path = ft_strdup(get_env(ft_strdup("HOME"), info));
		else
		{
			ft_printf("cd: HOME not set\n");
			return ;
		}
	}
	else if (parser_node->cmd[1][ft_strlen(parser_node->cmd[1]) - 1] == ' ')
		path = ft_strtrim(parser_node->cmd[1], "    ");
	else
		path = ft_strdup(parser_node->cmd[1]);
	ft_change_oldpwd_env(info);
	if (chdir((const char *)(path)) == -1)
		ft_check_cd_error(path);
	else
		info->exit_status = 0;
	ft_change_pwd_env(info);
	free(path);
}
