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
			gameStatus = CM_START_ED;
		return valReturn;

	case CM_START_ED:
		return PlayingProc( hwnd, message, wParam, lParam );
	}

	return DefWindowProc( hwnd, message, wParam, lParam );
}