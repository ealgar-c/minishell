/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:59:10 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/25 12:30:47 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_new_env_node(char *name, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->name = name;
	env->value = value;
	env->next = NULL;
	env->prev = NULL;
	return (env);
}

void	env_add_back(t_env **root, t_env *new)
{
	t_env	*ptr;

	ptr = *root;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	ptr->next->prev = ptr;
}

char	*ft_get_env_name(char *fullenv)
{
	int	i;

	i = 0;
	while (fullenv[i] && fullenv[i] != '=' && fullenv[i] != ' ')
		i++;
	return (ft_substr(fullenv, 0, i));
}

char	*ft_get_env_value(char *fullenv)
{
	int	i;

	i = 0;
	while (fullenv[i] && fullenv[i] != '=' && fullenv[i] != ' ')
		i++;
	return (ft_substr(fullenv, i + 1, ft_strlen(fullenv) - i));
}

t_env	*save_envp(char **envp)
{
	t_env	*root;
	int		i;

	root = ft_new_env_node(ft_get_env_name(envp[0]),
			ft_get_env_value(envp[0]));
	i = 1;
	while (envp[i])
	{
		env_add_back(&root, ft_new_env_node(ft_get_env_name(envp[i]),
				ft_get_env_value(envp[i])));
		i++;
	}
	return (root);
}
