/*
 * Copyright 1994-2012 The MathWorks, Inc.
 *
 * File: rtiostream_serial.c     
 *
 * Abstract:
 *  Serial communications channel for a Windows/UNIX machine
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h> 
#include <limits.h>
#include "rtiostream.h"
#include "tmwtypes.h"
#include <assert.h>

#ifdef _WIN32
/* WINDOWS */

#if defined(_MSC_VER)
 /* temporarily disable warning triggered
  * by windows.h */
 #pragma warning(push)
 #pragma warning(disable: 4255)
#endif

# include <windows.h>

#if defined(_MSC_VER)
 /* restore warning */
 #pragma warning(pop)
#endif

# ifdef __LCC__
#   include <errno.h>
#   ifndef MAXDWORD
#      define MAXDWORD 0xFFFFFFFF
#   endif
# endif

#else
#include <termios.h>/* POSIX terminal control definition*/
#include <unistd.h>/*UNIX standard function definitions*/
#include <fcntl.h> /* File control definition*/
#include <errno.h> /*To get a description of error */
#include <sys/ioctl.h> /*For IOCTL Functions*/
#endif

#ifdef USE_MEXPRINTF
#include "mex.h"
#define printf mexPrintf
#endif
                                         
/***************** DEFINES ****************************************************/

#define N_SERIAL_PORTS  10         /* Number of com ports allowed to open */
#define MAX_COM_LEN 30             /* length of com port name */
#define MAX_COM_PREFIX_LEN 7       /* Full prefix is \\.\COM  */
#define TMP_BUF_SIZ (40)
                                         
#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifdef _WIN32

#define COM_PORT_PREFIX "\\\\.\\"  /* includes escape chars, so this is really \\.\ */
#define PORTNAME_DEFAULT_VAL "\\\\.\\COM1" /* includes escape chars, so this is really \\.\COM1 */

#else /*UNIX*/

#define COM_PORT_PREFIX "/dev/"  
#define PORTNAME_DEFAULT_VAL "/dev/ttyS0" 

#endif

#define BAUD_DEFAULT_VAL 57600

/* define a set of verbosity levels:
 *
 * 0: no verbose output
 * 1: basic verbose output
 * 2: extra verbose output */
typedef enum {VERBOSITY_LEVEL_0=0, VERBOSITY_LEVEL_1, VERBOSITY_LEVEL_2} VerbosityLevel;
/* default verbosity */
#define DEFAULT_VERBOSITY VERBOSITY_LEVEL_0

#define READ_FILE_TIMEOUT 10000         /* 10 seconds */
#define WRITE_FILE_TIMEOUT 2000         /* 2 seconds. This should be large 
                                         * enough to send 512 bytes at the 
                                         * lowest possible baud rate. See
                                         * comments in serialDataSet for 
                                         * more details
                                         */

/***************** TYPEDEFS **************************************************/

typedef struct SerialCommsData_tag {
    int isInUse; /* flag to indicate whether an instance is in use */
    char        port[MAX_COM_LEN];
#ifdef _WIN32/*WIN32*/
    HANDLE      serialHandle;
#else /*UNIX*/
    int serialHandle;
#endif
    uint32_T    baud;
    VerbosityLevel verbosity;
} SerialCommsData;

/**************** LOCAL DATA *************************************************/

/* All local data resides in the per instance SerialCommsData structures to 
 * make sure each connection is completely independent.
 *
 * The static array will be deallocated when the shared library is unloaded. 
 *
 * Using an array rather than a linked list allows us to have fast direct lookup
 * of SerialCommsData from streamID during calls to rtIOStreamSend/Recv */
static SerialCommsData SerialData[N_SERIAL_PORTS];
static bool dataInitialised = false;

