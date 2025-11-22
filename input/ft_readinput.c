/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readinput.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:35:16 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 14:38:10 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

extern int g_signal_status;

void	ft_readinput(t_process *process)
{
	process->prompt->display = ft_prompt(process);
	if (process->prompt->display == NULL)
	{
        perror("malloc");
        exit(EXIT_FAILURE);
    }
	// 1. Leemos (readline se bloquea aquí esperando al usuario)
	process->line = readline(process->prompt->display);
	// 2. ¡AQUÍ! Justo al despertar, miramos si fue por Ctrl+C
	// CASO 1: Ctrl+C ocurrió mientras esperábamos
	if (g_signal_status != 0)
	{
		process->status = g_signal_status; // Actualizamos $? a 130
		g_signal_status = 0;               // Reseteamos
	}
	// CASO 2: Ctrl+D (EOF) -> Salimos del shell
	if (process->line == NULL)
	{
		ft_putstr_fd("exit\n", 1); // Bash imprime "exit" al salir por EOF
		exit(process->status);     // Salimos con el último estado conocido
	}
	// CASO 3: Línea vacía -> No hacemos nada (vuelve al bucle, status se conserva)
	if (*(process->line) == '\0')
		return ;
	add_history(process->line);
	// 3. Ahora sí parseamos (y $? ya valdrá 130 si hubo señal)
	ft_parse_line(process);
}
