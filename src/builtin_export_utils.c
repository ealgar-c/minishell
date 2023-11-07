/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:28:47 by erivero-          #+#    #+#             */
/*   Updated: 2023/11/07 18:58:33 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_env	*sort_list(t_env *lst)
{
	t_env	*root;
	t_env	*swap;

	root = lst;
	swap = ft_new_env_node(NULL, NULL);
	while (lst->next != NULL)
	{
		if (lst->next && ft_strcmp(lst->name, lst->next->name) > 0)
		{
			swap->name = lst->name;
			swap->value = lst->value;
			lst->name = lst->next->name;
			lst->value = lst->next->value;
			lst->next->name = swap->name;
			lst->next->value = swap->value;
			lst = root;
		}
		else
			lst = lst->next;
	}
	lst = root;
	free(swap);
	return (lst);
}

static t_env	*copy_list(t_env *lst)
{
	t_env	*cpy;
	t_env	*ptr;

	ptr = lst;
	cpy = NULL;
	while (ptr)
	{
		if (!cpy)
			cpy = ft_new_env_node(strdup(ptr->name), strdup(ptr->value));
		else
			env_add_back(&cpy, ft_new_env_node(strdup(ptr->name),
					strdup(ptr->value)));
		ptr = ptr->next;
	}
	return (cpy);
}

void	ft_non_arg_export(t_info *info)
{
	t_env	*ptr;
	t_env	*root;

	root = copy_list(info->env_root);
	ptr = sort_list(root);
	while (ptr)
	{
		if (ptr->value[0])
			ft_printf("declare -x %s=\"%s\"\n", ptr->name, ptr->value);
		else
			ft_printf("declare -x %s\n", ptr->name);
		ptr = ptr->next;
	}
	ft_free_env(root);
}
