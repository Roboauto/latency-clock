/* GStreamer
 * Copyright (C) 2017 Atish Nazir <github@cognitive-i.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef _GSTTIMESTAMPOVERLAY_TIMEPOLYFILL_H_
#define _GSTTIMESTAMPOVERLAY_TIMEPOLYFILL_H_

#ifndef __APPLE__
#include <time.h>
#else
/*
 * OS-X does not provide a clock_gettime implementation, polyfill in
 * terms of gettimeofday.
 *
 * Polyfilling rather than replace all usages with so that we can retain
 * nanosecond precision on Linux.
 *
 */

#include <sys/time.h>

enum clockid_t {
  CLOCK_REALTIME
};

static int
clock_gettime(enum clockid_t clk_id, struct timespec *tp)
{
  struct timeval now;

  if (CLOCK_REALTIME != clk_id) {
    errno = EINVAL;
    return -1;
  }

  if (NULL == tp) {
    return 0;
  }

  if (! gettimeofday(&now, NULL)) {
    /* errno are sufficiently similiar between gettimeofday and clock_gettime */
    return -1;
  } else {
    tp->tv_sec = now.tv_sec;
    tp->tv_nsec = now.tv_usec * 1000;
    return 0;
  }
}

#endif

#endif
