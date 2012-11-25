/*
 * @file Messages.h
 *
 * @author	Mahmoud Dariti
 * @author	Mohamed Sakhri
 * @date Nov 25, 2012
 *
 *
 *	This header contains en enum of all possible messages, which could be sent as pulses
 *	from Demupltiplexer to Dispatcher or from Controller to Dispatcher
 *	Dispatcher has an event handler table, where it assigns "each" message to an event handler
 */
#ifndef MESSAGES_H_
#define MESSAGES_H_

//TODO  filter which messages are useless and may be assign some numbers
// to each message instead of the default ones used by enum.
enum message {
	// Message's for interrupt's from Port B
	WP_IN_ENGINE_START,
	WP_OUT_ENGINE_START,
	WP_IN_HEIGHT_M,
	WP_OUT_HEIGHT_M,
	WP_IN_TOLERANCE_R,
	WP_NOT_IN_TOLERANCE_R,
	WP_IS_METAL,
	WP_NOT_METAL,
	WP_IN_SWITCH,
	WP_OUT_SWITCH,
	SWITCH_IS_OPEN,
	SWITCH_IS_CLOSED,
	WP_IN_SLIDE,
	WP_OUT_SLIDE,
	WP_IN_ENGINE_END,
	WP_OUT_ENGINE_END,

	// Messages for Interrupt's from Port C
	START_PRESSED,
	START_RELEASED,
	STOP_PRESSED,
	STOP_RELEASED,
	RESET_PRESSED,
	RESET_RELEASED,
	E_STOP_PRESSED,
	E_STOP_RELEASED,

	// Messages for errors. Those can be sent from Controller to dispatcher in case of errors
	WP_IS_MISSING,		// a workpiece disappears or arrives to late
	WP_IS_STRANGER,		// an unknown workpiece in engine or a workpiece arrives too early
	WP_NOT_TURNED,		// Error from band2 if workpiece has not been turned in the end of band1
	SLIDE_FULL
	// More specified errors are possible and could be added as messages here. May be later!
} ;


#endif /* MESSAGES_H_ */
