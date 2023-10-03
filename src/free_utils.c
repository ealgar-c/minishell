/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:17:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/03 15:47:29 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_utils(t_ast_utils *utils)
{
	t_lexer		*lx_tmp;
	t_lexer		*next_lx_tmp;
	t_parser	*par_tmp;
	t_parser	*next_par_tmp;

	if (utils->lexer_root)
	{
		lx_tmp = utils->lexer_root;
		while (lx_tmp)
		{
			next_lx_tmp = lx_tmp->next;
			free(lx_tmp);
			lx_tmp = next_lx_tmp;
		}
	}
	if (utils->parser_root)
	{
		par_tmp = utils->parser_root;
		while (par_tmp)
		{
			next_par_tmp = par_tmp->next;
			free(par_tmp);
			par_tmp = next_par_tmp;
		}
	}
	free(utils);
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
