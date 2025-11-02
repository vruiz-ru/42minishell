/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:50:12 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/02 19:36:48 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_exit(t_process *process)
{
	free_process(process);
	rl_clear_history();
	ft_putstr_fd("exit\n", 1);
	process->exit_status = 0;
	exit(EXIT_SUCCESS);
	return (1);
}