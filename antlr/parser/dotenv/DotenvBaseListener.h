
// Generated from Dotenv.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "DotenvListener.h"


/**
 * This class provides an empty implementation of DotenvListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  DotenvBaseListener : public DotenvListener {
public:

  virtual void enterDotenv(DotenvParser::DotenvContext * /*ctx*/) override { }
  virtual void exitDotenv(DotenvParser::DotenvContext * /*ctx*/) override { }

  virtual void enterLineContent(DotenvParser::LineContentContext * /*ctx*/) override { }
  virtual void exitLineContent(DotenvParser::LineContentContext * /*ctx*/) override { }

  virtual void enterEmptyLine(DotenvParser::EmptyLineContext * /*ctx*/) override { }
  virtual void exitEmptyLine(DotenvParser::EmptyLineContext * /*ctx*/) override { }

  virtual void enterPair(DotenvParser::PairContext * /*ctx*/) override { }
  virtual void exitPair(DotenvParser::PairContext * /*ctx*/) override { }

  virtual void enterKey(DotenvParser::KeyContext * /*ctx*/) override { }
  virtual void exitKey(DotenvParser::KeyContext * /*ctx*/) override { }

  virtual void enterValue(DotenvParser::ValueContext * /*ctx*/) override { }
  virtual void exitValue(DotenvParser::ValueContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

