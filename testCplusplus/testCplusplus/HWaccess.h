/*
 * Steuerung ob Simulation oder HW Plattform (C Interface)
 *
 * Diese Datei MUSS ueberall includiert werden, wo auf die HW zugegriffen wird.
 *
 */

/*
 * Ueber SIMULATION wird zwischen Simulation und HW umgeschaltet
 *
 * Damit die Aenderungen beachtet werden, muss Check Dependencies On/Off -> Check User Headers Only
 * gesetzt sein.
 *
 * Zur Not : Ein Clean auf das Projekt ausfuehren
 */

//#define SIMULATION

// Die drei folgenden includes duerfen nur in dieser Datei stehen

#include <stdio.h>
#include <sys/neutrino.h>
#include <hw/inout.h>

#ifdef SIMULATION
#include <ioaccess.h>
#endif

// End of File
