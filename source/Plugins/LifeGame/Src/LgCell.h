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
#ifndef ___LG_CELL_H___
#define ___LG_CELL_H___

#include <Pixel.h>

namespace LifeGame
{
	struct Cell
	{
		Cell();
		~Cell();

		void Set( ProceduralTextures::UbPixel * p_pixel, int p_alive );
		void Die();
		void Live();
		void SetAlive( int p_alive );
		int CountAliveNeighbours();

		ProceduralTextures::UbPixel * m_pixel;
		std::array< Cell *, 8 > m_neighbours;
		int m_alive;
	};
}

#endif
