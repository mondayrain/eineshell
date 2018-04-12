#ifndef EINESHELL_JOB_CONTROL_H
#define EINESHELL_JOB_CONTROL_H

#include <sys/types.h>
#include <termios.h>

// Borrowed liberally from https://www.gnu.org/software/libc/manual/html_node/Data-Structures.html#Data-Structures

/* A process is a single process.  */
struct process
{
  struct process *next;       /* next process in pipeline */
  char **argv;                /* for exec */
  pid_t pid;                  /* process ID */
  char completed;             /* true if process has completed */
  char stopped;               /* true if process has stopped */
  int status;                 /* reported status value */
};


/* A job is a pipeline of processes.  */
struct job
{
  struct job *next;           /* next active job */
  char *command;              /* command line, used for messages */
  process *first_process;     /* list of processes in this job */
  pid_t pgid;                 /* process group ID */
  char notified;              /* true if user told about stopped job */
  int stdin, stdout, stderr;  /* standard i/o channels */
};

/* The active jobs are linked into a list.  This is its head.   */
job *first_job = nullptr;


job * find_job (pid_t pgid);
int job_is_stopped (job *j);
int job_is_completed (job *j);


#endif //EINESHELL_JOB_CONTROL_H
