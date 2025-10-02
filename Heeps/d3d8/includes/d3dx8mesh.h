/*==========================================================================;
 *
 *  Copyright (C) 1994-2001 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       d3dx8mesh.h
 *  Content:    D3DX mesh types and functions
 *
 ***************************************************************************/

#ifndef __D3DX8MESH_H__
#define __D3DX8MESH_H__

#include "d3dx8core.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


//----------------------------------------------------------------------------
// D3DXMESH:
// ---------
// The different types of meshes supported by D3DX.
//----------------------------------------------------------------------------

typedef enum _D3DXMESH {
    D3DXMESH_MANAGED = 0x001, // Mesh is in D3DPOOL_MANAGED
    D3DXMESH_WRITEONLY = 0x002, // Mesh is in D3DPOOL_DEFAULT and is write-only
    D3DXMESH_32BIT = 0x004, // Mesh has 32-bit indices
    D3DXMESH_SYSTEMMEM = 0x800, // Mesh is in D3DPOOL_SYSTEMMEM
} D3DXMESH;



//----------------------------------------------------------------------------
// D3DXMESHDATA:
// -------------
// This structure is used to hold information about a particular mesh data
// type. It is used in the extended create mesh call to specify what type
// of mesh data you would like D3DX to generate for you.
//
//  Type
//      The type of the mesh that should be created.
//
//  pMesh
//      A pointer to the mesh object that will be filled with the mesh data.
//      This can be NULL if you do not want this data type to be generated.
//
//  pAdjacency
//      A pointer to a buffer that D3DX will fill with the adjacency data.
//      This can be NULL if you do not want this data type to be generated.
//----------------------------------------------------------------------------

typedef struct _D3DXMESHDATA
{
    DWORD               Type;
    LPD3DXMESH          pMesh;
    LPD3DXBUFFER*       ppAdjacency;

} D3DXMESHDATA, *LPD3DXMESHDATA;



//----------------------------------------------------------------------------
// ID3DXBaseMesh:
// --------------
// This is the root of the mesh object hierarchy. ID3DXBaseMesh contains
// methods that are common to all mesh objects.
//----------------------------------------------------------------------------

typedef interface ID3DXBaseMesh ID3DXBaseMesh;
typedef ID3DXBaseMesh *LPD3DXBASEMESH;

#undef INTERFACE
#define INTERFACE ID3DXBaseMesh

DECLARE_INTERFACE_(ID3DXBaseMesh, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // ID3DXBaseMesh
    STDMETHOD(DrawSubset)(THIS_ DWORD AttribId) PURE;
    STDMETHOD_(DWORD, GetNumFaces)(THIS) PURE;
    STDMETHOD_(DWORD, GetNumVertices)(THIS) PURE;
    STDMETHOD_(DWORD, GetFVF)(THIS) PURE;
    STDMETHOD(GetDeclaration)(THIS_ DWORD Declaration[MAX_FVF_DECL_SIZE]) PURE;
    STDMETHOD_(DWORD, GetOptions)(THIS) PURE;
    STDMETHOD(GetDevice)(THIS_ LPDIRECT3DDEVICE8* ppDevice) PURE;
    STDMETHOD(CloneMeshFVF)(THIS_ DWORD Options, DWORD FVF,
                LPDIRECT3DDEVICE8 pD3DDevice, LPD3DXBASEMESH* ppCloneMesh) PURE;
    STDMETHOD(CloneMesh)(THIS_ DWORD Options, CONST DWORD *pDeclaration,
                LPDIRECT3DDEVICE8 pD3DDevice, LPD3DXBASEMESH* ppCloneMesh) PURE;
    STDMETHOD(GetVertexBuffer)(THIS_ LPDIRECT3DVERTEXBUFFER8* ppVB) PURE;
    STDMETHOD(GetIndexBuffer)(THIS_ LPDIRECT3DINDEXBUFFER8* ppIB) PURE;
    STDMETHOD(LockVertexBuffer)(THIS_ DWORD Flags, BYTE** ppData) PURE;
    STDMETHOD(UnlockVertexBuffer)(THIS) PURE;
    STDMETHOD(LockIndexBuffer)(THIS_ DWORD Flags, BYTE** ppData) PURE;
    STDMETHOD(UnlockIndexBuffer)(THIS) PURE;
    STDMETHOD(GetAttributeTable)(
                THIS_ D3DXATTRIBUTERANGE* pAttribTable, DWORD* pAttribTableSize) PURE;

    STDMETHOD(ConvertPointRepsToAdjacency)(THIS_ CONST DWORD* pPRep, DWORD* pAdjacency) PURE;
    STDMETHOD(ConvertAdjacencyToPointReps)(THIS_ CONST DWORD* pAdjacency, DWORD* pPRep) PURE;
    STDMETHOD(GenerateAdjacency)(THIS_ FLOAT Epsilon, DWORD* pAdjacency) PURE;
};


//----------------------------------------------------------------------------
// ID3DXMesh:
// ----------
// This object is an extension of ID3DXBaseMesh. It is used for storing
// and manipulating mesh data.
//----------------------------------------------------------------------------

typedef interface ID3DXMesh ID3DXMesh;
typedef ID3DXMesh *LPD3DXMESH;

#undef INTERFACE
#define INTERFACE ID3DXMesh

