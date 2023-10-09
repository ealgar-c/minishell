/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:28:47 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/09 14:19:43 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_variable(char *name, char *value, t_ast_utils *utils)
{
	t_env *ptr;

	ptr = utils->env_root;
	while (ptr->next)
	{ //si ya hay creada una variable con ese nombre, la sobreescribe
		if (!ft_strncmp(ptr->name, name, ft_strlen(name)))
		{
			ptr->value = value;
			return (1);
		}
	}
	return (0);
}

static void save_variable(char *name, char *value, t_ast_utils *utils)
{
	t_env	*env;

/* 	if (getenv(name)) //si es una predefinida
	{ esto es mierda y no vale pa na 
		ft_printf("The variable %s can't be overwritten\n", name);
		return ;
	} */
	if (!check_variable(name, value, utils)) //si no existe, crea la variable
	{
		env = new_env(name, value);
		if (!utils->env_root)
			utils->env_root = env;
		else
			env_add_back(utils->env_root, env);
	}	
}


static void split_variable(char *variable, t_ast_utils *utils)
{
	int		i;
	char	*name;
	char	*value;

	while (variable[i] != '=')
		i++;
	name = ft_substr(variable, 0, i);
	value = clean_quotes(ft_substr(variable, i + 1, ft_strlen(variable)));
	save_variable(name, value, utils);
	free(name);
	free(value);
}

t_env	*sort_list(t_env* lst, int (*ft_strncmp)(char *, char *, int))
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

void	ft_export(t_parser *parser_node, t_info *info)
{
	t_env	*ptr;
	char	q;
	int		i;

	if (parser_node->cmd[2])
	{
		i = 2;
		while (parser_node->cmd[i++])
			ft_printf("export: `%s': not a valid identifier\n", parser_node->cmd[i]);
	}
	if (parser_node->cmd[1])
			split_variable(parser_node->cmd[1], info->utils);
	else //si no recibe argumentos, printea la lista de todas
	{
		ptr = sort_list(info->utils->env_root, ft_strncmp);
		q = 34; //no se me ocurre cómo gestionar las comillas si no pq se buggea
		while (ptr->next)
		{
			ft_printf("%s=%c%s%c\n",ptr->name, q, ptr->value, q);
			ptr = ptr->next;
		}
	}
}
