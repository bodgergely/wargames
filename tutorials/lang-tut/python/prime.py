def sieve(n): 
    # Create a boolean array "prime[0..n]" and initialize 
    # all entries it as true. A value in prime[i] will 
    # finally be false if i is Not a prime, else true. 
    prime = [True for i in range(n + 1)] 
    p = 2
    while (p * p <= n): 
          
        # If prime[p] is not changed, then it is a prime 
        if (prime[p] == True): 
              
            # Update all multiples of p 
            for i in range(p * 2, n + 1, p): 
                prime[i] = False
        p += 1
    prime[0]= False
    prime[1]= False
    
    res = []
    for p in range(n + 1): 
        if prime[p]: 
            res.append(p)
    return res

def factors(n):
    """Find prime factors of n.

    :n: positive integer
    :returns: list of primes

    """
    facts = []
    candidates = sieve(n)
    for i in candidates:
        if n % i == 0:
            facts.append(i)
    if facts[-1] == n:
        facts.pop()

    return facts

def factorize(n):
    res = []
    facts = factors(n)
    if len(facts) == 1:
        a = 1
        while a!=n:
            res.append(facts[0])
            a*=facts[0]
    else:
        res = facts
    
    return res
    

import unittest
class TestFactor(unittest.TestCase):
    def validate(self, n):
        def multiply(lis):
            c = 1
            for l in lis:
                c*=l
            return c
        facts = factorize(n)
        if sieve(n)[-1] == n:
            self.assertEqual(len(facts), 0)
        if facts:
            self.assertEqual(multiply(facts), n)
    def testFactors(self):
         for i in range(2, 3000):
             self.validate(i)
        # self.validate(4)
    def testPrime(self):
        primes = sieve(4000)
        import random
        for i in range(300):
            p  = random.choice(primes)
            self.assertEqual(len(factorize(p)), 0)
        

if __name__ == "__main__":
    unittest.main()