DECLARE_INTERFACE_(ID3DXMesh, ID3DXBaseMesh)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // ID3DXBaseMesh
    STDMETHOD(DrawSubset)(THIS_ DWORD AttribId) PURE;
    STDMETHOD_(DWORD, GetNumFaces)(THIS) PURE;
    STDMETHOD_(DWORD, GetNumVertices)(THIS) PURE;
    STDMETHOD_(DWORD, GetFVF)(THIS) PURE;
    STDMETHOD(GetDeclaration)(THIS_ DWORD Declaration[MAX_FVF_DECL_SIZE]) PURE;
    STDMETHOD_(DWORD, GetOptions)(THIS) PURE;
    STDMETHOD(GetDevice)(THIS_ LPDIRECT3DDEVICE8* ppDevice) PURE;
    STDMETHOD(CloneMeshFVF)(THIS_ DWORD Options, DWORD FVF,
                LPDIRECT3DDEVICE8 pD3DDevice, LPD3DXBASEMESH* ppCloneMesh) PURE;
    STDMETHOD(CloneMesh)(THIS_ DWORD Options, CONST DWORD *pDeclaration,
                LPDIRECT3DDEVICE8 pD3DDevice, LPD3DXBASEMESH* ppCloneMesh) PURE;
    STDMETHOD(GetVertexBuffer)(THIS_ LPDIRECT3DVERTEXBUFFER8* ppVB) PURE;
    STDMETHOD(GetIndexBuffer)(THIS_ LPDIRECT3DINDEXBUFFER8* ppIB) PURE;
    STDMETHOD(LockVertexBuffer)(THIS_ DWORD Flags, BYTE** ppData) PURE;
    STDMETHOD(UnlockVertexBuffer)(THIS) PURE;
    STDMETHOD(LockIndexBuffer)(THIS_ DWORD Flags, BYTE** ppData) PURE;
    STDMETHOD(UnlockIndexBuffer)(THIS) PURE;
    STDMETHOD(GetAttributeTable)(
                THIS_ D3DXATTRIBUTERANGE* pAttribTable, DWORD* pAttribTableSize) PURE;

    STDMETHOD(ConvertPointRepsToAdjacency)(THIS_ CONST DWORD* pPRep, DWORD* pAdjacency) PURE;
    STDMETHOD(ConvertAdjacencyToPointReps)(THIS_ CONST DWORD* pAdjacency, DWORD* pPRep) PURE;
    STDMETHOD(GenerateAdjacency)(THIS_ FLOAT Epsilon, DWORD* pAdjacency) PURE;

    // ID3DXMesh
    STDMETHOD(LockAttributeBuffer)(THIS_ DWORD Flags, DWORD** ppData) PURE;
    STDMETHOD(UnlockAttributeBuffer)(THIS) PURE;
    STDMETHOD(Optimize)(THIS_ DWORD Flags, CONST DWORD* pAdjacencyIn,
                DWORD* pAdjacencyOut, DWORD* pFaceRemap, LPD3DXBUFFER* ppVertexRemap,
                LPD3DXMESH* ppOptMesh) PURE;
    STDMETHOD(OptimizeInplace)(THIS_ DWORD Flags, CONST DWORD* pAdjacencyIn,
                DWORD* pAdjacencyOut, DWORD* pFaceRemap, LPD3DXBUFFER* ppVertexRemap) PURE;

    STDMETHOD(SetAttributeTable)(THIS_ CONST D3DXATTRIBUTERANGE *pAttribTable, DWORD cAttribTableSize) PURE;
};


//----------------------------------------------------------------------------
// ID3DXPMesh:
// -----------
// This object is an extension of ID3DXBaseMesh. It is used for storing
// and manipulating progressive mesh data.
//----------------------------------------------------------------------------

typedef interface ID3DXPMesh ID3DXPMesh;
typedef ID3DXPMesh *LPD3DXPMESH;

#undef INTERFACE
#define INTERFACE ID3DXPMesh

DECLARE_INTERFACE_(ID3DXPMesh, ID3DXBaseMesh)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // ID3DXBaseMesh
    STDMETHOD(DrawSubset)(THIS_ DWORD AttribId) PURE;
    STDMETHOD_(DWORD, GetNumFaces)(THIS) PURE;
    STDMETHOD_(DWORD, GetNumVertices)(THIS) PURE;
    STDMETHOD_(DWORD, GetFVF)(THIS) PURE;
    STDMETHOD(GetDeclaration)(THIS_ DWORD Declaration[MAX_FVF_DECL_SIZE]) PURE;
    STDMETHOD_(DWORD, GetOptions)(THIS) PURE;
    STDMETHOD(GetDevice)(THIS_ LPDIRECT3DDEVICE8* ppDevice) PURE;
    STDMETHOD(CloneMeshFVF)(THIS_ DWORD Options, DWORD FVF,
                LPDIRECT3DDEVICE8 pD3DDevice, LPD3DXBASEMESH* ppCloneMesh) PURE;
    STDMETHOD(CloneMesh)(THIS_ DWORD Options, CONST DWORD *pDeclaration,
                LPDIRECT3DDEVICE8 pD3DDevice, LPD3DXBASEMESH* ppCloneMesh) PURE;
    STDMETHOD(GetVertexBuffer)(THIS_ LPDIRECT3DVERTEXBUFFER8* ppVB) PURE;
    STDMETHOD(GetIndexBuffer)(THIS_ LPDIRECT3DINDEXBUFFER8* ppIB) PURE;
    STDMETHOD(LockVertexBuffer)(THIS_ DWORD Flags, BYTE** ppData) PURE;
    STDMETHOD(UnlockVertexBuffer)(THIS) PURE;
    STDMETHOD(LockIndexBuffer)(THIS_ DWORD Flags, BYTE** ppData) PURE;
    STDMETHOD(UnlockIndexBuffer)(THIS) PURE;
    STDMETHOD(GetAttributeTable)(
                THIS_ D3DXATTRIBUTERANGE* pAttribTable, DWORD* pAttribTableSize) PURE;

    STDMETHOD(ConvertPointRepsToAdjacency)(THIS_ CONST DWORD* pPRep, DWORD* pAdjacency) PURE;
    STDMETHOD(ConvertAdjacencyToPointReps)(THIS_ CONST DWORD* pAdjacency, DWORD* pPRep) PURE;
    STDMETHOD(GenerateAdjacency)(THIS_ FLOAT Epsilon, DWORD* pAdjacency) PURE;

    // ID3DXPMesh
    STDMETHOD(ClonePMeshFVF)(THIS_ DWORD Options, DWORD FVF,
                LPDIRECT3DDEVICE8 pD3DDevice, LPD3DXPMESH* ppCloneMesh) PURE;
    STDMETHOD(ClonePMesh)(THIS_ DWORD Options, CONST DWORD *pDeclaration,
                LPDIRECT3DDEVICE8 pD3DDevice, LPD3DXPMESH* ppCloneMesh) PURE;
    STDMETHOD(SetNumFaces)(THIS_ DWORD Faces) PURE;
    STDMETHOD(SetNumVertices)(THIS_ DWORD Vertices) PURE;
    STDMETHOD_(DWORD, GetMaxFaces)(THIS) PURE;
    STDMETHOD_(DWORD, GetMinFaces)(THIS) PURE;
    STDMETHOD_(DWORD, GetMaxVertices)(THIS) PURE;
    STDMETHOD_(DWORD, GetMinVertices)(THIS) PURE;
    STDMETHOD(Save)(THIS_ IStream* pStream, CONST D3DXMATERIAL* pMaterials, DWORD NumMaterials) PURE;

    STDMETHOD(Optimize)(THIS_ DWORD Flags, DWORD* pAdjacencyOut,
                DWORD* pFaceRemap, LPD3DXBUFFER* ppVertexRemap,
                LPD3DXPMESH* ppOptMesh) PURE;

    STDMETHOD(GetAdjacency)(THIS_ DWORD** ppAdjacency) PURE;

    STDMETHOD(GenerateVertexHistory)(THIS_ DWORD* pVertexHistory) PURE;
};


