/*==========================================================================;
 *
 *  Copyright (C) 1994-1998 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       d3d8.h
 *  Content:    Direct3D include file
 *
 ***************************************************************************/

#ifndef _D3D8_H_
#define _D3D8_H_

#ifndef DIRECT3D_VERSION
#define DIRECT3D_VERSION         0x0800
#endif  //DIRECT3D_VERSION

// include this file content only if compiling for DX8 interfaces
#if (DIRECT3D_VERSION >= 0x0800)

#include <stdlib.h>

#define COM_NO_WINDOWS_H
#include <objbase.h>

#include <windows.h>

#define D3DAPI WINAPI

/*
 * Interface IID's
 */
DEFINE_GUID(IID_IDirect3D8,              0x1dd9e8da, 0x1c77, 0x4d40, 0xb0, 0xcf, 0x98, 0xfe, 0xfd, 0xff, 0x95, 0x12);
DEFINE_GUID(IID_IDirect3DDevice8,        0x7360e9cd, 0xe14a, 0x4a43, 0x88, 0x45, 0xa9, 0x4f, 0x00, 0x84, 0x3d, 0x58);
DEFINE_GUID(IID_IDirect3DResource8,      0x1b36bb7b, 0x9b54, 0x4015, 0x98, 0xde, 0x4d, 0x42, 0x85, 0x4e, 0x4f, 0x9f);
DEFINE_GUID(IID_IDirect3DBaseTexture8,   0xb4211cfa, 0x51b9, 0x4a9f, 0xab, 0x38, 0x45, 0xdf, 0xae, 0x65, 0x8d, 0xa7);
DEFINE_GUID(IID_IDirect3DTexture8,       0xe4cdd575, 0x2866, 0x4f01, 0xb1, 0x2e, 0x7e, 0xe7, 0x34, 0x07, 0x9e, 0x75);
DEFINE_GUID(IID_IDirect3DCubeTexture8,   0x3ee5b968, 0x2aca, 0x4c34, 0x8a, 0xb8, 0x79, 0x52, 0x17, 0x6b, 0x88, 0x87);
DEFINE_GUID(IID_IDirect3DVolumeTexture8, 0x4b8aa25a, 0x5ae0, 0x475f, 0x8a, 0x2e, 0x8a, 0x78, 0x3a, 0xdd, 0x15, 0x53);
DEFINE_GUID(IID_IDirect3DVertexBuffer8,  0x8aeeeac7, 0x05f9, 0x44d4, 0xb5, 0x91, 0x66, 0xfe, 0x1b, 0x53, 0x1e, 0x98);
DEFINE_GUID(IID_IDirect3DIndexBuffer8,   0x0e689c9a, 0x053d, 0x44a0, 0x98, 0x22, 0xde, 0x9d, 0x32, 0x74, 0x4c, 0x73);
DEFINE_GUID(IID_IDirect3DSurface8,       0xb96eebca, 0xb326, 0x4ea5, 0x88, 0x2f, 0x2f, 0xf5, 0xba, 0xe0, 0x21, 0x56);
DEFINE_GUID(IID_IDirect3DVolume8,        0xbd76942a, 0x182e, 0x4826, 0x84, 0xee, 0xc1, 0x3c, 0x60, 0xd0, 0xbf, 0x8c);
DEFINE_GUID(IID_IDirect3DSwapChain8,     0x928c088b, 0x76b9, 0x42b4, 0x9c, 0x18, 0x7a, 0x1e, 0x0e, 0xd3, 0xd2, 0x3d);

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Forward declarations
 */

typedef interface IDirect3D8                  IDirect3D8;
typedef interface IDirect3DDevice8            IDirect3DDevice8;
typedef interface IDirect3DResource8          IDirect3DResource8;
typedef interface IDirect3DBaseTexture8       IDirect3DBaseTexture8;
typedef interface IDirect3DTexture8           IDirect3DTexture8;
typedef interface IDirect3DCubeTexture8       IDirect3DCubeTexture8;
typedef interface IDirect3DVolumeTexture8     IDirect3DVolumeTexture8;
typedef interface IDirect3DVertexBuffer8      IDirect3DVertexBuffer8;
typedef interface IDirect3DIndexBuffer8       IDirect3DIndexBuffer8;
typedef interface IDirect3DSurface8           IDirect3DSurface8;
typedef interface IDirect3DVolume8            IDirect3DVolume8;
typedef interface IDirect3DSwapChain8         IDirect3DSwapChain8;

/*
 * Constants
 */

/* D3DCREATE flags */
#define D3DCREATE_FPU_PRESERVE                  0x00000002L
#define D3DCREATE_MULTITHREADED                 0x00000004L

#define D3DCREATE_PUREDEVICE                    0x00000010L
#define D3DCREATE_SOFTWARE_VERTEXPROCESSING     0x00000020L
#define D3DCREATE_HARDWARE_VERTEXPROCESSING     0x00000040L
#define D3DCREATE_MIXED_VERTEXPROCESSING        0x00000080L

#define D3DCREATE_DISABLE_DRIVER_MANAGEMENT     0x00000100L
#define D3DCREATE_ADAPTERGROUP_DEVICE           0x00000200L

/* D3DDEVTYPE */
typedef enum _D3DDEVTYPE
{
    D3DDEVTYPE_HAL         = 1,
    D3DDEVTYPE_REF         = 2,
    D3DDEVTYPE_SW          = 3,

    D3DDEVTYPE_FORCE_DWORD  = 0x7fffffff
} D3DDEVTYPE;

/* D3DMULTISAMPLE_TYPE */
typedef enum _D3DMULTISAMPLE_TYPE
{
    D3DMULTISAMPLE_NONE            =  0,
    D3DMULTISAMPLE_2_SAMPLES       =  2,
    D3DMULTISAMPLE_3_SAMPLES       =  3,
    D3DMULTISAMPLE_4_SAMPLES       =  4,
    D3DMULTISAMPLE_5_SAMPLES       =  5,
    D3DMULTISAMPLE_6_SAMPLES       =  6,
    D3DMULTISAMPLE_7_SAMPLES       =  7,
    D3DMULTISAMPLE_8_SAMPLES       =  8,
    D3DMULTISAMPLE_9_SAMPLES       =  9,
    D3DMULTISAMPLE_10_SAMPLES      = 10,
    D3DMULTISAMPLE_11_SAMPLES      = 11,
    D3DMULTISAMPLE_12_SAMPLES      = 12,
    D3DMULTISAMPLE_13_SAMPLES      = 13,
    D3DMULTISAMPLE_14_SAMPLES      = 14,
    D3DMULTISAMPLE_15_SAMPLES      = 15,
    D3DMULTISAMPLE_16_SAMPLES      = 16,

    D3DMULTISAMPLE_FORCE_DWORD = 0x7fffffff
} D3DMULTISAMPLE_TYPE;

/* D3DFORMAT */
#define D3DFMT_UNKNOWN              0
#define D3DFMT_R8G8B8               20
#define D3DFMT_A8R8G8B8             21
#define D3DFMT_X8R8G8B8             22
#define D3DFMT_R5G6B5               23
#define D3DFMT_X1R5G5B5             24
#define D3DFMT_A1R5G5B5             25
#define D3DFMT_A4R4G4B4             26
#define D3DFMT_R3G3B2               27
#define D3DFMT_A8                   28
#define D3DFMT_A8R3G3B2             29
#define D3DFMT_X4R4G4B4             30
#define D3DFMT_A8P8                 40
#define D3DFMT_P8                   41
#define D3DFMT_L8                   50
#define D3DFMT_A8L8                 51
#define D3DFMT_A4L4                 52
#define D3DFMT_V8U8                 60
#define D3DFMT_L6V5U5               61
#define D3DFMT_X8L8V8U8             62
#define D3DFMT_Q8W8V8U8             63
#define D3DFMT_V16U16               64
#define D3DFMT_W11V11U10            65
#define D3DFMT_A2W10V10U10          67
#define D3DFMT_UYVY                 MAKEFOURCC('U', 'Y', 'V', 'Y')
#define D3DFMT_YUY2                 MAKEFOURCC('Y', 'U', 'Y', '2')
#define D3DFMT_DXT1                 MAKEFOURCC('D', 'X', 'T', '1')
#define D3DFMT_DXT2                 MAKEFOURCC('D', 'X', 'T', '2')
#define D3DFMT_DXT3                 MAKEFOURCC('D', 'X', 'T', '3')
#define D3DFMT_DXT4                 MAKEFOURCC('D', 'X', 'T', '4')
#define D3DFMT_DXT5                 MAKEFOURCC('D', 'X', 'T', '5')
#define D3DFMT_D16_LOCKABLE         70
#define D3DFMT_D32                  71
#define D3DFMT_D15S1                73
#define D3DFMT_D24S8                75
#define D3DFMT_D16                  80
#define D3DFMT_D24X8                77
#define D3DFMT_D24X4S4              79
#define D3DFMT_VERTEXDATA           100
#define D3DFMT_INDEX16              101
#define D3DFMT_INDEX32              102

typedef enum _D3DFORMAT
{
    D3DFMT_FORCE_DWORD = 0x7fffffff
} D3DFORMAT;


/* D3DDISPLAYMODE */
typedef struct _D3DDISPLAYMODE
{
    UINT            Width;
    UINT            Height;
    UINT            RefreshRate;
    D3DFORMAT       Format;
} D3DDISPLAYMODE;

