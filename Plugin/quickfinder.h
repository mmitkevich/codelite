#ifndef __quickfinder__
#define __quickfinder__

#include <wx/string.h>

class IManager;

class QuickFinder {
	static IManager *m_manager;
public:

	static void Initialize(IManager *manager);
	/**
	 * @brief open a workspae file
	 * @param s
	 */
	static bool OpenWorkspaceFile(const wxString &s);
	
	/**
	 * @brief set the focus to the active editor
	 */
	static void FocusActiveEditor();

};
#endif // __quickfinder__
