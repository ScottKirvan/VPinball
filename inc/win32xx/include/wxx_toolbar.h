// Win32++   Version 8.8
// Release Date: 15th October 2020
//
//      David Nash
//      email: dnash@bigpond.net.au
//      url: https://sourceforge.net/projects/win32-framework
//
//
// Copyright (c) 2005-2020  David Nash
//
// Permission is hereby granted, free of charge, to
// any person obtaining a copy of this software and
// associated documentation files (the "Software"),
// to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify,
// merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom
// the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice
// shall be included in all copies or substantial portions
// of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
// ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
// TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
// SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
// ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
// OR OTHER DEALINGS IN THE SOFTWARE.
//
////////////////////////////////////////////////////////


#ifndef _WIN32XX_TOOLBAR_H_
#define _WIN32XX_TOOLBAR_H_

#include "wxx_wincore.h"
#include "wxx_gdi.h"
#include "wxx_controls.h"


namespace Win32xx
{

    ///////////////////////////////////////////////
    // The CToolBar class provides the functionality a toolbar control.
    class CToolBar : public CWnd
    {
    public:
        CToolBar();
        virtual ~CToolBar();

        // Operations
        virtual int  AddBitmap(UINT bitmapID);
        virtual BOOL AddButton(UINT id, BOOL isEnabled = TRUE, int image = -1);
        virtual BOOL AddReplaceBitmap(UINT id);
        virtual void Destroy();
        virtual BOOL ReplaceBitmap(UINT newBitmapID);
        virtual BOOL SetButtonText(int buttonID, LPCTSTR text);

        // Wrappers for Win32 API functions
        BOOL  AddButtons(UINT buttonCount, LPTBBUTTON pButtonInfoArray) const;
        int   AddString(UINT stringID) const;
        int   AddStrings(LPCTSTR pStrings) const;
        void  Autosize() const;
        void  CheckButton(int buttonID, BOOL isChecked) const;
        int   CommandToIndex(int buttonID) const;
        void  Customize() const;
        BOOL  DeleteButton(int index) const;
        BOOL  DisableButton(int buttonID) const;
        BOOL  EnableButton(int buttonID, BOOL isEnabled = TRUE) const;
        BOOL  GetButton(int index, TBBUTTON& buttonInfo) const;
        int   GetButtonCount() const;
        DWORD GetButtonSize() const;
        UINT  GetButtonState(int buttonID) const;
        BYTE  GetButtonStyle(int buttonID) const;
        CString GetButtonText(int buttonID) const;
        int   GetCommandID(int index) const;
        CImageList GetDisabledImageList();
        DWORD GetExtendedStyle() const;
        CImageList GetHotImageList();
        int   GetHotItem() const;
        CImageList GetImageList();
        CRect GetItemRect(int index) const;
        CSize GetMaxSize() const;
        DWORD GetPadding() const;
        CRect GetRect(int buttonID) const;
        int   GetRows() const;
        int   GetTextRows() const;
        HWND  GetToolTips() const;
        BOOL  HasText() const;
        BOOL  HideButton(int buttonID, BOOL show) const;
        int   HitTest() const;
        BOOL  Indeterminate(int buttonID, BOOL isIndeterminate) const;
        BOOL  InsertButton(int index, TBBUTTON& buttonInfo) const;
        BOOL  IsButtonHidden(int buttonID) const;
        BOOL  IsButtonHighlighted(int buttonID) const;
        BOOL  IsButtonIndeterminate(int buttonID) const;
        BOOL  IsButtonPressed(int buttonID) const;
        int   MapAccelerator(TCHAR accelChar) const;
        BOOL  MarkButton(int buttonID, BOOL highlight = TRUE ) const;
        BOOL  MoveButton(UINT oldPos, UINT newPos) const;
        BOOL  PressButton(int buttonID, BOOL press) const;
        void  SaveRestore(BOOL save, TBSAVEPARAMS* pSaveInfo) const;
        BOOL  SetBitmapSize(int cx, int cy) const;
        void  SetButtonInfo(int buttonID, int buttonNewID, int image, BYTE style = 0, BYTE state = 0) const;
        BOOL  SetButtonSize(int cx, int cy) const;
        BOOL  SetButtonState(int buttonID, UINT state) const;
        BOOL  SetButtonStyle(int buttonID, BYTE style) const;
        BOOL  SetButtonWidth(int buttonID, int width) const;
        BOOL  SetCommandID(int index, int buttonID) const;
        HIMAGELIST SetDisableImageList(HIMAGELIST disabledImages);
        DWORD SetDrawTextFlags(DWORD mask, DWORD flags) const;
        DWORD SetExtendedStyle(DWORD exStyle) const;
        HIMAGELIST SetHotImageList(HIMAGELIST hotImages);
        int   SetHotItem(int index) const;
        HIMAGELIST SetImageList(HIMAGELIST normalImages);
        BOOL  SetIndent(int indent) const;
        BOOL  SetMaxTextRows(int maxRows) const;
        BOOL  SetPadding(int cx, int cy) const;
        void  SetToolTips(HWND toolTip) const;

    protected:
        // Overridables
        virtual void OnAttach();
        virtual void OnDestroy();
        virtual LRESULT OnWindowPosChanging(UINT msg, WPARAM wparam, LPARAM lparam);
        virtual void PreCreate(CREATESTRUCT& cs);
        virtual void PreRegisterClass(WNDCLASS& wc);

        // Not intended to be overridden
        LRESULT WndProcDefault(UINT msg, WPARAM wparam, LPARAM lparam);

    private:
        CToolBar(const CToolBar&);              // Disable copy construction
        CToolBar& operator = (const CToolBar&); // Disable assignment operator

        std::map<CString, int> m_stringMap; // a map of strings used in SetButtonText

