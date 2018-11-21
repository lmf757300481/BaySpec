#ifndef _Sense2020DLL_
#define _Sense2020DLL_


//difine the export type
#define DLL_PORT_TYPE __declspec(dllexport)
#define DLL_PORT_FUNCTION_TYPE __stdcall	//this can be used in visual basic program

//----------------------------------Export function declaration----------------------------------
/*function
********************************************************************************
<PRE>
Name:			DLL_Get_DLL_Versions

Operation:		Get versions for Sense 2020 DLL

Parameter:		pdwDLLVersion:  Pointer of DWORD Sense 2020 DLL revision

Return value:	TRUE:  Open device OK, 
				FALSE: Open device failed
-------------------------------------------------------------------------------- 
</PRE>
*******************************************************************************/ 
DLL_PORT_TYPE	BOOL  DLL_PORT_FUNCTION_TYPE DLL_Get_DLL_Versions(DWORD* pdwDLLVersion);


/*function
********************************************************************************
<PRE>
Name:			DLL_Open_Device

Operation:		Creat an instance and initialize the device 

Parameter:		None

Return value:	TRUE:  Open device OK, 
				FALSE: Open device failed

Note:			The memories for 20000 spectrum line and peaks info have been allocated in this function.
				DLL_Close_Device must be called to delete these memories  
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/ 
DLL_PORT_TYPE	BOOL  DLL_PORT_FUNCTION_TYPE DLL_Open_Device();


/*function
********************************************************************************
<PRE>
Name:			DLL_Close_Device

Operation:		Delete the instance

Parameter:		None

Return value:	None

Note:			The memories for 20000 spectrum line and peaks info are deleted in this fuction 
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/ 
DLL_PORT_TYPE	void DLL_PORT_FUNCTION_TYPE DLL_Close_Device();


/*function
********************************************************************************
<PRE>
Name:			DLL_Is_Device_OK

Operation:		Check Device status

Parameter:		None

Return value:	TRUE:  Device OK, 
				FALSE: Device failed
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/ 
DLL_PORT_TYPE	BOOL DLL_PORT_FUNCTION_TYPE DLL_Is_Device_OK();


/*function
********************************************************************************
<PRE>
Name:			DLL_Get_Device_Count

Operation:		Get connected USB20BS device count 

Parameter:		None

Return value:	Total connected USB20BS device count
				-1:  Operation failed
-------------------------------------------------------------------------------- 
</PRE>
*******************************************************************************/ 
DLL_PORT_TYPE	int  DLL_PORT_FUNCTION_TYPE DLL_Get_Device_Count();


/*function
********************************************************************************
<PRE>
Name:			DLL_Select_Device

Operation:		Select device with index to active it 

Parameter:		wDeviceIndex: Index of selected device

Return value:	TRUE:  Operation completed, 
				FALSE: Operation failed
-------------------------------------------------------------------------------- 
</PRE>
*******************************************************************************/ 
DLL_PORT_TYPE	BOOL  DLL_PORT_FUNCTION_TYPE DLL_Select_Device(WORD wDeviceIndex);


/*function
********************************************************************************
<PRE>
Name:			DLL_Get_Device_SN

Operation:		Get device serial number
 
Parameter:		lpszSN: Pointer of char buffer. Buffer size >= 8 byte

Return value:	TRUE:  Operation completed, 
				FALSE: Operation failed
-------------------------------------------------------------------------------- 
</PRE>
*******************************************************************************/ 
DLL_PORT_TYPE	BOOL  DLL_PORT_FUNCTION_TYPE DLL_Get_Device_SN(LPSTR lpszSN);


/*function
********************************************************************************
<PRE>
Name:			DLL_Get_HW_FW_REV

Operation:		Get hardware and firmware revision

Parameter:		pdwHW:  Pointer of DWORD hardware revision
				pdwFW:  Pointer of DWORD firmware revision

Return value:   TRUE:  Operation completed, 
				FALSE: Operation failed
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/								
DLL_PORT_TYPE BOOL DLL_PORT_FUNCTION_TYPE DLL_Get_HW_FW_REV(DWORD* pdwHW,
														    DWORD* pdwFW); 

/*function
********************************************************************************
<PRE>
Name:			DLL_Get_Pixel_Count

Operation:		Get pixel count
 
Parameter:		None

Return value:	Pixel Count
				-1:  Operation failed				
-------------------------------------------------------------------------------- 
</PRE>
*******************************************************************************/ 
DLL_PORT_TYPE	int  DLL_PORT_FUNCTION_TYPE DLL_Get_Pixel_Count();


