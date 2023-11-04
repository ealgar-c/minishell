/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:17:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/04 13:22:30 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_lexer(t_ast_utils *utils)
{
	t_lexer		*lx_tmp;
	t_lexer		*next_lx_tmp;

	if (utils->lexer_root)
	{
		lx_tmp = utils->lexer_root;
		while (lx_tmp)
		{
			next_lx_tmp = lx_tmp->next;
			if (lx_tmp->token == CMD || lx_tmp->token == ARG || lx_tmp-> token == REDIR_FILE)
				free(lx_tmp->content);
			free(lx_tmp);
			lx_tmp = next_lx_tmp;
		}
	}
}

void	ft_free_parserargs(t_parser_args *root)
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

void	ft_free_parser(t_ast_utils *utils)
{
	t_parser		*par_tmp;
	t_parser		*next_par_tmp;

	if (utils->parser_root)
	{
		par_tmp = utils->parser_root;
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

void	ft_free_env(t_env *root)
{
	t_env	*env_tmp;
	t_env	*next_env_tmp;

	if (root)
	{
		env_tmp = root;
		while (env_tmp)
		{
			next_env_tmp = env_tmp->next;
			free(env_tmp->name);
			free(env_tmp->value);
			free(env_tmp);
			env_tmp = next_env_tmp;
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
		{
			ft_free_env(info->env_root);
			//free(info);
		}
	}
}

void	ft_free(char **str)
{
	char	**ptr;

	if (!str)
		return ;
	ptr = str;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(str);
}
