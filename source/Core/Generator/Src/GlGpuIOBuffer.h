/*
This source file is part of ProceduralGenerator (https://sourceforge.net/projects/proceduralgene/ )

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (At your option ) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
the program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
*/
#ifndef ___GENERATOR_GL_PIXEL_BUFFER_H___
#define ___GENERATOR_GL_PIXEL_BUFFER_H___

#include "GlBufferObject.h"

#include "Vertex.h"

namespace ProceduralTextures
{
namespace gl
{
	/*!
	@author
		Sylvain DOREMUS
	@date
		14/02/2010
	@brief
		Base class for pixel transfer buffers
	*/
	class GeneratorAPI GpuIOBuffer
	{
	public:
		/** Constructor
		@param[in] p_openGl
			The OpenGL instance
		@param[in] p_packMode
			The pixel transfer direction (pack or unpack)
		@param[in] p_drawMode
			The buffer mode (GL_STATIC_DRAW, ...)
		*/
		GpuIOBuffer( OpenGl & p_openGl, unsigned int p_packMode, unsigned int p_drawMode );

		/** Destructor
		*/
		~GpuIOBuffer();

		/** Creates and initialises the buffer
		@param[in] p_size
			The buffer size
		@return
			true if it is successfully initialised
		*/
		bool Initialise( size_t p_size );

		/** Destroys the buffer
		*/
		void Cleanup();

		/** Tries to activate the buffer
		@return
			true if it is successfully activated
		*/
		bool Bind();

		/** Deactivates the buffer
		*/
		void Unbind();

		/** Updates the buffer data on GPU
		@param[in] p_buffer
			The buffer data
		@param[in] p_size
			The buffer size
		*/
		void Data( void const * p_buffer, size_t p_size );

		/** Maps the buffer data into RAM memory
		@param[in] p_access
			The memory access
		@return
			The mapped memory
		*/
		void * Lock( unsigned int p_access );

		/** Unmaps the buffer data from RAM memory
		*/
		void Unlock();

	private:
		//! The OpenGL buffer object
		BufferObject m_bufferObject;
	};
}
}

#endif
