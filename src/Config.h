/*
 *  Copyright (C) 2004-2005 Andrej Vodopivec <andrejv@users.sourceforge.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <wx/wx.h>
#include <wx/image.h>

#include <wx/spinctrl.h>
#include <wx/notebook.h>

#ifndef CONFIG_H
#define CONFIG_H

#include "TextStyle.h"

enum {
  mp_browse_id,
  mf_browse_id,
  combobox_colour,
  combobox_styleFor,
  checkbox_bold,
  checkbox_italic,
  checkbox_underlined,
  checkbox_header
};

class Config: public wxDialog {
public:
  Config(wxWindow* parent, int id, const wxString& title,
         const wxPoint& pos=wxDefaultPosition,
         const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);
  bool isOk() { return m_ok; }
private:
  // begin wxGlade: Config::methods
  void set_properties();
  void do_layout();
  // end wxGlade
protected:
  // begin wxGlade: Config::attributes
  wxStaticBox* sizer_11_staticbox;
  wxStaticBox* sizer_9_staticbox;
  wxStaticBox* sizer_6_staticbox;
  wxStaticBox* sizer_4_staticbox;
  wxStaticText* label_1;
  wxStaticText* label_5;
  wxTextCtrl* m_maximaProgram;
  wxButton* m_mpBrowse;
  wxStaticText* label_6;
  wxTextCtrl* m_additionalParameters;
  wxStaticText* label_4;
  wxComboBox* m_language;
  wxCheckBox* m_saveSize;
  wxCheckBox* m_matchParens;
  wxCheckBox* m_showLong;
  wxCheckBox* m_showHeader;
  wxPanel* notebook_1_pane_1;
  wxStaticText* label_7;
  wxSpinCtrl* m_fontSize;
  wxStaticText* label_8;
  wxComboBox* m_fontFamily;
  wxComboBox* m_styleFor;
  wxComboBox* m_styleColor;
  wxCheckBox* m_styleBold;
  wxCheckBox* m_styleItalic;
  wxCheckBox* m_styleUnderlined;
  wxPanel* notebook_1_pane_2;
  wxNotebook* notebook_1;
  wxButton* m_buttonOK;
  wxButton* m_buttonCancel;
  style m_styleNormalText, m_styleHiddenText, m_styleMainPrompt,
        m_styleOtherPrompt, m_styleLabel, m_styleSpecial, m_styleInput;
  // end wxGlade
  bool m_ok;
  void onOk(wxCommandEvent& event);
  void onCancel(wxCommandEvent& event);
  void onMpBrowse(wxCommandEvent& event);
  void onChangeStyle(wxCommandEvent& event);
  void onChangeColor(wxCommandEvent& event);
  void onCheckbox(wxCommandEvent& event);
  void readStyles();
  void writeStyles();
  void setupFontList();
  style* GetStylePointer();
  DECLARE_EVENT_TABLE()
};


#endif // CONFIG_H