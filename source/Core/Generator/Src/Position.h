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
#ifndef ___GENERATOR_POSITION_H___
#define ___GENERATOR_POSITION_H___

#include "Point.h"

namespace ProceduralTextures
{
	/*!
	@author
		Sylvain DOREMUS
	@version
		2.0.0
	@date
		16/02/2015
	@brief
		Position representation
	*/
	class Position
	{
	public:
		/** Specified constructor
		@param[in] p_x
			The first value
		@param[in] p_y
			The second value
		*/
		template< typename U, typename V >
		Position( U const & p_x, V const & p_y )
			: m_x( int32_t( p_x ) )
			, m_y( int32_t( p_y ) )
		{
		}

		/** Specified constructor
		@param[in] p_pt
			The value
		*/
		template< typename T >
		Position( Point< T, 2 > const & p_pt )
			: Position( p_pt[0], p_pt[1] )
		{
		}

		/** Default constructor
		*/
		Position()
			: Position( 0, 0 )
		{
		}

		/** Destructor
		*/
		~Position()
		{
		}

		/** Retrieves the x position
		@return
			A constant reference on the position
		*/
		inline int32_t const & x()const
		{
			return m_x;
		}

		/** Retrieves the x position
		@return
			A reference on the position
		*/
		inline int32_t & x()
		{
			return m_x;
		}

		/** Retrieves the y position
		@return
			A constant reference on the position
		*/
		inline int32_t const & y()const
		{
			return m_y;
		}

		/** Retrieves the y position
		@return
			A reference on the position
		*/
		inline int32_t & y()
		{
			return m_y;
		}

		/** Addition assignment operator
		@param[in] p_position
			The object to add
		@return
			A reference to this object
		*/
		inline Position & operator+=( const Position & p_position )
		{
			m_x += p_position.m_x;
			m_y += p_position.m_y;
			return *this;
		}

		/** Subtraction assignment operator
		@param[in] p_position
			The object to subtract
		@return
			A reference to this object
		*/
		inline Position & operator-=( const Position & p_position )
		{
			m_x -= p_position.m_x;
			m_y -= p_position.m_y;
			return *this;
		}

		/** Addition assignment operator
		@param[in] p_coord
			The value to add
		@return
			A reference to this object
		*/
		template < typename U > inline Position & operator+=( U const & p_coord )
		{
			m_x += int32_t( p_coord );
			m_y += int32_t( p_coord );
			return *this;
		}

		/** Subtraction assignment operator
		@param[in] p_coord
			The value to subtract
		@return
			A reference to this object
		*/
		template < typename U > inline Position & operator-=( U const & p_coord )
		{
			m_x -= int32_t( p_coord );
			m_y -= int32_t( p_coord );
			return *this;
		}

		/** Multiplication assignment operator
		@param[in] p_coord
			The value to multiply
		@return
			A reference to this object
		*/
		template < typename U > inline Position & operator*=( U const & p_coord )
		{
			m_x = int32_t( m_x * p_coord );
			m_y = int32_t( m_y * p_coord );
			return *this;
		}

		/** Division assignment operator
		@param[in] p_coord
			The value to divide
		@return
			A reference to this object
		*/
		template < typename U > inline Position & operator/=( U const & p_coord )
		{
			if ( p_coord != 0 )
			{
				m_x = int32_t( m_x / p_coord );
				m_y = int32_t( m_y / p_coord );
			}

			return *this;
		}

	private:
		//! The x position
		int32_t m_x;
		//! The y position
		int32_t m_y;
	};

	/** Equality operator
	@param[in] p_a, p_b
		The values to compare
	@return
		\p true if values have same dimensions and same values
	*/
	inline bool operator==( const Position & p_a, const Position & p_b )
	{
		return p_a.x() == p_b.x() && p_a.y() == p_b.y();
	}

	/** Difference operator
	@param[in] p_a, p_b
		The values to compare
	@return
		\p true if values have different dimensions or At least one different value
	*/
	inline bool operator!=( const Position & p_a, const Position & p_b )
	{
		return p_a.x() != p_b.x() || p_a.y() != p_b.y();
	}

	/** Addition operator
	@param[in] p_a, p_b
		The values to add
	@return
		The result
	*/
	inline Position operator+( const Position & p_a, const Position & p_b )
	{
		Position l_tmp( p_a );
		l_tmp += p_b;
		return l_tmp;
	}

	/** Subtraction operator
	@param[in] p_a, p_b
		The values to subtract
	@return
		The result
	*/
	inline Position operator-( const Position & p_a, const Position & p_b )
	{
		Position l_tmp( p_a );
		l_tmp -= p_b;
		return l_tmp;
	}

