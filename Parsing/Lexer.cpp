#include "Lexer.hpp"

enum eState {
	state_operator,
	state_operand,
	state_comment,
}

union uTokenData {
	IOperand * operand_obj,
	eOperator operator_id,
}

struct Token {
public:
	bool is_operator;
	IOperand * operand;
	eOperator operator_id,
}

class Lexer {
	std::vector<
public:
	Lexer();
	~Lexer();
	void feed_line( std::string & line );
	std::vector<Token> get_tokens();
};