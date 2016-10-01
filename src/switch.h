/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */


#ifndef SWITCH_H
#define	SWITCH_H

#define SW1 PORTDbits.RD7
#define PRESSED 0
#define RELEASED 1

void initializeSwitches();
void initSwitchReset();
void initSwitchStartStop();

#endif	/* SWITCH_H */

