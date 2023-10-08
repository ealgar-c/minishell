/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extensor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 20:03:54 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/08 20:56:09 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_env(char *env)
{
	char	*ret;

	ret = getenv(env);
	/* if (ret == NULL)
	{
		aqui se tiene q buscar dentro de las env metidas por nosotros
	} */
	return (ret);
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
			return (ft_itoa(info->last_exit));
		}
		env = ft_strtrim(content, "$");
		ret_env = get_env(env);
		return (ret_env);
	}
	return (content);
}
