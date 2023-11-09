/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 12:09:04 by erivero-          #+#    #+#             */
/*   Updated: 2023/11/09 09:24:10 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	ft_token_check(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

int	loop_check(char c, bool *quote, char q)
{

	if (!*quote)
	{
		if (c == 0 || c == 32 || ft_token_check(c))
			return (0);
		if (c == 34 || c == 39)
			*quote = true;
	}
	else
	{
		if (c == q)
			*quote = false;
		if (c == 0)
			return (0);
	}
	return (1);
}

char	*get_content(char *str, int i, t_info *info)
{
	int		len;
	bool	quote;
	char	q;

	len = 0;
	q = 42;
	quote = false;
	(void)info;
	while (loop_check(str[i + len], &quote, q))
	{
		if (str[i + len] == 39 || str[i + len] == 34)
		{
			q = str[i + len];
			quote = true;
		}
		len++;
	}
//	ft_printf("content after get_content is: \'%s\'n\", ft_substr(str, i, len));
	return (ft_substr(str, i, len));
}
