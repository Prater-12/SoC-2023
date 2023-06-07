#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock

const int ALPHABET_SIZE = 26;

class Node
{
    Node *children[ALPHABET_SIZE];
    bool end;

    static int getIndex(char c)
    {
        return tolower(c) - 'a';
    }

public:
    Node()
    {
        end = false;

        for (int i = 0; i < ALPHABET_SIZE; i++)
            children[i] = nullptr;
    };

    void insert(std::string key)
    {
        Node *temp = this;

        for (int i = 0; i < key.length(); ++i)
        {
            int index = Node::getIndex(key[i]);
            if (temp->children[index] == nullptr)
                temp->children[index] = new Node();

            temp = temp->children[index];
        }

        temp->end = true;
    }

    bool search(std::string key)
    {
        Node *temp = this;

        for (int i = 0; i < key.length(); i++)
        {
            int index = Node::getIndex(key[i]);
            if (temp->children[index] == nullptr)
                return false;

            temp = temp->children[index];
        }

        return temp->end;
    }
};

int main()
{
    std::vector<std::string> allWords = {"It", "is", "a", "period", "of", "civil", "war", "Rebel", "spaceships", "striking", "from", "a", "hidden", "base", "have", "won", "their", "first", "victory", "against", "the", "evil", "Galactic", "Empire", "During", "the", "battle", "Rebel", "spies", "managed", "to", "steal", "secret", "plans", "to", "the", "Empire", "ultimate", "weapon", "the", "DEATH", "STAR", "an", "armored", "space", "station", "with", "enough", "power", "to", "destroy", "an", "entire", "planet", "Pursued", "by", "the", "Empire", "sinister", "agents", "Princess", "Leia", "races", "home", "aboard", "her", "starship", "custodian", "of", "the", "stolen", "plans", "that", "can", "save", "her", "people", "and", "restore", "freedom", "to", "the", "galaxy"};

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(allWords.begin(), allWords.end(), std::default_random_engine(seed));

    Node *root = new Node;

    for (int i = 0; i < 10; ++i)
        root->insert(allWords[i]);

    for (int i = 7; i < 13; ++i)
    {
        std::cout << allWords[i] << " --- " << (root->search(allWords[i]) ? "Present" : "Not present") << std::endl;
    }
}
