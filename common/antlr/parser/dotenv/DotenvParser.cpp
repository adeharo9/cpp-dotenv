
// Generated from Dotenv.g4 by ANTLR 4.8


#include "DotenvListener.h"

#include "DotenvParser.h"


using namespace antlrcpp;
using namespace antlr4;

DotenvParser::DotenvParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

DotenvParser::~DotenvParser() {
  delete _interpreter;
}

std::string DotenvParser::getGrammarFileName() const {
  return "Dotenv.g4";
}

const std::vector<std::string>& DotenvParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& DotenvParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- DotenvContext ------------------------------------------------------------------

DotenvParser::DotenvContext::DotenvContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<DotenvParser::LineContext *> DotenvParser::DotenvContext::line() {
  return getRuleContexts<DotenvParser::LineContext>();
}

DotenvParser::LineContext* DotenvParser::DotenvContext::line(size_t i) {
  return getRuleContext<DotenvParser::LineContext>(i);
}

tree::TerminalNode* DotenvParser::DotenvContext::EOF() {
  return getToken(DotenvParser::EOF, 0);
}

std::vector<tree::TerminalNode *> DotenvParser::DotenvContext::NL() {
  return getTokens(DotenvParser::NL);
}

tree::TerminalNode* DotenvParser::DotenvContext::NL(size_t i) {
  return getToken(DotenvParser::NL, i);
}


size_t DotenvParser::DotenvContext::getRuleIndex() const {
  return DotenvParser::RuleDotenv;
}

void DotenvParser::DotenvContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DotenvListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDotenv(this);
}

void DotenvParser::DotenvContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DotenvListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDotenv(this);
}

DotenvParser::DotenvContext* DotenvParser::dotenv() {
  DotenvContext *_localctx = _tracker.createInstance<DotenvContext>(_ctx, getState());
  enterRule(_localctx, 0, DotenvParser::RuleDotenv);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(10);
    line();
    setState(15);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == DotenvParser::NL) {
      setState(11);
      match(DotenvParser::NL);
      setState(12);
      line();
      setState(17);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(18);
    match(DotenvParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LineContext ------------------------------------------------------------------

DotenvParser::LineContext::LineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t DotenvParser::LineContext::getRuleIndex() const {
  return DotenvParser::RuleLine;
}

void DotenvParser::LineContext::copyFrom(LineContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- EmptyLineContext ------------------------------------------------------------------

tree::TerminalNode* DotenvParser::EmptyLineContext::WS() {
  return getToken(DotenvParser::WS, 0);
}

DotenvParser::EmptyLineContext::EmptyLineContext(LineContext *ctx) { copyFrom(ctx); }

void DotenvParser::EmptyLineContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DotenvListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEmptyLine(this);
}
void DotenvParser::EmptyLineContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DotenvListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEmptyLine(this);
}
//----------------- LineContentContext ------------------------------------------------------------------

DotenvParser::PairContext* DotenvParser::LineContentContext::pair() {
  return getRuleContext<DotenvParser::PairContext>(0);
}

std::vector<tree::TerminalNode *> DotenvParser::LineContentContext::WS() {
  return getTokens(DotenvParser::WS);
}

tree::TerminalNode* DotenvParser::LineContentContext::WS(size_t i) {
  return getToken(DotenvParser::WS, i);
}

DotenvParser::LineContentContext::LineContentContext(LineContext *ctx) { copyFrom(ctx); }

void DotenvParser::LineContentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DotenvListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLineContent(this);
}
void DotenvParser::LineContentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DotenvListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLineContent(this);
}
DotenvParser::LineContext* DotenvParser::line() {
  LineContext *_localctx = _tracker.createInstance<LineContext>(_ctx, getState());
  enterRule(_localctx, 2, DotenvParser::RuleLine);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(30);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<LineContext *>(_tracker.createInstance<DotenvParser::LineContentContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(21);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == DotenvParser::WS) {
        setState(20);
        match(DotenvParser::WS);
      }
      setState(23);
      pair();
      setState(25);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == DotenvParser::WS) {
        setState(24);
        match(DotenvParser::WS);
      }
      break;
    }

    case 2: {
      _localctx = dynamic_cast<LineContext *>(_tracker.createInstance<DotenvParser::EmptyLineContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(28);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == DotenvParser::WS) {
        setState(27);
        match(DotenvParser::WS);
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PairContext ------------------------------------------------------------------

DotenvParser::PairContext::PairContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

DotenvParser::KeyContext* DotenvParser::PairContext::key() {
  return getRuleContext<DotenvParser::KeyContext>(0);
}

tree::TerminalNode* DotenvParser::PairContext::EQ() {
  return getToken(DotenvParser::EQ, 0);
}

DotenvParser::ValueContext* DotenvParser::PairContext::value() {
  return getRuleContext<DotenvParser::ValueContext>(0);
}

std::vector<tree::TerminalNode *> DotenvParser::PairContext::WS() {
  return getTokens(DotenvParser::WS);
}

tree::TerminalNode* DotenvParser::PairContext::WS(size_t i) {
  return getToken(DotenvParser::WS, i);
}


size_t DotenvParser::PairContext::getRuleIndex() const {
  return DotenvParser::RulePair;
}

void DotenvParser::PairContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DotenvListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPair(this);
}

void DotenvParser::PairContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DotenvListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPair(this);
}

