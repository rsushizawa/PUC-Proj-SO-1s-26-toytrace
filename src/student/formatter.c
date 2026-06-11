#include "student_api.h"

#include "syscall_names.h"

#include "trace_helpers.h"

#include <sys/syscall.h>

#include <stdio.h>

void student_debug_raw_event(const struct syscall_event *ev, char *buf,
                             size_t bufsz) {
  snprintf(buf, bufsz, "pid=%d %s %s", ev->pid, syscall_name(ev->syscall_no),
           ev->entering ? "entrada" : "saida");
}

void student_format_event(const struct syscall_event *ev, char *buf,
                          size_t bufsz) {
  switch (ev->syscall_no) {
  case SYS_read: {
    char texto[256] = {0};

    if (ev->ret > 0 &&
        read_child_string(ev->pid, ev->args[1], texto, sizeof(texto)) >= 0) {
      snprintf(buf, bufsz, "read(%ld, \"%s\", %ld) = %ld", ev->args[0], texto,
               ev->args[2], ev->ret);
    } else {
      snprintf(buf, bufsz, "read(%ld, <ilegivel>, %ld) = %ld", ev->args[0],
               ev->args[2], ev->ret);
    }

    break;
  }

  case SYS_write: {
    char texto_write[256] = {0};

    if (ev->ret > 0 && read_child_string(ev->pid, ev->args[1], texto_write,
                                         sizeof(texto_write)) >= 0) {
      snprintf(buf, bufsz, "write(%ld, \"%s\", %ld) = %ld", ev->args[0],
               texto_write, ev->args[2], ev->ret);
    } else {
      snprintf(buf, bufsz, "write(%ld, <ilegivel>, %ld) = %ld", ev->args[0],
               ev->args[2], ev->ret);
    }

    break;
  }

  case SYS_openat: {
    char path[256] = {0};

    if (read_child_string(ev->pid, ev->args[1], path, sizeof(path)) >= 0) {
      snprintf(buf, bufsz, "openat(%ld, \"%s\", %#lx, %#lx) = %ld", ev->args[0],
               path, ev->args[2], ev->args[3], ev->ret);
    } else {
      snprintf(buf, bufsz, "openat(%ld, <ilegivel>, %#lx, %#lx) = %ld",
               ev->args[0], ev->args[2], ev->args[3], ev->ret);
    }

    break;
  }

  case SYS_execve: {
    char path_execve[256] = {0};

    if (read_child_string(ev->pid, ev->args[0], path_execve,
                          sizeof(path_execve)) >= 0) {
      snprintf(buf, bufsz, "execve(\"%s\", ...) = %ld", path_execve, ev->ret);
    } else {
      snprintf(buf, bufsz, "execve(<ilegivel>, ...) = %ld", ev->ret);
    }

    break;
  }

  case SYS_exit_group:
    snprintf(buf, bufsz, "exit_group(%ld)", ev->args[0]);
    break;

  default:
    snprintf(buf, bufsz, "%s(%#lx, %#lx, %#lx, %#lx, %#lx, %#lx) = %ld",
             syscall_name(ev->syscall_no), ev->args[0], ev->args[1],
             ev->args[2], ev->args[3], ev->args[4], ev->args[5], ev->ret);
    break;
  }
}
