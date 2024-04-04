#include "startingOrProduct.hpp"
#include "Reagent.hpp"

struct concentrationTable {
    float M1 = -1;
    float M2 = -1;
    float V1 = -1;
    float V2 = -1;
};

struct pathReturn
{
    int errorCode;           // Error code indicating the result of the saveAsDialog function.
    const char* filePath;    // File path selected by the user.
};

/*
* Function: concentrationCalc
* Arguments: concentrationTable calcTable, char calcVar
* Warnings: None
* Description: Calculates the missing variable in a concentration table
* Returns: The calculated value
*/
float concentrationCalc(concentrationTable calcTable, char calcVar)
{
    switch (calcVar)
    {
    case 'M':
        if (calcTable.M2 == -1) {
            return (calcTable.M1 * calcTable.V1) / calcTable.V2;
        }
        else if (calcTable.M1 == -1) {
            return (calcTable.M2 * calcTable.V2) / calcTable.V1;
        }
        else {
            return -1;
        }

    case 'V':
        if (calcTable.V2 > 0) {
            return (calcTable.M1 * calcTable.V1) / calcTable.M2;
        }
        else if (calcTable.V1 > 0) {
            return (calcTable.M2 * calcTable.V2) / calcTable.M1;
        }
        else {
            return -1;
        }

    default:
        return -1;
    }
}

/*
* Function: toChar
* Arguments: wchar_t* str
* Warnings: None
* Description: Converts a wide char string to a char string
* Returns: The converted string
* https://learn.microsoft.com/en-us/cpp/text/how-to-convert-between-various-string-types?view=msvc-170
*/
char* toChar(const wchar_t* str)
{
    size_t len = wcslen(str) + 1;
    char* cStr = new char[len];
    size_t convertedChars = 0;
    wcstombs_s(&convertedChars, cStr, len, str, _TRUNCATE);
    return cStr;
}

/*
* Function: convertReagent
* Arguments: startingOrProduct* convertee, startingOrProduct* startingMaterial
* Warnings: None
* Description: Converts a startingOrProduct to a reagent
* Returns: reagent*
*/
reagent* convertReagent(startingOrProduct* convertee, startingOrProduct* startingMaterial) {
    reagent* converted = new reagent(convertee->baseCompound);
    converted->setMol(convertee->getMol());
    converted->setMV(convertee->getMV(), convertee->getMVU());
    converted->setEquivalents(1);

    converted->calculateReagent(startingMaterial);

    return converted;
}

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
        std::wstring selectedFileName = fileName;
        std::wstring selectedFileType = ofn.lpstrFilter;

        size_t fileTypeStart = selectedFileType.find(L"*.") + 1;
        std::wstring fileType = selectedFileType.substr(fileTypeStart, (selectedFileType.find(L")", fileTypeStart)) - fileTypeStart);

        // Check if the selected file name already has an extension
        if (selectedFileName.find(fileType) == std::wstring::npos)
        {
            selectedFileName += fileType;
        }

        return pathReturn{ 0, toChar(selectedFileName.c_str()) };
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
        std::wstring selectedFileName = fileName;
        std::wstring selectedFileType = ofn.lpstrFilter;

        size_t fileTypeStart = selectedFileType.find(L"*.") + 1;
        size_t fileTypeEnd = selectedFileType.find(L")", fileTypeStart);
        std::wstring fileType = selectedFileType.substr(fileTypeStart, fileTypeEnd - fileTypeStart);

        // Check if the selected file name already has an extension
        auto temp = selectedFileName.find(fileType);
        auto temp2 = std::wstring::npos;
        if (selectedFileName.find(fileType) == std::wstring::npos)
        {
            selectedFileName += fileType;
        }

        return pathReturn{ 0, toChar(selectedFileName.c_str()) };
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
    pathReturn rv = { 0, nullptr };
    if (FAILED(CoInitialize(NULL))) { return { -1, "CoInitialize failed" }; }
    IFileDialog* pfd;
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd));

    if (SUCCEEDED(hr))
    {
        DWORD dwOptions;
        hr = pfd->GetOptions(&dwOptions);
        if (SUCCEEDED(hr))
        {
            hr = pfd->SetOptions(dwOptions | FOS_PICKFOLDERS);
        }
        else { rv = { -2, "Failed to get options" }; }


        if (SUCCEEDED(hr))
        {
            hr = pfd->Show(NULL);
            if (SUCCEEDED(hr))
            {
                IShellItem* psi;
                hr = pfd->GetResult(&psi);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszPath;
                    hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &pszPath);
                    if (SUCCEEDED(hr))
                    {
                        std::wcout << pszPath << std::endl;
                        rv = { 0, toChar(pszPath) };
                        CoTaskMemFree(pszPath);
                    }
                    else
                    {
                        rv = { -6, "Failed to get display name" };
                    }
                    psi->Release();
                }
                else { rv = { -3, "Failed to get result" }; }
            }
            else { rv = { -4, "Failed to show dialog" }; }
        }
        else { rv = { -5, "Failed to set options" }; }
        pfd->Release();
    }
    else { rv = { -1, "CoCreateInstance failed" }; }
    CoUninitialize();
    return rv;
}