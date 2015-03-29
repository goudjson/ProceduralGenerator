/*
This source file is part of ProceduralGenerator (https://sourceforge.net/projects/proceduralgene/)

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the Free Software
Foundation; either version 2 of the License, or (At your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License along with
the program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place - Suite 330, Boston, MA 02111-1307, USA, or go to
http://www.gnu.org/copyleft/lesser.txt.
*/
#ifndef ___TFX_CPU_STEP_H___
#define ___TFX_CPU_STEP_H___

#include <CpuStep.h>

namespace TextEffects
{
	/*!
	\author		Sylvain DOREMUS
	\date		05/03/2015
	\brief		Text effects CPU step
	*/
	class CpuStep
		:	public ProceduralTextures::CpuStepBase
	{
	public:
		/**
		 *\brief		Constructor
		 *\param[in]	p_generator	The parent generator
		 *\param[in]	p_size		The dimensions
		 */
		CpuStep( std::shared_ptr< ProceduralTextures::GeneratorBase > p_generator, ProceduralTextures::Size const & p_size );
		/**
		 *\brief		Destructor
		 */
		virtual ~CpuStep();
		/**
		 *\brief		Sets the image buffer
		 *\param[in]	p_path	The new value
		 */
		void SetBackgroundImage( ProceduralTextures::PixelBuffer const & p_image );

	private:
		/**
		 *\copydoc		ProceduralTexture::CpuStep::DoInitialiseStep
		 */
		virtual void DoInitialiseStep();
		/**
		 *\copydoc		ProceduralTexture::CpuStep::DoInitialise
		 */
		virtual void DoInitialise();
		/**
		 *\copydoc		ProceduralTexture::CpuStep::DoCleanup
		 */
		virtual void DoCleanup();
		/**
		 *\copydoc		ProceduralTexture::CpuStep::DoSwapBuffers
		 */
		virtual void DoSwapBuffers();
		/**
		 *\brief		Launches the threads
		 */
		virtual void DoThreadsStart();
		/**
		 *\brief		Cleans the threads up
		 */
		virtual void DoThreadsCleanup();
	};
}

#endif
