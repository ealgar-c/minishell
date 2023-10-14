/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:28:47 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/14 12:14:57 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_variable(char *name, char *value, t_info *info)
{
	t_env *ptr;

	ptr = info->env_root;
	ft_printf("me he roto ya?\n");
	if (!ptr) //sin esta condición hace segmentation fault, aunque para cuando se llame a esta función en la shell
		return (0); //la lista ya habrá sido creada, al menos para las envp, pero por ahora no, creo
	while (ptr->next)
	{ //si ya hay creada una variable con ese nombre, la sobreescribe
		if (!ft_strncmp(ptr->name, name, ft_strlen(name)))
		{
			ptr->value = value;
			return (1);
		}
		ptr = ptr->next;
	}
	ft_printf("y ahora?\n");
	return (0);
}

static void save_variable(char *name, char *value, t_info *info)
{
	t_env	*env;

	if (!check_variable(name, value, info)) //si no existe, crea la variable
	{
		ft_printf("hola, he hecho cosas\n");
		env = ft_new_env_node(name, value);
/* 		if (!info->env_root)
			info->env_root = env;
		else */
		env_add_back(&info->env_root, env);
		ft_printf("Variable named: %s, has been saved\n", env->name);
	}
}

static void split_variable(char *variable, t_info *info)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (variable[i] != '=')
		i++;
	name = ft_substr(variable, 0, i);
	value = clean_quotes(ft_substr(variable, i + 1, ft_strlen(variable)));
	ft_printf("name is: %s\nvalue is: %s\n", name, value);
	save_variable(name, value, info);
	free(name);
	free(value);
}
//int	ft_strncmp(const char *s1, const char *s2, size_t n)

t_env	*sort_list(t_env* lst, int (*ft_strncmp)(const char *,const char *, size_t))
{
	t_env	*tmp;
	char	*name_cpy;
	char	*value_cpy;

	tmp = lst;
	while (lst->next != NULL)
	{
		if (((*ft_strncmp)(lst->name, lst->next->name, ft_strlen(lst->name))) > 0)
		{
			name_cpy = ft_strdup(lst->name);
			value_cpy = ft_strdup(lst->value);
			lst->name = lst->next->name;
			lst->value = lst->next->value;
			lst->next->name = name_cpy;
			lst->next->value = value_cpy;
			lst = tmp;
			free(name_cpy);
			free(value_cpy);
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}
/* t_env	*sort_list(t_env* lst)
{
	t_env	*tmp;
	char	*name_cpy;
	char	*value_cpy;

	tmp = lst;
	ft_printf("todo bien?\n");
	while (lst->next != NULL)
	{
		if (lst->next && ft_strncmp(lst->name, lst->next->name, ft_strlen(lst->name)) > 0)
		{
			name_cpy = ft_strdup(lst->name);
			value_cpy = ft_strdup(lst->value);
			lst->name = lst->next->name;
			lst->value = lst->next->value;
			lst->next->name = name_cpy;
			lst->next->value = value_cpy;
			lst = tmp;
			free(name_cpy);
			free(value_cpy);
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
} */
bool	input_checker(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[i]))
	{
		ft_printf("export: `%s': not a valid identifier\n", arg[i]);	
		return (false);
	}
	while (arg[i])	
	{
		if (ft_isalnum(arg[i]) || arg[i] == '_')
			i++;
		else
		{
			ft_printf("export: `%s': not a valid identifier\n", arg[i]);	
			return (false);
		}
	}
	return (true);
}

void	ft_export(t_parser *parser_node, t_info *info)
{
	t_env	*ptr;
	char	**cmd;
	int		i;

	cmd = ft_split(parser_node->cmd, 32);
	if (!cmd[1])
	{
//		ptr = sort_list(info->env_root, ft_strncmp);
		ptr = info->env_root;
		if (!ptr)
			return ;
		while (ptr)
		{
			ft_printf("declare -x %s=\"%s\"\n", ptr->name, ptr->value);
			ptr = ptr->next;
		}
	}
	else
	{
		i = 1;
		while (cmd[i++])
		{
			if (input_checker(cmd[i]))
				split_variable(cmd[i], info);
		}
	}
	free(cmd);
}
