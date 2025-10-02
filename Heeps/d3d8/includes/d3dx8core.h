/*==========================================================================;
 *
 *  Copyright (C) 1994-2001 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       d3dx8core.h
 *  Content:    D3DX core types and functions
 *
 ***************************************************************************/

#ifndef __D3DX8CORE_H__
#define __D3DX8CORE_H__

#include "d3d8.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

//----------------------------------------------------------------------------
// D3DX_VERSION:
// --------------
// The D3DX_SDK_VERSION is used to confirm that the header files used by an
// application are from the same release as the D3DX library files that the
// application links to.  D3DX8.DLL is not a redistributable DLL, so this
// will not be a problem for most applications.  However, for those that
// do ship D3DX8.DLL, this version check will prevent problems when the
// user has a different version of the DirectX 8 SDK installed on their
// machine.
//----------------------------------------------------------------------------

#define D3DX_SDK_VERSION 12

#ifndef D3DX_SDK_VERSION
#define D3DX_SDK_VERSION 0
#endif

#if(D3DX_SDK_VERSION != 0)
#if(DIRECT3D_VERSION != 0x0800)
#error D3DX8 requires D3D8
#endif
#endif



//----------------------------------------------------------------------------
// D3DXGetDriverLevel:
// ------------------
// Returns the "level" of the Direct3D driver.  This is basically the same
// as the DirectX version, but is retrieved from the driver so that we can
// be sure of the driver's capabilities. (ie. a DX7 driver on a DX8 system)
//
// Returns:
//      800     DirectX 8.0 driver
//      700     DirectX 7.0 driver
//      600     DirectX 6.0 driver
//      ...
//
//----------------------------------------------------------------------------

UINT WINAPI
    D3DXGetDriverLevel(
        IDirect3DDevice8 *pDevice);



//----------------------------------------------------------------------------
// D3DXCreateTexture, D3DXCreateCubeTexture, D3DXCreateVolumeTexture
// ----------------------------------------------------------------
// Create texture objects.
//
// Parameters:
//  pDevice
//      The D3D device with which the texture is to be associated.
//  Width
//      Width of the texture.
//  Height
//      Height of the texture.
//  Depth
//      Depth of the texture.
//  EdgeLength
//      EdgeLength of the cube texture.
//  MipLevels
//      Number of mip-levels.  Use 0 for a complete mip-chain.
//  Usage
//      D3DUSAGE flags.
//  Format
//      D3DFORMAT request for the texture.
//  Pool
//      D3DPOOL in which to place the texture.
//  ppTexture
//      The texture object that will be created.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateTexture(
        LPDIRECT3DDEVICE8       pDevice,
        UINT                    Width,
        UINT                    Height,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        LPDIRECT3DTEXTURE8*     ppTexture);

HRESULT WINAPI
    D3DXCreateCubeTexture(
        LPDIRECT3DDEVICE8       pDevice,
        UINT                    EdgeLength,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        LPDIRECT3DCUBETEXTURE8* ppCubeTexture);

HRESULT WINAPI
    D3DXCreateVolumeTexture(
        LPDIRECT3DDEVICE8       pDevice,
        UINT                    Width,
        UINT                    Height,
        UINT                    Depth,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        LPDIRECT3DVOLUMETEXTURE8* ppVolumeTexture);


//----------------------------------------------------------------------------
// D3DXCreateTextureFromFile, D3DXCreateCubeTextureFromFile, D3DXCreateVolumeTextureFromFile
// D3DXCreateTextureFromResource, D3DXCreateCubeTextureFromResource, D3DXCreateVolumeTextureFromResource
// D3DXCreateTextureFromFileInMemory, D3DXCreateCubeTextureFromFileInMemory, D3DCreateVolumeTextureFromFileInMemory
// --------------------------------------------------------------------------------
// Create a texture from a file or resource.
//
// Parameters:
//  pDevice
//      The D3D device with which the texture is to be associated.
//  pSrcFile
//      File name.
//  hSrcModule
//      Module handle. if NULL, current module will be used.
//  pSrcResource
//      Resource name in module
//  pSrcData
//      Pointer to file in memory.
//  SrcDataSize
//      Size in bytes of file in memory.
//  Width, Height, Depth, EdgeLength
//      Size of texture to create.  If 0, the size will be taken from the
//      file.  If the file is not a .dds file, D3DX will attempt to create
//      a texture with these dimensions, and then stretch the image to
//      fit.
//  MipLevels
//      Number of mip-levels.  Use D3DX_DEFAULT for a complete mip-chain, or
//      1 for a single level texture.
//  Usage
//      D3DUSAGE flags.
//  Format
//      D3DFORMAT request for the texture.  Use D3DFMT_UNKNOWN to take the
//      format from the file.
//  Pool
//      D3DPOOL in which to place the texture.  Use D3DPOOL_DEFAULT to have
//      D3DX select the best pool based on Usage.  Textures with D3DUSAGE_RENDERTARGET
//      or D3DUSAGE_DEPTHSTENCIL must be in D3DPOOL_DEFAULT.
//  Filter
//      D3DX_FILTER flags controlling how the image is filtered.
//      Or D3DX_DEFAULT to use D3DX_FILTER_TRIANGLE.
//  MipFilter
//      D3DX_FILTER flags controlling how the mip-levels are filtered.
//      Or D3DX_DEFAULT to use D3DX_FILTER_BOX.
//  ColorKey
//      Color to be replaced with D3DCOLOR_RGBA(0,0,0,0).  Or 0 to disable
//      the colorkey.  This is always a 32-bit ARGB color, independent of
//      the source image format.  Alpha is significant.
//  pSrcInfo
//      Returns information about the source image.
//  pPalette
//      256 color palette to be filled in.
//  ppTexture
//      The texture object that will be created
//----------------------------------------------------------------------------