//----------------------------------------------------------------------------
// ID3DXSPMesh:
// ------------
// This object is an extension of ID3DXBaseMesh. It is used for storing
// and manipulating simplified mesh data.
//----------------------------------------------------------------------------

typedef interface ID3DXSPMesh ID3DXSPMesh;
typedef ID3DXSPMesh *LPD3DXSPMESH;

#undef INTERFACE
#define INTERFACE ID3DXSPMesh

DECLARE_INTERFACE_(ID3DXSPMesh, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // ID3DXSPMesh
    STDMETHOD_(DWORD, GetNumFaces)(THIS) PURE;
    STDMETHOD_(DWORD, GetNumVertices)(THIS) PURE;
    STDMETHOD_(DWORD, GetFVF)(THIS) PURE;
    STDMETHOD(GetDeclaration)(THIS_ DWORD Declaration[MAX_FVF_DECL_SIZE]) PURE;
    STDMETHOD_(DWORD, GetOptions)(THIS) PURE;
    STDMETHOD(GetDevice)(THIS_ LPDIRECT3DDEVICE8* ppDevice) PURE;
    STDMETHOD(CloneMeshFVF)(THIS_ DWORD Options, DWORD FVF,
                LPDIRECT3DDEVICE8 pD3DDevice, LPD3DXSPMESH* ppCloneMesh) PURE;
    STDMETHOD(CloneMesh)(THIS_ DWORD Options, CONST DWORD *pDeclaration,
                LPDIRECT3DDEVICE8 pD3DDevice, LPD3DXSPMESH* ppCloneMesh) PURE;
    STDMETHOD(GetVertexBuffer)(THIS_ LPDIRECT3DVERTEXBUFFER8* ppVB) PURE;
    STDMETHOD(GetIndexBuffer)(THIS_ LPDIRECT3DINDEXBUFFER8* ppIB) PURE;
    STDMETHOD(LockVertexBuffer)(THIS_ DWORD Flags, BYTE** ppData) PURE;
    STDMETHOD(UnlockVertexBuffer)(THIS) PURE;
    STDMETHOD(LockIndexBuffer)(THIS_ DWORD Flags, BYTE** ppData) PURE;
    STDMETHOD(UnlockIndexBuffer)(THIS) PURE;
    STDMETHOD(GetAttributeTable)(
                THIS_ D3DXATTRIBUTERANGE* pAttribTable, DWORD* pAttribTableSize) PURE;

    STDMETHOD(GetAdjacency)(THIS_ DWORD** pAdjacency) PURE;
    STDMETHOD(ReduceFaces)(THIS_ DWORD Faces) PURE;
    STDMETHOD(ReduceVertices)(THIS_ DWORD Vertices) PURE;
    STDMETHOD_(DWORD, GetMaxFaces)(THIS) PURE;
    STDMETHOD_(DWORD, GetMaxVertices)(THIS) PURE;
    STDMETHOD(Save)(THIS_ IStream* pStream, CONST D3DXMATERIAL* pMaterials, DWORD NumMaterials) PURE;
};


//----------------------------------------------------------------------------
// D3DXMESHOPT:
// ------------
// This enum is used to specify options for mesh optimization.
// The D3DXMESHOPT_XXX flags are used by ID3DXMesh::Optimize
// and D3DXOptimizeFaces.  The D3DXMESHOPT_STRIPREORDER flag is used by
// ID3DXMesh::Optimize and D3DXOptimizeVertices.
//----------------------------------------------------------------------------

typedef enum _D3DXMESHOPT {
    D3DXMESHOPT_COMPACT         = 0x01000000,
    D3DXMESHOPT_ATTRSORT        = 0x02000000,
    D3DXMESHOPT_VERTEXCACHE     = 0x04000000,
    D3DXMESHOPT_STRIPREORDER    = 0x08000000,
    D3DXMESHOPT_IGNOREVERTS     = 0x10000000,
    D3DXMESHOPT_SHAREVB         = 0x20000000,
} D3DXMESHOPT;

