/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:21:02 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/26 15:30:42 by erivero-         ###   ########.fr       */
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
	{
		parser->redir_in = open(lexer->next->content, O_RDONLY, 0777);
		if (parser->redir_in < 0)
			ft_printf("%s: No such file or directory\n", lexer->next->content);
	}
	else if (token == LESS_LESS)
	{
//		parser->redir_in = open(lexer->next->content, O_RDONLY, 0777);
		parser->heredoc_flag = true;
		parser->heredoc = lexer->next->content;
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

	new_node = malloc(sizeof(t_parser));
	if (!new_node)
		return (NULL);
	new_node->tmp_arg = par_newargnode(lexer->content);
	new_node->redir_in = STDIN_FILENO;
	new_node->redir_out = STDOUT_FILENO;
	new_node->heredoc = NULL;
	new_node->heredoc_flag = false;
	new_node->double_out = false;
	new_node->pipe = false;
	new_node->prev = prev;
	new_node->next = NULL;
	return (new_node);
}

t_parser	*ft_config_pipe(t_parser *parser, t_lexer *lexer_ptr)
{
	lexer_ptr = lexer_ptr->next;
	parser->pipe = true;
	get_final_cmd(parser);
	parser->next = new_parser_node(lexer_ptr, parser);
	parser = parser->next;
	return (parser);
}

void	ft_parser(t_info *info)
{
	t_lexer		*lexer_ptr;
	t_parser	*parser;

	lexer_ptr = info->utils->lexer_root;
	while (lexer_ptr)
	{
		if (!lexer_ptr->prev)
		{
			parser = new_parser_node(lexer_ptr, NULL);
			info->utils->parser_root = parser;
		}
		else if (lexer_ptr->token == ARG)
			get_arguments(lexer_ptr, info->utils->parser_root);
		else if (lexer_ptr->token == PIPE)
			parser = ft_config_pipe(parser, lexer_ptr);
		else
			check_redir(lexer_ptr, parser);
		lexer_ptr = lexer_ptr->next;
	}
	get_final_cmd(parser);
}
