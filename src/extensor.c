/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extensor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:03:54 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/10 13:36:57 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*check_notenv(char *env, t_info *info)
{
	char	*ret;

	if (ft_strcmp(env, "?") == 0)
		ret = ft_strdup(ft_itoa(info->exit_status));
	else if (ft_strcmp(env, "0") == 0)
		ret = (ft_strdup("conchita"));
	else
		return (NULL);
	return (ret);
}

char	*get_env(char *env, t_info *info)
{
	t_env	*tmp;
	char	*tmp_ret;

	tmp_ret = check_notenv(env, info);
	if (tmp_ret != NULL)
		return (free(env), tmp_ret);
	tmp = info->env_root;
	while (tmp && ft_strcmp(env, tmp->name) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (free(env), NULL);
	if (env[ft_strlen(env) - 1] == 32)
		return (free(env), ft_strjoin(tmp->value, " "));
	return (free(env), ft_strdup(tmp->value));
}

static char	*get_extended(char *str, int orig, t_info *info)
{
	int		len;
	char	*env_to_check;
	char	*ret;

	len = 0;
	while (str[orig + len] && str[orig + len] != ' ' && str[orig + len] != '$'
		&& str[orig + len] != '/')
		len++;
	env_to_check = ft_substr(str, orig, len);
	ret = get_env(env_to_check, info);
	return (ft_insertstr(str, orig - 1, len + 1, ret));
}

/* static char	*clean_quotes(char *str)
{
	return (ft_substr(str, 1, ft_strlen(str) - 2));
}
 */
char	*check_extensor(char *content, t_info *info, char quoted)
{
	int		i;
	char	*to_extend;

	i = 0;
	to_extend = ft_strdup(content);
	while (to_extend[i])
	{
		if (to_extend[i] == '$' && quoted != 39)
			to_extend = get_extended(to_extend, i + 1, info);
		else if (to_extend[0] == '~' && quoted != 39 && quoted != 34)
			to_extend = ft_strdup(getenv("HOME"));
		if (!(to_extend[i] == '$' && quoted != 39))
			i++;
	}
	return (free(content), to_extend);
}
/* char	*check_extensor(char *content, t_info *info, char q)
{
	int		i;
	char	*to_extend;

	i = 0;
	to_extend = ft_strdup(content);
	while (to_extend[i])
	{
		if (to_extend[i] == '$' && q != 39)
			to_extend = get_extended(to_extend, i + 1, info);
		else if (to_extend[0] == '~' && q != 39 && q != 34)
			to_extend = ft_strdup(getenv("HOME"));
		if (!(to_extend[i] == '$' && q != 39))
			i++;
	}
	return (free(content), to_extend);
} */
