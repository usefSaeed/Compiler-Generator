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
    /// FOLLOW(A) = { $, a, b, c }
    /// FOLLOW(B) = { $, a, b, c }
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

TEST(FollowSetGeneration,CircularScenario){
    /// A --> a B  | D B
    /// B --> b A | f  C
    /// C --> c C A C e | d B D
    /// D --> e C
    /// FIRST(A) = { a, e}
    /// FIRST(B) = { b, f }
    /// FIRST(C) = { c, d }
    /// FIRST(D) = { e }
    /// FOLLOW(A) = { $, c, d, e }
    /// FOLLOW(B) = { $, c, d, e }
    /// FOLLOW(C) = { $, a, b, c, d, e, f }
    /// FOLLOW(C) = { $, a, b, c, d, e, f }
    std::shared_ptr<NonTerminal> A = std::make_shared<NonTerminal>("A");
    std::shared_ptr<NonTerminal> B = std::make_shared<NonTerminal>("B");
    std::shared_ptr<NonTerminal> C = std::make_shared<NonTerminal>("C");
    std::shared_ptr<NonTerminal> D = std::make_shared<NonTerminal>("D");
    std::shared_ptr<Terminal> a = std::make_shared<Terminal>("a");
    std::shared_ptr<Terminal> b = std::make_shared<Terminal>("b");
    std::shared_ptr<Terminal> c = std::make_shared<Terminal>("c");
    std::shared_ptr<Terminal> d = std::make_shared<Terminal>("d");
    std::shared_ptr<Terminal> e = std::make_shared<Terminal>("e");
    std::shared_ptr<Terminal> f = std::make_shared<Terminal>("f");
    std::shared_ptr<Terminal> eps = std::make_shared<Terminal>("\\L");
    Grammar::epsilon = eps.get();

    std::vector<std::vector<std::shared_ptr<Symbol>>> vv_s;
    std::vector<std::shared_ptr<Symbol>> v_s;
    v_s.push_back(a); v_s.push_back(B); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(D); v_s.push_back(B); vv_s.push_back(v_s);
    A->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(b); v_s.push_back(A); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(f); v_s.push_back(C); vv_s.push_back(v_s);
    B->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(c);v_s.push_back(C); v_s.push_back(A); v_s.push_back(C); v_s.push_back(e); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(d); v_s.push_back(B); v_s.push_back(D); vv_s.push_back(v_s);
    C->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(e); v_s.push_back(C); vv_s.push_back(v_s);
    D->setProductions(vv_s);

    v_s.clear(); vv_s.clear();

    std::vector<std::shared_ptr<NonTerminal>> nts = {A,B,C,D};

    std::shared_ptr<FirstSet> tempFS = std::make_shared<FirstSet>();
    tempFS->add(e.get());    tempFS->add(a.get());
    A->getFirstSet()->addAll(tempFS);
    tempFS->clear();
    tempFS->add(b.get());    tempFS->add(f.get());
    B->getFirstSet()->addAll(tempFS);
    tempFS->clear();
    tempFS->add(d.get()); tempFS->add(c.get());
    C->getFirstSet()->addAll(tempFS);
    tempFS->clear();
    tempFS->add(e.get());
    D->getFirstSet()->addAll(tempFS);

    FollowSetsGenerator followSG(nts,A.get());

    FollowSet fs_expected;
    fs_expected.add(e.get()); fs_expected.add(d.get()); fs_expected.add(c.get());fs_expected.addEOI();
    ASSERT_EQ(B->getFollowSet().get()->getSet(), fs_expected.getSet());
    ASSERT_EQ(A->getFollowSet().get()->getSet(), fs_expected.getSet());
    fs_expected.add(f.get()); fs_expected.add(b.get());fs_expected.add(a.get());
    ASSERT_EQ(D->getFollowSet().get()->getSet(), fs_expected.getSet());
    ASSERT_EQ(C->getFollowSet().get()->getSet(), fs_expected.getSet());
}

