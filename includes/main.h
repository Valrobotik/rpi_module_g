#ifndef MAIN_H
# define MAIN_H

# include "libft.h"

# include <unistd.h>
# include <poll.h>
# include <bcm2835.h>
# include <termios.h>
# include <stdlib.h>

# define GNL_BUFF_SIZE	2048

# define PINOUT		21
# define PINREED	27
# define PINRESET	22
# define PINSIDE	11

# define B_SIDE		0
# define Y_SIDE		1

# define STOP_TIME	98 	//prevoir une secu, genre 95/100

# define SIDE	4
# define REED	3
# define RESET	2		//1 is reserved for static initialisation

struct pollfd 	g_fds[1];
int		g_fd;
int		g_wr;
int		g_rd;
int		g_flag;
int		g_side;
clock_t		g_time_start;


	/* chained list, containing a status (in process or not procceded) and a command  */
typedef struct		s_pile
{
	struct s_pile	*next;
	char		*cmd;
	int		status;
	int		move;
	double		x;
	double		y;
	double		a;
	double		time;

}			t_pile;

/*	FONCTION REAL CONDITIONS 	*/

int	start_robot(void);
int	do_flag(char *str, int argc, char **argv);
int	real_condition(void);

/*	FONCTION RISE & FALL		*/

int	detect_rising(int value, int elmt);
int	detect_falling(int value, int elmt);

/*	FONCTION PILE HUNDLER		*/

t_pile	*build_pile(void);
int	unpile_cmd(t_pile **pile);
void	get_resp(struct pollfd fds[1], int fd);
//int 	wait_tirette(void);

/*	SETUP FONCTION			*/

int	set_interface_attribs(int fd, int speed, int parity);
void	setup_flag(void);
#endif
