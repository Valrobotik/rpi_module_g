#include <unistd.h>
#include "libft.h"
#include <math.h>
#include <stdlib.h>

void ftoa(float f, char *str, int precision)
{
  	float decimals;
	int i, j, divisor = 1;
	int8_t log_f;
	int32_t int_digits = (int)f;             //store the integer digits
	char *s1;

	if (f < 0) {                             //if a negative number 
		str[0] = '-';                          //start the char array with '-'
		f = abs(f);                            //store its positive absolute value
	}
	log_f = ceil(log10(f));                  //get number of digits before the decimal
	if (log_f > 0) {                         //log value > 0 indicates a number > 1
		if (log_f == precision) {              //if number of digits = significant figures
			f += 0.5;                            //add 0.5 to round up decimals >= 0.5
			s1 = ft_itoa(f);                     //itoa converts the number to a char array
			ft_strcat(str, s1);                     //add to the number string
		}
		else if ((log_f - precision) > 0) {    //if more integer digits than significant digits
			i = log_f - precision;               //count digits to discard
			divisor = 10;
			for (j = 0; j < i; j++) divisor *= 10;    //divisor isolates our desired integer digits 
			f /= divisor;                             //divide
			f += 0.5;                            //round when converting to int
			int_digits = (int)f;
			int_digits *= divisor;               //and multiply back to the adjusted value
			s1 = ft_itoa(int_digits);
			ft_strcat(str, s1);
		}
		else {                                 //if more precision specified than integer digits,
			s1 = ft_itoa(int_digits);            //convert
			ft_strcat(str, s1);                     //and append
		}
	}

	else {                                   //decimal fractions between 0 and 1: leading 0
		ft_strcat(str, "0");
	}
	if (log_f < precision) {                 //if precision exceeds number of integer digits,
		decimals = f - (int)f;                 //get decimal value as float
		strcat(str, ".");                      //append decimal point to char array

		i = precision - log_f;                 //number of decimals to read
		for (j = 0; j < i; j++) {              //for each,
			decimals *= 10;                      //multiply decimals by 10
			if (j == (i-1)) decimals += 0.5;     //and if it's the last, add 0.5 to round it
			s1 = ft_itoa((int)decimals);         //convert as integer to character array
			strcat(str, s1);                     //append to string
			decimals -= (int)decimals;           //and remove, moving to the next
		}
	}
}
