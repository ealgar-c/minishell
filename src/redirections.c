/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:44:29 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/29 17:07:04 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_heredoc_loop(int fd, char *delim)
{
	char	*line;

	while (1)
	{
		ft_printf("\033[0;32m> \033[0m");
		line = get_next_line(0);
		if (!line)
			break ; //habria que cerrar mejor
		if (!ft_strncmp(delim, line, ft_strlen(delim)) 
		&& !ft_strncmp(delim, line, ft_strlen(line - 1)))
			break ;
		write(fd, line, ft_strlen(line));
	}
	free(line);
}

int ft_heredoc(t_parser *parser)
{
	int	pipefd[2];

	pipe(pipefd); // parchear por si falla?
	g_signals.heredoc = true;
	ft_heredoc_loop(pipefd[1], parser->heredoc);
	close(pipefd[1]);
	g_signals.heredoc = false;
	return(pipefd[0]);
}

void	ft_redirector(t_parser *parser_node)
{
	if (parser_node->heredoc_flag)
		dup2(ft_heredoc(parser_node), STDIN_FILENO);
	if (parser_node->redir_in != -1)
		dup2(parser_node->redir_in, STDIN_FILENO);
	if (parser_node->redir_out != -1)
		dup2(parser_node->redir_out, STDOUT_FILENO);
}