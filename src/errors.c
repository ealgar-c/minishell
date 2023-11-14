/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:08:55 by erivero-          #+#    #+#             */
/*   Updated: 2023/11/14 13:43:08 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_error(int error, char *str)
{
	ft_printf("\033[0;33mconchita: \033[0m");
	if (error == 1)
	{
		printf("\033[0;33msyntax error \033[0m");
		printf("\033[0;33mnear unexpected token '%s'\n\033[0m", str);
	}
	if (error == 2)
		ft_printf("\033[0;33m%s: No such file or directory\n\033[0m", str);
	if (error == 3)
		ft_printf("\033[0;33mError while creating a pipe\n\033[0m");
	if (error == 42)
		ft_printf("\033[0;33m%s\n\033[0m", str);
}

void	ft_error_handling(int error, char *str, t_info	*info)
{
	if (error)
		ft_print_error(error, str);
	ft_free_utils(info, false);
	info->exit_status = 258;
	info->error = true;
}

/* error = 0 -> sin mensaje
error = 1 -> syntax error 
error = 2 -> No such file or directory
error = 42 -> Mensaje personalizado */