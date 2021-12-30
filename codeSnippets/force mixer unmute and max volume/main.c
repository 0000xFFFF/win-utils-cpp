#include <stdio.h>
#include <windows.h>

#include <commctrl.h>
#include <initguid.h> // must include before mmdeviceapi.h, endpointvolue.h to have: CLSID_MMDeviceEnumerator, etc.
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audioclient.h>

HRESULT D(HRESULT ret, const char* funcname) {
	printf("%s -> %ld\n", funcname, ret);
	return ret;
}

int main() {
	int WORKING = 1;
	
	CoInitialize(NULL);
	
	IMMDeviceEnumerator* deviceEnumerator = NULL;
	if (FAILED(D(CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, &IID_IMMDeviceEnumerator, (LPVOID*)&deviceEnumerator), "deviceEnumerator CoCreateInstance"))) { return 1; }
	
	IMMDevice* defaultDevice = NULL;
	if (FAILED(D(deviceEnumerator->lpVtbl->GetDefaultAudioEndpoint(deviceEnumerator, eRender, eConsole, &defaultDevice), "deviceEnumerator defaultDevice GetDefaultAudioEndpoint"))) { return 1; }
	
	IAudioEndpointVolume* endpointVolume = NULL;
	BOOL isSet1 = FALSE;
	if (SUCCEEDED(D(defaultDevice->lpVtbl->Activate(defaultDevice, &IID_IAudioEndpointVolume, CLSCTX_ALL, NULL, (LPVOID*)&endpointVolume), "endpointVolume Activate"))) { isSet1 = TRUE; }
	printf("isSet1: %d\n", isSet1);
	
	#define REFTIMES_PER_SEC 10000000
	IAudioClient* audioClient = NULL;
	ISimpleAudioVolume* simpleAudioVolume = NULL;
	BOOL isSet2 = FALSE;
	if (FAILED(D(defaultDevice->lpVtbl->Activate(defaultDevice, &IID_IAudioClient, CLSCTX_ALL, NULL, (LPVOID*)&audioClient), "audioClient Activate"))) { printf("Activate failed\n"); return 1; }
	
	WAVEFORMATEX* pwfx = NULL;
	if (FAILED(D(audioClient->lpVtbl->GetMixFormat(audioClient, &pwfx), "audioClient GetMixFormat"))) { return 0; }
	if (FAILED(D(audioClient->lpVtbl->Initialize(audioClient, AUDCLNT_SHAREMODE_SHARED, 0, REFTIMES_PER_SEC, REFTIMES_PER_SEC, pwfx, NULL), "audioClient Initialize"))) { return 1; }
	if (SUCCEEDED(D(audioClient->lpVtbl->GetService(audioClient, &IID_ISimpleAudioVolume, (LPVOID*)&simpleAudioVolume), "audioClient GetService"))) { isSet2 = TRUE; }
	printf("isSet2: %d\n", isSet2);
	
	audioClient->lpVtbl->Release(audioClient);
	
	int exitnow = 0;
	while (WORKING) {
		if (isSet1) {
			D(endpointVolume->lpVtbl->SetMute(endpointVolume, FALSE, NULL), "endpointVolume SetMute");
			D(endpointVolume->lpVtbl->SetMasterVolumeLevelScalar(endpointVolume, 1.0f, NULL), "endpointVolume SetMasterVolumeLevelScalar");
		}
		
		if (isSet2) {
			D(simpleAudioVolume->lpVtbl->SetMute(simpleAudioVolume, FALSE, NULL), "simpleAudioVolume SetMute");
			D(simpleAudioVolume->lpVtbl->SetMasterVolume(simpleAudioVolume, 1.0f, NULL), "simpleAudioVolume SetMasterVolume");
		}
		
		exitnow++;
		if (exitnow > 100) { WORKING = 0; }
		Sleep(10);
	}
	
	if (isSet1) { D(endpointVolume->lpVtbl->Release(endpointVolume), "endpointVolume Release"); }
	if (isSet2) { D(simpleAudioVolume->lpVtbl->Release(simpleAudioVolume), "simpleAudioVolume Release"); }
	
	
	D(defaultDevice->lpVtbl->Release(defaultDevice), "defaultDevice Release");
	D(deviceEnumerator->lpVtbl->Release(deviceEnumerator), "deviceEnumerator Release");
	return 0;
}
