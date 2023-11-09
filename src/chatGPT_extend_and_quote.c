/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_and_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:11:25 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/09 11:28:53 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*update_prev(char *prev, char *content)
{
	char	*temp;

	temp = prev;
	if (prev)
	{
		prev = ft_strjoin(prev, content);
		free(temp);
	}
	else
		prev = ft_strdup(content);
	free(content);
	return (prev);
}

char	*ft_quote_handling(char *str, int i, t_info *info)
{
	char	*content;
	int		len;
	char	q;

	len = 1;
	q = str[i];
	ft_printf("index before: %i\n", i);
	while (str[i + len] && str[i + len] != q)
		len++;
	ft_printf("index after: %i\n", i + len);
	if (!str[i + len])
	{
		ft_error_handling(42, "Wrong quotes, please fix", info);
		return (NULL);
	}
	if (len - i > 0) // si hay algo entre las comillas
		content = check_extensor(ft_substr(str, i + 1, len - 1), info, q);
	else // dice enrique que hay que alojar el nulo
		content = ft_strdup(NULL);
	return (content);
}

char	*ft_content_handling(char *str, int i, t_info *info)
{
	char	*content;
	int		len;

	len = 0;
	while (str[i + len] && str[i + len] != 34 && str[i + len] != 39)
		len++;
	content = check_extensor(ft_substr(str, i, len), info, str[i]);
	return (content);
}

char	*ft_join_content(char *str, t_info *info)
{
	char	*cmd;
	char	*prev;
	char	*tmp;
	int		i;

	i = 0;
	cmd = NULL;
	while (str[i] && !info->error)
	{
		prev = cmd;
		tmp = NULL;
		if (str[i] == 34 || str[i] == 39) {
			tmp = ft_quote_handling(str, i, info);
			i += 2; // Saltar la comilla y avanzar
		}
		else
		{
			tmp = ft_content_handling(str, i, info);
			i += ft_strlen(tmp);
		}
		cmd = update_prev(prev, tmp);
		i++;
	}
	free(str);
	return (cmd);
}


void	ft_extend_and_quotes(char **cmd, t_info *info)
{
	int		j;

	j = 0;
	while (cmd[j] && !info->error)
	{
		cmd[j] = ft_join_content(cmd[j], info);
//		ft_printf("cmd[j] is: %s\n", cmd[j]);
		j++;
	}
}