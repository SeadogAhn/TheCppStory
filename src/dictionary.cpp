#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <utility>
#include <stdexcept>

class Dictionary{
public:
    typedef std::multimap< std::string, std::string >   DicContainer;
    typedef DicContainer::iterator                      iterator;
    typedef DicContainer::const_iterator                const_iterator;
    typedef DicContainer::size_type                     size_type;
    typedef std::pair< std::string, std::string >       record;

    Dictionary(){}
    ~Dictionary(){}
    //! dictionary initialize
    /*!
        word dictionary file format
        (word),(description)
    */
    void initData( std::istream &is );
    //! It insert word & description in dictionary container.
    void addWord( const std::string &word, const std::string &desc );
    //! find word
    void findWord( const std::string &word, std::ostream &os );
    //! Return number of dictionary size
    size_type getWordCount() const { return dic_.size(); }

private:
    // copy constructor & operator= don't use.
    Dictionary( const Dictionary& );
    Dictionary& operator= ( const Dictionary& );
    //! split string by delim
    record splitString( const std::string &str, char delim = ',' );
    //! delete round braket
    std::string delRoundBracket( const std::string &str )
    {
        return str.substr( str.find( '(' )+1, str.find( ')' )-1 );
    }

    DicContainer dic_;
};

void Dictionary::initData( std::istream &is )
{
    try{
        std::string strLine;
        while( !is.eof() ){
            std::getline( is, strLine );
            if( strLine.empty() ) continue;
            dic_.insert( splitString( strLine ) );
        }
    }
    catch ( const std::exception & error ){
        throw error;
    }
    catch ( ... )
    {
        throw;
    }
}

void Dictionary::addWord( const std::string &word, const std::string &desc )
{
    dic_.insert( std::make_pair( word, desc ) );
}

Dictionary::record Dictionary::splitString( const std::string &str, char delim )
{
    std::string word, desc;

    size_t pos = str.find_first_of( delim );
    if( pos == std::string::npos ) throw std::domain_error( "Couldn't find deliminator charactor!" );

    word = str; word.erase( pos );
    desc = str; desc.erase( 0, pos+1 );

    return record( delRoundBracket( word ), delRoundBracket( desc ) );
}

void Dictionary::findWord( const std::string &word, std::ostream &os )
{
    for( iterator recordpos = dic_.lower_bound( word ) ; recordpos != dic_.upper_bound( word ) ; ++recordpos ){
        os << "Word : " << recordpos->first << "\t Description : " << recordpos->second << std::endl;
    }
}

#include <memory>

using namespace std;

int main()
{
    try{
        ifstream dicFile( "dic.txt" );

        // declraration dic
        unique_ptr< Dictionary > dic( new Dictionary );
        // dictionary data initialize
        dic->initData( dicFile );

        dic->findWord( "test", cout );
        dic->addWord( "help", "to give or provide what is necessary to accomplish a task or satisfy a need." );
    	dic->findWord( "help", cout );
    }
    catch ( const exception& error ){
        cerr << error.what() << endl;
        exit( EXIT_FAILURE );
    }
    catch ( ... ){
        cerr << "Unknown error catched, process has been halted!" << endl;
        exit( EXIT_FAILURE );
    }

	return EXIT_SUCCESS;
}
