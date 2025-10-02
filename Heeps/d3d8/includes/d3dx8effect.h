/*==========================================================================;
 *
 *  Copyright (C) 1994-2001 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       d3dx8effect.h
 *  Content:    D3DX effect types and functions
 *
 ***************************************************************************/

#ifndef __D3DX8EFFECT_H__
#define __D3DX8EFFECT_H__

#include "d3dx8core.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


//----------------------------------------------------------------------------
// D3DXCreateEffectFromFile:
// -------------------------
// Creates an effect from a given file.
//
// Parameters:
//  pDevice
//      The D3D device with which the effect is to be associated.
//  pSrcFile
//      The name of the effect file to load.
//  pDefines
//      An array of NULL-terminated macro definitions.
//  pInclude
//      An include handler interface.
//  dwFlags
//      See D3DXSHADER flags.
//  ppEffect
//      Returns a pointer to the created effect.
//  ppCompilationErrors
//      Returns a buffer containing any compilation errors.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateEffectFromFileA(
        LPDIRECT3DDEVICE8 pDevice,
        LPCSTR pSrcFile,
        CONST D3DXMACRO *pDefines,
        LPD3DXINCLUDE pInclude,
        DWORD dwFlags,
        LPD3DXEFFECT *ppEffect,
        LPD3DXBUFFER *ppCompilationErrors);

HRESULT WINAPI
    D3DXCreateEffectFromFileW(
        LPDIRECT3DDEVICE8 pDevice,
        LPCWSTR pSrcFile,
        CONST D3DXMACRO *pDefines,
        LPD3DXINCLUDE pInclude,
        DWORD dwFlags,
        LPD3DXEFFECT *ppEffect,
        LPD3DXBUFFER *ppCompilationErrors);

#ifdef UNICODE
#define D3DXCreateEffectFromFile D3DXCreateEffectFromFileW
#else
#define D3DXCreateEffectFromFile D3DXCreateEffectFromFileA
#endif


//----------------------------------------------------------------------------
// D3DXCreateEffectFromResource:
// -----------------------------
// Creates an effect from a resource.
//
// Parameters:
//  pDevice
//      The D3D device with which the effect is to be associated.
//  hSrcModule
//      The module from which to load the resource.
//  pSrcResource
//      The name of the resource to load.
//  pDefines
//      An array of NULL-terminated macro definitions.
//  pInclude
//      An include handler interface.
//  dwFlags
//      See D3DXSHADER flags.
//  ppEffect
//      Returns a pointer to the created effect.
//  ppCompilationErrors
//      Returns a buffer containing any compilation errors.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateEffectFromResourceA(
        LPDIRECT3DDEVICE8 pDevice,
        HMODULE hSrcModule,
        LPCSTR pSrcResource,
        CONST D3DXMACRO *pDefines,
        LPD3DXINCLUDE pInclude,
        DWORD dwFlags,
        LPD3DXEFFECT *ppEffect,
        LPD3DXBUFFER *ppCompilationErrors);

HRESULT WINAPI
    D3DXCreateEffectFromResourceW(
        LPDIRECT3DDEVICE8 pDevice,
        HMODULE hSrcModule,
        LPCWSTR pSrcResource,
        CONST D3DXMACRO *pDefines,
        LPD3DXINCLUDE pInclude,
        DWORD dwFlags,
        LPD3DXEFFECT *ppEffect,
        LPD3DXBUFFER *ppCompilationErrors);

#ifdef UNICODE
#define D3DXCreateEffectFromResource D3DXCreateEffectFromResourceW
#else
#define D3DXCreateEffectFromResource D3DXCreateEffectFromResourceA
#endif


