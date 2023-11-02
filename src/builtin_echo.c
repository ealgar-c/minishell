/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:24:18 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/02 18:55:15 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* char	*clean_quotes(char *content)
{
	return (ft_strtrim(content, "\"\'"));
} */

void	ft_echo(t_parser *parser_node, t_info *info)
{
	int		i;
	
	i = 1;
	if (!parser_node->cmd[i])
	{
		write(1, "\n", 1);
		return ;
	}
	if (parser_node->pipe || (parser_node->prev && parser_node->prev->pipe))
		ft_redirector_builtinpipes(parser_node, info);
	else
		ft_redirector(parser_node, info);
	if (ft_strcmp(parser_node->cmd[i], "-n ") == 0)
		i++;
	while (parser_node->cmd[i])
	{
		ft_printf("%s", parser_node->cmd[i]);
		i++;
	}
	if (ft_strcmp(parser_node->cmd[1], "-n " ) != 0)
		ft_printf("\n");
	ft_redirector_back(info);
	info->exit_status = 0;
}
