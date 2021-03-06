#include <stdexcept>

namespace ProceduralTextures
{
	template< typename T, size_t Count1, size_t Count2, bool Inverted > struct PixelCopier;

	template< typename T > struct PixelCopier< T, 4, 0, false >
	{
		void operator()( Pixel< T > & p_pixel, const T * p_buf1, const T * /*p_buf2*/ )
		{
			memcpy( &p_pixel.r, p_buf1, 4 * sizeof( T ) );
		}
	};

	template< typename T > struct PixelCopier< T, 3, 1, false >
	{
		void operator()( Pixel< T > & p_pixel, const T * p_buf1, const T * p_buf2 )
		{
			memcpy( &p_pixel.r, p_buf1, 3 * sizeof( T ) );
			p_pixel.a = T( p_buf2[0] );
		}
	};

	template< typename T > struct PixelCopier< T, 3, 0, false >
	{
		void operator()( Pixel< T > & p_pixel, const T * p_buf1, const T * /*p_buf2*/ )
		{
			memcpy( &p_pixel.r, p_buf1, 3 * sizeof( T ) );
			p_pixel.a = std::numeric_limits< T >::max();
		}
	};

	template< typename T > struct PixelCopier< T, 0, 3, false >
	{
		void operator()( Pixel< T > & p_pixel, const T * /*p_buf1*/, const T * p_buf2 )
		{
			p_pixel.a = std::numeric_limits< T >::max();
			memcpy( &p_pixel.r, p_buf2, 3 * sizeof( T ) );
		}
	};

	template< typename T > struct PixelCopier< T, 1, 3, false >
	{
		void operator()( Pixel< T > & p_pixel, const T * p_buf1, const T * p_buf2 )
		{
			p_pixel.a = T( p_buf1[0] );
			memcpy( &p_pixel.r, p_buf2, 3 * sizeof( T ) );
		}
	};

	template< typename T > struct PixelCopier< T, 0, 4, false >
	{
		void operator()( Pixel< T > & p_pixel, const T * /*p_buf1*/, const T * p_buf2 )
		{
			p_pixel.a = T( p_buf2[0] );
			memcpy( &p_pixel.r, & p_buf2[1], 3 * sizeof( T ) );
		}
	};

	template< typename T > struct PixelCopier< T, 4, 0, true >
	{
		void operator()( Pixel< T > & p_pixel, const T * p_buf1, const T * /*p_buf2*/ )
		{
			p_pixel.a = T( p_buf1[0] );
			p_pixel.b = T( p_buf1[1] );
			p_pixel.g = T( p_buf1[2] );
			p_pixel.r = T( p_buf1[3] );
		}
	};

	template< typename T > struct PixelCopier< T, 3, 1, true >
	{
		void operator()( Pixel< T > & p_pixel, const T * p_buf1, const T * p_buf2 )
		{
			p_pixel.b = T( p_buf1[0] );
			p_pixel.g = T( p_buf1[1] );
			p_pixel.r = T( p_buf1[2] );
			p_pixel.a = T( p_buf2[0] );
		}
	};

	template< typename T > struct PixelCopier< T, 3, 0, true >
	{
		void operator()( Pixel< T > & p_pixel, const T * p_buf1, const T * /*p_buf2*/ )
		{
			p_pixel.b = T( p_buf1[0] );
			p_pixel.g = T( p_buf1[1] );
			p_pixel.r = T( p_buf1[2] );
			p_pixel.a = std::numeric_limits< T >::max();
		}
	};

	template< typename T > struct PixelCopier< T, 0, 3, true >
	{
		void operator()( Pixel< T > & p_pixel, const T * /*p_buf1*/, const T * p_buf2 )
		{
			p_pixel.b = T( p_buf2[0] );
			p_pixel.g = T( p_buf2[1] );
			p_pixel.r = T( p_buf2[2] );
			p_pixel.a = std::numeric_limits< T >::max();
		}
	};

	template< typename T > struct PixelCopier< T, 1, 3, true >
	{
		void operator()( Pixel< T > & p_pixel, const T * p_buf1, const T * p_buf2 )
		{
			p_pixel.b = T( p_buf2[0] );
			p_pixel.g = T( p_buf2[1] );
			p_pixel.r = T( p_buf2[2] );
			p_pixel.a = T( p_buf1[0] );
		}
	};

