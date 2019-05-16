/* Copyright © 2018-2019 N. Van Bossuyt.                                      */
/* This code is licensed under the MIT License.                               */
/* See: LICENSE.md                                                            */

#include <skift/thread.h>

DEFN_SYSCALL0(thread_self, SYS_THREAD_SELF);
DEFN_SYSCALL2(thread_create, SYS_THREAD_CREATE, int, void *);

DEFN_SYSCALL1(thread_exit, SYS_THREAD_EXIT, void *);
DEFN_SYSCALL2(thread_cancel, SYS_THREAD_CANCEL, int, void*);

DEFN_SYSCALL1(thread_sleep, SYS_THREAD_SLEEP, int);
DEFN_SYSCALL1(thread_wakeup, SYS_THREAD_WAKEUP, int);

DEFN_SYSCALL2(thread_wait_thread, SYS_THREAD_WAIT_THREAD, int, int *);
DEFN_SYSCALL2(thread_wait_process, SYS_THREAD_WAIT_PROCESS, int, int *);