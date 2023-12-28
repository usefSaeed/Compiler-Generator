//
// Created by usef on 12/28/2023.
//

#include "gtest/gtest.h"
#include "../SyntaxPhase/FirstAndFollowGenerator/FollowSetsGenerator.h"
#include "../SyntaxPhase/GrammarParser/Grammar.h"

TEST(FollowSetGeneration,TerminalScenario){
    /// A --> a B b | B c
    /// B --> b C a | A a | \\L
    /// C --> A b c | \\L
    /// FIRST(A) = { a, b}
    /// FIRST(B) = { a, b, \\L}
    /// FIRST(C) = { a, b, \\L}
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
    v_s.push_back(a); v_s.push_back(B); v_s.push_back(b); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(B); v_s.push_back(c); vv_s.push_back(v_s);
    A->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(b); v_s.push_back(C); v_s.push_back(a); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(A); v_s.push_back(a); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(eps); vv_s.push_back(v_s);
    B->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(A); v_s.push_back(b); v_s.push_back(c); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(eps); vv_s.push_back(v_s);
    C->setProductions(vv_s);

    v_s.clear(); vv_s.clear();

    std::vector<std::shared_ptr<NonTerminal>> nts = {A,B,C};

    std::shared_ptr<FirstSet> tempFS = std::make_shared<FirstSet>();
    tempFS->add(a.get()); tempFS->add(b.get());
    A->getFirstSet()->addAll(tempFS);
    tempFS->add(eps.get());
    B->getFirstSet()->addAll(tempFS);
    C->getFirstSet()->addAll(tempFS);

    FollowSetsGenerator followSG(nts,A.get());

    FollowSet fs_expected;
    fs_expected.add(a.get());
    ASSERT_EQ(C->getFollowSet().get()->getSet(), fs_expected.getSet());
    fs_expected.addEOI();  fs_expected.add(b.get());
    ASSERT_EQ(A->getFollowSet().get()->getSet(), fs_expected.getSet());
    fs_expected.clear();
    fs_expected.add(b.get()); fs_expected.add(c.get());
    ASSERT_EQ(B->getFollowSet().get()->getSet(), fs_expected.getSet());
}


TEST(FollowSetGeneration,NonTerminalScenario){
    /// A --> a B C | C A
    /// B --> b C B | A B
    /// C --> c A C
    /// FIRST(A) = { a, c }
    /// FIRST(B) = { a, b, c }
    /// FIRST(C) = { c }
    /// FOLLOW(A) = { $, a, b, c }
    /// FOLLOW(B) = { c }
    /// FOLLOW(C) = { $, a, b, c }
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
    v_s.push_back(a); v_s.push_back(B); v_s.push_back(C); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(C); v_s.push_back(A); vv_s.push_back(v_s);
    A->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(b); v_s.push_back(C); v_s.push_back(B); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(A); v_s.push_back(B); vv_s.push_back(v_s);
    B->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(c); v_s.push_back(A); v_s.push_back(C); vv_s.push_back(v_s);
    C->setProductions(vv_s);

    v_s.clear(); vv_s.clear();

    std::vector<std::shared_ptr<NonTerminal>> nts = {A,B,C};

    std::shared_ptr<FirstSet> tempFS = std::make_shared<FirstSet>();
    tempFS->add(c.get());
    C->getFirstSet()->addAll(tempFS);
    tempFS->add(a.get());
    A->getFirstSet()->addAll(tempFS);
    tempFS->add(b.get());
    B->getFirstSet()->addAll(tempFS);

    FollowSetsGenerator followSG(nts,A.get());

    FollowSet fs_expected;

    fs_expected.add(c.get());
    ASSERT_EQ(B->getFollowSet().get()->getSet(), fs_expected.getSet());
    fs_expected.addEOI();  fs_expected.add(b.get()); fs_expected.add(a.get());
    ASSERT_EQ(A->getFollowSet().get()->getSet(), fs_expected.getSet());
    ASSERT_EQ(C->getFollowSet().get()->getSet(), fs_expected.getSet());
}

TEST(FollowSetGeneration,EpsilonScenario){
    /// A --> a B C | C A
    /// B --> b C B | C B
    /// C --> c A C | \\L
    /// FIRST(A) = { a, c }
    /// FIRST(B) = { b, c }
    /// FIRST(C) = { c, \\L }
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
    v_s.push_back(a); v_s.push_back(B); v_s.push_back(C); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(C); v_s.push_back(A); vv_s.push_back(v_s);
    A->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(b); v_s.push_back(C); v_s.push_back(B); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(C); v_s.push_back(B); vv_s.push_back(v_s);
    B->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(c); v_s.push_back(A); v_s.push_back(C); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(eps);
    C->setProductions(vv_s);

    v_s.clear(); vv_s.clear();

    std::vector<std::shared_ptr<NonTerminal>> nts = {A,B,C};

    std::shared_ptr<FirstSet> tempFS = std::make_shared<FirstSet>();
    tempFS->add(c.get());tempFS->addEpsilon();
    C->getFirstSet()->addAll(tempFS);
    tempFS->removeEpsilon();
    tempFS->add(a.get());
    A->getFirstSet()->addAll(tempFS);
    tempFS->clear();
    tempFS->add(b.get()); tempFS->add(c.get());
    B->getFirstSet()->addAll(tempFS);

    FollowSetsGenerator followSG(nts,A.get());

    FollowSet fs_expected;
    fs_expected.add(a.get()); fs_expected.add(b.get()); fs_expected.add(c.get());fs_expected.addEOI();
    ASSERT_EQ(B->getFollowSet().get()->getSet(), fs_expected.getSet());
    ASSERT_EQ(A->getFollowSet().get()->getSet(), fs_expected.getSet());
    ASSERT_EQ(C->getFollowSet().get()->getSet(), fs_expected.getSet());
}
