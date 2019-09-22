#include <algorithm>
#include <vector>
#include <string>

typedef std::vector<std::string> Vec_STR;

bool fnNotWhiteSpace(char c) { return !std::isspace(c); }
bool fnWhiteSpace(char c) { return std::isspace(c); }

//! predicate function object for string compare
class CFOStringCompare : public std::binary_function< std::string, std::string, bool > {
public:
    bool operator()( const std::string &str1, const std::string &str2 ) const
    {
        return ( str1.find( str2 + "_" ) != std::string::npos );
    }
};

//! predicate function object for string compare
class CFOCharCompare : public std::binary_function< char, char, bool > {
public:
    bool operator()( char c1, char c2 ) const
    {
        return ( c1 == c2 );
    }
};

std::string fnStringTrim( const std::string &str )
{
    std::string::const_iterator i = std::find_if(str.begin(), str.end(), fnNotWhiteSpace);
    std::string::const_iterator j = std::find_if(i, str.end(), fnWhiteSpace);
    return (std::string(i,j));
}

Vec_STR fnStringSpliter( const std::string &str, char c, bool trimoption )
{
    typedef std::string::const_iterator iter;
    Vec_STR vs;
    iter i=str.begin();

    while(i!=str.end()){
        iter j=std::find_if(i,str.end(), std::bind2nd( CFOCharCompare(), c ) );
        if( i == j ) vs.push_back("");
        else{
            if( trimoption ){
                vs.push_back( fnStringTrim( std::string(i,j) ) );
            }
            else{
                vs.push_back(std::string(i,j));
            }
        }

        if( j != str.end() ) i = ++j;
        else i = j;
    }
    return vs;
}

Vec_STR fnStringSpliter( const std::string &str, bool (*predicate)(char c), bool trimoption )
{
    typedef string::const_iterator iter;
    Vec_STR vs;
    iter i=str.begin();

    while(i!=str.end()){
        iter j=std::find_if(i,str.end(),predicate);
        if( i == j ) vs.push_back("");
        else{
            if( trimoption ){
                vs.push_back( fnStringTrim(std::string(i,j)));
            }
            else{
                vs.push_back(std::string(i,j));
            }
        }

        if(j != str.end()) i = ++j;
        else i = j;
    }
    return vs;
}

Vec_STR fnStringSpliter( const std::string &str, bool (*predicate)(char c),  bool (*not_predicate)(char c), bool trimoption )
{
    typedef string::const_iterator iter;
    Vec_STR vs;
    iter i=str.begin();

    while(i!=str.end())
    {
        i=std::find_if(i,str.end(),not_predicate);
        iter j=std::find_if(i,str.end(),predicate);
        if(i!=str.end()){
            if( trimoption ){
                vs.push_back( fnStringTrim(std::string(i,j)));
            }
            else{
                vs.push_back(std::string(i,j));
            }
        }
        i=j;
    }
    return vs;
}

template < typename Container = std::vector<std::string> >
void fnStringSpliter( Container& container, std::string const & strSource, const char* const chDelimiters = " \t\n,|")
{
    const std::string::size_type len = strSource.length();
    std::string::size_type i = 0;

    while (i < len)
    {
        // Eat leading whitespace
        i = strSource.find_first_not_of(chDelimiters, i);
        if (i == std::string::npos)
            return;   // Nothing left but white space

        // Find the end of the token
        std::string::size_type j = strSource.find_first_of(chDelimiters, i);

        // Push token
        if (j == std::string::npos) {
            container.push_back(strSource.substr(i));
            return;
        }
        else {
            container.push_back(strSource.substr(i, j-i));
        }
        // Set up for next loop
        i = j + 1;
    }
}
