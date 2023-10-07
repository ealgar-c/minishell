/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:40:28 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/07 11:42:34 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	ft_token_check(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

char	*ft_quote_handling(char *str, int i, int len)
{
	char	*content;

	while (str[i + len] != '"')
	{
		if (str[i + len] == '\0')
		{
			ft_printf("Wrong quotes, please fix\n");
			return (NULL);
// el return no está bien gestionado, habría que salir del todo, con una nueva promt
		}
		len++;
	}
//	content = ft_substr(str, i + 1, len - 1); //+1 y -1 para que omita las comillas
	content = ft_substr(str, i, len);
// no puedo quitarle las comillas aquí pq si no se jodería al aumentar i en el lexer con i+=strlen
	return (content);
}

char	*get_content(char *str, int i)
{
	char	*content;
	int		len;

	len = 0;
	if (str[i + len] == '"')
		content = ft_quote_handling(str, i, len);
	else
	{
		while (str[i + len] > 32 && !ft_token_check(str[i + len]))
			len++;
		content = ft_substr(str, i, len);
	}
	return (content);
}

//no estoy liberando content, habría que hacerlo en la función ppal
t_lexer	*get_token(char *str, int i, t_ast_utils *utils)
{
	t_lexer	*node;

	if (str[i] == '|')
		node = new_lexer_node("|", PIPE, utils);
	else if (str[i] == '>' && str[i + 1] != '>')
		node = new_lexer_node(">", GREAT, utils);
	else if (str[i] == '>' && str[i + 1] == '>') //añadir condición pa que no haya >>>?
		node = new_lexer_node(">>", GREAT_GREAT, utils);
	else if (str[i] == '<' && str[i + 1] != '<')
		node = new_lexer_node("<", LESS, utils);
	else
		node = new_lexer_node("<", LESS_LESS, utils);
	return(node);
}

void	ft_lexer(char *str, t_info *info)
{
	int			i;
	t_ast_utils	*utils;
	t_lexer		*tmp_node;

	i = 0;
	utils = info->utils;
	while (str[i])
	{
		while (str[i] <= 32)
			i++;
		if (!tmp_node || tmp_node->token == PIPE)
			tmp_node = new_lexer_node(get_content(str, i), CMD, utils);
		else if (ft_token_check(str[i]))
			tmp_node = get_token(str, i, utils);
		else if (!ft_check_last_node(utils))
			tmp_node = new_lexer_node(get_content(str, i), ARG, utils);
		else
			tmp_node = new_lexer_node(get_content(str, i), REDIR_FILE, utils);
		i += ft_strlen(tmp_node->content);
	}
}
