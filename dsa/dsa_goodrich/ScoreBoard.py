class GameEntry:
    def __init__(self, name, score):
        self._name = name
        self._score = score

    def get_name(self):
        return self._name

    def get_score(self):
        return self._score

    def __str__(self):
        return f"({self._name}, {self._score})"


class Scoreboard:
    def __init__(self, capacity=10):
        self._board = [None] * capacity
        self._n = 0

    def __getitem__(self, k):
        return self._board[k]

    def __len__(self):
        return self._n

    def __str__(self):
        return "\n".join(str(self._board[j]) for j in range(self._n))

    def add(self, entry):
        score = entry.get_score()

        # Is this score good enough to be added?
        good = (
            self._n < len(self._board)
            or score > self._board[self._n - 1].get_score()
        )

        if good:

            # If board not full, increase number of entries
            if self._n < len(self._board):
                self._n += 1

            j = self._n - 1

            # Shift lower scores to the right
            while (
                j > 0
                and self._board[j - 1] is not None
                and self._board[j - 1].get_score() < score
            ):
                self._board[j] = self._board[j - 1]
                j -= 1

            self._board[j] = entry


if __name__ == "__main__":
    board = Scoreboard(5)

    board.add(GameEntry("Rayan", 89))
    board.add(GameEntry("Riyad", 90))
    board.add(GameEntry("Alice", 75))
    board.add(GameEntry("Bob", 100))

    print(board)