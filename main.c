/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:50:39 by aghergut          #+#    #+#             */
/*   Updated: 2025/12/12 21:51:00 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

int	g_signal_status = 0;

int	main(int argc, char *argv[], char *envp[])
{
	t_process	*process;

	if (argc > 1)
		return (0);
	process = NULL;
	if (!ft_init_parent(&process, argv[0], envp))
		return (0);
	ft_shell_loop(process);
	return (0);
}
