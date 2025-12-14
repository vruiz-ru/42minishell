/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vruiz-ru <vruiz-ru@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:50:39 by vruiz-ru          #+#    #+#             */
/*   Updated: 2025/12/14 12:50:59 by vruiz-ru         ###   ########.fr       */
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
