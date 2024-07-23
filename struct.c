/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   struct.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: irene <irgonzal@student.42madrid.com>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/05/30 21:50:39 by pablo			 #+#	#+#			 */
/*   Updated: 2024/07/14 14:03:25 by irene			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

void	*ft_free_env(char **env)
{
	int	i;

	i = -1;
	if (!env)
		return (NULL);
	while (env[++i])
		free(env[i]);
	//*env = NULL;
	free(env);
	return (NULL);
}

static char	**ft_copy_env(char **envp)
{
	char	**env_copy;
	int		i;
	int		total_variables;

	total_variables = 0;
	while (envp[total_variables])
		total_variables++;
	env_copy = (char **)malloc((total_variables + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (i < total_variables)
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (!env_copy[i])
			return (ft_free_env(env_copy));
		i++;
	}
	env_copy[total_variables] = NULL;
	return (env_copy);
}

void	ft_init_mix(t_mix *data, char **envp)
{
	data->exit_status = 0;
	data->m_env = NULL;
	data->heredocs = NULL;
	data->pipesfd = NULL;
	data->m_env = ft_copy_env(envp);
}

//pasamos los datos a la struct
/*
void	ft_fill_struct(t_mix *data, char **envp)
{
	data->m_env = ft_copy_env(envp);
}*/
