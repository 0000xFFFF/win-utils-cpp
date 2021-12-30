// from: https://openclassrooms.com/forum/sujet/fonction-de-volume-windows-son#message-89033908

#include <stdio.h>
#include <initguid.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
 
 /*
DEFINE_GUID(CLSID_MMDeviceEnumerator, 0xBCDE0395, 0xE52F, 0x467C, 0x8E, 0x3D, 0xC4, 0x57, 0x92, 0x91, 0x69, 0x2E);
DEFINE_GUID(IID_IMMDeviceEnumerator,  0xA95664D2, 0x9614, 0x4F35, 0xA7, 0x46, 0xDE, 0x8D, 0xB6, 0x36, 0x17, 0xE6);
DEFINE_GUID(IID_IAudioEndpointVolume, 0x5CDF2C82, 0x841E, 0x4546, 0x97, 0x22, 0x0C, 0xF7, 0x40, 0x78, 0x22, 0x9A);
*/

IAudioEndpointVolume *InitVolume(void)
{
  IMMDevice *Dev;
  IMMDeviceEnumerator *DevEnum;
  IAudioEndpointVolume *EndpointVolume;
 
  CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_INPROC_SERVER, &IID_IMMDeviceEnumerator, (void **)&DevEnum);
  DevEnum->lpVtbl->GetDefaultAudioEndpoint(DevEnum, eRender, eConsole, &Dev);
  Dev->lpVtbl->Activate(Dev, &IID_IAudioEndpointVolume, CLSCTX_INPROC_SERVER, NULL, (void **)&EndpointVolume);
  DevEnum->lpVtbl->Release(DevEnum);
  Dev->lpVtbl->Release(Dev);
  return EndpointVolume;
}
 
float GetVolume(IAudioEndpointVolume *endpointVolume)
{
  float Volume = .0;
  endpointVolume->lpVtbl->GetMasterVolumeLevelScalar(endpointVolume, &Volume);
  return Volume;
}
 
void SetVolume(IAudioEndpointVolume *endpointVolume, float Volume)
{
  endpointVolume->lpVtbl->SetMasterVolumeLevelScalar(endpointVolume, Volume, 0);
}
 
void FreeVolume(IAudioEndpointVolume *endpointVolume)
{
  endpointVolume->lpVtbl->Release(endpointVolume);
}
 
int main(void)
{
  IAudioEndpointVolume *EndpointVolume;
 
  CoInitialize(0);
  EndpointVolume = InitVolume();
  printf("Volume : %g\n", GetVolume(EndpointVolume) * 100.);
  SetVolume(EndpointVolume, 1);
  printf("Volume : %g\n", GetVolume(EndpointVolume) * 100.);
  FreeVolume(EndpointVolume);
  CoUninitialize();
  return 0;
}