#include "ShaderEffects.h"

namespace ShaderEffects
{
	namespace
	{
		/*!
		@author
			Sylvain DOREMUS
		@date
			23/05/2012
		@brief
			The controls IDs
		*/
		typedef enum
		{
			eID_ANY = -1,
			eID_IMAGEPATH = 52,
			eID_SEPTYPE = 53,
			eID_SEPOFFSET = 54,
			eID_RESETTIME = 55,
			eID_SHADERS = 56,
			eID_REMOVE = 57,
			eID_VERTEXFILE = 58,
			eID_FRAGMENTFILE = 59,
			eID_COMPILE = 60,
			eID_COMPILERLOG = 61,
			eID_HELP_OPEN = 62,
			eID_HELP_CLOSE = 63,
		}	eID;
	}

	Generator::Generator()
		: ProceduralTextures::Generator< CpuStep, GpuStep >( true, ProceduralTextures::DEFAULT_FRAME_TIME )
	{
	}

	Generator::~Generator()
	{
	}

	void Generator::DoCreate( ProceduralTextures::Size const & p_size, ProceduralTextures::Size const & p_bordersSize )
	{
		m_cpuStep = std::make_shared< CpuStep >( shared_from_this(), p_size );
		m_gpuStep = std::make_shared< GpuStep >( shared_from_this(), p_size, p_bordersSize );
	}

	void Generator::DoDestroy()
	{
		m_cpuStep.reset();
		m_gpuStep.reset();
	}

