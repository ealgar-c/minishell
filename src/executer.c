/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:48:47 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/02 17:34:48 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	ft_filter(t_parser *parser_node, char **cmd, t_info *info)
{
//	ft_redirector(parser_node);
	if ((ft_strcmp(cmd[0], "echo") == 0))
		ft_echo(parser_node, info);
	else if ((ft_strcmp(cmd[0], "cd") == 0))
		ft_cd(parser_node, info);
	else if ((ft_strcmp(cmd[0], "pwd") == 0))
		ft_pwd(parser_node, info);
	else if ((ft_strcmp(cmd[0], "export") == 0))
		ft_export(parser_node, info);
	else if ((ft_strcmp(cmd[0], "env") == 0))
		ft_env(parser_node, info);
	else if ((ft_strcmp(cmd[0], "unset\0") == 0))
		ft_unset(parser_node, info);
	else if ((ft_strcmp(cmd[0], "exit\0") == 0))
		ft_exit(cmd, info);
	else
		return (false);
	return (true);
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

char	**env_to_array(t_info *info)
{
	int		len;
	t_env	*tmp;
	char	**ret;
	char	*tmp_str;

	len = 0;
	tmp = info->env_root;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	ret = malloc((sizeof(char *) * len) + 1);
	tmp = info->env_root;
	len = 0;
	while (tmp)
	{
		tmp_str = ft_strjoin(tmp->name, "=");
		ret[len] = ft_strjoin(tmp_str, tmp->value);
		free(tmp_str);
		tmp = tmp->next;
		len++;
	}
	ret[len] = NULL;
	return (ret);
}

/* void print_cmd(char **cmd)
{
	int i = 0;
	while (cmd[i])
	{
		ft_printf("cmd[%i]: \'%s\'\n", i, cmd[i]);
		i++;
	}	
} */
char **ft_prepare_cmd(char **cmd)
{
	char	*line;
	char	**new_cmd;
	int		i;

	i = 0;
	line = cmd[i];
	if (cmd[i][ft_strlen(cmd[i]) - 1] != 32) // si no hay espacio al final, lo pone
		line = ft_strjoin(line, " ");
	while(cmd[++i])
	{
		if (cmd[i][ft_strlen(cmd[i]) - 1] != 32) // si no hay espacio al final, lo pone
			line = ft_strjoin(line, " ");
		line = ft_strjoin(line, cmd[i]);
	}
	new_cmd = ft_split(line, ' ');
	free(line);
	return(new_cmd);
}

static void	c_process(t_parser *prsr_node, t_info *info, char **cmd, char *path)
{
	char	**envp;
	char	**new_cmd;

	envp = env_to_array(info);
	ft_extend_and_quotes(cmd, info);
	if (prsr_node->pipe)
		config_pipes(prsr_node->next, 2);
	if (prsr_node->prev && prsr_node->prev->pipe)
		config_pipes(prsr_node->prev, 1);
	ft_redirector(prsr_node, info);
	new_cmd = ft_prepare_cmd(cmd);
	ft_free(cmd);
	info->exit_status = execve(path, new_cmd, envp);
	ft_free(envp);
	if (info->exit_status == -1)
	{
		ft_printf("%s: command not found\n", new_cmd[0]);
		info->exit_status = 127;
	}
	exit(info->exit_status);
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
	g_signals.builtin = ft_filter(parser, parser->cmd, info);
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