#define D3DX_DEFAULT            ((UINT) -1)
#define D3DX_DEFAULT_NONPOW2    ((UINT) -2)
#define D3DX_DEFAULT_FLOAT      ((float) -3)

// Image information, returned by D3DXGetImageInfoFromFile etc.
typedef struct _D3DXIMAGE_INFO
{
    UINT Width;
    UINT Height;
    UINT Depth;
    UINT MipLevels;
    D3DFORMAT Format;
    D3DRESOURCETYPE ResourceType;

} D3DXIMAGE_INFO;


// D3DXCubeMap layout
typedef enum _D3DXCUBEMAP_FACES
{
    D3DXCUBEMAP_FACE_POSITIVE_X = 0,
    D3DXCUBEMAP_FACE_NEGATIVE_X = 1,
    D3DXCUBEMAP_FACE_POSITIVE_Y = 2,
    D3DXCUBEMAP_FACE_NEGATIVE_Y = 3,
    D3DXCUBEMAP_FACE_POSITIVE_Z = 4,
    D3DXCUBEMAP_FACE_NEGATIVE_Z = 5,

} D3DXCUBEMAP_FACES;


// Filter modes
#define D3DX_FILTER_NONE              (1L << 0)
#define D3DX_FILTER_POINT             (2L << 0)
#define D3DX_FILTER_LINEAR            (3L << 0)
#define D3DX_FILTER_TRIANGLE          (4L << 0)
#define D3DX_FILTER_BOX               (5L << 0)

#define D3DX_FILTER_MIRROR_U          (1L << 16)
#define D3DX_FILTER_MIRROR_V          (2L << 16)
#define D3DX_FILTER_MIRROR_W          (4L << 16)
#define D3DX_FILTER_MIRROR            (7L << 16)

#define D3DX_FILTER_DITHER            (1L << 19)
#define D3DX_FILTER_SRGB_IN           (1L << 20)
#define D3DX_FILTER_SRGB_OUT          (2L << 20)
#define D3DX_FILTER_SRGB              (3L << 20)


HRESULT WINAPI
    D3DXCreateTextureFromFileA(
        LPDIRECT3DDEVICE8       pDevice,
        LPCSTR                  pSrcFile,
        LPDIRECT3DTEXTURE8*     ppTexture);

HRESULT WINAPI
    D3DXCreateTextureFromFileW(
        LPDIRECT3DDEVICE8       pDevice,
        LPCWSTR                 pSrcFile,
        LPDIRECT3DTEXTURE8*     ppTexture);

#ifdef UNICODE
#define D3DXCreateTextureFromFile D3DXCreateTextureFromFileW
#else
#define D3DXCreateTextureFromFile D3DXCreateTextureFromFileA
#endif


HRESULT WINAPI
    D3DXCreateTextureFromFileExA(
        LPDIRECT3DDEVICE8       pDevice,
        LPCSTR                  pSrcFile,
        UINT                    Width,
        UINT                    Height,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        DWORD                   Filter,
        DWORD                   MipFilter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*           pPalette,
        LPDIRECT3DTEXTURE8*     ppTexture);

HRESULT WINAPI
    D3DXCreateTextureFromFileExW(
        LPDIRECT3DDEVICE8       pDevice,
        LPCWSTR                 pSrcFile,
        UINT                    Width,
        UINT                    Height,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        DWORD                   Filter,
        DWORD                   MipFilter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*           pPalette,
        LPDIRECT3DTEXTURE8*     ppTexture);

#ifdef UNICODE
#define D3DXCreateTextureFromFileEx D3DXCreateTextureFromFileExW
#else
#define D3DXCreateTextureFromFileEx D3DXCreateTextureFromFileExA
#endif



HRESULT WINAPI
    D3DXCreateTextureFromResourceA(
        LPDIRECT3DDEVICE8       pDevice,
        HMODULE                 hSrcModule,
        LPCSTR                  pSrcResource,
        LPDIRECT3DTEXTURE8*     ppTexture);

HRESULT WINAPI
    D3DXCreateTextureFromResourceW(
        LPDIRECT3DDEVICE8       pDevice,
        HMODULE                 hSrcModule,
        LPCWSTR                 pSrcResource,
        LPDIRECT3DTEXTURE8*     ppTexture);

#ifdef UNICODE
#define D3DXCreateTextureFromResource D3DXCreateTextureFromResourceW
#else
#define D3DXCreateTextureFromResource D3DXCreateTextureFromResourceA
#endif


