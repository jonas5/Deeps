/*==========================================================================;
 *
 *  Copyright (C) 1994-2001 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       d3dx8shape.h
 *  Content:    D3DX simple shape routines
 *
 ***************************************************************************/

#ifndef __D3DX8SHAPE_H__
#define __D3DX8SHAPE_H__

#include "d3dx8mesh.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus


//----------------------------------------------------------------------------
// D3DXCreatePolygon:
// ------------------
// Creates a polygon mesh.
//
// Parameters:
//  pDevice
//      The D3D device with which the mesh is to be associated.
//	Length
//		Length of the polygon.  (distance from origin to each vertex)
//	Sides
//		Number of sides the polygon has.  (must be >= 3)
//  ppMesh
//      The mesh object that will be created.  This object will have
//      the D3DFVF_XYZ and D3DFVF_NORMAL FVFs.
//	ppAdjacency
//		Returns a buffer containing adjacency data.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreatePolygon(
        LPDIRECT3DDEVICE8  pDevice,
        float              Length,
        UINT               Sides,
        LPD3DXMESH*        ppMesh,
        LPD3DXBUFFER*      ppAdjacency);


//----------------------------------------------------------------------------
// D3DXCreateBox:
// --------------
// Creates a box mesh.
//
// Parameters:
//  pDevice
//      The D3D device with which the mesh is to be associated.
//	Width
//		Width of the box
//	Height
//		Height of the box
//	Depth
//		Depth of the box
//  ppMesh
//      The mesh object that will be created.  This object will have
//      the D3DFVF_XYZ and D3DFVF_NORMAL FVFs.
//	ppAdjacency
//		Returns a buffer containing adjacency data.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateBox(
        LPDIRECT3DDEVICE8  pDevice,
        float              Width,
        float              Height,
        float              Depth,
        LPD3DXMESH*        ppMesh,
        LPD3DXBUFFER*      ppAdjacency);


//----------------------------------------------------------------------------
// D3DXCreateCylinder:
// -------------------
// Creates a cylinder mesh.
//
// Parameters:
//  pDevice
//      The D3D device with which the mesh is to be associated.
//	Radius1
//		Radius of the cylinder at the -Z end
//	Radius2
//		Radius of the cylinder at the +Z end
//	Length
//		Length of the cylinder
//	Slices
//		Number of slices about the main axis
//	Stacks
//		Number of stacks along the main axis
//  ppMesh
//      The mesh object that will be created.  This object will have
//      the D3DFVF_XYZ and D3DFVF_NORMAL FVFs.
//	ppAdjacency
//		Returns a buffer containing adjacency data.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateCylinder(
        LPDIRECT3DDEVICE8  pDevice,
        float              Radius1,
        float              Radius2,
        float              Length,
        UINT               Slices,
        UINT               Stacks,
        LPD3DXMESH*        ppMesh,
        LPD3DXBUFFER*      ppAdjacency);


//----------------------------------------------------------------------------
// D3DXCreateSphere:
// -----------------
// Creates a sphere mesh.
//
// Parameters:
//  pDevice
//      The D3D device with which the mesh is to be associated.
//	Radius
//		Radius of the sphere
//	Slices
//		Number of slices about the main axis
//	Stacks
//		Number of stacks along the main axis
//  ppMesh
//      The mesh object that will be created.  This object will have
//      the D3DFVF_XYZ and D3DFVF_NORMAL FVFs.
//	ppAdjacency
//		Returns a buffer containing adjacency data.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateSphere(
        LPDIRECT3DDEVICE8  pDevice,
        float              Radius,
        UINT               Slices,
        UINT               Stacks,
        LPD3DXMESH*        ppMesh,
        LPD3DXBUFFER*      ppAdjacency);


//----------------------------------------------------------------------------
// D3DXCreateTorus:
// ----------------
// Creates a torus mesh.
//
// Parameters:
//  pDevice
//      The D3D device with which the mesh is to be associated.
//	InnerRadius
//		Inner radius of the torus
//	OuterRadius
//		Outer radius of the torus
//	Sides
//		Number of sides in a cross-section
//	Rings
//		Number of rings making up the torus
//  ppMesh
//      The mesh object that will be created.  This object will have
//      the D3DFVF_XYZ and D3DFVF_NORMAL FVFs.
//	ppAdjacency
//		Returns a buffer containing adjacency data.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateTorus(
        LPDIRECT3DDEVICE8  pDevice,
        float              InnerRadius,
        float              OuterRadius,
        UINT               Sides,
        UINT               Rings,
        LPD3DXMESH*        ppMesh,
        LPD3DXBUFFER*      ppAdjacency);


//----------------------------------------------------------------------------
// D3DXCreateTeapot:
// -----------------
// Creates a teapot mesh.
//
// Parameters:
//  pDevice
//      The D3D device with which the mesh is to be associated.
//  ppMesh
//      The mesh object that will be created.  This object will have
//      the D3DFVF_XYZ and D3DFVF_NORMAL FVFs.
//	ppAdjacency
//		Returns a buffer containing adjacency data.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateTeapot(
        LPDIRECT3DDEVICE8  pDevice,
        LPD3DXMESH*        ppMesh,
        LPD3DXBUFFER*      ppAdjacency);


//----------------------------------------------------------------------------
// D3DXCreateText:
// ---------------
// Creates a text mesh.
//
// Parameters:
//  pDevice
//      The D3D device with which the mesh is to be associated.
//  hDC
//      Device context, with desired font selected.
//  hFont
//      A handle to the font to be used to create the mesh
//  c
//      The character to create
//  deviation
//      The maximum cordal deviation from the true font outlines.
//  extrusion
//      The depth of the character mesh
//  ppMesh
//      The mesh object that will be created.  This object will have
//      the D3DFVF_XYZ and D3DFVF_NORMAL FVFs.
//  ppAdjacency
//      Returns a buffer containing adjacency data.
//  pGlyphMetrics
//      Returns the glyph metrics for the character. May be NULL.
//
//----------------------------------------------------------------------------

HRESULT WINAPI
    D3DXCreateTextA(
        LPDIRECT3DDEVICE8  pDevice,
        HDC                hDC,
        LPCSTR             pText,
        float              deviation,
        float              extrusion,
        LPD3DXMESH*        ppMesh,
        LPD3DXBUFFER*      ppAdjacency,
        LPGLYPHMETRICSFLOAT pGlyphMetrics);

HRESULT WINAPI
    D3DXCreateTextW(
        LPDIRECT3DDEVICE8  pDevice,
        HDC                hDC,
        LPCWSTR            pText,
        float              deviation,
        float              extrusion,
        LPD3DXMESH*        ppMesh,
        LPD3DXBUFFER*      ppAdjacency,
        LPGLYPHMETRICSFLOAT pGlyphMetrics);

#ifdef UNICODE
#define D3DXCreateText D3DXCreateTextW
#else
#define D3DXCreateText D3DXCreateTextA
#endif


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__D3DX8SHAPE_H__