/* D3DPRESENT_PARAMETERS */
typedef struct _D3DPRESENT_PARAMETERS_
{
    UINT                BackBufferWidth;
    UINT                BackBufferHeight;
    D3DFORMAT           BackBufferFormat;
    UINT                BackBufferCount;

    D3DMULTISAMPLE_TYPE MultiSampleType;

    D3DSWAPEFFECT       SwapEffect;
    HWND                hDeviceWindow;
    BOOL                Windowed;
    BOOL                EnableAutoDepthStencil;
    D3DFORMAT           AutoDepthStencilFormat;
    DWORD               Flags;

    /* FullScreen_RefreshRateInHz must be zero for windowed mode */
    UINT                FullScreen_RefreshRateInHz;
    /* FullScreen_PresentationInterval can be any of the D3DPRESENT_INTERVAL flags */
    UINT                FullScreen_PresentationInterval;

} D3DPRESENT_PARAMETERS;

/* D3DPRESENTFLAG */
#define D3DPRESENTFLAG_LOCKABLE_BACKBUFFER      0x00000001L
#define D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL     0x00000002L
#define D3DPRESENTFLAG_DEVICECLIP               0x00000004L
#define D3DPRESENTFLAG_VIDEO                    0x00000010L

/* D3DSWAPEFFECT */
typedef enum _D3DSWAPEFFECT
{
    D3DSWAPEFFECT_DISCARD           = 1,
    D3DSWAPEFFECT_FLIP              = 2,
    D3DSWAPEFFECT_COPY              = 3,
    D3DSWAPEFFECT_COPY_VSYNC        = 4,

    D3DSWAPEFFECT_FORCE_DWORD  = 0x7fffffff
} D3DSWAPEFFECT;

/* D3DPOOL */
typedef enum _D3DPOOL {
    D3DPOOL_DEFAULT                 = 0,
    D3DPOOL_MANAGED                 = 1,
    D3DPOOL_SYSTEMMEM               = 2,
    D3DPOOL_SCRATCH                 = 3,

    D3DPOOL_FORCE_DWORD = 0x7fffffff
} D3DPOOL;

/* D3DPRESENT_INTERVAL */
#define D3DPRESENT_INTERVAL_DEFAULT         0x00000000L
#define D3DPRESENT_INTERVAL_ONE             0x00000001L
#define D3DPRESENT_INTERVAL_TWO             0x00000002L
#define D3DPRESENT_INTERVAL_THREE           0x00000003L
#define D3DPRESENT_INTERVAL_FOUR            0x00000004L
#define D3DPRESENT_INTERVAL_IMMEDIATE       0x80000000L

/* D3DCAPS8 */
#define D3DCAPS_READ_SCANLINE               0x00020000L

typedef struct _D3DCAPS8
{
    /* Device Info */
    D3DDEVTYPE  DeviceType;
    UINT    AdapterOrdinal;

    /* Caps from DX7 Draw */
    DWORD   Caps;
    DWORD   Caps2;
    DWORD   Caps3;
    DWORD   PresentationIntervals;

    /* Cursor Caps */
    DWORD   CursorCaps;

    /* Driver Caps */
    DWORD   DevCaps;

    DWORD   PrimitiveMiscCaps;
    DWORD   RasterCaps;
    DWORD   ZCmpCaps;
    DWORD   SrcBlendCaps;
    DWORD   DestBlendCaps;
    DWORD   AlphaCmpCaps;
    DWORD   ShadeCaps;
    DWORD   TextureCaps;
    DWORD   TextureFilterCaps;  // D3DPTFILTERCAPS for IDirect3DTexture8's
    DWORD   CubeTextureFilterCaps;// D3DPTFILTERCAPS for IDirect3DCubeTexture8's
    DWORD   VolumeTextureFilterCaps;// D3DPTFILTERCAPS for IDirect3DVolumeTexture8's
    DWORD   TextureAddressCaps; // D3DPTADDRESSCAPS for IDirect3DTexture8's
    DWORD   VolumeTextureAddressCaps; // D3DPTADDRESSCAPS for IDirect3DVolumeTexture8's

    DWORD   LineCaps;

    DWORD   MaxTextureWidth, MaxTextureHeight;
    DWORD   MaxVolumeExtent;

    DWORD   MaxTextureRepeat;
    DWORD   MaxTextureAspectRatio;
    DWORD   MaxAnisotropy;
    float   MaxVertexW;

    float   GuardBandLeft;
    float   GuardBandTop;
    float   GuardBandRight;
    float   GuardBandBottom;

    float   ExtentsAdjust;
    DWORD   StencilCaps;

    DWORD   FVFCaps;
    DWORD   TextureOpCaps;
    DWORD   MaxTextureBlendStages;
    DWORD   MaxSimultaneousTextures;

    DWORD   VertexProcessingCaps;
    DWORD   MaxActiveLights;
    DWORD   MaxUserClipPlanes;
    DWORD   MaxVertexBlendMatrices;
    DWORD   MaxVertexBlendMatrixIndex;

    float   MaxPointSize;

    DWORD   MaxPrimitiveCount;
    DWORD   MaxVertexIndex;
    DWORD   MaxStreams;
    DWORD   MaxStreamStride;

    DWORD   VertexShaderVersion;
    DWORD   MaxVertexShaderConst;

    DWORD   PixelShaderVersion;
    float   MaxPixelShaderValue;

} D3DCAPS8;

/* IDirect3D8 */
#undef INTERFACE
#define INTERFACE IDirect3D8

DECLARE_INTERFACE_(IDirect3D8, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    // IDirect3D8
    STDMETHOD(RegisterSoftwareDevice)(THIS_ void* pInitializeFunction) PURE;
    STDMETHOD_(UINT, GetAdapterCount)(THIS) PURE;
    STDMETHOD(GetAdapterIdentifier)(THIS_ UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER8* pIdentifier) PURE;
    STDMETHOD_(UINT, GetAdapterModeCount)(THIS_ UINT Adapter) PURE;
    STDMETHOD(EnumAdapterModes)(THIS_ UINT Adapter,UINT Mode,D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(GetAdapterDisplayMode)(THIS_ UINT Adapter,D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(CheckDeviceType)(THIS_ UINT Adapter,D3DDEVTYPE CheckType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed) PURE;
    STDMETHOD(CheckDeviceFormat)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat) PURE;
    STDMETHOD(CheckDeviceMultiSampleType)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType) PURE;
    STDMETHOD(CheckDepthStencilMatch)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat) PURE;
    STDMETHOD(GetDeviceCaps)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS8* pCaps) PURE;
    STDMETHOD_(HMONITOR, GetAdapterMonitor)(THIS_ UINT Adapter) PURE;
    STDMETHOD(CreateDevice)(THIS_ UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice8** ppReturnedDeviceInterface) PURE;
};

/* D3DADAPTER_IDENTIFIER8 */
#define MAX_DEVICE_IDENTIFIER_STRING 512
typedef struct _D3DADAPTER_IDENTIFIER8
{
    char            Driver[MAX_DEVICE_IDENTIFIER_STRING];
    char            Description[MAX_DEVICE_IDENTIFIER_STRING];

    LARGE_INTEGER   DriverVersion;

    DWORD           VendorId;
    DWORD           DeviceId;
    DWORD           SubSysId;
    DWORD           Revision;

    GUID            DeviceIdentifier;

    DWORD           WHQLLevel;

} D3DADAPTER_IDENTIFIER8;

/* D3DERR */
#define D3D_OK                              S_OK
#define D3DERR_WRONGTEXTUREFORMAT               MAKE_D3DHRESULT(2072)
#define D3DERR_UNSUPPORTEDCOLOROPERATION        MAKE_D3DHRESULT(2073)
#define D3DERR_UNSUPPORTEDCOLORARG              MAKE_D3DHRESULT(2074)
#define D3DERR_UNSUPPORTEDALPHAOPERATION        MAKE_D3DHRESULT(2075)
#define D3DERR_UNSUPPORTEDALPHAARG              MAKE_D3DHRESULT(2076)
#define D3DERR_TOOMANYOPERATIONS                MAKE_D3DHRESULT(2077)
#define D3DERR_CONFLICTINGTEXTUREFILTER         MAKE_D3DHRESULT(2078)
#define D3DERR_UNSUPPORTEDFACTORVALUE           MAKE_D3DHRESULT(2079)
#define D3DERR_CONFLICTINGRENDERSTATE           MAKE_D3DHRESULT(2081)
#define D3DERR_UNSUPPORTEDTEXTUREFILTER         MAKE_D3DHRESULT(2082)
#define D3DERR_CONFLICTINGTEXTUREPALETTE        MAKE_D3DHRESULT(2086)
#define D3DERR_DRIVERINTERNALERROR              MAKE_D3DHRESULT(2087)
#define D3DERR_NOTFOUND                         MAKE_D3DHRESULT(2150)
#define D3DERR_MOREDATA                         MAKE_D3DHRESULT(2151)
#define D3DERR_DEVICELOST                       MAKE_D3DHRESULT(2152)
#define D3DERR_DEVICENOTRESET                   MAKE_D3DHRESULT(2153)
#define D3DERR_NOTAVAILABLE                     MAKE_D3DHRESULT(2154)
#define D3DERR_OUTOFVIDEOMEMORY                 MAKE_D3DHRESULT(380)
#define D3DERR_INVALIDDEVICE                    MAKE_D3DHRESULT(2155)
#define D3DERR_INVALIDCALL                      MAKE_D3DHRESULT(2156)
#define D3DERR_DRIVERINVALIDCALL                MAKE_D3DHRESULT(2157)

