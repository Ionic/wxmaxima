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

#include "SystemWiz.h"

SysWiz::SysWiz(wxWindow* parent, int id, const wxString& title, int numEq,
               const wxPoint& pos, const wxSize& sz, long style):
  wxDialog(parent, id, title, pos, sz, wxDEFAULT_DIALOG_STYLE)
{
  size = numEq;
  label_1 = new wxStaticText(this, -1, title);
  for (int i=0; i<size; i++) {
    inputs.push_back(new BTextCtrl(this, -1, wxT("0"), wxDefaultPosition,
                                   wxSize(230,-1)));
  }
  variables = new BTextCtrl(this, -1, wxT(""), wxDefaultPosition,
                            wxSize(230,-1));
  static_line_1 = new wxStaticLine(this, -1);
  button_1 = new wxButton(this, wxOK, _("OK"));
  button_2 = new wxButton(this, wxCANCEL, _("Cancel"));
  button_1->SetDefault();

  set_properties();
  do_layout();

  ok = false;
}

void SysWiz::set_properties()
{
  label_1->SetFont(wxFont(20, wxROMAN, wxITALIC, wxNORMAL, 0, wxT("")));
  variables->SetToolTip(_("Enter comma separated list of variables."));
}

void SysWiz::do_layout()
{
  wxFlexGridSizer* grid_sizer_1 = new wxFlexGridSizer(4, 1, 3, 3);
  wxFlexGridSizer* grid_sizer_2 = new wxFlexGridSizer(size+1, 2, 1, 3);
  wxBoxSizer* sizer_1 = new wxBoxSizer(wxHORIZONTAL);
  wxStaticText* text;
  for (int i=1; i<=size; i++) {
    text = new wxStaticText(this, -1, wxString::Format(_("Equation %d:"), i));
    grid_sizer_2->Add(text, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 1);
    grid_sizer_2->Add(inputs[i-1], 0, wxALL, 1);
  }
  text = new wxStaticText(this, -1, _("Variables:"));
  grid_sizer_2->Add(text, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 0);
  grid_sizer_2->Add(variables, 0, wxALL, 1);
  grid_sizer_1->Add(label_1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 3);
  grid_sizer_1->Add(grid_sizer_2, 1, wxEXPAND, 0);
  grid_sizer_1->Add(static_line_1, 0, wxEXPAND, 0);
  sizer_1->Add(button_1, 0, wxALL, 2);
  sizer_1->Add(button_2, 0, wxALL, 2);
  grid_sizer_1->Add(sizer_1, 1, wxALIGN_RIGHT, 0);
  SetAutoLayout(true);
  SetSizer(grid_sizer_1);
  grid_sizer_1->Fit(this);
  grid_sizer_1->SetSizeHints(this);
  Layout();
}

wxString SysWiz::getValue()
{
  wxString cmd = wxT("([");
  for (int i=0; i<size; i++) {
    cmd += inputs[i]->GetValue();
    if (i<size-1)
      cmd += wxT(", ");
  }
  cmd += wxT("], [") + variables->GetValue() + wxT("]);");
  return cmd;
}

void SysWiz::onButton(wxCommandEvent& event)
{
  if (event.GetId() == wxOK)
    ok = true;
  Close();
}

BEGIN_EVENT_TABLE(SysWiz, wxDialog)
  EVT_BUTTON(wxOK, SysWiz::onButton)
  EVT_BUTTON(wxCANCEL, SysWiz::onButton)
END_EVENT_TABLE()