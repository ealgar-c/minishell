/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extend_and_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:11:25 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/10 10:18:37 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_quote_handling(char *str, char *prev, int i, t_info *info)
{
	char	*content;
	int		len;
	char	q;

	len = 1;
	q = str[i];
	while (str[i + len] && str[i + len] != q)
		len++;
	if (!str[i + len])
	{
		ft_error_handling(42, "Wrong quotes, please fix", info);
		return (free(prev), NULL);
	}
	if (len - i > 0) // si hay algo entre las comillas
		content = check_extensor(ft_substr(str, i + 1, len - 1), info, q);
	else // dice enrique que hay que alojar el nulo
		content = ft_strdup(NULL);
	if (prev)
	{
//		ft_printf("Q_h PREV was: %s, content was: %s\n", content);
		content = ft_strjoin(prev, content);
		free(prev);
	}
//	ft_printf("after quote_h: %s\n", content);
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
//		ft_printf("cont_h PREV was: %s, content was: %s\n", content);
		content = ft_strjoin(prev, content);
		free(prev);
	}
//	ft_printf("cont_h after joinin: %s\n", content);
	return (content);
}

char	*update_prev(char *prev, char *content) {
    char *temp = prev;
    if (prev) {
        prev = ft_strjoin(prev, content);
        free(temp);
    } else {
        prev = ft_strdup(content);
    }
    free(content);
    return prev;
}

char	*ft_join_content(char *str, t_info *info) {
    char *cmd = NULL;
    int i = 0;

    while (str[i] && !info->error) 
	{
        char *prev = cmd;
        char *content = NULL;

        if (str[i] == 34 || str[i] == 39) {
            content = ft_quote_handling(str, NULL, i, info);
            i += 2; // Saltar la comilla y avanzar
        } else {

/*             while (str[j] && str[j] != 34 && str[j] != 39)
                j++; */
            content = ft_content_handling(str, NULL, i, info);
            i += ft_strlen(content);
        }

        cmd = update_prev(prev, content);
        i++;
    }

    free(str);
    return cmd;
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