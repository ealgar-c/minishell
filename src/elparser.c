/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elparser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:21:02 by erivero-          #+#    #+#             */
/*   Updated: 2023/09/26 15:59:11 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_redir(t_lexer *lexer, t_parser *parser)
{
	int	token;

	token = lexer->token;
	if (token == GREAT)
		parser->redir_out = lexer->next->content;
	else if (token == LESS)
		parser->redir_in = lexer->next->content;
	else if (token == LESS_LESS)
	{
		parser->redir_in = lexer->next->content;
		parser->heredoc_flag = true;
	}
	else if (token == GREAT_GREAT)
	{
		parser->redir_out = lexer->next->content;
		parser->double_out = true;
	}
}

void *(ft_builtincmp(char *str))(t_parser?)
{

	if (strncmp(str, "echo", 4))
		return (ft_echo);
	if (strncmp(str, "cd", 2))
		return (ft_cd);
	if (strncmp(str, "pwd", 3))
		return (ft_pwd);
	if (strncmp(str, "export", 6))
		return (ft_export);
	if (strncmp(str, "env", 3))
		return (ft_env);
	if (strncmp(str, "exit", 4))
		return (ft_exit);
	return (NULL);
}

t_parser	*new_parser_node(t_lexer *lexer, t_ast_utils *utils, t_parser *prev)
{
	t_parser *new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->cmd = lexer->content;
//cada vez que creemos un nodo, estaremos o al principio, o tras una pipe, por lo que siempre 
//debería ser un comando. Por eso he guardado el contenido directamente.

	new_node->function = ft_builtincmp(new_node->cmd);
	new_node->redirections = new_lexer_node("NULL", 0, 0, utils);
	new_node->prev = prev;
	new_node->next = NULL;
	return (new_node);
	
}

void ft_parser(t_ast_utils *utils)
{
	t_lexer		*lexer_ptr;
	t_parser	*parser;

	lexer_ptr = utils->lexer_root;
	while(lexer_ptr->next)
	{
		if (!lexer_ptr->prev)
		{
			parser = new_parser_node(lexer_ptr, utils, NULL);
			utils->parser_root = parser;
		}
		check_redir(lexer_ptr, parser)
		if (lexer_ptr->token == ARG)
		//guardar argumentos, ya veremos si como array o qué
		if (lexer_ptr->token == PIPE)
		{
			lexer_ptr = lexer_ptr->next;
			parser->next = new_parser_node(lexer_ptr, utils, parser);
			parser = parser->next;
		}
		lexer_ptr = lexer_ptr->next;
	}
}

//Para tema redirecciones podríamos guardar un puntero al nodo de la t_lexer
//o bien, directamente, pasarlo por una función que consiga el fd del archivo que sea
//lo malo es que esa función debería llamar a open y ya dejar el archivo abierto y eso no me hace
//especial gracia. Creo que eso sería mejor hacerlo ya en el executor.