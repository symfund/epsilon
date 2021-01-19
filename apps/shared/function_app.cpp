#include "function_app.h"

using namespace Poincare;

namespace Shared {

FunctionApp::Snapshot::Snapshot() :
  m_cursor(),
  m_indexFunctionSelectedByCursor(0),
  m_rangeVersion(0)
{
}

void FunctionApp::Snapshot::reset() {
  m_indexFunctionSelectedByCursor = 0;
  m_rangeVersion = 0;
  setActiveTab(0);
}

void FunctionApp::Snapshot::storageDidChangeForRecord(const Ion::Storage::Record record) {
  functionStore()->storageDidChangeForRecord(record);
}

void FunctionApp::willBecomeInactive() {
  if (m_modalViewController.isDisplayingModal()) {
    m_modalViewController.dismissModalViewController(true);
  }
  if (inputViewController()->isDisplayingModal()) {
    inputViewController()->abortEditionAndDismiss();
  }
  ::App::willBecomeInactive();
}


bool FunctionApp::isAcceptableExpression(const Expression exp) {
 return TextFieldDelegateApp::isAcceptableExpression(exp) && ExpressionCanBeSerialized(exp, false, Expression(), localContext());
}

}
