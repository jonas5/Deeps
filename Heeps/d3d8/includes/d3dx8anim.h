/*==========================================================================;
 *
 *  Copyright (C) 1994-2001 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       d3dx8anim.h
 *  Content:    D3DX animation types and functions
 *
 ***************************************************************************/

#ifndef __D3DX8ANIM_H__
#define __D3DX8ANIM_H__

#include "d3dx8mesh.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

//----------------------------------------------------------------------------
// D3DXFrame:
// ----------
// This structure is used to represent a frame in a hierarchy.
//
//  Name
//      The name of the frame.
//  TransformationMatrix
//      The transformation matrix of the frame.
//  pMeshContainer
//      A pointer to a mesh container, if the frame has a mesh.
//  pFrameSibling
//      A pointer to the next frame in the hierarchy.
//  pFrameFirstChild
//      A pointer to the first child frame in the hierarchy.
//----------------------------------------------------------------------------

typedef struct _D3DXFRAME
{
    LPSTR                   Name;
    D3DXMATRIX              TransformationMatrix;
    LPD3DXMESHCONTAINER     pMeshContainer;
    struct _D3DXFRAME*      pFrameSibling;
    struct _D3DXFRAME*      pFrameFirstChild;

} D3DXFRAME, *LPD3DXFRAME;


//----------------------------------------------------------------------------
// D3DXMESHCONTAINER:
// ------------------
// This structure is used to hold information about a mesh in a frame.
//
//  Name
//      The name of the mesh.
//  MeshData
//      The mesh data for the mesh.
//  pMaterials
//      An array of materials for the mesh.
//  pEffects
//      An array of effects for the mesh.
//  NumMaterials
//      The number of materials in the pMaterials array.
//  pAdjacency
//      The adjacency data for the mesh.
//  pSkinInfo
//      A pointer to a skin info object, if the mesh is skinned.
//  pNextMeshContainer
//      A pointer to the next mesh container in the frame.
//----------------------------------------------------------------------------

typedef struct _D3DXMESHCONTAINER
{
    LPSTR                 Name;
    D3DXMESHDATA          MeshData;
    LPD3DXMATERIAL        pMaterials;
    LPD3DXEFFECTINSTANCE  pEffects;
    DWORD                 NumMaterials;
    DWORD*                pAdjacency;
    LPD3DXSKININFO        pSkinInfo;
    struct _D3DXMESHCONTAINER* pNextMeshContainer;

} D3DXMESHCONTAINER, *LPD3DXMESHCONTAINER;


//----------------------------------------------------------------------------
// ID3DXAllocateHierarchy:
// -----------------------
// This interface is used as a callback for allocating and freeing frames
// and mesh containers.
//----------------------------------------------------------------------------

typedef interface ID3DXAllocateHierarchy ID3DXAllocateHierarchy;
typedef ID3DXAllocateHierarchy *LPD3DXALLOCATEHIERARCHY;

#undef INTERFACE
#define INTERFACE ID3DXAllocateHierarchy

DECLARE_INTERFACE(ID3DXAllocateHierarchy)
{
    STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame) PURE;
    STDMETHOD(CreateMeshContainer)(THIS_
        LPCSTR Name,
        CONST D3DXMESHDATA *pMeshData,
        CONST D3DXMATERIAL *pMaterials,
        CONST D3DXEFFECTINSTANCE *pEffectInstances,
        DWORD NumMaterials,
        CONST DWORD *pAdjacency,
        LPD3DXSKININFO pSkinInfo,
        LPD3DXMESHCONTAINER *ppNewMeshContainer) PURE;
    STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree) PURE;
    STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree) PURE;
};


//----------------------------------------------------------------------------
// D3DXLoadMeshHierarchyFromX:
// ---------------------------
// Loads a mesh hierarchy from a .x file.
//
// Parameters:
//  pFilename
//      The name of the .x file to load.
//  MeshOptions
//      A combination of D3DXMESH flags.
//  pDevice
//      The D3D device with which the mesh is to be associated.
//  pAlloc
//      An allocation interface for creating frames and mesh containers.
//  pUserDataLoader
//      An interface for loading user data.
//  ppFrameHierarchy
//      Returns a pointer to the loaded frame hierarchy.
//  ppAnimController
//      Returns a pointer to the loaded animation controller.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXLoadMeshHierarchyFromXA(
        LPCSTR                          pFilename,
        DWORD                           MeshOptions,
        LPDIRECT3DDEVICE8               pDevice,
        LPD3DXALLOCATEHIERARCHY         pAlloc,
        LPD3DXLOADUSERDATA              pUserDataLoader,
        LPD3DXFRAME*                    ppFrameHierarchy,
        LPD3DXANIMATIONCONTROLLER*      ppAnimController);

