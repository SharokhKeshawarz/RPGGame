#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>
#include <sys/stat.h>
#include <stdbool.h>

#include <SFML/System.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Network.h>

// MESSAGE
#define COLOR_RESET   "\x1b[0m"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"

#define PRINT_INFO(message, ...)   printf(COLOR_BLUE "INFO: " message COLOR_RESET "\n", ##__VA_ARGS__)
#define PRINT_ERROR(message, ...)  printf(COLOR_RED "ERROR: " message COLOR_RESET "\n", ##__VA_ARGS__)
#define PRINT_SUCCESS(message, ...) printf(COLOR_GREEN "SUCCESS: " message COLOR_RESET "\n", ##__VA_ARGS__)

#endif /* MAIN_H */
