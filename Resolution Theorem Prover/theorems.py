howling = [[1, ['howl(Z)'], ['hound(Z)']], [2, [], ['have(X,Y)', 'cat(Y)', 'have(X,Z)', 'mouse(Z)']], [3, [],
            ['ls(W)', 'have(W, V)', 'howl(V)']], [4, ['have(john,a)'], []], [5, ['cat(a)', 'hound(a)'], []],
           [6, ['mouse(b)'], []], [7, ['ls(john)'], []], [8, ['have(john,b)'], []]]

rr = [[1, ['rr(a)'], ['coyote(Y)']], [2, ['chase(Z,a)'], ['coyote(Z)']], [3, ['smart(X)'], ['rr(X)', 'beep(X)']],
        [4, [], ['coyote(W)', 'rr(U)', 'catch(W,U)', 'smart(U)']], [5, ['frustrated(S)', 'catch(S,T)'],
        ['coyote(S)', 'rr(T)', 'chase(S,T)']], [6, ['beep(R)'], ['rr(R)']], [7, ['coyote(b)'], []], [8, [],
        ['frustrated(b)']]]

customs = [[1, ['v(X)', 's(X,f(X))'], ['e(X)']], [2, ['v(Y)', 'c(f(Y))'], ['e(Y)']], [3, ['e(a)'], []], [4, ['d(a)'],
            []], [5, ['d(Z)'], ['s(a,Z)']], [6, [], ['d(W)', 'v(W)']], [7, [], ['d(R)', 'c(R)']]]

harmonia = [[1, ['grandparent(X,Y)'], ['parent(X,Z)', 'parent(Z,Y)']], [2, ['parent(X,Y)'], ['mother(X,Y)']], [3,
            ['parent(X,Y)'], ['father(X,Y)']], [4, ['father(zeus,ares)'], []], [5, ['mother(hera,ares)'], []],
            [6, ['father(ares,harmonia)'], []], [7, [], ['grandparent(X,harmonia)']]]

user = [[1, ['record(r)'], []], [2, ['plays(turntable,r)'], []], [3, ['speaker(X)'], ['record(Y)', 'plays(X,Y)']],
        [4, [], ['speaker(S)', 'music(Y)', 'stops(S,Y)']], [5, ['stops(turntable,electronic)', 'stops(cops,electronic)'], []],
        [6, ['song(electronic)'], []], [7, ['music(Z)'], ['song(Z)']], [8, [], ['stops(cops,electronic)']]]
