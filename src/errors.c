/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:08:55 by erivero-          #+#    #+#             */
/*   Updated: 2023/11/13 13:21:33 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_error(int error, char *str)
{
	ft_printf("\033[38;5;208mconchita$: \033[0m");
	if (error == 1)
	{
		printf("\033[38;5;208msyntax error \033[0m");
		printf("\033[38;5;208mnear unexpected token '%s'\n\033[0m", str);
	}
	if (error == 2)
		ft_printf("\033[38;5;208m%s: No such file or directory\n\033[0m", str);
	if (error == 3)
		ft_printf("\033[38;5;208mError while creating a pipe\n\033[0m");
	if (error == 42)
		ft_printf("\033[38;5;208m%s\n\033[0m", str);
}

void	ft_error_handling(int error, char *str, t_info	*info)
{
	if (error)
		ft_print_error(error, str);
	ft_free_utils(info, false);
	info->error = true;
}

/* error = 0 -> sin mensaje
error = 1 -> syntax error 
error = 2 -> No such file or directory
error = 42 -> Mensaje personalizado */