        UINT m_oldBitmapID;                // Bitmap Resource ID, used in AddBitmap/ReplaceBitmap

    };  // class CToolBar

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


namespace Win32xx
{

    ////////////////////////////////////
    // Definitions for the CToolBar class
    //

    inline CToolBar::CToolBar() : m_oldBitmapID(0)
    {
    }

    inline CToolBar::~CToolBar()
    {
    }

    // Adds one or more images to the list of button images available for a ToolBar.
    // Note: AddBitmap supports a maximum colour depth of 8 bits (256 colours)
    //       This is an obsolete functioned retained for Win95 support.
    //       Unless Win95 support is required, use SetImageList instead.
    // Refer to TB_ADDBITMAP in the Windows API documentation for more information.
    inline int CToolBar::AddBitmap(UINT bitmapID)
    {
        assert(IsWindow());

        CBitmap Bitmap(bitmapID);
        assert (Bitmap.GetHandle());
        BITMAP data = Bitmap.GetBitmapData();
        int imageWidth  = MAX(data.bmHeight, 16);
        int images = data.bmWidth / imageWidth;

        TBADDBITMAP tbab;
        ZeroMemory(&tbab, sizeof(tbab));
        tbab.hInst = GetApp()->GetResourceHandle();
        tbab.nID   = bitmapID;
        int result = (int)SendMessage(TB_ADDBITMAP, (WPARAM)images, (LPARAM)&tbab);

        if (result != -1)
            m_oldBitmapID = bitmapID;

        return result;
    }

    // Adds a single button to the Toolbar. It provides a convenient alternative to AddButtons.
    // A resource ID of 0 is a separator. image is the index of the image in the ImageList.
    // The default is -1 in which case the image based on the button's position is chosen.
    // Refer to TB_ADDBUTTONS in the Windows API documentation for more information.
    inline BOOL CToolBar::AddButton(UINT id, BOOL isEnabled /* = TRUE */, int image /* = -1 */)
    {
        assert(IsWindow());

        // Count toolbar buttons with Command IDs
        int nImages = 0;

        if (image == -1)
        {
            // choose the image based on the number of buttons already used
            for (int i = 0; i < GetButtonCount(); ++i)
            {
                if (GetCommandID(i) > 0)
                    nImages++;
            }
        }
        else
        {
            nImages = image;
        }

        // TBBUTTON structure for each button in the toolbar
        TBBUTTON tbb;
        ZeroMemory(&tbb, sizeof(tbb));

        if (id == 0)
        {
            tbb.fsStyle = TBSTYLE_SEP;
        }
        else
        {
            tbb.iBitmap = nImages;
            tbb.idCommand = id;
            tbb.fsState = isEnabled? TBSTATE_ENABLED : 0;
            tbb.fsStyle = TBSTYLE_BUTTON;
        }

        // Add the button to the toolbar
        return (SendMessage(TB_ADDBUTTONS, (WPARAM)1, (LPARAM)&tbb) != 0);
    }

    // Adds one or more buttons to a ToolBar. pButtonInfoArray is a pointer to an array of TBBUTTON.
    // Refer to TB_ADDBUTTONS in the Windows API documentation for more information.
    inline BOOL CToolBar::AddButtons(UINT buttonCount, LPTBBUTTON pButtonInfoArray) const
    {
        assert(IsWindow());
        return (SendMessage(TB_ADDBUTTONS, (WPARAM)buttonCount, (LPARAM)pButtonInfoArray) != 0);
    }

    // Adds images to the toolbar, or replaces the existing ones.
    // Note: AddReplaceBitmap supports a maximum colour depth of 8 bits (256 colours)
    //       This is an obsolete functioned retained for Win95 support.
    //       Unless Win95 support is required, use SetImageList instead.
    // Refer to AddBitmap and ReplaceBitmap for more information.
    inline BOOL CToolBar::AddReplaceBitmap(UINT id)
    {
        assert(IsWindow());

        CBitmap bitmap(id);
        assert(bitmap.GetHandle());
        BITMAP data = bitmap.GetBitmapData();

        int imageHeight = data.bmHeight;
        int imageWidth = MAX(data.bmHeight, 16);

        // Set the bitmap size first
        SetBitmapSize(imageWidth, imageHeight);

        BOOL succeeded = FALSE;
        if (m_oldBitmapID)
            succeeded = ReplaceBitmap(id);
        else
            succeeded = AddBitmap(id);

        return succeeded;
    }

    // Adds a new string, passed as a resource ID, to the ToolBar's internal list of strings.
    // Refer to TB_ADDSTRING in the Windows API documentation for more information.
    inline int CToolBar::AddString(UINT stringID) const
    {
        assert(IsWindow());
        return (int)SendMessage(TB_ADDSTRING, (WPARAM)(GetApp()->GetResourceHandle()), (LPARAM)stringID);
    }

    // Adds a new string or strings to the list of strings available for a ToolBar control.
    // Strings in the buffer must be separated by a null character. The last string must have two null terminators.
    // Refer to TB_ADDSTRING in the Windows API documentation for more information.
    inline int CToolBar::AddStrings(LPCTSTR pStrings) const
    {
        assert(IsWindow());
        return (int)SendMessage(TB_ADDSTRING, 0, (LPARAM)pStrings);
    }

    // Causes a ToolBar to be resized.
    // Refer to TB_AUTOSIZE in the Windows API documentation for more information.
    inline void CToolBar::Autosize() const
    {
        assert(IsWindow());
        SendMessage(TB_AUTOSIZE, 0, 0);
    }

    // Checks or unchecks the specified button in a ToolBar.
    // When a button is checked, it is displayed in the pressed state.
    // Refer to TB_CHECKBUTTON in the Windows API documentation for more information.
    inline void CToolBar::CheckButton(int buttonID, BOOL isChecked) const
    {
        assert(IsWindow());
        SendMessage(TB_CHECKBUTTON, (WPARAM)buttonID, (LPARAM)MAKELONG(isChecked, 0));
    }

