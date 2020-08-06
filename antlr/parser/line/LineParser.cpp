
// Generated from Line.g4 by ANTLR 4.8


#include "LineListener.h"

#include "LineParser.h"


using namespace antlrcpp;
using namespace antlr4;

LineParser::LineParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

LineParser::~LineParser() {
  delete _interpreter;
}

std::string LineParser::getGrammarFileName() const {
  return "Line.g4";
}

const std::vector<std::string>& LineParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& LineParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- LineContext ------------------------------------------------------------------

LineParser::LineContext::LineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LineParser::LineContext::EOF() {
  return getToken(LineParser::EOF, 0);
}

LineParser::ContentContext* LineParser::LineContext::content() {
  return getRuleContext<LineParser::ContentContext>(0);
}


size_t LineParser::LineContext::getRuleIndex() const {
  return LineParser::RuleLine;
}

void LineParser::LineContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LineListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLine(this);
}

void LineParser::LineContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LineListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLine(this);
}

LineParser::LineContext* LineParser::line() {
  LineContext *_localctx = _tracker.createInstance<LineContext>(_ctx, getState());
  enterRule(_localctx, 0, LineParser::RuleLine);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(7);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << LineParser::ESC_SEQ)
      | (1ULL << LineParser::BOUNDED_VARIABLE)
      | (1ULL << LineParser::UNBOUNDED_VARIABLE)
      | (1ULL << LineParser::STRING_CHAR))) != 0)) {
      setState(6);
      content();
    }
    setState(9);
    match(LineParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ContentContext ------------------------------------------------------------------

LineParser::ContentContext::ContentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> LineParser::ContentContext::STRING_CHAR() {
  return getTokens(LineParser::STRING_CHAR);
}

tree::TerminalNode* LineParser::ContentContext::STRING_CHAR(size_t i) {
  return getToken(LineParser::STRING_CHAR, i);
}

std::vector<tree::TerminalNode *> LineParser::ContentContext::ESC_SEQ() {
  return getTokens(LineParser::ESC_SEQ);
}

tree::TerminalNode* LineParser::ContentContext::ESC_SEQ(size_t i) {
  return getToken(LineParser::ESC_SEQ, i);
}

std::vector<LineParser::VariableContext *> LineParser::ContentContext::variable() {
  return getRuleContexts<LineParser::VariableContext>();
}

LineParser::VariableContext* LineParser::ContentContext::variable(size_t i) {
  return getRuleContext<LineParser::VariableContext>(i);
}


size_t LineParser::ContentContext::getRuleIndex() const {
  return LineParser::RuleContent;
}

void LineParser::ContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LineListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterContent(this);
}

void LineParser::ContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LineListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitContent(this);
}

LineParser::ContentContext* LineParser::content() {
  ContentContext *_localctx = _tracker.createInstance<ContentContext>(_ctx, getState());
  enterRule(_localctx, 2, LineParser::RuleContent);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(14); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(14);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case LineParser::STRING_CHAR: {
          setState(11);
          match(LineParser::STRING_CHAR);
          break;
        }

        case LineParser::ESC_SEQ: {
          setState(12);
          match(LineParser::ESC_SEQ);
          break;
        }

        case LineParser::BOUNDED_VARIABLE:
        case LineParser::UNBOUNDED_VARIABLE: {
          setState(13);
          variable();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(16); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << LineParser::ESC_SEQ)
      | (1ULL << LineParser::BOUNDED_VARIABLE)
      | (1ULL << LineParser::UNBOUNDED_VARIABLE)
      | (1ULL << LineParser::STRING_CHAR))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableContext ------------------------------------------------------------------

LineParser::VariableContext::VariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* LineParser::VariableContext::BOUNDED_VARIABLE() {
  return getToken(LineParser::BOUNDED_VARIABLE, 0);
}

tree::TerminalNode* LineParser::VariableContext::UNBOUNDED_VARIABLE() {
  return getToken(LineParser::UNBOUNDED_VARIABLE, 0);
}


size_t LineParser::VariableContext::getRuleIndex() const {
  return LineParser::RuleVariable;
}

void LineParser::VariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LineListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariable(this);
}

void LineParser::VariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<LineListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariable(this);
}

LineParser::VariableContext* LineParser::variable() {
  VariableContext *_localctx = _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 4, LineParser::RuleVariable);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(18);
    _la = _input->LA(1);
    if (!(_la == LineParser::BOUNDED_VARIABLE

    || _la == LineParser::UNBOUNDED_VARIABLE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> LineParser::_decisionToDFA;
atn::PredictionContextCache LineParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN LineParser::_atn;
std::vector<uint16_t> LineParser::_serializedATN;

std::vector<std::string> LineParser::_ruleNames = {
  "line", "content", "variable"
};

std::vector<std::string> LineParser::_literalNames = {
};

std::vector<std::string> LineParser::_symbolicNames = {
  "", "ESC_SEQ", "BOUNDED_VARIABLE", "UNBOUNDED_VARIABLE", "STRING_CHAR"
};

dfa::Vocabulary LineParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> LineParser::_tokenNames;

LineParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x6, 0x17, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x3, 0x2, 0x5, 0x2, 0xa, 0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x6, 0x3, 0x11, 0xa, 0x3, 0xd, 0x3, 0xe, 0x3, 0x12, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x2, 0x2, 0x5, 0x2, 0x4, 0x6, 0x2, 0x3, 
    0x3, 0x2, 0x4, 0x5, 0x2, 0x17, 0x2, 0x9, 0x3, 0x2, 0x2, 0x2, 0x4, 0x10, 
    0x3, 0x2, 0x2, 0x2, 0x6, 0x14, 0x3, 0x2, 0x2, 0x2, 0x8, 0xa, 0x5, 0x4, 
    0x3, 0x2, 0x9, 0x8, 0x3, 0x2, 0x2, 0x2, 0x9, 0xa, 0x3, 0x2, 0x2, 0x2, 
    0xa, 0xb, 0x3, 0x2, 0x2, 0x2, 0xb, 0xc, 0x7, 0x2, 0x2, 0x3, 0xc, 0x3, 
    0x3, 0x2, 0x2, 0x2, 0xd, 0x11, 0x7, 0x6, 0x2, 0x2, 0xe, 0x11, 0x7, 0x3, 
    0x2, 0x2, 0xf, 0x11, 0x5, 0x6, 0x4, 0x2, 0x10, 0xd, 0x3, 0x2, 0x2, 0x2, 
    0x10, 0xe, 0x3, 0x2, 0x2, 0x2, 0x10, 0xf, 0x3, 0x2, 0x2, 0x2, 0x11, 
    0x12, 0x3, 0x2, 0x2, 0x2, 0x12, 0x10, 0x3, 0x2, 0x2, 0x2, 0x12, 0x13, 
    0x3, 0x2, 0x2, 0x2, 0x13, 0x5, 0x3, 0x2, 0x2, 0x2, 0x14, 0x15, 0x9, 
    0x2, 0x2, 0x2, 0x15, 0x7, 0x3, 0x2, 0x2, 0x2, 0x5, 0x9, 0x10, 0x12, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

LineParser::Initializer LineParser::_init;
