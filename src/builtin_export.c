/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:28:47 by erivero-          #+#    #+#             */
/*   Updated: 2023/11/14 13:23:28 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_variable(char *name, char *value, t_info *info)
{
	t_env	*ptr;

	ptr = info->env_root;
	if (!ptr)
		return (0);
	while (ptr)
	{
		if (!ft_strcmp(ptr->name, name))
		{
			free(ptr->name);
			free(ptr->value);
			ptr->name = name;
			ptr->value = value;
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

void	save_variable(char *variable, t_info *info)
{
	t_env	*env;
	char	*name;
	char	*value;

	name = ft_get_env_name(variable);
	value = ft_get_env_value(variable);
	if (!check_variable(name, value, info))
	{
		env = ft_new_env_node(name, value);
		env_add_back(&info->env_root, env);
	}
}

bool	input_checker(char *arg, char *cmd)
{
	int		i;
	char	*name;

	i = 0;
	name = ft_get_env_name(arg);
	if (ft_isdigit(name[i]))
	{
		ft_printf("\033[0;33mconchita: %s: \033[0m", cmd);
		ft_printf("\033[0;33m`%s': not a valid identifier\n\033[0m", name);
		return (free(name), false);
	}
	while (name[i])
	{
		if (ft_isalnum(name[i]) || name[i] == '_')
			i++;
		else
		{
			ft_printf("\033[0;33mconchita: export: \033[0m");
			ft_printf("\033[0;33m`%s': not a valid identifier\n\033[0m", name);
			return (free(name), false);
		}
	}
	return (free(name), true);
}

void	ft_export(t_parser *parser_node, t_info *info)
{
	int		i;

	i = 1;
	info->exit_status = 0;
	if (!parser_node->cmd[1])
		ft_non_arg_export(info);
	else
	{
		while (parser_node->cmd[i])
		{
			if (input_checker(parser_node->cmd[i], parser_node->cmd[0]))
				save_variable(parser_node->cmd[i], info);
			else
				info->exit_status = 1;
			i++;
		}
	}
}