#ifdef _WIN32
/*
 * From http://msdn.microsoft.com/en-us/library/aa363190(v=vs.85).aspx:
 * For ReadFile:
 * If an application sets ReadIntervalTimeout and ReadTotalTimeoutMultiplier
 * to MAXDWORD and sets ReadTotalTimeoutConstant to a value greater than
 * zero and less than MAXDWORD, one of the following occurs when the
 * ReadFile function is called:
 * o If there are any bytes in the input buffer, ReadFile returns
 *   immediately with the bytes in the buffer.
 * o If there are no bytes in the input buffer, ReadFile waits until a
 *   byte arrives and then returns immediately.
 * o If no bytes arrive within the time specified by
 *   ReadTotalTimeoutConstant, ReadFile times out.
 * 
 * For WriteFile:
 * If the total number of bytes is not sent within the specified timeout,
 * the WriteFile operation will conclude returning the count of bytes that
 * was written. This is not considered an error.
 */
static COMMTIMEOUTS cto_timeout = { MAXDWORD,MAXDWORD,READ_FILE_TIMEOUT,0,WRITE_FILE_TIMEOUT};
static DCB dcb;

#else /*UNIX*/

/*
 * Refer to geck 700573 for resources used  
 * All the parameters defined for Termios structure which 
 * stores anything in relation to port attributes
*/
static struct termios sTermios;
#endif

/************** LOCAL FUNCTION PROTOTYPES ************************************/

static int serialDataSet(
    SerialCommsData *sd,
    const void *src,
    const size_t size,
    size_t *sizeSent);

static int serialDataGet(
    SerialCommsData *sd,
    char          *dst,
    const size_t   size,
    size_t        *sizeRecvd);

static int serialDataPending(
    SerialCommsData *sd,
    int    *outPending);

static int processArgs(
    const int      argc,
    void         * argv[],
    SerialCommsData *sd);

static void initSerialCommsDataStructure(
    void);

static SerialCommsData * getSerialData(int streamID);

/*************** LOCAL FUNCTIONS **********************************************/

/* Function: initSerialCommsDataStructure ===========================================================
 * Abstract:
 *  Initializes the data structures to zero.
 */
static void initSerialCommsDataStructure(void)
{
    if (!dataInitialised) {
        memset(&SerialData, 0, sizeof( SerialData ) );
        dataInitialised = true;
    }
}

#ifdef _WIN32
/* Function: initDCB ===========================================================
 * Abstract:
 *  Initializes the control settings for a win32 serial communications device.
 */
static void initDCB(uint32_T baud) 
{
    dcb.DCBlength       = sizeof(dcb);                   
        
    /* ---------- Serial Port Config ------- */
    dcb.BaudRate        = baud;
    dcb.Parity          = NOPARITY;
    dcb.fParity         = 0;
    dcb.StopBits        = ONESTOPBIT;
    dcb.ByteSize        = 8;
    dcb.fOutxCtsFlow    = 0;
    dcb.fOutxDsrFlow    = 0;
    dcb.fDtrControl     = DTR_CONTROL_DISABLE;
    dcb.fDsrSensitivity = 0;
    dcb.fRtsControl     = RTS_CONTROL_DISABLE;
    dcb.fOutX           = 0;
    dcb.fInX            = 0;
        
    /* ---------- Misc Parameters ---------- */
    dcb.fErrorChar      = 0;
    dcb.fBinary         = 1;
    dcb.fNull           = 0;
    dcb.fAbortOnError   = 0;
    dcb.wReserved       = 0;
    dcb.XonLim          = 2;
    dcb.XoffLim         = 4;
    dcb.XonChar         = 0x13;
    dcb.XoffChar        = 0x19;
    dcb.EvtChar         = 0;

} /* end initDCB */

#else /*UNIX */

/* Function: initTermios ===========================================================
 * Abstract:
 *  Initializes the control settings for a UNIX serial communications device.
 */
