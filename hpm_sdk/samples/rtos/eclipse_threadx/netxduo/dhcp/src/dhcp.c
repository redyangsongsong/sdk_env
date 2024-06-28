/*
 * Copyright (c) 2023-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "board.h"
#include "hpmicro_netx_driver.h"
#include "nx_api.h"
#include "nxd_dhcp_client.h"
#include "tx_api.h"
#include <stdio.h>

/* Define vars that the dhcp need*/
ATTR_PLACE_AT_NONCACHEABLE_WITH_ALIGNMENT(64) NX_DHCP dhcp_client;
UCHAR ip_address[4];
UCHAR network_mask[4];

/* Define vars that the thread which print message to console need*/
TX_THREAD thread_0;
#define DEMO_STACK_SIZE 1024
ULONG demo_stack[DEMO_STACK_SIZE >> 2];

VOID thread_0_entry(ULONG thread_input);

/* Define sample IP address.  */
#define SAMPLE_IPV4_ADDRESS IP_ADDRESS(192, 168, 1, 223)
#define SAMPLE_IPV4_MASK 0xFFFFFF00UL

/* Define packet pool.  */
#define PACKET_SIZE 1536
#define PACKET_COUNT 30
#define PACKET_POOL_SIZE ((PACKET_SIZE + sizeof(NX_PACKET)) * PACKET_COUNT)

/* Define IP stack size.   */
#define IP_STACK_SIZE 2048

/* Define IP thread priority.  */
#define IP_THREAD_PRIORITY 1

/* Define ARP pool.  */
#define ARP_POOL_SIZE 1024

/* Define the ThreadX and NetX object control blocks...  */
NX_PACKET_POOL default_pool;
NX_IP default_ip;

/* Define memory buffers.  */
ULONG pool_area[PACKET_POOL_SIZE >> 2];
ULONG ip_stack[IP_STACK_SIZE >> 2];
ULONG arp_area[ARP_POOL_SIZE >> 2];

/* Define the counters used in the demo application...  */
ULONG error_counter;

/* Define main entry point.  */
INT main(VOID)
{
    board_init();

    /* Initialize GPIOs */
    board_init_enet_pins(ENET);

    /* Reset an enet PHY */
    board_reset_enet_phy(ENET);

/* Set RGMII clock delay */
#if defined(RGMII) && RGMII
    board_init_enet_rgmii_clock_delay(ENET);
#elif defined(RMII) && RMII
    /* Set RMII reference clock */
    board_init_enet_rmii_reference_clock(ENET, BOARD_ENET_RMII_INT_REF_CLK);
    printf("Reference Clock: %s\n", BOARD_ENET_RMII_INT_REF_CLK ? "Internal Clock" : "External Clock");
#endif

    /* Start a board timer */
    board_timer_create(2000, sys_timer_callback);

    /* Enter the ThreadX kernel.  */
    tx_kernel_enter();
}

/* Define what the initial system looks like.  */
VOID tx_application_define(VOID *first_unused_memory)
{

    UINT status;

    NX_PARAMETER_NOT_USED(first_unused_memory);

    tx_thread_create(&thread_0, "thread 0", thread_0_entry, 0, demo_stack, DEMO_STACK_SIZE, 1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);

    /* Initialize the NetX system.  */
    nx_system_initialize();

    /* Create a packet pool.  */
    status = nx_packet_pool_create(&default_pool, "NetX Main Packet Pool", PACKET_SIZE, pool_area, sizeof(pool_area));

    /* Check for packet pool create errors.  */
    if (status)
        error_counter++;

    /* Create an IP instance.  */
    status = nx_ip_create(&default_ip, "NetX IP Instance 0", IP_ADDRESS(0, 0, 0, 0), IP_ADDRESS(0, 0, 0, 0), &default_pool,
                          _nx_driver_hpm, (VOID *)ip_stack, sizeof(ip_stack), IP_THREAD_PRIORITY);

    /* Check for IP create errors.  */
    if (status)
        error_counter++;

    /* Enable ARP and supply ARP cache memory for IP Instance 0.  */
    status = nx_arp_enable(&default_ip, (VOID *)arp_area, sizeof(arp_area));

    /* Check for ARP enable errors.  */
    if (status)
        error_counter++;

    /* Enable ICMP */
    status = nx_icmp_enable(&default_ip);

    /* Check for ICMP enable errors.  */
    if (status)
        error_counter++;

    /* Enable UDP traffic.  */
    status = nx_udp_enable(&default_ip);

    /* Check for UDP enable errors.  */
    if (status)
        error_counter++;

    /* Enable TCP traffic.  */
    status = nx_tcp_enable(&default_ip);

    /* Check for TCP enable errors.  */
    if (status)
        error_counter++;

    assert(error_counter == 0);

    /* Output IP address and network mask.  */
    printf("NetXDuo is running\r\n");
}

VOID thread_0_entry(ULONG thread_input)
{

    UINT status;
    ULONG actual_status;
    ULONG temp;
    TX_PARAMETER_NOT_USED(thread_input);
    /* Create the DHCP instance.  */
    printf("DHCP In Progress...\r\n");

    nx_dhcp_create(&dhcp_client, &default_ip, "dhcp_client");

    /* Start the DHCP Client.  */
    nx_dhcp_start(&dhcp_client);

    /* Wait util address is solved. */
    status = nx_ip_status_check(&default_ip, NX_IP_ADDRESS_RESOLVED, &actual_status, 8000);

    if (status) {
        /* DHCP Failed...  no IP address! */
        printf("Can't resolve address\r\n");
    } else {
        /* Get IP address. */
        nx_ip_address_get(&default_ip, (ULONG *)&ip_address[0], (ULONG *)&network_mask[0]);

        /* Convert IP address & network mask from little endian.  */
        temp = *((ULONG *)&ip_address[0]);
        NX_CHANGE_ULONG_ENDIAN(temp);
        *((ULONG *)&ip_address[0]) = temp;

        temp = *((ULONG *)&network_mask[0]);
        NX_CHANGE_ULONG_ENDIAN(temp);
        *((ULONG *)&network_mask[0]) = temp;

        /* Output IP address. */
        printf("IP address: %d.%d.%d.%d\r\nMask: %d.%d.%d.%d\r\n", (UINT)(ip_address[0]), (UINT)(ip_address[1]),
            (UINT)(ip_address[2]), (UINT)(ip_address[3]), (UINT)(network_mask[0]), (UINT)(network_mask[1]),
            (UINT)(network_mask[2]), (UINT)(network_mask[3]));
    }

    while (1) {
        tx_thread_sleep(100);
    }
}