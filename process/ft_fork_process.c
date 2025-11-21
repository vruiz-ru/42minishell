/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergut <aghergut@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 10:36:15 by aghergut          #+#    #+#             */
/*   Updated: 2025/11/09 17:01:30 by aghergut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/* 1. Función para aplicar dup2: conecta los tubos */
static void apply_redirections(t_cmd *cmd)
{
    // Input Redirection (<)
    if (cmd->fd_in != 0) // Si no es el teclado
    {
        if (cmd->fd_in < 0)
            exit(1); // Error previo al abrir
        dup2(cmd->fd_in, STDIN_FILENO); // STDIN ahora es el archivo
        close(cmd->fd_in);
    }

    // Output Redirection (>, >>)
    if (cmd->fd_out != 1) // Si no es la pantalla
    {
        // ¡AQUÍ ESTABA EL PROBLEMA ANTES!
        // Decimos: "Quiero que el STDOUT (1) apunte a donde apunta fd_out (3)"
        dup2(cmd->fd_out, STDOUT_FILENO);
        close(cmd->fd_out); // Cerramos el 3 porque ya lo hemos clonado en el 1
    }
}

/* 2. Cierra los FDs en el padre para evitar leaks */
static void close_fds(t_cmd *cmd)
{
    if (cmd->fd_in != 0)
        close(cmd->fd_in);
    if (cmd->fd_out != 1)
        close(cmd->fd_out);
}

/* 3. Ejecuta comando externo */
static void ft_execute_external(t_process *process, t_cmd *cmd)
{
    char *path;

    path = ft_get_cmd_path(cmd->args[0], process->envs->parent_env);
    if (!path)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(cmd->args[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        exit(127);
    }
    if (execve(path, cmd->args, process->envs->parent_env) == -1)
    {
        perror("execve error");
        free(path);
        exit(1);
    }
}

/* 4. Función Principal */
int ft_fork_process(t_process *process)
{
    t_cmd   *cmd;
    int     status;

    cmd = process->commands;
    if (!cmd || !cmd->args)
        return (0);

    process->pid = fork();
    if (process->pid < 0)
        return (perror("fork failed"), 0);

    // --- PROCESO HIJO ---
    if (process->pid == 0)
    {
        // 1. ¡IMPORTANTE! Cambiamos la salida ANTES de ejecutar
        apply_redirections(cmd); 
        
        // 2. Ahora 'ls' creerá que escribe en pantalla, pero escribe en el archivo
        ft_execute_external(process, cmd);
    }
    
    // --- PROCESO PADRE ---
    // Esperamos al hijo
    waitpid(process->pid, &status, 0);
    
    // ¡IMPORTANTE! Cerrar el archivo en el padre también, si no se queda abierto
    close_fds(cmd);

    if (WIFEXITED(status))
        process->status = WEXITSTATUS(status);
    
    return (1);
}


/*
int	ft_fork_process(t_process *process, int(*built_f)(t_process *))
{
	int	status;

	if (!ft_isbuiltin(process))
		return (0);
	process->pid = fork();
	if (process->pid < 0)
		return (perror("fork"), exit(EXIT_FAILURE), 0);
	if (process->pid == 0)
	{
		if (built_f(process))
			exit(EXIT_SUCCESS);
		exit(EXIT_FAILURE);
	}
	if (waitpid(process->pid, &status, 0) < 0)
		return (perror("waitpid"), exit(EXIT_FAILURE), 0);
	if (WIFEXITED(status))
		process->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		process->status = 128 + WTERMSIG(status);
	else if (WIFSIGNALED(status))
		process->status = 128 + WIFSTOPPED(status);
	return(1);
}*/