/* D3DRESOURCETYPE */
typedef enum _D3DRESOURCETYPE {
    D3DRTYPE_SURFACE                =  1,
    D3DRTYPE_VOLUME                 =  2,
    D3DRTYPE_TEXTURE                =  3,
    D3DRTYPE_VOLUMETEXTURE          =  4,
    D3DRTYPE_CUBETEXTURE            =  5,
    D3DRTYPE_VERTEXBUFFER           =  6,
    D3DRTYPE_INDEXBUFFER            =  7,

    D3DRTYPE_FORCE_DWORD = 0x7fffffff
} D3DRESOURCETYPE;

/* D3DUSAGE */
#define D3DUSAGE_RENDERTARGET       0x00000001L
#define D3DUSAGE_DEPTHSTENCIL       0x00000002L
#define D3DUSAGE_WRITEONLY          0x00000008L
#define D3DUSAGE_SOFTWAREPROCESSING 0x00000010L
#define D3DUSAGE_DONOTCLIP          0x00000020L
#define D3DUSAGE_POINTS             0x00000040L
#define D3DUSAGE_RTPATCHES          0x00000080L
#define D3DUSAGE_NPATCHES           0x00000100L
#define D3DUSAGE_DYNAMIC            0x00000200L

/* D3DCUBEMAP_FACES */
typedef enum _D3DCUBEMAP_FACES
{
    D3DCUBEMAP_FACE_POSITIVE_X     = 0,
    D3DCUBEMAP_FACE_NEGATIVE_X     = 1,
    D3DCUBEMAP_FACE_POSITIVE_Y     = 2,
    D3DCUBEMAP_FACE_NEGATIVE_Y     = 3,
    D3DCUBEMAP_FACE_POSITIVE_Z     = 4,
    D3DCUBEMAP_FACE_NEGATIVE_Z     = 5,

    D3DCUBEMAP_FACE_FORCE_DWORD = 0x7fffffff
} D3DCUBEMAP_FACES;

/* D3DVERTEXBUFFER_DESC */
typedef struct _D3DVERTEXBUFFER_DESC
{
    D3DFORMAT       Format;
    D3DRESOURCETYPE Type;
    DWORD           Usage;
    D3DPOOL         Pool;
    UINT            Size;
    DWORD           FVF;
} D3DVERTEXBUFFER_DESC;

/* D3DINDEXBUFFER_DESC */
typedef struct _D3DINDEXBUFFER_DESC
{
    D3DFORMAT       Format;
    D3DRESOURCETYPE Type;
    DWORD           Usage;
    D3DPOOL         Pool;
    UINT            Size;
} D3DINDEXBUFFER_DESC;

/* D3DSURFACE_DESC */
typedef struct _D3DSURFACE_DESC
{
    D3DFORMAT           Format;
    D3DRESOURCETYPE     Type;
    DWORD               Usage;
    D3DPOOL             Pool;

    D3DMULTISAMPLE_TYPE MultiSampleType;
    UINT                Width;
    UINT                Height;
} D3DSURFACE_DESC;

/* D3DVOLUME_DESC */
typedef struct _D3DVOLUME_DESC
{
    D3DFORMAT           Format;
    D3DRESOURCETYPE     Type;
    DWORD               Usage;
    D3DPOOL             Pool;
    UINT                Width;
    UINT                Height;
    UINT                Depth;
} D3DVOLUME_DESC;

/* D3DLOCKED_RECT */
typedef struct _D3DLOCKED_RECT
{
    INT                 Pitch;
    void*               pBits;
} D3DLOCKED_RECT;

/* D3DBOX */
typedef struct _D3DBOX
{
    UINT                Left;
    UINT                Top;
    UINT                Right;
    UINT                Bottom;
    UINT                Front;
    UINT                Back;
} D3DBOX;

/* D3DLOCKED_BOX */
typedef struct _D3DLOCKED_BOX
{
    INT                 RowPitch;
    INT                 SlicePitch;
    void*               pBits;
} D3DLOCKED_BOX;

/* D3DRANGE */
typedef struct _D3DRANGE
{
    UINT                Offset;
    UINT                Size;
} D3DRANGE;

/* D3DRECTPATCH_INFO */
typedef struct _D3DRECTPATCH_INFO
{
    UINT                StartVertexOffsetWidth;
    UINT                StartVertexOffsetHeight;
    UINT                Width;
    UINT                Height;
    UINT                Stride;
    D3DBASISTYPE        Basis;
    D3DDEGREETYPE       Degree;
} D3DRECTPATCH_INFO;

/* D3DTRIPATCH_INFO */
typedef struct _D3DTRIPATCH_INFO
{
    UINT                StartVertexOffset;
    UINT                NumVertices;
    UINT                Stride;
    D3DBASISTYPE        Basis;
    D3DDEGREETYPE       Degree;
} D3DTRIPATCH_INFO;

/* IDirect3DDevice8 */
#undef INTERFACE
#define INTERFACE IDirect3DDevice8

