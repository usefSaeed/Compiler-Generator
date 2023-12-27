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

TEST(FirstSetGeneration,NonTerminalScenario){
    /// A --> B a | C b
    /// B --> C a | \\L
    /// C --> c
    std::shared_ptr<NonTerminal> A = std::make_shared<NonTerminal>("A");
    std::shared_ptr<NonTerminal> B = std::make_shared<NonTerminal>("B");
    std::shared_ptr<NonTerminal> C = std::make_shared<NonTerminal>("C");
    std::shared_ptr<Terminal> a = std::make_shared<Terminal>("a");
    std::shared_ptr<Terminal> b = std::make_shared<Terminal>("b");
    std::shared_ptr<Terminal> c = std::make_shared<Terminal>("c");
    std::shared_ptr<Terminal> eps = std::make_shared<Terminal>("\\L");
    Grammar::epsilon = eps.get();

    std::vector<std::vector<std::shared_ptr<Symbol>>> vv_s;
    std::vector<std::shared_ptr<Symbol>> v_s;
    v_s.push_back(B); v_s.push_back(a); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(C); v_s.push_back(b); vv_s.push_back(v_s);
    A->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(C); v_s.push_back(a); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(eps); vv_s.push_back(v_s);
    B->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(c); vv_s.push_back(v_s);
    C->setProductions(vv_s);

    v_s.clear(); vv_s.clear();

    std::vector<std::shared_ptr<NonTerminal>> nts = {A,B,C};

    FirstSetsGenerator firstSG(nts);

    FirstSet fs_expected;
    fs_expected.add(c.get());
    ASSERT_EQ(nts[2]->getFirstSet().get()->getSet(), fs_expected.getSet());
    fs_expected.add(eps.get());
    ASSERT_EQ(nts[1]->getFirstSet().get()->getSet(), fs_expected.getSet());
    fs_expected.removeEpsilon();
    fs_expected.add(a.get());
    ASSERT_EQ(nts[0]->getFirstSet().get()->getSet(), fs_expected.getSet());
}


TEST(FirstSetGeneration,LateFirstCase){
    /// A --> B C D | C B a
    /// B --> C a | \\L
    /// C --> c | \\L
    /// D --> d | b
    std::shared_ptr<NonTerminal> A = std::make_shared<NonTerminal>("A");
    std::shared_ptr<NonTerminal> B = std::make_shared<NonTerminal>("B");
    std::shared_ptr<NonTerminal> C = std::make_shared<NonTerminal>("C");
    std::shared_ptr<NonTerminal> D = std::make_shared<NonTerminal>("D");
    std::shared_ptr<Terminal> a = std::make_shared<Terminal>("a");
    std::shared_ptr<Terminal> b = std::make_shared<Terminal>("b");
    std::shared_ptr<Terminal> c = std::make_shared<Terminal>("c");
    std::shared_ptr<Terminal> d = std::make_shared<Terminal>("d");
    std::shared_ptr<Terminal> eps = std::make_shared<Terminal>("\\L");
    Grammar::epsilon = eps.get();

    std::vector<std::vector<std::shared_ptr<Symbol>>> vv_s;
    std::vector<std::shared_ptr<Symbol>> v_s;
    v_s.push_back(B); v_s.push_back(C); v_s.push_back(D); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(C); v_s.push_back(B); v_s.push_back(a); vv_s.push_back(v_s);
    A->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(C); v_s.push_back(a); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(eps); vv_s.push_back(v_s);
    B->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(c); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(eps); vv_s.push_back(v_s);
    C->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(d); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(b); vv_s.push_back(v_s);
    D->setProductions(vv_s);

    v_s.clear(); vv_s.clear();

    std::vector<std::shared_ptr<NonTerminal>> nts = {A,B,C,D};

    FirstSetsGenerator firstSG(nts);

    FirstSet fs_expected;
    fs_expected.add(c.get()); fs_expected.add(eps.get());
    ASSERT_EQ(nts[2]->getFirstSet().get()->getSet(), fs_expected.getSet());
    fs_expected.add(a.get());
    ASSERT_EQ(nts[1]->getFirstSet().get()->getSet(), fs_expected.getSet());
    fs_expected.removeEpsilon();
    fs_expected.add(b.get());fs_expected.add(d.get());
    ASSERT_EQ(nts[0]->getFirstSet().get()->getSet(), fs_expected.getSet());
    fs_expected.clear();
    fs_expected.add(b.get());fs_expected.add(d.get());
    ASSERT_EQ(nts[3]->getFirstSet().get()->getSet(), fs_expected.getSet());
}

TEST(FirstSetGeneration,LateEpsilonCase){
    /// A --> B C D | C B a
    /// B --> C a | \\L
    /// C --> c | \\L
    /// D --> d | b | \\L

    std::shared_ptr<NonTerminal> A = std::make_shared<NonTerminal>("A");
    std::shared_ptr<NonTerminal> B = std::make_shared<NonTerminal>("B");
    std::shared_ptr<NonTerminal> C = std::make_shared<NonTerminal>("C");
    std::shared_ptr<NonTerminal> D = std::make_shared<NonTerminal>("D");
    std::shared_ptr<Terminal> a = std::make_shared<Terminal>("a");
    std::shared_ptr<Terminal> b = std::make_shared<Terminal>("b");
    std::shared_ptr<Terminal> c = std::make_shared<Terminal>("c");
    std::shared_ptr<Terminal> d = std::make_shared<Terminal>("d");
    std::shared_ptr<Terminal> eps = std::make_shared<Terminal>("\\L");
    Grammar::epsilon = eps.get();

    std::vector<std::vector<std::shared_ptr<Symbol>>> vv_s;
    std::vector<std::shared_ptr<Symbol>> v_s;
    v_s.push_back(B); v_s.push_back(C); v_s.push_back(D); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(C); v_s.push_back(B); v_s.push_back(a); vv_s.push_back(v_s);
    A->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(C); v_s.push_back(a); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(eps); vv_s.push_back(v_s);
    B->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(c); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(eps); vv_s.push_back(v_s);
    C->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(d); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(b); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(eps); vv_s.push_back(v_s);
    D->setProductions(vv_s);

    v_s.clear(); vv_s.clear();

    std::vector<std::shared_ptr<NonTerminal>> nts = {A,B,C,D};

    FirstSetsGenerator firstSG(nts);

    FirstSet fs_expected;
    fs_expected.add(c.get()); fs_expected.add(eps.get());
    ASSERT_EQ(nts[2]->getFirstSet().get()->getSet(), fs_expected.getSet());
    fs_expected.add(a.get());
    ASSERT_EQ(nts[1]->getFirstSet().get()->getSet(), fs_expected.getSet());
    fs_expected.add(b.get());fs_expected.add(d.get());
    ASSERT_EQ(nts[0]->getFirstSet().get()->getSet(), fs_expected.getSet());
    fs_expected.clear();
    fs_expected.add(b.get());fs_expected.add(d.get());fs_expected.add(eps.get());
    ASSERT_EQ(nts[3]->getFirstSet().get()->getSet(), fs_expected.getSet());
}

