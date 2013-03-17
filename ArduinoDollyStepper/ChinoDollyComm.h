#ifndef __ChinoDollyComm__
#define __ChinoDollyComm__


/*
	Definitions of the command IDs
*/

#define CMD_MOVE_FORWARD	0
#define CMD_MOVE_BACKWARD	1
#define CMD_CALIBRATE		2
#define CMD_TILT_UP			3
#define CMD_TILT_DOWN		4
#define CMD_SHIFT_LEFT		5
#define CMD_SHIFT_RIGHT		6
#define CMD_SET_SPEED		7


/*
	Definition of the communication messages
*/

typedef struct
{
	unsigned char ReqId;
	unsigned char Val;
}tDollyRequest;

/* TODO
typedef struct
{
	unsigned char RespCode;
	unsigned char RespVal;
}tDollyResponse;
*/
#endif