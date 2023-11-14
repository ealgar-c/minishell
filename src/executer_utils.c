/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:48:47 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/14 13:23:28 by ealgar-c         ###   ########.fr       */
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

void	c_process(t_parser *prsr_node, t_info *info, char **cmd, char *path)
{
	char	**envp;

	envp = env_to_array(info);
	if (info->error)
		return ;
	if (prsr_node->pipe)
		config_pipes(prsr_node->next, 2, info);
	if (prsr_node->prev && prsr_node->prev->pipe)
		config_pipes(prsr_node->prev, 1, info);
	ft_redirector(prsr_node, info);
	info->exit_status = execve(path, cmd, envp);
	ft_free(envp);
	if (info->exit_status == -1)
	{
		ft_redirector_back(info);
		ft_printf("\033[0;33mconchita: %s:\033[0m", cmd[0]);
		ft_printf("\033[0;33m command not found\n\033[0m");
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

bool	ft_check_paths(t_env *env_root)
{
	t_env	*tmp;
	bool	flag;

	tmp = env_root;
	flag = true;
	while (tmp && ft_strcmp(tmp->name, "PATH") != 0)
		tmp = tmp->next;
	if (!tmp)
		flag = false;
	return (flag);
}
