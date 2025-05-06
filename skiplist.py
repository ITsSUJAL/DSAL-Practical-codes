import random

class SkipNode:
    def __init__(self, value, level):
        self.value = value
        self.forward = [None] * (level + 1)

class SkipList:
    def __init__(self, max_level):
        self.max_level = max_level
        self.header = SkipNode(None, max_level)
        self.level = 0

    def _random_level(self):
        level = 0
        while random.random() < 0.5 and level < self.max_level:
            level += 1
        return level

    def insert(self, value):
        update = [None] * (self.max_level + 1)
        current = self.header

        # Traverse from top level down to 0
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].value < value:
                current = current.forward[i]
            update[i] = current

        new_level = self._random_level()
        if new_level > self.level:
            for i in range(self.level + 1, new_level + 1):
                update[i] = self.header
            self.level = new_level

        new_node = SkipNode(value, new_level)
        for i in range(new_level + 1):
            new_node.forward[i] = update[i].forward[i]
            update[i].forward[i] = new_node

    def find_closest(self, target):
        current = self.header
        # Traverse from top level down to 0
        for i in range(self.level, -1, -1):
            while current.forward[i] and current.forward[i].value < target:
                current = current.forward[i]

        # Check the closest among current and the next node
        candidates = []
        if current.value is not None:
            candidates.append(current.value)
        if current.forward[0]:
            candidates.append(current.forward[0].value)

        if not candidates:
            return None

        return min(candidates, key=lambda x: abs(x - target))

# Testing
elements = [3, 6, 9, 12, 17, 21, 25]
skip_list = SkipList(3)
for element in elements:
    skip_list.insert(element)

target = 23
closest = skip_list.find_closest(target)
print(f"Closest to {target}: {closest}")
