/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extensor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:03:54 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/09 17:00:59 by ealgar-c         ###   ########.fr       */
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
	return (content);
}
