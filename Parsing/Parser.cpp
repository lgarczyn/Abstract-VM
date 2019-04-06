
class Parser {
public:
	Parser();
	~Parser();
	void feed_line( std::string & line );
	std::vector<Token> get_tokens();
};