TEST(FollowSetGeneration,Complex){
    /// E --> T E`
    /// E` --> + E | \\L
    /// T --> F T`
    /// T` --> T | \\L
    /// F --> P F`
    /// F` --> * F | \\L
    /// P --> ( E ) | a | b | Em
    /// FIRST(E) = FIRST(F) = FIRST(T) = FIRST(P) = { a, b, (, Em }
    /// FIRST(T`) = { a, b, (, Em, \\L }
    /// FIRST(E') = { +, \\L }
    /// FIRST(F') = { *, \\L }
    /// FOLLOW(E) = FOLLOW(E`) = { $, +, ) }
    /// FOLLOW(T) = FOLLOW(T`) = { $, +, ) }
    /// FOLLOW(E) = FOLLOW(E`) = { $, ), (, a, b, Em, + }
    /// FOLLOW(P) = { $, ), (, a, b, Em, +, * }

    std::shared_ptr<NonTerminal> E = std::make_shared<NonTerminal>("E");
    std::shared_ptr<NonTerminal> E_d = std::make_shared<NonTerminal>("E`");
    std::shared_ptr<NonTerminal> T = std::make_shared<NonTerminal>("T");
    std::shared_ptr<NonTerminal> T_d = std::make_shared<NonTerminal>("T`");
    std::shared_ptr<NonTerminal> F = std::make_shared<NonTerminal>("F");
    std::shared_ptr<NonTerminal> F_d = std::make_shared<NonTerminal>("F`");
    std::shared_ptr<NonTerminal> P = std::make_shared<NonTerminal>("P");
    std::shared_ptr<Terminal> plus = std::make_shared<Terminal>("+");
    std::shared_ptr<Terminal> ast = std::make_shared<Terminal>("*");
    std::shared_ptr<Terminal> lb = std::make_shared<Terminal>("(");
    std::shared_ptr<Terminal> rb = std::make_shared<Terminal>(")");
    std::shared_ptr<Terminal> a = std::make_shared<Terminal>("a");
    std::shared_ptr<Terminal> b = std::make_shared<Terminal>("b");
    std::shared_ptr<Terminal> Em = std::make_shared<Terminal>("Em");
    std::shared_ptr<Terminal> eps = std::make_shared<Terminal>("\\L");
    Grammar::epsilon = eps.get();

    std::vector<std::vector<std::shared_ptr<Symbol>>> vv_s;
    std::vector<std::shared_ptr<Symbol>> v_s;
    v_s.push_back(T); v_s.push_back(E_d); vv_s.push_back(v_s);
    E->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(plus); v_s.push_back(E); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(eps); vv_s.push_back(v_s);
    E_d->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(F);v_s.push_back(T_d); vv_s.push_back(v_s);
    T->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(T); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(eps); vv_s.push_back(v_s);
    T_d->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(P); v_s.push_back(F_d); vv_s.push_back(v_s);
    F->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(ast); v_s.push_back(F); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(eps); vv_s.push_back(v_s);
    F_d->setProductions(vv_s);

    v_s.clear(); vv_s.clear();
    v_s.push_back(lb); v_s.push_back(E); v_s.push_back(rb); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(a); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(b); vv_s.push_back(v_s);
    v_s.clear();
    v_s.push_back(Em); vv_s.push_back(v_s);
    P->setProductions(vv_s);


    std::shared_ptr<FirstSet> tempFS = std::make_shared<FirstSet>();
    tempFS->add(a.get()); tempFS->add(b.get()); tempFS->add(lb.get()); tempFS->add(Em.get());
    E->getFirstSet()->addAll(tempFS);
    T->getFirstSet()->addAll(tempFS);
    F->getFirstSet()->addAll(tempFS);
    P->getFirstSet()->addAll(tempFS);
    tempFS->add(eps.get());
    T_d->getFirstSet()->addAll(tempFS);
    tempFS->clear();
    tempFS->add(eps.get());tempFS->add(plus.get());
    E_d->getFirstSet()->addAll(tempFS);
    tempFS->clear();
    tempFS->add(eps.get());tempFS->add(ast.get());
    F_d->getFirstSet()->addAll(tempFS);

    std::vector<std::shared_ptr<NonTerminal>> nts = {E,E_d,T,T_d,F,F_d,P};

    FollowSetsGenerator followSG(nts,E.get());

    FollowSet fs_expected;
    fs_expected.add(rb.get());fs_expected.addEOI();
    ASSERT_EQ(E->getFollowSet().get()->getSet(), fs_expected.getSet());
    ASSERT_EQ(E_d->getFollowSet().get()->getSet(), fs_expected.getSet());
    fs_expected.add(plus.get());
    ASSERT_EQ(T->getFollowSet().get()->getSet(), fs_expected.getSet());
    ASSERT_EQ(T_d->getFollowSet().get()->getSet(), fs_expected.getSet());
    fs_expected.add(a.get()); fs_expected.add(b.get()); fs_expected.add(Em.get()); fs_expected.add(lb.get());
    ASSERT_EQ(F->getFollowSet().get()->getSet(), fs_expected.getSet());
    ASSERT_EQ(F_d->getFollowSet().get()->getSet(), fs_expected.getSet());
    fs_expected.add(ast.get());
    ASSERT_EQ(P->getFollowSet().get()->getSet(), fs_expected.getSet());
}