//----------------------------------------------------------------------------
// D3DXCreateEffect:
// -----------------
// Creates an effect from a given text block.
//
// Parameters:
//  pDevice
//      The D3D device with which the effect is to be associated.
//  pSrcData
//      A pointer to the effect data.
//  SrcDataLen
//      The size of the effect data.
//  pDefines
//      An array of NULL-terminated macro definitions.
//  pInclude
//      An include handler interface.
//  dwFlags
//      See D3DXSHADER flags.
//  ppEffect
//      Returns a pointer to the created effect.
//  ppCompilationErrors
//      Returns a buffer containing any compilation errors.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateEffect(
        LPDIRECT3DDEVICE8 pDevice,
        LPCVOID pSrcData,
        UINT SrcDataLen,
        CONST D3DXMACRO *pDefines,
        LPD3DXINCLUDE pInclude,
        DWORD dwFlags,
        LPD3DXEFFECT *ppEffect,
        LPD3DXBUFFER *ppCompilationErrors);


//----------------------------------------------------------------------------
// D3DXCompileShader:
// ------------------
// Compiles a shader.
//
// Parameters:
//  pSrcData
//      A pointer to the shader data.
//  SrcDataLen
//      The size of the shader data.
//  pDefines
//      An array of NULL-terminated macro definitions.
//  pInclude
//      An include handler interface.
//  pFunctionName
//      The name of the entry-point function.
//  pProfile
//      The shader profile.
//  dwFlags
//      See D3DXSHADER flags.
//  ppShader
//      Returns a buffer containing the compiled shader.
//  ppErrorMsgs
//      Returns a buffer containing any compilation errors.
//  ppConstantTable
//      Returns a constant table for the shader.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCompileShader(
        LPCVOID pSrcData,
        UINT SrcDataLen,
        CONST D3DXMACRO *pDefines,
        LPD3DXINCLUDE pInclude,
        LPCSTR pFunctionName,
        LPCSTR pProfile,
        DWORD dwFlags,
        LPD3DXBUFFER *ppShader,
        LPD3DXBUFFER *ppErrorMsgs,
        LPD3DXCONSTANTTABLE *ppConstantTable);


//----------------------------------------------------------------------------
// D3DXCompileShaderFromFile:
// --------------------------
// Compiles a shader from a file.
//
// Parameters:
//  pSrcFile
//      The name of the shader file to load.
//  pDefines
//      An array of NULL-terminated macro definitions.
//  pInclude
//      An include handler interface.
//  pFunctionName
//      The name of the entry-point function.
//  pProfile
//      The shader profile.
//  dwFlags
//      See D3DXSHADER flags.
//  ppShader
//      Returns a buffer containing the compiled shader.
//  ppErrorMsgs
//      Returns a buffer containing any compilation errors.
//  ppConstantTable
//      Returns a constant table for the shader.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCompileShaderFromFileA(
        LPCSTR pSrcFile,
        CONST D3DXMACRO *pDefines,
        LPD3DXINCLUDE pInclude,
        LPCSTR pFunctionName,
        LPCSTR pProfile,
        DWORD dwFlags,
        LPD3DXBUFFER *ppShader,
        LPD3DXBUFFER *ppErrorMsgs,
        LPD3DXCONSTANTTABLE *ppConstantTable);

HRESULT WINAPI
    D3DXCompileShaderFromFileW(
        LPCWSTR pSrcFile,
        CONST D3DXMACRO *pDefines,
        LPD3DXINCLUDE pInclude,
        LPCSTR pFunctionName,
        LPCSTR pProfile,
        DWORD dwFlags,
        LPD3DXBUFFER *ppShader,
        LPD3DXBUFFER *ppErrorMsgs,
        LPD3DXCONSTANTTABLE *ppConstantTable);

#ifdef UNICODE
#define D3DXCompileShaderFromFile D3DXCompileShaderFromFileW
#else
#define D3DXCompileShaderFromFile D3DXCompileShaderFromFileA
#endif


