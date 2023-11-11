/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:16:30 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/11 16:26:46 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*	mode:
		0 if i want to create the pipes (as the first side of it)
		1 close redir_out
		2 close redir_in
*/
void	config_pipes(t_parser *parser, int mode, t_info *info)
{
	int	fd[2];

	if (mode == 0)
	{
		pipe(fd);
		if (fd < 0)
			ft_error_handling(3, NULL, info);
		parser->pipe_redir_out = fd[1];
		parser->next->pipe_redir_in = fd[0];
	}
	else if (mode == 1)
		close(parser->pipe_redir_out);
	else if (mode == 2)
		close(parser->pipe_redir_in);
}

static void	pipein(t_parser *parser_node, int *flag)
{
	if (parser_node->redir_in == STDIN_FILENO)
		dup2(parser_node->pipe_redir_in, STDIN_FILENO);
	else
		*flag += 1;
	close(parser_node->pipe_redir_in);
}

int	ft_redirector_builtinpipes(t_parser *parser_node, t_info *info)
{
	int	flag;

	flag = 0;
	if (parser_node->heredoc_flag)
		dup2(ft_heredoc(parser_node, info), STDIN_FILENO);
	else if (parser_node->pipe_redir_in != -1)
		pipein(parser_node, &flag);
	else
		flag += 1;
	if (parser_node->pipe_redir_out != -1)
	{
		if (parser_node->redir_out == STDOUT_FILENO)
			dup2(parser_node->pipe_redir_out, STDOUT_FILENO);
		else
			flag += 2;
		close(parser_node->pipe_redir_out);
	}
	else
		flag += 2;
	return (flag);
}
