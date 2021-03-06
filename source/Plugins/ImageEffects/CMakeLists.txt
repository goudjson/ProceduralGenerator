project( ImageEffects )
include_directories( ${CMAKE_SOURCE_DIR}/Core/Generator/Src )

set( BinsDependencies
	${BinsDependencies}
	ImageEffects
	PARENT_SCOPE
)

set( IFX_VERSION_MAJOR	2 )
set( IFX_VERSION_MINOR	0 )
set( IFX_VERSION_BUILD	1 )

add_target(
	ImageEffects
	plugin
	"Generator"
	"Generator;${OPT_LINKS}"
	"PrecompiledHeader.h"
	"PrecompiledHeader.cpp"
	"${wxWidgets_CFLAGS}"
	"${wxWidgets_CXXFLAGS}"
)

copy_languages( ImageEffects ../internationalisation ProceduralGenerator "fr" )
set( Build "yes (version ${IFX_VERSION_MAJOR}.${IFX_VERSION_MINOR}.${IFX_VERSION_BUILD})" PARENT_SCOPE )
add_target_astyle( ImageEffects ".h;.inl;.hpp;.c;.cpp" )
set_property( TARGET ImageEffects PROPERTY FOLDER "Plugins" )