    // Retrieves the zero-based index for the button associated with the specified command identifier.
    // Refer to TB_COMMANDTOINDEX in the Windows API documentation for more information.
    inline int CToolBar::CommandToIndex(int buttonID) const
    {
        assert(IsWindow());

        // returns -1 on fail
        return (int)SendMessage(TB_COMMANDTOINDEX, (WPARAM)buttonID, 0);
    }

    // Displays the Customize Toolbar dialog box. The parent must handle the TBN_QUERYINSERT
    // and TBN_QUERYDELETE notifications for the Customize Toolbar dialog box to appear.
    // Requires the CCS_ADJUSTABLE style to be set when the toolbar is created.
    // Refer to TB_CUSTOMIZE in the Windows API documentation for more information.
    inline void CToolBar::Customize() const
    {
        assert(IsWindow());
        SendMessage(TB_CUSTOMIZE, 0, 0);
    }

    // Deletes a button from the ToolBar.
    // index is the Zero-based index of the button to delete.
    // Refer to TB_DELETEBUTTON in the Windows API documentation for more information.
    inline BOOL CToolBar::DeleteButton(int index) const
    {
        assert(IsWindow());
        return (int)SendMessage(TB_DELETEBUTTON, (WPARAM)index, 0);
    }

    // Destroys the toolbar.
    inline void CToolBar::Destroy()
    {
        CWnd::Destroy();
        m_stringMap.clear();
    }

    // Disables the specified button in a ToolBar.
    // An example of buttonID would be IDM_FILE_OPEN.
    // Refer to TB_ENABLEBUTTON in the Windows API documentation for more information.
    inline BOOL CToolBar::DisableButton(int buttonID) const
    {
        assert(IsWindow());
        return (SendMessage(TB_ENABLEBUTTON, (WPARAM)buttonID, (LPARAM)MAKELONG(FALSE, 0)) != 0);
    }

    // Enables the specified button in a ToolBar.
    // Refer to TB_ENABLEBUTTON in the Windows API documentation for more information.
    inline BOOL CToolBar::EnableButton(int buttonID, BOOL isEnabled) const
    {
        assert(IsWindow());
        return (SendMessage(TB_ENABLEBUTTON, (WPARAM)buttonID, (LPARAM)MAKELONG(isEnabled, 0 )) != 0);
    }

    // Receives the TBBUTTON structure information from the specified button.
    // Refer to TB_GETBUTTON in the Windows API documentation for more information.
    inline BOOL CToolBar::GetButton(int index, TBBUTTON& buttonInfo) const
    {
        assert(IsWindow());
        return (SendMessage(TB_GETBUTTON, (WPARAM)index, (LPARAM)&buttonInfo) != 0);
    }

    // Retrieves a count of the buttons currently in the ToolBar.
    // Refer to TB_BUTTONCOUNT in the Windows API documentation for more information.
    inline int CToolBar::GetButtonCount() const
    {
        assert(IsWindow());
        return (int)SendMessage(TB_BUTTONCOUNT, 0, 0);
    }

    // Retrieves the current width and height of ToolBar buttons, in pixels.
    // Returns a DWORD value that contains the width and height values in the low word and high word, respectively.
    // Refer to TB_GETBUTTONSIZE in the Windows API documentation for more information.
    inline DWORD CToolBar::GetButtonSize() const
    {
        assert(IsWindow());
        return (DWORD)SendMessage(TB_GETBUTTONSIZE, 0, 0);
    }

    // Retrieves the state of an individual button
    //  TBSTATE_CHECKED     The button has the TBSTYLE_CHECK style and is being clicked.
    //  TBSTATE_ELLIPSES    The button's text is cut off and an ellipsis is displayed.
    //  TBSTATE_ENABLED     The button accepts user input. A button that doesn't have this state is grayed.
    //  TBSTATE_HIDDEN      The button is not visible and cannot receive user input.
    //  TBSTATE_INDETERMINATE   The button is grayed.
    //  TBSTATE_MARKED      The button is marked. The interpretation of a marked item is dependent upon the application.
    //  TBSTATE_PRESSED     The button is being clicked.
    //  TBSTATE_WRAP        The button is followed by a line break.
    // Refer to TB_GETSTATE in the Windows API documentation for more information.
    inline UINT CToolBar::GetButtonState(int buttonID) const
    {
        assert(IsWindow());
        return (UINT)SendMessage(TB_GETSTATE, (WPARAM)buttonID, 0);
    }

    //  Retrieves the the style of the ToolBar control. The following button styles are supported:
    //  TBSTYLE_BUTTON      Standard push button (default)
    //  TBSTYLE_SEP         Separator
    //  TBSTYLE_CHECK       Auto check-box button
    //  TBSTYLE_GROUP       Marks the start of a group of buttons
    //  TBSTYLE_CHECKGROUP  Marks the start of a group of check-box buttons
    //  TBSTYLE_DROPDOWN    Creates a drop-down list button
    //  TBSTYLE_AUTOSIZE    The button's width will be calculated based on the text of the button, not on the size of the image
    //  TBSTYLE_NOPREFIX    The button text will not have an accelerator prefix associated with it
    // Refer to TB_GETBUTTON in the Windows API documentation for more information.
    inline BYTE CToolBar::GetButtonStyle(int buttonID) const
    {
        assert(IsWindow());

        int index = CommandToIndex(buttonID);
        TBBUTTON tbb;
        ZeroMemory(&tbb, sizeof(tbb));
        SendMessage(TB_GETBUTTON, (WPARAM)index, (LPARAM)&tbb);

        return tbb.fsStyle;
    }

