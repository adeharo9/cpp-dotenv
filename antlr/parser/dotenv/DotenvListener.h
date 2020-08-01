
// Generated from Dotenv.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "DotenvParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by DotenvParser.
 */
class  DotenvListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterDotenv(DotenvParser::DotenvContext *ctx) = 0;
  virtual void exitDotenv(DotenvParser::DotenvContext *ctx) = 0;

  virtual void enterLineContent(DotenvParser::LineContentContext *ctx) = 0;
  virtual void exitLineContent(DotenvParser::LineContentContext *ctx) = 0;

  virtual void enterEmptyLine(DotenvParser::EmptyLineContext *ctx) = 0;
  virtual void exitEmptyLine(DotenvParser::EmptyLineContext *ctx) = 0;

  virtual void enterPair(DotenvParser::PairContext *ctx) = 0;
  virtual void exitPair(DotenvParser::PairContext *ctx) = 0;

  virtual void enterKey(DotenvParser::KeyContext *ctx) = 0;
  virtual void exitKey(DotenvParser::KeyContext *ctx) = 0;

  virtual void enterValue(DotenvParser::ValueContext *ctx) = 0;
  virtual void exitValue(DotenvParser::ValueContext *ctx) = 0;


};

