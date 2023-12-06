#ifndef MINITALK_H
# define MINITALK_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>

# ifndef SLEEP_TIME
#  define SLEEP_TIME 100
# endif

int		ft_printf(const char *str, ...);
int		ft_atoi(const char *nptr);
int		*atob(char c);
char	btoa(int bin[8]);
void	signal_handler_server(int sig, siginfo_t *info, void *context);
void	send_signal(pid_t server_pid, int bin[8]);
void	signal_handler_client(int sig);

#endif