DECLARE_INTERFACE_(IDirect3DDevice8, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    // IDirect3DDevice8
    STDMETHOD(TestCooperativeLevel)(THIS) PURE;
    STDMETHOD_(UINT, GetAvailableTextureMem)(THIS) PURE;
    STDMETHOD(ResourceManagerDiscardBytes)(THIS_ DWORD Bytes) PURE;
    STDMETHOD(GetDirect3D)(THIS_ IDirect3D8** ppD3D8) PURE;
    STDMETHOD(GetDeviceCaps)(THIS_ D3DCAPS8* pCaps) PURE;
    STDMETHOD(GetDisplayMode)(THIS_ D3DDISPLAYMODE* pMode) PURE;
    STDMETHOD(GetCreationParameters)(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters) PURE;
    STDMETHOD(SetCursorProperties)(THIS_ UINT XHotSpot,UINT YHotSpot,IDirect3DSurface8* pCursorBitmap) PURE;
    STDMETHOD_(void, SetCursorPosition)(THIS_ int X,int Y,DWORD Flags) PURE;
    STDMETHOD_(BOOL, ShowCursor)(THIS_ BOOL bShow) PURE;
    STDMETHOD(CreateAdditionalSwapChain)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain8** pSwapChain) PURE;
    STDMETHOD(Reset)(THIS_ D3DPRESENT_PARAMETERS* pPresentationParameters) PURE;
    STDMETHOD(Present)(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion) PURE;
    STDMETHOD(GetBackBuffer)(THIS_ UINT BackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface8** ppBackBuffer) PURE;
    STDMETHOD(GetRasterStatus)(THIS_ D3DRASTER_STATUS* pRasterStatus) PURE;
    STDMETHOD_(void, SetGammaRamp)(THIS_ DWORD Flags,CONST D3DGAMMARAMP* pRamp) PURE;
    STDMETHOD_(void, GetGammaRamp)(THIS_ D3DGAMMARAMP* pRamp) PURE;
    STDMETHOD(CreateTexture)(THIS_ UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture8** ppTexture) PURE;
    STDMETHOD(CreateVolumeTexture)(THIS_ UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture8** ppVolumeTexture) PURE;
    STDMETHOD(CreateCubeTexture)(THIS_ UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture8** ppCubeTexture) PURE;
    STDMETHOD(CreateVertexBuffer)(THIS_ UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer8** ppVertexBuffer) PURE;
    STDMETHOD(CreateIndexBuffer)(THIS_ UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer8** ppIndexBuffer) PURE;
    STDMETHOD(CreateRenderTarget)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,BOOL Lockable,IDirect3DSurface8** ppSurface) PURE;
    STDMETHOD(CreateDepthStencilSurface)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,IDirect3DSurface8** ppSurface) PURE;
    STDMETHOD(CreateImageSurface)(THIS_ UINT Width,UINT Height,D3DFORMAT Format,IDirect3DSurface8** ppSurface) PURE;
    STDMETHOD(CopyRects)(THIS_ IDirect3DSurface8* pSourceSurface,CONST RECT* pSourceRectsArray,UINT cRects,IDirect3DSurface8* pDestinationSurface,CONST POINT* pDestPointsArray) PURE;
    STDMETHOD(UpdateTexture)(THIS_ IDirect3DBaseTexture8* pSourceTexture,IDirect3DBaseTexture8* pDestinationTexture) PURE;
    STDMETHOD(GetFrontBuffer)(THIS_ IDirect3DSurface8* pDestSurface) PURE;
    STDMETHOD(SetRenderTarget)(THIS_ IDirect3DSurface8* pRenderTarget,IDirect3DSurface8* pNewZStencil) PURE;
    STDMETHOD(GetRenderTarget)(THIS_ IDirect3DSurface8** ppRenderTarget) PURE;
    STDMETHOD(GetDepthStencilSurface)(THIS_ IDirect3DSurface8** ppZStencilSurface) PURE;
    STDMETHOD(BeginScene)(THIS) PURE;
    STDMETHOD(EndScene)(THIS) PURE;
    STDMETHOD(Clear)(THIS_ DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil) PURE;
    STDMETHOD(SetTransform)(THIS_ D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix) PURE;
    STDMETHOD(GetTransform)(THIS_ D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix) PURE;
    STDMETHOD(MultiplyTransform)(THIS_ D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix) PURE;
    STDMETHOD(SetViewport)(THIS_ CONST D3DVIEWPORT8* pViewport) PURE;
    STDMETHOD(GetViewport)(THIS_ D3DVIEWPORT8* pViewport) PURE;
    STDMETHOD(SetMaterial)(THIS_ CONST D3DMATERIAL8* pMaterial) PURE;
    STDMETHOD(GetMaterial)(THIS_ D3DMATERIAL8* pMaterial) PURE;
    STDMETHOD(SetLight)(THIS_ DWORD Index,CONST D3DLIGHT8* pLight) PURE;
    STDMETHOD(GetLight)(THIS_ DWORD Index,D3DLIGHT8* pLight) PURE;
    STDMETHOD(LightEnable)(THIS_ DWORD Index,BOOL Enable) PURE;
    STDMETHOD(GetLightEnable)(THIS_ DWORD Index,BOOL* pEnable) PURE;
    STDMETHOD(SetClipPlane)(THIS_ DWORD Index,CONST float* pPlane) PURE;
    STDMETHOD(GetClipPlane)(THIS_ DWORD Index,float* pPlane) PURE;
    STDMETHOD(SetRenderState)(THIS_ D3DRENDERSTATETYPE State,DWORD Value) PURE;
    STDMETHOD(GetRenderState)(THIS_ D3DRENDERSTATETYPE State,DWORD* pValue) PURE;
    STDMETHOD(BeginStateBlock)(THIS) PURE;
    STDMETHOD(EndStateBlock)(THIS_ DWORD* pToken) PURE;
    STDMETHOD(ApplyStateBlock)(THIS_ DWORD Token) PURE;
    STDMETHOD(CaptureStateBlock)(THIS_ DWORD Token) PURE;
    STDMETHOD(DeleteStateBlock)(THIS_ DWORD Token) PURE;
    STDMETHOD(CreateStateBlock)(THIS_ D3DSTATEBLOCKTYPE Type,DWORD* pToken) PURE;
    STDMETHOD(SetClipStatus)(THIS_ CONST D3DCLIPSTATUS8* pClipStatus) PURE;
    STDMETHOD(GetClipStatus)(THIS_ D3DCLIPSTATUS8* pClipStatus) PURE;
    STDMETHOD(GetTexture)(THIS_ DWORD Stage,IDirect3DBaseTexture8** ppTexture) PURE;
    STDMETHOD(SetTexture)(THIS_ DWORD Stage,IDirect3DBaseTexture8* pTexture) PURE;
    STDMETHOD(GetTextureStageState)(THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue) PURE;
    STDMETHOD(SetTextureStageState)(THIS_ DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value) PURE;
    STDMETHOD(ValidateDevice)(THIS_ DWORD* pNumPasses) PURE;
    STDMETHOD(GetInfo)(THIS_ DWORD DevInfoID,void* pDevInfoStruct,DWORD DevInfoStructSize) PURE;
    STDMETHOD(SetPaletteEntries)(THIS_ UINT PaletteNumber,CONST PALETTEENTRY* pEntries) PURE;
    STDMETHOD(GetPaletteEntries)(THIS_ UINT PaletteNumber,PALETTEENTRY* pEntries) PURE;
    STDMETHOD(SetCurrentTexturePalette)(THIS_ UINT PaletteNumber) PURE;
    STDMETHOD(GetCurrentTexturePalette)(THIS_ UINT *PaletteNumber) PURE;
    STDMETHOD(DrawPrimitive)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount) PURE;
    STDMETHOD(DrawIndexedPrimitive)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT minIndex,UINT NumVertices,UINT startIndex,UINT primCount) PURE;
    STDMETHOD(DrawPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) PURE;
    STDMETHOD(DrawIndexedPrimitiveUP)(THIS_ D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertexIndices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride) PURE;
    STDMETHOD(ProcessVertices)(THIS_ UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer8* pDestBuffer,DWORD Flags) PURE;
    STDMETHOD(CreateVertexShader)(THIS_ CONST DWORD* pDeclaration,CONST DWORD* pFunction,DWORD* pHandle,DWORD Usage) PURE;
    STDMETHOD(SetVertexShader)(THIS_ DWORD Handle) PURE;
    STDMETHOD(GetVertexShader)(THIS_ DWORD* pHandle) PURE;
    STDMETHOD(DeleteVertexShader)(THIS_ DWORD Handle) PURE;
    STDMETHOD(GetVertexShaderDeclaration)(THIS_ DWORD Handle,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(GetVertexShaderFunction)(THIS_ DWORD Handle,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(SetStreamSource)(THIS_ UINT StreamNumber,IDirect3DVertexBuffer8* pStreamData,UINT Stride) PURE;
    STDMETHOD(GetStreamSource)(THIS_ UINT StreamNumber,IDirect3DVertexBuffer8** ppStreamData,UINT* pStride) PURE;
    STDMETHOD(SetIndices)(THIS_ IDirect3DIndexBuffer8* pIndexData,UINT BaseVertexIndex) PURE;
    STDMETHOD(GetIndices)(THIS_ IDirect3DIndexBuffer8** ppIndexData,UINT* pBaseVertexIndex) PURE;
    STDMETHOD(CreatePixelShader)(THIS_ CONST DWORD* pFunction,DWORD* pHandle) PURE;
    STDMETHOD(SetPixelShader)(THIS_ DWORD Handle) PURE;
    STDMETHOD(GetPixelShader)(THIS_ DWORD* pHandle) PURE;
    STDMETHOD(DeletePixelShader)(THIS_ DWORD Handle) PURE;
    STDMETHOD(GetPixelShaderFunction)(THIS_ DWORD Handle,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(DrawRectPatch)(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo) PURE;
    STDMETHOD(DrawTriPatch)(THIS_ UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo) PURE;
    STDMETHOD(DeletePatch)(THIS_ UINT Handle) PURE;
};

/* D3DDEVICE_CREATION_PARAMETERS */
typedef struct _D3DDEVICE_CREATION_PARAMETERS
{
    UINT            AdapterOrdinal;
    D3DDEVTYPE      DeviceType;
    HWND            hFocusWindow;
    DWORD           BehaviorFlags;
} D3DDEVICE_CREATION_PARAMETERS;

/* D3DBACKBUFFER_TYPE */
typedef enum _D3DBACKBUFFER_TYPE
{
    D3DBACKBUFFER_TYPE_MONO         = 0,
    D3DBACKBUFFER_TYPE_LEFT         = 1,
    D3DBACKBUFFER_TYPE_RIGHT        = 2,

    D3DBACKBUFFER_TYPE_FORCE_DWORD  = 0x7fffffff
} D3DBACKBUFFER_TYPE;

/* D3DRASTER_STATUS */
typedef struct _D3DRASTER_STATUS
{
    BOOL            InVBlank;
    UINT            ScanLine;
} D3DRASTER_STATUS;

/* D3DGAMMARAMP */
typedef struct _D3DGAMMARAMP
{
    WORD                red[256];
    WORD                green[256];
    WORD                blue[256];
} D3DGAMMARAMP;

/* D3DCLEAR */
#define D3DCLEAR_TARGET            0x00000001l
#define D3DCLEAR_ZBUFFER           0x00000002l
#define D3DCLEAR_STENCIL           0x00000004l

/* D3DCOLOR */
typedef DWORD D3DCOLOR;

#ifndef D3DCOLOR_DEFINED
#define D3DCOLOR_DEFINED
#endif

#define D3DCOLOR_ARGB(a,r,g,b) \
    ((D3DCOLOR)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define D3DCOLOR_RGBA(r,g,b,a) D3DCOLOR_ARGB(a,r,g,b)
#define D3DCOLOR_XRGB(r,g,b)   D3DCOLOR_ARGB(0xff,r,g,b)

#define D3DCOLOR_COLORVALUE(r,g,b,a) \
    D3DCOLOR_RGBA((DWORD)((r)*255.f),(DWORD)((g)*255.f),(DWORD)((b)*255.f),(DWORD)((a)*255.f))

/* D3DRECT */
typedef struct _D3DRECT {
    LONG x1;
    LONG y1;
    LONG x2;
    LONG y2;
} D3DRECT;

/* D3DTRANSFORMSTATETYPE */
typedef enum _D3DTRANSFORMSTATETYPE {
    D3DTS_VIEW          = 2,
    D3DTS_PROJECTION    = 3,
    D3DTS_TEXTURE0      = 16,
    D3DTS_TEXTURE1      = 17,
    D3DTS_TEXTURE2      = 18,
    D3DTS_TEXTURE3      = 19,
    D3DTS_TEXTURE4      = 20,
    D3DTS_TEXTURE5      = 21,
    D3DTS_TEXTURE6      = 22,
    D3DTS_TEXTURE7      = 23,

    D3DTS_FORCE_DWORD = 0x7fffffff
} D3DTRANSFORMSTATETYPE;

/* D3DMATRIX */
typedef struct _D3DMATRIX {
    union {
        struct {
            float        _11, _12, _13, _14;
            float        _21, _22, _23, _24;
            float        _31, _32, _33, _34;
            float        _41, _42, _43, _44;

        };
        float m[4][4];
    };
} D3DMATRIX;

/* D3DVIEWPORT8 */
typedef struct _D3DVIEWPORT8 {
    DWORD       X;
    DWORD       Y;
    DWORD       Width;
    DWORD       Height;
    float       MinZ;
    float       MaxZ;
} D3DVIEWPORT8;

/* D3DMATERIAL8 */
typedef struct _D3DMATERIAL8 {
    D3DCOLORVALUE   Diffuse;
    D3DCOLORVALUE   Ambient;
    D3DCOLORVALUE   Specular;
    D3DCOLORVALUE   Emissive;
    float           Power;
} D3DMATERIAL8;

/* D3DLIGHTTYPE */
typedef enum _D3DLIGHTTYPE {
    D3DLIGHT_POINT          = 1,
    D3DLIGHT_SPOT           = 2,
    D3DLIGHT_DIRECTIONAL    = 3,

    D3DLIGHT_FORCE_DWORD = 0x7fffffff
} D3DLIGHTTYPE;

/* D3DLIGHT8 */
typedef struct _D3DLIGHT8 {
    D3DLIGHTTYPE    Type;
    D3DCOLORVALUE   Diffuse;
    D3DCOLORVALUE   Specular;
    D3DCOLORVALUE   Ambient;
    D3DVECTOR       Position;
    D3DVECTOR       Direction;
    float           Range;
    float           Falloff;
    float           Attenuation0;
    float           Attenuation1;
    float           Attenuation2;
    float           Theta;
    float           Phi;
} D3DLIGHT8;

/* D3DRENDERSTATETYPE */
typedef enum _D3DRENDERSTATETYPE {
    D3DRS_ZENABLE                   = 7,
    D3DRS_FILLMODE                  = 8,
    D3DRS_SHADEMODE                 = 9,
    D3DRS_LINEPATTERN               = 10,
    D3DRS_ZWRITEENABLE              = 14,
    D3DRS_ALPHATESTENABLE           = 15,
    D3DRS_LASTPIXEL                 = 16,
    D3DRS_SRCBLEND                  = 19,
    D3DRS_DESTBLEND                 = 20,
    D3DRS_CULLMODE                  = 22,
    D3DRS_ZFUNC                     = 23,
    D3DRS_ALPHAREF                  = 24,
    D3DRS_ALPHAFUNC                 = 25,
    D3DRS_DITHERENABLE              = 26,
    D3DRS_ALPHABLENDENABLE          = 27,
    D3DRS_FOGENABLE                 = 28,
    D3DRS_SPECULARENABLE            = 29,
    D3DRS_FOGCOLOR                  = 34,
    D3DRS_FOGTABLEMODE              = 35,
    D3DRS_FOGSTART                  = 36,
    D3DRS_FOGEND                    = 37,
    D3DRS_FOGDENSITY                = 38,
    D3DRS_RANGEFOGENABLE            = 48,
    D3DRS_STENCILENABLE             = 52,
    D3DRS_STENCILFAIL               = 53,
    D3DRS_STENCILZFAIL              = 54,
    D3DRS_STENCILPASS               = 55,
    D3DRS_STENCILFUNC               = 56,
    D3DRS_STENCILREF                = 57,
    D3DRS_STENCILMASK               = 58,
    D3DRS_STENCILWRITEMASK          = 59,
    D3DRS_TEXTUREFACTOR             = 60,
    D3DRS_WRAP0                     = 128,
    D3DRS_WRAP1                     = 129,
    D3DRS_WRAP2                     = 130,
    D3DRS_WRAP3                     = 131,
    D3DRS_WRAP4                     = 132,
    D3DRS_WRAP5                     = 133,
    D3DRS_WRAP6                     = 134,
    D3DRS_WRAP7                     = 135,
    D3DRS_CLIPPING                  = 136,
    D3DRS_LIGHTING                  = 137,
    D3DRS_AMBIENT                   = 139,
    D3DRS_FOGVERTEXMODE             = 140,
    D3DRS_COLORVERTEX               = 141,
    D3DRS_LOCALVIEWER               = 142,
    D3DRS_NORMALIZENORMALS          = 143,
    D3DRS_DIFFUSEMATERIALSOURCE     = 145,
    D3DRS_SPECULARMATERIALSOURCE    = 146,
    D3DRS_AMBIENTMATERIALSOURCE     = 147,
    D3DRS_EMISSIVEMATERIALSOURCE    = 148,
    D3DRS_VERTEXBLEND               = 151,
    D3DRS_CLIPPLANEENABLE           = 152,
    D3DRS_POINTSIZE                 = 154,
    D3DRS_POINTSIZE_MIN             = 155,
    D3DRS_POINTSPRITEENABLE         = 156,
    D3DRS_POINTSCALEENABLE          = 157,
    D3DRS_POINTSCALE_A              = 158,
    D3DRS_POINTSCALE_B              = 159,
    D3DRS_POINTSCALE_C              = 160,
    D3DRS_MULTISAMPLEANTIALIAS      = 161,
    D3DRS_MULTISAMPLEMASK           = 162,
    D3DRS_PATCHEDGESTYLE            = 163,
    D3DRS_DEBUGMONITORTOKEN         = 165,
    D3DRS_POINTSIZE_MAX             = 166,
    D3DRS_INDEXEDVERTEXBLENDENABLE  = 167,
    D3DRS_COLORWRITEENABLE          = 168,
    D3DRS_TWEENFACTOR               = 170,
    D3DRS_BLENDOP                   = 171,
    D3DRS_POSITIONDEGREE            = 172,
    D3DRS_NORMALDEGREE              = 173,
    D3DRS_SCISSORTESTENABLE         = 174,
    D3DRS_SLOPESCALEDEPTHBIAS       = 175,
    D3DRS_ANTIALIASEDLINEENABLE     = 176,
    D3DRS_MINTESSELLATIONLEVEL      = 178,
    D3DRS_MAXTESSELLATIONLEVEL      = 179,
    D3DRS_ADAPTIVETESS_X            = 180,
    D3DRS_ADAPTIVETESS_Y            = 181,
    D3DRS_ADAPTIVETESS_Z            = 182,
    D3DRS_ADAPTIVETESS_W            = 183,
    D3DRS_ENABLEADAPTIVETESSELLATION = 184,
    D3DRS_TWOSIDEDSTENCILMODE       = 185,
    D3DRS_CCW_STENCILFAIL           = 186,
    D3DRS_CCW_STENCILZFAIL          = 187,
    D3DRS_CCW_STENCILPASS           = 188,
    D3DRS_CCW_STENCILFUNC           = 189,
    D3DRS_COLORWRITEENABLE1         = 190,
    D3DRS_COLORWRITEENABLE2         = 191,
    D3DRS_COLORWRITEENABLE3         = 192,
    D3DRS_BLENDFACTOR               = 193,
    D3DRS_SRGBWRITEENABLE           = 194,
    D3DRS_DEPTHBIAS                 = 195,
    D3DRS_WRAP8                     = 198,
    D3DRS_WRAP9                     = 199,
    D3DRS_WRAP10                    = 200,
    D3DRS_WRAP11                    = 201,
    D3DRS_WRAP12                    = 202,
    D3DRS_WRAP13                    = 203,
    D3DRS_WRAP14                    = 204,
    D3DRS_WRAP15                    = 205,
    D3DRS_SEPARATEALPHABLENDENABLE  = 206,
    D3DRS_SRCBLENDALPHA             = 207,
    D3DRS_DESTBLENDALPHA            = 208,
    D3DRS_BLENDOPALPHA              = 209,

    D3DRS_FORCE_DWORD = 0x7fffffff
} D3DRENDERSTATETYPE;

/* D3DSTATEBLOCKTYPE */
typedef enum _D3DSTATEBLOCKTYPE
{
    D3DSBT_ALL          = 1,
    D3DSBT_PIXELSTATE   = 2,
    D3DSBT_VERTEXSTATE  = 3,

    D3DSBT_FORCE_DWORD = 0x7fffffff
} D3DSTATEBLOCKTYPE;

/* D3DTEXTURESTAGESTATETYPE */
typedef enum _D3DTEXTURESTAGESTATETYPE
{
    D3DTSS_COLOROP        =  1,
    D3DTSS_COLORARG1      =  2,
    D3DTSS_COLORARG2      =  3,
    D3DTSS_ALPHAOP        =  4,
    D3DTSS_ALPHAARG1      =  5,
    D3DTSS_ALPHAARG2      =  6,
    D3DTSS_BUMPENVMAT00   =  7,
    D3DTSS_BUMPENVMAT01   =  8,
    D3DTSS_BUMPENVMAT10   =  9,
    D3DTSS_BUMPENVMAT11   = 10,
    D3DTSS_TEXCOORDINDEX  = 11,
    D3DTSS_BUMPENVLSCALE  = 22,
    D3DTSS_BUMPENVLOFFSET = 23,
    D3DTSS_TEXTURETRANSFORMFLAGS = 24,
    D3DTSS_COLORARG0      = 26,
    D3DTSS_ALPHAARG0      = 27,
    D3DTSS_RESULTARG      = 28,

    D3DTSS_FORCE_DWORD = 0x7fffffff
} D3DTEXTURESTAGESTATETYPE;

/* D3DTEXTUREOP */
typedef enum _D3DTEXTUREOP
{
    D3DTOP_DISABLE              = 1,
    D3DTOP_SELECTARG1           = 2,
    D3DTOP_SELECTARG2           = 3,
    D3DTOP_MODULATE             = 4,
    D3DTOP_MODULATE2X           = 5,
    D3DTOP_MODULATE4X           = 6,
    D3DTOP_ADD                  =  7,
    D3DTOP_ADDSIGNED            =  8,
    D3DTOP_ADDSIGNED2X          =  9,
    D3DTOP_SUBTRACT             = 10,
    D3DTOP_ADDSMOOTH            = 11,
    D3DTOP_BLENDDIFFUSEALPHA    = 12,
    D3DTOP_BLENDTEXTUREALPHA    = 13,
    D3DTOP_BLENDFACTORALPHA     = 14,
    D3DTOP_BLENDTEXTUREALPHAPM  = 15,
    D3DTOP_BLENDCURRENTALPHA    = 16,
    D3DTOP_PREMODULATE          = 17,
    D3DTOP_MODULATEALPHA_ADDCOLOR = 18,
    D3DTOP_MODULATECOLOR_ADDALPHA = 19,
    D3DTOP_MODULATEINVALPHA_ADDCOLOR = 20,
    D3DTOP_MODULATEINVCOLOR_ADDALPHA = 21,
    D3DTOP_BUMPENVMAP           = 22,
    D3DTOP_BUMPENVMAPLUMINANCE  = 23,
    D3DTOP_DOTPRODUCT3          = 24,
    D3DTOP_MULTIPLYADD          = 25,
    D3DTOP_LERP                 = 26,

    D3DTOP_FORCE_DWORD = 0x7fffffff
} D3DTEXTUREOP;

/* D3DTEXTUREADDRESS */
typedef enum _D3DTEXTUREADDRESS {
    D3DTADDRESS_WRAP            = 1,
    D3DTADDRESS_MIRROR          = 2,
    D3DTADDRESS_CLAMP           = 3,
    D3DTADDRESS_BORDER          = 4,
    D3DTADDRESS_MIRRORONCE      = 5,

    D3DTADDRESS_FORCE_DWORD = 0x7fffffff
} D3DTEXTUREADDRESS;

/* D3DCULL */
typedef enum _D3DCULL {
    D3DCULL_NONE                = 1,
    D3DCULL_CW                  = 2,
    D3DCULL_CCW                 = 3,

    D3DCULL_FORCE_DWORD = 0x7fffffff
} D3DCULL;

/* D3DCMPFUNC */
typedef enum _D3DCMPFUNC {
    D3DCMP_NEVER                = 1,
    D3DCMP_LESS                 = 2,
    D3DCMP_EQUAL                = 3,
    D3DCMP_LESSEQUAL            = 4,
    D3DCMP_GREATER              = 5,
    D3DCMP_NOTEQUAL             = 6,
    D3DCMP_GREATEREQUAL         = 7,
    D3DCMP_ALWAYS               = 8,

    D3DCMP_FORCE_DWORD = 0x7fffffff
} D3DCMPFUNC;

/* D3DSTENCILOP */
typedef enum _D3DSTENCILOP {
    D3DSTENCILOP_KEEP           = 1,
    D3DSTENCILOP_ZERO           = 2,
    D3DSTENCILOP_REPLACE        = 3,
    D3DSTENCILOP_INCRSAT        = 4,
    D3DSTENCILOP_DECRSAT        = 5,
    D3DSTENCILOP_INVERT         = 6,
    D3DSTENCILOP_INCR           = 7,
    D3DSTENCILOP_DECR           = 8,

    D3DSTENCILOP_FORCE_DWORD = 0x7fffffff
} D3DSTENCILOP;

/* D3DFOGMODE */
typedef enum _D3DFOGMODE {
    D3DFOG_NONE                 = 0,
    D3DFOG_EXP                  = 1,
    D3DFOG_EXP2                 = 2,
    D3DFOG_LINEAR               = 3,

    D3DFOG_FORCE_DWORD = 0x7fffffff
} D3DFOGMODE;

/* D3DZBUFFERTYPE */
typedef enum _D3DZBUFFERTYPE {
    D3DZB_FALSE                 = 0,
    D3DZB_TRUE                  = 1, // Z buffering
    D3DZB_USEW                  = 2, // W buffering

    D3DZB_FORCE_DWORD = 0x7fffffff
} D3DZBUFFERTYPE;

/* D3DPRIMITIVETYPE */
typedef enum _D3DPRIMITIVETYPE {
    D3DPT_POINTLIST             = 1,
    D3DPT_LINELIST              = 2,
    D3DPT_LINESTRIP             = 3,
    D3DPT_TRIANGLELIST          = 4,
    D3DPT_TRIANGLESTRIP         = 5,
    D3DPT_TRIANGLEFAN           = 6,

    D3DPT_FORCE_DWORD = 0x7fffffff
} D3DPRIMITIVETYPE;

/* D3DSHADEMODE */
typedef enum _D3DSHADEMODE {
    D3DSHADE_FLAT               = 1,
    D3DSHADE_GOURAUD            = 2,
    D3DSHADE_PHONG              = 3,

    D3DSHADE_FORCE_DWORD = 0x7fffffff
} D3DSHADEMODE;

/* D3DFILLMODE */
typedef enum _D3DFILLMODE {
    D3DFILL_POINT               = 1,
    D3DFILL_WIREFRAME           = 2,
    D3DFILL_SOLID               = 3,

    D3DFILL_FORCE_DWORD = 0x7fffffff
} D3DFILLMODE;

/* D3DBLEND */
typedef enum _D3DBLEND {
    D3DBLEND_ZERO               = 1,
    D3DBLEND_ONE                = 2,
    D3DBLEND_SRCCOLOR           = 3,
    D3DBLEND_INVSRCCOLOR        = 4,
    D3DBLEND_SRCALPHA           = 5,
    D3DBLEND_INVSRCALPHA        = 6,
    D3DBLEND_DESTALPHA          = 7,
    D3DBLEND_INVDESTALPHA       = 8,
    D3DBLEND_DESTCOLOR          = 9,
    D3DBLEND_INVDESTCOLOR       = 10,
    D3DBLEND_SRCALPHASAT        = 11,
    D3DBLEND_BOTHSRCALPHA       = 12,
    D3DBLEND_BOTHINVSRCALPHA    = 13,

    D3DBLEND_FORCE_DWORD = 0x7fffffff
} D3DBLEND;

/* D3DBLENDOP */
typedef enum _D3DBLENDOP {
    D3DBLENDOP_ADD              = 1,
    D3DBLENDOP_SUBTRACT         = 2,
    D3DBLENDOP_REVSUBTRACT      = 3,
    D3DBLENDOP_MIN              = 4,
    D3DBLENDOP_MAX              = 5,

    D3DBLENDOP_FORCE_DWORD = 0x7fffffff
} D3DBLENDOP;

/* D3DTEXTUREFILTERTYPE */
typedef enum _D3DTEXTUREFILTERTYPE
{
    D3DTEXF_NONE            = 0,
    D3DTEXF_POINT           = 1,
    D3DTEXF_LINEAR          = 2,
    D3DTEXF_ANISOTROPIC     = 3,
    D3DTEXF_FLATCUBIC       = 4,
    D3DTEXF_GAUSSIANCUBIC   = 5,

    D3DTEXF_FORCE_DWORD = 0x7fffffff
} D3DTEXTUREFILTERTYPE;

/* D3DVSDE_ */
typedef struct _D3DVERTEXSHADERDECL
{
    DWORD       Token;
    DWORD       Offset;
    DWORD       Type;
    DWORD       Method;
    DWORD       Usage;
    BYTE        UsageIndex;
} D3DVERTEXSHADERDECL;

/* D3DVSD_TOKENTYPE */
enum D3DVSD_TOKENTYPE
{
    D3DVSD_TOKEN_NOP        = 0,
    D3DVSD_TOKEN_STREAM,
    D3DVSD_TOKEN_STREAMDATA,
    D3DVSD_TOKEN_TESSELLATOR,
    D3DVSD_TOKEN_CONSTMEM,
    D3DVSD_TOKEN_EXT,
    D3DVSD_TOKEN_END = 7,

    D3DVSD_FORCE_DWORD = 0x7fffffff
};

/* D3DVSD_DATALOADTYPE */
enum D3DVSD_DATALOADTYPE
{
    D3DVSD_LOAD_FLOAT1 = 0,
    D3DVSD_LOAD_FLOAT2,
    D3DVSD_LOAD_FLOAT3,
    D3DVSD_LOAD_FLOAT4,
    D3DVSD_LOAD_D3DCOLOR,
    D3DVSD_LOAD_UBYTE4,
    D3DVSD_LOAD_SHORT2,
    D3DVSD_LOAD_SHORT4,
    D3DVSD_LOAD_NORMSHORT2,
    D3DVSD_LOAD_NORMSHORT4,
    D3DVSD_LOAD_NORMPACKED3,
    D3DVSD_LOAD_SHORT2N,
    D3DVSD_LOAD_SHORT4N,
    D3DVSD_LOAD_USHORT2N,
    D3DVSD_LOAD_USHORT4N,
    D3DVSD_LOAD_UDEC3,
    D3DVSD_LOAD_DEC3N,
    D3DVSD_LOAD_FLOAT16_2,
    D3DVSD_LOAD_FLOAT16_4,

    D3DVSD_LOAD_FORCE_DWORD = 0x7fffffff
};

/* D3DVSD_METHOD */
enum D3DVSD_METHOD
{
    D3DVSD_METHOD_DEFAULT = 0,
    D3DVSD_METHOD_PARTIALU,
    D3DVSD_METHOD_PARTIALV,
    D3DVSD_METHOD_CROSSUV,
    D3DVSD_METHOD_UV,
    D3DVSD_METHOD_LOOKUP,
    D3DVSD_METHOD_LOOKUPPRESAMPLED,

    D3DVSD_METHOD_FORCE_DWORD = 0x7fffffff
};

/* D3DVSD_USAGE */
enum D3DVSD_USAGE
{
    D3DVSD_USAGE_POSITION = 0,
    D3DVSD_USAGE_BLENDWEIGHT,
    D3DVSD_USAGE_BLENDINDICES,
    D3DVSD_USAGE_NORMAL,
    D3DVSD_USAGE_PSIZE,
    D3DVSD_USAGE_DIFFUSE,
    D3DVSD_USAGE_SPECULAR,
    D3DVSD_USAGE_TEXCOORD,
    D3DVSD_USAGE_POSITIONT,
    D3DVSD_USAGE_TANGENT,
    D3DVSD_USAGE_BINORMAL,
    D3DVSD_USAGE_TESSFACTOR,

    D3DVSD_FORCE_DWORD = 0x7fffffff
};

/* D3DFVF */
#define D3DFVF_RESERVED0        0x001
#define D3DFVF_POSITION_MASK    0x00E
#define D3DFVF_XYZ              0x002
#define D3DFVF_XYZRHW           0x004
#define D3DFVF_XYZB1            0x006
#define D3DFVF_XYZB2            0x008
#define D3DFVF_XYZB3            0x00A
#define D3DFVF_XYZB4            0x00C
#define D3DFVF_XYZB5            0x00E
#define D3DFVF_NORMAL           0x010
#define D3DFVF_PSIZE            0x020
#define D3DFVF_DIFFUSE          0x040
#define D3DFVF_SPECULAR         0x080
#define D3DFVF_TEXCOUNT_MASK    0xf00
#define D3DFVF_TEXCOUNT_SHIFT   8
#define D3DFVF_TEX0             0x000
#define D3DFVF_TEX1             0x100
#define D3DFVF_TEX2             0x200
#define D3DFVF_TEX3             0x300
#define D3DFVF_TEX4             0x400
#define D3DFVF_TEX5             0x500
#define D3DFVF_TEX6             0x600
#define D3DFVF_TEX7             0x700
#define D3DFVF_TEX8             0x800
#define D3DFVF_RESERVED2        0xE000
#define D3DFVF_TEXTUREFORMAT2   0
#define D3DFVF_TEXTUREFORMAT1   3
#define D3DFVF_TEXTUREFORMAT3   1
#define D3DFVF_TEXTUREFORMAT4   2

/* D3DVS_ADDRESSMODE */
typedef enum _D3DVS_ADDRESSMODE_TYPE
{
    D3DVS_ADDR_ABSOLUTE,
    D3DVS_ADDR_RELATIVE,

    D3DVS_ADDR_FORCE_DWORD = 0x7fffffff
} D3DVS_ADDRESSMODE_TYPE;

/* D3DVS_SWIZZLE */
#define D3DVS_NOSWIZZLE ( (D3DVS_X_X<<0L) | (D3DVS_Y_Y<<2L) | (D3DVS_Z_Z<<4L) | (D3DVS_W_W<<6L) )
#define D3DVS_SWIZZLE_MASK 0x000000FFL
#define D3DVS_REPLICATE_MASK 0x00000003L
#define D3DVS_X_X 0
#define D3DVS_Y_Y 1
#define D3DVS_Z_Z 2
#define D3DVS_W_W 3
#define D3DVS_X_Y 2
#define D3DVS_X_Z 3
#define D3DVS_X_W 0
#define D3DVS_Y_X 3
#define D3DVS_Y_Z 0
#define D3DVS_Y_W 1
#define D3DVS_Z_X 0
#define D3DVS_Z_Y 1
#define D3DVS_Z_W 2
#define D3DVS_W_X 1
#define D3DVS_W_Y 2
#define D3DVS_W_Z 3

/* D3DSHADER_INSTRUCTION_OPCODE_TYPE */
typedef enum _D3DSHADER_INSTRUCTION_OPCODE_TYPE
{
    D3DSIO_NOP          = 0,
    D3DSIO_MOV          = 1,
    D3DSIO_ADD          = 2,
    D3DSIO_SUB          = 3,
    D3DSIO_MAD          = 4,
    D3DSIO_MUL          = 5,
    D3DSIO_RCP          = 6,
    D3DSIO_RSQ          = 7,
    D3DSIO_DP3          = 8,
    D3DSIO_DP4          = 9,
    D3DSIO_MIN          = 10,
    D3DSIO_MAX          = 11,
    D3DSIO_SLT          = 12,
    D3DSIO_SGE          = 13,
    D3DSIO_EXP          = 14,
    D3DSIO_LOG          = 15,
    D3DSIO_LIT          = 16,
    D3DSIO_DST          = 17,
    D3DSIO_LRP          = 18,
    D3DSIO_FRC          = 19,
    D3DSIO_M4x4         = 20,
    D3DSIO_M4x3         = 21,
    D3DSIO_M3x4         = 22,
    D3DSIO_M3x3         = 23,
    D3DSIO_M3x2         = 24,
    D3DSIO_CALL         = 25,
    D3DSIO_CALLNZ       = 26,
    D3DSIO_LOOP         = 27,
    D3DSIO_RET          = 28,
    D3DSIO_ENDLOOP      = 29,
    D3DSIO_LABEL        = 30,
    D3DSIO_DCL          = 31,
    D3DSIO_POW          = 32,
    D3DSIO_CRS          = 33,
    D3DSIO_SGN          = 34,
    D3DSIO_ABS          = 35,
    D3DSIO_NRM          = 36,
    D3DSIO_SINCOS       = 37,
    D3DSIO_REP          = 38,
    D3DSIO_ENDREP       = 39,
    D3DSIO_IF           = 40,
    D3DSIO_IFC          = 41,
    D3DSIO_ELSE         = 42,
    D3DSIO_ENDIF        = 43,
    D3DSIO_BREAK        = 44,
    D3DSIO_BREAKC       = 45,
    D3DSIO_MOVA         = 46,
    D3DSIO_DEFB         = 47,
    D3DSIO_DEFI         = 48,
    D3DSIO_TEX          = 64,
    D3DSIO_TEXCOORD     = 65,
    D3DSIO_TEXKILL      = 66,
    D3DSIO_TEXLD        = 67,
    D3DSIO_DEF          = 68,
    D3DSIO_PHASE        = 0xFFFD,
    D3DSIO_COMMENT      = 0xFFFE,
    D3DSIO_END          = 0xFFFF,

    D3DSIO_FORCE_DWORD  = 0x7fffffff
} D3DSHADER_INSTRUCTION_OPCODE_TYPE;

/* D3DSHADER_PARAM_REGISTER_TYPE */
typedef enum _D3DSHADER_PARAM_REGISTER_TYPE
{
    D3DSPR_TEMP,
    D3DSPR_INPUT,
    D3DSPR_CONST,
    D3DSPR_ADDR,
    D3DSPR_RASTOUT,
    D3DSPR_ATTROUT,
    D3DSPR_TEXCRDOUT,
    D3DSPR_CONST2,
    D3DSPR_CONST3,
    D3DSPR_CONST4,
    D3DSPR_CONSTINT,
    D3DSPR_COLOROUT,
    D3DSPR_DEPTHOUT,
    D3DSPR_SAMPLER,
    D3DSPR_CONSTBOOL,
    D3DSPR_LOOP,
    D3DSPR_TEMPFLOAT16,
    D3DSPR_MISCTYPE,
    D3DSPR_LABEL,
    D3DSPR_PREDICATE,

    D3DSPR_FORCE_DWORD = 0x7fffffff
} D3DSHADER_PARAM_REGISTER_TYPE;

/* D3DSHADER_MISCTYPE_OFFSETS */
typedef enum _D3DSHADER_MISCTYPE_OFFSETS
{
    D3DSMO_POSITION,
    D3DSMO_FACE
} D3DSHADER_MISCTYPE_OFFSETS;

/* D3DSHADER_PARAM_SRCMOD_TYPE */
typedef enum _D3DSHADER_PARAM_SRCMOD_TYPE
{
    D3DSPSM_NONE,
    D3DSPSM_NEG,
    D3DSPSM_BIAS,
    D3DSPSM_BIASNEG,
    D3DSPSM_SIGN,
    D3DSPSM_SIGNNEG,
    D3DSPSM_COMP,
    D3DSPSM_X2,
    D3DSPSM_X2NEG,
    D3DSPSM_DZ,
    D3DSPSM_DW,
    D3DSPSM_ABS,
    D3DSPSM_ABSNEG,
    D3DSPSM_NOT,

    D3DSPSM_FORCE_DWORD = 0x7fffffff
} D3DSHADER_PARAM_SRCMOD_TYPE;

/* D3DBASISTYPE */
typedef enum _D3DBASISTYPE
{
    D3DBASIS_BEZIER      = 0,
    D3DBASIS_BSPLINE     = 1,
    D3DBASIS_CATMULL_ROM = 2,

    D3DBASIS_FORCE_DWORD = 0x7fffffff
} D3DBASISTYPE;

/* D3DDEGREETYPE */
typedef enum _D3DDEGREETYPE
{
    D3DDEGREE_LINEAR      = 1,
    D3DDEGREE_QUADRATIC   = 2,
    D3DDEGREE_CUBIC       = 3,
    D3DDEGREE_QUINTIC     = 5,

    D3DDEGREE_FORCE_DWORD = 0x7fffffff
} D3DDEGREETYPE;

/* D3DCLIPSTATUS8 */
typedef struct _D3DCLIPSTATUS8
{
    DWORD   ClipUnion;
    DWORD   ClipIntersection;
} D3DCLIPSTATUS8;

/* IDirect3DResource8 */
#undef INTERFACE
#define INTERFACE IDirect3DResource8

DECLARE_INTERFACE_(IDirect3DResource8, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    // IDirect3DResource8
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;
};

/* IDirect3DBaseTexture8 */
#undef INTERFACE
#define INTERFACE IDirect3DBaseTexture8

DECLARE_INTERFACE_(IDirect3DBaseTexture8, IDirect3DResource8)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    // IDirect3DResource8
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;

    // IDirect3DBaseTexture8
    STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) PURE;
    STDMETHOD_(DWORD, GetLOD)(THIS) PURE;
    STDMETHOD_(DWORD, GetLevelCount)(THIS) PURE;
};

/* IDirect3DTexture8 */
#undef INTERFACE
#define INTERFACE IDirect3DTexture8

DECLARE_INTERFACE_(IDirect3DTexture8, IDirect3DBaseTexture8)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    // IDirect3DResource8
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;

    // IDirect3DBaseTexture8
    STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) PURE;
    STDMETHOD_(DWORD, GetLOD)(THIS) PURE;
    STDMETHOD_(DWORD, GetLevelCount)(THIS) PURE;

    // IDirect3DTexture8
    STDMETHOD(GetLevelDesc)(THIS_ UINT Level,D3DSURFACE_DESC *pDesc) PURE;
    STDMETHOD(GetSurfaceLevel)(THIS_ UINT Level,IDirect3DSurface8** ppSurfaceLevel) PURE;
    STDMETHOD(LockRect)(THIS_ UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) PURE;
    STDMETHOD(UnlockRect)(THIS_ UINT Level) PURE;
    STDMETHOD(AddDirtyRect)(THIS_ CONST RECT* pDirtyRect) PURE;
};

