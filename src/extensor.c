/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extensor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:03:54 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/14 11:33:02 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_env(char *env, t_info *info)
{
	t_env	*tmp;

	tmp = info->env_root;

	while (ft_strncmp(env, tmp->name, ft_strlen(env)) != 0)
		tmp = tmp->next;
	return (tmp->value);
}

char	*check_extensor(char *content, t_info *info)
{
	char	*env;
	char	*ret_env;

	ret_env = NULL;
	if (content[0] == '$')
	{
		if (ft_strncmp(content, "$?\0", 3) == 0)
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
	else if (content[0] == 34)
		return (check_extensor(clean_quotes(content), info)); //creo que esto está mal porque sólo checkearía el primer caracter tras las comillas
	return (content);
}