DotenvParser::PairContext* DotenvParser::pair() {
  PairContext *_localctx = _tracker.createInstance<PairContext>(_ctx, getState());
  enterRule(_localctx, 4, DotenvParser::RulePair);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(32);
    key();
    setState(34);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == DotenvParser::WS) {
      setState(33);
      match(DotenvParser::WS);
    }
    setState(36);
    match(DotenvParser::EQ);
    setState(38);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
    case 1: {
      setState(37);
      match(DotenvParser::WS);
      break;
    }

    }
    setState(40);
    value();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KeyContext ------------------------------------------------------------------

DotenvParser::KeyContext::KeyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> DotenvParser::KeyContext::UNQUOTED_STRING() {
  return getTokens(DotenvParser::UNQUOTED_STRING);
}

tree::TerminalNode* DotenvParser::KeyContext::UNQUOTED_STRING(size_t i) {
  return getToken(DotenvParser::UNQUOTED_STRING, i);
}

tree::TerminalNode* DotenvParser::KeyContext::WS() {
  return getToken(DotenvParser::WS, 0);
}

tree::TerminalNode* DotenvParser::KeyContext::STRING() {
  return getToken(DotenvParser::STRING, 0);
}


size_t DotenvParser::KeyContext::getRuleIndex() const {
  return DotenvParser::RuleKey;
}

void DotenvParser::KeyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DotenvListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKey(this);
}

void DotenvParser::KeyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DotenvListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKey(this);
}

DotenvParser::KeyContext* DotenvParser::key() {
  KeyContext *_localctx = _tracker.createInstance<KeyContext>(_ctx, getState());
  enterRule(_localctx, 6, DotenvParser::RuleKey);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(52);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(44);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
      case 1: {
        setState(42);
        dynamic_cast<KeyContext *>(_localctx)->export_token = match(DotenvParser::UNQUOTED_STRING);
        setState(43);
        match(DotenvParser::WS);
        break;
      }

      }
      setState(46);
      dynamic_cast<KeyContext *>(_localctx)->key_unquoted = match(DotenvParser::UNQUOTED_STRING);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(49);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == DotenvParser::UNQUOTED_STRING) {
        setState(47);
        dynamic_cast<KeyContext *>(_localctx)->export_token = match(DotenvParser::UNQUOTED_STRING);
        setState(48);
        match(DotenvParser::WS);
      }
      setState(51);
      dynamic_cast<KeyContext *>(_localctx)->key_string = match(DotenvParser::STRING);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueContext ------------------------------------------------------------------

DotenvParser::ValueContext::ValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> DotenvParser::ValueContext::UNQUOTED_STRING() {
  return getTokens(DotenvParser::UNQUOTED_STRING);
}

tree::TerminalNode* DotenvParser::ValueContext::UNQUOTED_STRING(size_t i) {
  return getToken(DotenvParser::UNQUOTED_STRING, i);
}

std::vector<tree::TerminalNode *> DotenvParser::ValueContext::WS() {
  return getTokens(DotenvParser::WS);
}

