/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:17:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/06 13:08:28 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_close(t_parser *node)
{
	while (node)
	{
		if (node->redir_in != STDIN_FILENO)
			close(node->redir_in);
		if (node->redir_out != STDOUT_FILENO)
			close(node->redir_out);
		node = node->next;
	}
}

static void	ft_free_lexer(t_ast_utils *utils)
{
	t_lexer		*lx_tmp;
	t_lexer		*next_lx_tmp;

	if (utils->lexer_root)
	{
		lx_tmp = utils->lexer_root;
		while (lx_tmp)
		{
			next_lx_tmp = lx_tmp->next;
			if (lx_tmp->token == CMD || lx_tmp->token == ARG
				|| lx_tmp-> token == REDIR_FILE)
				free(lx_tmp->content);
			free(lx_tmp);
			lx_tmp = next_lx_tmp;
		}
	}
}

static void	ft_free_parserargs(t_parser_args *root)
{
	t_parser_args	*arg_tmp;
	t_parser_args	*next_arg_tmp;

	if (root)
	{
		arg_tmp = root;
		while (arg_tmp)
		{
			next_arg_tmp = arg_tmp->next;
			free(arg_tmp);
			arg_tmp = next_arg_tmp;
		}
	}
}

static void	ft_free_parser(t_ast_utils *utils)
{
	t_parser		*par_tmp;
	t_parser		*next_par_tmp;

	if (utils->parser_root)
	{
		par_tmp = utils->parser_root;
		ft_close(par_tmp);
		while (par_tmp)
		{
			next_par_tmp = par_tmp->next;
			ft_free_parserargs(par_tmp->tmp_arg);
			ft_free(par_tmp->cmd);
			free(par_tmp);
			par_tmp = next_par_tmp;
		}
	}
}

void	ft_free_utils(t_info *info, bool mode)
{
	if (info->utils)
	{
		ft_free_lexer(info->utils);
		ft_free_parser(info->utils);
		free(info->utils);
		if (mode == true)
			ft_free_env(info->env_root);
	}
}