	template< typename T > struct PixelCopier< T, 0, 4, true >
	{
		void operator()( Pixel< T > & p_pixel, const T * /*p_buf1*/, const T * p_buf2 )
		{
			p_pixel.a = T( p_buf2[0] );
			p_pixel.b = T( p_buf2[1] );
			p_pixel.g = T( p_buf2[2] );
			p_pixel.r = T( p_buf2[3] );
		}
	};
	
	template< typename T, typename U, size_t Count1, size_t Count2, bool InvertedX, bool InvertedY, typename Enable=void > struct BufferCopier;

	template< typename T, typename U, size_t Count1, size_t Count2, bool InvertedX, bool InvertedY >
	struct BufferCopier< T, U, Count1, Count2, InvertedX, InvertedY, typename std::enable_if< Count1 + Count2 < sizeof( T ) >::type >
	{
		void operator()( Buffer< T > * p_pBuffer, const U * p_pBuffer1, const U * p_pBuffer2 )
		{
			throw std::invalid_argument( "Count1 + Count2 must be equal to sizeof( T )" );
		}
	};

	template< typename T, typename U, size_t Count1, size_t Count2, bool InvertedX >
	struct BufferCopier< T, U, Count1, Count2, InvertedX, false, typename std::enable_if< sizeof( T ) <= Count1 + Count2 >::type >
	{
		void operator()( Buffer< T > * p_pBuffer, const U * p_pBuffer1, const U * p_pBuffer2 )
		{
			size_t l_uiCount = p_pBuffer->GetElementsCount();
			size_t l_uiCount1 = 0;
			size_t l_uiCount2 = 0;
			U * l_pBuffer1 = const_cast< U * >( & p_pBuffer1[l_uiCount1] );
			U * l_pBuffer2 = const_cast< U * >( & p_pBuffer2[l_uiCount2] );
			PixelCopier< U, Count1, Count2, InvertedX > l_copier;

			for ( size_t i = 0; i < l_uiCount; i++ )
			{
				l_copier( p_pBuffer->Ptr()[i], l_pBuffer1, l_pBuffer2 );
				l_pBuffer1 += Count1;
				l_pBuffer2 += Count2;
			}
		}
	};

	template< typename T, typename U, size_t Count1, size_t Count2, bool InvertedX >
	struct BufferCopier< T, U, Count1, Count2, InvertedX, true, typename std::enable_if< sizeof( T ) <= Count1 + Count2 >::type >
	{
		void operator()( Buffer< T > * p_pBuffer, const U * p_pBuffer1, const U * p_pBuffer2 )
		{
			size_t l_uiCount = p_pBuffer->GetElementsCount();
			size_t l_uiCount1 = ( l_uiCount - 2 ) * Count1;
			size_t l_uiCount2 = ( l_uiCount - 2 ) * Count2;
			U * l_pBuffer1 = const_cast< U * >( & p_pBuffer1[l_uiCount1] );
			U * l_pBuffer2 = const_cast< U * >( & p_pBuffer2[l_uiCount2] );
			PixelCopier< U, Count1, Count2, InvertedX > l_copier;

			for ( size_t i = 0; i < l_uiCount; i++ )
			{
				l_copier( p_pBuffer->Ptr()[i], l_pBuffer1, l_pBuffer2 );
				l_pBuffer1 -= Count1;
				l_pBuffer2 -= Count2;
			}
		}
	};

	//*************************************************************************************************

	template< typename T >
	Pixel< T >::Pixel()
		: r( 0 )
		, g( 0 )
		, b( 0 )
		, a( 0 )
	{
	}

	template< typename T >
	template< typename U >
	Pixel< T >::Pixel( U p_r, U p_g, U p_b, U p_a )
		: r( T( p_r ) )
		, g( T( p_g ) )
		, b( T( p_b ) )
		, a( T( p_a ) )
	{
	}

