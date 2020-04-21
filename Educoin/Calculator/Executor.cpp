#include "Executor.hpp"

void Executor::doOperation(std::list<Token>::iterator &op) {
  std::list<Token>::iterator firstElem;
  std::list<Token>::iterator secondElem;

  firstElem = op, --firstElem;
  secondElem = op, ++secondElem;

  if (op->getToken() == PLUS)
    firstElem->getNValue() += secondElem->getNValue();
  else if (op->getToken() == MIN)
    firstElem->getNValue() -= secondElem->getNValue();
  else if (op->getToken() == DIV)
    firstElem->getNValue() /= secondElem->getNValue();
  else if (op->getToken() == MULT)
    firstElem->getNValue() *= secondElem->getNValue();
  else if (op->getToken() == MOD)
    firstElem->getNValue() %= secondElem->getNValue();

  list.erase(op, ++secondElem);
  op = firstElem;
}

void Executor::computeByPriority(std::list<Token>::iterator begin,
                                 std::list<Token>::iterator end) {
  std::list<Token>::iterator iter = begin;

  // Compute all first priority operations
  while (iter != end) {
    eToken t = iter->getToken();
    if (t == DIV || t == MULT || t == MOD) doOperation(iter);
    ++iter;
  }

  // Compute all second priority operations
  iter = begin;
  while (iter != end) {
    eToken t = iter->getToken();
    if (t == PLUS || t == MIN) doOperation(iter);
    ++iter;
  }

  iter = begin, ++iter;
  std::swap(*begin, *iter);
  list.erase(iter, end);
}

typedef std::tuple<bool, std::list<Token>::iterator, std::list<Token>::iterator>
    parenthese_t;
parenthese_t find_parenthese(std::list<Token>::iterator begin,
                             std::list<Token>::iterator end) {
  auto openSIter = begin;
  auto closeSIter = begin;

  while (++openSIter != end) {
    if (openSIter->getToken() == OpenScope) break;
  }

  if (openSIter != end) {
    auto closeSIter = openSIter;
    unsigned int openCounter = 1;

    ++closeSIter;
    while (openCounter != 0) {
      if (closeSIter->getToken() == OpenScope)
        ++openCounter;
      else if (closeSIter->getToken() == CloseScope)
        --openCounter;

      ++closeSIter;
    }

    return std::make_tuple(true, openSIter, closeSIter);
  }
  return std::make_tuple(false, openSIter, closeSIter);
}

void Executor::recursiveExecute(std::list<Token>::iterator begin,
                                std::list<Token>::iterator end) {
  bool is_found = false;  // about parentheses
  std::list<Token>::iterator new_begin;
  std::list<Token>::iterator new_end;

  do {
    std::tie(is_found, new_begin, new_end) = find_parenthese(begin, end);

    if (is_found) recursiveExecute(new_begin, new_end);

  } while (is_found);

  computeByPriority(begin, end);
}

void Executor::saveValueInBuf(int_fast64_t val) {
  cicle_buf[positionForSave] = val;
  positionForSave++;
  if (positionForSave >= 10) positionForSave = 0;
}

void Executor::changeVarsToNums() {
  for (Token &t : list) {
    if (t.getToken() == VAR) {
      uint8_t index = t.getNValue();
      Token tmp(NUM, std::to_string(cicle_buf[index]));
      std::swap(t, tmp);
    }
  }
}

int_fast64_t Executor::executeExpression(std::string const &expr) {
  int_fast64_t result;

  list.clear();
  lexer.doLexAnalization(&list, expr);
  parser.doParsingAnalization(&list);
  changeVarsToNums();

  recursiveExecute(list.begin(), list.end());

  result = list.front().getNValue();
  saveValueInBuf(result);

  return result;
}