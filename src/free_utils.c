/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:17:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/10 13:36:49 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_env(t_env *root)
{
	t_env	*env_tmp;
	t_env	*next_env_tmp;

	if (root)
	{
		env_tmp = root;
		while (env_tmp)
		{
			next_env_tmp = env_tmp->next;
			if (env_tmp->name)
				free(env_tmp->name);
			if (env_tmp->value)
				free(env_tmp->value);
			free(env_tmp);
			env_tmp = next_env_tmp;
		}
	}
}

void	ft_free(char **str)
{
	char	**ptr;

	if (!str)
		return ;
	ptr = str;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(str);
}