	/** Addition operator
	@param[in] p_position, p_coord
		The values to add
	@return
		The result
	*/
	template< typename U > inline Position operator+( const Position & p_position, U const & p_coord )
	{
		Position l_tmp( p_position );
		l_tmp += p_coord;
		return l_tmp;
	}

	/** Subtraction operator
	@param[in] p_position, p_coord
		The values to subtract
	@return
		The result
	*/
	template< typename U > inline Position operator-( const Position & p_position, U const & p_coord )
	{
		Position l_tmp( p_position );
		l_tmp -= p_coord;
		return l_tmp;
	}

	/** Multiplication operator
	@param[in] p_position, p_coord
		The values to multiply
	@return
		The result
	*/
	template< typename U > inline Position operator*( const Position & p_position, U const & p_coord )
	{
		Position l_tmp( p_position );
		l_tmp *= p_coord;
		return l_tmp;
	}

	/** Division operator
	@param[in] p_position, p_coord
		The values to divide
	@return
		The result
	*/
	template< typename U > inline Position operator/( const Position & p_position, U const & p_coord )
	{
		Position l_tmp( p_position );
		l_tmp /= p_coord;
		return l_tmp;
	}

	/** Addition operator
	@param[in] p_value, p_position
		The values to add
	@return
		The result
	*/
	inline Position operator+( int p_value, const Position & p_position )
	{
		Position l_tmp( p_position );
		l_tmp += p_value;
		return l_tmp;
	}

	/** Subtraction operator
	@param[in] p_value, p_position
		The values to subtract
	@return
		The result
	*/
	inline Position operator-( int p_value, const Position & p_position )
	{
		Position l_tmp( p_position );
		l_tmp -= p_value;
		return l_tmp;
	}

	/** Multiplication operator
	@param[in] p_value, p_position
		The values to multiply
	@return
		The result
	*/
	inline Position operator*( int p_value, const Position & p_position )
	{
		Position l_tmp( p_position );
		l_tmp *= p_value;
		return l_tmp;
	}

	/** Addition operator
	@param[in] p_value, p_position
		The values to add
	@return
		The result
	*/
	inline Position operator+( double p_value, const Position & p_position )
	{
		Position l_tmp( p_position );
		l_tmp += p_value;
		return l_tmp;
	}

	/** Subtraction operator
	@param[in] p_value, p_position
		The values to subtract
	@return
		The result
	*/
	inline Position operator-( double p_value, const Position & p_position )
	{
		Position l_tmp( p_position );
		l_tmp -= p_value;
		return l_tmp;
	}

	/** Multiplication operator
	@param[in] p_value, p_position
		The values to multiply
	@return
		The result
	*/
	inline Position operator*( double p_value, const Position & p_position )
	{
		Position l_tmp( p_position );
		l_tmp *= p_value;
		return l_tmp;
	}

	/** Computes the squared Euclidian distance from the point to the origin
	@param[in] p_a, p_b
		The two positions
	@return
		The squared Euclidian distance
	*/
	inline double GetSquaredDistance( Position const & p_a, Position const & p_b )
	{
		Position l_diff( p_a - p_b );
		return double( l_diff.x() * l_diff.x() + l_diff.y() * l_diff.y() );
	}

	/** Computes the Euclidian distance from the point to the origin
	@param[in] p_a, p_b
		The two positions
	@return
		The Euclidian distance
	*/
	inline double GetDistance( Position const & p_a, Position const & p_b = Position() )
	{
		return sqrt( GetSquaredDistance( p_a, p_b ) );
	}

	/** Computes the Manhattan distance from the point to the origin
	@param[in] p_a, p_b
		The two positions
	@return
		The Manhattan distance
	*/
	inline double GetManhattanDistance( Position const & p_a, Position const & p_b = Position() )
	{
		Position l_diff( p_a - p_b );
		return std::abs( l_diff.x() ) + std::abs( l_diff.y() );
	}

	/** Computes the Minkowski distance from the point to the origin
	@param[in] p_order
		The Minkowski order
	@param[in] p_a, p_b
		The two positions
	@return
		The Minkowski distance
	*/
	inline double GetMinkowskiDistance( double p_order, Position const & p_a, Position const & p_b = Position() )
	{
		Position l_diff( p_a - p_b );
		return std::pow( std::pow( std::abs( l_diff.x() ), p_order ) + std::pow( std::abs( l_diff.y() ), p_order ), 1.0 / p_order );
	}

	/** Computes the Chebychev distance from the point to the origin
	@param[in] p_a, p_b
		The two positions
	@return
		The Chebychev distance
	*/
	inline double GetChebychevDistance( Position const & p_a, Position const & p_b = Position() )
	{
		Position l_diff( p_a - p_b );
		return std::max( std::abs( l_diff.x() ), std::abs( l_diff.y() ) );
	}
}

#endif
