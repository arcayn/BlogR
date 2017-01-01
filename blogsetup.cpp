// import them standard shizzles

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>

// because I'm a scrub

using namespace std;

// function for replacing shizzle in shiznit

void replaceAll(string& str, const string& from, const string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

// function for putting shizzle in shiznit

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
   replaceAll(line, "##pwd##", reps[4]);
   replaceAll(line, "##usr##", reps[5]);
   replaceAll(line, "%#cwd##", "##cwd##");
   replaceAll(line, "%#wsn##", "##wsn##");
   replaceAll(line, "%#bgt##", "##bgt##");
   replaceAll(line, "%#bgn##", "##bgn##");
   fout << line << endl;
  }
}

int main() {

  // get the shizzle

  cout << endl << "BlogR Setup" << endl << "PLEASE NOTE: No changes will be made to any files external to BlogR" << endl << endl;
  string webServer;
  string currDir;
  string bgName;
  string bgTitle;
  string usrname;
  string pwrd;
  cout << "Enter the name of your web server, for example, 'example.com': ";
  cin >> webServer;
  cout << "Enter the name of your CWD, omitting the path to /var/www (type '/' for the web server root): ";
  cin >> currDir;
  cout << "Enter the Blog Name: ";
  cin.clear();
  getline(cin, bgName);
  getline(cin, bgName);
  cout << "Enter the Blog Title: ";
  getline(cin, bgTitle);
  cout << "Enter the admin panel username: ";
  getline(cin, usrname);
  cout << "Enter the admin panel password: ";
  getline(cin, pwrd);
  cout << endl << "Setting up your blog..." << endl;
  vector<string> reps;
  reps.push_back(currDir); reps.push_back(webServer); reps.push_back(bgTitle); reps.push_back(bgName); reps.push_back(pwrd); reps.push_back(usrname);

  // put the shizzle in the admin panel

  makefile("bg-admin.txt", "bg-admin.php", reps);
  
  // put the shizzle in the theme config

  ofstream tconf;
  tconf.open("themes/themeconfig.ini");
  tconf << "basic" << endl << webServer << endl << currDir << endl << bgName << endl << bgTitle;

  // put the shizzle in the rss stuff

  makefile("xml-header.txt", "xml-header.blg", reps);
  makefile("xml-footer.txt", "xml-footer.blg", reps);

  // put the shizzle in the basic theme (only header has any variable stuff here)

  makefile("themes/basic/header.txt", "themes/basic/header.blg", reps);

  // put the shizzle in the post display script

  makefile("archive/post-display.txt", "archive/post-display.php", reps);

  // load the basic theme rss page

  makefile("themes/basic/rsspage.blg", "rss-style.xsl", reps);

  // make the empty dirs

  struct stat info;

  if (stat("posts", &info) != 0) {system("mkdir posts");}
  if (stat("xml-posts", &info) != 0) {system("mkdir xml-posts");}
  if (stat("categories", &info) != 0) {system("mkdir categories");}
  if (stat("uploads", &info) != 0) {system("mkdir uploads");}

  // U DID IT

  cout << "Done!" << endl << endl;

  // bc main

  return 0;

}
