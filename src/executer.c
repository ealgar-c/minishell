/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:48:47 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/09 18:48:19 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	ft_filter(t_parser *parser_node, char **cmd, t_info *info)
{
	if ((ft_strncmp(cmd[0], "echo\0", 5) == 0))
		ft_echo(parser_node, info);
	else if ((ft_strncmp(cmd[0], "cd\0", 3) == 0))
		ft_cd(parser_node, info);
	else if ((ft_strncmp(cmd[0], "pwd\0", 4) == 0))
		ft_pwd(parser_node, info);
	else if ((ft_strncmp(cmd[0], "export", 6) == 0))
		ft_export(parser_node, info);
	else if ((ft_strncmp(cmd[0], "env", 3) == 0))
		ft_env(parser_node, info);
	else if ((ft_strncmp(cmd[0], "exit\0", 5) == 0))
		ft_exit(cmd, info);
	else
		return (false);
	return (true);
}

void	ft_redirector(t_parser *parser_node)
{
	if (parser_node->redir_in != -1)
		dup2(parser_node->redir_in, STDIN_FILENO);
	if (parser_node->redir_out != -1)
		dup2(parser_node->redir_out, STDOUT_FILENO);
}

static char	*get_useful_path(char *cmd, t_env *env_root)
{
	t_env	*tmp;
	char	**paths;
	char	*path;
	int		i;
	char	*tmp_str;

	tmp = env_root;
	while (ft_strncmp(tmp->name, "PATH", 4) != 0)
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

static void	c_process(t_parser *prsr_node, t_info *info, char **cmd, char *path)
{
	char	**envp;

	envp = env_to_array(info);
	ft_redirector(prsr_node);
	info ->exit_status = execve(path, cmd, envp);
	ft_free(envp);
	if (info->exit_status == -1)
	{
		ft_printf("%s: command not found\n", cmd[0]);
		info->exit_status = 127;
		exit(0);
	}
}

static void	execute_process(t_info *info, t_parser *parser_node)
{
	char	*path;
	char	**cmd;
	pid_t	pid;
	int		status;

	cmd = ft_split(parser_node->cmd, ' ');
	if (ft_isalnum(cmd[0][0]) != 0)
		path = get_useful_path(cmd[0], info->env_root);
	else
		path = ft_strdup(cmd[0]);
	if (ft_filter(parser_node, cmd, info) == false)
	{
		pid = fork();
		if (pid == -1)
			exit(0);
		else if (pid == 0)
			c_process(parser_node, info, cmd, path);
		else
			waitpid(-1, &status, 0);
	}
	ft_free(cmd);
	free(path);
}

void	ft_executer(t_info *info)
{
	t_parser	*parser_tmp;

	parser_tmp = info->utils->parser_root;
	while (parser_tmp)
	{
		if (parser_tmp->pipe)
			ft_printf("toy chiquito no se hacer pipes\n");
		else
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