/* IDirect3DCubeTexture8 */
#undef INTERFACE
#define INTERFACE IDirect3DCubeTexture8

DECLARE_INTERFACE_(IDirect3DCubeTexture8, IDirect3DBaseTexture8)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    // IDirect3DResource8
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;

    // IDirect3DBaseTexture8
    STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) PURE;
    STDMETHOD_(DWORD, GetLOD)(THIS) PURE;
    STDMETHOD_(DWORD, GetLevelCount)(THIS) PURE;

    // IDirect3DCubeTexture8
    STDMETHOD(GetLevelDesc)(THIS_ UINT Level,D3DSURFACE_DESC *pDesc) PURE;
    STDMETHOD(GetCubeMapSurface)(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,IDirect3DSurface8** ppCubeMapSurface) PURE;
    STDMETHOD(LockRect)(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level,D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) PURE;
    STDMETHOD(UnlockRect)(THIS_ D3DCUBEMAP_FACES FaceType,UINT Level) PURE;
    STDMETHOD(AddDirtyRect)(THIS_ D3DCUBEMAP_FACES FaceType,CONST RECT* pDirtyRect) PURE;
};

/* IDirect3DVolumeTexture8 */
#undef INTERFACE
#define INTERFACE IDirect3DVolumeTexture8

