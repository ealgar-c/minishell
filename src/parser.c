/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:21:02 by erivero-          #+#    #+#             */
/*   Updated: 2023/11/13 13:43:21 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_redir(t_lexer *lexer, t_info *info)
{
	int	token;

	token = 0;
	if (lexer->token > 1 && lexer->token < 7)
		token = lexer->token;
	if (token && !lexer->next)
		ft_error_handling(1, "newline", info);
	else if (token > PIPE && lexer->next->token > 1 && lexer->next->token < 7)
		ft_error_handling(1, lexer->content, info);
	else if (token == PIPE && lexer->next->token == PIPE)
		ft_error_handling(42, "This shell can not handle \'||\'", info);
}

void	get_redir(t_lexer *lexer, t_parser *parser, t_info *info)
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
			ft_error_handling(2, lexer->next->content, info);
	}
	else if (token == LESS_LESS)
	{
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

t_parser	*new_parser_node(t_lexer *lexer, t_parser *prev, t_info *info)
{
	t_parser	*new_node;
	t_lexer		*tmp_lex;

	new_node = malloc(sizeof(t_parser));
	if (!new_node)
		return (NULL);
	tmp_lex = lexer;
	while (tmp_lex && tmp_lex->token != CMD)
		tmp_lex = tmp_lex->next;
	fill_new_par_node(new_node, prev, tmp_lex);
	if (lexer->token != CMD)
	{
		check_redir(lexer, info);
		if (!info->error)
			get_redir(lexer, new_node, info);
	}
	return (new_node);
}

t_parser	*ft_config_pipe(t_parser *parser, t_lexer *lexer_ptr, t_info *info)
{
	lexer_ptr = lexer_ptr->next;
	parser->pipe = true;
	get_final_cmd(parser, info);
	parser->next = new_parser_node(lexer_ptr, parser, info);
	parser = parser->next;
	return (parser);
}

void	ft_parser(t_info *info)
{
	t_lexer		*lexer_ptr;
	t_parser	*parser;

	lexer_ptr = info->utils->lexer_root;
	while (lexer_ptr && !info->error)
	{
		check_redir(lexer_ptr, info);
		if (!lexer_ptr->prev && !info->error)
		{
			parser = new_parser_node(lexer_ptr, NULL, info);
			info->utils->parser_root = parser;
		}
		else if (lexer_ptr->token == ARG && !info->error)
			get_arguments(lexer_ptr, info->utils->parser_root);
		else if (lexer_ptr->token != CMD && !info->error)
		{
			if (lexer_ptr->token == PIPE)
				parser = ft_config_pipe(parser, lexer_ptr, info);
			else
				get_redir(lexer_ptr, parser, info);
		}
		lexer_ptr = lexer_ptr->next;
	}
	get_final_cmd(parser, info);
}
