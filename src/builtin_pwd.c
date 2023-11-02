/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:55:45 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/02 10:54:07 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_pwd_exec(t_info *info)
{
	char	*path;

	path = malloc(sizeof(char) * 100);
	path = getcwd(path, 100);
	ft_printf("%s\n", path);
	free(path);
	info->exit_status = 0;
}

void	ft_pwd(t_parser *parser_node, t_info *info)
{
	ft_redirector(parser_node, info);
	ft_pwd_exec(info);
	ft_redirector_back(info);
}
