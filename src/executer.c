/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:48:47 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/08 16:15:48 by ealgar-c         ###   ########.fr       */
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
	/* else if ((ft_strncmp(cmd[0], "export", 6) == 0))
		ft_export(cmd);
	else if ((ft_strncmp(cmd[0], "unset", 5) == 0))
		ft_unset(cmd);
	else if ((ft_strncmp(cmd[0], "env", 3) == 0))
		ft_env(cmd); */
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

static char	*get_useful_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**all_paths;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	all_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		path = ft_strjoin(ft_strjoin(all_paths[i], "/"), cmd);
		if (access(path, X_OK) == 0)
		{	
			ft_free(all_paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free(all_paths);
	return (NULL);
}

static void	c_process(t_parser *prsr_node, t_info *info, char **cmd, char *path)
{
	ft_redirector(prsr_node);
	info ->last_exit = execve(path, cmd, info->envp);
	if (info->last_exit == -1)
	{
		ft_printf("%s: command not found\n", cmd[0]);
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
	path = get_useful_path(cmd[0], info->envp);
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
