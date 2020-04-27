#include "FunctionStorage.h"

FunctionStorage &FunctionStorage::GetInstance() {
    static FunctionStorage storage;
    return storage;
}

void FunctionStorage::Set(func_symbol symbol, std::shared_ptr<FunctionObject> function) {
    functions_[symbol] = function;
}


std::shared_ptr<FunctionObject> FunctionStorage::Get(func_symbol symbol) const {
    if (functions_.find(symbol) != functions_.end()) {
        return functions_.at(symbol);
    } else {
        throw std::runtime_error("Function not found");
    }
}
