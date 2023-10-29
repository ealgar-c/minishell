/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:40:28 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/29 12:09:47 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_content(char *str, int i, int token)
{
	char	*content;
	int		len;

	len = 0;
	if (str[i + len] == 34 || str[i + len] == 39)
		content = ft_quote_handling(str, i, len, str[i + len], token);
	else
	{
		while (str[i + len] > 32 && !ft_token_check(str[i + len]) 
			&& str[i + len] != 34 && str[i + len] != 39)
			len++;
		content = ft_substr(str, i, len);
		if (token == ARG)
			ft_add_space(str, i + len, content, '\0');
	}
	return (content);
}

t_lexer	*get_token(char *str, int i, t_ast_utils *utils)
{
	t_lexer	*node;

	if (str[i] == '|')
		node = new_lexer_node("|", PIPE, utils);
	else if (str[i] == '>' && str[i + 1] != '>')
		node = new_lexer_node(">", GREAT, utils);
	else if (str[i] == '>' && str[i + 1] == '>')
		node = new_lexer_node(">>", GREAT_GREAT, utils);
	else if (str[i] == '<' && str[i + 1] != '<')
		node = new_lexer_node("<", LESS, utils);
	else
		node = new_lexer_node("<<", LESS_LESS, utils);
	return (node);
}

/* void print_lexer(t_info *info)
{
	t_lexer	*ptr;
	
	ptr = info->utils->lexer_root;
	while(ptr)
	{
		ft_printf("*** NUEVO NODO ***\n");
		ft_printf("content is: %s\n", ptr->content);
		ft_printf("token is: %i\n", ptr->token);
		ptr = ptr->next;
	}
} */

bool	ft_lexer_list(char *str, int i, t_ast_utils *utils, t_lexer *tmp_node, bool getcmd) //creo que norminette acepta 5 arg por función
{
	while (str[i])
	{
		while (str[i] <= 32 && str[i])
			i++;
		if (!str[i])
			return (true);
		if (ft_token_check(str[i]))
			tmp_node = get_token(str, i, utils);
		else if ((!tmp_node || tmp_node->token == PIPE || getcmd == true))
		{
			tmp_node = new_lexer_node(get_content(str, i, CMD), CMD, utils);
			getcmd = false;
		}
		else if (!ft_check_last_node(utils))
			tmp_node = new_lexer_node(get_content(str, i, ARG), ARG, utils);
		else
		{
			tmp_node = new_lexer_node(get_content(str, i, REDIR_FILE), REDIR_FILE, utils);
			getcmd = true;
		}
		if (tmp_node == NULL)
			return (false);
		i += ft_strlen(tmp_node->content);
	}
	return (true);
}

bool	ft_lexer(char *str, t_info *info)
{
	int			i;
	t_ast_utils	*utils;
	t_lexer		*tmp_node;
	bool		getcmd;
	bool		ret;

	i = 0;
	utils = info->utils;
	tmp_node = NULL; //sin esto en mi portatil petaba y en 42 no me explicas?????
	getcmd = false;
	while (str[i] <= 32 && str[i])
		i++;
	if (!str[i])
		return (false); //ya no hace segmentation fault cuando se le envían solo espacios
	ret = ft_lexer_list(str, i, utils, tmp_node, getcmd);
//	print_lexer(info);
	return (ret);
}
