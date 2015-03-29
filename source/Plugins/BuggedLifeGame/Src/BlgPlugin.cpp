#include "BlgPlugin.h"

using namespace ProceduralTextures;

namespace BuggedLifeGame
{
	IMPLEMENT_PLUGIN( Plugin, Generator )

	Plugin::Plugin()
		:	ProceduralTextures::Plugin< Generator, Plugin >( _T( "BuggedLifeGame" ) )
	{
	}

	Plugin::~Plugin()
	{
	}

	String Plugin::GetName()
	{
		String l_strBaseName = _( "Bugged Life Game" );
#if !defined( NDEBUG )
		l_strBaseName += _T( " (Debug )" );
#endif
		return l_strBaseName;
	}
}