//----------------------------------------------------------------------------
// D3DXCompileShaderFromResource:
// ------------------------------
// Compiles a shader from a resource.
//
// Parameters:
//  hSrcModule
//      The module from which to load the resource.
//  pSrcResource
//      The name of the resource to load.
//  pDefines
//      An array of NULL-terminated macro definitions.
//  pInclude
//      An include handler interface.
//  pFunctionName
//      The name of the entry-point function.
//  pProfile
//      The shader profile.
//  dwFlags
//      See D3DXSHADER flags.
//  ppShader
//      Returns a buffer containing the compiled shader.
//  ppErrorMsgs
//      Returns a buffer containing any compilation errors.
//  ppConstantTable
//      Returns a constant table for the shader.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCompileShaderFromResourceA(
        HMODULE hSrcModule,
        LPCSTR pSrcResource,
        CONST D3DXMACRO *pDefines,
        LPD3DXINCLUDE pInclude,
        LPCSTR pFunctionName,
        LPCSTR pProfile,
        DWORD dwFlags,
        LPD3DXBUFFER *ppShader,
        LPD3DXBUFFER *ppErrorMsgs,
        LPD3DXCONSTANTTABLE *ppConstantTable);

HRESULT WINAPI
    D3DXCompileShaderFromResourceW(
        HMODULE hSrcModule,
        LPCWSTR pSrcResource,
        CONST D3DXMACRO *pDefines,
        LPD3DXINCLUDE pInclude,
        LPCSTR pFunctionName,
        LPCSTR pProfile,
        DWORD dwFlags,
        LPD3DXBUFFER *ppShader,
        LPD3DXBUFFER *ppErrorMsgs,
        LPD3DXCONSTANTTABLE *ppConstantTable);

#ifdef UNICODE
#define D3DXCompileShaderFromResource D3DXCompileShaderFromResourceW
#else
#define D3DXCompileShaderFromResource D3DXCompileShaderFromResourceA
#endif


//----------------------------------------------------------------------------
// D3DXFindShaderComment:
// ----------------------
// Finds a specific comment in a shader.
//
// Parameters:
//  pFunction
//      A pointer to the shader function.
//  fourcc
//      The comment fourcc code.
//  ppData
//      Returns a pointer to the comment data.
//  pSizeInBytes
//      Returns the size of the comment data.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXFindShaderComment(
        CONST DWORD *pFunction,
        DWORD fourcc,
        LPCVOID *ppData,
        UINT *pSizeInBytes);


//----------------------------------------------------------------------------
// D3DXGetShaderSize:
// ------------------
// Returns the size of a shader in bytes.
//
// Parameters:
//  pFunction
//      A pointer to the shader function.
//
//----------------------------------------------------------------------------

UINT WINAPI
    D3DXGetShaderSize(
        CONST DWORD *pFunction);


//----------------------------------------------------------------------------
// D3DXGetShaderVersion:
// ---------------------
// Returns the version of a shader.
//
// Parameters:
//  pFunction
//      A pointer to the shader function.
//
//----------------------------------------------------------------------------

DWORD WINAPI
    D3DXGetShaderVersion(
        CONST DWORD *pFunction);


//----------------------------------------------------------------------------
// D3DXGetShaderConstantTable:
// ---------------------------
// Gets the constant table from a shader.
//
// Parameters:
//  pFunction
//      A pointer to the shader function.
//  ppConstantTable
//      The returned constant table.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXGetShaderConstantTable(
        CONST DWORD *pFunction,
        LPD3DXCONSTANTTABLE *ppConstantTable);


//----------------------------------------------------------------------------
// D3DXGetPixelShaderProfile, D3DXGetVertexShaderProfile:
// ------------------------------------------------------
// Returns the name of the best profile for the device.
//
// Parameters:
//  pDevice
//      The D3D device.
//
//----------------------------------------------------------------------------

LPCSTR WINAPI
    D3DXGetPixelShaderProfile(
        LPDIRECT3DDEVICE8 pDevice);

LPCSTR WINAPI
    D3DXGetVertexShaderProfile(
        LPDIRECT3DDEVICE8 pDevice);


//----------------------------------------------------------------------------
// D3DXAssembleShader:
// -------------------
// Assembles a shader.
//
// Parameters:
//  pSrcData
//      A pointer to the shader data.
//  SrcDataLen
//      The size of the shader data.
//  dwFlags
//      See D3DXSHADER flags.
//  ppShader
//      Returns a buffer containing the assembled shader.
//  ppErrorMsgs
//      Returns a buffer containing any compilation errors.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXAssembleShader(
        LPCVOID pSrcData,
        UINT SrcDataLen,
        DWORD dwFlags,
        LPD3DXBUFFER *ppShader,
        LPD3DXBUFFER *ppErrorMsgs);


