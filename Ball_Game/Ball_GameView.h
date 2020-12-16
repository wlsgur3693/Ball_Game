
// Ball_GameView.h: CBallGameView 클래스의 인터페이스
//

#pragma once


class CBallGameView : public CView
{
protected: // serialization에서만 만들어집니다.
	CBallGameView() noexcept;
	DECLARE_DYNCREATE(CBallGameView)

// 특성입니다.
public:
	CBallGameDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CBallGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CPoint m_Ball;
	bool m_flag;
	int m_WinRight;
	int m_WinBottom;
	bool Touch();
	CRect m_Goal;
	CRect m_Wall1;
	CRect m_Wall2;
	CRect m_Wall3;
	bool TouchGoal();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // Ball_GameView.cpp의 디버그 버전
inline CBallGameDoc* CBallGameView::GetDocument() const
   { return reinterpret_cast<CBallGameDoc*>(m_pDocument); }
#endif

