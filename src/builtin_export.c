/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:43:39 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/07 13:14:14 by erivero-         ###   ########.fr       */
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

t_env	*new_env(char *name, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->name = name;
	env->value = value;
}

void	env_add_back(t_env **root, t_env *new)
{
	t_env	*ptr;

	ptr = *root;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}
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

void ft_export(char **cmd, t_ast_utils *utils)
{
	char *name;
	char *value;
	int i;

	if (cmd[2])
		ft_printf("Flags no suported in this case\n");
	i = 0;
	while (cmd[1][i] != '=')
		i++;
	name = ft_substr(cmd[1], 0, i);
	value = clean_quotes(ft_substr(cmd[1], i + 1, ft_strlen(cmd[1])));
	save_variable(name, value, utils);
	free(name);
	free(value);
}
/* Me han dicho que hay envp que contienen el caracter '='.
Para no pillarme los dedos he cambiado el sistema de spliteo, 
de forma que ya no llamo a split con '=', sino que creo dos substrings
separándolas por el primer '=' que encuentre, y obviando los demás */
