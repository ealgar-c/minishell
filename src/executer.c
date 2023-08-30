/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:48:47 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/08/30 13:27:22 by ealgar-c         ###   ########.fr       */
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

void	execute_process(char **cmd, char **envp)
{
	char	*path;
	//char	**cmd_splitted;
	int		i;

	i = 0;
	//cmd_splitted = ft_split(cmd, ' ');
	path = get_useful_path(cmd[0], envp);
	execve(path, cmd, envp);
}

void	executer(char **cmd, char **envp)
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
}
