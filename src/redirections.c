/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:44:29 by erivero-          #+#    #+#             */
/*   Updated: 2023/11/05 22:05:12 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_heredoc_loop(int fd, char *delim)
{
	char	*line;

	while (1)
	{
		ft_printf("\033[0;32m> \033[0m");
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(delim, line, ft_strlen(delim))
			&& !ft_strncmp(delim, line, ft_strlen(line - 1)))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
}

int	ft_heredoc(t_parser *parser, t_info	*info)
{
	int	pipefd[2];

	pipe(pipefd);
	if (pipefd < 0)
		ft_error_handling(3, NULL, info);
	g_signals.heredoc = true;
	ft_heredoc_loop(pipefd[1], parser->heredoc);
	close(pipefd[1]);
	g_signals.heredoc = false;
	return (pipefd[0]);
}

void	ft_redirector_builtinpipes(t_parser *parser_node, t_info *info)
{
	if (parser_node->heredoc_flag)
		dup2(ft_heredoc(parser_node, info), STDIN_FILENO);
	else if (parser_node->redir_in != -1 && parser_node->redir_in != 0)
	{
		dup2(parser_node->redir_in, STDIN_FILENO);
		close(parser_node->redir_in);
	}
	if (parser_node->redir_out != -1 && parser_node->redir_out != STDOUT_FILENO)
	{
		dup2(parser_node->redir_out, STDOUT_FILENO);
		close(parser_node->redir_out);
	}
}

void	ft_redirector(t_parser *parser_node, t_info *info)
{
	if (parser_node->pipe || (parser_node->prev && parser_node->prev->pipe))
		ft_redirector_builtinpipes(parser_node, info);
	else
	{
		if (parser_node->heredoc_flag)
			dup2(ft_heredoc(parser_node, info), STDIN_FILENO);
		else if (parser_node->redir_in != -1)
			dup2(parser_node->redir_in, STDIN_FILENO);
		if (parser_node->redir_out != -1)
			dup2(parser_node->redir_out, STDOUT_FILENO);
	}
}

void	ft_redirector_back(t_info *info)
{
	dup2(info->stdin_cpy, STDIN_FILENO);
	dup2(info->stdout_cpy, STDOUT_FILENO);
}
