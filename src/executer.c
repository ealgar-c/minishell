/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:48:47 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/04 16:24:28 by erivero-         ###   ########.fr       */
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
	pid_t	pid;

	if (parser->pipe)
		config_pipes(parser, 0);
	if (ft_isalnum(parser->cmd[0][0]) != 0)
		path = get_useful_path(parser->cmd[0], info->env_root);
	else
		path = ft_strdup(parser->cmd[0]);
	g_signals.builtin = builtin_redirector(parser, parser->cmd, info);
	if (g_signals.builtin == false)
	{
		pid = fork();
		if (pid == -1)
			exit(0);
		else if (pid == 0)
			c_process(parser, info, parser->cmd, path);
		else
		{
			if (parser->pipe)
				config_pipes(parser, 1);
			if (parser->prev && parser->prev->pipe)
				config_pipes(parser, 2);
			waitpid(-1, &info->exit_status, 0);
			if (WIFEXITED(info->exit_status))
				info->exit_status = WEXITSTATUS(info->exit_status);
		}
		g_signals.builtin = true;
	}
	free(path);
}

void	ft_executer(t_info *info)
{
	t_parser	*parser_tmp;

	parser_tmp = info->utils->parser_root;
	while (parser_tmp)
	{
		ft_extend_and_quotes(parser_tmp->cmd, info);
		execute_process(info, parser_tmp);
		parser_tmp = parser_tmp->next;
	}
}

/* void	executer(char **cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit(0);
	else if (pid == 0)
		execute_process(cmd, envp);
	else
		waitpid(-1, &status, 0);
} */

// cat Makefile | wc -l