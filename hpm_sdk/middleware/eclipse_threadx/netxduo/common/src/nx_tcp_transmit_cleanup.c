/***************************************************************************
 * Copyright (c) 2024 Microsoft Corporation 
 * 
 * This program and the accompanying materials are made available under the
 * terms of the MIT License which is available at
 * https://opensource.org/licenses/MIT.
 * 
 * SPDX-License-Identifier: MIT
 **************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** NetX Component                                                        */
/**                                                                       */
/**   Transmission Control Protocol (TCP)                                 */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/

#define NX_SOURCE_CODE


/* Include necessary system files.  */

#include "nx_api.h"
#include "tx_thread.h"
#include "tx_timer.h"
#include "nx_ip.h"
#include "nx_tcp.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _nx_tcp_transmit_cleanup                            PORTABLE C      */
/*                                                           6.1          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Yuxin Zhou, Microsoft Corporation                                   */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This function processes TCP transmit timeout and thread terminate   */
/*    actions that require the TCP socket data structures to be cleaned   */
/*    up.                                                                 */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    thread_ptr                            Pointer to suspended thread's */
/*                                            control block               */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    tx_event_flags_set                    Set event flag                */
/*    _tx_thread_system_resume              Resume thread service         */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    _nx_tcp_deferred_cleanup_check        Deferred cleanup processing   */
/*    _nx_tcp_socket_disconnect             Disconnect processing         */
/*    _nx_tcp_socket_connection_reset       Reset processing              */
/*    _tx_thread_timeout                    Thread timeout processing     */
/*    _tx_thread_terminate                  Thread terminate processing   */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Yuxin Zhou               Initial Version 6.0           */
/*  09-30-2020     Yuxin Zhou               Modified comment(s),          */
/*                                            resulting in version 6.1    */
/*                                                                        */
/**************************************************************************/
VOID  _nx_tcp_transmit_cleanup(TX_THREAD *thread_ptr NX_CLEANUP_PARAMETER)
{

TX_INTERRUPT_SAVE_AREA

NX_TCP_SOCKET *socket_ptr;  /* Working socket pointer  */
NX_IP         *ip_ptr;

    NX_CLEANUP_EXTENSION

    /* Disable interrupts.  */
    TX_DISABLE

    /* Setup pointer to TCP socket control block.  */
    socket_ptr =  (NX_TCP_SOCKET *)thread_ptr -> tx_thread_suspend_control_block;

    /* Determine if the socket pointer is valid.  */
    if ((!socket_ptr) || (socket_ptr -> nx_tcp_socket_id != NX_TCP_ID))
    {

        /* Restore interrupts.  */
        TX_RESTORE

        return;
    }

    /* Determine if the cleanup is still required.  */
    if (!(thread_ptr -> tx_thread_suspend_cleanup))
    {

        /* Restore interrupts.  */
        TX_RESTORE

        return;
    }

    /* Determine if the caller is an ISR or the system timer thread.  */
#ifndef TX_TIMER_PROCESS_IN_ISR
    if ((TX_THREAD_GET_SYSTEM_STATE()) || (_tx_thread_current_ptr == &_tx_timer_thread))
#else
    if (TX_THREAD_GET_SYSTEM_STATE())
#endif
    {

        /* Yes, defer the processing to the NetX IP thread.  */

        /* Yes, change the suspend cleanup routine to indicate the cleanup is deferred.  */
        thread_ptr -> tx_thread_suspend_cleanup =  _nx_tcp_cleanup_deferred;

        /* Pickup the IP pointer.  */
        ip_ptr =  socket_ptr -> nx_tcp_socket_ip_ptr;

        /* Restore interrupts.  */
        TX_RESTORE

        /* Set the deferred cleanup flag for the IP thread.  */
        tx_event_flags_set(&(ip_ptr -> nx_ip_events), NX_IP_TCP_CLEANUP_DEFERRED, TX_OR);

        /* Return to caller.  */
        return;
    }
    else
    {

        /* Yes, we still have thread suspension!  */

        /* Clear the suspension cleanup flag.  */
        thread_ptr -> tx_thread_suspend_cleanup =  TX_NULL;

        /* Remove the suspended thread from the list.  */

        /* See if this is the only suspended thread on the list.  */
        if (thread_ptr == thread_ptr -> tx_thread_suspended_next)
        {

            /* Yes, the only suspended thread.  */

            /* Update the head pointer.  */
            socket_ptr -> nx_tcp_socket_transmit_suspension_list =  NX_NULL;
        }
        else
        {

            /* At least one more thread is on the same suspension list.  */

            /* Update the list head pointer.  */
            socket_ptr -> nx_tcp_socket_transmit_suspension_list =  thread_ptr -> tx_thread_suspended_next;

            /* Update the links of the adjacent threads.  */
            (thread_ptr -> tx_thread_suspended_next) -> tx_thread_suspended_previous =
                thread_ptr -> tx_thread_suspended_previous;
            (thread_ptr -> tx_thread_suspended_previous) -> tx_thread_suspended_next =
                thread_ptr -> tx_thread_suspended_next;
        }

        /* Decrement the suspension count.  */
        socket_ptr -> nx_tcp_socket_transmit_suspended_count--;

        /* Now we need to determine if this cleanup is from a terminate, timeout,
           or from a wait abort.  */
        if (thread_ptr -> tx_thread_state == TX_TCP_IP)
        {

            /* Thread still suspended on the TCP socket.  Setup return error status and
               resume the thread.  */

            /* Determine which transmit error is present.  */
            if (socket_ptr -> nx_tcp_socket_state != NX_TCP_ESTABLISHED)
            {

                /* This socket is no longer connected.  */
                thread_ptr -> tx_thread_suspend_status =  NX_NOT_CONNECTED;
            }
            else if (socket_ptr -> nx_tcp_socket_transmit_sent_count < socket_ptr -> nx_tcp_socket_transmit_queue_maximum)
            {

                /* Not a queue depth problem, return a window overflow error.  */
                thread_ptr -> tx_thread_suspend_status =  NX_WINDOW_OVERFLOW;
            }
            else
            {

                /* Return a transmit queue exceeded error.  */
                thread_ptr -> tx_thread_suspend_status =  NX_TX_QUEUE_DEPTH;
            }

            /* Temporarily disable preemption.  */
            _tx_thread_preempt_disable++;

            /* Restore interrupts.  */
            TX_RESTORE

            /* Resume the thread!  */
            _tx_thread_system_resume(thread_ptr);

            /* Finished, just return.  */
            return;
        }
    }

    /* Restore interrupts.  */
    TX_RESTORE
}

