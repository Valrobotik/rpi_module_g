#ifndef LIDAR_H
# define LIDAR_H
# include "main.h"
# include <time.h>
# include <poll.h>
# include <termios.h>

# define LIDAR_BUFF 6000 //dix fois trop grand pour l'essai
# define NBR_VAL 682

# define READ_BUFF	200

# define WIN_HEIGHT 600
# define WIN_WIDTH 1200

# define CMD_INF "MD0044072501000\n" //command used to do infinite resp, terminated by QT\n command


char		g_buff[LIDAR_BUFF];
int		*g_range;
int		g_size;

/*	DECODE FUNCTION 		*/

//	find command, and srip it
char	*cmd_finder(char *str, int *pos);
//	find command and wait till it's the right one, and srip it
int	cmd_finder_name(char *str, int *pos, char *cmd);
//	find second element which is the status, and strip it
char	*scnd_finder(char *str, int *pos);
//	find the time stamp and strip it
char	*time_finder(char *str, int *pos);
//	find the code and decode (call decoder) it into the buffer
char	*code_finder(char *str, int *pos);
//	decode the data field (and might be inproved to check)
int	code_decode(char *str, int *pos, int nb);
//	decode 2 or 3 byte according to the lidar encodage into an int
int	decode(const char code[], int nbr_bytes);

/*	NEW LIB FUNCTION		*/

void	ft_print_digit(int *range, int size);
void	ft_print_digit_fd(int fd, int *range, int size);
int	fct_print(char buffer[READ_BUFF]);
void	led_stop(void);
int	fct_decod_resp(void);
int	fct_decod_resp_name(char *cmd);

/*	DISPLAY FUNCTION		*/

//	display x function theta
void	linear_display(void);
//	display x function theta in polar
void	polar_display(double start, double end);
//	Main of the display element
int	display(int argc, char **argv);
//	Pre made forms, could be deleted
void	form_bat(void);
void	form_tri(void);

/*	COMMUNICATION FUNCTION		*/

int	open_serial(void);
int	lidar_write(char *word, int fd);
int	lidar_read(char *buffer[4096], int fd);

	/* aquisition function used to get the information sent by Lidar 
	 * try: will check if something is to be read or left
	 * 	otherwise it will continue until someting is to be read
	 * 	return wether it succed or not
	 * print: */

void	lidar_get_resp(struct pollfd fds[1], int fd);
int	lidar_try_get_resp(struct pollfd fds[1], int fd);
void	lidar_get_resp_print(struct pollfd fds[1], int fd);
int	lidar_try_get_resp_print(struct pollfd fds[1], int fd);

int	lidar_cmd_is_premade(char buffer[READ_BUFF]);
#endif