    // Retrieves the display text of a button on a ToolBar.
    // Refer to TB_GETBUTTONTEXT in the Windows API documentation for more information.
    inline CString CToolBar::GetButtonText(int buttonID) const
    {
        assert(IsWindow());

        int length = (int)SendMessage(TB_GETBUTTONTEXT, (WPARAM)buttonID, 0);
        CString str;
        if (length > 0)
        {
            LPTSTR szStr = str.GetBuffer(length);
            SendMessage(TB_GETBUTTONTEXT, (WPARAM)buttonID, (LPARAM)szStr);
            str.ReleaseBuffer();
        }

        return str;
    }

    // Retrieves information about the specified button in a ToolBar.
    // Refer to TB_GETBUTTON in the Windows API documentation for more information.
    inline int CToolBar::GetCommandID(int index) const
    {
        assert(IsWindow());
        TBBUTTON tbb;
        ZeroMemory(&tbb, sizeof(tbb));
        SendMessage(TB_GETBUTTON, (WPARAM)index, (LPARAM)&tbb);

        // returns zero if failed
        return tbb.idCommand;
    }

    // Retrieves the image list that a ToolBar control uses to display inactive buttons.
    // Refer to TB_GETDISABLEDIMAGELIST in the Windows API documentation for more information.
    inline CImageList CToolBar::GetDisabledImageList()
    {
        assert(IsWindow());
        HIMAGELIST images = (HIMAGELIST)SendMessage(TB_GETDISABLEDIMAGELIST, 0, 0);
        return CImageList(images);
    }

    // Retrieves the he extended styles currently in use for the toolbar control.
    // Possible extended styles: TBSTYLE_EX_DRAWDDARROWS, TBSTYLE_EX_HIDECLIPPEDBUTTONS, TBSTYLE_EX_DOUBLEBUFFER and TBSTYLE_EX_MIXEDBUTTONS.
    // Refer to TB_GETEXTENDEDSTYLE in the Windows API documentation for more information.
    inline DWORD CToolBar::GetExtendedStyle() const
    {
        assert(IsWindow());
        return (DWORD)SendMessage(TB_GETEXTENDEDSTYLE, 0, 0);
    }

    // Retrieves the image list that a ToolBar control uses to display hot buttons.
    // Refer to TB_GETHOTIMAGELIST in the Windows API documentation for more information.
    inline CImageList CToolBar::GetHotImageList()
    {
        assert(IsWindow());
        HIMAGELIST images = (HIMAGELIST)SendMessage(TB_GETHOTIMAGELIST, 0, 0);
        return CImageList(images);
    }

    // Retrieves the index of the hot item in a ToolBar, or -1 if no hot item is set.
    // Refer to TB_GETHOTITEM in the Windows API documentation for more information.
    inline int CToolBar::GetHotItem() const
    {
        assert(IsWindow());
        return static_cast<int>(SendMessage(TB_GETHOTITEM, 0, 0));
    }

    // Retrieves the image list that a ToolBar control uses to display buttons in their default state.
    // Refer to TB_GETIMAGELIST in the Windows API documentation for more information.
    inline CImageList CToolBar::GetImageList()
    {
        assert(IsWindow());
        HIMAGELIST images = (HIMAGELIST)SendMessage(TB_GETIMAGELIST, 0, 0);
        return CImageList(images);
    }

    // Retrieves the bounding rectangle of a button in a ToolBar.
    // Refer to TB_GETITEMRECT in the Windows API documentation for more information.
    inline CRect CToolBar::GetItemRect(int index) const
    {
        assert(IsWindow());
        CRect rc;
        int count = (int)SendMessage(TB_BUTTONCOUNT, 0, 0);

        if (count >= index)
            SendMessage(TB_GETITEMRECT, (WPARAM)index, (LPARAM)&rc);

        return rc;
    }

    // Retrieves the total size of all of the visible buttons and separators in the ToolBar.
    // Refer to TB_GETMAXSIZE in the Windows API documentation for more information.
    inline CSize CToolBar::GetMaxSize() const
    {
        assert(IsWindow());
        CSize sz;
        SendMessage(TB_GETMAXSIZE, 0, (LPARAM)&sz);

        // This fixes a Windows bug calculating the size when TBSTYLE_DROPDOWN is used.
        int cxMaxSize = 0;
        int cyMaxSize = 0;
        for (int i= 0 ; i < GetButtonCount(); ++i)
        {
            CRect itemRect = GetItemRect(i);
            cxMaxSize += itemRect.Width();
            cyMaxSize += itemRect.Height();
        }

        if (GetStyle() & CCS_VERT)
            sz.cy = cyMaxSize;
        else
            sz.cx = cxMaxSize;

        return sz;
    }

    // Returns a DWORD value that contains the horizontal padding in the low word and
    // the vertical padding in the high word, in pixels.
    // Refer to TB_GETPADDING in the Windows API documentation for more information.
    inline DWORD CToolBar::GetPadding() const
    {
        assert(IsWindow());
        return (DWORD)SendMessage(TB_GETPADDING, 0, 0);
    }

    // Retrieves the bounding rectangle for a specified ToolBar button.
    // Refer to TB_GETRECT in the Windows API documentation for more information.
    inline CRect CToolBar::GetRect(int buttonID) const
    {
        assert(IsWindow());
        CRect rc;
        SendMessage(TB_GETRECT, (WPARAM)buttonID, (LPARAM)&rc);
        return rc;
    }

    // Retrieves the number of rows of buttons in a ToolBar with the TBSTYLE_WRAPABLE style.
    // Refer to TB_GETROWS in the Windows API documentation for more information.
    inline int CToolBar::GetRows() const
    {
        assert(IsWindow());
        return (int)SendMessage(TB_GETROWS, 0, 0);
    }

    // Retrieves the maximum number of text rows that can be displayed on a ToolBar button.
    // Refer to TB_GETTEXTROWS in the Windows API documentation for more information.
    inline int CToolBar::GetTextRows() const
    {
        assert(IsWindow());
        return (int)SendMessage(TB_GETTEXTROWS, 0, 0);
    }

