#include "stdafx.h"
#include "MainFrm.h"
#include "AboutDlg.h"
#include "GdiCanvas.h"

#include "../CompositeLib/ColorUtils.h"
#include "../CompositeLib/IGroup.h"
#include "../CompositeLib/IStyle.h"
#include "../CompositeLib/ShapeFactory.h"
#include "../CompositeLib/Slide.h"
#include "../CompositeLib/StyleFactory.h"

using namespace std;

namespace
{

RGBAColor SetAlpha(RGBAColor color, BYTE alpha)
{
	return MakeColorRGBA(
		GetRedValue(color),
		GetGreenValue(color),
		GetBlueValue(color),
		alpha);
}

void SetAlpha(IGroup& group, BYTE a)
{
	auto getShape = [&group](auto index) {
		return group.GetShapeAtIndex(index);
	};

	boost::for_each(boost::irange<size_t>(0, group.GetShapesCount()) | boost::adaptors::transformed(getShape), [a](const IShapePtr& shape) {
		auto fillStyle = shape->GetFillStyle();
		fillStyle->SetColor(SetAlpha(fillStyle->GetColor(), a));

		auto lineStyle = shape->GetLineStyle();
		lineStyle->SetColor(SetAlpha(lineStyle->GetColor(), a));
	});
}

auto CreateSlide()
{
	auto shape1 = CreateRectangle(
		RectD{ 10, 10, 100, 100 },
		CreateFillStyle(MakeColorRGB(0xff, 0, 0)),
		CreateLineStyle(MakeColorRGB(0, 0, 0), 5.f));

	auto shape2 = CreateTriangle(
		RectD{ 120, 10, 100, 100 },
		CreateFillStyle(MakeColorRGB(0, 0xff, 0)),
		CreateLineStyle(MakeColorRGB(0x64, 0x64, 0x64), 3.f));

	auto shape3 = CreateEllipse(
		RectD{ 230, 10, 100, 100 },
		CreateFillStyle(MakeColorRGB(0, 0, 0xff)),
		CreateLineStyle(MakeColorRGB(0xff, 0x7f, 0x7f), 0.f, false));

	auto group1 = CreateGroup();
	AddShape(*group1, shape1->Clone());
	AddShape(*group1, shape2->Clone());
	AddShape(*group1, shape3->Clone());
	AddShape(*group1, CreateRectangle(
		RectD{ 340, 10, 150, 100 },
		CreateFillStyle(MakeColorRGB(0x7f, 0x7f, 0x7f)),
		CreateLineStyle(MakeColorRGB(0xff, 0xff, 0xff), 5.f)));
	SetAlpha(*group1, 0x7f);
	group1->SetFrame(RectD{ 10, 120, 480, 100 });

	auto group2 = group1->Clone();
	AddShape(*group2->GetGroup(), CreateTriangle(
		RectD{ 500, 130, 150, 80 },
		CreateNoFillStyle(),
		CreateNoLineStyle()));
	assert(group2->GetLineStyle() == nullptr);
	group2->SetLineStyle(CreateLineStyle(MakeColorRGB(0x41, 0x71, 0x9c), 3.f));
	assert(group2->GetLineStyle() != nullptr);

	assert(group2->GetFillStyle() == nullptr);
	group2->SetFillStyle(CreateFillStyle(MakeColorRGB(0x5b, 0x9b, 0xd5)));
	assert(group2->GetFillStyle() != nullptr);
	group2->SetFrame(RectD{ 10, 240, 480, 150 });

	auto slide = make_unique<CSlide>(800, 600);
	slide->SetBackgroundColor(MakeColorRGB(0xff, 0xff, 0xe0));
	slide->AddShape(shape1);
	slide->AddShape(shape2);
	slide->AddShape(shape3);
	slide->AddShape(group1);
	slide->AddShape(group2);
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
	CDCHandle dc{ memDC.m_hDC };
	dc.FillSolidRect(&paintDC.m_ps.rcPaint, RGB(0, 0, 0));
	m_slide->Draw(canvas);
}
