import numpy as np

def evaluate(hand: list) -> int:
    bit_hand = [handDict[card] for card in hand]
    flushval = 0xF000
    flushval = (bit_hand[0] & bit_hand[1] & bit_hand[2] & bit_hand[3] & bit_hand[4]) & 0xF000
    if flushval > 0:
        lookupid = (bit_hand[0] | bit_hand[1] | bit_hand[2] | bit_hand[3] | bit_hand[4]) >> 16
        return flushes[lookupid]
    lookupid = (bit_hand[0] | bit_hand[1] | bit_hand[2] | bit_hand[3] | bit_hand[4]) >> 16
    straight_highcard = unique5[lookupid]
    if straight_highcard > 0:
        return straight_highcard
    lookupid = (bit_hand[0] & 0xFF) * (bit_hand[1] & 0xFF) * (bit_hand[2] & 0xFF) * (bit_hand[3] & 0xFF) * (bit_hand[4] & 0xFF)
    hand_rank = prodVal[lookupid]
    return hand_rank

def pick_winner(hands: list) -> int:
    '''returns index of hands'''
    hand_ranks = np.array([evaluate(hand) for hand in hands])
    return np.argsort(hand_ranks)[0] # 
