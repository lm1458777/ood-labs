// TextEditor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../TextEditorLib/Document.h"
#include "../TextEditorLib/Editor.h"
#include "../TextEditorLib/FileSystem.h"
#include "../TextEditorLib/Menu.h"

using namespace std;

namespace
{

class ErrorReporter : public IErrorReporter
{
public:
	explicit ErrorReporter(ostream& out)
		: m_out(out)
	{
	}

	void InvalidPosition() override
	{
		m_out << "Invalid position" << endl;
	}

	void InvalidSize() override
	{
		m_out << "Invalid image size" << endl;
	}

	void PositionOutOfRange() override
	{
		m_out << "Position is out of range" << endl;
	}

	void ReportError(const std::string& errorMsg) override
	{
		m_out << errorMsg.c_str() << endl;
	}

	void CantUndo() override
	{
		m_out << "Can't undo" << endl;
	}

	void CantRedo() override
	{
		m_out << "Can't redo" << endl;
	}

private:
	ostream& m_out;
};

} // namespace

int main()
{
	Document doc{ make_shared<FileSystem>() };
	ErrorReporter errorReporter{ cout };
	Editor editor{ doc, errorReporter, cout };
	Menu menu{ cin, cout };

	using MenuHandler = void (Editor::*)(std::istream & in);
	auto addMenuItem = [&](const string& shortcut, const string& args, const string& description, MenuHandler handler) {
		menu.AddItem(shortcut, args, description, bind(handler, &editor, placeholders::_1));
	};

	addMenuItem("InsertParagraph", "<position|end> <text>", "Insert paragraph at position.", &Editor::InsertParagraph);
	addMenuItem("InsertImage", "<position|end> <width> <height> <path>", "Insert image at position.", &Editor::InsertImage);
	addMenuItem("SetTitle", "<document title>", "Set document title.", &Editor::SetTitle);
	menu.AddItem("List", "", "List document title and items.", [&](istream& /*in*/) { editor.List(); });
	addMenuItem("ReplaceText", "<position> <new text>", "Replace text at position.", &Editor::ReplaceText);
	addMenuItem("ResizeImage", "<position> <new width> <new height>", "Resize image at position.", &Editor::ResizeImage);
	addMenuItem("DeleteItem", "<position>", "Delete item at position.", &Editor::DeleteItem);
	menu.AddItem("Help", "", "Show help.", [&](istream&) { menu.ShowInstructions(); });
	menu.AddItem("Undo", "", "Undo last command.", [&](istream& /*in*/) { editor.Undo(); });
	menu.AddItem("Redo", "", "Redo undone command.", [&](istream& /*in*/) { editor.Redo(); });
	menu.AddItem("Save", "<html path>", "Save html document to path.", [&](istream& in) { editor.Save(in); });
	menu.AddItem("Exit", "", "Exit app.", [&](istream& /*in*/) { menu.Exit(); });

	menu.Run();

	return 0;
}
