/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:21:02 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/19 12:00:54 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_redir(t_lexer *lexer, t_parser *parser)
{
	int	token;

	token = lexer->token;
	if (token == GREAT)
		parser->redir_out = open(lexer->next->content,
				O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else if (token == LESS)
		parser->redir_in = open(lexer->next->content, O_RDONLY, 0777);
	else if (token == LESS_LESS)
	{
		parser->redir_in = open(lexer->next->content, O_RDONLY, 0777);
		parser->heredoc_flag = true;
	}
	else if (token == GREAT_GREAT)
	{
		parser->redir_out = open(lexer->next->content,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
		parser->double_out = true;
	}
}

t_parser	*new_parser_node(t_lexer *lexer, t_parser *prev)
{
	t_parser	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->cmd = ft_strdup(lexer->content);
	new_node->redir_in = STDIN_FILENO;
	new_node->redir_out = STDOUT_FILENO;
	new_node->heredoc_flag = false;
	new_node->double_out = false;
	new_node->pipe = false;
	new_node->prev = prev;
	new_node->next = NULL;
	return (new_node);
}

t_parser	*ft_config_pipe(t_parser *parser, t_lexer *lexer_ptr)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) != 0)
		return (NULL);
	lexer_ptr = lexer_ptr->next;
	parser->redir_out = pipe_fd[0];
	parser->pipe = true;
	parser->next = new_parser_node(lexer_ptr, parser);
	parser = parser->next;
	parser->redir_in = pipe_fd[1];
	return (parser);
}

void	ft_parser(t_info *info)
{
	t_lexer		*lexer_ptr;
	t_parser	*parser;
	char		*tmp;

	lexer_ptr = info->utils->lexer_root;
	while (lexer_ptr)
	{
		if (!lexer_ptr->prev)
		{
			parser = new_parser_node(lexer_ptr, NULL);
			info->utils->parser_root = parser;
		}
		else if (lexer_ptr->token == ARG)
		{
			tmp = ft_strjoin(parser->cmd, " ");
			parser->cmd = ft_strjoin(tmp,
					check_extensor(lexer_ptr->content, info));
			free(tmp);
		}
		else if (lexer_ptr->token == PIPE)
			parser = ft_config_pipe(parser, lexer_ptr);
		else
			check_redir(lexer_ptr, parser);
		lexer_ptr = lexer_ptr->next;
	}
}