DECLARE_INTERFACE_(IDirect3DVolumeTexture8, IDirect3DBaseTexture8)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    // IDirect3DResource8
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;

    // IDirect3DBaseTexture8
    STDMETHOD_(DWORD, SetLOD)(THIS_ DWORD LODNew) PURE;
    STDMETHOD_(DWORD, GetLOD)(THIS) PURE;
    STDMETHOD_(DWORD, GetLevelCount)(THIS) PURE;

    // IDirect3DVolumeTexture8
    STDMETHOD(GetLevelDesc)(THIS_ UINT Level,D3DVOLUME_DESC *pDesc) PURE;
    STDMETHOD(GetVolumeLevel)(THIS_ UINT Level,IDirect3DVolume8** ppVolumeLevel) PURE;
    STDMETHOD(LockBox)(THIS_ UINT Level,D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags) PURE;
    STDMETHOD(UnlockBox)(THIS_ UINT Level) PURE;
    STDMETHOD(AddDirtyBox)(THIS_ CONST D3DBOX* pDirtyBox) PURE;
};

/* IDirect3DVertexBuffer8 */
#undef INTERFACE
#define INTERFACE IDirect3DVertexBuffer8

DECLARE_INTERFACE_(IDirect3DVertexBuffer8, IDirect3DResource8)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    // IDirect3DResource8
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;

    // IDirect3DVertexBuffer8
    STDMETHOD(Lock)(THIS_ UINT OffsetToLock,UINT SizeToLock,BYTE** ppbData,DWORD Flags) PURE;
    STDMETHOD(Unlock)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ D3DVERTEXBUFFER_DESC *pDesc) PURE;
};