//----------------------------------------------------------------------------
// D3DXCleanMesh:
// -------------
//  Cleans a mesh using the specified adjacency buffer.
//
//  Parameters:
//   pMesh
//      The mesh to be cleaned.
//   pAdjacency
//      The adjacency data for the mesh.
//   ppMeshOut
//      The resulting cleaned mesh.
//   ppAdjacencyOut
//      The resulting adjacency data.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCleanMesh(
        LPD3DXMESH pMesh,
        CONST DWORD* pAdjacency,
        LPD3DXMESH* ppMeshOut,
        DWORD* pAdjacencyOut,
        LPD3DXBUFFER *ppErrorsAndWarnings);

//----------------------------------------------------------------------------
// D3DXValidMesh:
// --------------
//  Determine if a mesh is valid.  Checks for manifoldness, etc.
//  It also can return messages in a string to indicate what is wrong
//  with the mesh
//
//  Parameters:
//   pMesh
//      The mesh to be validated.
//   pAdjacency
//      The adjacency data for the mesh.
//   ppErrorsAndWarnings
//      A buffer which will be filled with a string of errors, warnings,
//      and other information.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXValidMesh(
        LPD3DXMESH pMeshIn,
        CONST DWORD* pAdjacency,
        LPD3DXBUFFER *ppErrorsAndWarnings);

//----------------------------------------------------------------------------
// D3DXGeneratePMesh:
// -----------------
//  Generates a progressive mesh from a given mesh.
//
//  Parameters:
//   pMesh
//      The mesh to be simplified.
//   pAdjacency
//      The adjacency data for the mesh.
//   pVertexAttributeWeights
//      Array of D3DXATTRIBUTEWEIGHTS that describe how to weight each
//      vertex component.
//   pVertexWeights
//      Array of floats that specify a per-vertex weight.
//   MinValue
//      The minimum number of vertices/faces for the progressive mesh.
//   Options
//      Specifies simplification options. (D3DXMESHSIMP)
//   ppPMesh
//      The resulting progressive mesh.
//----------------------------------------------------------------------------
HRESULT WINAPI
    D3DXGeneratePMesh(
        LPD3DXMESH pMesh,
        CONST DWORD *pAdjacency,
        CONST D3DXATTRIBUTEWEIGHTS *pVertexAttributeWeights,
        CONST FLOAT *pVertexWeights,
        DWORD MinValue,
        DWORD Options,
        LPD3DXPMESH *ppPMesh);


//----------------------------------------------------------------------------
// D3DXCreateSimplificationMesh:
// ----------------------------
//  Generates a simplification mesh.
//
//  Parameters:
//   pMesh
//      The mesh to be simplified.
//   pAdjacency
//      The adjacency data for the mesh.
//   pVertexAttributeWeights
//      Array of D3DXATTRIBUTEWEIGHTS that describe how to weight each
//      vertex component.
//   pVertexWeights
//      Array of floats that specify a per-vertex weight.
//   ppSMesh
//      The resulting simplification mesh.
//----------------------------------------------------------------------------
HRESULT WINAPI
    D3DXCreateSimplificationMesh(
        LPD3DXMESH pMesh,
        CONST DWORD *pAdjacency,
        CONST D3DXATTRIBUTEWEIGHTS *pVertexAttributeWeights,
        CONST FLOAT *pVertexWeights,
        LPD3DXSPMESH *ppSMesh);


//----------------------------------------------------------------------------
// D3DXCreateMesh:
// ---------------
// Creates a mesh object.
//
// Parameters:
//  NumFaces
//      Number of faces in the mesh.
//  NumVertices
//      Number of vertices in the mesh.
//  Options
//      A combination of D3DXMESH flags.
//  pDeclaration
//      An array of D3DVERTEXELEMENT8s that describe the vertex format.
//  pD3DDevice
//      The D3D device with which the mesh is to be associated.
//  ppMesh
//      The mesh object that will be created.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateMesh(
        DWORD NumFaces,
        DWORD NumVertices,
        DWORD Options,
        CONST DWORD *pDeclaration,
        LPDIRECT3DDEVICE8 pD3DDevice,
        LPD3DXMESH* ppMesh);


//----------------------------------------------------------------------------
// D3DXCreateMeshFVF:
// ------------------
// Creates a mesh object using an FVF.
//
// Parameters:
//  NumFaces
//      Number of faces in the mesh.
//  NumVertices
//      Number of vertices in the mesh.
//  Options
//      A combination of D3DXMESH flags.
//  FVF
//      The FVF of the vertices in the mesh.
//  pD3DDevice
//      The D3D device with which the mesh is to be associated.
//  ppMesh
//      The mesh object that will be created.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateMeshFVF(
        DWORD NumFaces,
        DWORD NumVertices,
        DWORD Options,
        DWORD FVF,
        LPDIRECT3DDEVICE8 pD3DDevice,
        LPD3DXMESH* ppMesh);

//----------------------------------------------------------------------------
// D3DXCreatePMeshFromStream:
// --------------------------
// Creates a progressive mesh from a stream.
//
// Parameters:
//  pStream
//      An IStream object that contains the progressive mesh data.
//  Options
//      A combination of D3DXMESH flags.
//  pD3DDevice
//      The D3D device with which the mesh is to be associated.
//  ppMaterials
//      Returns a buffer containing the materials in the mesh.
//  ppPMesh
//      The mesh object that will be created.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreatePMeshFromStream(
        IStream *pStream,
        DWORD Options,
        LPDIRECT3DDEVICE8 pD3DDevice,
        LPD3DXBUFFER* ppMaterials,
        LPD3DXPMESH* ppPMesh);


//----------------------------------------------------------------------------
// D3DXCreateSPMeshFromStream:
// ---------------------------
// Creates a simplification mesh from a stream.
//
// Parameters:
//  pStream
//      An IStream object that contains the simplification mesh data.
//  Options
//      A combination of D3DXMESH flags.
//  pD3DDevice
//      The D3D device with which the mesh is to be associated.
//  ppMaterials
//      Returns a buffer containing the materials in the mesh.
//  ppPMesh
//      The mesh object that will be created.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateSPMeshFromStream(
        IStream *pStream,
        DWORD Options,
        LPDIRECT3DDEVICE8 pD3DDevice,
        LPD3DXBUFFER* ppMaterials,
        LPD3DXSPMESH* ppSMesh);


