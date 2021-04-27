import numpy as np
import os 


class AI:
    def __init__(self):
        self.cards = np.array([-2,0,1,2,3,4,5,6,7,8,9,10,11])
        self.hand = np.array([[13] * 3, [13] * 3])
        self.hand[0,0] = self.__get_card()
        self.hand[1,0] = self.__get_card()
    
    def __get_card(self):
        return self.cards[np.random.randint(0,high=len(self.cards))]

    def __col_total(self, column):
        '''returns column total
        Args:
            column - the column index to calculate'''
        if self.hand[0,column] == self.hand[1,column]:
            return 0
        else:
            return self.hand[0,column] + self.hand[1,column]

    def change(self, card):
        '''returns an array of 3,3 where each element represents the change
        in score if replaced by card'''
        changes = np.zeros(6)
        i = 0
        for j in range(3):
            if self.hand[0,j] == self.hand[1,j] and self.hand[0,j] != 13:
                changes[i] = card + self.hand[1,j]
                i += 1
                continue
            if self.hand[1,j] == card:
                changes[i] = -1 * card
                i += 1
                continue
            if self.hand[0,j] == 13:
                less = (card**2 + card)/2
                if card == -2:
                    less = 0
                more = (11**2 + 11)/2 - less
                if card != -2: less -= 2
                less *= np.where(self.cards == card)[0] /12
                more *= (len(self.cards) - np.where(self.cards == card)[0]) / 12
                EV = less - more
                changes[i] = EV/66 * 5
                i += 1
                continue
            changes[i] = card - self.hand[0,j]
            i +=1
        for j in range(3):
            if self.hand[0,j] == self.hand[1,j] and self.hand[1,j] != 13:
                changes[i] = card + self.hand[0,j]
                i += 1
                continue
            if self.hand[0,j] == card:
                changes[i] = -1 * card
                i += 1
                continue
            if self.hand[0,j] == 13:
                less = (card**2 + card)/2
                if card == -2:
                    less = 0
                more = (11**2 + 11)/2 - less
                if card != -2: less -= 2
                less *= np.where(self.cards == card)[0] /12
                more *= (len(self.cards) - np.where(self.cards == card)[0]) / 12
                EV = less - more
                changes[i] = EV/66 *  5
                i += 1
                continue
            changes[i] = card - self.hand[1,j]
            i += 1
        return changes.reshape(2,3)

    def score(self):
        score = 0
        for i in range(3):
            score += self.__col_total(i)
        return score
        
    def play(self, card, end=False):
        other_cards = np.delete(self.cards, card)
        other_card_values = []
        for c in other_cards:
            other_card_values.append(self.change(c))
        card_value = np.mean(self.change(card))
        other_value = np.mean(other_card_values)
        if card_value > other_value:
            card = self.__get_card()
        changes = self.change(card)
        index = np.argmin(changes)
        if changes.flatten()[index] >= 0:
            if end == True:
                self.hand = np.where(self.hand == 13, self.__get_card(), self.hand)
            return card
        self.hand = self.hand.flatten()
        tmp = self.hand[index]
        self.hand[index] = card
        self.hand = self.hand.reshape(2,3)
        if tmp == 13:
            tmp = self.__get_card()
        if end == True:
            self.hand = np.where(self.hand == 13, self.__get_card(), self.hand)
        return tmp 

class Player(AI):
    def __init__(self):
        super().__init__()
        self.valid_input = '012345n'
    def __get_card(self):
        return self.cards[np.random.randint(0, len(self.cards))]
    def play(self, card, end=False):
        print('Current Card', card)
        inp = input()
        if inp not in self.valid_input:
            if end == True:
                self.hand = np.where(self.hand == 13, self.__get_card(), self.hand)
            return card
        if inp == 'n':
            card = self.__get_card()
            print('New Card: ', card)
            inp = input()
        if inp not in self.valid_input[:-1]:
            if end == True:
                self.hand = np.where(self.hand == 13, self.__get_card(), self.hand)
            return card
        inp = int(inp)
        self.hand = self.hand.flatten()
        tmp = self.hand[inp]
        self.hand[inp] = card
        self.hand = self.hand.reshape(2,3)
        if tmp == 13:
            tmp = self.__get_card()
        if end == True:
            self.hand = np.where(self.hand == 13, self.__get_card(), self.hand)
        return tmp

        


class Game:
    def __init__(self, players):
        self.players = []
        self.players.append(Player())
        self.cards = np.array([-2,0,1,2,3,4,5,6,7,8,9,10,11])
        for i in range(players):
            self.players.append(AI())
    def __get_card(self):
        return self.cards[np.random.randint(0, 13)]
    
    def play(self):
        end = len(self.players)
        curr_player_index = 0 # index of the player whose turn it is
        current_card = self.__get_card()
        while end != (curr_player_index % len(self.players)):
            curr_player = self.players[curr_player_index % len(self.players)]
            if curr_player_index % len(self.players) == 0:
                self.display_board()
            if end != len(self.players):
                current_card = curr_player.play(current_card, end=True)
            else:
                current_card = curr_player.play(current_card)
            if np.count_nonzero(curr_player.hand==13) == 0 and end == len(self.players):
                end = curr_player_index % len(self.players)
                print('end has been set as ', end)
            curr_player_index += 1
            os.system('clear')
        self.display_board()
        for i, p in enumerate(self.players):
            print(f'Player {i} Score: {p.score()}')

            
    def display_board(self):
        for i in range(len(self.players) - 1, -1, -1):
            curr_player = self.players[i]
            print(f'''Player {i}\n\t{curr_player.hand[0]}\n\t{curr_player.hand[1]}''')
        
            
game = Game(2)
game.play()