tree::TerminalNode* DotenvParser::ValueContext::WS(size_t i) {
  return getToken(DotenvParser::WS, i);
}

tree::TerminalNode* DotenvParser::ValueContext::STRING() {
  return getToken(DotenvParser::STRING, 0);
}


size_t DotenvParser::ValueContext::getRuleIndex() const {
  return DotenvParser::RuleValue;
}

void DotenvParser::ValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DotenvListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterValue(this);
}

void DotenvParser::ValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<DotenvListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitValue(this);
}

DotenvParser::ValueContext* DotenvParser::value() {
  ValueContext *_localctx = _tracker.createInstance<ValueContext>(_ctx, getState());
  enterRule(_localctx, 8, DotenvParser::RuleValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    setState(64);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case DotenvParser::UNQUOTED_STRING: {
        enterOuterAlt(_localctx, 1);
        setState(54);
        match(DotenvParser::UNQUOTED_STRING);
        setState(59);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(55);
            match(DotenvParser::WS);
            setState(56);
            match(DotenvParser::UNQUOTED_STRING); 
          }
          setState(61);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx);
        }
        break;
      }

      case DotenvParser::STRING: {
        enterOuterAlt(_localctx, 2);
        setState(62);
        match(DotenvParser::STRING);
        break;
      }

      case DotenvParser::EOF:
      case DotenvParser::NL:
      case DotenvParser::WS: {
        enterOuterAlt(_localctx, 3);

        break;
      }

    default:
      throw NoViableAltException(this);
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
std::vector<dfa::DFA> DotenvParser::_decisionToDFA;
atn::PredictionContextCache DotenvParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN DotenvParser::_atn;
std::vector<uint16_t> DotenvParser::_serializedATN;

std::vector<std::string> DotenvParser::_ruleNames = {
  "dotenv", "line", "pair", "key", "value"
};

std::vector<std::string> DotenvParser::_literalNames = {
  "", "'='"
};

std::vector<std::string> DotenvParser::_symbolicNames = {
  "", "EQ", "NL", "WS", "COMMENT", "STRING", "UNQUOTED_STRING"
};

dfa::Vocabulary DotenvParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> DotenvParser::_tokenNames;

