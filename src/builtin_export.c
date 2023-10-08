/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:43:39 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/09 01:02:56 by ealgar-c         ###   ########.fr       */
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

void save_variable(char *name, char *value, t_ast_utils *utils)
{
	t_env	*env;


	if (getenv(name)) //si es una predefinida
	{ //no sé si esto está bien realmente
		ft_printf("The variable %s can't be overwritten\n", name);
		return ;
	}
	if (!check_variable(name, value, utils)) //si no existe, crea la variable
	{
		env = new_env(name, value);
		if (!utils->env_root)
			utils->env_root = env;
		else
			env_add_back(utils->env_root, env);
	}	
}

void	ft_export(t_parser *parser_node, t_info *info)
{
	char *name;
	char *value;
	int i;

	if (parser_node->cmd[2])
		ft_printf("Flags no suported in this case\n");
	i = 0;
	while (parser_node->cmd[1][i] != '=')
		i++;
	name = ft_substr(parser_node->cmd[1], 0, i);
	value = clean_quotes(ft_substr(parser_node->cmd[1], i + 1, ft_strlen(parser_node->cmd[1])));
	save_variable(name, value, utils);
	free(name);
	free(value);
}
/* Me han dicho que hay envp que contienen el caracter '='.
Para no pillarme los dedos he cambiado el sistema de spliteo, 
de forma que ya no llamo a split con '=', sino que creo dos substrings
separándolas por el primer '=' que encuentre, y obviando los demás */
