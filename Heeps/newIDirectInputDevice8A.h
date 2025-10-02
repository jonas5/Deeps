#ifndef __NEWIDIRECTINPUTDEVICE8A_H_INCLUDED__
#define __NEWIDIRECTINPUTDEVICE8A_H_INCLUDED__

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <dinput.h>

class newIDirectInputDevice8A : public IDirectInputDevice8A
{
public:
    newIDirectInputDevice8A(IDirectInputDevice8A*);
    ~newIDirectInputDevice8A();

    HRESULT __stdcall QueryInterface(REFIID riid, LPVOID* ppvObj);
    ULONG   __stdcall AddRef();
    ULONG   __stdcall Release();

    HRESULT __stdcall GetCapabilities(LPDIDEVCAPS);
    HRESULT __stdcall EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA, LPVOID, DWORD);
    HRESULT __stdcall GetProperty(REFGUID, LPDIPROPHEADER);
    HRESULT __stdcall SetProperty(REFGUID, LPCDIPROPHEADER);
    HRESULT __stdcall Acquire();
    HRESULT __stdcall Unacquire();
    HRESULT __stdcall GetDeviceState(DWORD, LPVOID);
    HRESULT __stdcall GetDeviceData(DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);
    HRESULT __stdcall SetDataFormat(LPCDIDATAFORMAT);
    HRESULT __stdcall SetEventNotification(HANDLE);
    HRESULT __stdcall SetCooperativeLevel(HWND, DWORD);
    HRESULT __stdcall GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA, DWORD, DWORD);
    HRESULT __stdcall GetDeviceInfo(LPDIDEVICEINSTANCEA);
    HRESULT __stdcall RunControlPanel(HWND, DWORD);
    HRESULT __stdcall Initialize(HINSTANCE, DWORD, REFGUID);
    HRESULT __stdcall CreateEffect(REFGUID, LPCDIEFFECT, LPDIRECTINPUTEFFECT*, LPUNKNOWN);
    HRESULT __stdcall EnumEffects(LPDIENUMEFFECTSCALLBACKA, LPVOID, DWORD);
    HRESULT __stdcall GetEffectInfo(LPDIEFFECTINFOA, REFGUID);
    HRESULT __stdcall GetForceFeedbackState(LPDWORD);
    HRESULT __stdcall SendForceFeedbackCommand(DWORD);
    HRESULT __stdcall EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK, LPVOID, DWORD);
    HRESULT __stdcall Escape(LPDIEFFESCAPE);
    HRESULT __stdcall Poll();
    HRESULT __stdcall SendDeviceData(DWORD, LPCDIDEVICEOBJECTDATA, LPDWORD, DWORD);
    HRESULT __stdcall EnumEffectsInFile(LPCSTR, LPDIENUMEFFECTSINFILECALLBACK, LPVOID, DWORD);
    HRESULT __stdcall WriteEffectToFile(LPCSTR, DWORD, LPDIFILEEFFECT, DWORD);
    HRESULT __stdcall BuildActionMap(LPDIACTIONFORMATA, LPCSTR, DWORD);
    HRESULT __stdcall SetActionMap(LPDIACTIONFORMATA, LPCSTR, DWORD);
    HRESULT __stdcall GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA);

private:
    IDirectInputDevice8A* m_pDevice;
};

#endif // __NEWIDIRECTINPUTDEVICE8A_H_INCLUDED__