HRESULT WINAPI
    D3DXLoadMeshHierarchyFromXW(
        LPCWSTR                         pFilename,
        DWORD                           MeshOptions,
        LPDIRECT3DDEVICE8               pDevice,
        LPD3DXALLOCATEHIERARCHY         pAlloc,
        LPD3DXLOADUSERDATA              pUserDataLoader,
        LPD3DXFRAME*                    ppFrameHierarchy,
        LPD3DXANIMATIONCONTROLLER*      ppAnimController);

#ifdef UNICODE
#define D3DXLoadMeshHierarchyFromX D3DXLoadMeshHierarchyFromXW
#else
#define D3DXLoadMeshHierarchyFromX D3DXLoadMeshHierarchyFromXA
#endif


//----------------------------------------------------------------------------
// D3DXEFFECTINSTANCE:
// -------------------
// This structure is used to hold information about an effect instance.
//
//  pEffectFilename
//      The name of the effect file.
//  NumDefaults
//      The number of defaults in the pDefaults array.
//  pDefaults
//      An array of default values for the effect.
//----------------------------------------------------------------------------

typedef struct _D3DXEFFECTINSTANCE
{
    LPSTR               pEffectFilename;
    DWORD               NumDefaults;
    LPD3DXEFFECTDEFAULT pDefaults;

} D3DXEFFECTINSTANCE, *LPD3DXEFFECTINSTANCE;


//----------------------------------------------------------------------------
// D3DXEFFECTDEFAULT:
// ------------------
// This structure is used to hold information about an effect default.
//
//  pParamName
//      The name of the parameter.
//  Type
//      The type of the parameter.
//  NumBytes
//      The number of bytes in the parameter.
//  pValue
//      A pointer to the parameter data.
//----------------------------------------------------------------------------

typedef struct _D3DXEFFECTDEFAULT
{
    LPSTR               pParamName;
    D3DXPARAMETER_TYPE  Type;
    DWORD               NumBytes;
    LPVOID              pValue;

} D3DXEFFECTDEFAULT, *LPD3DXEFFECTDEFAULT;


//----------------------------------------------------------------------------
// ID3DXLoadUserData:
// ------------------
// This interface is used as a callback for loading user data.
//----------------------------------------------------------------------------

typedef interface ID3DXLoadUserData ID3DXLoadUserData;
typedef ID3DXLoadUserData *LPD3DXLOADUSERDATA;

#undef INTERFACE
#define INTERFACE ID3DXLoadUserData

DECLARE_INTERFACE(ID3DXLoadUserData)
{
    STDMETHOD(LoadUserData)(THIS_ LPDIRECTXFILEDATA pXof, LPD3DXBUFFER *ppData) PURE;
};


//----------------------------------------------------------------------------
// D3DXKEY_VECTOR3:
// ----------------
// This structure is used to hold a vector key for animation.
//
//  Time
//      The time of the key.
//  Value
//      The value of the key.
//----------------------------------------------------------------------------

typedef struct _D3DXKEY_VECTOR3
{
    FLOAT       Time;
    D3DXVECTOR3 Value;
} D3DXKEY_VECTOR3, *LPD3DXKEY_VECTOR3;


//----------------------------------------------------------------------------
// D3DXKEY_QUATERNION:
// -------------------
// This structure is used to hold a quaternion key for animation.
//
//  Time
//      The time of the key.
//  Value
//      The value of the key.
//----------------------------------------------------------------------------

typedef struct _D3DXKEY_QUATERNION
{
    FLOAT          Time;
    D3DXQUATERNION Value;
} D3DXKEY_QUATERNION, *LPD3DXKEY_QUATERNION;


