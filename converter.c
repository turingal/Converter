#define USAGE "Usage: tconvert TEMP [SCALE]\n\nWhere SCALE can be\n  C\tConvert from Celsius\n  F\tConvert from Fahrenheit\n  K\tConvert from Kelvin\n\nLeave blank to use all scales\n"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

float convert_c_f(float c);

float convert_c_k(float c);

float convert_f_c(float f);

float convert_k_c(float k);

float convert_k_f(float k);

float convert_f_k(float f);

int is_temperature_correct(float t, char c);

void convert_from_c(float t);

void convert_from_f(float t);

void convert_from_k(float t);

int wrong_scale_error();

int main(int argc, char *argv[]){
	float input_temp;
	char *input_scale_char;

	if (argc < 2 || argc >  3){
		printf(USAGE);
		return 0;
	}

	input_temp = atof(argv[1]);  // 0.0 if number was not found

	if (argc == 2){
		printf(  "C: %.2f\n", input_temp);
		convert_from_c(input_temp);
		printf("\nF: %.2f\n", input_temp);
		convert_from_f(input_temp);
		printf("\nK: %.2f\n", input_temp);
		convert_from_k(input_temp);
	}
	else if (argc == 3){
		input_scale_char = argv[2];

		if (strlen(input_scale_char) != 1) return wrong_scale_error();

		switch(tolower(input_scale_char[0])){
			case 'c':
				convert_from_c(input_temp);
				break;
			case 'f':
				convert_from_f(input_temp);
				break;
			case 'k':
				convert_from_k(input_temp);
				break;

			default: return wrong_scale_error();
		}
	}
	return 0;
}

float convert_c_f(float c)
{
	return c * (9.0 / 5.0) + 32;
}

float convert_c_k(float c)
{
	return c + 273.15;
}

float convert_f_c(float f)
{
	return (f - 32) * (5.0 / 9.0);
}

float convert_k_c(float k)
{
	return k - 273.15;
}

float convert_k_f(float k)
{
	return k * (9.0 / 5.0) - 459.67;
}

float convert_f_k(float f)
{
	return (f + 459.67) * (5.0 / 9.0);
}

int is_temperature_correct(float t, char c){
	switch(c){
		case 'c':
			if (t >= -273.15) return 1;
			break;
		case 'f':
			if (t >= -459.67) return 1;
			break;
		case 'k':
			if (t >= 0) return 1;
			break;
	}

	printf("Temperature can't be below absolute zero!\n");
	return 0;
}

void convert_from_c(float t){
	if (! is_temperature_correct(t, 'c')) return;

	printf("%.2f F\n%.2f K\n", convert_c_f(t), convert_c_k(t));
}

void convert_from_f(float t){
	if (! is_temperature_correct(t, 'f')) return;

	printf("%.2f C\n%.2f K\n", convert_f_c(t), convert_f_k(t));
}

void convert_from_k(float t){
	if (! is_temperature_correct(t, 'k')) return;

	printf("%.2f C\n%.2f F\n", convert_k_c(t), convert_k_f(t));
}

int wrong_scale_error(){
	printf("Unknown scale! Should be one of C, F, K\n");
	return 1;
}