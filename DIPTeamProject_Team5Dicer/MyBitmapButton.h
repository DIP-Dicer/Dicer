#pragma once
#include "afxext.h"

class CMyBitmapButton :
	public CBitmapButton
{
public:
	CMyBitmapButton(void);
	~CMyBitmapButton(void);

	BOOL AutoLoad(UINT nID, CWnd* pParent);
	void DrawItem(LPDRAWITEMSTRUCT lpDIS);
};
