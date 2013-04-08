#include "GameWndProc.h"

//////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK WndProc( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	static int gameStatus = CM_UN_START;
	LRESULT valReturn;

	switch( gameStatus )
	{
	case CM_UN_START:
		valReturn = DealBeginMenuMsg( hwnd, message, wParam, lParam );
		if( valReturn == CM_START_GAME )
			SetWindowLong( hwnd, GWL_WNDPROC, (long)PlayingProc );
		return valReturn;
	}

	return DefWindowProc( hwnd, message, wParam, lParam );
}