//----------------------------------------------------------------------------
// D3DXAssembleShaderFromFile:
// ---------------------------
// Assembles a shader from a file.
//
// Parameters:
//  pSrcFile
//      The name of the shader file to load.
//  dwFlags
//      See D3DXSHADER flags.
//  ppShader
//      Returns a buffer containing the assembled shader.
//  ppErrorMsgs
//      Returns a buffer containing any compilation errors.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXAssembleShaderFromFileA(
        LPCSTR pSrcFile,
        DWORD dwFlags,
        LPD3DXBUFFER *ppShader,
        LPD3DXBUFFER *ppErrorMsgs);

HRESULT WINAPI
    D3DXAssembleShaderFromFileW(
        LPCWSTR pSrcFile,
        DWORD dwFlags,
        LPD3DXBUFFER *ppShader,
        LPD3DXBUFFER *ppErrorMsgs);

#ifdef UNICODE
#define D3DXAssembleShaderFromFile D3DXAssembleShaderFromFileW
#else
#define D3DXAssembleShaderFromFile D3DXAssembleShaderFromFileA
#endif


//----------------------------------------------------------------------------
// D3DXAssembleShaderFromResource:
// -------------------------------
// Assembles a shader from a resource.
//
// Parameters:
//  hSrcModule
//      The module from which to load the resource.
//  pSrcResource
//      The name of the resource to load.
//  dwFlags
//      See D3DXSHADER flags.
//  ppShader
//      Returns a buffer containing the assembled shader.
//  ppErrorMsgs
//      Returns a buffer containing any compilation errors.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXAssembleShaderFromResourceA(
        HMODULE hSrcModule,
        LPCSTR pSrcResource,
        DWORD dwFlags,
        LPD3DXBUFFER *ppShader,
        LPD3DXBUFFER *ppErrorMsgs);

HRESULT WINAPI
    D3DXAssembleShaderFromResourceW(
        HMODULE hSrcModule,
        LPCWSTR pSrcResource,
        DWORD dwFlags,
        LPD3DXBUFFER *ppShader,
        LPD3DXBUFFER *ppErrorMsgs);

#ifdef UNICODE
#define D3DXAssembleShaderFromResource D3DXAssembleShaderFromResourceW
#else
#define D3DXAssembleShaderFromResource D3DXAssembleShaderFromResourceA
#endif


//----------------------------------------------------------------------------
// D3DXDisassembleShader:
// ----------------------
// Disassembles a shader.
//
// Parameters:
//  pShader
//      A pointer to the shader function.
//  EnableColorCode
//      TRUE to enable color codes in the disassembly.
//  ppDisassembly
//      Returns a buffer containing the disassembly.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXDisassembleShader(
        CONST DWORD *pShader,
        BOOL EnableColorCode,
        LPD3DXBUFFER *ppDisassembly);


//----------------------------------------------------------------------------
// ID3DXEffect:
// ------------
// This is the main interface for the effect system.
//----------------------------------------------------------------------------

typedef interface ID3DXEffect ID3DXEffect;
typedef ID3DXEffect *LPD3DXEFFECT;

#undef INTERFACE
#define INTERFACE ID3DXEffect

