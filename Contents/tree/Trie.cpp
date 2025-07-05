class TrieNode{
public:
    set<int> end ;
    TrieNode *next[26] ;

    TrieNode(){
        for ( int i=0 ; i<26 ; i++ ) next[i] = nullptr ;
    }
};

class Trie{
private:
    int cnt ;
    TrieNode *root ;
public:
    Trie() : cnt(0) {
        root = new TrieNode() ;
    }

    void insert(string &str, int n){
        TrieNode* node = root ;
        for ( auto s : str ){
            int path = s - 'a' ;

            if(node->next[path] == nullptr) node->next[path] = new TrieNode() ;
            node = node->next[path] ;
        }
        node->end.insert(n) ;
    }

    void search(string &str){
        TrieNode* node = root ;
        for ( auto s : str ){
            int path = s - 'a' ;
            if(node->next[path] == nullptr) return ;
            node = node->next[path] ;
        }

        int flg = 0 ;
        for ( auto n : node->end ){
            if(flg) cout << " " ;
            else flg = 1 ;

            cout << n ;
        }
    }

    void clear(TrieNode* node) {
        if (!node) return ;
        for (int i = 0; i < 26; i++) {
            if (node->next[i]) {
                clear(node->next[i]) ;
            }
        }
        delete node ;
    }

    ~Trie(){
        clear(root) ;
    }
};