//----------------------------------------------------------------------------
// D3DXWELDEPSILONS:
// --------
// This structure is used to specify epsilon values for welding vertices.
//
//  Position
//      The epsilon value to use for vertex positions.
//  BlendWeights
//      The epsilon value to use for vertex blend weights.
//  Normal
//      The epsilon value to use for vertex normals.
//  PSize
//      The epsilon value to use for vertex point sizes.
//  Specular
//      The epsilon value to use for vertex specular colors.
//  Diffuse
//      The epsilon value to use for vertex diffuse colors.
//  Texcoord
//      An array of epsilon values to use for each texture coordinate set.
//----------------------------------------------------------------------------

typedef struct _D3DXWELDEPSILONS
{
    FLOAT Position;
    FLOAT BlendWeights;
    FLOAT Normal;
    FLOAT PSize;
    FLOAT Specular;
    FLOAT Diffuse;
    FLOAT Texcoord[8];

    // D3DXWELDEPSILONS_DEFAULT provides reasonable default values
} D3DXWELDEPSILONS, *LPD3DXWELDEPSILONS;

extern CONST D3DXWELDEPSILONS D3DXWELDEPSILONS_DEFAULT;

//----------------------------------------------------------------------------
// D3DXWeldVertices:
// ---------------
// Welds vertices that are within a given epsilon.
//
// Parameters:
//  pMesh
//      The mesh to be welded.
//  Flags
//      A combination of D3DXWELDEPSILONS flags.
//  pEpsilons
//      An array of epsilon values to use for the weld.
//  pAdjacencyIn
//      The adjacency data for the mesh.
//  pAdjacencyOut
//      The resulting adjacency data.
//  pFaceRemap
//      An array that will be filled with the original face indices.
//  ppVertexRemap
//      A buffer that will be filled with the original vertex indices.
//----------------------------------------------------------------------------

// Flags for D3DXWeldVertices
#define D3DXWELDEPSILONS_WELDALL            (1 << 0)
#define D3DXWELDEPSILONS_WELDPARTIALMATCHES (1 << 1)
#define D3DXWELDEPSILONS_DONOTREMOVEUNUSEDVERTS (1 << 2)
#define D3DXWELDEPSILONS_DONOTSPLIT (1 << 3)

HRESULT WINAPI
    D3DXWeldVertices(
        LPD3DXMESH pMesh,
        DWORD Flags,
        CONST D3DXWELDEPSILONS *pEpsilons,
        CONST DWORD* pAdjacencyIn,
        DWORD* pAdjacencyOut,
        DWORD* pFaceRemap,
        LPD3DXBUFFER* ppVertexRemap);


//----------------------------------------------------------------------------
// D3DXSplitMesh:
// --------------
// Splits a mesh into multiple sub-meshes based on attribute.
//
// Parameters:
//  pMesh
//      The mesh to be split.
//  pAdjacency
//      The adjacency data for the mesh.
//  MaxVerts
//      The maximum number of vertices per mesh.
//  Options
//      D3DXMESHOPT flags.
//  pMeshes
//      An array of meshes that will be filled with the split-off meshes.
//  pAdjacencyOut
//      An array of buffers that will be filled with the new adjacency data.
//  pFaceRemap
//      An array that will be filled with the original face indices.
//  pVertRemap
//      An array that will be filled with the original vertex indices.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXSplitMesh(
        LPD3DXMESH pMesh,
        CONST DWORD *pAdjacency,
        CONST DWORD MaxSize,
        CONST DWORD Options,
        DWORD *pNumMeshes,
        LPD3DXBUFFER **ppMeshes,
        LPD3DXBUFFER **ppAdjacency,
        LPD3DXBUFFER **ppFaceRemap,
        LPD3DXBUFFER **ppVertRemap);



//----------------------------------------------------------------------------
// D3DXTessellateNPatches:
// -----------------------
// Tessellates an N-Patch mesh.
//
// Parameters:
//  pMesh
//      The mesh to be tessellated.
//  pAdjacency
//      The adjacency data for the mesh.
//  NumSegs
//      The number of segments to tessellate with.
//  ppMesh
//      The resulting tessellated mesh.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXTessellateNPatches(
        LPD3DXMESH pMeshIn,
        CONST DWORD* pAdjacency,
        FLOAT NumSegs,
        BOOL QuadraticInterp,
        LPD3DXMESH *ppMeshOut,
        LPD3DXBUFFER *ppAdjacencyOut);


//----------------------------------------------------------------------------
// D3DXComputeNormals:
// -------------------
// Computes normals for a mesh.
//
// Parameters:
//  pMesh
//      The mesh to compute normals for. The mesh must contain a normal vector
//      field. Any existing normals will be overwritten.
//  pAdjacency
//      The adjacency data for the mesh. If NULL, normals will not be
//      smoothed across edges.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXComputeNormals(
        LPD3DXBASEMESH pMesh,
        CONST DWORD *pAdjacency);


//----------------------------------------------------------------------------
// D3DXComputeBoundingSphere:
// --------------------------
// Computes a bounding sphere for a mesh.
//
// Parameters:
//  pPoints
//      Pointer to the first vertex position in the mesh.
//  NumPoints
//      Number of points in the mesh.
//  Stride
//      The stride between positions in the buffer.
//  pCenter
//      Returns the center of the bounding sphere.
//  pRadius
//      Returns the radius of the bounding sphere.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXComputeBoundingSphere(
        CONST D3DXVECTOR3 *pPoints,
        DWORD NumPoints,
        DWORD Stride,
        D3DXVECTOR3 *pCenter,
        FLOAT *pRadius);


