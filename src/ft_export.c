/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:43:39 by erivero-          #+#    #+#             */
/*   Updated: 2023/09/28 12:03:15 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* typedef struct	s_env
{
	char			*name;
	int				len; //pa comparar con ft_strncmp
	char			*value;
	struct s_env	*next;

}	t_env;
 */

/* a lo mejor habría que añadir una comprobación de que el nombre y el contenido de
la variable a añadir sean correctos, tipo mayúsculas y toda la pesca, pero eso 
es problema de la eli del futuro  */

t_env	*new_env(char **var)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->name = var[0];
	env->value = ft_strtrim(var[1], """");
}

void	env_add_back(t_env **root, t_env *new)
{
	t_env	*ptr;

	ptr = *root;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}
int	check_variable(char **var, t_ast_utils *utils)
{
	t_env *ptr;

	ptr = utils->env_root;
	while (ptr->next)
	{ //si ya hay creada una variable con ese nombre, la sobreescribe
		if (!ft_strncmp(ptr->name, var[0], ft_strlen(var[0])))
		{
			ptr->value = var[1];
			return (1);
		}
	}
	return (0);
}

void save_variable(char *str, t_ast_utils *utils)
{
	char	**var;
	t_env	*env;


	var = ft_split(str, '=');
	if (getenv(var[0])) //si es una predefinida
	{ //no sé si esto está bien realmente
		ft_printf("The variable %s can't be overwritten\n", var[0]);
		return ;
	}
	if (!check_variable(var, utils)) //si no existe, crea la variable
	{
		env = new_env(var);
		if (!utils->env_root)
			utils->env_root = env;
		else
			env_add_back(utils->env_root, env);
	}	
	free(var);
}


void ft_export(char **cmd, t_ast_utils *utils)
{
	if (cmd[2])
		ft_printf("Flags no suported in this case\n");
	save_variable(cmd[1], utils);	
}