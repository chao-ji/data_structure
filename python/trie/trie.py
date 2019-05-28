
class Node(object):
  def __init__(self, size):
    self.children = [None for _ in range(size)]
    self.count = 0

class Trie(object):
  def __init__(self, size=128):
    self.root = Node(size)
    self.size = size

  def insert(self, key, val=None):
    node = self.root

    for c in key:
      if node.children[ord(c)] is None:
        node.children[ord(c)] = Node(self.size)
      node = node.children[ord(c)]
 
    node.count += 1

  def count(self, key):
    node = self.root

    for c in key:
      if node.children[ord(c)] is None:
        return 0
      else:
        node = node.children[ord(c)]

    return node.count

  def containsKey(self, key):
    return self.count(key) > 0


  def has_prefix(self, key):
    keys = []
    node = self.root

    for c in key:
      if node.children[ord(c)] is None:
        return keys
      else:
        node = node.children[ord(c)]

    queue = [(node, key)]
   
    while queue:
      node, pref = queue.pop(0)

      if node.count != 0:
        keys.append(pref)

      for i in range(len(node.children)):
        if node.children[i] is not None:
          queue.append((node.children[i], pref + chr(i)))
          
    return keys

  def get_keys(self):
   return self.has_prefix('')


if __name__ == '__main__':
  text = "it is not news that nathan milstein is a wizard of the violin . certainly not in orchestra hall where he has played countless recitals , and where thursday night he celebrated his 20th season with the chicago symphony orchestra , playing the brahms concerto with his own slashing , demon-ridden cadenza melting into the high , pale , pure and lovely song with which a violinist unlocks the heart of the music , or forever finds it closed . there was about that song something incandescent , for this brahms was milstein at white heat . not the noblest performance we have heard him play , or the most spacious , or even the most eloquent . those would be reserved for the orchestra's great nights when the soloist can surpass himself . this time the orchestra gave him some superb support fired by response to his own high mood . but he had in walter hendl a willing conductor able only up to a point . that is , when mr. milstein thrust straight to the core of the music , sparks flying , bow shredding , violin singing , glittering and sometimes spitting , mr. hendl could go along . but mr. hendl does not go straight to any point . he flounders and lets music sprawl ."

  trie = Trie()
  for word in text.split(' '):
    trie.insert(word)



