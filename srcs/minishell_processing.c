#include "../minishell.h"

int	var_len_diff(t_var *var, char *str)
{
	int		i;
	int		len;
	char	*var_name;

	i = 1;
	var_name = ft_strdup(str + 1);
	if (!var_name)
		ms_exit(var, ms_perror("", "malloc fail()", "", errno));
	while (ft_isalnum(var_name[i]))
		i++;
	var_name[i] = '\0';
	len = ft_strlen(get_env_var(var, var_name)) - ft_strlen(var_name);
	free(var_name);
	return (len - 1);
}

char	*var_finder(t_var *var, char *str)
{
	int		i;
	char	*var_name;
	char	*content;

	i = 1;
	var_name = ft_strdup(str + 1);
	if (!var_name)
		ms_exit(var, ms_perror("", "malloc fail()", "", errno));
	while (ft_isalnum(var_name[i]))
		i++;
	var_name[i] = '\0';
	content = get_env_var(var, var_name);
	free(var_name);
	return (content);
}

int	new_token_size(t_var *var, char *token)
{
	int	len;
	int	i;

	len = ft_strlen(token);
	i = 0;
	if (token[0] == '\'')
		return (len - 2);
	else if (token[0] == '"')
		len -= 2;
	while (token[i])
	{
		if (token[i] == '$' && (ft_isalpha(token[i + 1]) || token[i + 1] == '_'))
			len += var_len_diff(var, token + i);
		i++;
	}
	return (len);
}

char	*token_builder(t_var *var, char *token)
{
	char	*new_token;
	char	*tmp;
	int		len;
	int		i;
	int		j;

	len = new_token_size(var, token);
	new_token = (char *)malloc(sizeof(char) * (len + 1)); //NOTE: do something for malloc failure
	if (!new_token)
		return (NULL);
	i = 0;
	j = 0;
	if (token[0] == '\'' || token[0] == '"')
		j++;
	if (token[0] == '\'')
		while (i < len)
			new_token[i++] = token[j++];
	while (i < len)
	{
		if (token[j] == '$' && (ft_isalpha(token[j + 1]) || token[j + 1] == '_'))
		{
			tmp = var_finder(var, token + j);
			i += ft_strlcpy(new_token + i, tmp, ft_strlen(tmp) + 1);
			j++;
			while (ft_isalnum(token[j]) || token[j] == '_')
				j++;
			continue ;
		}
		else
			new_token[i] = token[j];
		i++;
		j++;
	}
	new_token[i] = '\0';
	return (new_token);
}

char	**expand_cmd(t_var *var, char **cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (cmd[i])
	{
		tmp = cmd[i];
		cmd[i] = token_builder(var, cmd[i]);
		if (!cmd[i])
			ms_exit(var, 1);//NOTE: do something for malloc failure
		free(tmp);
		i++;
	}
	return (cmd);
}

_Bool	ms_cmd_expander(t_var *var)
{
	int		i;

	i = 0;
	while(var->cmds[i])
	{
		var->cmds[i] = expand_cmd(var, var->cmds[i]); 
		i++;
	}
	return false;
}