	template< typename T >
	template< typename U >
	Pixel< T >::Pixel( const Pixel< U > & p_pxl )
		: r( T( p_pxl.r ) )
		, g( T( p_pxl.g ) )
		, b( T( p_pxl.b ) )
		, a( T( p_pxl.a ) )
	{
	}

	template< typename T >
	template< typename U >
	Pixel< T > & Pixel< T >::operator=( const Pixel< U > & p_pxl )
	{
		r = T( p_pxl.r );
		g = T( p_pxl.g );
		b = T( p_pxl.b );
		a = T( p_pxl.a );
		return * this;
	}

	template< typename T >
	template< typename U >
	Pixel< T > & Pixel< T >::operator+=( const Pixel< U > & p_px )
	{
		r = T( U( r ) + p_px.r );
		g = T( U( g ) + p_px.g );
		b = T( U( b ) + p_px.b );
		a = T( U( a ) + p_px.a );
		return * this;
	}

	template< typename T >
	template< typename U >
	Pixel< T > & Pixel< T >::operator-=( const Pixel< U > & p_px )
	{
		r = T( U( r ) - p_px.r );
		g = T( U( g ) - p_px.g );
		b = T( U( b ) - p_px.b );
		a = T( U( a ) - p_px.a );
		return * this;
	}

	template< typename T >
	template< typename U >
	Pixel< T > & Pixel< T >::operator*=( const Pixel< U > & p_px )
	{
		r = T( U( r ) * p_px.r );
		g = T( U( g ) * p_px.g );
		b = T( U( b ) * p_px.b );
		a = T( U( a ) * p_px.a );
		return * this;
	}

	template< typename T >
	template< typename U >
	Pixel< T > & Pixel< T >::operator/=( const Pixel< U > & p_px )
	{
		r = ( p_px.r == 0 ? r : T( U( r ) / p_px.r ) );
		g = ( p_px.g == 0 ? g : T( U( g ) / p_px.g ) );
		b = ( p_px.b == 0 ? b : T( U( b ) / p_px.b ) );
		a = ( p_px.a == 0 ? a : T( U( a ) / p_px.a ) );
		return * this;
	}

	template< typename T >
	template< typename U >
	Pixel< T > & Pixel< T >::operator+=( U const & p_t )
	{
		r = T( U( r ) + p_t );
		g = T( U( g ) + p_t );
		b = T( U( b ) + p_t );
		a = T( U( a ) + p_t );
		return * this;
	}

	template< typename T >
	template< typename U >
	Pixel< T > & Pixel< T >::operator-=( U const & p_t )
	{
		r = T( U( r ) - p_t );
		g = T( U( g ) - p_t );
		b = T( U( b ) - p_t );
		a = T( U( a ) - p_t );
		return * this;
	}

	template< typename T >
	template< typename U >
	Pixel< T > & Pixel< T >::operator*=( U const & p_t )
	{
		r = T( U( r ) * p_t );
		g = T( U( g ) * p_t );
		b = T( U( b ) * p_t );
		a = T( U( a ) * p_t );
		return * this;
	}

	template< typename T >
	template< typename U >
	Pixel< T > & Pixel< T >::operator/=( U const & p_t )
	{
		r = ( p_t == 0 ? r : T( U( r ) / p_t ) );
		g = ( p_t == 0 ? g : T( U( g ) / p_t ) );
		b = ( p_t == 0 ? b : T( U( b ) / p_t ) );
		a = ( p_t == 0 ? a : T( U( a ) / p_t ) );
		return * this;
	}

	template< typename T >
	Pixel< T > & Pixel< T >::operator>>=( size_t p_t )
	{
		r >>= p_t;
		g >>= p_t;
		b >>= p_t;
		a >>= p_t;
		return * this;
	}

	template< typename T >
	Pixel< T > & Pixel< T >::operator<<=( size_t p_t )
	{
		r <<= p_t;
		g <<= p_t;
		b <<= p_t;
		a <<= p_t;
		return * this;
	}

	template< typename T >
	template< typename U >
	void Pixel< T >::Set( U p_r, U p_g, U p_b, U p_a )
	{
		r = T( p_r );
		g = T( p_g );
		b = T( p_b );
		a = T( p_a );
	}

