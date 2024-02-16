#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#include<iostream>
#include<fstream>

struct pathReturn
{
    int errorCode;           // Error code indicating the result of the saveAsDialog function.
    const char* filePath;    // File path selected by the user.
};

//Following fucntions credit Microsoft documentation and Windows API documentation

/*
* Function: saveAsDialog
* Arguments: const wchar_t windowTitle[MAX_PATH], HWND owner, LPCWSTR filter
* Warnings: Default arguments [L"Save File", NULL, L"All Files (*.*)\0*.*\0"]
* Description: Opens the Windows save file dialog
* Returns: Struct with values int sucess where 0 is sucess and -1 is error and string const char* path where value "Error" is returned if error path if sucess
*/
pathReturn saveAsDialog(const wchar_t windowTitle[MAX_PATH] = L"Save File", HWND owner = NULL, LPCWSTR filter = L"All Files (*.*)\0*.*\0")
{
    // Initialize the OPENFILENAME structure and file name buffer.
    OPENFILENAME ofn;
    wchar_t fileName[MAX_PATH] = L"";

    // Clear the OPENFILENAME structure.
    ZeroMemory(&ofn, sizeof(ofn));

    // Set the OPENFILENAME structure members.
    ofn.lStructSize = sizeof(OPENFILENAME);
    // If there is a window to center over, put its HANDLE here
    ofn.hwndOwner = owner;
    // Set the file filter
    ofn.lpstrFilter = filter;
    // Set the file name buffer
    ofn.lpstrFile = fileName;
    // Set the maximum file name length
    ofn.nMaxFile = MAX_PATH;
    // Set the window title
    ofn.lpstrTitle = windowTitle;
    // Set the dialog flags
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

    // Display the save file dialog and return the result.
    if (GetSaveFileNameW(&ofn))
    {
        return pathReturn{ 0, (const char*)fileName };
    }
    else
    {
        return pathReturn{ -1, "Error" };
    }
}

/*
* Function: openFileDialog
* Arguments: const wchar_t windowTitle[MAX_PATH], HWND owner, LPCWSTR filter
* Warnings: Default arguments [L"Open File", NULL, L"All Files (*.*)\0*.*\0"]
* Description: Opens the Windows open file dialog
* Returns: Struct with values int sucess where 0 is sucess and -1 is error and string const char* path where value "Error" is returned if error path if sucess
*/
pathReturn openFileDialog(const wchar_t windowTitle[MAX_PATH] = L"Open File", HWND owner = NULL, LPCWSTR filter = L"All Files (*.*)\0*.*\0")
{
    // Initialize the OPENFILENAME structure and file name buffer.
    OPENFILENAME ofn;
    wchar_t fileName[MAX_PATH] = L"";

    // Clear the OPENFILENAME structure.
    ZeroMemory(&ofn, sizeof(ofn));

    // Set the OPENFILENAME structure members.
    ofn.lStructSize = sizeof(OPENFILENAME);
    // If you have a window to center over, put its HANDLE here
    ofn.hwndOwner = owner;
    // Set the file filter
    ofn.lpstrFilter = filter;
    // Set the file name buffer
    ofn.lpstrFile = fileName;
    // Set the maximum file name length
    ofn.nMaxFile = MAX_PATH;
    // Set the window title
    ofn.lpstrTitle = windowTitle;
    // Set the dialog flags
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

    // Display the open file dialog and return the result.
    if (GetOpenFileNameW(&ofn))
    {
        return pathReturn{ 0, (const char*)fileName };
    }
    else
    {
        return pathReturn{ -1, "Error" };
    }
}

/*
* Function: folderSelectionDialog
* Arguments: None
* Warnings: None
* Description: Opens the Windows folder selection dialog
* Returns: Struct with values int sucess where 0 is sucess and -1 is error and string const char* path where value "Error" is returned if error path if sucess
*/
pathReturn folderSelectionDialog()
{
    // Initialize COM
    IFileDialog* pfd;
    // CoCreate the File Open Dialog object.
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));

    // Show the File Open Dialog
    if (SUCCEEDED(hr))
    {
        // Set the options on the dialog.
        DWORD dwOptions;
        // Before setting, always get the options first in order not to override existing options.
        hr = pfd->GetOptions(&dwOptions);

        // In this case, get shell items only for file system items.
        if (SUCCEEDED(hr))
        {
            // Add the pick folders option.
            hr = pfd->SetOptions(dwOptions | FOS_PICKFOLDERS);
        }

        // Show the dialog
        if (SUCCEEDED(hr))
        {
            // Show the Open dialog box.
            hr = pfd->Show(NULL);
            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem* psi;
                hr = pfd->GetResult(&psi);

                if (SUCCEEDED(hr))
                {
                    PWSTR path;
                    // Get the path of the file
                    hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &path);

                    if (SUCCEEDED(hr))
                    {
                        return pathReturn{ 0, (const char*)path };
                        CoTaskMemFree(path);
                    }

                    // Release the IShellItem object.
                    psi->Release();
                }
            }

            else
            {
                return pathReturn{ -1, "Error" };
            }
        }

        pfd->Release();
    }

    CoUninitialize();
}