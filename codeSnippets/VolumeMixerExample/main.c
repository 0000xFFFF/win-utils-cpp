#include <stdio.h>
#include <windows.h>
#include <commctrl.h>
#include <initguid.h> // must include before mmdeviceapi.h, endpointvolue.h to have: CLSID_MMDeviceEnumerator, etc.
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audioclient.h>

#include "gotoxy.h"

// Sources:
//   WASAPI                         --- https://docs.microsoft.com/en-us/windows/win32/coreaudio/wasapi?redirectedfrom=MSDN
//   IAudioEndpointVolume interface --- https://docs.microsoft.com/en-us/windows/win32/api/endpointvolume/nn-endpointvolume-iaudioendpointvolume
//   IAudioClient interface         --- https://docs.microsoft.com/en-us/windows/win32/api/audioclient/nn-audioclient-iaudioclient
//   ISimpleAudioVolume interface   --- https://docs.microsoft.com/en-us/windows/win32/api/audioclient/nn-audioclient-isimpleaudiovolume

/* // don't really have to define these... they are in <initguid.h>
DEFINE_GUID(CLSID_MMDeviceEnumerator, 0xBCDE0395, 0xE52F, 0x467C, 0x8E, 0x3D, 0xC4, 0x57, 0x92, 0x91, 0x69, 0x2E);
DEFINE_GUID(IID_IMMDeviceEnumerator,  0xA95664D2, 0x9614, 0x4F35, 0xA7, 0x46, 0xDE, 0x8D, 0xB6, 0x36, 0x17, 0xE6);
DEFINE_GUID(IID_IAudioEndpointVolume, 0x5CDF2C82, 0x841E, 0x4546, 0x97, 0x22, 0x0C, 0xF7, 0x40, 0x78, 0x22, 0x9A);

static const GUID XIID_MMDeviceEnumerator   = { 0xBCDE0395, 0xE52F, 0x467C, { 0x8E, 0x3D, 0xC4, 0x57, 0x92, 0x91, 0x69, 0x2E } };
static const GUID XIID_IMMDeviceEnumerator  = { 0xA95664D2, 0x9614, 0x4F35, { 0xA7, 0x46, 0xDE, 0x8D, 0xB6, 0x36, 0x17, 0xE6 } };
static const GUID XIID_IAudioEndpointVolume = { 0x5CDF2C82, 0x841E, 0x4546, { 0x97, 0x22, 0x0C, 0xF7, 0x40, 0x78, 0x22, 0x9A } };
*/

// CLSCTX_ALL CLSCTX_INPROC_SERVER

BOOL mixer_GetMasterVolumeLevelScalar(float* fOutVolume) {
	BOOL bSuccess = FALSE;
	IMMDeviceEnumerator* deviceEnumerator = NULL;
	if (SUCCEEDED(CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, &IID_IMMDeviceEnumerator, (LPVOID*)&deviceEnumerator))) {
		IMMDevice* defaultDevice = NULL;
		if (SUCCEEDED(deviceEnumerator->lpVtbl->GetDefaultAudioEndpoint(deviceEnumerator, eRender, eConsole, &defaultDevice))) {
			IAudioEndpointVolume* endpointVolume = NULL;
			if (SUCCEEDED(defaultDevice->lpVtbl->Activate(defaultDevice, &IID_IAudioEndpointVolume, CLSCTX_ALL, NULL, (LPVOID*)&endpointVolume))) {
				if (SUCCEEDED(endpointVolume->lpVtbl->GetMasterVolumeLevelScalar(endpointVolume, fOutVolume))) {
					bSuccess = TRUE;
				}
				endpointVolume->lpVtbl->Release(endpointVolume);
			}
			defaultDevice->lpVtbl->Release(defaultDevice);
		}
		deviceEnumerator->lpVtbl->Release(deviceEnumerator);
	}
	return bSuccess;
}

BOOL mixer_SetMasterVolumeLevelScalar(float fVolume) {
	BOOL bSuccess = FALSE;
	IMMDeviceEnumerator* deviceEnumerator = NULL;
	if (SUCCEEDED(CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, &IID_IMMDeviceEnumerator, (LPVOID*)&deviceEnumerator))) {
		IMMDevice* defaultDevice = NULL;
		if (SUCCEEDED(deviceEnumerator->lpVtbl->GetDefaultAudioEndpoint(deviceEnumerator, eRender, eConsole, &defaultDevice))) {
			IAudioEndpointVolume* endpointVolume = NULL;
			if (SUCCEEDED(defaultDevice->lpVtbl->Activate(defaultDevice, &IID_IAudioEndpointVolume, CLSCTX_ALL, NULL, (LPVOID*)&endpointVolume))) {
				if (SUCCEEDED(endpointVolume->lpVtbl->SetMasterVolumeLevelScalar(endpointVolume, fVolume, NULL))) {
					bSuccess = TRUE;
				}
				endpointVolume->lpVtbl->Release(endpointVolume);
			}
			defaultDevice->lpVtbl->Release(defaultDevice);
		}
		deviceEnumerator->lpVtbl->Release(deviceEnumerator);
	}
	return bSuccess;
}