//----------------------------------------------------------------------------
// D3DXKEY_MATRIX:
// ----------------
// This structure is used to hold a matrix key for animation.
//
//  Time
//      The time of the key.
//  Value
//      The value of the key.
//----------------------------------------------------------------------------

typedef struct _D3DXKEY_MATRIX
{
    FLOAT       Time;
    D3DXMATRIX  Value;
} D3DXKEY_MATRIX, *LPD3DXKEY_MATRIX;


//----------------------------------------------------------------------------
// ID3DXAnimationSet:
// ------------------
// This interface is used to hold an animation set.
//----------------------------------------------------------------------------

typedef interface ID3DXAnimationSet ID3DXAnimationSet;
typedef ID3DXAnimationSet *LPD3DXANIMATIONSET;

#undef INTERFACE
#define INTERFACE ID3DXAnimationSet

DECLARE_INTERFACE_(ID3DXAnimationSet, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // Name
    STDMETHOD_(LPCSTR, GetName)(THIS) PURE;

    // Period
    STDMETHOD_(DOUBLE, GetPeriod)(THIS) PURE;
    STDMETHOD_(DOUBLE, GetPeriodicPosition)(THIS_ DOUBLE Position) PURE;

    // Animation names
    STDMETHOD_(UINT, GetNumAnimations)(THIS) PURE;
    STDMETHOD(GetAnimationName)(THIS_ UINT Index, LPCSTR *ppName) PURE;
    STDMETHOD(GetAnimationIndex)(THIS_ LPCSTR pName, LPUINT pIndex) PURE;

    // Animation data
    STDMETHOD(GetAnimation)(THIS_ UINT Index,
        D3DXPLAYBACK_TYPE *pPlayback,
        UINT *pAnimation,
        UINT *pNumKeys,
        D3DXKEY_VECTOR3 **ppTranslationKeys,
        D3DXKEY_VECTOR3 **ppScaleKeys,
        D3DXKEY_QUATERNION **ppRotationKeys) PURE;

    // SRT
    STDMETHOD(GetSRT)(THIS_
        DOUBLE PeriodicPosition,
        UINT Animation,
        D3DXVECTOR3 *pScale,
        D3DXQUATERNION *pRotation,
        D3DXVECTOR3 *pTranslation) PURE;
};


//----------------------------------------------------------------------------
// ID3DXAnimationController:
// -------------------------
// This interface is used to control animation.
//----------------------------------------------------------------------------

typedef interface ID3DXAnimationController ID3DXAnimationController;
typedef ID3DXAnimationController *LPD3DXANIMATIONCONTROLLER;

#undef INTERFACE
#define INTERFACE ID3DXAnimationController