static  void initTermios(int fd, uint32_T baud) 
{
    tcgetattr(fd, &sTermios); /*Get the attributes set by default*/
    
    /* ---------- Serial Port Config ------- */
    sTermios.c_cflag |=(CLOCAL     /*To not become port 'owner'*/
                        |CREAD);   /*Allow reading of incoming data*/
    sTermios.c_cflag &= ~(CSTOPB   /*To have one stop bit */
                          |CSIZE); /*Mask Character size bites */
    sTermios.c_cflag &= ~(PARENB); /*Disable Parity Check*/
    sTermios.c_cflag |= CS8;       /*Character size at 8 bits */

    sTermios.c_lflag &= ~(ICANON   /*To have raw output*/
                          | ECHO   /*Disable input character echo*/
                          | ECHOE  /*Disable echo character erase*/
                          | ISIG); /*Disable SIGINTR, SIGSUSP, SIGDSUSP, 
                                     and SIGQUIT signals*/
    
    sTermios.c_cc[VMIN]  = 0;      /*To not have read operation dependent 
                                    on number of characters received*/
    sTermios.c_cc[VTIME] = (unsigned int)(READ_FILE_TIMEOUT/100);
                                   /* 10ths of seconds*/
    sTermios.c_cc[VSTART] = 0x13;  /*Start flow on XON char*/
    sTermios.c_cc[VSTOP] = 0x19;   /*Stop flow on XOFF char*/

    sTermios.c_iflag &= ~(IXON     /*Disable Software Flow Control*/
                          |IXOFF
                          |IXANY);

    sTermios.c_oflag &= ~OPOST;    /*Disable Post processing of output*/

    cfsetispeed(&sTermios, baud);  /*Set incoming Baud Rate*/
    cfsetospeed(&sTermios, baud);  /*Set outgoing Baud Rate*/

    /************Didn't Find Equivalent for following***************/
    /* Write timeout not available for UNIX*/
    /* No equivalent for XonLim and XoffLim or EvtChar*/
    /***************************************************************/

    /* -------- Serial Port Config END---- */

    tcsetattr(fd, TCSANOW, &sTermios);

}

#endif

/* Function: serialDataPending =================================================
 * Abstract:
 *  Returns true, via the 'pending' arg, if data is pending on the comm line.
 *  Returns false otherwise.
 *
 *  RTIOSTREAM_NO_ERROR is returned on success, RTIOSTREAM_ERROR on failure.
 */
static int serialDataPending(
    SerialCommsData *sd,
    int    *outPending)
{
    int retVal = RTIOSTREAM_NO_ERROR;

#ifdef _WIN32

    struct _COMSTAT status;
    unsigned long   etat;

    assert(sd->serialHandle != NULL);

    /* Find out how much data is available. */
    if (!ClearCommError(sd->serialHandle, &etat, &status)) {
	*outPending = 0;
        retVal = RTIOSTREAM_ERROR;
    } else {
	*outPending = status.cbInQue;
    }

#else /*UNIX*/

    int temp =0;

    assert(sd->serialHandle >= 0);

    /* Find out how much data is available. */
    temp = ioctl(sd->serialHandle, FIONREAD, outPending);
    if(temp<0)
    {
        retVal = RTIOSTREAM_ERROR;
        *outPending = 0; 
    }

#endif

    return retVal;
} /* end serialDataPending */ 


/* Function: serialDataGet =====================================================
 * Abstract:
 *  Attempts to gets the specified number of bytes from the specified serial.
 *  The number of bytes read is returned via the 'sizeRecvd' parameter.
 *  RTIOSTREAM_NO_ERROR is returned on success, RTIOSTREAM_ERROR is returned on
 *  failure.
 *
 * NOTES:
 *  o it is not an error for 'sizeRecvd' to be returned as 0
 *  o this function waits for at most READ_FILE_TIMEOUT  
 */
static int serialDataGet(
    SerialCommsData *sd,
    char          *dst,
    const size_t   size,
    size_t        *sizeRecvd)
{
    static const char *fnName = "serialDataGet:";
    int retVal = RTIOSTREAM_NO_ERROR;
    int avail = 0;    

#ifdef _WIN32
    DWORD sizeRecvdTemp = 0;
    assert( sd->serialHandle != NULL);
#else
    ssize_t sizeRecvdTemp = 0;
    assert(sd->serialHandle >= 0);
#endif

    *sizeRecvd = 0;
    if (size == 0) {
        /* return immediately if caller requested to read 0 bytes */
        return retVal;
    }
    
    retVal = serialDataPending( sd, &avail);
    if (retVal == RTIOSTREAM_ERROR || avail == 0) {
        if (retVal == RTIOSTREAM_ERROR) {
            printf( "%s Pending returned RTIOSTREAM_ERROR\n", fnName);
        }
        return retVal;
    }

#ifdef _WIN32
    if (!ReadFile( sd->serialHandle, dst, (DWORD) size, &sizeRecvdTemp, NULL))/*Error Condition check*/
#else /*UNIX*/
    sizeRecvdTemp = read(sd->serialHandle,dst,size);
    if(sizeRecvdTemp < 0) /*Error Condition check*/
#endif

    {
        printf( "%s ReadFile returned ERROR\n", fnName);
        retVal = RTIOSTREAM_ERROR;
        return retVal;
    }   

    *sizeRecvd = (size_t) sizeRecvdTemp;

    return retVal;
} /* end serialDataGet */ 


