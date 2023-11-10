/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 15:08:55 by erivero-          #+#    #+#             */
/*   Updated: 2023/11/10 17:37:48 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_error(int error, char *str)
{
	ft_printf("conchita$: ");
	if (error == 1)
		ft_printf("syntax error near unexpected token \'%s\'\n", str);
	if (error == 2)
		ft_printf("%s: No such file or directory\n", str);
	if (error == 3)
		ft_printf("Error while creating a pipe\n");
	if (error == 42)
		ft_printf("%s\n", str);
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