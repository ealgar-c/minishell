/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:09:04 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/30 09:10:05 by erivero-         ###   ########.fr       */
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
			return (NULL);
		len++;
	}
	content = ft_substr(str, i, len + 1);
	if (token == ARG)
		content = ft_add_space(str, i + len + 1, content, q);
	return (content);
}