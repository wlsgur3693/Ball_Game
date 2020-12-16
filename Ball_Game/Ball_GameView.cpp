
// Ball_GameView.cpp: CBallGameView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Ball_Game.h"
#endif

#include "Ball_GameDoc.h"
#include "Ball_GameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define BSIZE 30
#endif


// CBallGameView

IMPLEMENT_DYNCREATE(CBallGameView, CView)

BEGIN_MESSAGE_MAP(CBallGameView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CHAR()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CBallGameView 생성/소멸

CBallGameView::CBallGameView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_Ball = CPoint(50, 300);
	m_flag = true;
}

CBallGameView::~CBallGameView()
{
}

BOOL CBallGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CBallGameView 그리기

void CBallGameView::OnDraw(CDC* pDC)
{
	CBallGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDC->Rectangle(m_Wall3);
	pDC->Ellipse(m_Ball.x - BSIZE, m_Ball.y - BSIZE,
		m_Ball.x + BSIZE, m_Ball.y + BSIZE);
	pDC->Rectangle(m_Goal);
	pDC->Rectangle(m_Wall1);
	pDC->Rectangle(m_Wall2);
}


// CBallGameView 인쇄

BOOL CBallGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CBallGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CBallGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CBallGameView 진단

#ifdef _DEBUG
void CBallGameView::AssertValid() const
{
	CView::AssertValid();
}

void CBallGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBallGameDoc* CBallGameView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBallGameDoc)));
	return (CBallGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CBallGameView 메시지 처리기




void CBallGameView::OnTimer(UINT_PTR nIDEvent)
{
	if (Touch()) {
		AfxMessageBox(L"실패");
		KillTimer(1);
	}
	else if(TouchGoal())
	{
		AfxMessageBox(L"성공!");
		KillTimer(1);
	}
	Invalidate();
	CView::OnTimer(nIDEvent);
}


void CBallGameView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_RETURN: 
		SetTimer(1, 100, NULL);
		break;
	case VK_LEFT: 
		if (m_flag)
		{
			m_Ball.x = m_Ball.x - BSIZE;
		}
		break;
	case VK_RIGHT:
		if (m_flag)
		{
			m_Ball.x = m_Ball.x + BSIZE;
		}
		break;
	case VK_DOWN: 
		if (m_flag)
		{
			m_Ball.y = m_Ball.y + BSIZE;
		}
		break;
	case VK_UP: 
		if (m_flag)
		{
			m_Ball.y = m_Ball.y - BSIZE;
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CBallGameView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	m_WinRight = cx;
	m_WinBottom = cy;
	m_Goal = CRect(m_WinRight-80,  80, m_WinRight-20, 20);
	m_Wall1 = CRect(m_WinRight-110, 0, m_WinRight-108, 520);
	m_Wall2 = CRect(m_WinRight - 230, 120, m_WinRight - 228, m_WinBottom);
	m_Wall3 = CRect(0, 0, m_WinRight, m_WinBottom);
}



bool CBallGameView::Touch()
{
	// TODO: 여기에 구현 코드 추가.
	if (m_Ball.x - 30 <= 0|| m_Ball.x + 30 >= m_WinRight|| m_Ball.y +40 > m_WinBottom|| m_Ball.y  <= 0 ||
		((m_Ball.x <m_WinRight - 200 && m_Ball.x >m_WinRight - 260) && m_Ball.y > 150)||
		((m_Ball.x <m_WinRight - 80 && m_Ball.x >m_WinRight - 140) && m_Ball.y < 550))
	{
		return(true);
	}
	else {
		return(false);
	}
	
}
bool CBallGameView::TouchGoal()
{
	if (m_Ball.x + 30 >= m_WinRight - 80 && m_Ball.y + 30 <=  80)
	{
		return(true);
	}
	else {
		return(false);
	}
}
