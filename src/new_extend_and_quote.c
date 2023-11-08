/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_and_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:11:25 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/08 16:10:50 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* char	*clean_quotes(char *str)
{
	char	*clean;

	clean = ft_substr(str, 1, ft_strlen(str) - 2);
	return (free(str), clean);
}

char	*clean_quotes(char *str)
{
	char	*clean;

	clean = ft_calloc(ft_strlen(str) - 2);
	while (*str)
	{
		if ()
		*clean++ = *str++;
	}
	return (free(str), clean);
}

int	check_quotes(char *cmd)
{
	if (cmd[0] == 34)
		return (DOUBLE);
	else if (cmd[0] == 39)
		return (SINGLE);
	return (NONE);
}

void	ft_extend_and_quote(char **cmd, t_info *info)
{
	int			i;
	int			quoted;

	i = 0;
	while (cmd[i])
	{
		quoted = check_quotes(cmd[i]);
		if (quoted != NONE)
			cmd[i] = clean_quotes(cmd[i]);
		cmd[i] = check_extensor(cmd[i], info, quoted);
		i++;
	}
} */

char	*ft_quote_handling(char *str, char *prev, int i, t_info *info)
{
	char	*content;
	int		len;
	char	q;

	len = 1;
	q = str[i];
	ft_printf("character check: %c\n", q);
	while (str[i + len] != q)
		len++;
	if (len - i > 0) // si hay algo entre las comillas
		content = check_extensor(ft_substr(str, i + 1, len - 1), info, q);
	else // dice enrique que hay que alojar el nulo
		content = ft_strdup(NULL);
	if (prev)
	{
		content = ft_strjoin(prev, content);
		free(prev);
	}
	ft_printf("after quote_h: %s\n", content);
	return (content);
}

char	*ft_content_handling(char *str, char *prev, int i, t_info *info)
{
	char	*content;
	int		len;

	len = 0;
	while (str[i + len] && str[i + len] != 34 && str[i + len] != 39)
		len++;
	content = check_extensor(ft_substr(str, i, len), info, str[i]);
	if (prev)
	{
		content = ft_strjoin(prev, content);
		free(prev);
	}
	ft_printf("after cont_h: %s\n", content);
	return (content);
}

char	*ft_join_content(char *str, t_info *info)
{
	char	*cmd;
	char	*prev;
	int		i;

	i = 0;
	prev = NULL;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			cmd = ft_quote_handling(str, prev, i, info);
			i += 2;
		}
		else
			cmd = ft_content_handling(str, prev, i, info);
		i += ft_strlen(cmd);
	}
	return (free(str), cmd);
}

void	ft_extend_and_quote(char **cmd, t_info *info)
{
	int		j;

	j = 0;
	while (cmd[j])
	{
		cmd[j] = ft_join_content(cmd[j], info);
		ft_printf("cmd[j] is: %s\n", cmd[j]);
		j++;
	}
}