HRESULT WINAPI
    D3DXCreateTextureFromResourceExA(
        LPDIRECT3DDEVICE8       pDevice,
        HMODULE                 hSrcModule,
        LPCSTR                  pSrcResource,
        UINT                    Width,
        UINT                    Height,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        DWORD                   Filter,
        DWORD                   MipFilter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*           pPalette,
        LPDIRECT3DTEXTURE8*     ppTexture);

HRESULT WINAPI
    D3DXCreateTextureFromResourceExW(
        LPDIRECT3DDEVICE8       pDevice,
        HMODULE                 hSrcModule,
        LPCWSTR                 pSrcResource,
        UINT                    Width,
        UINT                    Height,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        DWORD                   Filter,
        DWORD                   MipFilter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*           pPalette,
        LPDIRECT3DTEXTURE8*     ppTexture);

#ifdef UNICODE
#define D3DXCreateTextureFromResourceEx D3DXCreateTextureFromResourceExW
#else
#define D3DXCreateTextureFromResourceEx D3DXCreateTextureFromResourceExA
#endif


HRESULT WINAPI
    D3DXCreateTextureFromFileInMemory(
        LPDIRECT3DDEVICE8       pDevice,
        LPCVOID                 pSrcData,
        UINT                    SrcDataSize,
        LPDIRECT3DTEXTURE8*     ppTexture);

HRESULT WINAPI
    D3DXCreateTextureFromFileInMemoryEx(
        LPDIRECT3DDEVICE8       pDevice,
        LPCVOID                 pSrcData,
        UINT                    SrcDataSize,
        UINT                    Width,
        UINT                    Height,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        DWORD                   Filter,
        DWORD                   MipFilter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*           pPalette,
        LPDIRECT3DTEXTURE8*     ppTexture);


HRESULT WINAPI
    D3DXCreateCubeTextureFromFileA(
        LPDIRECT3DDEVICE8       pDevice,
        LPCSTR                  pSrcFile,
        LPDIRECT3DCUBETEXTURE8* ppCubeTexture);

HRESULT WINAPI
    D3DXCreateCubeTextureFromFileW(
        LPDIRECT3DDEVICE8       pDevice,
        LPCWSTR                 pSrcFile,
        LPDIRECT3DCUBETEXTURE8* ppCubeTexture);

#ifdef UNICODE
#define D3DXCreateCubeTextureFromFile D3DXCreateCubeTextureFromFileW
#else
#define D3DXCreateCubeTextureFromFile D3DXCreateCubeTextureFromFileA
#endif

HRESULT WINAPI
    D3DXCreateCubeTextureFromFileExA(
        LPDIRECT3DDEVICE8       pDevice,
        LPCSTR                  pSrcFile,
        UINT                    Size,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        DWORD                   Filter,
        DWORD                   MipFilter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*           pPalette,
        LPDIRECT3DCUBETEXTURE8* ppCubeTexture);

HRESULT WINAPI
    D3DXCreateCubeTextureFromFileExW(
        LPDIRECT3DDEVICE8       pDevice,
        LPCWSTR                 pSrcFile,
        UINT                    Size,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        DWORD                   Filter,
        DWORD                   MipFilter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*           pPalette,
        LPDIRECT3DCUBETEXTURE8* ppCubeTexture);

#ifdef UNICODE
#define D3DXCreateCubeTextureFromFileEx D3DXCreateCubeTextureFromFileExW
#else
#define D3DXCreateCubeTextureFromFileEx D3DXCreateCubeTextureFromFileExA
#endif


HRESULT WINAPI
    D3DXCreateCubeTextureFromResourceA(
        LPDIRECT3DDEVICE8       pDevice,
        HMODULE                 hSrcModule,
        LPCSTR                  pSrcResource,
        LPDIRECT3DCUBETEXTURE8* ppCubeTexture);

HRESULT WINAPI
    D3DXCreateCubeTextureFromResourceW(
        LPDIRECT3DDEVICE8       pDevice,
        HMODULE                 hSrcModule,
        LPCWSTR                 pSrcResource,
        LPDIRECT3DCUBETEXTURE8* ppCubeTexture);

#ifdef UNICODE
#define D3DXCreateCubeTextureFromResource D3DXCreateCubeTextureFromResourceW
#else
#define D3DXCreateCubeTextureFromResource D3DXCreateCubeTextureFromResourceA
#endif


HRESULT WINAPI
    D3DXCreateCubeTextureFromResourceExA(
        LPDIRECT3DDEVICE8       pDevice,
        HMODULE                 hSrcModule,
        LPCSTR                  pSrcResource,
        UINT                    Size,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        DWORD                   Filter,
        DWORD                   MipFilter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*           pPalette,
        LPDIRECT3DCUBETEXTURE8* ppCubeTexture);

HRESULT WINAPI
    D3DXCreateCubeTextureFromResourceExW(
        LPDIRECT3DDEVICE8       pDevice,
        HMODULE                 hSrcModule,
        LPCWSTR                 pSrcResource,
        UINT                    Size,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        DWORD                   Filter,
        DWORD                   MipFilter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*           pPalette,
        LPDIRECT3DCUBETEXTURE8* ppCubeTexture);

#ifdef UNICODE
#define D3DXCreateCubeTextureFromResourceEx D3DXCreateCubeTextureFromResourceExW
#else
#define D3DXCreateCubeTextureFromResourceEx D3DXCreateCubeTextureFromResourceExA
#endif


