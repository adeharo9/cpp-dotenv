
// Generated from Line.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "LineParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by LineParser.
 */
class  LineListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterLine(LineParser::LineContext *ctx) = 0;
  virtual void exitLine(LineParser::LineContext *ctx) = 0;

  virtual void enterContent(LineParser::ContentContext *ctx) = 0;
  virtual void exitContent(LineParser::ContentContext *ctx) = 0;

  virtual void enterVariable(LineParser::VariableContext *ctx) = 0;
  virtual void exitVariable(LineParser::VariableContext *ctx) = 0;


};

