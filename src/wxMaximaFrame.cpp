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


#include "wxMaximaFrame.h"
#include "Version.h"

#include <wx/artprov.h>

#ifndef __WXMSW__
#include "maximaicon.xpm"
#endif

wxMaximaFrame::wxMaximaFrame(wxWindow* parent, int id, const wxString& title,
                             const wxPoint& pos, const wxSize& size,
                             long style):
  wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE)
{
  panel = new wxPanel(this, -1);
  
  // menus
  frame_1_menubar = new wxMenuBar();
  SetMenuBar(frame_1_menubar);
  
  // File menu
  wxMenu* wxglade_tmp_menu_1 = new wxMenu();
  wxglade_tmp_menu_1->Append(menu_save_id, _("&Save session\tCtrl-S"),
                             _("Save session to a file"), wxITEM_NORMAL);
  wxglade_tmp_menu_1->Append(menu_open_id, _("&Open session\tCtrl-O"),
                             _("Open session from a file"), wxITEM_NORMAL);
/*
  wxglade_tmp_menu_1->Append(menu_sconsole_id, _("Save &console"),
                             _("Save console output"), wxITEM_NORMAL);
*/
  wxglade_tmp_menu_1->Append(menu_load_id, _("&Load package\tCtrl-L"),
                             _("Load a maxima package file"), wxITEM_NORMAL);
  wxglade_tmp_menu_1->Append(menu_batch_id, _("&Batch file\tCtrl-B"),
                             _("Batch maxima file"), wxITEM_NORMAL);
  wxglade_tmp_menu_1->AppendSeparator();
  wxglade_tmp_menu_1->Append(menu_select_file, _("Select &file"),
                             _("Select a file (copy filename to input line)"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_1->Append(menu_monitor_file, _("&Monitor file"),
                             _("Autoload a file when it is updated"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_1->AppendSeparator();
  wxglade_tmp_menu_1->Append(menu_print_setup, _("Print setup"),
                             _("Setup printer"));
  wxglade_tmp_menu_1->Append(menu_print, _("&Print\tCtrl-P"),
                             _("Print session"));
  wxglade_tmp_menu_1->AppendSeparator();
  wxglade_tmp_menu_1->Append(menu_exit_id, _("E&xit\tCtrl-Q"),
                             _("Exit wxMaxima"), wxITEM_NORMAL);
  frame_1_menubar->Append(wxglade_tmp_menu_1, _("&File"));
  
  // Maxima menu
  wxMenu* wxglade_tmp_menu_2 = new wxMenu();
  wxglade_tmp_menu_2->Append(menu_clear_screen, _("C&lear screen"),
                             _("Delete the contents of console."),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_2->Append(menu_copy_from_console, _("Copy"),
                             _("Copy selection from console"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_2->Append(menu_copy_lb_from_console, _("Copy text"),
                             _("Copy selection from console (including linebreaks)"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_2->Append(menu_delete_selection, _("Delete selection"),
                             _("Delete selected input/output group"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_2->Append(menu_goto_input, _("Go to input\tF4"),
                             _("Set focus to the input line"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_2->AppendSeparator();
  wxglade_tmp_menu_2->Append(menu_interrupt_id, _("&Interrupt\tCtrl-G"),
                            _("Interrupt current computation"), wxITEM_NORMAL);
  wxglade_tmp_menu_2->Append(menu_restart_id, _("&Restart maxima"),
                             _("Restart maxima"), wxITEM_NORMAL);
  wxglade_tmp_menu_2->Append(menu_soft_restart, _("&Soft restart"),
                             _("Restart maxima (softly)"), wxITEM_NORMAL);
  wxglade_tmp_menu_2->Append(menu_add_path, _("Add to &path"),
                             _("Add a directory to search path"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_2->AppendSeparator();
  wxglade_tmp_menu_2->Append(menu_functions, _("Show &functions"),
                             _("Show defined functions"), wxITEM_NORMAL);
  wxglade_tmp_menu_2->Append(menu_fun_def, _("Show &definition"),
                             _("Show definition of a function"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_2->Append(menu_variables, _("Show &variables"),
                             _("Show defined variables"), wxITEM_NORMAL);
  wxglade_tmp_menu_2->Append(menu_clear_fun, _("Delete f&unction"),
                             _("Delete a function"), wxITEM_NORMAL);
  wxglade_tmp_menu_2->Append(menu_clear_var, _("Delete v&ariable"),
                             _("Delete a variable"), wxITEM_NORMAL);
  wxglade_tmp_menu_2->AppendSeparator();
  wxglade_tmp_menu_2->Append(menu_time, _("Toggle &time display"),
                             _("Display time used for execution"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_2->Append(menu_display, _("Toggle &2d display"),
                             _("Toggle the 2d display of maxima output"), wxITEM_NORMAL);
  wxglade_tmp_menu_2->Append(menu_texform, _("Display Te&X form"),
                             _("Display expression in TeX form"), wxITEM_NORMAL);
  wxglade_tmp_menu_2->Append(menu_options_id, _("C&onfigure"),
                             _("Configure wxMaxima"), wxITEM_NORMAL);
  frame_1_menubar->Append(wxglade_tmp_menu_2, _("&Maxima"));

  // Equations menu
  wxMenu* wxglade_tmp_menu_3 = new wxMenu();
  wxglade_tmp_menu_3->Append(menu_solve, _("&Solve"),
                             _("Solve equation(s)"), wxITEM_NORMAL);
  wxglade_tmp_menu_3->Append(menu_allroots, _("Roots of &polynomial"),
                             _("Find all roots of a polynomial"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_3->Append(menu_realroots, _("&Roots of polynomial (real)"),
                             _("Find real roots of a polynomial"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_3->Append(menu_solve_lin, _("Solve &linear system"),
                             _("Solve linear system of equations"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_3->Append(menu_solve_algsys, _("Solve &algebraic system"),
                             _("Solve algebraic system of equations"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_3->Append(menu_eliminate, _("&Eliminate variable"),
                             _("Eliminate a variable from a system "
                               "of equations"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_3->AppendSeparator();
  wxglade_tmp_menu_3->Append(menu_solve_ode, _("Solve &ODE"),
                             _("Solve ordinary differential equation "
                               "of maximum degree 2"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_3->Append(menu_ivp_1, _("Initial value problem (&1)"),
                             _("Solve initial value problem for first"
                               " degree ODE"), wxITEM_NORMAL);
  wxglade_tmp_menu_3->Append(menu_ivp_2, _("Initial value problem (&2)"),
                             _("Solve initial value problem for second "
                               "degree ODE"), wxITEM_NORMAL);
  wxglade_tmp_menu_3->Append(menu_bvp, _("&Boundary value problem"),
                             _("Solve boundary value problem for second "
                               "degree ODE"), wxITEM_NORMAL);
  wxglade_tmp_menu_3->AppendSeparator();
  wxglade_tmp_menu_3->Append(menu_solve_de, _("Solve ODE with Lapla&ce"),
                             _("Solve ordinary differential equations "
                               "with Laplace transformation"), wxITEM_NORMAL);
  wxglade_tmp_menu_3->Append(menu_atvalue, _("A&t value"),
                             _("Setup atvalues for solving ODE with "
                               "Laplace transformation"), wxITEM_NORMAL);
  frame_1_menubar->Append(wxglade_tmp_menu_3, _("&Equations"));

  // Algebra menu
  wxMenu* wxglade_tmp_menu_4 = new wxMenu();
  wxglade_tmp_menu_4->Append(menu_gen_mat, _("&Generate matrix"),
                             _("Generate a matrix from a 2-dimensional array"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_4->Append(menu_enter_mat, _("&Enter matrix"),
                             _("Enter a matrix"), wxITEM_NORMAL);
  wxglade_tmp_menu_4->Append(menu_invert_mat, _("&Invert matrix"),
                             _("Compute the inverse of a matrix"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_4->Append(menu_cpoly, _("&Characteristic poly"),
                             _("Compute the characteristic polynomial "
                               "of a matrix"), wxITEM_NORMAL);
  wxglade_tmp_menu_4->Append(menu_determinant, _("&Determinant"),
                             _("Compute the determinant of a matrix"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_4->Append(menu_eigen, _("Eigen&values"),
                             _("Find eigenvalues of a matrix"), wxITEM_NORMAL);
  wxglade_tmp_menu_4->Append(menu_eigvect, _("Eige&nvectors"),
                             _("Find eigenvectors of a matrix"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_4->Append(menu_adjoint_mat, _("Ad&joint matrix"),
                             _("Compute the adjoint maxrix"), wxITEM_NORMAL);
  wxglade_tmp_menu_4->Append(menu_transpose, _("&Transpose matrix"),
                             _("Transpose a matrix"), wxITEM_NORMAL);
  wxglade_tmp_menu_4->AppendSeparator();
  wxglade_tmp_menu_4->Append(menu_map_mat, _("Ma&p to matrix"),
                             _("Map function to a matrix"), wxITEM_NORMAL);
  wxglade_tmp_menu_4->Append(menu_map, _("&Map to list"),
                             _("Map function to a list"), wxITEM_NORMAL);
  wxglade_tmp_menu_4->Append(menu_make_list, _("Make &list"),
                             _("Make list from expression"), wxITEM_NORMAL);
  wxglade_tmp_menu_4->Append(menu_apply, _("&Apply"),
                             _("Apply function to a list"), wxITEM_NORMAL);
  frame_1_menubar->Append(wxglade_tmp_menu_4, _("&Algebra"));

  // Calculus menu
  wxMenu*  wxglade_tmp_menu_6 = new wxMenu();
  wxglade_tmp_menu_6->Append(menu_integrate, _("&Integrate"),
                             _("Integrate expression"), wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_risch, _("Risch integration"),
                             _("Integrate expression with Risch algorithm"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_diff, _("&Differentiate"),
                             _("Differentiate expression"), wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_limit, _("Find &limit"),
                             _("Find a limit of an expression"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_series, _("Get &series"),
                             _("Get the Taylor or power series of expression"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_pade, _("P&ade approximation"),
                             _("Pade approximation of a Taylor series"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_sum, _("Calculate su&m"),
                             _("Calculate sums"), wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_unsum, _("U&nsum expression"),
                             _("What has to be summed to get this result"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_product, _("Calculate &product"),
                             _("Calculate products"), wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_laplace, _("Laplace &transform"),
                             _("Get Laplace transformation of an expression"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_ilt, _("Inverse Laplace t&ransform"),
                             _("Get inverse Laplace transformation of an expression"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_gcd, _("&Greatest common divisor"),
                             _("Compute the greatest common divisor"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_lcm, _("Least common multiple"),
                             _("Compute the least common multiple "
                               "(do load(functs) befor using)"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_divide, _("Di&vide polynomials"),
                             _("Divide numbers or polynomials"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_partfrac, _("Partial &fractions"),
                             _("Decompose rational function to partial fractions"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_continued_fraction, _("&Continued fraction"),
                             _("Compute continued fraction of a value"),
                             wxITEM_NORMAL);
  frame_1_menubar->Append(wxglade_tmp_menu_6, _("&Calculus"));

  // Simplify menu
  wxMenu* wxglade_tmp_menu_5 = new wxMenu();
  wxglade_tmp_menu_5->Append(menu_ratsimp, _("&Simplify expression"),
                             _("Simplify rational expression"), wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_radsimp, _("Simplify &radicals"),
                             _("Simplify expression containing radicals"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_logcontract, _("Contract logarithms"),
                             _("Convert sum of logarithms to logarithm of product"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_factor, _("&Factor expression"),
                             _("Factor an expression"), wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_gfactor, _("Factor &complex"),
                             _("Factor an expression in Gaussian numbers"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_expand, _("&Expand expression"),
                             _("Expand an expression"), wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_logexpand, _("Expand logarithms"),
                             _("Convert logarithm of product to sum of logarithms"),
                              wxITEM_NORMAL);
  wxglade_tmp_menu_5->AppendSeparator();
  wxglade_tmp_menu_5->Append(menu_to_fact, _("Convert to factorials"),
                             _("Convert binomials, beta and gamma function to factorials"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_to_gamma, _("Convert to gamma"),
                             _("Convert binomials, factorials and beta function to gamma function"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_factsimp, _("Simplify factoria&ls"),
                             _("Simplify an expression containing factorials"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_factcomb, _("Combine factorials"),
                             _("Combine factorials in an expression"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->AppendSeparator();
  wxglade_tmp_menu_5->Append(menu_trigsimp, _("Simplify &trigonometric"),
                             _("Simplify trigonometric expression"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_trigreduce, _("Reduce tr&igonometric"),
                             _("Reduce trigonometric expression"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_trigexpand, _("E&xpand trigonometric"),
                             _("Expand trigonometric expression"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_trigrat, _("Rationalize trigonometric"),
                             _("Rationalize trigonometrix expression"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->AppendSeparator();
  wxglade_tmp_menu_5->Append(menu_rectform, _("Convert t&o rectform"),
                             _("Convert complex expression to rect form"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_polarform, _("Convert to &polarform"),
                             _("Convert complex expression to polar form"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_realpart, _("Get real part"),
                             _("Get the real part of complex expression"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_imagpart, _("Get imaginary part"),
                             _("Get the imaginary part of complex expression"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_demoivre, _("&Demoivre"),
                             _("Convert exponential function of imaginary argument to trigonometric form"), wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_exponentialize, _("Expo&nentialize"),
                             _("Conver trigonometric functions to exponential form"), wxITEM_NORMAL);
  wxglade_tmp_menu_5->AppendSeparator();
  wxglade_tmp_menu_5->Append(menu_talg, _("Toggle &algebraic"),
                             _("Toggle algebraic computation"), wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_tellrat, _("Add algebraic e&quality"),
                             _("Add equality to the rational simplifier"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_5->Append(menu_modulus, _("&Modulus computation"),
                             _("Setup modulus computation"), wxITEM_NORMAL);
  frame_1_menubar->Append(wxglade_tmp_menu_5, _("&Simplify"));

  // Plot menu
  wxglade_tmp_menu_6 = new wxMenu();
  wxglade_tmp_menu_6->Append(gp_plot2, _("Plot &2d"),
                             _("Plot in 2 dimensions"), wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(gp_plot3, _("Plot &3d"),
                             _("Plot in 3 dimensions"), wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_plot_format, _("Plot &format"),
                             _("Set plot format"), wxITEM_NORMAL);
  frame_1_menubar->Append(wxglade_tmp_menu_6, _("&Plotting"));

  // Numeric menu
  wxglade_tmp_menu_6 = new wxMenu();
  wxglade_tmp_menu_6->Append(menu_num_out, _("Toggle &numeric output"),
                             _("Toggle numeric output"), wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_to_float, _("To &float"),
                             _("The float value of an expression"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_to_bfloat, _("To &bigfloat"),
                             _("The bigfloat value of an expression"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_6->Append(menu_set_precision, _("Set &precision"),
                             _("Set the floating point precision"),
                             wxITEM_NORMAL);
  frame_1_menubar->Append(wxglade_tmp_menu_6, _("&Numeric"));

  // Help menu
  wxMenu* wxglade_tmp_menu_7 = new wxMenu();
  wxglade_tmp_menu_7->Append(menu_help_id, _("Maxima &help\tF1"),
                             _("Show maxima help"), wxITEM_NORMAL);
  wxglade_tmp_menu_7->Append(menu_describe, _("&Describe\tCtrl-H"),
                             _("Show the description of a command"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_7->Append(menu_example, _("&Example"),
                             _("Show an example of usage"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_7->Append(menu_apropos, _("&Apropos"),
                             _("Show commands similar to"),
                             wxITEM_NORMAL);
  wxglade_tmp_menu_7->Append(menu_show_tip, _("Show &tip"),
                             _("Show a tip"), wxITEM_NORMAL);
  wxglade_tmp_menu_7->AppendSeparator();
  wxglade_tmp_menu_7->Append(menu_build_info, _("Build &info"),
                             _("Info about maxima build"), wxITEM_NORMAL);
  wxglade_tmp_menu_7->Append(menu_bug_report, _("&Bug report"),
                             _("Report bug"), wxITEM_NORMAL);
  wxglade_tmp_menu_7->AppendSeparator();
  wxglade_tmp_menu_7->Append(menu_about_id, _("About"),
                             _("About wxMaxima"), wxITEM_NORMAL);
  frame_1_menubar->Append(wxglade_tmp_menu_7, _("&Help"));

  // input line
  label_1 = new wxStaticText(panel, -1, _("INPUT:"));
  m_inputLine = new CommandLine(panel, input_line_id, wxT(""),
                                wxDefaultPosition, wxDefaultSize,
                                wxTE_PROCESS_ENTER|wxTE_PROCESS_TAB|
                                wxTE_RICH);
  button_0 = new wxBitmapButton(panel, button_enter,
                                wxArtProvider::GetBitmap(wxART_TICK_MARK,
                                                         wxART_HELP_BROWSER));
  button_1 = new wxBitmapButton(panel, button_long_input,
                                wxArtProvider::GetBitmap(wxART_NORMAL_FILE,
                                                         wxART_HELP_BROWSER));
  button_0->SetSize(button_1->GetSize());
  
  // buttons
  button_2 = new wxButton(panel, button_ratsimp, _("Simplify"));
  button_3 = new wxButton(panel, button_radcan, _("Simplify (r)"));
  button_4 = new wxButton(panel, button_factor, _("Factor"));
  button_5 = new wxButton(panel, button_expand, _("Expand"));
  button_6 = new wxButton(panel, button_trigsimp, _("Simplify (tr)"));
  button_7 = new wxButton(panel, button_trigexpand, _("Expand (tr)"));
  button_8 = new wxButton(panel, button_trigreduce, _("Reduce (tr)"));
  button_9 = new wxButton(panel, button_rectform, _("Rectform"));
  button_10 = new wxButton(panel, button_sum, _("Sum"));
  button_11 = new wxButton(panel, button_product, _("Product"));
  button_12 = new wxButton(panel, button_solve, _("Solve"));
  button_13 = new wxButton(panel, button_solve_ode, _("Solve ODE"));
  button_14 = new wxButton(panel, button_diff, _("Diff"));
  button_15 = new wxButton(panel, button_integrate, _("Integrate"));
  button_16 = new wxButton(panel, button_limit, _("Limit"));
  button_17 = new wxButton(panel, button_taylor, _("Series"));
  button_18 = new wxButton(panel, button_subst, _("Substitute"));
  button_19 = new wxButton(panel, button_map, _("Map"));
  button_20 = new wxButton(panel, button_plot2, _("Plot 2D"));
  button_21 = new wxButton(panel, button_plot3, _("Plot 3D"));
  
  // console
  m_console = new MathCtrl(panel, -1, wxDefaultPosition, wxDefaultSize);

  frame_1_statusbar = CreateStatusBar(1);
  
  set_properties();
  do_layout();
}

void wxMaximaFrame::set_properties()
{
  SetIcon(wxICON(maximaicon));
  SetTitle(wxString::Format(_("wxMaxima %s"), wxT(WXMAXIMA_VERSION)));
  // Set font for input line
#if defined(__WXGTK12__) && !defined(__WXGTK20__)
  m_inputLine->SetFont(wxFont(12, wxMODERN, wxNORMAL, wxNORMAL, 0, wxT("")));
#else
  m_inputLine->SetFont(wxFont(10, wxMODERN, wxNORMAL, wxNORMAL, 0, wxT("")));
#endif
  
  m_console->SetBackgroundColour(wxColour(wxT("WHITE")));
#if wxCHECK_VERSION(2, 5, 0)
  m_console->SetMinSize(wxSize(100, 100));
#endif

  button_0->SetToolTip(_("Enter command"));
  button_1->SetToolTip(_("Multiline input"));
  frame_1_statusbar->SetStatusText(_("Welcome to wxMaxima"), 0);
}

void wxMaximaFrame::do_layout()
{
  wxFlexGridSizer* grid_sizer_1 = new wxFlexGridSizer(3, 1, 0, 0);
  wxBoxSizer *sizer_1 = new wxBoxSizer(wxHORIZONTAL);
  wxGridSizer* grid_sizer_2 = new wxGridSizer(2, 10, 0, 0);
  wxFlexGridSizer* sizer_3 = new wxFlexGridSizer(1, 4, 0, 0);

  // buttons
  grid_sizer_2->Add(button_2, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_3, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_4, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_5, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_6, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_7, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_8, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_9, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_10, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_11, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_12, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_13, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_14, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_15, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_16, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_17, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_18, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_19, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_20, 0, wxALL|wxEXPAND, 0);
  grid_sizer_2->Add(button_21, 0, wxALL|wxEXPAND, 0);
   
  // input line
  sizer_3->Add(label_1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|
               wxALIGN_CENTER_VERTICAL, 2);
  sizer_3->Add(m_inputLine, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 2);
  sizer_3->Add(button_0, 0, wxALL, 2);
  sizer_3->Add(button_1, 0, wxALL, 2);
  sizer_3->AddGrowableCol(1);
  
  // all
  grid_sizer_1->Add(m_console, 1, wxALL|wxEXPAND, 2);
  grid_sizer_1->Add(sizer_3, 1, wxALL|wxEXPAND, 0);
  grid_sizer_1->Add(grid_sizer_2, 1, wxALL, 2);
  
  panel->SetAutoLayout(true);
  panel->SetSizer(grid_sizer_1);
  grid_sizer_1->Fit(panel);
  grid_sizer_1->SetSizeHints(panel);
  grid_sizer_1->AddGrowableRow(0);
  grid_sizer_1->AddGrowableCol(0);

  sizer_1->Add(panel, 1, wxEXPAND, 0);
  SetAutoLayout(true);
  SetSizer(sizer_1);
  Layout();
}