/**
* @file main.c
* @brief Generates an animated GIF file for a game of life simulation
* @date 2016-10-09
* @author Vitor Carreira
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <time.h>
#include <regex.h>
#include <dirent.h>
#include <math.h>

#include "debug.h"
#include "memory.h"
#include "args.h"

#define ELAPSED_MILLIS(end,start) (((end).tv_sec - (start).tv_sec)*1e3 + ((end).tv_nsec - (start).tv_nsec)/1e6)

#define ERR_ARGS 1
#define ERR_THREADS 2
#define ERR_SYS_CALL 3

void iterate_folder(char *path);
void process_file(char *folder, char *file);
void create_pbm(FILE *input, FILE *output, unsigned int grid_size);
void convert_to_animated_gif(char *output_folder, unsigned int grid_size, char *animation_name);

int main(int argc, char *argv[]){
    struct gengetopt_args_info args;

    if (cmdline_parser(argc, argv, &args) != 0) {
        exit(ERR_ARGS);
    }
    if (args.folder_arg[strlen(args.folder_arg)-1] == '/') {
        args.folder_arg[strlen(args.folder_arg)-1] = 0;
    }

    iterate_folder(args.folder_arg);

    cmdline_parser_free(&args);
	return 0;
}

void iterate_folder(char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        ERROR(ERR_SYS_CALL, "opendir() failed");
    }

    regex_t regex;
    if (regcomp(&regex, "^simulation-[[:digit:]]\\{8\\}-[[:digit:]]\\{6\\}-0", 0) != 0) {
        ERROR(ERR_SYS_CALL, "regcomp() failed");
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (regexec(&regex, entry->d_name, 0, NULL, 0) == 0) {
            process_file(path, entry->d_name);
        }
    }
    closedir(dir);
    regfree(&regex);
}

void process_file(char *folder, char *file)
{

    size_t input_size = strlen(folder) + strlen(file) + 15;
    char *input_file = MALLOC(input_size);
    char *fmt_input = MALLOC(input_size);
    snprintf(fmt_input, input_size, "%s/%s", folder, file);
    fmt_input[strlen(fmt_input)-1] = 0; // removes generation 0
    strcat(fmt_input, "%d"); // appends integer specifier


    char template[] = "gameoflife.XXXXXX";
    char *output_folder = mkdtemp(template);
    if (output_folder == NULL) {
        ERROR(ERR_SYS_CALL, "mkdtemp() failed");
    }

    char output_file[40];
    char fmt_output[40];
    snprintf(fmt_output, sizeof(fmt_output), "%s/%%d.pbm", output_folder);

    int generation = 0;
    snprintf(input_file, input_size, fmt_input, generation);
    FILE *input = fopen(input_file, "r");
    if (input == NULL) {
        ERROR(ERR_SYS_CALL, "fopen() failed for generation 0: %s", input_file);
    }

    char animation_name[32];
    strncpy(animation_name, file, sizeof(animation_name));
    animation_name[strlen(file)-2] = 0; // remove -0 prefix
    strcat(animation_name, ".gif");

    fseek(input, 0, SEEK_END);
    unsigned int grid_size = (unsigned int)floor(sqrt(ftell(input)));
    fseek(input, 0, SEEK_SET);

    do {
        snprintf(output_file, sizeof(output_file), fmt_output, generation);

        FILE *output = fopen(output_file, "w");
        if (output == NULL) {
            ERROR(ERR_SYS_CALL, "fopen() failed for file %s", output_file);
        }
        create_pbm(input, output, grid_size);
        fclose(input);
        fclose(output);

        generation++;
        snprintf(input_file, input_size, fmt_input, generation);
        input = fopen(input_file, "r");
    } while (input != NULL);

    convert_to_animated_gif(output_folder, grid_size, animation_name);

    rmdir(output_folder);

    FREE(fmt_input);
    FREE(input_file);
}

void create_pbm(FILE *input, FILE *output, unsigned int grid_size)
{
    fprintf(output, "P1\n%u %u\n", grid_size, grid_size);
    fseek(input, 0, SEEK_SET);

    unsigned int total = grid_size * grid_size;
    unsigned int i;
    for (i = 0; i < total; ++i) {
        int ch = fgetc(input);
        if (ch == EOF) {
            ERROR(ERR_SYS_CALL, "fgetc() failed");
        }
        if (ch != '0' && ch != '1') {
            printf("Invalid simulation file: %c\n", ch);
            exit(ERR_ARGS);
        }
        fputc(ch, output);
        fputc(' ', output);
    }
}

void convert_to_animated_gif(char *output_folder, unsigned int grid_size, char *animation_name)
{
    char cmd[1024];
    if (grid_size < 150) {
        strncpy(cmd, "mogrify -scale 150x150 -format png *.pbm", sizeof(cmd));
    } else {
        strncpy(cmd, "mogrify -format png *.pbm", sizeof(cmd));
    }

    chdir(output_folder);
    system(cmd);
    snprintf(cmd, sizeof(cmd), "convert -delay 100 -loop 0 *.png ../%s", animation_name);
    system(cmd);
    system("rm *.png; rm *.pbm");

    chdir("..");
}
