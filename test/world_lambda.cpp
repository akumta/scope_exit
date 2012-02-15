
// Copyright (C) 2006-2009, 2012 Alexander Nasonov
// Copyright (C) 2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/scope_exit

#include <boost/config.hpp>
#ifndef BOOST_NO_LAMBDAS

#define BOOST_TEST_MODULE TestWorldLambda
#include <boost/test/unit_test.hpp>
#include <vector>

struct person {};

struct world {
    void add_person(person const& a_person);
    std::vector<person> persons_;
};

//[world_lambda
#include <functional>

struct scope_exit {
    scope_exit(std::function<void (void)> f) : f_(f) {}
    ~scope_exit(void) { f_(); }
private:
    std::function<void (void)> f_;
};

void world::add_person(person const& a_person) {
    bool commit = false;

    persons_.push_back(a_person);
    scope_exit on_exit1([&commit, &persons_]() { // Use C++11 lambda.
        if(!commit) persons_.pop_back();
    });

    // ...

    commit = true;
}
//]

BOOST_AUTO_TEST_CASE( test_world_lambda ) {
    world w;
    person p;
    w.add_person(p);
    BOOST_CHECK( w.persons_.size() == 1 );
}

#else // No lambdas (trivial test).

int main(void) { return 0; }

#endif