HRESULT WINAPI
    D3DXCreateCubeTextureFromFileInMemory(
        LPDIRECT3DDEVICE8       pDevice,
        LPCVOID                 pSrcData,
        UINT                    SrcDataSize,
        LPDIRECT3DCUBETEXTURE8* ppCubeTexture);

HRESULT WINAPI
    D3DXCreateCubeTextureFromFileInMemoryEx(
        LPDIRECT3DDEVICE8       pDevice,
        LPCVOID                 pSrcData,
        UINT                    SrcDataSize,
        UINT                    Size,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        DWORD                   Filter,
        DWORD                   MipFilter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*           pPalette,
        LPDIRECT3DCUBETEXTURE8* ppCubeTexture);


HRESULT WINAPI
    D3DXCreateVolumeTextureFromFileA(
        LPDIRECT3DDEVICE8       pDevice,
        LPCSTR                  pSrcFile,
        LPDIRECT3DVOLUMETEXTURE8* ppVolumeTexture);

HRESULT WINAPI
    D3DXCreateVolumeTextureFromFileW(
        LPDIRECT3DDEVICE8       pDevice,
        LPCWSTR                 pSrcFile,
        LPDIRECT3DVOLUMETEXTURE8* ppVolumeTexture);

#ifdef UNICODE
#define D3DXCreateVolumeTextureFromFile D3DXCreateVolumeTextureFromFileW
#else
#define D3DXCreateVolumeTextureFromFile D3DXCreateVolumeTextureFromFileA
#endif

HRESULT WINAPI
    D3DXCreateVolumeTextureFromFileExA(
        LPDIRECT3DDEVICE8       pDevice,
        LPCSTR                  pSrcFile,
        UINT                    Width,
        UINT                    Height,
        UINT                    Depth,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        DWORD                   Filter,
        DWORD                   MipFilter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*           pPalette,
        LPDIRECT3DVOLUMETEXTURE8* ppVolumeTexture);

HRESULT WINAPI
    D3DXCreateVolumeTextureFromFileExW(
        LPDIRECT3DDEVICE8       pDevice,
        LPCWSTR                 pSrcFile,
        UINT                    Width,
        UINT                    Height,
        UINT                    Depth,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        DWORD                   Filter,
        DWORD                   MipFilter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*           pPalette,
        LPDIRECT3DVOLUMETEXTURE8* ppVolumeTexture);

#ifdef UNICODE
#define D3DXCreateVolumeTextureFromFileEx D3DXCreateVolumeTextureFromFileExW
#else
#define D3DXCreateVolumeTextureFromFileEx D3DXCreateVolumeTextureFromFileExA
#endif


HRESULT WINAPI
    D3DXCreateVolumeTextureFromResourceA(
        LPDIRECT3DDEVICE8       pDevice,
        HMODULE                 hSrcModule,
        LPCSTR                  pSrcResource,
        LPDIRECT3DVOLUMETEXTURE8* ppVolumeTexture);

HRESULT WINAPI
    D3DXCreateVolumeTextureFromResourceW(
        LPDIRECT3DDEVICE8       pDevice,
        HMODULE                 hSrcModule,
        LPCWSTR                 pSrcResource,
        LPDIRECT3DVOLUMETEXTURE8* ppVolumeTexture);

#ifdef UNICODE
#define D3DXCreateVolumeTextureFromResource D3DXCreateVolumeTextureFromResourceW
#else
#define D3DXCreateVolumeTextureFromResource D3DXCreateVolumeTextureFromResourceA
#endif


HRESULT WINAPI
    D3DXCreateVolumeTextureFromResourceExA(
        LPDIRECT3DDEVICE8       pDevice,
        HMODULE                 hSrcModule,
        LPCSTR                  pSrcResource,
        UINT                    Width,
        UINT                    Height,
        UINT                    Depth,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        DWORD                   Filter,
        DWORD                   MipFilter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*           pPalette,
        LPDIRECT3DVOLUMETEXTURE8* ppVolumeTexture);

HRESULT WINAPI
    D3DXCreateVolumeTextureFromResourceExW(
        LPDIRECT3DDEVICE8       pDevice,
        HMODULE                 hSrcModule,
        LPCWSTR                 pSrcResource,
        UINT                    Width,
        UINT                    Height,
        UINT                    Depth,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        DWORD                   Filter,
        DWORD                   MipFilter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*           pPalette,
        LPDIRECT3DVOLUMETEXTURE8* ppVolumeTexture);

#ifdef UNICODE
#define D3DXCreateVolumeTextureFromResourceEx D3DXCreateVolumeTextureFromResourceExW
#else
#define D3DXCreateVolumeTextureFromResourceEx D3DXCreateVolumeTextureFromResourceExA
#endif


HRESULT WINAPI
    D3DXCreateVolumeTextureFromFileInMemory(
        LPDIRECT3DDEVICE8       pDevice,
        LPCVOID                 pSrcData,
        UINT                    SrcDataSize,
        LPDIRECT3DVOLUMETEXTURE8* ppTexture);