	template< typename T >
	template< typename U >
	void Pixel< T >::Set( const Pixel< U > & p_px )
	{
		r = T( p_px.r );
		g = T( p_px.g );
		b = T( p_px.b );
		a = T( p_px.a );
	}

	template< typename T >
	template < size_t Count1, size_t Count2 >
	void Pixel< T >::Set( const T * p_pBuffer1, const T * p_pBuffer2 )
	{
		PixelCopier< T, Count1, Count2, false >()( * this, p_pBuffer1, p_pBuffer2 );
	}

	template< typename T >
	template< typename U >
	U Pixel< T >::Sum()const
	{
		return abs( U( r ) + U( g ) + U( b ) );
	}

	//*************************************************************************************************

	template< typename T, typename U >
	bool operator==( const Pixel< T > & p_pixel, const Pixel< U > & p_pxl )
	{
		return p_pixel.r == T( p_pxl.r ) && p_pixel.g == T( p_pxl.g ) && p_pixel.b == T( p_pxl.b ) && p_pixel.a == T( p_pxl.a );
	}

	template< typename T, typename U >
	Pixel< T > operator+( const Pixel< T > & p_pixel, const Pixel< U > & p_px )
	{
		Pixel< T > l_pxReturn( p_pixel );
		l_pxReturn += p_px;
		return l_pxReturn;
	}

	template< typename T, typename U >
	Pixel< T > operator-( const Pixel< T > & p_pixel, const Pixel< U > & p_px )
	{
		Pixel< T > l_pxReturn( p_pixel );
		l_pxReturn -= p_px;
		return l_pxReturn;
	}

	template< typename T, typename U >
	Pixel< T > operator*( const Pixel< T > & p_pixel, const Pixel< U > & p_px )
	{
		Pixel< T > l_pxReturn( p_pixel );
		l_pxReturn *= p_px;
		return l_pxReturn;
	}

	template< typename T, typename U >
	Pixel< T > operator/( const Pixel< T > & p_pixel, const Pixel< U > & p_px )
	{
		Pixel< T > l_pxReturn( p_pixel );
		l_pxReturn /= p_px;
		return l_pxReturn;
	}

	template< typename T, typename U >
	Pixel< T > operator+( const Pixel< T > & p_pixel, U const & p_t )
	{
		Pixel< T > l_pxReturn( p_pixel );
		l_pxReturn += p_t;
		return l_pxReturn;
	}

	template< typename T, typename U >
	Pixel< T > operator-( const Pixel< T > & p_pixel, U const & p_t )
	{
		Pixel< T > l_pxReturn( p_pixel );
		l_pxReturn -= p_t;
		return l_pxReturn;
	}

	template< typename T, typename U >
	Pixel< T > operator*( const Pixel< T > & p_pixel, U const & p_t )
	{
		Pixel< T > l_pxReturn( p_pixel );
		l_pxReturn *= p_t;
		return l_pxReturn;
	}

	template< typename T, typename U >
	Pixel< T > operator/( const Pixel< T > & p_pixel, U const & p_t )
	{
		Pixel< T > l_pxReturn( p_pixel );
		l_pxReturn /= p_t;
		return l_pxReturn;
	}

	template< typename T, typename U >
	Pixel< U > operator+( U const & p_t, const Pixel< T > & p_pixel )
	{
		Pixel< U > l_pxReturn( p_pixel );
		l_pxReturn += p_t;
		return l_pxReturn;
	}

	template< typename T, typename U >
	Pixel< U > operator-( U const & p_t, const Pixel< T > & p_pixel )
	{
		Pixel< U > l_pxReturn( p_pixel );
		l_pxReturn -= p_t;
		return l_pxReturn;
	}

	template< typename T, typename U >
	Pixel< U > operator*( U const & p_t, const Pixel< T > & p_pixel )
	{
		Pixel< U > l_pxReturn( p_pixel );
		l_pxReturn *= p_t;
		return l_pxReturn;
	}

	template< typename T, typename U >
	Pixel< U > operator/( U const & p_t, const Pixel< T > & p_pixel )
	{
		Pixel< U > l_pxReturn( p_pixel );
		l_pxReturn /= p_t;
		return l_pxReturn;
	}
}
