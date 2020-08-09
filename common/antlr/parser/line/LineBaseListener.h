
// Generated from Line.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "LineListener.h"


/**
 * This class provides an empty implementation of LineListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  LineBaseListener : public LineListener {
public:

  virtual void enterLine(LineParser::LineContext * /*ctx*/) override { }
  virtual void exitLine(LineParser::LineContext * /*ctx*/) override { }

  virtual void enterContent(LineParser::ContentContext * /*ctx*/) override { }
  virtual void exitContent(LineParser::ContentContext * /*ctx*/) override { }

  virtual void enterVariable(LineParser::VariableContext * /*ctx*/) override { }
  virtual void exitVariable(LineParser::VariableContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

