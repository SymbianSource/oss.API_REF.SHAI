/*
  idletimer.h

  Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies). 
  All rights reserved.

  This program and the accompanying materials are made available 
  under the terms of the Eclipse Public License v1.0 which accompanies 
  this distribution, and is available at 
  http://www.eclipse.org/legal/epl-v10.html

  Initial Contributors:
  Nokia Corporation - initial contribution.

  Contributors:
*/
// Description
// 

#ifndef IDLETIMER_H
#define IDLETIMER_H

#include <nkern.h>

/**
@file API for Idle Timers
@publishedPartner
@prototype
*/

/**
@publishedPartner
@prototype

Idle Timer class. These are a timers which allow the client to specify a window in which
the timer should queue a Dfc. The implementation aligns multiple timers to allow the device
to spend longer periods in low power modes, thus saving power.
 */	
NONSHARABLE_CLASS(TIdleTimer)
    {
public:
	static const TInt KNoTimeout = -1;
	
	enum TFault
		{
		
		/**
		This fault is raised from TIdleTimer::SetDfcQ if an attempt is made to set the Dfc
		queue for an Idle Timer where one has already been set.
		*/
		EDfcQueAlreadySet = 0,
		
		/**
		This fault is raised from TIdleTimer::SetFunciton if an attempt is made to change
		the function the Dfc callback should call whilst either a OneShot or Periodic
		request is outstanding on the Idle Timer.
		*/		
		ESetFunctionCalledOnPendingTimer = 1,
		
		/**
		This fault is raised if either TIdleTimer::OneShot or TIdleTimer::Periodic is
		called but no Dfc queue has been set for the Idle Timer.
		*/
		ENoDfcQSet = 2
		};
	
public:
	/** Idle Timer constructor

	@param	aFunction, function to call on completion of the timer
	@param	aPtr, parameter to be passed to function callback
	@param	aPriority, priority of DFC within the queue (0 to 7, where 7 is highest)
	*/
	IMPORT_C TIdleTimer(TDfcFn aFunction, TAny* aPtr, TInt aPriority);

	/** Idle Timer constructor

	@param	aFunction, function to call on completion of the timer
	@param	aPtr, parameter to be passed to function callback
	@param	aDfcQ, pointer to a DFC queue on which this Idle Timer should queue 
			the DFC callback on timer completion.
	@param	aPriority, priority of DFC within the queue (0 to 7, where 7 is highest)
	*/
	IMPORT_C TIdleTimer(TDfcFn aFunction, TAny* aPtr, TDfcQue* aDfcQ, TInt aPriority);

	/** Set the Dfc queue on which this Idle Timer should make its Dfc callback on
		completion of the timer.

	A Dfc queue must be set either with this function or from the TIdleTimer
	constructor before the Idle Timer can be used – not doing so will fault the
	kernel when the Idle Timer is scheduled.

	This function should only be used in the initialization of the Idle Timer,
	when it has not previously had a Dfc queue set. This function does not move
	the Idle Timer from one queue to another –attempting to do so will fault the kernel.

	@param	aDfcQ, pointer to a DFC queue on which this Idle Timer should queue 
			the DFC callback on timer completion.
	*/
	IMPORT_C void SetDfcQ(TDfcQue* aDfcQ);

	/** Sets the function to be run when the Idle Timer is completed. This function
	may only be called when the Idle Timer is not queued - attempting otherwise will
	fault the kernel.

	@param	aDfcFn, The function called when the TIdleTimer expires
	*/
	IMPORT_C void SetFunction(TDfcFn aDfcFn);
	
	/** Starts a one-shot Idle Timer
	
	The timer will queue a Dfc callback at a time (in nanokernel ticks) between aTime
	and aMaxTime after this function is called. The callback will be made to the previously
	set DfcFn on the requested DfcQue.
	
	If the default value of KNoTimeout is specified for aMaxTime the Idle Timer will
	have no upper bound on when to schedule the DFC callback. As such, if the device was
	idle at the time aTime number of ticks after the OneShot request was made, the
	Idle Timer will not be completed (i.e. the Dfc callback will not be queued) until the next
	occasion the device comes out of idle.
	
	@param	aTime the minimum number of nanokernel ticks after which the Dfc callback
			is to be be queued.
	@param	aMaxTime the maximum number of nanokernel ticks before which the Dfc
			callback must be queued.
	@return	KErrNone if no error, KErrInUse if timer is already active, KErrArgument if
			aMaxTime is neither greater than aMinTime nor equal to TIdleTimer::KNoTimeout

	@pre    No fast mutex can be held.
	@pre    Kernel must be unlocked.
	@pre    Call in a thread context.
	@pre    Interrupts must be enabled.
	
	@see	NKern::TimerTicks()
	*/
    IMPORT_C TInt OneShot(TInt aTime, TInt aMaxTime = KNoTimeout);

	/** Starts a periodic Idle Timer
	
	The timer will queue a DFC callback at a time (in nanokernel ticks) between aTime and aMaxTime
	after this function is called, and then at successive intervals somewhere between aTime
	and aMaxTime after the previous queuing. The callback will be made to the previously set
	DfcFn on the requested DfcQue. Since the callback is queued automatically, the Idle Timer
	must be explicitly cancelled after Periodic is called on it before it can safely go out of scope.
	
	If the default value of KNoTimeout is specified for aMaxTime, the Idle Timer will have no
	maximum timeout each cycle. In this case, if the device was idle at the minimum expiry time
	(aTime + time of previous expiry) queuing of the Dfc will not occur until the next time the
	device comes out of idle.

	@param	aTime – the minimum number of nanokernel ticks from the previous completion
			after which the Dfc callback is to be queued.
	@param 	aMaxTime – the maximum number of nanokernel ticks after the previous
			completion before which the Dfc callback must be queued.
	@return	KErrNone if no error, KErrInUse if timer is already active, KErrArgument if 
			aMaxTime is neither greater than aMinTime nor equal to TIdleTimer::KNoTimeout
	
	@pre    No fast mutex can be held.
	@pre    Kernel must be unlocked.
	@pre    Call in a thread context.
	@pre    Interrupts must be enabled.
	
	@see    NKern::TimerTicks()
	*/
    IMPORT_C TInt Periodic(TInt aTime, TInt aMaxTime = KNoTimeout);
	
	/** Cancels an Idle Timer
	
	This function does nothing if the Idle Timer is not scheduled.

	Note that the implementation of this function is such that, if Cancel is called from a
	thread (i.e. DFC queue) other than the one that the callback is to be made on…
		•	if the callback has started, Cancel will block until the callback has finished
		•	if the callback hasn’t started, Cancel will ensure that it won’t run after Cancel
			has returned
	In order to do this, if called from a different thread, the Cancel function blocks the calling
	thread on a semaphore until the DFC queue thread used for the callback eventually signals it.
	Given this, if the callback function somehow reciprocally blocks on the thread that is calling
	Cancel, a deadlock could occur. It is up to the client to ensure this doesn’t happen.
	
	To re-iterate - the deadlock scenario described above is only a possibility if Cancel is called
	from a different thread (i.e. DFC queue) than that in which the callback is made. If Cancel
	is called from the same thread then there’s nothing to worry about in this respect.
	
	@pre    No fast mutex can be held.
	@pre    Kernel must be unlocked.
	@pre    Call in a thread context.
	@pre    Interrupts must be enabled.
	*/
    IMPORT_C void Cancel();

private:
	TInt iData[20];	//Reserved space for implementation
    };

#endif //IDLETIMER_H