DotenvParser::Initializer::Initializer() {
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
    0x3, 0x8, 0x45, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x2, 0x7, 0x2, 0x10, 0xa, 0x2, 0xc, 0x2, 0xe, 0x2, 0x13, 0xb, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x3, 0x5, 0x3, 0x18, 0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x5, 0x3, 0x1c, 0xa, 0x3, 0x3, 0x3, 0x5, 0x3, 0x1f, 0xa, 0x3, 0x5, 0x3, 
    0x21, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x25, 0xa, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x5, 0x4, 0x29, 0xa, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x5, 0x3, 
    0x5, 0x5, 0x5, 0x2f, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 
    0x34, 0xa, 0x5, 0x3, 0x5, 0x5, 0x5, 0x37, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x7, 0x6, 0x3c, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x3f, 0xb, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x43, 0xa, 0x6, 0x3, 0x6, 0x2, 0x2, 0x7, 
    0x2, 0x4, 0x6, 0x8, 0xa, 0x2, 0x2, 0x2, 0x4c, 0x2, 0xc, 0x3, 0x2, 0x2, 
    0x2, 0x4, 0x20, 0x3, 0x2, 0x2, 0x2, 0x6, 0x22, 0x3, 0x2, 0x2, 0x2, 0x8, 
    0x36, 0x3, 0x2, 0x2, 0x2, 0xa, 0x42, 0x3, 0x2, 0x2, 0x2, 0xc, 0x11, 
    0x5, 0x4, 0x3, 0x2, 0xd, 0xe, 0x7, 0x4, 0x2, 0x2, 0xe, 0x10, 0x5, 0x4, 
    0x3, 0x2, 0xf, 0xd, 0x3, 0x2, 0x2, 0x2, 0x10, 0x13, 0x3, 0x2, 0x2, 0x2, 
    0x11, 0xf, 0x3, 0x2, 0x2, 0x2, 0x11, 0x12, 0x3, 0x2, 0x2, 0x2, 0x12, 
    0x14, 0x3, 0x2, 0x2, 0x2, 0x13, 0x11, 0x3, 0x2, 0x2, 0x2, 0x14, 0x15, 
    0x7, 0x2, 0x2, 0x3, 0x15, 0x3, 0x3, 0x2, 0x2, 0x2, 0x16, 0x18, 0x7, 
    0x5, 0x2, 0x2, 0x17, 0x16, 0x3, 0x2, 0x2, 0x2, 0x17, 0x18, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0x19, 0x3, 0x2, 0x2, 0x2, 0x19, 0x1b, 0x5, 0x6, 0x4, 
    0x2, 0x1a, 0x1c, 0x7, 0x5, 0x2, 0x2, 0x1b, 0x1a, 0x3, 0x2, 0x2, 0x2, 
    0x1b, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x21, 0x3, 0x2, 0x2, 0x2, 0x1d, 
    0x1f, 0x7, 0x5, 0x2, 0x2, 0x1e, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1f, 
    0x3, 0x2, 0x2, 0x2, 0x1f, 0x21, 0x3, 0x2, 0x2, 0x2, 0x20, 0x17, 0x3, 
    0x2, 0x2, 0x2, 0x20, 0x1e, 0x3, 0x2, 0x2, 0x2, 0x21, 0x5, 0x3, 0x2, 
    0x2, 0x2, 0x22, 0x24, 0x5, 0x8, 0x5, 0x2, 0x23, 0x25, 0x7, 0x5, 0x2, 
    0x2, 0x24, 0x23, 0x3, 0x2, 0x2, 0x2, 0x24, 0x25, 0x3, 0x2, 0x2, 0x2, 
    0x25, 0x26, 0x3, 0x2, 0x2, 0x2, 0x26, 0x28, 0x7, 0x3, 0x2, 0x2, 0x27, 
    0x29, 0x7, 0x5, 0x2, 0x2, 0x28, 0x27, 0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 
    0x3, 0x2, 0x2, 0x2, 0x29, 0x2a, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x2b, 0x5, 
    0xa, 0x6, 0x2, 0x2b, 0x7, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2d, 0x7, 0x8, 
    0x2, 0x2, 0x2d, 0x2f, 0x7, 0x5, 0x2, 0x2, 0x2e, 0x2c, 0x3, 0x2, 0x2, 
    0x2, 0x2e, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x2f, 0x30, 0x3, 0x2, 0x2, 0x2, 
    0x30, 0x37, 0x7, 0x8, 0x2, 0x2, 0x31, 0x32, 0x7, 0x8, 0x2, 0x2, 0x32, 
    0x34, 0x7, 0x5, 0x2, 0x2, 0x33, 0x31, 0x3, 0x2, 0x2, 0x2, 0x33, 0x34, 
    0x3, 0x2, 0x2, 0x2, 0x34, 0x35, 0x3, 0x2, 0x2, 0x2, 0x35, 0x37, 0x7, 
    0x7, 0x2, 0x2, 0x36, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x36, 0x33, 0x3, 0x2, 
    0x2, 0x2, 0x37, 0x9, 0x3, 0x2, 0x2, 0x2, 0x38, 0x3d, 0x7, 0x8, 0x2, 
    0x2, 0x39, 0x3a, 0x7, 0x5, 0x2, 0x2, 0x3a, 0x3c, 0x7, 0x8, 0x2, 0x2, 
    0x3b, 0x39, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x3d, 
    0x3b, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x43, 
    0x3, 0x2, 0x2, 0x2, 0x3f, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x40, 0x43, 0x7, 
    0x7, 0x2, 0x2, 0x41, 0x43, 0x3, 0x2, 0x2, 0x2, 0x42, 0x38, 0x3, 0x2, 
    0x2, 0x2, 0x42, 0x40, 0x3, 0x2, 0x2, 0x2, 0x42, 0x41, 0x3, 0x2, 0x2, 
    0x2, 0x43, 0xb, 0x3, 0x2, 0x2, 0x2, 0xe, 0x11, 0x17, 0x1b, 0x1e, 0x20, 
    0x24, 0x28, 0x2e, 0x33, 0x36, 0x3d, 0x42, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

DotenvParser::Initializer DotenvParser::_init;
