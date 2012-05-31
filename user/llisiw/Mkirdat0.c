/* 2-D Post-stack Kirchhoff redatuming. */
/*
  Copyright (C) 2012 University of Texas at Austin
  
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

#include <rsf.h>

#include "kirdat.h"

int main(int argc, char* argv[])
{
    bool adj;
    int it, nt, ix, nx, left, right, ic, aper, shift;
    float datum, length, t0, dt, x0, dx, dist, tau, delta=0.;
    float **tr_in, **tr_out, **table;
    sf_file in, out, green;

    sf_init (argc,argv);
    in = sf_input("in");
    out = sf_output("out");
    
    if (!sf_getbool("adj",&adj)) adj=true;
    /* y for upward, n for downward */

    if (!sf_getfloat("datum",&datum)) sf_error("Need datum=");
    /* datum depth */

    if (!sf_getint("aperture",&aper)) aper=50;
    /* aperture (number of near traces) */

    if (!sf_getfloat("length",&length)) length=0.025;
    /* filter length (in seconds) */

    /* read input */
    if (!sf_histint(in,"n1",&nt)) sf_error("No nt=");
    if (!sf_histint(in,"n2",&nx)) sf_error("No nx=");
    
    if (!sf_histfloat(in,"o1",&t0)) sf_error("No t0=");
    if (!sf_histfloat(in,"d1",&dt)) sf_error("No dt=");
    
    if (!sf_histfloat(in,"o2",&x0)) sf_error("No x0=");
    if (!sf_histfloat(in,"d2",&dx)) sf_error("No dx=");

    tr_in = sf_floatalloc2(nt,nx);
    sf_floatread(tr_in[0],nt*nx,in);

    /* allocate memory for output */
    tr_out = sf_floatalloc2(nt,nx);

    /* read Green's function (traveltime table) */
    green = sf_input("table");
    table = sf_floatalloc2(nx,nx);
    sf_floatread(table[0],nx*nx,green);
    sf_fileclose(green);

    /* initialize */
    filt_init(dt,length);

    for (ix=0; ix < nx; ix++) {

	/* aperture */
	left  = (ix-aper < 0)?    0:    ix-aper;
	right = (ix+aper > nx-1)? nx-1: ix+aper;

	for (ic=left; ic <= right; ic++) {
	    
	    /* time delay */
	    tau = table[ix][ic];

	    /* distance */
	    dist = datum*datum+(ic-ix)*dx*(ic-ix)*dx;

	    /* filter (tau dependent) */
	    filt_set(tau);

	    shift = 0;
	    for (it=0; it < nt; it++) {
		if (((float)it)*dt < tau) 
		    continue;
		else if (shift == 0)
		    delta = (((float)it*dt)-tau)/dt;

		tr_out[ix][it] += 1./SF_PI
		    *dx*datum*tau/dist
		    *pick(delta,tr_in[ic],shift);
		shift++;
	    }
	}
    }

    /* write output */
    sf_floatwrite(tr_out[0],nt*nx,out);

    exit(0);
}
