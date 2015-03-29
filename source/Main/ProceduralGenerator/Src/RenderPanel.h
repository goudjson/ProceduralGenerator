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
#ifndef ___Pg_RenderPanel___
#define ___Pg_RenderPanel___

#pragma warning( push )
#pragma warning( disable:4996 )
#include <wx/timer.h>
#include <wx/glcanvas.h>
#pragma warning( pop )

#include <GeneratorPrerequisites.h>
#include <GeneratorSignal.h>

#if defined( PGEN_FFMPEG )
#	define USE_STREAMS 0
extern "C"
{
#	include <libavutil/opt.h>
#	include <libavcodec/avcodec.h>
#	include <libavformat/avformat.h>
#	include <libavutil/common.h>
#	include <libavutil/imgutils.h>
#	include <libavutil/mathematics.h>
#	include <libavutil/samplefmt.h>
#	include <libswscale/swscale.h>
#	include <libswresample/swresample.h>
}
#elif defined( PGEN_OCV )
#	include <opencv2/opencv.hpp>
#endif

#undef _
#define _( x ) wxString( ProceduralTextures::Translator::TranslateString( _T( x ) ).c_str(), wxConvUTF8 )

namespace ProceduralGenerator
{
	class wxStatusUpdateEvent;
	class MainFrame;

	const int eID_TIMER = 3465;

	class RenderPanel
		: public wxGLCanvas
	{
	public:
		RenderPanel( MainFrame * m_pFrame, int * p_attribList, wxPoint const & p_position, wxSize const & p_size );
		~RenderPanel();

		void SetGenerator( std::shared_ptr< ProceduralTextures::GeneratorBase > p_pGenerator );
		std::shared_ptr< ProceduralTextures::GeneratorBase > GetGenerator()const;
		void SaveFrame();
		void Render();
#if defined( PGEN_RECORDS )
		bool StartRecord();
		bool IsRecording();
		void StopRecord();
#endif

	private:
		void DoStopGenerator();
		void DoRender();

		DECLARE_EVENT_TABLE();
		void OnPaint( wxPaintEvent & p_event );
		void OnSize( wxSizeEvent & p_event );
		void OnTimer( wxTimerEvent & p_event );
		void OnClose( wxCloseEvent & p_event );
		void OnKeyDown( wxKeyEvent & p_event );
		void OnKeyUp( wxKeyEvent & p_event );
		void OnChar( wxKeyEvent & p_event );
		void OnMouseMove( wxMouseEvent & p_event );
		void OnLeftDown( wxMouseEvent & p_event );
		void OnLeftUp( wxMouseEvent & p_event );
		void OnMiddleDown( wxMouseEvent & p_event );
		void OnMiddleUp( wxMouseEvent & p_event );
		void OnRightDown( wxMouseEvent & p_event );
		void OnRightUp( wxMouseEvent & p_event );
		void OnLeftDClick( wxMouseEvent & p_event );

	private:
		static const int m_iTimerId = 27;
		static wxString m_strGlErrors[6];
		std::shared_ptr< ProceduralTextures::GeneratorBase > m_pGenerator;
		wxGLContext * m_pContext;
		bool m_bInitialised;
		bool m_bFullScreen;
		MainFrame * m_pFrame;
		ProceduralTextures::Signal< std::function< void( ProceduralTextures::Position const & ) > > m_signalMouseMove;
		uint32_t m_mouseMoveIndex;
		wxTimer * m_timer;
		uint32_t m_count;
#if defined( PGEN_RECORDS )
		wxMilliClock_t m_msSaved;
		uint32_t m_uiRecordedCount;
		uint64_t m_ui64RecordedTime;
		std::vector< uint8_t > m_bufferNV12;
#	if defined( PGEN_FFMPEG )
		AVCodec * m_pAvCodec;
		AVFrame * m_pAvFrame;
		AVPicture m_avEncodedPicture;
#		if USE_STREAMS
		AVFormatContext * m_pAvFormatContext;
		AVStream * m_pAvStream;
#		else
		AVCodecContext * m_pAvCodecContext;
		FILE * m_pFile;
#		endif
#	elif defined( PGEN_OCV )
		cv::VideoWriter m_writer;
#	endif
#endif
	};
}

#endif