/* Function: serialDataSet =====================================================
 * Abstract:
 *  Utility function to send data via the specified serial
 */
static int serialDataSet(
    SerialCommsData *sd,
    const void *src,
    const size_t size,
    size_t *sizeSent)
{
    static const char *fnName = "serialDataSet:";
    int retVal = RTIOSTREAM_NO_ERROR;
    
    /* G861098: workaround an issue for some serial drivers (i.e. 
     * Arduino and C2000 USB based serial drivers). When the send operation 
     * times out for these drivers, they return that 0 bytes were sent. 
     * However, we know this is not true (i.e. we know they have actually 
     * sent non-zero bytes). The workaround is to limit the max size that 
     * one can send so it can be successfully sent with the 
     * WRITE_FILE_TIMEOUT of 2 seconds. The client code (PIL/ExtMode) 
     * is responsible to loop to send the whole amount of data.
     */
    const size_t maxAllowedTransferSize = 512;  /* in bytes */
    const size_t transferAmount = MIN(maxAllowedTransferSize, size);

#ifdef _WIN32
    DWORD sizeSentTemp = 0;
#else
    ssize_t sizeSentTemp = 0;
#endif
    *sizeSent = 0;
       
    if (size == 0) {
        /* return immediately if caller requested to write 0 bytes */
        return retVal;
    }
    
#ifdef _WIN32
    if (!WriteFile( sd->serialHandle, src, (DWORD) transferAmount, &sizeSentTemp, NULL))
#else /*UNIX*/
    sizeSentTemp = write(sd->serialHandle,src,transferAmount);
    
    /*G807280 Check the error number. If resource is "Temporarily Unavailable"
      don't error, but let caller application deal with zero data*/
    if((sizeSentTemp < 0) && ((errno == EAGAIN) || (errno == EWOULDBLOCK)))
    {
        sizeSentTemp = 0;
    }

    if(sizeSentTemp < 0)
#endif
    {
        printf( "%s WriteFile returned ERROR\n", fnName);
        retVal = RTIOSTREAM_ERROR;
    }
    
    *sizeSent = (size_t) sizeSentTemp;
    
    return retVal;
}

/* Function: serialDataFlush =================================================
 * Abstract:
 *  Utility function to flush a port
 */
static int serialDataFlush( 
    SerialCommsData *sd)
{
    char tmpBuf[TMP_BUF_SIZ];
    size_t numRecvd = 0;
    int pending = 0;
    int error;
    static const char *fnName = "serialDataFlush:";

    do {
        error = serialDataPending( sd, &pending);
        if ( (pending > 0) && (error==RTIOSTREAM_NO_ERROR) ) {
           if (sd->verbosity) {
              printf("serialDataFlush: pending = %d\n", pending);
           }
           error = serialDataGet( sd, tmpBuf, sizeof( tmpBuf), &numRecvd);
           if (sd->verbosity) {
              size_t currElement;
              printf("serialDataFlush: sizeRecvd = %lu: ", (unsigned long) numRecvd);
              for (currElement = 0; currElement < numRecvd; currElement++) {
                 printf("%u ", (unsigned char) tmpBuf[currElement]);
              }       
              printf("\n");
           }
        }
    }  while (  (pending > 0) && (error==RTIOSTREAM_NO_ERROR) && numRecvd > 0);
    if (error == RTIOSTREAM_ERROR) {
        printf( "%s Flushing returned RTIOSTREAM_ERROR\n", fnName);
    }
    return error;
}

