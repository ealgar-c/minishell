/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:48:47 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/29 12:59:15 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			return (path);
		free(path);
		i++;
	}
	i = 0;
	while (all_paths[i])
		free(all_paths[i++]);
	free(all_paths);
	return (NULL);
}

void	child_process(t_parser *prsr_node, char **envp, char **cmd, char *path)
{
	dup2(prsr_node->redir_in, STDIN_FILENO);
	dup2(prsr_node->redir_out, STDOUT_FILENO);
	if (execve(path, cmd, envp) == -1)
		ft_printf("%s: command not found\n", cmd[0]);
}

void	execute_process(t_parser *parser_node, char **envp)
{
	char	*path;
	char	**cmd;
	pid_t	pid;
	int		status;

	cmd = ft_split(parser_node->cmd, ' ');
	path = get_useful_path(cmd[0], envp);
	if (ft_filter(parser_node, cmd) == false)
	{
		pid = fork();
		if (pid == -1)
			exit(0);
		else if (pid == 0)
			child_process(parser_node, envp, cmd, path);
		else
			waitpid(-1, &status, 0);
	}
}

void	executer(t_ast_utils *utils, char **envp)
{
	t_parser	*parser_tmp;

	parser_tmp = utils->parser_root;
	while (parser_tmp)
	{
		if (parser_tmp->pipe)
			ft_printf("toy chiquito no se hacer pipes\n");
		else
			execute_process(parser_tmp, envp);
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
