/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:05:20 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/06 13:05:39 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fill_new_par_node(t_parser *new, t_parser *prev, t_lexer *tmp_lex)
{
	new->tmp_arg = par_newargnode(tmp_lex);
	new->redir_in = STDIN_FILENO;
	new->redir_out = STDOUT_FILENO;
	new->heredoc = NULL;
	new->heredoc_flag = false;
	new->double_out = false;
	new->pipe = false;
	new->prev = prev;
	new->next = NULL;
	new->pipe_redir_out = -1;
	new->pipe_redir_in = -1;
}
