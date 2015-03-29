﻿/*
This source file is part of ProceduralGenerator (https://sourceforge.net/projects/proceduralgene/ )

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
the program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
*/
#ifndef ___GENERATOR_BORDER_PANEL_OVERLAY_H___
#define ___GENERATOR_BORDER_PANEL_OVERLAY_H___

#include "Overlay.h"

#include "GlTexture.h"

#pragma warning( push )
#pragma warning( disable:4251 )
#pragma warning( disable:4275 )

namespace ProceduralTextures
{
	/*!
	\author 	Sylvain DOREMUS
	\date 		25/08/2010
	\version	2.0.0
	\brief		A rectangular overlay with a border
	\remark		Uses a spceific material for the border
	*/
	class GeneratorAPI BorderPanelOverlay
		:	public Overlay
	{
	public:
		/**
		 *\brief		Constructor
		 *\param[in]	p_openGl			The OpenGl instance
		 *\param[in]	p_material			The material
		 *\param[in]	p_bordersMaterial	The borders material
		 *\param[in]	p_parent			The parent overlay (if any)
		 */
		BorderPanelOverlay( std::shared_ptr< gl::OpenGl > p_openGl, Material const & p_material, Material const & p_bordersMaterial, std::shared_ptr< Overlay > p_parent );
		/**
		 *\~english
		 *\brief		Destructor
		 *\~french
		 *\brief		Destructeur
		 */
		virtual ~BorderPanelOverlay();
		/**
		 *\brief		Sets the borders shader program
		 *\param[in]	p_type		The new value
		 *\param[in]	p_program	The new value
		 */
		void SetBordersProgram( eMATERIAL_TYPE p_type, std::shared_ptr< gl::ShaderProgram > p_program );
		/**
		 *\brief		Sets the colour of the borders of the overlay
		 *\param[in]	p_colour	The new colour
		 */
		void SetBordersColour( Colour const & p_colour );
		/**
		 *\brief		Sets the texture of the borders of the overlay
		 *\param[in]	p_texture	The new texture
		 */
		void SetBordersTexture( std::shared_ptr< gl::Texture > p_texture );
		/**
		 *\brief		Retrieves the borders of the overlay colour
		 *\return		The value
		 */
		inline Colour const & GetBordersColour()const
		{
			return m_bordersMaterial.GetColour();
		}
		/**
		 *\brief		Retrieves the borders of the overlay texture
		 *\return		The value
		 */
		inline std::shared_ptr< gl::Texture > GetBordersTexture()const
		{
			return m_bordersMaterial.GetTexture();
		}
		/**
		 *\brief		Retrieves the left border thickness
		 *\return		The value
		 */
		inline double GetLeftBorderSize()const
		{
			return m_ptBorderSize[0];
		}
		/**
		 *\brief		Retrieves the top border thickness
		 *\return		The value
		 */
		inline double GetTopBorderSize()const
		{
			return m_ptBorderSize[1];
		}
		/**
		 *\brief		Retrieves the right border thickness
		 *\return		The value
		 */
		inline double GetRightBorderSize()const
		{
			return m_ptBorderSize[2];
		}
		/**
		 *\brief		Retrieves the bottom border thickness
		 *\return		The value
		 */
		inline double GetBottomBorderSize()const
		{
			return m_ptBorderSize[3];
		}
		/**
		 *\brief		Retrieves the borders thicknesses
		 *\return		The value
		 */
		inline Point4d const & GetBordersSize()const
		{
			return m_ptBorderSize;
		}
		/**
		 *\brief		Retrieves the borders thicknesses
		 *\return		The value
		 */
		inline Point4d & GetBordersSize()
		{
			return m_ptBorderSize;
			m_changed = true;
		}
		/**
		 *\brief		Sets the left border thickness
		 *\param[in]	p_fSize	The new value
		 */
		inline void SetLeftBorderSize( double p_fSize )
		{
			m_ptBorderSize[0] = p_fSize;
			m_changed = true;
		}
		/**
		 *\brief		Sets the top border thickness
		 *\param[in]	p_fSize	The new value
		 */
		inline void SetTopBorderSize( double p_fSize )
		{
			m_ptBorderSize[1] = p_fSize;
			m_changed = true;
		}
		/**
		 *\brief		Sets the right border thickness
		 *\param[in]	p_fSize	The new value
		 */
		inline void SetRightBorderSize( double p_fSize )
		{
			m_ptBorderSize[2] = p_fSize;
			m_changed = true;
		}
		/**
		 *\brief		Sets the bottom border thickness
		 *\param[in]	p_fSize	The new value
		 */
		inline void SetBottomBorderSize( double p_fSize )
		{
			m_ptBorderSize[3] = p_fSize;
			m_changed = true;
		}
		/**
		 *\brief		Sets the borders thicknesses
		 *\param[in]	p_ptSize	The new value
		 */
		inline void SetBordersSize( Point4d const & p_ptSize )
		{
			m_ptBorderSize = p_ptSize;
			m_changed = true;
		}
		/**
		 *\brief		Retrieves the left border thickness
		 *\return		The value
		 */
		inline int GetLeftBorderPixelSize()const
		{
			return m_borderSize[0];
		}
		/**
		 *\brief		Retrieves the top border thickness
		 *\return		The value
		 */
		inline int GetTopBorderPixelSize()const
		{
			return m_borderSize[1];
		}
		/**
		 *\brief		Retrieves the right border thickness
		 *\return		The value
		 */
		inline int GetRightBorderPixelSize()const
		{
			return m_borderSize[2];
		}
		/**
		 *\brief		Retrieves the bottom border thickness
		 *\return		The value
		 */
		inline int GetBottomBorderPixelSize()const
		{
			return m_borderSize[3];
		}
		/**
		 *\brief		Retrieves the borders thicknesses
		 *\return		The value
		 */
		inline Point4i const & GetBorderPixelSize()const
		{
			return m_borderSize;
		}
		/**
		 *\brief		Retrieves the borders thicknesses
		 *\return		The value
		 */
		inline Point4i & GetBordersPixelSize()
		{
			return m_borderSize;
			m_changed = true;
		}
		/**
		 *\brief		Sets the left border thickness
		 *\param[in]	p_fSize	The new value
		 */
		inline void SetLeftBorderPixelSize( int p_size )
		{
			m_borderSize[0] = p_size;
			m_changed = true;
		}
		/**
		 *\brief		Sets the top border thickness
		 *\param[in]	p_fSize	The new value
		 */
		inline void SetTopBorderPixelSize( int p_size )
		{
			m_borderSize[1] = p_size;
			m_changed = true;
		}
		/**
		 *\brief		Sets the right border thickness
		 *\param[in]	p_fSize	The new value
		 */
		inline void SetRightBorderPixelSize( int p_size )
		{
			m_borderSize[2] = p_size;
			m_changed = true;
		}
		/**
		 *\brief		Sets the bottom border thickness
		 *\param[in]	p_fSize	The new value
		 */
		inline void SetBottomBorderPixelSize( int p_size )
		{
			m_borderSize[3] = p_size;
			m_changed = true;
		}
		/**
		 *\brief		Sets the borders thicknesses
		 *\param[in]	p_ptSize	The new value
		 */
		inline void SetBordersPixelSize( Point4i const & p_size )
		{
			m_borderSize = p_size;
			m_changed = true;
		}
		/**
		 *\brief		Retrieves the border position
		 *\return		The value
		 */
		eBORDER_POSITION GetBordersPosition()const
		{
			return m_borderPosition;
		}
		/**
		 *\brief		Sets the border position
		 *\param[in]	p_position	The new value
		 */
		void SetBordersPosition( eBORDER_POSITION p_position )
		{
			m_borderPosition = p_position;
		}
		/**
		 *\brief		Sets the borders outer part UV
		 *\param[in]	val	The new value (left, top, right and bottom)
		 */
		inline void SetBordersOuterUV( Point4d const & val )
		{
			m_borderOuterUv = val;
		}
		/**
		 *\brief		Retrieves the borders outer part UV
		 *\return		The value (left, top, right and bottom)
		 */
		inline Point4d const & GetBordersOuterUV()const
		{
			return m_borderOuterUv;
		}
		/**
		 *\brief		Sets the borders inner part UV
		 *\param[in]	val	The new value (left, top, right and bottom)
		 */
		inline void SetBordersInnerUV( Point4d const & val )
		{
			m_borderInnerUv = val;
		}
		/**
		 *\brief		Retrieves the borders inner part UV
		 *\return		The value (left, top, right and bottom)
		 */
		inline Point4d const & GetBordersInnerUV()const
		{
			return m_borderInnerUv;
		}

	protected:
		/**
		 *\brief		Initialises the overlay and its buffers
		 */
		virtual void DoInitialise();
		/**
		 *\brief		Cleans the overlay and its buffers up
		 */
		virtual void DoCleanup();
		/**
		 *\brief		Draws the overlay
		 */
		virtual void DoRender();
		/**
		 *\brief		Updates the vertex buffer
		 */
		virtual void DoUpdate();
		/**
		 *\brief		Updates the overlay position and size, taking care of wanted pixel size and position
		 */
		virtual void DoUpdatePositionAndSize( Size const & p_size );

	protected:
		//! The borders geometry buffers
		std::shared_ptr< GeometryBuffersI > m_bordersGeometryBuffers;
		//! The borders material
		Material m_bordersMaterial;
		//! The border size
		Point4d m_ptBorderSize;
		//! The absolute size in pixels
		Point4i m_borderSize;
		//! The border material name
		eBORDER_POSITION m_borderPosition;
		//! The UV for the outer part of the border
		Point4d m_borderOuterUv;
		//! The UV for the inner part of the border
		Point4d m_borderInnerUv;
	};
}

#pragma warning( pop )

#endif