BOOL mixer_GetMute(BOOL* bOutValue) {
	BOOL bSuccess = FALSE;
	IMMDeviceEnumerator* deviceEnumerator = NULL;
	if (SUCCEEDED(CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, &IID_IMMDeviceEnumerator, (LPVOID*)&deviceEnumerator))) {
		IMMDevice* defaultDevice = NULL;
		if (SUCCEEDED(deviceEnumerator->lpVtbl->GetDefaultAudioEndpoint(deviceEnumerator, eRender, eConsole, &defaultDevice))) {
			IAudioEndpointVolume* endpointVolume = NULL;
			if (SUCCEEDED(defaultDevice->lpVtbl->Activate(defaultDevice, &IID_IAudioEndpointVolume, CLSCTX_ALL, NULL, (LPVOID*)&endpointVolume))) {
				if (SUCCEEDED(endpointVolume->lpVtbl->GetMute(endpointVolume, bOutValue))) {
					bSuccess = TRUE;
				}
				endpointVolume->lpVtbl->Release(endpointVolume);
			}
			defaultDevice->lpVtbl->Release(defaultDevice);
		}
		deviceEnumerator->lpVtbl->Release(deviceEnumerator);
	}
	return bSuccess;
}

BOOL mixer_SetMute(BOOL bValue) {
	BOOL bSuccess = FALSE;
	IMMDeviceEnumerator* deviceEnumerator = NULL;
	if (SUCCEEDED(CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, &IID_IMMDeviceEnumerator, (LPVOID*)&deviceEnumerator))) {
		IMMDevice* defaultDevice = NULL;
		if (SUCCEEDED(deviceEnumerator->lpVtbl->GetDefaultAudioEndpoint(deviceEnumerator, eRender, eConsole, &defaultDevice))) {
			IAudioEndpointVolume* endpointVolume = NULL;
			if (SUCCEEDED(defaultDevice->lpVtbl->Activate(defaultDevice, &IID_IAudioEndpointVolume, CLSCTX_ALL, NULL, (LPVOID*)&endpointVolume))) {
				if (SUCCEEDED(endpointVolume->lpVtbl->SetMute(endpointVolume, bValue, NULL))) {
					bSuccess = TRUE;
				}
				endpointVolume->lpVtbl->Release(endpointVolume);
			}
			defaultDevice->lpVtbl->Release(defaultDevice);
		}
		deviceEnumerator->lpVtbl->Release(deviceEnumerator);
	}
	return bSuccess;
}

BOOL mixer_GetVolumeRange(float* min, float* max, float* incr) {
	BOOL bSuccess = FALSE;
	IMMDeviceEnumerator* deviceEnumerator = NULL;
	if (SUCCEEDED(CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, &IID_IMMDeviceEnumerator, (LPVOID*)&deviceEnumerator))) {
		IMMDevice* defaultDevice = NULL;
		if (SUCCEEDED(deviceEnumerator->lpVtbl->GetDefaultAudioEndpoint(deviceEnumerator, eRender, eConsole, &defaultDevice))) {
			IAudioEndpointVolume* endpointVolume = NULL;
			if (SUCCEEDED(defaultDevice->lpVtbl->Activate(defaultDevice, &IID_IAudioEndpointVolume, CLSCTX_ALL, NULL, (LPVOID*)&endpointVolume))) {
				if (SUCCEEDED(endpointVolume->lpVtbl->GetVolumeRange(endpointVolume, min, max, incr))) {
					bSuccess = TRUE;
				}
				endpointVolume->lpVtbl->Release(endpointVolume);
			}
			defaultDevice->lpVtbl->Release(defaultDevice);
		}
		deviceEnumerator->lpVtbl->Release(deviceEnumerator);
	}
	return bSuccess;
}