	void Generator::DoGeneratePanel()
	{
		using namespace ProceduralTextures;

		String l_sepChoices[] =
		{
			_( "Not separated" ),
			_( "Horizontally" ),
			_( "Vertically" ),
		};
		String l_shaChoices[] =
		{
			_( "Shader 1" ),
			_( "New..." ),
		};
		String l_helpText = _( "Vertex attributes filled by ProceduralGenerator:" ) + _T( "\n" )
			+ _T( " - vertex: vec2 - \n    " ) + _( "Vertex position" ) + _T( "\n" )
			+ _T( " - texture: vec2 - \n    " ) + _( "Vertex texture coordinates" ) + _T( "\n" )
			+ _T( "\n" )
			+ _( "Addiditonal uniform variables added by ProceduralGenerator:" ) + _T( "\n" )
			+ _T( " - pg_width: int - \n    " ) + _( "Window width" ) + _T( "\n" )
			+ _T( " - pg_height: int - \n    " ) + _( "Window height" ) + _T( "\n" )
			+ _T( " - pg_time: int - \n    " ) + _( "Elapsed time, in ms" ) + _T( "\n" )
			+ _T( " - pg_sep_type: int - \n    " ) + _( "Separation type" ) + _T( "\n" )
			+ _T( "       0 =>" ) + _( "Not separated" ) + _T( "\n" )
			+ _T( "       1 =>" ) + _( "Horizontally" ) + _T( "\n" )
			+ _T( "       2 =>" ) + _( "Vertically" ) + _T( "\n" )
			+ _T( " - pg_texture: sampler2D - \n    " ) + _( "Selected texture" ) + _T( "\n" );

		uint32_t l_index = 0;

		m_buttonHelpOpen = std::make_shared< ButtonCtrl >( m_options, _( "PGEN GLSL Help" ), eID_HELP_OPEN, Position( 10, 10 + DEFAULT_HEIGHT * l_index++ ), Size( CONFIG_PANEL_WIDTH - 20, DEFAULT_HEIGHT ), 0, true );
		m_buttonHelpOpen->Connect( eBUTTON_EVENT_CLICKED, std::bind( &Generator::OnHelpOpen, this ) );
		m_panelHelp = std::make_shared< StaticCtrl >( nullptr, l_helpText, Position( CONFIG_PANEL_WIDTH, 0 ), Size( 200, CONFIG_PANEL_HEIGHT ), eSTATIC_STYLE_VALIGN_TOP | eSTATIC_STYLE_HALIGN_LEFT, false );
		m_buttonHelpClose = std::make_shared< ButtonCtrl >( m_panelHelp, _( "X" ), eID_HELP_CLOSE, Position( CONFIG_PANEL_WIDTH - 30, 10 ), Size( 20, 20 ), 0, false );
		m_buttonHelpClose->Connect( eBUTTON_EVENT_CLICKED, std::bind( &Generator::OnHelpClose, this ) );

		m_buttonImage = std::make_shared< ButtonCtrl >( m_options, _( "Image" ), eID_IMAGEPATH, Position( 10, 10 + DEFAULT_HEIGHT * l_index++ ), Size( CONFIG_PANEL_WIDTH -  20, DEFAULT_HEIGHT ) );
		m_buttonImage->Connect( eBUTTON_EVENT_CLICKED, std::bind( &Generator::OnImage, this ) );
		m_staticSeparator = std::make_shared< StaticCtrl >( m_options, _( "Separation" ), Position( 10, 10 + DEFAULT_HEIGHT * l_index++ ), Size( CONFIG_PANEL_WIDTH -  20, DEFAULT_HEIGHT ), eSTATIC_STYLE_VALIGN_CENTER | eSTATIC_STYLE_HALIGN_CENTER, false );
		m_comboSeparator = std::make_shared< ComboBoxCtrl >( m_options, l_sepChoices, 0, eID_SEPTYPE, Position( 10, 10 + DEFAULT_HEIGHT * l_index++ ), Size( CONFIG_PANEL_WIDTH -  20, DEFAULT_HEIGHT ), eCOMBO_STYLE_READONLY, false );
		m_comboSeparator->Connect( eCOMBOBOX_EVENT_SELECTED, std::bind( &Generator::OnSepType, this, std::placeholders::_1 ) );
		m_sliderOffset = std::make_shared< SliderCtrl >( m_options, Range( 0, 100 ), 50, eID_SEPOFFSET, Position( 10, 10 + DEFAULT_HEIGHT * l_index++ ), Size( CONFIG_PANEL_WIDTH -  20, DEFAULT_HEIGHT ), 0, false );
		m_sliderOffset->Connect( eSLIDER_EVENT_THUMBRELEASE, std::bind( &Generator::OnSepOffset, this, std::placeholders::_1 ) );
		m_sliderOffset->Connect( eSLIDER_EVENT_THUMBTRACK, std::bind( &Generator::OnSepOffset, this, std::placeholders::_1 ) );
		m_buttonReset = std::make_shared< ButtonCtrl >( m_options, _( "Reset Time" ), eID_RESETTIME, Position( 10, 10 + DEFAULT_HEIGHT * l_index++ ), Size( CONFIG_PANEL_WIDTH -  20, DEFAULT_HEIGHT ), 0, false );
		m_buttonReset->Connect( eBUTTON_EVENT_CLICKED, std::bind( &Generator::OnResetTime, this ) );
		m_staticShaders = std::make_shared< StaticCtrl >( m_options, _( "Shaders" ), Position( 10, 10 + DEFAULT_HEIGHT * l_index++ ), Size( CONFIG_PANEL_WIDTH -  20, DEFAULT_HEIGHT ), eSTATIC_STYLE_VALIGN_CENTER | eSTATIC_STYLE_HALIGN_CENTER, false );
		m_comboShaders = std::make_shared< ComboBoxCtrl >( m_options, l_shaChoices, -1, eID_SHADERS, Position( 10, 10 + DEFAULT_HEIGHT * l_index++ ), Size( CONFIG_PANEL_WIDTH -  20, DEFAULT_HEIGHT ), eCOMBO_STYLE_READONLY, false );
		m_comboShaders->Connect( eCOMBOBOX_EVENT_SELECTED, std::bind( &Generator::OnSelectShader, this, std::placeholders::_1 ) );
		m_buttonVertexFile = std::make_shared< ButtonCtrl >( m_options, _( "Vertex" ), eID_VERTEXFILE, Position( 10, 10 + DEFAULT_HEIGHT * l_index++ ), Size( CONFIG_PANEL_WIDTH -  20, DEFAULT_HEIGHT ), 0, false );
		m_buttonVertexFile->Connect( eBUTTON_EVENT_CLICKED, std::bind( &Generator::OnVertexShaderPath, this ) );
		m_buttonFragmentFile = std::make_shared< ButtonCtrl >( m_options, _( "Pixel" ), eID_FRAGMENTFILE, Position( 10, 10 + DEFAULT_HEIGHT * l_index++ ), Size( CONFIG_PANEL_WIDTH -  20, DEFAULT_HEIGHT ), 0, false );
		m_buttonFragmentFile->Connect( eBUTTON_EVENT_CLICKED, std::bind( &Generator::OnFragmentShaderPath, this ) );
		m_buttonCompile = std::make_shared< ButtonCtrl >( m_options, _( "Compile" ), eID_COMPILE, Position( 10, 10 + DEFAULT_HEIGHT * l_index++ ), Size( CONFIG_PANEL_WIDTH -  20, DEFAULT_HEIGHT ), 0, false );
		m_buttonCompile->Connect( eBUTTON_EVENT_CLICKED, std::bind( &Generator::OnShaderCompile, this ) );
		m_buttonCompilerLog = std::make_shared< ButtonCtrl >( m_options, _( "Compiler log" ), eID_COMPILERLOG, Position( 10, 10 + DEFAULT_HEIGHT * l_index++ ), Size( CONFIG_PANEL_WIDTH -  20, DEFAULT_HEIGHT ), 0, false );
		m_buttonCompilerLog->Connect( eBUTTON_EVENT_CLICKED, std::bind( &Generator::OnCompilerLog, this ) );
		m_buttonRemove = std::make_shared< ButtonCtrl >( m_options, _( "Remove" ), eID_REMOVE, Position( 10, 10 + DEFAULT_HEIGHT * l_index++ ), Size( CONFIG_PANEL_WIDTH -  20, DEFAULT_HEIGHT ), 0, false );
		m_buttonRemove->Connect( eBUTTON_EVENT_CLICKED, std::bind( &Generator::OnRemove, this ) );

		m_arrayControls.push_back( m_buttonHelpOpen );
		m_arrayControls.push_back( m_panelHelp );
		m_arrayControls.push_back( m_buttonHelpClose );
		m_arrayControls.push_back( m_buttonImage );
		m_arrayControls.push_back( m_staticSeparator );
		m_arrayControls.push_back( m_comboSeparator );
		m_arrayControls.push_back( m_sliderOffset );
		m_arrayControls.push_back( m_buttonReset );
		m_arrayControls.push_back( m_staticShaders );
		m_arrayControls.push_back( m_comboShaders );
		m_arrayControls.push_back( m_buttonVertexFile );
		m_arrayControls.push_back( m_buttonFragmentFile );
		m_arrayControls.push_back( m_buttonCompile );
		m_arrayControls.push_back( m_buttonCompilerLog );
		m_arrayControls.push_back( m_buttonRemove );
	}