DECLARE_INTERFACE_(ID3DXEffect, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // Descs
    STDMETHOD(GetDesc)(THIS_ D3DXEFFECT_DESC* pDesc) PURE;
    STDMETHOD(GetParameterDesc)(THIS_ DWORD dwIndex, D3DXPARAMETER_DESC* pDesc) PURE;
    STDMETHOD(GetTechniqueDesc)(THIS_ DWORD dwIndex, D3DXTECHNIQUE_DESC* pDesc) PURE;
    STDMETHOD(GetPassDesc)(THIS_ DWORD dwIndex, D3DXPASS_DESC* pDesc) PURE;

    // Handle operations
    STDMETHOD_(DWORD, GetParameter)(THIS_ DWORD dwIndex, DWORD dwParam) PURE;
    STDMETHOD_(DWORD, GetParameterByName)(THIS_ LPCSTR pName) PURE;
    STDMETHOD_(DWORD, GetParameterBySemantic)(THIS_ LPCSTR pSemantic) PURE;
    STDMETHOD_(DWORD, GetTechnique)(THIS_ DWORD dwIndex) PURE;
    STDMETHOD_(DWORD, GetTechniqueByName)(THIS_ LPCSTR pName) PURE;
    STDMETHOD_(DWORD, GetPass)(THIS_ DWORD dwIndex, DWORD dwPass) PURE;
    STDMETHOD_(DWORD, GetPassByName)(THIS_ DWORD dwIndex, LPCSTR pName) PURE;

    // Get/Set parameters
    STDMETHOD(GetValue)(THIS_ DWORD dwParameter, LPVOID pData, DWORD dwSizeOfData) PURE;
    STDMETHOD(SetValue)(THIS_ DWORD dwParameter, LPCVOID pData, DWORD dwSizeOfData) PURE;
    STDMETHOD(GetMatrix)(THIS_ DWORD dwParameter, D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(SetMatrix)(THIS_ DWORD dwParameter, CONST D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(GetTexture)(THIS_ DWORD dwParameter, LPDIRECT3DBASETEXTURE8* ppTexture) PURE;
    STDMETHOD(SetTexture)(THIS_ DWORD dwParameter, LPDIRECT3DBASETEXTURE8 pTexture) PURE;
    STDMETHOD(GetVertexShader)(THIS_ DWORD dwParameter, LPDWORD* pdwShader) PURE;
    STDMETHOD(SetVertexShader)(THIS_ DWORD dwParameter, DWORD dwShader) PURE;
    STDMETHOD(GetPixelShader)(THIS_ DWORD dwParameter, LPDWORD* pdwShader) PURE;
    STDMETHOD(SetPixelShader)(THIS_ DWORD dwParameter, DWORD dwShader) PURE;

    //Technique enumeration
    STDMETHOD(FindNextValidTechnique)(THIS_ DWORD dwIndex, LPDWORD pdwTechnique) PURE;
    STDMETHOD_(BOOL, IsParameterUsed)(THIS_ DWORD dwParameter, DWORD dwTechnique) PURE;

    // Using current technique
    STDMETHOD(SetTechnique)(THIS_ DWORD dwTechnique) PURE;
    STDMETHOD_(DWORD, GetCurrentTechnique)();
    STDMETHOD(Begin)(THIS_ LPDWORD pPasses, DWORD dwFlags) PURE;
    STDMETHOD(Pass)(THIS_ DWORD dwPass) PURE;
    STDMETHOD(End)(THIS) PURE;

    //Device state management
    STDMETHOD(OnLostDevice)(THIS) PURE;
    STDMETHOD(OnResetDevice)(THIS) PURE;

    //Parameter sharing
    STDMETHOD(CloneEffect)(LPDIRECT3DDEVICE8 pDevice, LPD3DXEFFECT *ppEffect) PURE;
};


//----------------------------------------------------------------------------
// D3DXEFFECT_DESC:
// ----------------
// This structure is used to hold information about an effect.
//
//  pDevice
//      The D3D device with which the effect is associated.
//  NumParameters
//      The number of parameters in the effect.
//  NumTechniques
//      The number of techniques in the effect.
//  NumFunctions
//      The number of functions in the effect.
//----------------------------------------------------------------------------

typedef struct _D3DXEFFECT_DESC
{
    LPDIRECT3DDEVICE8 pDevice;
    DWORD NumParameters;
    DWORD NumTechniques;
    DWORD NumFunctions;

} D3DXEFFECT_DESC;


//----------------------------------------------------------------------------
// D3DXPARAMETER_DESC:
// -------------------
// This structure is used to hold information about an effect parameter.
//
//  pName
//      The name of the parameter.
//  pSemantic
//      The semantic of the parameter.
//  Class
//      The class of the parameter.
//  Type
//      The type of the parameter.
//  Rows
//      The number of rows in the parameter.
//  Columns
//      The number of columns in the parameter.
//  Elements
//      The number of elements in the parameter.
//  StructMembers
//      The number of members in the parameter, if it is a struct.
//  Bytes
//      The number of bytes in the parameter.
//----------------------------------------------------------------------------

typedef struct _D3DXPARAMETER_DESC
{
    LPCSTR                  pName;
    LPCSTR                  pSemantic;
    D3DXPARAMETER_CLASS     Class;
    D3DXPARAMETER_TYPE      Type;
    UINT                    Rows;
    UINT                    Columns;
    UINT                    Elements;
    UINT                    StructMembers;
    DWORD                   Bytes;

} D3DXPARAMETER_DESC;


//----------------------------------------------------------------------------
// D3DXTECHNIQUE_DESC:
// -------------------
// This structure is used to hold information about an effect technique.
//
//  pName
//      The name of the technique.
//  NumPasses
//      The number of passes in the technique.
//----------------------------------------------------------------------------

typedef struct _D3DXTECHNIQUE_DESC
{
    LPCSTR                  pName;
    UINT                    NumPasses;

} D3DXTECHNIQUE_DESC;


//----------------------------------------------------------------------------
// D3DXPASS_DESC:
// --------------
// This structure is used to hold information about an effect pass.
//
//  pName
//      The name of the pass.
//  pVertexShaderFunction
//      A pointer to the vertex shader function.
//  pPixelShaderFunction
//      A pointer to the pixel shader function.
//----------------------------------------------------------------------------

typedef struct _D3DXPASS_DESC
{
    LPCSTR                  pName;
    DWORD*                  pVertexShaderFunction;
    DWORD*                  pPixelShaderFunction;

} D3DXPASS_DESC;


//----------------------------------------------------------------------------
// ID3DXConstantTable:
// -------------------
// This interface is used to set shader constants.
//----------------------------------------------------------------------------

typedef interface ID3DXConstantTable ID3DXConstantTable;
typedef ID3DXConstantTable *LPD3DXCONSTANTTABLE;

#undef INTERFACE
#define INTERFACE ID3DXConstantTable

DECLARE_INTERFACE_(ID3DXConstantTable, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // Descs
    STDMETHOD(GetDesc)(THIS_ D3DXCONSTANTTABLE_DESC* pDesc) PURE;
    STDMETHOD(GetConstantDesc)(THIS_ DWORD dwIndex, D3DXCONSTANT_DESC* pDesc) PURE;

    // Handle operations
    STDMETHOD_(DWORD, GetConstant)(THIS_ DWORD dwIndex, DWORD dwConstant) PURE;
    STDMETHOD_(DWORD, GetConstantByName)(THIS_ LPCSTR pName) PURE;

    // Set value functions
    STDMETHOD(SetValue)(THIS_ LPDIRECT3DDEVICE8 pDevice, DWORD hConstant, LPCVOID pData, DWORD dwSizeOfData) PURE;
    STDMETHOD(SetMatrix)(THIS_ LPDIRECT3DDEVICE8 pDevice, DWORD hConstant, CONST D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(SetMatrixTranspose)(THIS_ LPDIRECT3DDEVICE8 pDevice, DWORD hConstant, CONST D3DXMATRIX* pMatrix) PURE;
    STDMETHOD(SetVector)(THIS_ LPDIRECT3DDEVICE8 pDevice, DWORD hConstant, CONST D3DXVECTOR4* pVector) PURE;
    STDMETHOD(SetFloat)(THIS_ LPDIRECT3DDEVICE8 pDevice, DWORD hConstant, FLOAT f) PURE;
    STDMETHOD(SetInt)(THIS_ LPDIRECT3DDEVICE8 pDevice, DWORD hConstant, INT n) PURE;
    STDMETHOD(SetBool)(THIS_ LPDIRECT3DDEVICE8 pDevice, DWORD hConstant, BOOL b) PURE;
    STDMETHOD(SetMatrixArray)(THIS_ LPDIRECT3DDEVICE8 pDevice, DWORD hConstant, CONST D3DXMATRIX* pMatrix, DWORD dwCount) PURE;
    STDMETHOD(SetMatrixTransposeArray)(THIS_ LPDIRECT3DDEVICE8 pDevice, DWORD hConstant, CONST D3DXMATRIX* pMatrix, DWORD dwCount) PURE;
    STDMETHOD(SetVectorArray)(THIS_ LPDIRECT3DDEVICE8 pDevice, DWORD hConstant, CONST D3DXVECTOR4* pVector, DWORD dwCount) PURE;
    STDMETHOD(SetFloatArray)(THIS_ LPDIRECT3DDEVICE8 pDevice, DWORD hConstant, CONST FLOAT* pf, DWORD dwCount) PURE;
    STDMETHOD(SetIntArray)(THIS_ LPDIRECT3DDEVICE8 pDevice, DWORD hConstant, CONST INT* pn, DWORD dwCount) PURE;
    STDMETHOD(SetBoolArray)(THIS_ LPDIRECT3DDEVICE8 pDevice, DWORD hConstant, CONST BOOL* pb, DWORD dwCount) PURE;

    // Set default values
    STDMETHOD(SetDefaults)(THIS_ LPDIRECT3DDEVICE8 pDevice) PURE;
};


//----------------------------------------------------------------------------
// D3DXCONSTANTTABLE_DESC:
// -----------------------
// This structure is used to hold information about a constant table.
//
//  pCreator
//      The name of the creator of the constant table.
//  Version
//      The version of the constant table.
//  NumConstants
//      The number of constants in the table.
//----------------------------------------------------------------------------

typedef struct _D3DXCONSTANTTABLE_DESC
{
    LPCSTR pCreator;
    DWORD Version;
    UINT NumConstants;

} D3DXCONSTANTTABLE_DESC;


//----------------------------------------------------------------------------
// D3DXCONSTANT_DESC:
// ------------------
// This structure is used to hold information about a constant.
//
//  pName
//      The name of the constant.
//  RegisterSet
//      The register set of the constant.
//  RegisterIndex
//      The register index of the constant.
//  RegisterCount
//      The number of registers used by the constant.
//  Class
//      The class of the constant.
//  Type
//      The type of the constant.
//  Rows
//      The number of rows in the constant.
//  Columns
//      The number of columns in the constant.
//  Elements
//      The number of elements in the constant.
//  StructMembers
//      The number of members in the constant, if it is a struct.
//  Bytes
//      The number of bytes in the constant.
//  DefaultValue
//      The default value of the constant.
//----------------------------------------------------------------------------

typedef struct _D3DXCONSTANT_DESC
{
    LPCSTR                  pName;
    D3DXREGISTER_SET        RegisterSet;
    UINT                    RegisterIndex;
    UINT                    RegisterCount;
    D3DXPARAMETER_CLASS     Class;
    D3DXPARAMETER_TYPE      Type;
    UINT                    Rows;
    UINT                    Columns;
    UINT                    Elements;
    UINT                    StructMembers;
    UINT                    Bytes;
    LPCVOID                 DefaultValue;

} D3DXCONSTANT_DESC;


//----------------------------------------------------------------------------
// D3DXMACRO:
// ----------
// This structure is used to define a macro.
//
//  pName
//      The name of the macro.
//  pDefinition
//      The definition of the macro.
//----------------------------------------------------------------------------

typedef struct _D3DXMACRO
{
    LPCSTR pName;
    LPCSTR pDefinition;

} D3DXMACRO;


//----------------------------------------------------------------------------
// ID3DXInclude:
// -------------
// This interface is used as a callback for handling #include directives.
//----------------------------------------------------------------------------

typedef interface ID3DXInclude ID3DXInclude;
typedef ID3DXInclude *LPD3DXINCLUDE;

#undef INTERFACE
#define INTERFACE ID3DXInclude

DECLARE_INTERFACE(ID3DXInclude)
{
    STDMETHOD(Open)(THIS_ D3DXINCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, LPUINT pBytes) PURE;
    STDMETHOD(Close)(THIS_ LPCVOID pData) PURE;
};


//----------------------------------------------------------------------------
// D3DXINCLUDE_TYPE:
// -----------------
// This enum is used to specify the type of an #include directive.
//----------------------------------------------------------------------------

typedef enum _D3DXINCLUDE_TYPE
{
    D3DXINC_LOCAL,
    D3DXINC_SYSTEM,
    D3DXINC_FORCE_DWORD = 0x7fffffff

} D3DXINCLUDE_TYPE;


//----------------------------------------------------------------------------
// D3DXPARAMETER_CLASS:
// --------------------
// This enum is used to specify the class of a parameter.
//----------------------------------------------------------------------------

typedef enum _D3DXPARAMETER_CLASS
{
    D3DXPC_SCALAR,
    D3DXPC_VECTOR,
    D3DXPC_MATRIX_ROWS,
    D3DXPC_MATRIX_COLUMNS,
    D3DXPC_OBJECT,
    D3DXPC_STRUCT,
    D3DXPC_FORCE_DWORD = 0x7fffffff

} D3DXPARAMETER_CLASS;


//----------------------------------------------------------------------------
// D3DXPARAMETER_TYPE:
// -------------------
// This enum is used to specify the type of a parameter.
//----------------------------------------------------------------------------

typedef enum _D3DXPARAMETER_TYPE
{
    D3DXPT_VOID,
    D3DXPT_BOOL,
    D3DXPT_INT,
    D3DXPT_FLOAT,
    D3DXPT_STRING,
    D3DXPT_TEXTURE,
    D3DXPT_TEXTURE1D,
    D3DXPT_TEXTURE2D,
    D3DXPT_TEXTURE3D,
    D3DXPT_TEXTURECUBE,
    D3DXPT_SAMPLER,
    D3DXPT_SAMPLER1D,
    D3DXPT_SAMPLER2D,
    D3DXPT_SAMPLER3D,
    D3DXPT_SAMPLERCUBE,
    D3DXPT_PIXELSHADER,
    D3DXPT_VERTEXSHADER,
    D3DXPT_PIXELFRAGMENT,
    D3DXPT_VERTEXFRAGMENT,
    D3DXPT_FORCE_DWORD = 0x7fffffff

} D3DXPARAMETER_TYPE;


//----------------------------------------------------------------------------
// D3DXREGISTER_SET:
// -----------------
// This enum is used to specify the register set of a constant.
//----------------------------------------------------------------------------

typedef enum _D3DXREGISTER_SET
{
    D3DXRS_BOOL,
    D3DXRS_INT4,
    D3DXRS_FLOAT4,
    D3DXRS_SAMPLER,
    D3DXRS_FORCE_DWORD = 0x7fffffff

} D3DXREGISTER_SET;


//----------------------------------------------------------------------------
// D3DXSHADER flags:
// -----------------
// These flags are used to control shader compilation.
//----------------------------------------------------------------------------

#define D3DXSHADER_DEBUG                    (1 << 0)
#define D3DXSHADER_SKIPVALIDATION           (1 << 1)
#define D3DXSHADER_SKIPOPTIMIZATION         (1 << 2)
#define D3DXSHADER_PACKMATRIX_ROWMAJOR      (1 << 3)
#define D3DXSHADER_PACKMATRIX_COLUMNMAJOR   (1 << 4)
#define D3DXSHADER_PARTIALPRECISION         (1 << 5)
#define D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT  (1 << 6)
#define D3DXSHADER_FORCE_PS_SOFTWARE_NOOPT  (1 << 7)
#define D3DXSHADER_NO_PRESHADER             (1 << 8)
#define D3DXSHADER_USE_LEGACY_D3DX9_31_DLL  (1 << 16)


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__D3DX8EFFECT_H__