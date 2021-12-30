#include <stdio.h>
#include <windows.h>

// source: https://docs.microsoft.com/en-us/windows/win32/multimedia/recording-with-a-waveform-audio-device

// Uses the MCI_OPEN, MCI_RECORD, and MCI_SAVE commands to record and
// save a waveform-audio file. Returns 0L if successful; otherwise,
// it returns an MCI error code.
BOOL recordWAVEFile(DWORD dwMilliSeconds) {
	DWORD dwReturn;
	
	// Open a waveform-audio device with a new file for recording.
	MCI_OPEN_PARMS mciOpenParms;
	mciOpenParms.lpstrDeviceType = "waveaudio";
	mciOpenParms.lpstrElementName = "";
	dwReturn = mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID) &mciOpenParms);
	if (dwReturn) { return dwReturn; }
	
	// The device opened successfully; get the device ID.
	UINT wDeviceID = mciOpenParms.wDeviceID;
	
	// Begin recording and record for the specified number of 
	// milliseconds. Wait for recording to complete before continuing. 
	// Assume the default time format for the waveform-audio device 
	// (milliseconds).
	MCI_RECORD_PARMS mciRecordParms;
	mciRecordParms.dwTo = dwMilliSeconds;
	dwReturn = mciSendCommand(wDeviceID, MCI_RECORD,  MCI_TO | MCI_WAIT, (DWORD)(LPVOID) &mciRecordParms);
	if (dwReturn) { mciSendCommand(wDeviceID, MCI_CLOSE, 0, 0); return dwReturn; }
	
	// Play the recording and query user to save the file.
	MCI_PLAY_PARMS mciPlayParms;
	mciPlayParms.dwFrom = 0L;
	dwReturn = mciSendCommand(wDeviceID, MCI_PLAY, MCI_FROM | MCI_WAIT, (DWORD)(LPVOID) &mciPlayParms);
	if (dwReturn) { mciSendCommand(wDeviceID, MCI_CLOSE, 0, 0); return dwReturn; }
	
	if (MessageBox(NULL, "Do you want to save this recording?", "", MB_YESNO) == IDNO) {
		mciSendCommand(wDeviceID, MCI_CLOSE, 0, 0);
		return (0L);
	}
	
	// Save the recording to a file named TEMPFILE.WAV. Wait for
	// the operation to complete before continuing.
	MCI_SAVE_PARMS mciSaveParms;
	mciSaveParms.lpfilename = "recording.wav";
	dwReturn = mciSendCommand(wDeviceID, MCI_SAVE, MCI_SAVE_FILE | MCI_WAIT, (DWORD)(LPVOID) &mciSaveParms);
	if (dwReturn) { mciSendCommand(wDeviceID, MCI_CLOSE, 0, 0); return dwReturn; }
	
	return (0L);
}

int main() {
	
	recordWAVEFile(3000);
	
	return 0;
}
