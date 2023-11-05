/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:48:47 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/05 17:56:17 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char	**ft_prepare_cmd(char **cmd)
{
	char	*line;
	char	**new_cmd;
	int		i;

	i = 0;
	line = cmd[i];
	if (cmd[i][ft_strlen(cmd[i]) - 1] != 32)
		line = ft_strjoin(line, " ");
	while (cmd[++i])
	{
		if (cmd[i][ft_strlen(cmd[i]) - 1] != 32)
			line = ft_strjoin(line, " ");
		line = ft_strjoin(line, cmd[i]);
	}
	new_cmd = ft_split(line, ' ');
	free(line);
	return (new_cmd);
}

void	c_process(t_parser *prsr_node, t_info *info, char **cmd, char *path)
{
	char	**envp;
	char	**new_cmd;

	envp = env_to_array(info);
	ft_extend_and_quotes(cmd, info);
	if (prsr_node->pipe)
		config_pipes(prsr_node->next, 2, info);
	if (prsr_node->prev && prsr_node->prev->pipe)
		config_pipes(prsr_node->prev, 1, info);
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

void	ft_non_builtin(t_info *info, t_parser *parser, char *path)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(0);
	else if (pid == 0)
		c_process(parser, info, parser->cmd, path);
	else
	{
		if (parser->pipe)
			config_pipes(parser, 1, info);
		if (parser->prev && parser->prev->pipe)
			config_pipes(parser, 2, info);
		waitpid(-1, &info->exit_status, 0);
		if (WIFEXITED(info->exit_status))
			info->exit_status = WEXITSTATUS(info->exit_status);
	}
	g_signals.builtin = true;
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