HRESULT WINAPI
    D3DXCreateVolumeTextureFromFileInMemoryEx(
        LPDIRECT3DDEVICE8       pDevice,
        LPCVOID                 pSrcData,
        UINT                    SrcDataSize,
        UINT                    Width,
        UINT                    Height,
        UINT                    Depth,
        UINT                    MipLevels,
        DWORD                   Usage,
        D3DFORMAT               Format,
        D3DPOOL                 Pool,
        DWORD                   Filter,
        DWORD                   MipFilter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo,
        PALETTEENTRY*           pPalette,
        LPDIRECT3DVOLUMETEXTURE8* ppTexture);

//----------------------------------------------------------------------------
// D3DXGetImageInfoFromFile, D3DXGetImageInfoFromResource, D3DXGetImageInfoFromFileInMemory
// --------------------------------------------------------------------------------
// Get information about an image file.
//
// Parameters:
//  pSrcFile
//      File name.
//  hSrcModule
//      Module handle. if NULL, current module will be used.
//  pSrcResource
//      Resource name in module.
//  pSrcData
//      Pointer to file in memory.
//  SrcDataSize
//      Size in bytes of file in memory.
//  pSrcInfo
//      Returns information about the source image.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXGetImageInfoFromFileA(
        LPCSTR                  pSrcFile,
        D3DXIMAGE_INFO*         pSrcInfo);

HRESULT WINAPI
    D3DXGetImageInfoFromFileW(
        LPCWSTR                 pSrcFile,
        D3DXIMAGE_INFO*         pSrcInfo);

#ifdef UNICODE
#define D3DXGetImageInfoFromFile D3DXGetImageInfoFromFileW
#else
#define D3DXGetImageInfoFromFile D3DXGetImageInfoFromFileA
#endif


HRESULT WINAPI
    D3DXGetImageInfoFromResourceA(
        HMODULE                 hSrcModule,
        LPCSTR                  pSrcResource,
        D3DXIMAGE_INFO*         pSrcInfo);

HRESULT WINAPI
    D3DXGetImageInfoFromResourceW(
        HMODULE                 hSrcModule,
        LPCWSTR                 pSrcResource,
        D3DXIMAGE_INFO*         pSrcInfo);

#ifdef UNICODE
#define D3DXGetImageInfoFromResource D3DXGetImageInfoFromResourceW
#else
#define D3DXGetImageInfoFromResource D3DXGetImageInfoFromResourceA
#endif


HRESULT WINAPI
    D3DXGetImageInfoFromFileInMemory(
        LPCVOID                 pSrcData,
        UINT                    SrcDataSize,
        D3DXIMAGE_INFO*         pSrcInfo);



//----------------------------------------------------------------------------
// D3DXCheckTextureRequirements:
// ----------------------------
// Checks texture creation parameters.  If the device does not support the
// requested texture, this function will return the best alternative.
//
// Parameters:
//  pDevice
//      The D3D device with which the texture is to be associated.
//  pWidth, pHeight, pDepth
//      Requested size.  Returns the best alternative.
//  pNumMipLevels
//      Requested number of mip-levels.  Returns the best alternative.
//  Usage
//      D3DUSAGE flags.
//  pFormat
//      Requested format.  Returns the best alternative.
//  Pool
//      D3DPOOL in which the texture should be placed.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCheckTextureRequirements(
        LPDIRECT3DDEVICE8       pDevice,
        UINT*                   pWidth,
        UINT*                   pHeight,
        UINT*                   pNumMipLevels,
        DWORD                   Usage,
        D3DFORMAT*              pFormat,
        D3DPOOL                 Pool);

HRESULT WINAPI
    D3DXCheckCubeTextureRequirements(
        LPDIRECT3DDEVICE8       pDevice,
        UINT*                   pSize,
        UINT*                   pNumMipLevels,
        DWORD                   Usage,
        D3DFORMAT*              pFormat,
        D3DPOOL                 Pool);

HRESULT WINAPI
    D3DXCheckVolumeTextureRequirements(
        LPDIRECT3DDEVICE8       pDevice,
        UINT*                   pWidth,
        UINT*                   pHeight,
        UINT*                   pDepth,
        UINT*                   pNumMipLevels,
        DWORD                   Usage,
        D3DFORMAT*              pFormat,
        D3DPOOL                 Pool);


//----------------------------------------------------------------------------
// D3DXFilterTexture:
// -----------------
// Filters a texture. This function can be used to generate mip-chains and
// do texture format conversions.
//
// Parameters
//  pBaseTexture
//      The texture to be filtered.
//  pPalette
//      The palette to use for the conversion.  May be NULL.
//  SrcLevel
//      The level of the texture to be used as the source for the filter.
//  Filter
//      D3DX_FILTER flags controlling how the image is filtered.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXFilterTexture(
        LPDIRECT3DBASETEXTURE8  pBaseTexture,
        CONST PALETTEENTRY*     pPalette,
        UINT                    SrcLevel,
        DWORD                   Filter);