//----------------------------------------------------------------------------
// D3DXComputeBoundingBox:
// -----------------------
// Computes a bounding box for a mesh.
//
// Parameters:
//  pPoints
//      Pointer to the first vertex position in the mesh.
//  NumPoints
//      Number of points in the mesh.
//  Stride
//      The stride between positions in the buffer.
//  pMin
//      Returns the minimum point of the bounding box.
//  pMax
//      Returns the maximum point of the bounding box.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXComputeBoundingBox(
        CONST D3DXVECTOR3 *pPoints,
        DWORD NumPoints,
        DWORD Stride,
        D3DXVECTOR3 *pMin,
        D3DXVECTOR3 *pMax);


//----------------------------------------------------------------------------
// D3DXIntersect:
// --------------
// Find the intersection of a ray and a mesh.
//
// Parameters:
//  pMesh
//      The mesh to be intersected.
//  pRayPos
//      The origin of the ray.
//  pRayDir
//      The direction of the ray.
//  pHit
//      Returns TRUE if an intersection is found, otherwise FALSE.
//  pFaceIndex
//      Returns the index of the face that is intersected.
//  pU, pV
//      Returns the barycentric coordinates of the intersection.
//  pDist
//      Returns the distance from the origin to the intersection.
//  ppAllHits
//      Returns a buffer containing all of the hits.
//  pCountOfHits
//      Returns the number of hits in the buffer.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXIntersect(
        LPD3DXBASEMESH pMesh,
        CONST D3DXVECTOR3 *pRayPos,
        CONST D3DXVECTOR3 *pRayDir,
        BOOL    *pHit,
        DWORD   *pFaceIndex,
        FLOAT   *pU,
        FLOAT   *pV,
        FLOAT   *pDist,
        LPD3DXBUFFER *ppAllHits,
        DWORD   *pCountOfHits);


//----------------------------------------------------------------------------
// D3DXIntersectSubset:
// --------------------
// Find the intersection of a ray and a subset of a mesh.
//
// Parameters:
//  pMesh
//      The mesh to be intersected.
//  AttribId
//      The subset of the mesh to be intersected.
//  pRayPos
//      The origin of the ray.
//  pRayDir
//      The direction of the ray.
//  pHit
//      Returns TRUE if an intersection is found, otherwise FALSE.
//  pFaceIndex
//      Returns the index of the face that is intersected.
//  pU, pV
//      Returns the barycentric coordinates of the intersection.
//  pDist
//      Returns the distance from the origin to the intersection.
//  ppAllHits
//      Returns a buffer containing all of the hits.
//  pCountOfHits
//      Returns the number of hits in the buffer.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXIntersectSubset(
        LPD3DXBASEMESH pMesh,
        DWORD AttribId,
        CONST D3DXVECTOR3 *pRayPos,
        CONST D3DXVECTOR3 *pRayDir,
        BOOL    *pHit,
        DWORD   *pFaceIndex,
        FLOAT   *pU,
        FLOAT   *pV,
        FLOAT   *pDist,
        LPD3DXBUFFER *ppAllHits,
        DWORD   *pCountOfHits);


//----------------------------------------------------------------------------
// D3DXATTRIBUTEWEIGHTS:
// ---------------------
// This structure is used to specify the weighting for each component of a
// vertex when simplifying a mesh.
//----------------------------------------------------------------------------

typedef struct _D3DXATTRIBUTEWEIGHTS
{
    FLOAT Position;
    FLOAT Boundary;
    FLOAT Normal;
    FLOAT Diffuse;
    FLOAT Specular;
    FLOAT Texcoord[8];
    FLOAT Tangent;
    FLOAT Binormal;
} D3DXATTRIBUTEWEIGHTS, *LPD3DXATTRIBUTEWEIGHTS;


//----------------------------------------------------------------------------
// D3DXSimplifyMesh:
// -----------------
// Simplify a mesh.
//
// Parameters:
//  pMesh
//      The mesh to be simplified.
//  pAdjacency
//      The adjacency data for the mesh.
//  pVertexAttributeWeights
//      An array of attribute weights for the simplification.
//  pVertexWeights
//      An array of per-vertex weights for the simplification.
//  MinValue
//      The minimum number of primitives to simplify to.
//  Options
//      D3DXMESHSIMP options.
//  ppMesh
//      The resulting simplified mesh.
//----------------------------------------------------------------------------

// D3DXMESHSIMP flags
typedef enum _D3DXMESHSIMP
{
    D3DXMESHSIMP_VERTEX = 0x1,
    D3DXMESHSIMP_FACE = 0x2,

    D3DXMESHSIMP_FORCE_DWORD = 0x7fffffff
} D3DXMESHSIMP;

HRESULT WINAPI
    D3DXSimplifyMesh(
        LPD3DXMESH pMesh,
        CONST DWORD* pAdjacency,
        CONST D3DXATTRIBUTEWEIGHTS *pVertexAttributeWeights,
        CONST FLOAT *pVertexWeights,
        DWORD MinValue,
        DWORD Options,
        LPD3DXMESH* ppMesh);


//----------------------------------------------------------------------------
// D3DXComputeIMTFromPerVertexSignal:
// ----------------------------------
// Computes an integrated metric tensor (IMT) for each vertex of a mesh.
//
// Parameters:
//  pMesh
//      The mesh.
//  pSignal
//      An array of floats specifying the signal value at each vertex.
//  SignalDimension
//      The dimension of the signal vectors.
//  SignalStride
//      The stride of the signal vectors.
//  pIMT
//      An array of floats to be filled with the IMT data.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXComputeIMTFromPerVertexSignal(
        LPD3DXMESH pMesh,
        CONST FLOAT *pSignal,
        DWORD SignalDimension,
        DWORD SignalStride,
        DWORD *pAdjacency,
        LPD3DXBUFFER *pIMTData);