/* IDirect3DIndexBuffer8 */
#undef INTERFACE
#define INTERFACE IDirect3DIndexBuffer8

DECLARE_INTERFACE_(IDirect3DIndexBuffer8, IDirect3DResource8)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    // IDirect3DResource8
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD_(DWORD, SetPriority)(THIS_ DWORD PriorityNew) PURE;
    STDMETHOD_(DWORD, GetPriority)(THIS) PURE;
    STDMETHOD_(void, PreLoad)(THIS) PURE;
    STDMETHOD_(D3DRESOURCETYPE, GetType)(THIS) PURE;

    // IDirect3DIndexBuffer8
    STDMETHOD(Lock)(THIS_ UINT OffsetToLock,UINT SizeToLock,BYTE** ppbData,DWORD Flags) PURE;
    STDMETHOD(Unlock)(THIS) PURE;
    STDMETHOD(GetDesc)(THIS_ D3DINDEXBUFFER_DESC *pDesc) PURE;
};

/* IDirect3DSurface8 */
#undef INTERFACE
#define INTERFACE IDirect3DSurface8

DECLARE_INTERFACE_(IDirect3DSurface8, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    // IDirect3DSurface8
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD(GetContainer)(THIS_ REFIID riid,void** ppContainer) PURE;
    STDMETHOD(GetDesc)(THIS_ D3DSURFACE_DESC *pDesc) PURE;
    STDMETHOD(LockRect)(THIS_ D3DLOCKED_RECT* pLockedRect,CONST RECT* pRect,DWORD Flags) PURE;
    STDMETHOD(UnlockRect)(THIS) PURE;
};