DECLARE_INTERFACE_(ID3DXAnimationController, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // Time
    STDMETHOD(AdvanceTime)(THIS_ DOUBLE TimeDelta, LPD3DXANIMATIONCALLBACKHANDLER pCallbackHandler) PURE;
    STDMETHOD(ResetTime)(THIS) PURE;
    STDMETHOD_(DOUBLE, GetTime)(THIS) PURE;

    // AnimationSets
    STDMETHOD_(UINT, GetNumAnimationSets)(THIS) PURE;
    STDMETHOD(GetAnimationSet)(THIS_ UINT Index, LPD3DXANIMATIONSET *ppAnimationSet) PURE;
    STDMETHOD(GetAnimationSetByName)(THIS_ LPCSTR szName, LPD3DXANIMATIONSET *ppAnimationSet) PURE;
    STDMETHOD(RegisterAnimationSet)(THIS_ LPD3DXANIMATIONSET pAnimSet) PURE;
    STDMETHOD(UnregisterAnimationSet)(THIS_ LPD3DXANIMATIONSET pAnimSet) PURE;

    // Tracks
    STDMETHOD_(UINT, GetNumTracks)(THIS) PURE;
    STDMETHOD(SetTrackAnimationSet)(THIS_ UINT Track, LPD3DXANIMATIONSET pAnimSet) PURE;
    STDMETHOD(GetTrackAnimationSet)(THIS_ UINT Track, LPD3DXANIMATIONSET *ppAnimSet) PURE;
    STDMETHOD(SetTrackPosition)(THIS_ UINT Track, DOUBLE Position) PURE;
    STDMETHOD(SetTrackPriority)(THIS_ UINT Track, D3DXPRIORITY Priority) PURE;
    STDMETHOD(SetTrackSpeed)(THIS_ UINT Track, FLOAT Speed) PURE;
    STDMETHOD(SetTrackWeight)(THIS_ UINT Track, FLOAT Weight) PURE;
    STDMETHOD(SetTrackEnable)(THIS_ UINT Track, BOOL Enable) PURE;

    STDMETHOD_(DOUBLE, GetTrackPosition)(THIS_ UINT Track) PURE;
    STDMETHOD_(D3DXPRIORITY, GetTrackPriority)(THIS_ UINT Track) PURE;
    STDMETHOD_(FLOAT, GetTrackSpeed)(THIS_ UINT Track) PURE;
    STDMETHOD_(FLOAT, GetTrackWeight)(THIS_ UINT Track) PURE;
    STDMETHOD_(BOOL, GetTrackEnable)(THIS_ UINT Track) PURE;

    // Events
    STDMETHOD(KeyTrackSpeed)(THIS_ UINT Track, FLOAT NewSpeed, DOUBLE Time, DOUBLE Duration, D3DXTRANSITION_TYPE Transition) PURE;
    STDMETHOD(KeyTrackWeight)(THIS_ UINT Track, FLOAT NewWeight, DOUBLE Time, DOUBLE Duration, D3DXTRANSITION_TYPE Transition) PURE;
    STDMETHOD(KeyTrackPosition)(THIS_ UINT Track, DOUBLE NewPosition, DOUBLE Duration) PURE;
    STDMETHOD(KeyTrackEnable)(THIS_ UINT Track, BOOL NewEnable, DOUBLE Time) PURE;

    // Playback
    STDMETHOD(SetPlayback)(THIS_ D3DXPLAYBACK_TYPE Playback) PURE;
    STDMETHOD(GetPlayback)(THIS_ D3DXPLAYBACK_TYPE *pPlayback) PURE;

    // Blending
    STDMETHOD(SetBlendFactor)(THIS_ FLOAT BlendFactor) PURE;
    STDMETHOD_(FLOAT, GetBlendFactor)(THIS) PURE;
};


//----------------------------------------------------------------------------
// D3DXPLAYBACK_TYPE:
// ------------------
// This enum is used to specify the playback type of an animation set.
//----------------------------------------------------------------------------

typedef enum _D3DXPLAYBACK_TYPE
{
    D3DXPLAY_LOOP,
    D3DXPLAY_ONCE,
    D3DXPLAY_PINGPONG,
    D3DXPLAY_FORCE_DWORD = 0x7fffffff

} D3DXPLAYBACK_TYPE;


//----------------------------------------------------------------------------
// D3DXPRIORITY:
// -------------
// This enum is used to specify the priority of a track.
//----------------------------------------------------------------------------

typedef enum _D3DXPRIORITY
{
    D3DXPRIORITY_LOW,
    D3DXPRIORITY_HIGH,
    D3DXPRIORITY_FORCE_DWORD = 0x7fffffff

} D3DXPRIORITY;


//----------------------------------------------------------------------------
// D3DXTRANSITION_TYPE:
// --------------------
// This enum is used to specify the transition type of a keyframe.
//----------------------------------------------------------------------------

typedef enum _D3DXTRANSITION_TYPE
{
    D3DXTRANSITION_LINEAR,
    D3DXTRANSITION_EASEINEASEOUT,
    D3DXTRANSITION_FORCE_DWORD = 0x7fffffff

} D3DXTRANSITION_TYPE;


//----------------------------------------------------------------------------
// ID3DXAnimationCallbackHandler:
// ------------------------------
// This interface is used as a callback for handling animation events.
//----------------------------------------------------------------------------

typedef interface ID3DXAnimationCallbackHandler ID3DXAnimationCallbackHandler;
typedef ID3DXAnimationCallbackHandler *LPD3DXANIMATIONCALLBACKHANDLER;

#undef INTERFACE
#define INTERFACE ID3DXAnimationCallbackHandler

DECLARE_INTERFACE(ID3DXAnimationCallbackHandler)
{
    STDMETHOD(HandleCallback)(THIS_ UINT Track, LPVOID pCallbackData) PURE;
};


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__D3DX8ANIM_H__