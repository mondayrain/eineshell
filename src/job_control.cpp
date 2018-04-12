#include "job_control.h"

job * find_job (pid_t pgid) {
    /* Find the active job with the indicated pgid.  */
    job *j;

    for (j = first_job; j; j = j->next)
        if (j->pgid == pgid)
            return j;
    return nullptr;
}


int  job_is_stopped (job *j) {
    /* Return true if all processes in the job have stopped or completed.  */
    process *p;

    for (p = j->first_process; p; p = p->next)
        if (!p->completed && !p->stopped)
            return 0;
    return 1;
}


int job_is_completed (job *j) {
    /* Return true if all processes in the job have completed.  */

    process *p;

    for (p = j->first_process; p; p = p->next)
        if (!p->completed)
            return 0;
    return 1;
}