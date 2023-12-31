/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:02:56 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/29 11:18:30 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret_str;
	size_t	len;
	int		i;
	int		a;

	i = 0;
	a = 0;
	len = ((size_t)ft_strlen(s1) + (size_t)ft_strlen(s2));
	ret_str = (char *)malloc(((len + 1) * sizeof(char)));
	if (!ret_str)
		return (NULL);
	while (s1[i])
	{
		ret_str[i] = s1[i];
		i++;
	}
	while (s2[a])
	{
		ret_str[i + a] = s2[a];
		a++;
	}
	ret_str[i + a] = '\0';
	return (ret_str);
}
