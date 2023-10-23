/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:02:45 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/23 18:42:35 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	c_process(t_info *info, char **cmd, char *path)
{
	char	**envp;

	envp = env_to_array(info);
	ft_extend_and_quotes(cmd, info);
	info ->exit_status = execve(path, cmd, envp);
	ft_free(envp);
	if (info->exit_status == -1)
	{
		ft_printf("%s: command not found\n", cmd[0]);
		info->exit_status = 127;
		exit(0);
	}
}

static void	execute_process(t_info *info, t_parser *parser)
{
	char	*path;
	pid_t	pid;
	int		status;

	if (ft_isalnum(parser->cmd[0][0]) != 0)
		path = get_useful_path(parser->cmd[0], info->env_root);
	else
		path = ft_strdup(parser->cmd[0]);
	if (ft_filter(parser, parser->cmd, info) == false)
	{
		pid = fork();
		if (pid == -1)
			exit(0);
		else if (pid == 0)
			c_process(info, parser->cmd, path);
		else
			waitpid(-1, &status, 0);
	}
	free(path);
}

void	ft_pipex(t_parser *first_node, t_info *info)
{
	int			pid;
	int			fd[2];
	t_parser	*tmp;

	tmp = first_node;
	while (tmp->pipe)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			puts("soy el hijo");
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			execute_process(info, tmp);
			exit(0);
		}
		else
		{
			puts("soy el padre");
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			waitpid(-1, NULL, 0);
		}
		tmp = tmp->next;
	}
}
