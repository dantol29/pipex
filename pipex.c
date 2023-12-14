/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:05:19 by dtolmaco          #+#    #+#             */
/*   Updated: 2023/12/14 14:31:04 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.tube[1], 1);
	close(pipex.tube[0]);
	dup2(pipex.infile, 0);
	pipex.command = ft_split(argv[2], ' ');
	pipex.command_path = get_path(pipex.splitted_path, pipex.command[0]);
	if (!pipex.command_path)
		free_all(pipex);
	else
		execve(pipex.command_path, pipex.command, envp);
}

void	parent(t_pipex pipex, char **argv, char **envp)
{
	dup2(pipex.tube[0], 0);
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	pipex.command = ft_split(argv[3], ' ');
	pipex.command_path = get_path(pipex.splitted_path, pipex.command[0]);
	if (!pipex.command_path)
		free_all(pipex);
	else
		execve(pipex.command_path, pipex.command, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	check_files(argc, argv);
	pipex.infile = open(argv[1], O_RDONLY);
	pipex.outfile = open(argv[4], O_RDWR);
	pipex.env_path = find_path(envp);
	pipex.splitted_path = ft_split(pipex.env_path, ':');
	pipe(pipex.tube);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	else
		parent(pipex, argv, envp);
	close(pipex.tube[1]);
	close(pipex.tube[0]);
	waitpid(pipex.pid1, NULL, 0);
	return (0);
}
