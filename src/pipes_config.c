/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:16:30 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/29 19:35:29 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*	mode:
		0 if i want to create the pipes (as the first side of it)
		1 close redir_out
		2 close redir_in
*/
void	config_pipes(t_parser *parser, int mode)
{
	int	fd[2];

	if (mode == 0)
	{
		pipe(fd);
		parser->redir_out = fd[1];
		parser->next->redir_in = fd[0];
	}
	else if (mode == 1)
		close(parser->redir_out);
	else if (mode == 2)
		close(parser->redir_in);
}

/* 		ft_printf("entrada en modo 1\n");
		if (parser->pipe)
		{
			ft_printf("cerrando la entrada del siguiente\n");
			close(parser->next->redir_in);
		}
		if (parser->prev)
		{
			if (parser->prev->pipe)
			{
				ft_printf("cerrando la salida del anterior\n");
				close (parser->prev->redir_out);
			}
		} */