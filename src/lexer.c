/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:40:28 by erivero-          #+#    #+#             */
/*   Updated: 2023/11/02 13:41:16 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_content(char *str, int i, int token, t_info *info)
{
	char	*content;
	int		len;

	len = 0;
	if (str[i + len] == 34 || str[i + len] == 39)
	{
		content = ft_quote_handling(str, i, len, str[i + len], token);
		if (!content)
			ft_error_handling(42, "Wrong quotes, please fix", info);
	}
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

bool	ft_lexer_list(char *str, int i, t_info *info, t_lexer *tmp_node, bool getcmd) //creo que norminette acepta 5 arg por función
{
	while (str[i])
	{
		while (str[i] > 0 && str[i] < 33)
			i++;
		if (ft_token_check(str[i]))
			tmp_node = get_token(str, i, info->utils);
		else if ((!tmp_node || tmp_node->token == PIPE || getcmd == true))
		{
			tmp_node = new_lexer_node(get_content(str, i, CMD, info), CMD, info->utils);
			getcmd = false;
		}
		else if (!ft_check_last_node(info->utils))
			tmp_node = new_lexer_node(get_content(str, i, ARG, info), ARG, info->utils);
		else
		{
			tmp_node = new_lexer_node(get_content(str, i, REDIR_FILE, info), REDIR_FILE, info->utils);
			getcmd = true;
		}
		if (tmp_node == NULL)
			return (false);
		i += ft_strlen(tmp_node->content);
		if (!str[i])
			return (true);
	}
	return (true);
}


void ft_lexer(char *str, t_info *info)
{
	int			i;
	t_lexer		*tmp_node;
	bool		getcmd;
	bool		ret = true;
	char		*line;

	i = 0;
	tmp_node = NULL; //sin esto en mi portatil petaba y en 42 no me explicas?????
	getcmd = false;
	line = ft_strtrim(str, " ");
	g_signals.error = false;
	if (!line[i])
		ft_error_handling(0, NULL, info);
	if (line[i] == '|' || line[ft_strlen(line) - 1] == '|')
		ft_error_handling(1, "|", info);
	else if (!g_signals.error)
		ret = ft_lexer_list(line, i, info, tmp_node, getcmd);
	else if(!ret)
		ft_error_handling(0, NULL, info);
	tmp_node = info->utils->lexer_root;
	if (tmp_node->token > 1 && tmp_node->token < 7 && !tmp_node->next) // si lo primero es redir y no hay nada después
		ft_error_handling(1, "newline", info);
	free(line);
//	print_lexer(info);
}
