/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extensor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:03:54 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/05 17:51:44 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_env(char *env, t_info *info)
{
	t_env	*tmp;
	char	*tmp_env;

	tmp = info->env_root;
	tmp_env = ft_strtrim(env, " ");
	if (ft_strcmp(tmp_env, "?") == 0)
		return (free(tmp_env), ft_strdup(ft_itoa(info->exit_status)));
	else if (ft_strcmp(tmp_env, "0") == 0)
		return (free(tmp_env), ft_strdup("conchita"));
	while (tmp && ft_strcmp(tmp_env, tmp->name) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (free(tmp_env), NULL);
	if (env[ft_strlen(env) - 1] == 32)
		return (free(tmp_env), ft_strjoin(tmp->value, " "));
	return (free(tmp_env), tmp->value);
}

char	*get_extended(char *to_extend, char *orig, int i)
{
	char	*prev;

	if (i == 0)
		return (to_extend);
	prev = ft_substr(orig, 0, i);
	if (to_extend == NULL)
		return (prev);
	return (free(prev), ft_strjoin(prev, to_extend));
}

char	*check_extensor(char *content, t_info *info, int quoted)
{
	int		i;
	char	*to_extend;

	i = 0;
	to_extend = NULL;
	while (content[i])
	{
		if (content[i] == '$' && quoted != SINGLE)
		{
			to_extend = get_env(ft_substr(content, i + 1,
						ft_strlen(content) - i + 1), info);
			break ;
		}
		else if (content[0] == '~' && quoted == NONE)
		{
			to_extend = get_env("HOME", info);
			break ;
		}
		else
			i++;
	}
	if (to_extend == NULL && !content[i])
		return (content);
	return (get_extended(to_extend, content, i));
}
/* 
char	*check_extensor(char *content, t_info *info)
{
	char	*env;
	char	*ret_env;

	ret_env = NULL;
	if (content[0] == '$')
	{
		if (ft_strcmp(content, "$?") == 0)
		{
			return (ft_itoa(info->exit_status));
		}
		env = ft_strtrim(content, "$");
		ret_env = get_env(env, info);
		return (ret_env);
	}
	else if (content[0] == '~')
	{
		ret_env = get_env("HOME", info);
		env = ft_strtrim(content, "~");
		return (ft_strjoin(ret_env, env));
	}
	return (content);
}
 */