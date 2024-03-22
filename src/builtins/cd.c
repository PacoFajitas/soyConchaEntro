/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 22:57:31 by tfiguero          #+#    #+#             */
/*   Updated: 2024/03/22 14:01:58 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_access(t_data *data, char *path)
{
	struct stat	stat;

	lstat(path, &stat);
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(path);
	}
	if (!S_ISDIR(stat.st_mode))
		return (ft_error_ret(data, "cd", "Not a directory", 1));
	if (access(path, X_OK) == -1)
		return (ft_error_ret(data, "cd", "Permission denied", 1));
	return (0);
}

char	*ft_getcwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		return (NULL);
	}
	return (cwd);
}

int	ft_cd_path(t_env **env, t_env **exp, char *path, char *oldpwd)
{
	oldpwd = ft_getcwd();
	if (oldpwd == NULL)
		return (1);
	ft_change_env_value("OLDPWD", oldpwd, exp);
	if (ft_get_env_value(env, "OLDPWD"))
		ft_change_env_value("OLDPWD", oldpwd, env);
	free(oldpwd);
	chdir(path);
	oldpwd = ft_getcwd();
	ft_change_env_value("PWD", oldpwd, env);
	ft_change_env_value("PWD", oldpwd, exp);
	free(oldpwd);
	return (0);
}

int	ft_cd(t_data *data, t_pipe *p, t_env **env, t_env **exp)
{
	char	*oldpwd;
	char	*path;

	oldpwd = NULL;
	if (!p->cmds[1])
		path = ft_get_env_value(env, "HOME");
	else
	{
		path = p->cmds[1];
		if (ft_strlen(path) == 0)
			return (0);
	}
	if (!path)
		return (ft_error_ret(data, "cd", " HOME not set", 1));
	if (path && p->cmds && p->cmds[1] && p->cmds[1][0] == '-')
	{
		path = ft_get_env_value(env, "OLDPWD");
		if (!path || ft_strlen(path) == 0)
			return (ft_error_ret(data, "cd", " OLDPWD not set", 1));
	}
	if (ft_cd_access(data, path))
		return (1);
	if (ft_cd_path(env, exp, path, oldpwd))
		return (1);
	return (0);
}
