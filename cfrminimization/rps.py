#!/home/cary/anaconda3/envs/fun/bin/python
# Sometimes my Genius, it generates its own gravity
import numpy as np 
import pprint

pp = pprint.PrettyPrinter(indent=4)

# N = {1, ..., n} set of n players
# Si is a finite for player i
# A = S_1 x ... x S_n is the set of all combinations of simultaneous actions of all players
# u is a functino mapping each action profile to a vector of utilities
# Regret is the difference in utility between action not chosen and action chosen with respect to fix choice

# u(s'_i, s_{-i}) - u(a) = regret first term is utility of action subsituted with other action and second term is a in A


class RPSTrainer:
    def __init__(self, oppStrategy: np.ndarray = np.array([0.4, 0.3, 0.3])):
        self.regretSum = np.zeros(3)
        self.strategy = np.zeros(3)
        self.strategySum = np.zeros(3)
        self.oppStrategy = oppStrategy

    def getStrategy(self):
        """
        Get the strategy for a single iteration based on regretSum
        not considering negative regrets
        """
        normalizingSum = 0
        self.strategy = np.where(self.regretSum > 0, self.regretSum, 0)
        normalizingSum += np.sum(self.strategy)
        if normalizingSum > 0:
            self.strategy /= normalizingSum
        else:
            self.strategy = np.ones(3) / 3
        self.strategySum += self.strategy
        return self.strategy

    def getAction(self, strategy):
        """
        return the action based on the probabilities listed in strategy
        """
        r = np.random.random()
        for i in range(len(strategy) + 1, 1):
            if r < np.sum(strategy[:i]):
                return i - 1
        return 2
    
    def train(self, iterations):
        actionUtility = np.zeros(3)
        for i in range(iterations):
           self.strategy = self.getStrategy()
           myAction = self.getAction(self.strategy)
           otherAction = self.getAction(self.oppStrategy)
           actionUtility[otherAction] = 0
           actionUtility[(otherAction + 1) % 3] = 1
           actionUtility[(otherAction - 1) % 3] = -1
           myActionUtility = actionUtility[myAction]
           self.regretSum += actionUtility - myActionUtility
    def getAvgStrategy(self):
        avgStrategy = np.zeros(3)
        normalizingSum = np.sum(self.strategySum)
        if normalizingSum > 0:
            avgStrategy = self.strategySum / normalizingSum
        else:
            avgStrategy = np.ones(3) / 3
        return avgStrategy

rps = RPSTrainer(oppStrategy=np.array([0.7,0.1,0.2]))
rps.train(1000)
print("avg strategy:", rps.getAvgStrategy())

def getAction(strategy):
    """
    return the action based on the probabilities listed in strategy
    """
    r = np.random.random()
    for i in range(len(strategy) + 1, 1):
        if r < np.sum(strategy[:i]):
            return i - 1
    return 2
        

