import java.util.*;

public class T
{
    public static void main(String[] args)
    {
        Trie trie = new Trie();
//        System.out.println(trie.count(""));
//        System.out.println(trie.count("a"));

        String text = "it is not news that nathan milstein is a wizard of the violin . certainly not in orchestra hall where he has played countless recitals , and where thursday night he celebrated his 20th season with the chicago symphony orchestra , playing the brahms concerto with his own slashing , demon-ridden cadenza melting into the high , pale , pure and lovely song with which a violinist unlocks the heart of the music , or forever finds it closed . there was about that song something incandescent , for this brahms was milstein at white heat . not the noblest performance we have heard him play , or the most spacious , or even the most eloquent . those would be reserved for the orchestra's great nights when the soloist can surpass himself . this time the orchestra gave him some superb support fired by response to his own high mood . but he had in walter hendl a willing conductor able only up to a point . that is , when mr. milstein thrust straight to the core of the music , sparks flying , bow shredding , violin singing , glittering and sometimes spitting , mr. hendl could go along . but mr. hendl does not go straight to any point . he flounders and lets music sprawl .";
        String[] words = text.split(" ");

        for (String word : words)
            trie.insert(word);

        List<String> keys = trie.getKeys();

        for (String s : keys)
            System.out.println(s + "\t" + trie.count(s));
        System.out.println(keys.size());
    }

}
