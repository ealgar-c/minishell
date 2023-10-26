/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:28:47 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/26 14:50:05 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_variable(char *name, char *value, t_info *info)
{
	t_env *ptr;
//	int i = 1;

	ptr = info->env_root;
	if (!ptr) //sin esta condición hace segmentation fault, aunque para cuando se llame a esta función en la shell
		return (0); //la lista ya habrá sido creada, al menos para las envp, pero por ahora no, creo
	while (ptr)
	{ //si ya hay creada una variable con ese nombre, la sobreescribe
		if (!ft_strcmp(ptr->name, name))
		{
			free(ptr->name);
			free(ptr->value);
			ptr->name = name;
			ptr->value = value;
			return (1);
		}
		ptr = ptr->next;
//		i++;
	}
//	ft_printf("a total of %i variables where checked\n", i);
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
//		ft_printf("Variable named: \'%s\', has been saved\n", env->name);
	}
}

static bool	input_checker(char *arg)
{
	int		i;
	char	*name;

	i = 0;
	name = ft_get_env_name(arg);
	if (ft_isdigit(name[i]))
	{
		ft_printf("export: `%s': not a valid identifier\n", arg);
		return (free(name), false);
	}
	while (name[i])
	{
		if (ft_isalnum(name[i]) || name[i] == '_')
			i++;
		else
		{
			ft_printf("export: `%s': not a valid identifier\n", name);
			return (free(name), false);
		}
	}
	return (free(name), true);
}

t_env	*sort_list(t_env* lst)
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
/* 	free(swap->name); estaba liberando de más
	free(swap->value); */
	return (lst);
}


void	ft_export(t_parser *parser_node, t_info *info)
{
	t_env	*ptr;
	int		i;
//	("la primera variable a guardar es: \'%s\'\n", parser_node->cmd[1]);
	i = 1; //si es 0 guardo la variable "export" xd
	if (!parser_node->cmd[1])
	{
		ptr = sort_list(info->env_root);
		while (ptr)
		{
			if (ptr->value[0])
				ft_printf("declare -x %s=\"%s\"\n", ptr->name, ptr->value);
			else
				ft_printf("declare -x %s\n", ptr->name);
			ptr = ptr->next;
		}
	}
	else
	{
		while (parser_node->cmd[i])
		{
			if (input_checker(parser_node->cmd[i]))
				save_variable(parser_node->cmd[i], info);
			i++;
		}
	}
}