    // Retrieves the handle to the ToolTip control, if any, associated with the ToolBar.
    // Refer to TB_GETTOOLTIPS in the Windows API documentation for more information.
    inline HWND CToolBar::GetToolTips() const
    {
        assert(IsWindow());
        return (HWND)SendMessage(TB_GETTOOLTIPS, 0, 0);
    }

    // Returns TRUE if any button has text.
    // Refer to TB_GETBUTTONTEXT in the Windows API documentation for more information.
    inline BOOL CToolBar::HasText() const
    {
        assert(IsWindow());
        BOOL result = FALSE;

        for (int i = 0 ; i < GetButtonCount(); ++i)
        {
            if (SendMessage(TB_GETBUTTONTEXT, (WPARAM)GetCommandID(i), 0) != -1)
                result = TRUE;
        }

        // return TRUE if any button has text
        return result;
    }

    // Hides or shows the specified button in a ToolBar.
    // Refer to TB_HIDEBUTTON in the Windows API documentation for more information.
    inline BOOL CToolBar::HideButton(int buttonID, BOOL show) const
    {
        assert(IsWindow());
        return (SendMessage(TB_HIDEBUTTON, (WPARAM)buttonID, (LPARAM)MAKELONG (show, 0)) != 0);
    }

    // Determines where a point lies in a ToolBar control.
    // Refer to TB_HITTEST in the Windows API documentation for more information.
    inline int CToolBar::HitTest() const
    {
        // We do our own hit test since TB_HITTEST is a bit buggy,
        // and also doesn't work at all on earliest versions of Win95.

        assert(IsWindow());
        CPoint pos = GetCursorPos();
        ScreenToClient(pos);

        int buttons = (int)SendMessage(TB_BUTTONCOUNT, 0, 0);
        int button = -1;

        for (int i = 0 ; i < buttons; ++i)
        {
            CRect rc = GetItemRect(i);
            if (rc.PtInRect(pos))
                button = i;
        }

        return button;
    }

    // Sets or clears the indeterminate state of the specified button in a toolbar.
    // Refer to TB_INDETERMINATE in the Windows API documentation for more information.
    inline BOOL CToolBar::Indeterminate(int buttonID, BOOL isIndeterminate) const
    {
        assert(IsWindow());
        return (SendMessage(TB_INDETERMINATE, (WPARAM)buttonID, (LPARAM)MAKELONG (isIndeterminate, 0)) != 0);
    }

    // Inserts a button to the left of the specified button index.
    // Refer to TB_INSERTBUTTON in the Windows API documentation for more information.
    inline BOOL CToolBar::InsertButton(int index, TBBUTTON& buttonInfo) const
    {
        assert(IsWindow());
        return (SendMessage(TB_INSERTBUTTON, (WPARAM)index, (LPARAM)&buttonInfo) != 0);
    }

    // Determines whether the specified button in a ToolBar is hidden.
    // Refer to TB_ISBUTTONHIDDEN in the Windows API documentation for more information.
    inline BOOL CToolBar::IsButtonHidden(int buttonID) const
    {
        assert(IsWindow());
        return (SendMessage(TB_ISBUTTONHIDDEN, (WPARAM)buttonID, 0) != 0);
    }

    // Checks the highlight state of a ToolBar button.
    // Refer to TB_ISBUTTONHIGHLIGHTED in the Windows API documentation for more information.
    inline BOOL CToolBar::IsButtonHighlighted(int buttonID) const
    {
        assert(IsWindow());
        return (SendMessage(TB_ISBUTTONHIGHLIGHTED, (WPARAM)buttonID, 0) != 0);
    }

    // Determines whether the specified button in a ToolBar is indeterminate.
    // Refer to TB_ISBUTTONINDETERMINATE in the Windows API documentation for more information.
    inline BOOL CToolBar::IsButtonIndeterminate(int buttonID) const
    {
        assert(IsWindow());
        return (SendMessage(TB_ISBUTTONINDETERMINATE, (WPARAM)buttonID, 0) != 0);
    }

    // Determines whether the specified button in a ToolBar is pressed.
    // Refer to TB_ISBUTTONPRESSED in the Windows API documentation for more information.
    inline BOOL CToolBar::IsButtonPressed(int buttonID) const
    {
        assert(IsWindow());
        return (SendMessage(TB_ISBUTTONPRESSED, (WPARAM)buttonID, 0) != 0);
    }

    // Determines whether the specified button in a ToolBar is pressed.
    // Refer to TB_MAPACCELERATOR in the Windows API documentation for more information.
    inline int CToolBar::MapAccelerator(TCHAR accelChar) const
    {
        assert(IsWindow());
        int uButtonID;
        int idButton;
        if (SendMessage(TB_MAPACCELERATOR, (WPARAM)accelChar, (LPARAM)&uButtonID))
            idButton = uButtonID;
        else
            idButton = -1;

        return idButton;
    }

    // Sets the highlight state of a given button in a ToolBar control.
    // Refer to TB_MARKBUTTON in the Windows API documentation for more information.
    inline BOOL CToolBar::MarkButton(int buttonID, BOOL Highlight /*= TRUE*/ ) const
    {
        assert(IsWindow());
        return (SendMessage(TB_MARKBUTTON, (WPARAM)buttonID, (LPARAM)Highlight) != 0);
    }

    // Moves a button from one index to another.
    // Refer to TB_MOVEBUTTON in the Windows API documentation for more information.
    inline BOOL CToolBar::MoveButton(UINT oldPos, UINT newPos) const
    {
        assert(IsWindow());
        return (SendMessage(TB_MOVEBUTTON, (WPARAM)oldPos, (LPARAM)newPos) != 0);
    }

