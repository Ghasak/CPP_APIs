#ifndef MYLOGGING_H
#define MYLOGGING_H

#define RED "\033[1;31m"

#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define BLACK "\033[1;30m"

#define BRIGHT_RED "\033[1;91m"
#define BRIGHT_GREEN "\033[1;92m"
#define BRIGHT_YELLOW "\033[1;93m"
#define BRIGHT_BLUE "\033[1;94m"
#define BRIGHT_MAGENTA "\033[1;95m"
#define BRIGHT_CYAN "\033[1;96m"
#define BRIGHT_WHITE "\033[1;97m"
#define BRIGHT_BLACK "\033[1;90m"

#define RESET "\033[0m"

void init_logging(char** my_argv);
void log_info(const char* message);

#endif  // MYLOGGING_H
