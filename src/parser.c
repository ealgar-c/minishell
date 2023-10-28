/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:21:02 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/28 17:02:39 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	check_redir(t_lexer *lexer, t_parser *parser)
{
	int token;

	token = 0;
	if (lexer->token > 1 && lexer->token < 7) //si el token es una redirección
		token = lexer->token;
	if (token && !lexer->next) //si después de la redirección no hay nada en bash se printea:
	{
		ft_printf("syntax error near unexpected token `newline'\n");
		parser->redir_in = -1;
		return (false);
	}
	else if (token && lexer->next->token > 1 && lexer->next->token < 7)
	{
	//	ft_printf("token is %i, and next is %i\n", token, next);
		ft_printf("syntax error near unexpected token `%s'\n", lexer->content);
		parser->redir_in = -1; //para mandar cntrl+c al ejecutor
		return (false);
	}
	return (true);
}

void	get_redir(t_lexer *lexer, t_parser *parser)
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
	t_lexer		*tmp_lex;

	new_node = malloc(sizeof(t_parser));
	if (!new_node)
		return (NULL);
	tmp_lex = lexer;
	while (tmp_lex && tmp_lex->token != CMD)
		tmp_lex = tmp_lex->next;
	new_node->tmp_arg = par_newargnode(tmp_lex->content);
	new_node->redir_in = STDIN_FILENO;
	new_node->redir_out = STDOUT_FILENO;
	new_node->heredoc = NULL;
	new_node->heredoc_flag = false;
	new_node->double_out = false;
	new_node->pipe = false;
	new_node->prev = prev;
	new_node->next = NULL;
	if (lexer->token != CMD)
	{
		if (check_redir(lexer, new_node))
			get_redir(lexer, new_node);
	}
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
		else if (lexer_ptr->token != CMD)
		{
			if (check_redir(lexer_ptr, parser))
				get_redir(lexer_ptr, parser);
		}
		lexer_ptr = lexer_ptr->next;
	}
	get_final_cmd(parser);
}