//----------------------------------------------------------------------------
// D3DXLoadSurfaceFromFile, D3DXLoadSurfaceFromResource, D3DXLoadSurfaceFromFileInMemory
// --------------------------------------------------------------------------------
// Load a surface from a file or resource.
//
// Parameters:
//  pDestSurface
//      Destination surface, which will receive the image.
//  pDestPalette
//      Destination palette of 256 colors, used if pDestSurface is
//      a palettized format.
//  pDestRect
//      Destination rectangle.
//  pSrcFile
//      File name.
//  hSrcModule
//      Module handle. if NULL, current module will be used.
//  pSrcResource
//      Resource name in module.
//  pSrcData
//      Pointer to file in memory.
//  SrcDataSize
//      Size in bytes of file in memory.
//  pSrcRect
//      Source rectangle.
//  Filter
//      D3DX_FILTER flags controlling how the image is filtered.
//      Or D3DX_DEFAULT to use D3DX_FILTER_TRIANGLE.
//  ColorKey
//      Color to be replaced with D3DCOLOR_RGBA(0,0,0,0).  Or 0 to disable
//      the colorkey.  This is always a 32-bit ARGB color, independent of
//      the source image format.  Alpha is significant.
//  pSrcInfo
//      Returns information about the source image.
//
//----------------------------------------------------------------------------


HRESULT WINAPI
    D3DXLoadSurfaceFromFileA(
        LPDIRECT3DSURFACE8      pDestSurface,
        CONST PALETTEENTRY*     pDestPalette,
        CONST RECT*             pDestRect,
        LPCSTR                  pSrcFile,
        CONST RECT*             pSrcRect,
        DWORD                   Filter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo);

HRESULT WINAPI
    D3DXLoadSurfaceFromFileW(
        LPDIRECT3DSURFACE8      pDestSurface,
        CONST PALETTEENTRY*     pDestPalette,
        CONST RECT*             pDestRect,
        LPCWSTR                 pSrcFile,
        CONST RECT*             pSrcRect,
        DWORD                   Filter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo);

#ifdef UNICODE
#define D3DXLoadSurfaceFromFile D3DXLoadSurfaceFromFileW
#else
#define D3DXLoadSurfaceFromFile D3DXLoadSurfaceFromFileA
#endif


HRESULT WINAPI
    D3DXLoadSurfaceFromResourceA(
        LPDIRECT3DSURFACE8      pDestSurface,
        CONST PALETTEENTRY*     pDestPalette,
        CONST RECT*             pDestRect,
        HMODULE                 hSrcModule,
        LPCSTR                  pSrcResource,
        CONST RECT*             pSrcRect,
        DWORD                   Filter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo);

HRESULT WINAPI
    D3DXLoadSurfaceFromResourceW(
        LPDIRECT3DSURFACE8      pDestSurface,
        CONST PALETTEENTRY*     pDestPalette,
        CONST RECT*             pDestRect,
        HMODULE                 hSrcModule,
        LPCWSTR                 pSrcResource,
        CONST RECT*             pSrcRect,
        DWORD                   Filter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo);

#ifdef UNICODE
#define D3DXLoadSurfaceFromResource D3DXLoadSurfaceFromResourceW
#else
#define D3DXLoadSurfaceFromResource D3DXLoadSurfaceFromResourceA
#endif


HRESULT WINAPI
    D3DXLoadSurfaceFromFileInMemory(
        LPDIRECT3DSURFACE8      pDestSurface,
        CONST PALETTEENTRY*     pDestPalette,
        CONST RECT*             pDestRect,
        LPCVOID                 pSrcData,
        UINT                    SrcDataSize,
        CONST RECT*             pSrcRect,
        DWORD                   Filter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo);

//----------------------------------------------------------------------------
// D3DXLoadSurfaceFromSurface
// --------------------------------------------------------------------------------
// Load a surface from another surface.
//
// Parameters:
//  pDestSurface
//      Destination surface, which will receive the image.
//  pDestPalette
//      Destination palette of 256 colors, used if pDestSurface is
//      a palettized format.
//  pDestRect
//      Destination rectangle.
//  pSrcSurface
//      Source surface.
//  pSrcPalette
//      Source palette of 256 colors, used if pSrcSurface is
//      a palettized format.
//  pSrcRect
//      Source rectangle.
//  Filter
//      D3DX_FILTER flags controlling how the image is filtered.
//      Or D3DX_DEFAULT to use D3DX_FILTER_TRIANGLE.
//  ColorKey
//      Color to be replaced with D3DCOLOR_RGBA(0,0,0,0).  Or 0 to disable
//      the colorkey.  This is always a 32-bit ARGB color, independent of
//      the source image format.  Alpha is significant.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXLoadSurfaceFromSurface(
        LPDIRECT3DSURFACE8      pDestSurface,
        CONST PALETTEENTRY*     pDestPalette,
        CONST RECT*             pDestRect,
        LPDIRECT3DSURFACE8      pSrcSurface,
        CONST PALETTEENTRY*     pSrcPalette,
        CONST RECT*             pSrcRect,
        DWORD                   Filter,
        D3DCOLOR                ColorKey);


