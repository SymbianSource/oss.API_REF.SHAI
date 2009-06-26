/*
  CpsKernelIf.h

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

#ifndef __CPSKERNELIF_H__
#define __CPSKERNELIF_H__

//  - Includes ------------------------

//  - Namespace -----------------------

//  - Macros --------------------------

//  - Constants -----------------------

//  - External data -------------------

//  - Forward declarations ------------

class DCpsLddFactory;
class TCpsCallback;

//  - Data types ----------------------

//  - Class declarations --------------

/**
 * CPS interface for kernel side clients
 */
class DCpsKernelIf : public DBase
    {
public:
    /** 
     * Returns data stored into record (synchronous).
     *
     * @param  aGroup      The group ID which is accessed.
     * @param  aIndex      The index ID which is accessed.
     * @param  aLength     The size of data to be read from the beginning of record.
     * @param  aDataBuffer The pointer to data buffer that contains read data.
     * 
     * @return KErrNone or standard error code
     */
    IMPORT_C static TInt ReadRecord( TUint16 aGroup, TUint16 aIndex, TUint32 aLength, TDes8& aDataBuffer );
    
    /** 
     * Returns data stored into record (asynchronous).
     *
     * @param  aCb         The pointer to a CPS callback object.
     * @param  aGroup      The group ID which is accessed.
     * @param  aIndex      The index ID which is accessed.
     * @param  aLength     The size of data to be read from the beginning of record.
     * @param  aDataBuffer The pointer to data buffer that contains read data.
     */
    IMPORT_C static void ReadRecord( TCpsCallback* aCb, TUint16 aGroup, TUint16 aIndex, TUint32 aLength, TDes8& aDataBuffer );

    /**
     * Used to store data into record (synchronous).
     *
     * @param  aGroup      The group ID which is accessed.
     * @param  aIndex      The index ID which is accessed.
     * @param  aLength     The size of data to be written into record.
     * @param  aDataBuffer The pointer to data buffer that contains data.
     * 
     * @return KErrNone or standard error code
     */
    IMPORT_C static TInt WriteRecord( TUint16 aGroup, TUint16 aIndex, TUint32 aLength, const TDesC8& aDataBuffer );
        
    /**
     * Used to store data into record (asynchronous).
     *
     * @param  aCb         The pointer to a CPS callback object.
     * @param  aGroup      The group ID which is accessed.
     * @param  aIndex      The index ID which is accessed.
     * @param  aLength     The size of data to be written into record.
     * @param  aDataBuffer The pointer to data buffer that contains data.
     */
    IMPORT_C static void WriteRecord( TCpsCallback* aCb, TUint16 aGroup, TUint16 aIndex, TUint32 aLength, const TDesC8& aDataBuffer );

    /**
     * Used to remove existing record (synchronous).
     *
     * @param  aGroup      The group ID which is accessed.
     * @param  aIndex      The index ID which is accessed.
     * 
     * @return KErrNone or standard error code   
     */
    IMPORT_C static TInt RemoveRecord( TUint16 aGroup, TUint16 aIndex );
    
    /**
     * Used to remove existing record (asynchronous).
     *
     * @param  aCb         The pointer to a CPS callback object.
     * @param  aGroup      The group ID which is accessed.
     * @param  aIndex      The index ID which is accessed.   
     */
    IMPORT_C static void RemoveRecord( TCpsCallback* aCb, TUint16 aGroup, TUint16 aIndex );

    /**    
     * Used to remove all existing records from given group (synchronous).
     *
     * @param  aGroup      The group ID which is accessed.
     * 
     * @return KErrNone or standard error code
     */
    IMPORT_C static TInt RemoveAllRecords( TUint16 aGroup );

    /**    
     * Used to remove all existing records from given group (asynchronous).
     *
     * @param  aCb         The pointer to a CPS callback object.
     * @param  aGroup      The group ID which is accessed.  
     */
    IMPORT_C static void RemoveAllRecords( TCpsCallback* aCb, TUint16 aGroup );
    
    /**
     * Used to query size of existing record (synchronous).
     *
     * @param  aGroup      The group ID which is accessed.
     * @param  aIndex      The index ID which is accessed.
     * @param  aSize       CPS stores record size to this parameter.
     * 
     * @return KErrNone or standard error code     
     */
    IMPORT_C static TInt RecordSizeGet( TUint16 aGroup, TUint16 aIndex, TUint32& aSize );
    
    /**
     * Used to query amount of memory used by given group (synchronous).
     *
     * @param  aGroup      The group ID which is accessed.
     * @param  aSize       CPS stores amount of used memory by aGroup to this parameter.
     * 
     * @return KErrNone or standard error code   
     */
    IMPORT_C static TInt GroupSizeGet( TUint16 aGroup, TUint32& aSize );

    /**
     * Used to amount of available memory for given group (synchronous).
     *
     * @param  aGroup      The group ID which is accessed.
     * @param  aSize       CPS stores amount of available memory to this parameter.
     * 
     * @return KErrNone or standard error code     
     */
    IMPORT_C static TInt AvailableSizeGet( TUint16 aGroup, TUint32& aSize );

    /**
      * Cancels ongoing client request. 
      * 
      * @note Client's callback is called with KErrCancel status if request is removed successfully from the operation queue
      * 
      * @param  aCb         The pointer to a CPS callback object.
      */
    IMPORT_C static void CancelRequest( TCpsCallback* aCb );
        
    /**
     * CPS factory calls this to create kernel IF
     *
     * @note For CPS internal use only
     *
     * @param aFactoryObj   Factory object
     */
    static void CreateKernelInstance( DCpsLddFactory* aFactoryObj );

    /**
     * CPS factory calls this to delete kernel IF
     *
     * @note For CPS internal use only
     */
    static void DeleteKernelInstance();
    
private:
    
    /**
     * Used to query size of existing record (asynchronous).
     *
     * @param  aCb         The pointer to a CPS callback object.
     * @param  aGroup      The group ID which is accessed.
     * @param  aIndex      The index ID which is accessed.
     * @param  aSize       CPS stores record size to this parameter.     
     */
    static void RecordSizeGet( TCpsCallback* aCb, TUint16 aGroup, TUint16 aIndex, TUint32& aSize );

    /**
     * Used to query amount of memory used by given group (asynchronous).
     *
     * @param  aCb         The pointer to a CPS callback object.
     * @param  aGroup      The group ID which is accessed.
     * @param  aSize       CPS stores amount of used memory by aGroup to this parameter.   
     */
    static void GroupSizeGet( TCpsCallback* aCb, TUint16 aGroup, TUint32& aSize );
    
    /**
     * Used to amount of available memory for given group.
     *
     * @param  aCb         The pointer to a CPS callback object.
     * @param  aGroup      The group ID which is accessed.
     * @param  aSize       CPS stores amount of available memory to this parameter.     
     */
    static void AvailableSizeGet( TCpsCallback* aCb, TUint16 aGroup, TUint32& aSize );
        
    /**
     * Callback function for synchronous CPS kernel operation.
     * 
     * @ param aStatus KErrNone or standard error code
     * @ aArg Argument for callback
     */
    static void SyncOperationReady( TInt aStatus, TAny* aArg );
    
private:
    /**
     * Constructor
     */
    DCpsKernelIf();
    
    /**
     * Destructor
     */
    ~DCpsKernelIf();
    
private:
    /** Kernel IF object */
    static DCpsKernelIf* iKernelIf;
    
    /** Factory object */
    static DCpsLddFactory* iFactory;
    
    /** Callback for synchronous operations */
    TCpsCallback* iSyncCb;
    
    /** Semaphore for locking the synchronous interface */
    DSemaphore *iSyncLock;
    
    /** Synchronous operation result */
    TInt iSyncOpResult;
    };


/**
 * CPS asynchronous callback function 
 */
typedef void (*TCpsCbFn)( TInt aResult, TAny* aParam );

/**
 * CPS asynchronous callback DFC
 * The client must create one of these to be passed to each asynchronous call to kernel interface
 * The callback function is called in the context supplied by the client when creating an object of this kind (aQue)
 * The callback function takes as arguments the pin id and the state, so it can be common to all TGpioCallback
 */
class TCpsCallback : public TDfc
    {
public:
    inline TCpsCallback( TCpsCbFn aFn, TAny* aPtr, TDfcQue* aQue, TInt aPriority )
        : TDfc( DfcFunc, this, aQue, aPriority ), iParam( aPtr ), iCallback( aFn ) 
            {}
private:
    inline static void DfcFunc( TAny* aPtr )
        {
        TCpsCallback* pCb = (TCpsCallback*)aPtr;
        //Warning -- Possible use of null pointer
        //lint -e613
        pCb->iCallback( pCb->iResult, pCb->iParam );
        }
public:
    TInt iResult;
    TAny* iParam;
    TCpsCbFn iCallback;
    };

#endif /* __CPSKERNELIF_H__ */

