/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:48:47 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/10 13:47:22 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	builtin_redirector(t_parser *node, char **cmd, t_info *info)
{
	if (!ft_strcmp(cmd[0], "echo") || !ft_strcmp(cmd[0], "cd")
		|| !ft_strcmp(cmd[0], "pwd") || !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "env") || !ft_strcmp(cmd[0], "unset\0")
		|| !ft_strcmp(cmd[0], "exit\0"))
	{
		ft_redirector(node, info);
		ft_builtin(node, cmd, info);
		ft_redirector_back(info);
		return (true);
	}
	return (false);
}

void	ft_builtin(t_parser *parser_node, char **cmd, t_info *info)
{
	if ((ft_strcmp(cmd[0], "echo") == 0))
		ft_echo(parser_node, info);
	else if ((ft_strcmp(cmd[0], "cd") == 0))
		ft_cd(parser_node, info);
	else if ((ft_strcmp(cmd[0], "pwd") == 0))
		ft_pwd(info);
	else if ((ft_strcmp(cmd[0], "export") == 0))
		ft_export(parser_node, info);
	else if ((ft_strcmp(cmd[0], "env") == 0))
		ft_env(parser_node, info);
	else if ((ft_strcmp(cmd[0], "unset\0") == 0))
		ft_unset(parser_node, info);
	else if ((ft_strcmp(cmd[0], "exit\0") == 0))
		ft_exit(cmd, info);
}

char	*get_useful_path(char *cmd, t_env *env_root)
{
	t_env	*tmp;
	char	**paths;
	char	*path;
	int		i;
	char	*tmp_str;

	tmp = env_root;
	while (ft_strcmp(tmp->name, "PATH") != 0)
		tmp = tmp->next;
	paths = ft_split(tmp->value, ':');
	i = -1;
	while (paths[++i])
	{
		tmp_str = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp_str, cmd);
		free(tmp_str);
		if (access(path, X_OK) == 0)
		{
			ft_free(paths);
			return (path);
		}
		free(path);
	}
	ft_free(paths);
	return (NULL);
}

static void	execute_process(t_info *info, t_parser *parser)
{
	char	*path;

	if (parser->pipe)
		config_pipes(parser, 0, info);
	if (!parser->cmd[0])
		return ;
	g_signals.builtin = builtin_redirector(parser, parser->cmd, info);
	if (g_signals.builtin == false && !ft_check_paths(info->env_root))
	{
		ft_printf("%s: No such file or directory\n", parser->cmd[0]);
		return ;
	}
	if (g_signals.builtin == false)
	{
		if (ft_isalnum(parser->cmd[0][0]) != 0)
			path = get_useful_path(parser->cmd[0], info->env_root);
		else
			path = ft_strdup(parser->cmd[0]);
		ft_non_builtin(info, parser, path);
		free(path);
	}
}

void	ft_executer(t_info *info)
{
	t_parser	*parser_tmp;

	parser_tmp = info->utils->parser_root;
	while (parser_tmp)
	{
		ft_extend_and_quotes(parser_tmp->cmd, info);
		if (info->error)
			break ;
		execute_process(info, parser_tmp);
		parser_tmp = parser_tmp->next;
	}
}
