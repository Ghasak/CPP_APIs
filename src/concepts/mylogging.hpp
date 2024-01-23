#ifndef MYLOGGING_H
#define MYLOGGING_H

#define RED "\033[1;31m"
#define BLUE "\033[1;36m"
#define RESET "\033[0m"

void init_logging(char** my_argv);
void log_info(const char* message);

#endif  // MYLOGGING_H
