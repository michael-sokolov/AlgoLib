__author__ = 'tiirz'
import math
import sys


class automata:
    def __init__(self):
        self.len = []
        self.link = []
        self.to = []
        self.last = 0
        self.len.append(0)
        self.link.append(-1)
        self.to.append({})

    def add(self, c):
        self.len.append(self.len[self.last] + 1)
        self.to.append({})
        self.link.append(0)
        p = self.last
        cur = len(self.len) - 1
        while p != -1:
            if c in self.to[p]:
                break
            else:
                self.to[p][c] = cur
            p = self.link[p]
        if p == -1:
            self.link[cur] = 0
        else:
            q = self.to[p][c]
            if self.len[p] + 1 == self.len[q]:
                self.link[cur] = q
            else:
                clone = len(self.len)
                self.to.append(dict(self.to[q]))
                self.len.append(self.len[p] + 1)
                self.link.append(self.link[q])
                self.link[q] = clone
                self.link[cur] = clone
                while p != -1:
                    if self.to[p][c] == q:
                        self.to[p][c] = clone
                    p = self.link[p]
        self.last = cur
a = automata()
u = []


def dfs(v):
    u[v] = 1
    for key in a.to[v]:
        if u[a.to[v][key]] == -1:
            dfs(a.to[v][key])
        u[v] += u[a.to[v][key]]
    return u[v]


inp = open('bacon.in', 'r')
outp = open('bacon.out', 'w')
sys.setrecursionlimit(100000)
for s in inp:
    for i in range(0, len(s) - 1):
        a.add(s[i])

u = [-1, ] * 3 * 10000
outp.write(str(dfs(0) - 1))
outp.flush()
