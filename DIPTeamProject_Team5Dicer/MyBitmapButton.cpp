#include "pch.h"
#include "MyBitmapButton.h"

CMyBitmapButton::CMyBitmapButton(void)
{
}

CMyBitmapButton::~CMyBitmapButton(void)
{
}

BOOL CMyBitmapButton::AutoLoad(UINT nID, CWnd* pParent)
{
	if (!SubclassDlgItem(nID, pParent))
		return FALSE;

	CString buttonName;
	GetWindowText(buttonName);
	ASSERT(!buttonName.IsEmpty());

	LoadBitmaps(buttonName + _T("U"), buttonName + _T("D"),
		buttonName + _T("F"), buttonName + _T("X"));

	if (m_bitmap.m_hObject == NULL)
		return FALSE;

	return TRUE;
}

void CMyBitmapButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	ASSERT(lpDIS != NULL);
	ASSERT(m_bitmap.m_hObject != NULL);

	CBitmap* pBitmap = &m_bitmap;
	UINT state = lpDIS->itemState;
	if ((state & ODS_SELECTED) && m_bitmapSel.m_hObject != NULL)
		pBitmap = &m_bitmapSel;
	else if ((state & ODS_FOCUS) && m_bitmapFocus.m_hObject != NULL)
		pBitmap = &m_bitmapFocus;
	else if ((state & ODS_DISABLED) && m_bitmapDisabled.m_hObject != NULL)
		pBitmap = &m_bitmapDisabled;

	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOld = memDC.SelectObject(pBitmap);
	if (pOld == NULL)
		return;

	CRect rect;
	rect.CopyRect(&lpDIS->rcItem);

	BITMAP bits;
	pBitmap->GetObject(sizeof(BITMAP), &bits);
	pDC->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(),
		&memDC, 0, 0, bits.bmWidth, bits.bmHeight, SRCCOPY);

	memDC.SelectObject(pOld);
}