	void Generator::OnResetTime()
	{
		m_gpuStep->ResetTime();
	}

	void Generator::OnSepType( int p_value )
	{
		m_gpuStep->SetSepType( eSEPARATION( p_value ) );

		if ( p_value )
		{
			m_sliderOffset->Show();
		}
		else
		{
			m_sliderOffset->Hide();
		}
	}

	void Generator::OnSepOffset( int p_value )
	{
		m_gpuStep->SetSepOffset( p_value );
	}

	void Generator::OnSelectShader( uint32_t p_value )
	{
		if ( p_value == m_comboShaders->GetItemCount() - 1 )
		{
			m_gpuStep->AddEffect();
			ProceduralTextures::StringStream l_strPage;
			l_strPage << _T( "Shader " );
			l_strPage << m_comboShaders->GetItemCount();
			m_comboShaders->SetItemText( p_value, l_strPage.str() );
			m_comboShaders->AppendItem( _( "New..." ) );
			m_comboShaders->SetSelected( p_value );
		}
		else if ( p_value >= 0 )
		{
			m_comboShaders->SetSelected( p_value );
			m_buttonRemove->Show();
		}
		else
		{
			m_comboShaders->SetSelected( -1 );
			m_buttonRemove->Hide();
		}

		if ( p_value < m_comboShaders->GetItemCount() )
		{
			m_buttonVertexFile->Show();
			m_buttonFragmentFile->Show();
			m_gpuStep->SelectEffect( p_value );
		}
		else
		{
			m_buttonVertexFile->Hide();
			m_buttonFragmentFile->Hide();
		}
	}

