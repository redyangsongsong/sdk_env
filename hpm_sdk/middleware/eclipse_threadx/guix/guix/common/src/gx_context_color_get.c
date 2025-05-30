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
/** GUIX Component                                                        */
/**                                                                       */
/**   Context Management (Context)                                        */
/**                                                                       */
/**************************************************************************/

#define GX_SOURCE_CODE


/* Include necessary system files.  */

#include "gx_api.h"
#include "gx_system.h"
#include "gx_context.h"


/**************************************************************************/
/*                                                                        */
/*  FUNCTION                                               RELEASE        */
/*                                                                        */
/*    _gx_context_color_get                               PORTABLE C      */
/*                                                           6.1          */
/*  AUTHOR                                                                */
/*                                                                        */
/*    Kenneth Maxwell, Microsoft Corporation                              */
/*                                                                        */
/*  DESCRIPTION                                                           */
/*                                                                        */
/*    This service gets the color associated with the supplied            */
/*    resource ID from the system color table.                            */
/*                                                                        */
/*  INPUT                                                                 */
/*                                                                        */
/*    color_id                              Resource ID of color          */
/*    return_color                          Pointer to destination for    */
/*                                            color                       */
/*                                                                        */
/*  OUTPUT                                                                */
/*                                                                        */
/*    status                                Completion status             */
/*                                                                        */
/*  CALLS                                                                 */
/*                                                                        */
/*    None                                                                */
/*                                                                        */
/*  CALLED BY                                                             */
/*                                                                        */
/*    Application Code                                                    */
/*    _gx_context_brush_define                                            */
/*    _gx_context_fill_color_set                                          */
/*    _gx_context_line_color_set                                          */
/*                                                                        */
/*  RELEASE HISTORY                                                       */
/*                                                                        */
/*    DATE              NAME                      DESCRIPTION             */
/*                                                                        */
/*  05-19-2020     Kenneth Maxwell          Initial Version 6.0           */
/*  09-30-2020     Kenneth Maxwell          Modified comment(s),          */
/*                                            resulting in version 6.1    */
/*                                                                        */
/**************************************************************************/
UINT _gx_context_color_get(GX_RESOURCE_ID color_id, GX_COLOR *return_color)
{
UINT             status;
GX_DRAW_CONTEXT *context = _gx_system_current_draw_context;
GX_DISPLAY      *display;

    display = context -> gx_draw_context_display;

    /* Determine if the ID is within range.  */
    if (display == GX_NULL)
    {
        *return_color = 0;
        return GX_INVALID_DISPLAY;
    }

    if ((color_id < display -> gx_display_color_table_size) &&  (display -> gx_display_color_table != GX_NULL))
    {
        /* Yes, the ID is within range. Perform a table lookup and return the
            color.  */
        *return_color = display -> gx_display_color_table[color_id];
        status = GX_SUCCESS;
    }
    else
    {
        *return_color = 0;
        status = GX_INVALID_RESOURCE_ID;
    }

    return status;
}

