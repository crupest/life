package javatest;

import java.util.HashSet;
import java.util.Random;

public class E0204 {
	public static void main(String[] args) {
		Random r = new Random();
		HashSet<Card> set = new HashSet<Card>();

		while (set.size() != 4) {
			set.add(Card.random(r));
		}

		for (Card card : set) {
			System.out.println(card);
		}
	}
}

class Card {
	public static final String[] suits = { "Spades", "Hearts", "Clubs", "Diamonds" };
	public static final String[] ranks = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen",
			"King" };

	public static Card random(Random r) {
		return new Card(suits[r.nextInt(suits.length)], ranks[r.nextInt(ranks.length)]);
	}

	public Card(String suit, String rank) {
		super();
		this.suit = suit;
		this.rank = rank;
	}

	private String suit;
	private String rank;

	public String getSuit() {
		return suit;
	}

	public void setSuit(String suit) {
		this.suit = suit;
	}

	public String getRank() {
		return rank;
	}

	public void setRank(String rank) {
		this.rank = rank;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((rank == null) ? 0 : rank.hashCode());
		result = prime * result + ((suit == null) ? 0 : suit.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		Card other = (Card) obj;
		if (rank == null) {
			if (other.rank != null)
				return false;
		} else if (!rank.equals(other.rank))
			return false;
		if (suit == null) {
			if (other.suit != null)
				return false;
		} else if (!suit.equals(other.suit))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "Card [suit=" + suit + ", rank=" + rank + "]";
	}
}