/* Function: processArgs ====================================================
 * Abstract:
 *  Process the arguments specified by the user when opening the rtIOStream.
 *      
 *  If any unrecognized options are encountered, ignore them.
 *
 * Returns zero if successful or RTIOSTREAM_ERROR if 
 * an error occurred.
 *
 *  o IMPORTANT!!!
 *    As the arguments are processed, their strings should be set to NULL in
 *    the argv array. 
 */
static int processArgs(
    const int      argc,
    void         * argv[],
    SerialCommsData *sd)
{
    int        retVal    = RTIOSTREAM_NO_ERROR;
    int        count           = 0;
    
    while(count < argc) {
        const char *option = (char *)argv[count];
        count++;
        
        if (option != NULL) {
            
            if ((strcmp(option, "-port") == 0) && (count != argc)) {
                const char *portNameOrNum = (char *)argv[count];
                char portName[MAX_COM_LEN] = "";
				    char fullPortName[MAX_COM_LEN] = "";
                count++;     
                
                if ((portNameOrNum == NULL) ||
                        (strlen(portNameOrNum) > (MAX_COM_LEN - MAX_COM_PREFIX_LEN -1) )){
                    printf( "Length of COM port name %s exceeds allowed limit %d.\n",
                            portNameOrNum, (MAX_COM_LEN - MAX_COM_PREFIX_LEN -1) );
                    retVal = RTIOSTREAM_ERROR;
                    break;
                }
                {
                   char tmpstr[2];
                   int  portNum;
                   /*  Support existing external mode API which allows passing
                    *  in port number, so "1" translates to "COM1" 
                    */
                   if (sscanf(portNameOrNum,"%d%1s", &portNum, tmpstr) == 1) {
                      /* user passed port number */
#ifdef _WIN32             
                      sprintf(portName, "COM%d", portNum); 				
#else
                      sprintf(portName, "ttyS%d", portNum); 				
#endif

                   } else {
                      /* user passed port name */
                      strcpy(portName, portNameOrNum);
                   }
                }

                /* Use the full COM port name if not fully specified */
                if (strncmp(portName, COM_PORT_PREFIX, strlen(COM_PORT_PREFIX)) != 0) {
                   strcat(fullPortName, COM_PORT_PREFIX);
                   strcat(fullPortName, portName);
                }
                else {
                   strcpy(fullPortName, portName);
                }

                if (strlen (fullPortName) > MAX_COM_LEN - 1) {
                   retVal = RTIOSTREAM_ERROR;
                   break;
                } else {                                        
                   strcpy( sd->port, fullPortName);										
                   argv[count-2] = NULL;
                   argv[count-1] = NULL;
                }           

            } else if ((strcmp(option, "-baud") == 0) && (count != argc)) {
                int itemsConverted;
                int baudNum;
                const char *baudStr = (char *)argv[count];
                
                count++;

                itemsConverted = sscanf(baudStr,"%d", &baudNum);

                if ((itemsConverted != 1) || (baudNum < 0)) {
                    retVal = RTIOSTREAM_ERROR;
                    break;
                } else {
                    sd->baud = (uint32_T) baudNum;
                    argv[count-2] = NULL;
                    argv[count-1] = NULL;
                }
            } else if ((strcmp(option, "-verbose") == 0) && (count != argc)) {
               int itemsConverted;
               int verbosity;
               const char *verbosityStr = (char *)argv[count];
               count++;
               itemsConverted = sscanf(verbosityStr,"%d", &verbosity);

               if ((itemsConverted != 1) || (verbosity < 0)) {
                  retVal = RTIOSTREAM_ERROR;
                  break;
               } else {
                  sd->verbosity = (VerbosityLevel) verbosity;
                  argv[count-2] = NULL;
                  argv[count-1] = NULL;
               }
            } else {
                /* do nothing */
            }
        }
    }
    return retVal;
}


