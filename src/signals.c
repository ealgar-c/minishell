/* typedef struct s_signals
{
	bool	builtin;
	bool	heredoc;
}	t_signals;

t_signals	g_signals; */

void	sigint_handler(int sig)
{
	if (!g_signals->builtin)
	{
		write(1, "\033[K\n", 5);
		rl_replace_line("", 0);
		g_signals->builtin = true;
	}
	else if (g_signals->heredoc)
	{
		write(1, "\033[K\n", ft_strlen("\033[K\n"));
		close(0);
		g_signals->heredoc = false;
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		write(1, "\033[K\n", 5);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
	}
}