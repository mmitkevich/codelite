#include "clSingleChoiceDialog.h"

clSingleChoiceDialog::clSingleChoiceDialog(wxWindow* parent, const wxArrayString& options, int initialSelection)
    : clSingleChoiceDialogBase(parent)
{
    if(!options.IsEmpty()) {
        m_listBox->Append(options);
        if(initialSelection >= 0 && initialSelection < (int)options.size()) {
            m_listBox->Select(initialSelection);
        }
    }
    CenterOnParent();
}

clSingleChoiceDialog::~clSingleChoiceDialog() {}

void clSingleChoiceDialog::OnOKUI(wxUpdateUIEvent& event) { event.Enable(m_listBox->GetSelection() != -1); }

wxString clSingleChoiceDialog::GetSelection() const
{
    if(m_listBox->GetSelection() != wxNOT_FOUND) {
        return m_listBox->GetStringSelection();
    }
    return "";
}