static int serialPortOpenInitialize(SerialCommsData* sd, const int streamID,int argc, void* argv[])
{
    int errorCode = RTIOSTREAM_NO_ERROR;
#ifdef _WIN32
    HANDLE serialHandle;
#else
    int serialHandle;
#endif
    int closeFile = false;
    int result;

    sd->baud = BAUD_DEFAULT_VAL;
    strcpy(sd->port, PORTNAME_DEFAULT_VAL);
    sd->verbosity = DEFAULT_VERBOSITY;

    result = processArgs(argc, argv, sd);
    
    if (result == RTIOSTREAM_ERROR) {
        printf( "processArgs failed\n");
        errorCode = RTIOSTREAM_ERROR;
        goto EXIT_POINT;
    }

    if (sd->verbosity) {
       printf("rtIOStreamOpen (connection id %d): port %s, baud %lu\n", streamID, sd->port, (unsigned long) sd->baud);
    }
    
#ifdef _WIN32
    initDCB( sd->baud ); 
    serialHandle = (void *) CreateFile( sd->port, 
                                        GENERIC_READ | GENERIC_WRITE,
                                        0, NULL, OPEN_EXISTING,
                                        FILE_ATTRIBUTE_NORMAL, NULL);

    if (serialHandle == INVALID_HANDLE_VALUE) {

        DWORD err = GetLastError( );
        printf( "Open serial port failed, error %d or 0x%08x.", err, err);
#else/*UNIX*/
        initTermios(sd->serialHandle, sd->baud);

        serialHandle = open(sd->port, O_RDWR /*Enable Read and Write Operations*/
                            | O_NOCTTY       /*Not controlling flag specified*/
                            | O_NONBLOCK);   /*Make the port non -blocking*/

        if (serialHandle == -1) {            /*-1 returned on error by OPEN*/
            printf("Open serial port:%s  failed, error %d: %s", sd->port,errno,strerror(errno));
#endif

        printf( "Possible causes "
                "are:\n    a) The target is not powered on. \n    "
                "b) The specified port number is not correct. \n    "
                "c) The specified bit rate is not "
                "supported by the host machine.\n    d) The previous "
                "connection was not closed correctly. "
                "If this is the case, you may need to re-start MATLAB.\n");

        errorCode = RTIOSTREAM_ERROR;
        goto EXIT_POINT;
    }

    sd->serialHandle = serialHandle;

#ifdef _WIN32

    if (!SetCommTimeouts(serialHandle, &cto_timeout)) {
        printf( "SetCommTimeouts failed\n");
        errorCode = RTIOSTREAM_ERROR;
        closeFile = true;
        goto EXIT_POINT;
    }

    if (!SetCommState(serialHandle, &dcb)) {
        printf( "SetCommState failed\n");
        errorCode = RTIOSTREAM_ERROR;
        closeFile = true;
        goto EXIT_POINT;
    }

#endif    
    /*UNIX has this done with setting of termios data 
      structure in initTermios*/

    result = serialDataFlush( sd);      /* clear out old data on the port */
    
    if (result == RTIOSTREAM_ERROR) {
        printf( "serialDataFlush failed\n");
        errorCode = RTIOSTREAM_ERROR;
        closeFile = true;
        goto EXIT_POINT;
    }

  EXIT_POINT:
    if (closeFile) {
#ifdef _WIN32
        CloseHandle(serialHandle);
#else
        close(serialHandle);
#endif
    }
    return errorCode;
}

/* Function: getSerialData =================================================
 * Abstract:
 *  Retrieves a SerialCommsData instance given its streamID. 
 *
 * NOTE: An invalid streamID will lead to a NULL pointer being returned 
 */
static SerialCommsData * getSerialData(int streamID) {
   /* return NULL for invalid or uninitialized streamIDs */
   SerialCommsData * sd = NULL;
   if ((streamID >= 0) && (streamID < N_SERIAL_PORTS)) {
      if (SerialData[streamID].isInUse) {
         sd = &SerialData[streamID];
      }
   }
   return sd;
}

/***************** VISIBLE FUNCTIONS ******************************************/

/* Function: rtIOStreamOpen =================================================
 * Abstract:
 *  Open the connection with the target.
 */
int rtIOStreamOpen(int argc, void * argv[])
{    
    int streamID;
    int errorCode;
    SerialCommsData *sd;

    initSerialCommsDataStructure();

    /* Find any free ports */
    for (streamID = 0; streamID < N_SERIAL_PORTS; streamID++) {
        if (!SerialData[streamID].isInUse) {
            break;
        }
    }
    if (streamID == N_SERIAL_PORTS) {
        printf( "All %d elements of the SerialCommsData structure are already in use.",  N_SERIAL_PORTS );
        return RTIOSTREAM_ERROR;
    }

    sd = &SerialData[streamID];

    errorCode  = serialPortOpenInitialize(sd,streamID,argc,argv);
    if (errorCode == RTIOSTREAM_NO_ERROR) {
       /* flag instance as in use */
       SerialData[streamID].isInUse = 1;
       return streamID;
    }
    else {
       /* flag error */
       return RTIOSTREAM_ERROR;
    }
}



/* Function: rtIOStreamSend =====================================================
 * Abstract:
 *  Sends the specified number of bytes on the comm line. Returns the number of
 *  bytes sent (if successful) or a negative value if an error occurred. As long
 *  as an error does not occur, this function is guaranteed to set the requested
 *  number of bytes; the function blocks if the TCP/IP send buffer doesn't have
 *  room for all of the data to be sent
 */
int rtIOStreamSend(
    int streamID,
    const void * const src,
    size_t size,
    size_t *sizeSent)
{
    int retVal;
    SerialCommsData *sd = getSerialData(streamID);
    if (sd == NULL) {
       retVal = RTIOSTREAM_ERROR;
       return retVal;
    }
    retVal = serialDataSet( sd, src, size, sizeSent);
    if (sd->verbosity) {
       printf("rtIOStreamSend (connection id %d): size = %lu, sizeSent = %lu", 
             streamID, 
             (unsigned long) size, 
             (unsigned long) *sizeSent);
       if (sd->verbosity >= VERBOSITY_LEVEL_2) {
          size_t currElement;
          printf(": ");
          for (currElement = 0; currElement < *sizeSent; currElement++) {
             printf("%u ", ((const unsigned char *) src)[currElement]);
          }       
       }
       printf("\n");
    }
    return retVal;
}


/* Function: rtIOStreamRecv ================================================
 * Abstract: receive data
 *
 */
int rtIOStreamRecv(
    int      streamID,
    void   * const dst, 
    size_t   size,
    size_t * sizeRecvd) 
{   
    int retVal = RTIOSTREAM_NO_ERROR;
    SerialCommsData *sd = getSerialData(streamID);
    if (sd == NULL) {
       retVal = RTIOSTREAM_ERROR;
       return retVal;
    }
    retVal = serialDataGet( sd, (char *)dst, size, sizeRecvd);
    if (sd->verbosity) {
       printf("rtIOStreamRecv (connection id %d): size = %lu, sizeRecvd = %lu", 
             streamID, (unsigned long) size, (unsigned long) *sizeRecvd);
       if (sd->verbosity >= VERBOSITY_LEVEL_2) {
          size_t currElement;
          printf(": ");
          for (currElement = 0; currElement < *sizeRecvd; currElement++) {
             printf("%u ", ((unsigned char *) dst)[currElement]);
          }       
       }
       printf("\n");
    }
    return retVal;
}


/* Function: rtIOStreamClose ================================================
 * Abstract: close the connection.
 *
 */
int rtIOStreamClose(int streamID)
{
    int retVal = RTIOSTREAM_NO_ERROR;
    SerialCommsData *sd = getSerialData(streamID);
    if (sd == NULL) {
       retVal = RTIOSTREAM_ERROR;
       return retVal;
    }
    retVal = serialDataFlush( sd);
#ifdef _WIN32
    CloseHandle(sd->serialHandle);
    sd->serialHandle = 0;
#else
    close(sd->serialHandle);
    sd->serialHandle = -1;
    /*because unlike Windows which uses a pointer it uses an
      int File descriptor which can be 0*/
#endif
    /* clear in use flag */
    sd->isInUse = 0;

    if (sd->verbosity) {
       printf("rtIOStreamClose (connection id %d)\n", streamID);
    }

    return retVal;
}
