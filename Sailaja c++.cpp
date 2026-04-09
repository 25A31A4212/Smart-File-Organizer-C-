#include <iostream>
#include <filesystem>
using namespace std;
namespace fs = filesystem;

void organizeFiles(const string& path) {
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            string ext = entry.path().extension().string();
            string targetFolder;

            if (ext == ".jpg" || ext == ".png") {
                targetFolder = path + "/Images";
            }
            else if (ext == ".pdf" || ext == ".docx") {
                targetFolder = path + "/Documents";
            }
            else if (ext == ".mp4" || ext == ".mkv") {
                targetFolder = path + "/Videos";
            }
            else {
                targetFolder = path + "/Others";
            }

            fs::create_directory(targetFolder);
            fs::rename(entry.path(), targetFolder + "/" + entry.path().filename().string());
        }
    }
}

int main() {
    string folderPath;

    cout << "Enter folder path: ";
    cin >> folderPath;

    try {
        organizeFiles(folderPath);
        cout << "Files organized successfully!" << endl;
    }
    catch (exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
