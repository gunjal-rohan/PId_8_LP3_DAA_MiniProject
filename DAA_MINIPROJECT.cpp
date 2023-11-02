#include <bits/stdc++.h>
using namespace std;

#define d 256 // A prime number

void NaiveSearch(const string& pattern, const string& text, vector<int>& matches) {
    int M = pattern.length();
    int N = text.length();

    for (int i = 0; i <= N - M; i++) {
        int j = 0;

        while (j < M && tolower(text[i + j]) == tolower(pattern[j])) {
            j++;
        }

        if (j == M) {
            matches.push_back(i);
        }
    }
}

void RabinKarp(const string& pattern, const string& text, int q, vector<int>& matches) {
    int m = pattern.length();
    int n = text.length();
    int p = 0; // Hash value for pattern
    int t = 0; // Hash value for text
    int h = 1;

    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (int i = 0; i < m; i++) {
        p = (d * p + tolower(pattern[i])) % q;
        t = (d * t + tolower(text[i])) % q;
    }

    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            int j = 0;
            while (j < m && tolower(text[i + j]) == tolower(pattern[j])) {
                j++;
            }

            if (j == m) {
                matches.push_back(i);
            }
        }

        if (i < n - m) {
            t = (d * (t - tolower(text[i]) * h) + tolower(text[i + m])) % q;
            if (t < 0) {
                t = (t + q);
            }
        }
    }
}

int main() {
    string text = "THIS IS A TEST TEXT";
    string pattern = "test";
    int q = 101; // A prime number for Rabin-Karp algorithm

    vector<int> matches;
    int choice;

    do {
        cout << "\n1) Enter text and pattern.";
        cout << "\n2) Naive string matching.";
        cout << "\n3) Rabin-Karp String matching.";
        cout << "\n4) Exit.";
        cout << "\n\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter text: ";
                cin.ignore();
                getline(cin, text);
                cout << "Enter pattern: ";
                cin >> pattern;
                break;
            case 2:
                matches.clear();
                NaiveSearch(pattern, text, matches);
                if (matches.empty()) {
                    cout << "Pattern not found." << endl;
                } else {
                    cout << "Pattern found at the following indices: ";
                    for (int index : matches) {
                        cout << index << " ";
                    }
                    cout << endl;
                }
                break;
            case 3:
                matches.clear();
                RabinKarp(pattern, text, q, matches);
                if (matches.empty()) {
                    cout << "Pattern not found." << endl;
                } else {
                    cout << "Pattern found at the following indices: ";
                    for (int index : matches) {
                        cout << index << " ";
                    }
                    cout << endl;
                }
                break;
            case 4:
                cout << "\nExiting...";
                break;
            default:
                cout << "\nEnter a valid choice!";
                break;
        }
    } while (choice != 4);

    return 0;
}