//----------------------------------------------------------------------------
// D3DXLoadVolumeFromFile, D3DXLoadVolumeFromResource, D3DXLoadVolumeFromFileInMemory
// --------------------------------------------------------------------------------
// Load a volume from a file or resource.
//
// Parameters:
//  pDestVolume
//      Destination volume, which will receive the image.
//  pDestPalette
//      Destination palette of 256 colors, used if pDestVolume is
//      a palettized format.
//  pDestBox
//      Destination box.
//  pSrcFile
//      File name.
//  hSrcModule
//      Module handle. if NULL, current module will be used.
//  pSrcResource
//      Resource name in module.
//  pSrcData
//      Pointer to file in memory.
//  SrcDataSize
//      Size in bytes of file in memory.
//  pSrcBox
//      Source box.
//  Filter
//      D3DX_FILTER flags controlling how the image is filtered.
//      Or D3DX_DEFAULT to use D3DX_FILTER_TRIANGLE.
//  ColorKey
//      Color to be replaced with D3DCOLOR_RGBA(0,0,0,0).  Or 0 to disable
//      the colorkey.  This is always a 32-bit ARGB color, independent of
//      the source image format.  Alpha is significant.
//  pSrcInfo
//      Returns information about the source image.
//
//----------------------------------------------------------------------------


HRESULT WINAPI
    D3DXLoadVolumeFromFileA(
        LPDIRECT3DVOLUME8       pDestVolume,
        CONST PALETTEENTRY*     pDestPalette,
        CONST D3DBOX*           pDestBox,
        LPCSTR                  pSrcFile,
        CONST D3DBOX*           pSrcBox,
        DWORD                   Filter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo);

HRESULT WINAPI
    D3DXLoadVolumeFromFileW(
        LPDIRECT3DVOLUME8       pDestVolume,
        CONST PALETTEENTRY*     pDestPalette,
        CONST D3DBOX*           pDestBox,
        LPCWSTR                 pSrcFile,
        CONST D3DBOX*           pSrcBox,
        DWORD                   Filter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo);

#ifdef UNICODE
#define D3DXLoadVolumeFromFile D3DXLoadVolumeFromFileW
#else
#define D3DXLoadVolumeFromFile D3DXLoadVolumeFromFileA
#endif


HRESULT WINAPI
    D3DXLoadVolumeFromResourceA(
        LPDIRECT3DVOLUME8       pDestVolume,
        CONST PALETTEENTRY*     pDestPalette,
        CONST D3DBOX*           pDestBox,
        HMODULE                 hSrcModule,
        LPCSTR                  pSrcResource,
        CONST D3DBOX*           pSrcBox,
        DWORD                   Filter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo);

HRESULT WINAPI
    D3DXLoadVolumeFromResourceW(
        LPDIRECT3DVOLUME8       pDestVolume,
        CONST PALETTEENTRY*     pDestPalette,
        CONST D3DBOX*           pDestBox,
        HMODULE                 hSrcModule,
        LPCWSTR                 pSrcResource,
        CONST D3DBOX*           pSrcBox,
        DWORD                   Filter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo);

#ifdef UNICODE
#define D3DXLoadVolumeFromResource D3DXLoadVolumeFromResourceW
#else
#define D3DXLoadVolumeFromResource D3DXLoadVolumeFromResourceA
#endif


HRESULT WINAPI
    D3DXLoadVolumeFromFileInMemory(
        LPDIRECT3DVOLUME8       pDestVolume,
        CONST PALETTEENTRY*     pDestPalette,
        CONST D3DBOX*           pDestBox,
        LPCVOID                 pSrcData,
        UINT                    SrcDataSize,
        CONST D3DBOX*           pSrcBox,
        DWORD                   Filter,
        D3DCOLOR                ColorKey,
        D3DXIMAGE_INFO*         pSrcInfo);

//----------------------------------------------------------------------------
// D3DXLoadVolumeFromVolume
// --------------------------------------------------------------------------------
// Load a volume from another volume.
//
// Parameters:
//  pDestVolume
//      Destination volume, which will receive the image.
//  pDestPalette
//      Destination palette of 256 colors, used if pDestVolume is
//      a palettized format.
//  pDestBox
//      Destination box.
//  pSrcVolume
//      Source volume.
//  pSrcPalette
//      Source palette of 256 colors, used if pSrcVolume is
//      a palettized format.
//  pSrcBox
//      Source box.
//  Filter
//      D3DX_FILTER flags controlling how the image is filtered.
//      Or D3DX_DEFAULT to use D3DX_FILTER_TRIANGLE.
//  ColorKey
//      Color to be replaced with D3DCOLOR_RGBA(0,0,0,0).  Or 0 to disable
//      the colorkey.  This is always a 32-bit ARGB color, independent of
//      the source image format.  Alpha is significant.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXLoadVolumeFromVolume(
        LPDIRECT3DVOLUME8       pDestVolume,
        CONST PALETTEENTRY*     pDestPalette,
        CONST D3DBOX*           pDestBox,
        LPDIRECT3DVOLUME8       pSrcVolume,
        CONST PALETTEENTRY*     pSrcPalette,
        CONST D3DBOX*           pSrcBox,
        DWORD                   Filter,
        D3DCOLOR                ColorKey);



//----------------------------------------------------------------------------
// D3DXSaveSurfaceToFile, D3DXSaveVolumeToFile
// D3DXSaveTextureToFile, D3DXSaveCubeTextureToFile, D3DXSaveVolumeTextureToFile
// --------------------------------------------------------------------------------
// Save a texture, surface, or volume to a file.
//
// Parameters:
//  pDestFile
//      File name of the destination file
//  DestFormat
//      D3DXIMAGE_FILEFORMAT which describes the format of the destination file.
//  pSrcSurface
//      Source surface, containing the image to be saved
//  pSrcPalette
//      Source palette of 256 colors, used if pSrcSurface is a palettized format.
//  pSrcRect
//      Source rectangle.
//  pSrcVolume
//      Source volume, containing the image to be saved
//  pSrcBox
//      Source box.
//  pSrcTexture
//      Source texture, containing the image to be saved
//
//----------------------------------------------------------------------------