/*function
********************************************************************************
<PRE>
Name:			DLL_Set_Integration_Time_Line_Rate

Operation:		Set integration time and line rate

Parameter:		dwIntegrationTime: 0 to 30000000 us
				wLineRate:		   1 to 5000 Hz

Return value:   TRUE:  Operation completed, 
				FALSE: Operation failed

Note:			dwIntegrationTime > 10E6/wLineRate
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/								
DLL_PORT_TYPE BOOL DLL_PORT_FUNCTION_TYPE DLL_Set_Integration_Time_Line_Rate(DWORD dwIntegrationTime, 
																			 WORD  wLineRate); 

/*function
********************************************************************************
<PRE>
Name:			DLL_Get_Integration_Time_Line_Rate

Operation:      Get integration time and line rate

Parameter:		pdwIntegrationTime: Pionter of DWORD integration time; unit: us
				pwLineRate:			Pionter of WORD line rate; unit: Hz

Return value:	TRUE:  Operation completed, 
				FALSE: Operation failed
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/ 
DLL_PORT_TYPE	BOOL DLL_PORT_FUNCTION_TYPE   DLL_Get_Integration_Time_Line_Rate(DWORD* pdwIntegrationTime,
																				 WORD*  pwLineRate);
/*function
********************************************************************************
<PRE>
name:			DLL_Set_Sensor_Mode

operation:      Set device sensor mode

parameter:		wSensorMode: 0 - High sensitivity; 1 - High dynamical range

return value:	TRUE:  Operation completed, 
				FALSE: Operation failed
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/ 
DLL_PORT_TYPE	BOOL DLL_PORT_FUNCTION_TYPE   DLL_Set_Sensor_Mode(WORD wSensorMode); 


/*function
********************************************************************************
<PRE>
name:			DLL_Get_Sensor_Mode_Status

operation:      Get device sensor mode status

parameter:		None

return value:	0:  High sensitivity,
				1:  High dynamical range, 
				-1: Operation failed
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/ 
DLL_PORT_TYPE	int DLL_PORT_FUNCTION_TYPE   DLL_Get_Sensor_Mode_Status(); 


/*function
********************************************************************************
<PRE>
name:			DLL_Set_Optical_Switch

operation:		Set 1x4 optical switch state

parameter:		bAutoChannelScan: TRUE - Auto scan channel 1 to 4 repeatedly during continue data acquisition
								  FALSE - Disable auto channel scan
				wChannelIndex:	  1 - Channel 1; 2 - Channel 2; 3 - Channel 3, 4 - Channel
 
return value:   TRUE:  Operation completed, 
				FALSE: Operation failed

Note:			When bAutoChannelScan = TRUE, ignore the setting of wChannelIndex  
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/								
DLL_PORT_TYPE BOOL DLL_PORT_FUNCTION_TYPE DLL_Set_Optical_Switch(BOOL bAutoChannelScan, WORD wChannelIndex); 


/*function
********************************************************************************
<PRE>
name:			DLL_Get_Optical_Switch_Status

operation:		Get 1x4 optical switch status

parameter:		pbAutoChannelScan: Pointer of BOOL auto channel scan status
				pwChannelIndex:	   Pointer of WORD current selected channel index

return value:   TRUE:  Operation completed, 
				FALSE: Operation failed
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/								
DLL_PORT_TYPE BOOL DLL_PORT_FUNCTION_TYPE DLL_Get_Optical_Switch_Status(BOOL* pbAutoChannelScan, WORD* pwChannelIndex); 

/*function
********************************************************************************
<PRE>
name:			DLL_Set_GPIO_State

operation:      Set device GPIO state

parameter:		byteGPIOState: each bit for one GPIO pin

return value:	TRUE:  Operation completed, 
				FALSE: Operation failed
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/ 
DLL_PORT_TYPE	BOOL DLL_PORT_FUNCTION_TYPE   DLL_Set_GPIO_State(BYTE byteGPIOState); 


/*function
********************************************************************************
<PRE>
name:			DLL_Get_GPIO_State

operation:      Get device GPIO state

parameter:		pbyteGPIOState: Pionter of byte GPIO state

return value:	TRUE:  Operation completed, 
				FALSE: Operation failed
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/ 
DLL_PORT_TYPE	BOOL DLL_PORT_FUNCTION_TYPE   DLL_Get_GPIO_State(BYTE* pbyteGPIOState); 


/*function
********************************************************************************
<PRE>
Name:			DLL_Get_Temperature

Operation:		Get sensor temperature. 

Parameter:		pdblCaseTemperature:	Pionter of double case temperature; unit: C
				pdblSensor Temperature: Pionter of double sensor temperature; unit: C
				
Return value:   TRUE:  Operation completed, 
				FALSE: Operation failed

Notte:			This function will call DLL_Get_Spectra twise with integration time = 0
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/								
DLL_PORT_TYPE BOOL DLL_PORT_FUNCTION_TYPE DLL_Get_Temperature(double* pdblCaseTemperature,
															  double* pdblSensorTemperature); 

/*function
********************************************************************************
<PRE>
Name:			DLL_Get_Spectra

Operation:		Acquire one spectrum line 

Parameter:		pdblData:			 Pointer of double power array buffer. Buffer size = pixel count
				pdblCaseTemperature: Pointer of double case temperature in current acquisition

Return value:	TRUE:  Operation completed, 
				FALSE: Operation failed
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/ 
DLL_PORT_TYPE	BOOL  DLL_PORT_FUNCTION_TYPE DLL_Get_Spectra(double* pdblData, double* pdblCasTemperature);

 /*function
********************************************************************************
<PRE>
Name:			DLL_Load_Calibration_Data

Operation:		Load calibration data for selected device

Parameter:		wDeviceIndext:	 Device Index
				szDeviceSN:		 Pointer of device serial number constant character buffer
				szCalibFilePath: Pointer of full device's calibration data file path constant character buffer

Return value:   0 - Operation completed;
				1 - Device not connected 
				2 - Device index >= Connected device count
				3 - Open file failed; 
				4 - Wrong revision of the calibration data;
				5 - Wrong calibration data format; 
				6 - Device serial number is not match with that in calibration file
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/								
DLL_PORT_TYPE int DLL_PORT_FUNCTION_TYPE DLL_Load_Calibration_Data(WORD wDeviceIndex, LPCSTR szDeviceSN, LPCSTR szCalibFilePath);     

/*function
********************************************************************************
<PRE>
Name:			DLL_Get_Wavelenth

Operation:		Get wavelengthes for each pixel at the given case temperature

Parameter:		dblCaseTemperature:	Case temperature in C
				pdblWavelength:		Pointer of double wavelength array buffer. Buffer size = pixel count

return value:   TRUE:  Operation completed, 
				FALSE: Operation failed
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/								
DLL_PORT_TYPE BOOL DLL_PORT_FUNCTION_TYPE DLL_Get_Wavelength(double  dblCaseTemperature,
														     double* pdblWavelength); 

/*function
********************************************************************************
<PRE>
Name:			DLL_Search_Peak

Operation:		Search all peaks in the spectrum

Parameter:		wPeakSearchMode:			Peak search mode. 0 - Use uniform noise threshold, 1 - Use profile noise threshold
				wPixelCount:				Pixel count
				pdblWL:						Pointer of double wavelength or pixel array buffer. Buffer size = pixel count
											For pixel double array, pdblWL[] = {0, 1, 2, ..., (pixel count - 1)} 
				pdblPwr:					Pointer to double power array buffer. Buffer size = pixel count									
				dblNoiseThreshold:			Peak search noise threshold. The powers of all peaks must > dblNoiseThreshold and the power increase 
											of adjacent pixels at beginning of rising edge of all peaks must > 0.1 * dblNoiseThreshold
				pdblNoiseThresholdProfile:	Pointer of double noise threshold profile array buffer. Buffer size = pixel count
				pdwPeakInfo:				Pointer of DWORD spectrum peak information array buffer. Buffer size = 512,
											DWORD[0] = 0xFFFFFFFF 
											DWORD[1] = Peak count, 
											DWORD[2] to DWORD[128]   = Peak pixels or wavelengthes (* 1000),
											DWORD[129] to DWORD[255] = Peak power (* 1000) 
Return value:   TRUE:  Operation completed, 
				FALSE: Operation failed

Note:			It is recommended that the power intensities should be substracted by background 			
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/								
DLL_PORT_TYPE BOOL DLL_PORT_FUNCTION_TYPE DLL_Search_Peaks(WORD		wPeakSearchMode,
														   WORD		wPixelCount,
														   double*	pdblWL,
														   double*	pdblPwr,
														   double	dblNoiseThreshold,
														   double*	pdblNoiseThresholdProfile,
														   DWORD*	pdwPeakInfo);       

/*function
********************************************************************************
<PRE>
Name:			DLL_Start_Constantly_Grab_Spectra

Operation:		Start constantly grab spectra

Parameter:		wProcessMode:				0 - Save raw data only
											1 - Find and save peak pixel and peak power only
											2 - Find and save peak wavelength and peak power only
											3 - Save raw data, find and save peak pixel and peak power
											4 - Save raw data, find and save peak wavelength and peak power
				wPeakSearchMode:			0 - Use uniform noise threshold 
											1 - Use profile noise threshold
				wExternalTimingMode:		0 - Synchronous external trigger mode
											1 - Asynchronous external trigger mode
											2 - Disable external trigger mode
				wExternalTriggerMode:		0 - External level triggering
											1 - External rising edge triggering (Only work with synchronous external trigger mode)	
				pdblBackgroundData			Pointer to double background array buffer, buffer size = pixel count in mode 1, 2, 3 and 4
				dblNoiseThreshold:			Peak search noise threshold. The power of all peaks must > dblNoiseThreshold and the power increase of adjacent pixels
											at beginning of rising edge of all peaks must > 0.1 * dblNoiseThreshold in mode 1, 2, 3 and 4
				pdblNoiseThresholdProfile:  Pointer of double peak search noise threshold profile array. Buffer size = pixel count
				
Return value:   0 - Operation OK
				1 - Device not connected
				2 - nProcessMode is larger than device count
				3 - Constant grab spectra in running
				4 - pdblNoiseThresholdProfile == NULL when wPeakSearchMode = 2 
				5 - Calibration data not loaded
				6 - Allocate memory failed 

Note:			External triggering run in asynchronous mode, trinngering event will be marked in stream out spectra lines.
				External triggering only work in constantly data grabbing mode 
				When pdblBackgroundData = NULL, all backgraound = 0
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/								
DLL_PORT_TYPE int DLL_PORT_FUNCTION_TYPE DLL_Start_Constantly_Grab_Spectra(WORD    wProcessMode,
																		   WORD    wPeakSearchMode,
																		   WORD    wExternalTimingMode,
																		   WORD    wExternalTriggerMode,																		   
																		   double* pdblBackgroundData,
																		   double  dblNoiseThreshold,
																		   double* pdblNoiseThresholdProfile); 


/*function
********************************************************************************
<PRE>
Name:			DLL_Stop_Constantly_Grab_Spectra

Operation:		Stop constantly grab spectra

Parameter:		None
		
Return value:   None
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/								
DLL_PORT_TYPE void DLL_PORT_FUNCTION_TYPE DLL_Stop_Constantly_Grab_Spectra();  


/*function
********************************************************************************
<PRE>
Name:			DLL_Get_Last_Spectrum_Index

Operation:		Get the last spectrum index saved in internal memory in constant acquisition  mode

Parameter:		None

Return value:   The last spectrum index
				-1 - Operation failed
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/								
DLL_PORT_TYPE int DLL_PORT_FUNCTION_TYPE DLL_Get_Last_Spectrum_Index(); 

/*function
********************************************************************************
<PRE>
Name:			DLL_Get_Constantly_Grab_Spectra

Operation:		Get one spectrum of given index in constant acquisition mode

Parameter:		dwSpectrumIndex:		Spectrum Index in saved internal memory
				dwSpectrumLineStamp:	Spectrum line stamp generated by hardware for the spectrum with the index = dwSpectrumIndex
                pdblData:				Pointer of double spectrum power array buffer. Buffer size = pixel count

Return value:   TRUE:  Operation completed, 
				FALSE: Operation failed

Note:			In external triggering enabled mode, only the stectra during triggering event have been saved into the internal memory
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/								
DLL_PORT_TYPE BOOL DLL_PORT_FUNCTION_TYPE DLL_Get_Constantly_Grab_Spectra(DWORD		dwSpectrumIndex,
																		  DWORD*	pdwSpectrumLineStamp,
																		  double*	pdblData); 

/*function
********************************************************************************
<PRE>
Name:			DLL_Get_Constantly_Grab_Peaks

Operation:		Get all peaks info of one spectrum of given index in constant acquisition mode

Parameter:		dwSpectrumIndex:	Spectrum index
                pdwPeakInfo:		Pointer to spectrum peak info DWORD array buffer. Buffer size = 512,
									DWORD[0] = Spectrum line stamp, 
									DWORD[1] = Peak count, 
									DWORD[2] to DWORD[128]   = Peak pixels or wavelengthes (* 1000),
									DWORD[129] to DWORD[255] = Peak power (* 1000),
								
Return value:   TRUE:  Operation completed, 
				FALSE: Operation failed
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/								
DLL_PORT_TYPE BOOL DLL_PORT_FUNCTION_TYPE DLL_Get_Constantly_Grab_Peaks(DWORD  dwSpectrumIndex,
																	    DWORD* pdwPeakInfo); 
                   

#endif //_USB20_IR_DEV_OP_ATTACH_DLL_