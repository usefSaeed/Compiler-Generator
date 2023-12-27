//
// Created by usef on 12/27/2023.
//

#include "gtest/gtest.h"
#include "../SyntaxPhase/FirstAndFollowGenerator/FirstSetsGenerator.h"
#include "../SyntaxPhase/GrammarParser/Grammar.h"

TEST(FirstSetGeneration,TerminalScenario){
    /// A --> a B | b
    /// B --> b a B | a A | \L
    std::shared_ptr<NonTerminal> A = std::make_shared<NonTerminal>("A");
    std::shared_ptr<NonTerminal> B = std::make_shared<NonTerminal>("B");
    std::shared_ptr<Terminal> a = std::make_shared<Terminal>("a");
    std::shared_ptr<Terminal> b = std::make_shared<Terminal>("b");
    std::shared_ptr<Terminal> eps = std::make_shared<Terminal>("\\L");
    Grammar::epsilon = eps.get();

    std::vector<std::vector<std::shared_ptr<Symbol>>> vv_s;
    std::vector<std::shared_ptr<Symbol>> v_s;
    v_s.push_back(a); v_s.push_back(B); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(b); vv_s.push_back(v_s);
    A->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(b); v_s.push_back(a); v_s.push_back(B); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(a); v_s.push_back(A); vv_s.push_back(v_s);
    B->setProductions(vv_s);

    v_s.clear(); vv_s.clear();

    std::vector<std::shared_ptr<NonTerminal>> nts = {A,B};

    FirstSetsGenerator firstSG(nts);

    FirstSet fs_expected;
    fs_expected.add(a.get()); fs_expected.add(b.get());

    for (int i=0; i<2; i++){
        ASSERT_EQ(nts[i]->getFirstSet().get()->getSet(), fs_expected.getSet());
    }

}


