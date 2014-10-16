
#pragma once

#include <llvm/IR/IRBuilder.h>


namespace dev
{
namespace eth
{
namespace jit
{

/// Base class for compiler helpers like Memory, GasMeter, etc.
class CompilerHelper
{
protected:
	CompilerHelper(llvm::IRBuilder<>& _builder);

	CompilerHelper(const CompilerHelper&) = delete;
	void operator=(CompilerHelper) = delete;

	/// Reference to the IR module being compiled
	llvm::Module* getModule();

	/// Reference to parent compiler IR builder
	llvm::IRBuilder<>& m_builder;
};


/// Saves the insert point of the IR builder and restores it when destructed
struct InsertPointGuard
{
	InsertPointGuard(llvm::IRBuilder<>& _builder) :
		m_builder(_builder),
		m_insertBB(m_builder.GetInsertBlock()),
		m_insertPt(m_builder.GetInsertPoint())
	{}

	InsertPointGuard(const InsertPointGuard&) = delete;
	void operator=(InsertPointGuard) = delete;

	~InsertPointGuard()
	{
		m_builder.SetInsertPoint(m_insertBB, m_insertPt);
	}

private:
	llvm::IRBuilder<>& m_builder;
	llvm::BasicBlock* m_insertBB;
	llvm::BasicBlock::iterator m_insertPt;
};

}
}
}
