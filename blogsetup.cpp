#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void replaceAll(string& str, const string& from, const string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

void makefile(string start, string dest, vector<string> reps) {
  ifstream fin;
  fin.open(start.c_str());
  ofstream fout;
  fout.open(dest.c_str());
  string line;
  while (getline(fin, line)) {
   replaceAll(line, "##cwd##", reps[0]);
   replaceAll(line, "##wsn##", reps[1]);
   replaceAll(line, "##bgt##", reps[2]);
   replaceAll(line, "##bgn##", reps[3]);
   fout << line << endl;
  }
}

int main() {

  // get the shizzle

  cout << endl << "BlogR Setup" << endl << endl;
  string webServer;
  string currDir;
  string bgName;
  string bgTitle;
  cout << "Enter the name of your web server, for example, 'example.com': ";
  cin >> webServer;
  cout << "Enter the name of your CWD, omitting the path to your webdocs (type '/' for the web server root): ";
  cin >> currDir;
  cout << "Enter the Blog Name: ";
  cin.clear();
  getline(cin, bgName);
  getline(cin, bgName);
  cout << "Enter the Blog Title: ";
  getline(cin, bgTitle);
  cout << endl << "Setting up your blog..." << endl;
  vector<string> reps;
  reps.push_back(currDir); reps.push_back(webServer); reps.push_back(bgTitle); reps.push_back(bgName);

  // put the shizzle in the admin panel

  makefile("bg-admin.txt", "bg-admin.php", reps);
  
  // put the shizzle in the theme config

  ofstream tconf;
  tconf.open("themes/themeconfig.ini");
  tconf << "basic" << endl << webServer << endl << currDir << endl << bgName << endl << bgTitle;

  // put the shizzle in the rss header

  makefile("xml-header.txt", "xml-header.blg", reps);

  // put the shizzle in the basic theme

  makefile("themes/basic/header.txt", "themes/basic/header.blg", reps);

  // load the basic theme rss page

  makefile("themes/basic/rsspage.blg", "rss-style.xsl", reps);

return 0;
}