typedef enum _D3DXIMAGE_FILEFORMAT
{
    D3DXIFF_BMP         = 0,
    D3DXIFF_JPG         = 1,
    D3DXIFF_TGA         = 2,
    D3DXIFF_PNG         = 3,
    D3DXIFF_DDS         = 4,
    D3DXIFF_PPM         = 5,
    D3DXIFF_DIB         = 6,
    D3DXIFF_HDR         = 7,       // high dynamic range formats
    D3DXIFF_PFM         = 8,       //
    D3DXIFF_FORCE_DWORD = 0x7fffffff

} D3DXIMAGE_FILEFORMAT;


HRESULT WINAPI
    D3DXSaveSurfaceToFileA(
        LPCSTR                  pDestFile,
        D3DXIMAGE_FILEFORMAT    DestFormat,
        LPDIRECT3DSURFACE8      pSrcSurface,
        CONST PALETTEENTRY*     pSrcPalette,
        CONST RECT*             pSrcRect);

HRESULT WINAPI
    D3DXSaveSurfaceToFileW(
        LPCWSTR                 pDestFile,
        D3DXIMAGE_FILEFORMAT    DestFormat,
        LPDIRECT3DSURFACE8      pSrcSurface,
        CONST PALETTEENTRY*     pSrcPalette,
        CONST RECT*             pSrcRect);

#ifdef UNICODE
#define D3DXSaveSurfaceToFile D3DXSaveSurfaceToFileW
#else
#define D3DXSaveSurfaceToFile D3DXSaveSurfaceToFileA
#endif


HRESULT WINAPI
    D3DXSaveVolumeToFileA(
        LPCSTR                  pDestFile,
        D3DXIMAGE_FILEFORMAT    DestFormat,
        LPDIRECT3DVOLUME8       pSrcVolume,
        CONST PALETTEENTRY*     pSrcPalette,
        CONST D3DBOX*           pSrcBox);

HRESULT WINAPI
    D3DXSaveVolumeToFileW(
        LPCWSTR                 pDestFile,
        D3DXIMAGE_FILEFORMAT    DestFormat,
        LPDIRECT3DVOLUME8       pSrcVolume,
        CONST PALETTEENTRY*     pSrcPalette,
        CONST D3DBOX*           pSrcBox);

#ifdef UNICODE
#define D3DXSaveVolumeToFile D3DXSaveVolumeToFileW
#else
#define D3DXSaveVolumeToFile D3DXSaveVolumeToFileA
#endif


HRESULT WINAPI
    D3DXSaveTextureToFileA(
        LPCSTR                  pDestFile,
        D3DXIMAGE_FILEFORMAT    DestFormat,
        LPDIRECT3DBASETEXTURE8  pSrcTexture,
        CONST PALETTEENTRY*     pSrcPalette);

HRESULT WINAPI
    D3DXSaveTextureToFileW(
        LPCWSTR                 pDestFile,
        D3DXIMAGE_FILEFORMAT    DestFormat,
        LPDIRECT3DBASETEXTURE8  pSrcTexture,
        CONST PALETTEENTRY*     pSrcPalette);

#ifdef UNICODE
#define D3DXSaveTextureToFile D3DXSaveTextureToFileW
#else
#define D3DXSaveTextureToFile D3DXSaveTextureToFileA
#endif


//----------------------------------------------------------------------------
// D3DXFillTexture:
// ---------------
//
// Fills each texel of each mip level of a texture with a color, as
// specified by a function of the texel's coordinates.
//
// Parameters:
//  pTexture
//      The texture to be filled.
//  pFunction
//      The function used to compute the color.
//  pData
//      Data to be passed to the function.
//
//----------------------------------------------------------------------------

typedef void (WINAPI *LPD3DXFILL2D)(D3DXVECTOR4* pOut, CONST D3DXVECTOR2* pTexCoord,
    CONST D3DXVECTOR2* pTexelSize, LPVOID pData);

typedef void (WINAPI *LPD3DXFILL3D)(D3DXVECTOR4* pOut, CONST D3DXVECTOR3* pTexCoord,
    CONST D3DXVECTOR3* pTexelSize, LPVOID pData);

HRESULT WINAPI
    D3DXFillTexture(
        LPDIRECT3DTEXTURE8      pTexture,
        LPD3DXFILL2D            pFunction,
        LPVOID                  pData);

HRESULT WINAPI
    D3DXFillCubeTexture(
        LPDIRECT3DCUBETEXTURE8  pCubeTexture,
        LPD3DXFILL3D            pFunction,
        LPVOID                  pData);

HRESULT WINAPI
    D3DXFillVolumeTexture(
        LPDIRECT3DVOLUMETEXTURE8 pVolumeTexture,
        LPD3DXFILL3D            pFunction,
        LPVOID                  pData);


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__D3DX8CORE_H__