//----------------------------------------------------------------------------
// D3DXComputeIMTFromSignal:
// -------------------------
// Computes an integrated metric tensor (IMT) for each vertex of a mesh.
//
// Parameters:
//  pMesh
//      The mesh.
//  pSignal
//      An array of floats specifying the signal value at each texel.
//  uWidth
//      The width of the signal texture.
//  uHeight
//      The height of the signal texture.
//  uSignalDimension
//      The dimension of the signal vectors.
//  pIMT
//      An array of floats to be filled with the IMT data.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXComputeIMTFromSignal(
        LPD3DXMESH pMesh,
        LPCVOID pSignal,
        UINT uWidth,
        UINT uHeight,
        UINT uSignalDimension,
        DWORD *pAdjacency,
        LPD3DXBUFFER *pIMTData);


//----------------------------------------------------------------------------
// D3DXComputeIMTFromTexture:
// --------------------------
// Computes an integrated metric tensor (IMT) for each vertex of a mesh.
//
// Parameters:
//  pMesh
//      The mesh.
//  pTexture
//      The texture containing the signal data.
//  uSignalDimension
//      The dimension of the signal vectors.
//  pIMT
//      An array of floats to be filled with the IMT data.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXComputeIMTFromTexture(
        LPD3DXMESH pMesh,
        LPDIRECT3DTEXTURE8 pTexture,
        DWORD *pAdjacency,
        LPD3DXBUFFER *pIMTData);


//----------------------------------------------------------------------------
// D3DXCreateBuffer:
// -----------------
// Creates a buffer.
//
// Parameters:
//  NumBytes
//      Number of bytes in the buffer.
//  ppBuffer
//      The buffer object that will be created.
//----------------------------------------------------------------------------

typedef interface ID3DXBuffer ID3DXBuffer;
typedef ID3DXBuffer *LPD3DXBUFFER;

#undef INTERFACE
#define INTERFACE ID3DXBuffer

DECLARE_INTERFACE_(ID3DXBuffer, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    // ID3DXBuffer
    STDMETHOD_(LPVOID, GetBufferPointer)(THIS) PURE;
    STDMETHOD_(DWORD, GetBufferSize)(THIS) PURE;
};


HRESULT WINAPI
    D3DXCreateBuffer(
        DWORD NumBytes,
        LPD3DXBUFFER* ppBuffer);


//----------------------------------------------------------------------------
// D3DXCreateSkinInfo:
// -------------------
// Creates a skin info object.
//
// Parameters:
//  NumVertices
//      Number of vertices in the skin.
//  pDeclaration
//      Vertex declaration.
//  NumBones
//      Number of bones in the skin.
//  ppSkinInfo
//      The skin info object that will be created.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateSkinInfo(
        DWORD NumVertices,
        CONST DWORD *pDeclaration,
        DWORD NumBones,
        LPD3DXSKININFO* ppSkinInfo);


//----------------------------------------------------------------------------
// D3DXCreateSkinInfoFVF:
// ----------------------
// Creates a skin info object from an FVF.
//
// Parameters:
//  NumVertices
//      Number of vertices in the skin.
//  FVF
//      The FVF of the vertices in the skin.
//  NumBones
//      Number of bones in the skin.
//  ppSkinInfo
//      The skin info object that will be created.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateSkinInfoFVF(
        DWORD NumVertices,
        DWORD FVF,
        DWORD NumBones,
        LPD3DXSKININFO* ppSkinInfo);


//----------------------------------------------------------------------------
// D3DXCreateSkinInfoFromBlendedMesh:
// ----------------------------------
// Creates a skin info object from a blended mesh.
//
// Parameters:
//  pMesh
//      The blended mesh.
//  NumBones
//      The number of bones in the skin.
//  ppSkinInfo
//      The skin info object that will be created.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateSkinInfoFromBlendedMesh(
        LPD3DXMESH pMesh,
        DWORD NumBones,
        LPD3DXSKININFO *ppSkinInfo);


//----------------------------------------------------------------------------
// ID3DXSkinInfo:
// --------------
// This object is used for storing and manipulating skin data.
//----------------------------------------------------------------------------

typedef interface ID3DXSkinInfo ID3DXSkinInfo;
typedef ID3DXSkinInfo *LPD3DXSKININFO;

#undef INTERFACE
#define INTERFACE ID3DXSkinInfo

