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

#include "DiffCell.h"

DiffCell::DiffCell() : MathCell()
{
  m_baseCell = NULL;
  m_diffCell = NULL;
}

DiffCell::~DiffCell()
{
  if (m_baseCell != NULL)
    delete m_baseCell;
  if (m_diffCell != NULL)
    delete m_diffCell;
  if (m_next != NULL)
    delete m_next;
}

MathCell* DiffCell::Copy(bool all)
{
  DiffCell* tmp = new DiffCell;
  tmp->SetDiff(m_diffCell->Copy(true));
  tmp->SetBase(m_baseCell->Copy(true));
  if (all && m_nextToDraw!= NULL)
    tmp->AppendCell(m_nextToDraw->Copy(all));
  return tmp;
}

void DiffCell::Destroy()
{
  if (m_baseCell != NULL)
    delete m_baseCell;
  if (m_diffCell != NULL)
    delete m_diffCell;
  m_baseCell = NULL;
  m_diffCell = NULL;
  m_next = NULL;
}

void DiffCell::SetDiff(MathCell *diff)
{
  if (diff == NULL)
    return;
  if (m_diffCell != NULL)
    delete m_diffCell;
  m_diffCell = diff;
}

void DiffCell::SetBase(MathCell *base)
{
  if (base == NULL)
    return;
  if (m_baseCell != NULL)
    delete m_baseCell;
  m_baseCell = base;
}

void DiffCell::RecalculateWidths(CellParser& parser, int fontsize, bool all)
{
  double scale = parser.GetScale();
  m_baseCell->RecalculateWidths(parser, fontsize, true);
  m_diffCell->RecalculateWidths(parser, fontsize, true);
  m_width = m_baseCell->GetFullWidth(scale) + m_diffCell->GetFullWidth(scale);
  MathCell::RecalculateWidths(parser, fontsize, all);
}

void DiffCell::RecalculateSize(CellParser& parser, int fontsize, bool all)
{
  m_baseCell->RecalculateSize(parser, fontsize, true);
  m_diffCell->RecalculateSize(parser, fontsize, true);
  m_height = MAX(m_baseCell->GetMaxHeight(), m_diffCell->GetMaxHeight());
  m_center = MAX(m_diffCell->GetMaxCenter(), m_baseCell->GetMaxCenter());
  MathCell::RecalculateSize(parser, fontsize, all);
}

void DiffCell::Draw(CellParser& parser, wxPoint point, int fontsize, bool all)
{
  if (DrawThisCell(parser, point)) {
    wxPoint bs, df;
    df.x = point.x;
    df.y = point.y;
    m_diffCell->Draw(parser, df, fontsize, true);
  
    bs.x = point.x + m_diffCell->GetFullWidth(parser.GetScale());
    bs.y = point.y;
    m_baseCell->Draw(parser, bs, fontsize, true);
  }
  
  MathCell::Draw(parser, point, fontsize, all);
}

wxString DiffCell::ToString(bool all) {
  MathCell* tmp = m_baseCell->m_next;
  wxString s = wxT("'diff(");
  if (tmp != NULL)
    s += tmp->ToString(true);
  s += m_diffCell->ToString(true);
  s += wxT(")");
  s += MathCell::ToString(all);
  return s;
}

void DiffCell::SelectInner(wxRect& rect, MathCell** first, MathCell** last)
{
  *first = NULL;
  *last = NULL;
  if (m_baseCell->ContainsRect(rect))
    m_baseCell->SelectRect(rect, first, last);
  if (*first == NULL || *last == NULL) {
    *first = this;
    *last = this;
  }
}