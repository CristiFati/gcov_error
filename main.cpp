#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/TargetSelect.h>

void runTest() {
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  llvm::InitializeNativeTargetAsmParser();
  
  [[maybe_unused]] llvm::LLVMContext context;
}

int main() {
  runTest();
  return 0;
}