DECLARE_INTERFACE_(ID3DXSkinInfo, IUnknown)
{
    // IUnknown
    STDMETHOD(QueryInterface)(THIS_ REFIID iid, LPVOID *ppv) PURE;
    STDMETHOD_(ULONG, AddRef)(THIS) PURE;
    STDMETHOD_(ULONG, Release)(THIS) PURE;

    //FVF
    STDMETHOD_(DWORD, GetFVF)(THIS) PURE;
    STDMETHOD(GetDeclaration)(THIS_ DWORD Declaration[MAX_FVF_DECL_SIZE]) PURE;

    //Bones
    STDMETHOD_(DWORD, GetNumBones)(THIS) PURE;
    STDMETHOD(GetBoneInfo)(THIS_ DWORD bone, D3DXBONEINFO *pBoneInfo) PURE;
    STDMETHOD(SetBoneInfo)(THIS_ DWORD bone, CONST D3DXBONEINFO *pBoneInfo) PURE;
    STDMETHOD(GetBoneName)(THIS_ DWORD bone, LPSTR pName) PURE;
    STDMETHOD(SetBoneName)(THIS_ DWORD bone, LPCSTR pName) PURE;
    STDMETHOD_(DWORD, GetMaxVertexInfluences)(THIS_ DWORD bone) PURE;
    STDMETHOD(GetNumBoneInfluences)(THIS_ DWORD bone, DWORD *pNum) PURE;
    STDMETHOD(GetBoneInfluence)(THIS_ DWORD bone, DWORD *pVertices, float *pWeights) PURE;
    STDMETHOD(SetBoneInfluence)(THIS_ DWORD bone, DWORD NumInfluences,
                                CONST DWORD *pVertices, CONST float *pWeights) PURE;

    STDMETHOD(Remap)(THIS_ DWORD NumVertices, DWORD *pVertexRemap) PURE;

    STDMETHOD(ConvertToBlendedMesh)(THIS_ LPD3DXMESH pMesh,
                                    DWORD Options,
                                    CONST DWORD *pAdjacencyIn,
                                    LPDWORD pAdjacencyOut,
                                    LPDWORD pFaceRemap,
                                    LPD3DXBUFFER *ppVertexRemap,
                                    LPD3DXMESH *ppMesh) PURE;

    STDMETHOD(ConvertToIndexedBlendedMesh)(THIS_ LPD3DXMESH pMesh,
                                    DWORD Options,
                                    DWORD paletteSize,
                                    CONST DWORD *pAdjacencyIn,
                                    LPDWORD pAdjacencyOut,
                                    LPDWORD pFaceRemap,
                                    LPD3DXBUFFER *ppVertexRemap,
                                    LPDWORD pMaxVertexInfl,
                                    LPD3DXBUFFER *ppBoneCombinationTable,
                                    LPD3DXMESH *ppMesh) PURE;

    STDMETHOD(Clone)(THIS_ LPD3DXSKININFO *ppSkinInfo) PURE;
};


//----------------------------------------------------------------------------
// D3DXBONEINFO:
// -------------
// This structure is used to hold information about a single bone in a skin.
//
//  BoneName
//      The name of the bone.
//  pBoneWeights
//      An array of vertex weights for the bone.
//  pVertexIndices
//      An array of vertex indices for the bone.
//  NumBoneWeights
//      The number of weights in the pBoneWeights and pVertexIndices arrays.
//  OffsetMatrix
//      The matrix that transforms the skin from bind space to bone space.
//----------------------------------------------------------------------------

typedef struct _D3DXBONEINFO
{
    LPSTR Name;
    D3DXMATRIXA16 OffsetMatrix;
} D3DXBONEINFO, *LPD3DXBONEINFO;



//----------------------------------------------------------------------------
// D3DXMATERIAL:
// -------------
// This structure is used to hold material information.
//
//  pTextureFilename
//      Name of the texture file.
//  MatD3D
//      The D3D material structure.
//----------------------------------------------------------------------------

typedef struct _D3DXMATERIAL
{
    D3DMATERIAL8 MatD3D;
    LPSTR        pTextureFilename;
} D3DXMATERIAL, *LPD3DXMATERIAL;


//----------------------------------------------------------------------------
// D3DXATTRIBUTERANGE:
// -------------------
// This structure is used to define a range of faces in a mesh that all
// have the same attribute.
//
//  AttribId
//      The attribute id for this range.
//  FaceStart
//      The starting face of this range.
//  FaceCount
//      The number of faces in this range.
//  VertexStart
//      The starting vertex of this range.
//  VertexCount
//      The number of vertices in this range.
//----------------------------------------------------------------------------

typedef struct _D3DXATTRIBUTERANGE
{
    DWORD AttribId;
    DWORD FaceStart;
    DWORD FaceCount;
    DWORD VertexStart;
    DWORD VertexCount;
} D3DXATTRIBUTERANGE, *LPD3DXATTRIBUTERANGE;


//----------------------------------------------------------------------------
// D3DXINTERSECTINFO:
// ------------------
// This structure is returned by ID3DXBaseMesh::Intersect in the
// ppAllHits buffer.  It contains the information about a single intersection
// of a ray with a mesh.
//
//  FaceIndex
//      The index of the face that was intersected.
//  U, V
//      The barycentric coordinates of the intersection.
//  Dist
//      The distance from the ray's origin to the intersection.
//----------------------------------------------------------------------------

typedef struct _D3DXINTERSECTINFO
{
    DWORD FaceIndex;
    FLOAT U, V;
    FLOAT Dist;
} D3DXINTERSECTINFO, *LPD3DXINTERSECTINFO;



//----------------------------------------------------------------------------
// D3DXFVFToDecl:
// --------------
// Convert an FVF to a vertex declaration.
//
// Parameters:
//  FVF
//      The FVF to be converted.
//  pDeclaration
//      An array of D3DVERTEXELEMENT8s that will be filled with the converted
//      declaration data.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXFVFToDecl(
        DWORD FVF,
        DWORD pDeclaration[MAX_FVF_DECL_SIZE]);


//----------------------------------------------------------------------------
// D3DXDeclToFVF:
// --------------
// Convert a vertex declaration to an FVF.
//
// Parameters:
//  pDeclaration
//      An array of D3DVERTEXELEMENT8s that describe the vertex format.
//  pFVF
//      Returns the converted FVF.
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXDeclToFVF(
        CONST DWORD *pDeclaration,
        DWORD *pFVF);


//----------------------------------------------------------------------------
// D3DXGetDeclVertexSize:
// ----------------------
// Get the size of a vertex, given a declaration.
//
// Parameters:
//  pDeclaration
//      An array of D3DVERTEXELEMENT8s that describe the vertex format.
//  Stream
//      The stream index for which the size is to be returned.
//----------------------------------------------------------------------------

UINT WINAPI
    D3DXGetDeclVertexSize(
        CONST DWORD *pDeclaration,
        DWORD Stream);


//----------------------------------------------------------------------------
// D3DXGetFVFVertexSize:
// ---------------------
// Get the size of a vertex, given an FVF.
//
// Parameters:
//  FVF
//      The FVF of the vertex.
//----------------------------------------------------------------------------

UINT WINAPI
    D3DXGetFVFVertexSize(
        DWORD FVF);


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__D3DX8MESH_H__