#ifndef _WP_SAVE_IMAGE
#define _WP_SAVE_IMAGE

#define DLL_EXPORT extern "C" _declspec(dllexport)

DLL_EXPORT bool wpSaveJPEG(unsigned char *pData, char fileName[], int width, int height, int nChannels);
DLL_EXPORT bool WP_Save_JPEG(unsigned char *sData, unsigned char *dData, char fileName[], int width, int height, int nChannels, DWORD &dwSize);
#endif