#include "stdafx.h"
#include "MainFrm.h"
#include "AboutDlg.h"
#include "GdiCanvas.h"

#include "../CompositeLib/ColorUtils.h"
#include "../CompositeLib/Group.h"
#include "../CompositeLib/Rectangle.h"
#include "../CompositeLib/Slide.h"
#include "../CompositeLib/StyleFactory.h"

using namespace std;

namespace
{

auto CreateSlide()
{
	auto rect1 = make_shared<CRectangle>(
		RectD{ 10, 10, 100, 100 },
		CreateFillStyle(MakeColorRGB(0xff, 0, 0)),
		CreateLineStyle(MakeColorRGB(0, 0, 0), 5.f));

	auto rect2 = make_shared<CRectangle>(
		RectD{ 120, 10, 100, 100 },
		CreateFillStyle(MakeColorRGB(0, 0xff, 0)),
		CreateLineStyle(MakeColorRGB(0x64, 0x64, 0x64), 3.f));

	auto rect3 = make_shared<CRectangle>(
		RectD{ 230, 10, 100, 100 },
		CreateFillStyle(MakeColorRGB(0, 0, 0xff)),
		CreateLineStyle(MakeColorRGB(0xff, 0x7f, 0x7f), 0.f, false));

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

	//auto group = make_shared<CGroup>();
	//AddShape(*group, make_shared<CRectangle>(*rect1));
	////group->InsertShape(make_shared<CEllipse>(ellipse), 1);
	//group->SetFillStyle(make_shared<CStyle>(true, 0xFF00007F));
	//group->InsertShape(make_shared<CTriangle>(triangle), 1);

	//RectD groupFrame = { 0, 200, 600, 100 };
	//group->SetFrame(groupFrame);

	auto slide = make_unique<CSlide>(800, 600);
	slide->SetBackgroundColor(0x80ff80ff);
	//slide.AddShape(make_shared<CTriangle>(triangle));
	//slide.AddShape(make_shared<CEllipse>(ellipse));
	slide->AddShape(rect1);
	slide->AddShape(rect2);
	slide->AddShape(rect3);
	//slide->AddShape(group);

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
	bool remove_me;
	CDCHandle dc{ memDC.m_hDC };
	dc.FillSolidRect(&paintDC.m_ps.rcPaint, RGB(0, 0, 0));
	m_slide->Draw(canvas);
}
