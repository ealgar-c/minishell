/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:40:28 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/23 18:12:04 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	ft_token_check(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

char	*ft_add_space(char *str, int s, char *content, char q)
{
	int	i;

	i = s;
	while (str[i] && str[i] <= 32)
		i++;
	if (!str[i])
		return (content);
	if (str[s] == ' ')
	{
		if (q != '\0')
		{
			content[ft_strlen(content) - 1] = ' ';
			content[ft_strlen(content)] = q;
		}
		else
			content[ft_strlen(content)] = ' ';
	}
	return (content);
}

char	*ft_quote_handling(char *str, int i, int len, char q, int token)
{
	char	*content;

	len++;
	while (str[i + len] != q)
	{
		if (str[i + len] == '\0')
		{
			ft_printf("Wrong quotes, please fix\n");
			return (NULL);
		}
		len++;
	}
	content = ft_substr(str, i, len + 1);
	if (token == ARG)
		content = ft_add_space(str, i + len + 1, content, q);
	return (content);
}

char	*get_content(char *str, int i, int token)
{
	char	*content;
	int		len;

	len = 0;
	if (str[i + len] == 34 || str[i + len] == 39)
		content = ft_quote_handling(str, i, len, str[i + len], token);
	else
	{
		while (str[i + len] > 32 && !ft_token_check(str[i + len]))
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
		node = new_lexer_node("<", LESS_LESS, utils);
	return (node);
}

bool	ft_lexer(char *str, t_info *info)
{
	int			i;
	t_ast_utils	*utils;
	t_lexer		*tmp_node;

	i = 0;
	utils = info->utils;
	tmp_node = NULL; //sin esto en mi portatil petaba y en 42 no me explicas?????
	while (str[i])
	{
		while (str[i] <= 32 && str[i])
			i++;
		if (!str[i])
			return (true);
		if (!tmp_node || tmp_node->token == PIPE)
			tmp_node = new_lexer_node(get_content(str, i, CMD), CMD, utils);
		else if (ft_token_check(str[i]))
			tmp_node = get_token(str, i, utils);
		else if (!ft_check_last_node(utils))
			tmp_node = new_lexer_node(get_content(str, i, ARG), ARG, utils);
		else
			tmp_node = new_lexer_node(get_content(str, i, REDIR_FILE), REDIR_FILE, utils);
		if (tmp_node == NULL)
			return (false);
		i += ft_strlen(tmp_node->content);
	}
	return (true);
}
