/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:28:47 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/18 19:10:48 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_variable(char *name, char *value, t_info *info)
{
	t_env *ptr;
	int i = 1;

	ptr = info->env_root;
	if (!ptr) //sin esta condición hace segmentation fault, aunque para cuando se llame a esta función en la shell
		return (0); //la lista ya habrá sido creada, al menos para las envp, pero por ahora no, creo
	while (ptr)
	{ //si ya hay creada una variable con ese nombre, la sobreescribe
		if (!ft_strncmp(ptr->name, name, ft_strlen(ptr->name)))
		{
			ptr->value = value;
			return (1);
		}
		ptr = ptr->next;
		i++;
	}
	return (0);
}

static void save_variable(char *variable, t_info *info)
{
	t_env	*env;
	char	*name;
	char	*value;

	name = ft_get_env_name(variable);
	value = ft_get_env_value(variable);
	if (!check_variable(name, value, info)) //si no existe, crea la variable
	{
		env = ft_new_env_node(name, value);
/* 		if (!info->env_root)
			info->env_root = env;
		else */
		env_add_back(&info->env_root, env);
//		ft_printf("Variable named: %s, has been saved\n", env->name);
	}
}

static bool	input_checker(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[i]))
	{
		ft_printf("export: `%s': not a valid identifier\n", arg);
		return (false);
	}
	while (arg[i])
	{
		if (ft_isalnum(arg[i]) || arg[i] == '_')
			i++;
		else
		{
			ft_printf("export: `%s': not a valid identifier\n", arg);
			return (false);
		}
	}
	return (true);
}

t_env	*sort_list(t_env* lst)
{
	t_env	*root;
	t_env	*swap;

	root = lst;
	swap = ft_new_env_node(NULL, NULL);
	while (lst->next != NULL)
	{
		if (lst->next && ft_strncmp(lst->name, lst->next->name, ft_strlen(lst->name)) > 0)
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
	free(swap->name);
	free(swap->value);
	free(swap);
	return (lst);
}

void	ft_export(t_parser *parser_node, t_info *info)
{
	t_env	*ptr;
	char	**cmd;
	int		i;

	cmd = ft_split(parser_node->cmd, 32);
	i = 0;
	if (!cmd[1])
	{
		ptr = sort_list(info->env_root);
		if (!ptr)
			return ;
		while (ptr)
		{
			ft_printf("declare -x %s=\"%s\" %d\n", ptr->name, ptr->value, i);
			ptr = ptr->next;
		}
	}
	else
	{
		while (cmd[i])
		{
			if (input_checker(ft_get_env_name(cmd[i])))
				save_variable(cmd[i], info);
		}
	}
	ft_free(cmd);
}

