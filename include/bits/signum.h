/*
 *      This file is part of the KoraOS project.
 *  Copyright (C) 2015-2021  <Fabien Bavent>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   - - - - - - - - - - - - - - -
 */
#ifndef __BITS_SIGNUM_H
#define __BITS_SIGNUM_H 1


#define SIGHUP 1 // Hang up detected on controlling terminal or death of controlling process
#define SIGINT 2 // Issued if the user sends an interrupt signal (Ctrl + C)
#define SIGQUIT 3 // Issued if the user sends a quit signal (Ctrl + D)
#define SIGILL 4 // The ILL signal is sent to a process when it attempts to execute a malformed, unknown, or privileged instruction.
#define SIGTRAP 5 // The TRAP signal is sent to a process when a condition arises that a debugger is tracing
#define SIGABRT 6 // ABRT is usually sent by the process itself, when it calls the abort() system call to signal an abnormal termination, but it can be sent from any process like any other signal.
#define SIGBUS 7 // The BUS signal is sent to a process when it causes a bus error, such as an incorrect memory access alignment or non-existent physical address.
#define SIGFPE 8 // Issued if an illegal mathematical operation is attempted
#define SIGKILL 9 // If a process gets this signal it must quit immediately and will not perform any clean-up operations
#define SIGUSR1 10
#define SIGSEGV 11 // The SEGV signal is sent to a process when it makes an invalid virtual memory reference, or segmentation fault, i.e. when it performs a segmentation violation.
#define SIGUSR2 12
#define SIGPIPE 13 // The PIPE signal is sent to a process when it attempts to write to a pipe without a process connected to the other end.
#define SIGALRM 14 // Alarm clock signal (used for timers)
#define SIGTERM 15 // Software termination signal (sent by kill by default)
#define SIGSTKFLT 16 // Stack fault.
#define SIGCHLD 17 // The CHLD signal is sent to a process when a child process terminates, is interrupted, or resumes after being interrupted.
#define SIGCONT 18 // Continue executing after stopped, e.g., by STOP
#define SIGSTOP 19 // The STOP signal instructs the operating system to stop a process for later resumption.
#define SIGTSTP 20 // The TSTP signal is sent to a process by its controlling terminal to request it to stop temporarily. It is commonly initiated by the user pressing Control-Z.
#define SIGTTIN 21 // The TTIN signal is sent to a process when it attempts to read from the tty while in the background.
#define SIGTTOU 22 // TTOU signal is sent to a process when it attempts to write from the tty while in the background.
#define SIGURG 23 // The URG signal is sent to a process when a socket has urgent or out-of-band data available to read.
#define SIGXCPU 24 // The XCPU signal is sent to a process when it has used up the CPU for a duration that exceeds a certain predetermined user-settable value.
#define SIGXFSZ 25 // The XFSZ signal is sent to a process when it grows a file larger than the maximum allowed size.
#define SIGVTALRM 26 // Virtual alarm clock. May be sent by the alarm() system call.
#define SIGPROF 27
#define SIGWINCH 28
#define SIGIO 29
#define SIGPOLL     SIGIO
#define SIGPWR 30
#define SIGSYS 31 // Unused signal.
#define SIGRTMIN 32
#define SIGRTMAX 64

#define SIGUNUSED  SIGSYS

#endif  /* __BITS_SIGNUM_H */
