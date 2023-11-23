class AutomataProcessor:
    def __init__(self):
        self.start_input = ""  # input word to be found or not found
        self.found = 0  # stores found state
        self.accepted_config = []  # end configuration that was accepted

        # production rules ("read input", "pop stack", "push stack", "next state")
        self.productions = {}

        # start state and stack symbol
        self.start_symbol = ""
        self.stack_start = ""

        # list of acceptable states
        self.acceptable_states = []

        # E - accept on empty stack or F - acceptable state
        self.accept_with = ""

    def generate(self, state, input_str, stack, config):
        total = 0

        if self.found:
            return 0

        if self.is_found(state, input_str, stack):
            self.found = 1
            self.accepted_config.extend(config)
            return 1

        moves = self.get_moves(state, input_str, stack, config)
        if not moves:
            return 0

        for i in moves:
            total += self.generate(i[0], i[1], i[2], config + [(i[0], i[1], i[2])])

        return total

    def get_moves(self, state, input_str, stack, config):
        moves = []

        for i in self.productions:
            if i != state:
                continue

            for j in self.productions[i]:
                current = j
                new = [current[3]]

                if current[0]:
                    if input_str and input_str[0] == current[0]:
                        new.append(input_str[1:])
                    else:
                        continue
                else:
                    new.append(input_str)

                if current[1]:
                    if stack and stack[0] == current[1]:
                        new.append(current[2] + stack[1:])
                    else:
                        continue
                else:
                    new.append(current[2] + stack)

                moves.append(new)

        return moves

    def is_found(self, state, input_str, stack):
        if input_str:
            return 0

        if self.accept_with == "E":
            return len(stack) < 1

        return state in self.acceptable_states

    def print_config(self, config):
        for i in config:
            print(i)

    def parse_file(self, filename):
        try:
            with open(filename, 'r') as file:
                lines = [line.rstrip() for line in file]
        except FileNotFoundError:
            return 0

        self.start_symbol = lines[3]
        self.stack_start = lines[4]
        self.acceptable_states = lines[5].split()
        self.accept_with = lines[6]

        for i in range(7, len(lines)):
            production = lines[i].split()
            configuration = [(production[1], production[2], production[4], production[3])]
            key = production[0]

            if key not in self.productions:
                self.productions[key] = []

            configuration = [tuple(s if s != "e" else "" for s in tup) for tup in configuration]
            self.productions[key].extend(configuration)

        print(self.productions, self.start_symbol, self.stack_start, self.acceptable_states, self.accept_with)
        return 1

    def done(self):
        if self.found:
            print(f"Hurray! Input word \"{self.start_input}\" is part of grammar.")
        else:
            print(f"Sorry! Input word \"{self.start_input}\" is not part of grammar.")

    def run(self):
        filename = input("Please enter your automata file:\n")
        while not self.parse_file(filename):
            print("File not found!")
            filename = input("Please enter your automata file again:\n")
        print("Automata built.")

        self.start_input = input("Please enter your word:\n")
        print(f"Checking word \"{self.start_input}\" ...")

        while self.start_input != "end":
            if not self.generate(self.start_symbol, self.start_input, self.stack_start, [(self.start_symbol, self.start_input, self.stack_start)]):
                self.done()
            else:
                self.print_config(self.accepted_config)
                self.done()

            self.start_input = input("Enter your next word (or end):\n")
            print(f"Checking word \"{self.start_input}\" ...")


# To run the automata processor:
processor = AutomataProcessor()
processor.run()
