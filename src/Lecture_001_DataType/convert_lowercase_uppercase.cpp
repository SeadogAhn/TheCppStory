#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void predicate( char& ch ) { ch ^= 0x20; }

int main(int argc, char *argv[])
{

    ifstream ifs("org.txt");
    ofstream ofs("trs.txt");

    string strOneLine;

    ifs >> strOneLine;
    while ( !strOneLine.empty() && !ifs.eof() ) {
        for_each( strOneLine.begin(), strOneLine.end(), predicate );
        ofs << strOneLine << endl;
        ifs >> strOneLine;
    }

    ifs.close();
    ofs.close();

    return 0;
}

/* org.txt
abcdEFGHijklMNOP
asdfEFDF
*/
