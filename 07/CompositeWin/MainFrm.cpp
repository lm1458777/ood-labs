#include "stdafx.h"
#include "MainFrm.h"
#include "AboutDlg.h"
#include "GdiCanvas.h"

#include "../CompositeLib/Group.h"
#include "../CompositeLib/Rectangle.h"
#include "../CompositeLib/Slide.h"
#include "../CompositeLib/Style.h"

using namespace std;

namespace
{

auto CreateSlide()
{
	CRectangle rectangle(
		RectD{ 0, 0, 100, 100 },
		make_shared<CStyle>(true, 0x000000FF),
		make_shared<CStyle>(true, 0xFF0000FF));

	//CEllipse ellipse(
	//	RectD { 100, 100, 200, 100 },
	//	make_shared<CStyle>(true, 0x0000FFFF),
	//	make_shared<CStyle>(true, 0xFFFF00FF),
	//	3.f
	//);

	//CTriangle triangle(
	//	RectD { 300, 300, 100, 100 },
	//	make_shared<CStyle>(true, 0x00FF00FF),
	//	make_shared<CStyle>(false, 0x0000FFFF),
	//	5.f);

	auto group = make_shared<CGroup>();
	group->InsertShape(make_shared<CRectangle>(rectangle), 0);
	//group->InsertShape(make_shared<CEllipse>(ellipse), 1);
	group->SetFillStyle(make_shared<CStyle>(true, 0xFF0000FF));
	//group->InsertShape(make_shared<CTriangle>(triangle), 1);

	RectD groupFrame = { 0, 0, 600, 100 };
	group->SetFrame(groupFrame);

	auto slide = make_unique<CSlide>();
	slide->SetBackgroundColor(0x80ff80ff);
	//slide.AddShape(make_shared<CTriangle>(triangle));
	//slide.AddShape(make_shared<CEllipse>(ellipse));
	slide->AddShape(make_shared<CRectangle>(rectangle));
	slide->AddShape(group);

	return slide;
}

} // namespace

CMainFrame::CMainFrame()
	: m_slide{ CreateSlide() }
{
}

CMainFrame::~CMainFrame() = default;

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	return CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
	return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	bHandled = FALSE;
	return 1;
}

LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CMainFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: add code to initialize document

	return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

void CMainFrame::OnPaint(CDCHandle /*dc*/)
{
	CPaintDC paintDC{ m_hWnd };
	CMemoryDC memDC{ paintDC.m_hDC, paintDC.m_ps.rcPaint };

	GdiCanvas canvas{ memDC.m_hDC };
	m_slide->Draw(canvas);
}
