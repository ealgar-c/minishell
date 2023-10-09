/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:28:47 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/09 16:27:31 by erivero-         ###   ########.fr       */
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
		env = ft_new_env_node(name, value);
		if (!utils->env_root)
			utils->env_root = env;
		else
			env_add_back(&utils->env_root, env);
	}	
}


static void split_variable(char *variable, t_ast_utils *utils)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (variable[i] != '=')
		i++;
	name = ft_substr(variable, 0, i);
	value = clean_quotes(ft_substr(variable, i + 1, ft_strlen(variable)));
	save_variable(name, value, utils);
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

void	ft_export(t_parser *parser_node, t_info *info)
{
	t_env	*ptr;
	char	**cmd;
	char	q;
	int		i;

	cmd = ft_split(parser_node->cmd, 32);
	if (cmd[2])
	{
		i = 2;
		while (parser_node->cmd[i++])
		ft_printf("export: `%s': not a valid identifier\n", cmd[i]);
	}
	if (cmd[1])
		split_variable(cmd[1], info->utils);
	else //si no recibe argumentos, printea la lista de todas
	{
		ptr = sort_list(info->utils->env_root, ft_strncmp);
		q = 34; //no se me ocurre cómo gestionar las comillas si no pq se buggea
		while (ptr->next)
		{
			ft_printf("%s=%c%s%c\n", ptr->name, q, ptr->value, q);
			ptr = ptr->next;
		}
	}
	free(cmd);
}
