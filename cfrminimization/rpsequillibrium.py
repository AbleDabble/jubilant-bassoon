import numpy as np

class RPSTrainer:
    def __init__(self, initialStrategy: np.ndarray = np.array([0.4, 0.3, 0.3])):
        self.regretSum = np.zeros(3)
        self.strategy = np.zeros(3)
        self.strategySum = np.zeros(3)

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
        r = np.random.random() # type: ignore
        # print("Strategy in getAction", strategy)
        #print("len of strategy", len(strategy))
        for i in range(len(strategy) + 1):
            #print("strategy sum:", np.sum(strategy[:i]))
            #print("r", r)
            if r < np.sum(strategy[:i+1]):
                return i
        return 2
    
    def train(self, myAction, otherAction):
        actionUtility = np.zeros(3)
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

class Game:
    def __init__(self, initialStrategy: np.ndarray=np.array([0.5,0.25,0.25])):
        self.playerOne = RPSTrainer(initialStrategy=initialStrategy)
        self.playerOneStrategy = initialStrategy
        self.playerTwo = RPSTrainer(initialStrategy=initialStrategy)
        self.playerTwoStrategy = initialStrategy
        self.moveNames = ["ROCK", "PAPER", "SCISSORS"]
    
    def playGame(self, iterations):
        for _ in range(iterations):
            playerOneAction = self.playerOne.getAction(self.playerOneStrategy)
            playerTwoAction = self.playerTwo.getAction(self.playerTwoStrategy)
            self.playerOne.train(playerOneAction, playerTwoAction)
            self.playerTwo.train(playerTwoAction, playerOneAction)
            #print(f"{self.moveNames[playerOneAction]} vs {self.moveNames[playerTwoAction]}")
            self.playerOneStrategy = self.playerOne.getStrategy()
            self.playerTwoStrategy = self.playerTwo.getStrategy()
        print("Player one avg Strategy: ", self.playerOne.getAvgStrategy())
        print("Player two avg strategy: ", self.playerTwo.getAvgStrategy())
game = Game()
game.playGame(10_000)

           
        

