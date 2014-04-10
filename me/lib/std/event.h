/*
 * Copyright (C) 2012-2014,  Netronome Systems, Inc.  All rights reserved.
 *
 * @file          lib/std/event.h
 * @brief         Interface for event bus and event managers
 *
 */
#ifndef _STD__EVENT_H_
#define _STD__EVENT_H_

#include <nfp.h>

#include <nfp6000/nfp_event.h>

struct event_cls_filter;

/**
 * Get handler for CLS event filter
 *
 * @param fnum          event filter index
 *
 * Return a handle to use for other event_cls_filter functions.
 */
__intrinsic __cls struct event_cls_filter *event_cls_filter_handle(int fnum);

/**
 * Setup CLS event filter
 *
 * @param filter        event filter handle
 * @param type          type of event filter
 * @param match         match value for filter
 * @param mask          mask value for filter
 * @param status        configuration for the event filter status field
 */
__intrinsic void event_cls_filter_setup(__cls struct event_cls_filter *filter,
                                        int type,
                                        unsigned int match, unsigned int mask,
                                        struct nfp_em_filter_status status);

/**
 * Disable CLS event filter
 *
 * @param filter        event filter handle
 */
__intrinsic void event_cls_filter_disable(
    __cls struct event_cls_filter *filter);

/**
 * Acknowledge CLS event filter
 *
 * @param filter        event filter handle
 */
__intrinsic unsigned int event_cls_filter_ack(
    __cls struct event_cls_filter *filter);


/**
 * Trigger event on event bus
 *
 * @param evdata        event data
 *
 * Trigger an event on the event bus.  The upper four bits of the
 * event data (i.e., the event provider bits in [19:16]) are hardcoded
 * to the current cluster number.
 */
__intrinsic void event_cls_user_event(unsigned int evdata);

/**
 * Setup an event autopush signal
 *
 * @param apnum         autopush signal index number
 * @param master        master to push to
 * @param thd           thread number
 * @param signum        signal number
 * @param xfernum       xfer register number
 *
 * Set up an autopush entry to signal the indicated ME thread and push
 * a value to the indicated xfer register.  The @master parameter is
 * only four bbits wide, indicating the ME master within the current
 * cluster.
 */
__intrinsic void event_cls_autopush_signal_setup(unsigned int apnum,
                                                 unsigned int master,
                                                 unsigned int thd,
                                                 unsigned int signum,
                                                 unsigned int xfernum);

/**
 * Reset an event autopush filter
 *
 * @param fnum          autopush filter number
 * @param type          autopush filter type
 * @param autopush      autopush signal to invoke
 */
__intrinsic void event_cls_autopush_filter_reset(unsigned int fnum,
                                                 unsigned int type,
                                                 unsigned int autopush);

/**
 * Disable an event autopush filter
 *
 * @param fnum          autopush filter number
 */
__intrinsic void event_cls_autopush_filter_disable(unsigned int fnum);

#endif /* !_STD__EVENT_H_ */
