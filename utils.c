/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:03:52 by dtolmaco          #+#    #+#             */
/*   Updated: 2023/12/14 15:00:40 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, str + i, 1);
		i++;
	}
}

void	free_all(t_pipex pipex)
{
	int	i;

	i = 0;
	while (pipex.command[i])
	{
		free(pipex.command[i]);
		i++;
	}
	free(pipex.command);
	i = 0;
	while (pipex.splitted_path[i])
	{
		free(pipex.splitted_path[i]);
		i++;
	}
	free(pipex.splitted_path);
	exit(EXIT_FAILURE);
}

char	*get_path(char **splited_path, char *command)
{
	char	*cmd;
	char	*temp;

	while (*splited_path)
	{
		temp = ft_strjoin(*splited_path, "/");
		cmd = ft_strjoin(temp, command);
		free(temp);
		if (access(cmd, 0) == 0)
			return (cmd);
		free(cmd);
		splited_path++;
	}
	return (NULL);
}

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4) != 0)
		envp++;
	return (*envp + 5);
}

void	check_files(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr("The program takes 4 arguments\n");
		exit(EXIT_FAILURE);
	}
	if (access(argv[1], F_OK) == -1 || access(argv[4], F_OK) == -1)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
	else if (access(argv[1], R_OK) == -1 || access(argv[4], W_OK | R_OK) == -1)
	{
		perror(NULL);
		exit(EXIT_FAILURE);
	}
}