BOOL mixer_GetChannelCount(UINT* iCount) {
	BOOL bSuccess = FALSE;
	IMMDeviceEnumerator* deviceEnumerator = NULL;
	if (SUCCEEDED(CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, &IID_IMMDeviceEnumerator, (LPVOID*)&deviceEnumerator))) {
		IMMDevice* defaultDevice = NULL;
		if (SUCCEEDED(deviceEnumerator->lpVtbl->GetDefaultAudioEndpoint(deviceEnumerator, eRender, eConsole, &defaultDevice))) {
			IAudioEndpointVolume* endpointVolume = NULL;
			if (SUCCEEDED(defaultDevice->lpVtbl->Activate(defaultDevice, &IID_IAudioEndpointVolume, CLSCTX_ALL, NULL, (LPVOID*)&endpointVolume))) {
				if (SUCCEEDED(endpointVolume->lpVtbl->GetChannelCount(endpointVolume, iCount))) {
					bSuccess = TRUE;
				}
				endpointVolume->lpVtbl->Release(endpointVolume);
			}
			defaultDevice->lpVtbl->Release(defaultDevice);
		}
		deviceEnumerator->lpVtbl->Release(deviceEnumerator);
	}
	return bSuccess;
}

#define REFTIMES_PER_SEC 10000000

BOOL client_test() {
	BOOL bSuccess = FALSE;
	IMMDeviceEnumerator* deviceEnumerator = NULL;
	if (SUCCEEDED(CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, &IID_IMMDeviceEnumerator, (LPVOID*)&deviceEnumerator))) {
		IMMDevice* defaultDevice = NULL;
		if (SUCCEEDED(deviceEnumerator->lpVtbl->GetDefaultAudioEndpoint(deviceEnumerator, eRender, eConsole, &defaultDevice))) {
			IAudioClient* audioClient = NULL;
			if (SUCCEEDED(defaultDevice->lpVtbl->Activate(defaultDevice, &IID_IAudioClient, CLSCTX_ALL, NULL, (LPVOID*)&audioClient))) {
				WAVEFORMATEX* pwfx = NULL;
				if (SUCCEEDED(audioClient->lpVtbl->GetMixFormat(audioClient, &pwfx))) {
					if (SUCCEEDED(audioClient->lpVtbl->Initialize(audioClient, AUDCLNT_SHAREMODE_SHARED, 0, REFTIMES_PER_SEC, REFTIMES_PER_SEC, pwfx, NULL))) {
						ISimpleAudioVolume* simpleAudioVolume = NULL;
						if (SUCCEEDED(audioClient->lpVtbl->GetService(audioClient, &IID_ISimpleAudioVolume, (LPVOID*)&simpleAudioVolume))) {
							int r4 = simpleAudioVolume->lpVtbl->SetMute(simpleAudioVolume, FALSE, NULL);
							int r5 = simpleAudioVolume->lpVtbl->SetMasterVolume(simpleAudioVolume, 1.0f, NULL);
							bSuccess = SUCCEEDED(r4) && SUCCEEDED(r5);
							
							simpleAudioVolume->lpVtbl->Release(simpleAudioVolume);
						}
					}
				}
				audioClient->lpVtbl->Release(audioClient);
			}
			defaultDevice->lpVtbl->Release(defaultDevice);
		}
		deviceEnumerator->lpVtbl->Release(deviceEnumerator);
	}
	return bSuccess;
}

int main() {
	PlaySound(TEXT("file.wav"), NULL, SND_FILENAME | SND_ASYNC);
	int c = 0;
	system("cls");
	
	while (1) {
		
		printf("==================================================================\n");
		printf("COUNT                            : %d          \n", ++c);
		
		float vol;
		printf("mixer_GetMasterVolumeLevelScalar : %d          \n", mixer_GetMasterVolumeLevelScalar(&vol));
		printf(">>> float                        : %f          \n", vol);
		
		BOOL m;
		printf("mixer_GetMute                    : %d          \n", mixer_GetMute(&m));
		printf(">> BOOL                          : %d          \n", m);
		
		unsigned int count;
		printf("mixer_GetChannelCount            : %d          \n", mixer_GetChannelCount(&count));
		printf(">> unsigned int                  : %d          \n", count);
		
		float min, max, incr;
		printf("mixer_GetVolumeRange             : %d          \n", mixer_GetVolumeRange(&min, &max, &incr));
		printf(">> float min                     : %f          \n", min);
		printf(">> float max                     : %f          \n", max);
		printf(">> float incr                    : %f          \n", incr);
		
		// force stuff
		mixer_SetMasterVolumeLevelScalar(1);
		mixer_SetMute(FALSE);
		int g = client_test();
		printf("client                           : %d          \n", g);
		//waveOutSetVolume(NULL, 0xFFFFFFFF);
		Sleep(200);
		gotoxy(0,0);
	}
	
	return 0;
}
