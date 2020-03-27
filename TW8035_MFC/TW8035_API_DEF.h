//#define WM_COMM_RX_CNT				0x4000+10	// Recv Count Event Message. (wParam = UINT)

// Recv Data Event Message. (wParam = unsigned short *)
#define WM_COMM_RX_DATA				0x4000+11	
// Recv Calibration Data Event Message. (wParam = unsigned short *)
#define WM_COMM_RX_CAL_DATA			0x4000+12	
// Recv Data Event Message. (wParam = unsigned short *)
#define WM_COMM_RECV_INFO			0x4000+41	
// Recv Radio Offset Message (wParam == int)
#define WM_COMM_RECV_RADIO			0x4000+51

/// <summary>
/// Test Method
/// </summary>
/// <returns>123</returns>
extern "C" __declspec(dllimport) int test1(void);

/// <summary>
/// Request Port List
/// </summary>
/// <param name="int">TYPE Enum. 0 = All, 1 = Only TW8035</param>
/// <returns>IntPtr. Cast String for use. For C#</returns>
extern "C" __declspec(dllimport) int* getPortListForCSharp(int);

/// <summary>
/// Request Serial Port Close
/// </summary>
/// <param name="hWnd">Window Handle</param>
/// <returns>CString (ex:"|COM1|COM2"). For MFC</returns>
extern "C" __declspec(dllimport) CString getTW8035PortList(void);

/// <summary>
/// Request Serial Port Connect For C#
/// </summary>
/// <param name="hWnd">Window Handle</param>
/// <param name="BSTR">Port Name</param>
/// <returns>Success</returns>
extern "C" __declspec(dllimport) BOOL serialPortConnectWrapper(HWND, BSTR);
 
/// <summary>
/// Request Serial Port Connect for MFC
/// </summary>
/// <param name="CWnd">Window Handle</param>
/// <param name="CString">Port Name (ex:'com7')</param>
/// <returns>Success</returns>
extern "C" __declspec(dllimport) BOOL serialPortConnect(CWnd*, CString);

/// <summary>
/// Request Serial Port Close For MFC
/// </summary>
/// <param name="hWnd">Window Handle</param>
/// <returns>Success</returns>
extern "C" __declspec(dllimport) bool serialPortClose(CWnd*);

/// <summary>
/// Request Serial Port Close For C#
/// </summary>
/// <param name="hWnd">Window Handle</param>
/// <returns>Success</returns>
extern "C" __declspec(dllimport) bool serialPortCloseWrapper(HWND);

/// <summary>
/// Streaming Mode ON
/// Only returns whether the transfer was successful.
/// he data must be received in a message.
/// MESSAGE_ID = 0x4011
/// </summary>
/// <returns>Success</returns>
extern "C" __declspec(dllimport) BOOL requestRunStreamingMode(void);

/// <summary>
/// Streaming Mode OFF
/// </summary>
/// <returns>Success</returns>
extern "C" __declspec(dllimport) BOOL requestStop(void);

/// <summary>
/// Request Recv count.
/// </summary>
/// <returns>Recive Count</returns>
extern "C" __declspec(dllimport) UINT requestRecvCnt(void);

/// <summary>
/// Streaming Mode ON
/// </summary>
/// <param name="char">Flip. 1 = on</param>
/// <param name="char">Mirror. 1 = on</param>
/// <returns>Success</returns>
extern "C" __declspec(dllimport) BOOL requestImageConvert(char, char);

/// <summary>
/// Request Device Info
/// Only returns whether the transfer was successful.
/// he data must be received in a message.
/// MESSAGE_ID = 0x4041
/// </summary>
/// <returns>Success</returns>
extern "C" __declspec(dllimport) BOOL requestDeviceInfo(void);

/// <summary>
/// IsConnectd?
/// </summary>
/// <returns>true, false</returns>
extern "C" __declspec(dllimport) BOOL isConnected(void);

/// <summary>
/// Change FPS CMD
/// </summary>
/// <param name="char">0x00 ~ 0x1E(0 ~ 30)</param>
/// <returns>Success</returns>
extern "C" __declspec(dllimport) bool changeFPSCmd(char);

/// <summary>
/// Change Gain CMD
/// </summary>
/// <param name="char">0x00 ~ 0x04(0 ~ 4)</param>
/// <returns>Success</returns>
extern "C" __declspec(dllimport) bool changeGainCmd(char);

/// <summary>
/// Read Radiometry Offset
/// </summary>
/// <returns>Success</returns>
extern "C" __declspec(dllimport) bool getRadiometryOffset(void);

/// <summary>
/// Write Radiometry Offset
/// </summary>
/// <param name="char">0~100 (real Value = cahr - 50. ex : 0 == -50)</param>
/// <returns>Success</returns>
extern "C" __declspec(dllimport) bool setRadiometryOffset(char);

extern "C" __declspec(dllimport) bool setCalibrationMode(void);

extern "C" __declspec(dllimport) bool sendUserCommand(unsigned char[], int);

/// For Device Info. Message 0x4041
typedef struct PreTWDeviceInfo {
	LPSTR				FlashDate;				//  4 ~ 19
	LPSTR				DeviceType;				// 20 ~ 25
	LPSTR				DataType;				// 30 ~ 33
	LPSTR				SaveDate;				// 34 ~ 41
	LPSTR				InlineSerial;			// 42 ~ 59
	LPSTR				DeviceHWVer;			// 62 ~ 66
	LPSTR				DeviceSWVer;			// 67 ~ 71
} TWDeviceInfo;

/// For Data. Message 0x4011
typedef struct PreTWImageData {
	unsigned char	FPS;
	unsigned short	ImageWidth;
	unsigned short	ImageHeight;
	unsigned short	VCM;
	float			TempSensor;
	unsigned short	TempMCU;
	unsigned short	TempBoard;
	unsigned long	cnt = 0;
	// Image Data(Raw Data)
	unsigned short	ImageData[4800];
	// For Calculate Temperatur (in Celsius)
	// nSlope = 20.0f / (T_Data2 - T_Data1);
	// temp = ((nSlope * (ImageData[i] - T_Data1) + T_Data3) * 0.98f
	unsigned short  T_Data1;
	unsigned short  T_Data2;
	unsigned short  T_Data3;
} TWImageData;

typedef struct PreTWImageCalData {
	unsigned char	FPS;
	unsigned short	ImageWidth;
	unsigned short	ImageHeight;
	unsigned short	VCM;
	float			TempSensor;
	unsigned short	TempMCU;
	unsigned short	TempBoard;
	unsigned long	cnt = 0;
	unsigned short  MDCDC[80];
	unsigned short  A1[80];
	unsigned short  A2[80];
	unsigned short  A3[80];
	unsigned short  A4[80];
	unsigned short  A5[80];
	// Image Data(Raw Data)
	unsigned short	ImageData[4800];
} TWImageCalData;