/* IDirect3DVolume8 */
#undef INTERFACE
#define INTERFACE IDirect3DVolume8

DECLARE_INTERFACE_(IDirect3DVolume8, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    // IDirect3DVolume8
    STDMETHOD(GetDevice)(THIS_ IDirect3DDevice8** ppDevice) PURE;
    STDMETHOD(SetPrivateData)(THIS_ REFGUID refguid,CONST void* pData,DWORD SizeOfData,DWORD Flags) PURE;
    STDMETHOD(GetPrivateData)(THIS_ REFGUID refguid,void* pData,DWORD* pSizeOfData) PURE;
    STDMETHOD(FreePrivateData)(THIS_ REFGUID refguid) PURE;
    STDMETHOD(GetContainer)(THIS_ REFIID riid,void** ppContainer) PURE;
    STDMETHOD(GetDesc)(THIS_ D3DVOLUME_DESC *pDesc) PURE;
    STDMETHOD(LockBox)(THIS_ D3DLOCKED_BOX* pLockedVolume,CONST D3DBOX* pBox,DWORD Flags) PURE;
    STDMETHOD(UnlockBox)(THIS) PURE;
};

/* IDirect3DSwapChain8 */
#undef INTERFACE
#define INTERFACE IDirect3DSwapChain8

DECLARE_INTERFACE_(IDirect3DSwapChain8, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, void** ppvObj) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;

    // IDirect3DSwapChain8
    STDMETHOD(Present)(THIS_ CONST RECT* pSourceRect,CONST RECT* pDestRect,HWND hDestWindowOverride,CONST RGNDATA* pDirtyRegion) PURE;
    STDMETHOD(GetBackBuffer)(THIS_ UINT BackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface8** ppBackBuffer) PURE;
};

#ifdef __cplusplus
}
#endif

#endif // (DIRECT3D_VERSION >= 0x0800)
#endif // _D3D8_H_