    // Called when the toolbar window is created and attached to this object.
    inline void CToolBar::OnAttach()
    {
        // We must send this message before sending the TB_ADDBITMAP or TB_ADDBUTTONS message
        SendMessage(TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

        // allows buttons to have a separate drop-down arrow
        // Note: TBN_DROPDOWN notification is sent by a ToolBar control when the user clicks a drop-down button
        SendMessage(TB_SETEXTENDEDSTYLE, 0, (LPARAM)TBSTYLE_EX_DRAWDDARROWS);
    }

    // Called when the toolbar window is about to be destroyed.
    inline void CToolBar::OnDestroy()
    {
    }

    // Called when the toolbar is resized.
    inline LRESULT CToolBar::OnWindowPosChanging(UINT msg, WPARAM wparam, LPARAM lparam)
    {
        //  Used by ReBar controls to adjust ToolBar window size
        if ( GetParent().SendMessage(UWM_TBWINPOSCHANGING, (WPARAM)GetHwnd(), lparam) )
        {
            LPWINDOWPOS pWinPos = (LPWINDOWPOS)lparam;
            pWinPos->cx = GetMaxSize().cx;
            pWinPos->cy = GetMaxSize().cy;
        }

        return FinalWindowProc(msg, wparam, lparam);
    }

    // Sets the CREATESTRUCT parameters prior to window creation
    inline void CToolBar::PreCreate(CREATESTRUCT& cs)
    {
        cs.style = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT;
    }

    // Sets the window class.
    inline void CToolBar::PreRegisterClass(WNDCLASS& wc)
    {
        wc.lpszClassName =  TOOLBARCLASSNAME;
    }

    // Presses or releases the specified button in a ToolBar.
    // Refer to TB_PRESSBUTTON in the Windows API documentation for more information.
    inline BOOL CToolBar::PressButton(int buttonID, BOOL press) const
    {
        assert(IsWindow());
        return (SendMessage(TB_PRESSBUTTON, (WPARAM)buttonID, (LPARAM)MAKELONG(press, 0)) != 0);
    }

    // Replaces an existing bitmap with a new bitmap.
    // Note: ReplaceBitmap supports a maximum colour depth of 8 bits (256 colours)
    //       This is an obsolete functioned retained for Win95 support.
    //       Unless Win95 support is required, use SetImageList instead.
    // Refer to TB_REPLACEBITMAP in the Windows API documentation for more information.
    inline BOOL CToolBar::ReplaceBitmap(UINT newBitmapID)
    {
        assert(IsWindow());

        CBitmap Bitmap(newBitmapID);
        assert (Bitmap.GetHandle());
        BITMAP data = Bitmap.GetBitmapData();
        int imageWidth  = MAX(data.bmHeight, 16);
        int images = data.bmWidth / imageWidth;

        TBREPLACEBITMAP tbrb;
        ZeroMemory(&tbrb, sizeof(tbrb));
        tbrb.hInstNew = GetApp()->GetResourceHandle();
        tbrb.hInstOld = tbrb.hInstNew;
        tbrb.nIDNew = newBitmapID;
        tbrb.nIDOld = m_oldBitmapID;
        tbrb.nButtons  = images;

        BOOL result = (SendMessage(TB_REPLACEBITMAP, 0, (LPARAM)&tbrb) != 0);
        if (result)
            m_oldBitmapID = newBitmapID;

        return result;
    }

    // Saves or restores the toolbar state in the registry. Parameter values:
    //  save       If this parameter is TRUE, the information is saved, otherwise it is restored.
    //  pSaveInfo  Pointer to a TBSAVEPARAMS structure that specifies the registry key, subkey,
    //             and value name for the toolbar state information.
    // Refer to TB_SAVERESTORE in the Windows API documentation for more information.
    inline void CToolBar::SaveRestore(BOOL save, TBSAVEPARAMS* pSaveInfo) const
    {
        assert(IsWindow());
        SendMessage(TB_SAVERESTORE, (WPARAM)save, (LPARAM)pSaveInfo);
    }

    // Sets the size of the bitmapped images to be added to a ToolBar.
    // Needs to be used when the image size is not the default 16 x 15
    // Call this function before using AddBitmap or ReplaceBitmap.
    // Refer to TB_SETBITMAPSIZE in the Windows API documentation for more information.
    inline BOOL CToolBar::SetBitmapSize(int cx, int cy) const
    {
        assert(IsWindow());
        return (SendMessage(TB_SETBITMAPSIZE, 0, (LPARAM)MAKELONG(cx, cy)) != 0);
    }

    // Sets the size of the buttons to be added to a ToolBar.
    // This function should generally be called after adding buttons.
    // Refer to TB_SETBUTTONSIZE in the Windows API documentation for more information.
    inline BOOL CToolBar::SetButtonSize(int cx, int cy) const
    {
        assert(IsWindow());
        return (SendMessage(TB_SETBUTTONSIZE, 0, (LPARAM)MAKELONG(cx, cy)) != 0);
    }

    // Use this to change a button's Command ID. It can also be used to change a button's image.
    // Refer to TB_SETBUTTONINFO in the Windows API documentation for more information.
    inline void CToolBar::SetButtonInfo(int buttonID, int buttonNewID, int image, BYTE style /* = 0 */, BYTE state /* = 0 */) const
    {
        // Retrieve existing state and style
        TBBUTTON tb;
        ZeroMemory(&tb, sizeof(tb));
        BOOL result = GetButton(CommandToIndex(buttonID), tb);
        assert(result);

        if (result)
        {
            TBBUTTONINFO tbbi;
            ZeroMemory(&tbbi, sizeof(tbbi));
            tbbi.cbSize = sizeof(tbbi);
            tbbi.dwMask = TBIF_COMMAND | TBIF_IMAGE | TBIF_STYLE | TBIF_STATE;
            tbbi.idCommand = buttonNewID;
            tbbi.iImage = image;
            tbbi.fsStyle = style ? style : tb.fsStyle;
            tbbi.fsState = state ? state : tb.fsState;

            SendMessage(TB_SETBUTTONINFO, (WPARAM)buttonID, (LPARAM)&tbbi);
        }
    }

    // Set the state of an individual button
    //  TBSTATE_CHECKED     The button has the TBSTYLE_CHECK style and is being clicked.
    //  TBSTATE_ELLIPSES    The button's text is cut off and an ellipsis is displayed.
    //  TBSTATE_ENABLED     The button accepts user input. A button that doesn't have this state is grayed.
    //  TBSTATE_HIDDEN      The button is not visible and cannot receive user input.
    //  TBSTATE_INDETERMINATE   The button is grayed.
    //  TBSTATE_MARKED      The button is marked. The interpretation of a marked item is dependent upon the application.
    //  TBSTATE_PRESSED     The button is being clicked.
    //  TBSTATE_WRAP        The button is followed by a line break.
    // Refer to TB_SETSTATE in the Windows API documentation for more information.
    inline BOOL CToolBar::SetButtonState(int buttonID, UINT state) const
    {
        assert(IsWindow());
        return (SendMessage(TB_SETSTATE, (WPARAM)buttonID, (LPARAM)MAKELONG (state, 0)) != 0);
    }

    //  The the style of the ToolBar control. The following button styles are supported:
    //  TBSTYLE_BUTTON      Standard push button (default)
    //  TBSTYLE_SEP         Separator
    //  TBSTYLE_CHECK       Auto check-box button
    //  TBSTYLE_GROUP       Marks the start of a group of buttons
    //  TBSTYLE_CHECKGROUP  Marks the start of a group of check-box buttons
    //  TBSTYLE_DROPDOWN    Creates a drop-down list button
    //  TBSTYLE_AUTOSIZE    The button's width will be calculated based on the text of the button, not on the size of the image
    //  TBSTYLE_NOPREFIX    The button text will not have an accelerator prefix associated with it.
    // Refer to TB_SETBUTTONINFO in the Windows API documentation for more information.
    inline BOOL CToolBar::SetButtonStyle(int buttonID, BYTE style) const
    {
        assert(IsWindow());

        TBBUTTONINFO tbbi;
        ZeroMemory(&tbbi, sizeof(tbbi));
        tbbi.cbSize = sizeof(tbbi);
        tbbi.dwMask = TBIF_STYLE;
        tbbi.fsStyle = style;

        // Note:  TB_SETBUTTONINFO requires comctl32.dll version 4.71 or later
        //        i.e. Win95 with IE4 / NT with IE4   or later
        return (SendMessage(TB_SETBUTTONINFO, (WPARAM)buttonID, (LPARAM)&tbbi) != 0);
    }

    // This rather convoluted approach to setting ToolBar button text supports
    // all versions of Windows, including Win95 with COMCTL32.DLL version 4.0.
    // Refer to TB_INSERTBUTTON in the Windows API documentation for more information.
    inline BOOL CToolBar::SetButtonText(int buttonID, LPCTSTR text)
    {
        assert(IsWindow());
        int index = CommandToIndex(buttonID);
        assert(index != -1);

        BOOL succeeded = FALSE;
        CString string = text;
        std::map<CString, int>::iterator m;
        int stringIndex;

        // Check to see if the string is already added
        m = m_stringMap.find(string);
        if (m_stringMap.end() == m)
        {
            CString str;
            if (m_stringMap.size() == 0)
            {
                // Place a blank string first in the string table, in case some
                // buttons don't have text

                str = _T(" ");
                str += _T('\0');    // Double-null terminate
                AddStrings(str);
            }

            // No index for this string exists, so create it now
            str = text;
            str += _T('\0');        // Double-null terminate

            stringIndex = AddStrings(str);
            if (stringIndex != -1)
            {
                // Save the string its index in our map
                m_stringMap.insert(std::make_pair(string, stringIndex));

                succeeded = TRUE;
            }
        }
        else
        {
            // String found, use the index from our map
            stringIndex = m->second;
            succeeded = TRUE;
        }

        if (succeeded)
        {
            TBBUTTON tbb;
            ZeroMemory(&tbb, sizeof(tbb));
            succeeded = (SendMessage(TB_GETBUTTON, (WPARAM)index, (LPARAM)&tbb) != 0);

            tbb.iString = stringIndex;

            // Turn off ToolBar drawing
            SetRedraw(FALSE);

            if (succeeded)
                succeeded = (SendMessage(TB_DELETEBUTTON, (WPARAM)index, 0) != 0);

            if (succeeded)
                succeeded = (SendMessage(TB_INSERTBUTTON, (WPARAM)index, (LPARAM)&tbb) != 0);

            // Ensure the button now includes some text rows
            if (SendMessage(TB_GETTEXTROWS, 0, 0) == 0)
                SendMessage(TB_SETMAXTEXTROWS, (WPARAM)1, 0);

            // Turn on ToolBar drawing
            SetRedraw(TRUE);
        }
        // Redraw button
        CRect r = GetItemRect(index);
        InvalidateRect(r, TRUE);

        return succeeded;
    }

    // Sets the button width.
    // Adjust the width of a toolbar button after it is created.
    // This is useful when replacing a button with a ComboBox or other control.
    // Refer to TB_SETBUTTONINFO in the Windows API documentation for more information.
    inline BOOL CToolBar::SetButtonWidth(int buttonID, int width) const
    {
        assert(IsWindow());

        // Note:  TB_SETBUTTONINFO requires comctl32.dll version 4.71 or later
        //        i.e. Win95 with IE4 / NT with IE4   or later

        TBBUTTONINFO tbbi;
        ZeroMemory(&tbbi, sizeof(tbbi));
        tbbi.cbSize = sizeof(tbbi);
        tbbi.dwMask = TBIF_SIZE;
        tbbi.cx = static_cast<WORD>(width);
        BOOL result = (SendMessage(TB_SETBUTTONINFO, (WPARAM)buttonID, (LPARAM)&tbbi) != 0);

        // Send a changed message to the parent (used by the ReBar)
        SIZE maxSize = GetMaxSize();
        GetParent().SendMessage(UWM_TBRESIZE, (WPARAM)GetHwnd(), (LPARAM)&maxSize);

        return result;
    }

    // Sets the command identifier of a ToolBar button.
    // Refer to TB_SETCMDID in the Windows API documentation for more information.
    inline BOOL CToolBar::SetCommandID(int index, int buttonID) const
    {
        assert(IsWindow());
        return (SendMessage(TB_SETCMDID, (WPARAM)index, (LPARAM)buttonID) != 0);
    }

    // Sets the ImageList that the ToolBar control will use to display disabled buttons.
    // Refer to TB_SETDISABLEDIMAGELIST in the Windows API documentation for more information.
    inline HIMAGELIST CToolBar::SetDisableImageList(HIMAGELIST disabledImages)
    {
        assert(IsWindow());
        HIMAGELIST images = (HIMAGELIST)SendMessage(TB_SETDISABLEDIMAGELIST, 0, (LPARAM)disabledImages);
        return images;
    }

    // Sets the text drawing flags for the ToolBar.
    // Refer to TB_SETDRAWTEXTFLAGS in the Windows API documentation for more information.
    inline DWORD CToolBar::SetDrawTextFlags(DWORD mask, DWORD flags) const
    {
        assert(IsWindow());
        return (DWORD)SendMessage(TB_SETDRAWTEXTFLAGS, (WPARAM)mask, (LPARAM)flags);
    }

    // Sets the text drawing flags for the ToolBar.
    // Extended styles include: TBSTYLE_EX_DRAWDDARROWS, TBSTYLE_EX_HIDECLIPPEDBUTTONS, TBSTYLE_EX_DOUBLEBUFFER and TBSTYLE_EX_MIXEDBUTTONS.
    // Refer to TB_SETEXTENDEDSTYLE in the Windows API documentation for more information.
    inline DWORD CToolBar::SetExtendedStyle(DWORD exStyle) const
    {
        assert(IsWindow());
        return (DWORD)SendMessage(TB_SETEXTENDEDSTYLE, 0, (LPARAM)exStyle);
    }

    // Sets the image list that the ToolBar control will use to display hot buttons.
    // Refer to TB_SETHOTIMAGELIST in the Windows API documentation for more information.
    inline HIMAGELIST CToolBar::SetHotImageList(HIMAGELIST hotImages)
    {
        assert(IsWindow());
        HIMAGELIST images = (HIMAGELIST)SendMessage(TB_SETHOTIMAGELIST, 0, (LPARAM)hotImages);
        return images;
    }

    // Sets the hot item in a ToolBar.
    // Refer to TB_SETHOTITEM in the Windows API documentation for more information.
    inline int CToolBar::SetHotItem(int index) const
    {
        assert(IsWindow());
        return (int)SendMessage(TB_SETHOTITEM, (WPARAM)index, 0);
    }

    // Sets the image list that the ToolBar will use to display buttons that are in their default state.
    // Refer to TB_SETIMAGELIST in the Windows API documentation for more information.
    inline HIMAGELIST CToolBar::SetImageList(HIMAGELIST normalImages)
    {
        assert(IsWindow());
        HIMAGELIST images = (HIMAGELIST)SendMessage(TB_SETIMAGELIST, 0, (LPARAM)normalImages);
        return images;
    }

    // Sets the indentation for the first button in a ToolBar control.
    // Refer to TB_SETINDENT in the Windows API documentation for more information.
    inline BOOL CToolBar::SetIndent(int indent) const
    {
        assert(IsWindow());
        return (SendMessage(TB_SETINDENT, (WPARAM)indent, 0) != 0);
    }

    // Sets the maximum number of text rows displayed on a ToolBar button.
    // Refer to TB_SETMAXTEXTROWS in the Windows API documentation for more information.
    inline BOOL CToolBar::SetMaxTextRows(int maxRows) const
    {
        assert(IsWindow());
        return (SendMessage(TB_SETMAXTEXTROWS, (WPARAM)maxRows, 0) != 0);
    }

    // Sets the padding for a ToolBar control.
    // Refer to TB_SETPADDING in the Windows API documentation for more information.
    inline BOOL CToolBar::SetPadding(int cx, int cy) const
    {
        assert(IsWindow());
        return (SendMessage(TB_SETPADDING, 0, (LPARAM)MAKELONG(cx, cy)) != 0);
    }

    // Associates a ToolTip control with a ToolBar. This should be done before
    // adding any buttons to the ToolBar.
    // Refer to TB_SETTOOLTIPS in the Windows API documentation for more information.
    inline void CToolBar::SetToolTips(HWND toolTip) const
    {
        assert(IsWindow());
        SendMessage(TB_SETTOOLTIPS, (WPARAM)toolTip, 0);
    }

    // Provides default processing of the toolbar's messages.
    inline LRESULT CToolBar::WndProcDefault(UINT msg, WPARAM wparam, LPARAM lparam)
    {
        switch (msg)
        {
        case WM_WINDOWPOSCHANGING:  return OnWindowPosChanging(msg, wparam, lparam);
        case UWM_GETCTOOLBAR:       return reinterpret_cast<LRESULT>(this);
        }

        // pass unhandled messages on for default processing
        return CWnd::WndProcDefault(msg, wparam, lparam);
    }

} // namespace Win32xx

#endif // #ifndef _WIN32XX_TOOLBAR_H_