	void Generator::OnRemove()
	{
		size_t l_uiToRemove = size_t( m_comboShaders->GetSelected() );

		if ( l_uiToRemove > 0 && l_uiToRemove < m_comboShaders->GetItemCount() - 1 )
		{
			m_gpuStep->RemoveEffect();
			m_comboShaders->RemoveItem( int( l_uiToRemove ) );
			m_buttonVertexFile->Hide();
			m_buttonFragmentFile->Hide();
			m_buttonCompile->Hide();
			m_buttonCompilerLog->Hide();
			m_buttonRemove->Hide();
		}
	}

	void Generator::OnShaderCompile()
	{
		m_gpuStep->CompileEffect();
		m_buttonCompile->Hide();
		m_buttonCompilerLog->Show();
	}

	void Generator::OnCompilerLog()
	{
		ShowMessageBox( _( "Compile and Link result" ), m_gpuStep->GetCompilerLog() );
	}

	void Generator::OnVertexShaderPath()
	{
		ProceduralTextures::String l_path;

		if ( OpenFile( l_path, _( "Choose a vertex shader file" ), _( "Vertex shader GLSL files (*.glsl;*.vert)|*.glsl;*.vert" ) ) )
		{
			size_t l_index = size_t( m_comboShaders->GetSelected() );

			if ( l_index < m_comboShaders->GetItemCount() - 1 && !l_path.empty() )
			{
				m_buttonCompile->Show();
				m_buttonCompilerLog->Hide();
				m_gpuStep->SetVertexShaderPath( l_path );
			}
		}
	}

	void Generator::OnFragmentShaderPath()
	{
		ProceduralTextures::String l_path;

		if ( OpenFile( l_path, _( "Choose a fragment shader file" ), _( "Fragment shader GLSL files (*.glsl;*.frag)|*.glsl;*.frag" ) ) )
		{
			size_t l_index = size_t( m_comboShaders->GetSelected() );

			if ( l_index < m_comboShaders->GetItemCount() - 1 && !l_path.empty() )
			{
				m_buttonCompile->Show();
				m_buttonCompilerLog->Hide();
				m_gpuStep->SetFragmentShaderPath( l_path );
			}
		}
	}

	void Generator::OnImage()
	{
		ProceduralTextures::PixelBuffer l_image;

		if ( SelectImage( l_image ) )
		{
			Resize( l_image.GetDimensions() );
			m_cpuStep->SetImage( l_image );
			m_gpuStep->SetImage( l_image );
			m_staticSeparator->Show();
			m_sliderOffset->Show();
			m_buttonReset->Show();
			m_comboSeparator->Show();
			m_staticShaders->Show();
			m_comboShaders->Show();

			if ( m_comboShaders->GetSelected() == -1 )
			{
				m_comboShaders->SetSelected( m_comboShaders->GetItemCount() - 2 );
			}
		}
	}

	void Generator::OnHelpOpen()
	{
		m_panelHelp->Show();
		m_buttonHelpClose->Show();
	}

	void Generator::OnHelpClose()
	{
		m_buttonHelpClose->Hide();
		m_panelHelp->Hide();
	}
}
