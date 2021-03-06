/*
  Copyright (C) 1987 The Board of Trustees of Stanford University
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/*
 *
 *  source file:   ./filters/genlib/genmessage.c
 *
 * Joe Dellinger (SEP), June 11 1987
 *	Inserted this sample edit history entry.
 *	Please log any further modifications made to this file:
 */

#include	<stdio.h>
#include	"../include/mesgcom.h"
#include	"../include/enum.h"

void genmessage (int command, const char *string)
/*< Device independent subroutine to handle message operations >*/
{

    switch (command)
    {
    case MESG_HOME:
    case MESG_READY:
	fflush (stderr);
	break;
    case MESG_TEXT:
	fprintf (stderr, "%s", string);
	break;
    case MESG_HIGHLIGHT_ON:
	/* Beep at them to get their attention */
	fprintf (stderr, "\07\07");
	break;
    case MESG_ON:
    case MESG_OFF:
    case MESG_ERASE:
    case MESG_HIGHLIGHT_OFF:
    case MESG_DONE:
    default:
	fflush (stderr);
	break;
    }
}
