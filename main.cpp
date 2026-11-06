#include <bits/stdc++.h>
using namespace std;

// ── provided ───────────────────────────────────────────────────────────
// sha1_hex(bytes): SHA-1 as 40 lowercase hex chars. The grader (and the
// local runner) compile this one file with no external libraries — there is
// no OpenSSL — so SHA-1 (RFC 3174) lives here. You never need to change it.
static string sha1_hex(const string& data) {
    auto rol = [](uint32_t x, int n) { return (x << n) | (x >> (32 - n)); };
    uint32_t h[5] = {0x67452301u, 0xEFCDAB89u, 0x98BADCFEu, 0x10325476u, 0xC3D2E1F0u};
    vector<unsigned char> msg(data.begin(), data.end());
    uint64_t bits = (uint64_t)data.size() * 8;
    msg.push_back(0x80);
    while (msg.size() % 64 != 56) msg.push_back(0);
    for (int i = 7; i >= 0; i--) msg.push_back((unsigned char)(bits >> (8 * i)));
    for (size_t off = 0; off < msg.size(); off += 64) {
        uint32_t w[80];
        for (int i = 0; i < 16; i++)
            w[i] = ((uint32_t)msg[off + 4 * i] << 24) | ((uint32_t)msg[off + 4 * i + 1] << 16) |
                   ((uint32_t)msg[off + 4 * i + 2] << 8) | (uint32_t)msg[off + 4 * i + 3];
        for (int i = 16; i < 80; i++) w[i] = rol(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
        uint32_t a = h[0], b = h[1], c = h[2], d = h[3], e = h[4];
        for (int i = 0; i < 80; i++) {
            uint32_t f, k;
            if (i < 20)      { f = (b & c) | (~b & d);           k = 0x5A827999u; }
            else if (i < 40) { f = b ^ c ^ d;                    k = 0x6ED9EBA1u; }
            else if (i < 60) { f = (b & c) | (b & d) | (c & d);  k = 0x8F1BBCDCu; }
            else             { f = b ^ c ^ d;                    k = 0xCA62C1D6u; }
            uint32_t t = rol(a, 5) + f + e + k + w[i];
            e = d; d = c; c = rol(b, 30); b = a; a = t;
        }
        h[0] += a; h[1] += b; h[2] += c; h[3] += d; h[4] += e;
    }
    char out[41];
    for (int i = 0; i < 5; i++) snprintf(out + 8 * i, 9, "%08x", h[i]);
    return string(out, 40);
}

// Each input line is one file's content. The "\n" that ends the line is NOT part of it.

string hash_blob(const string& content) {
    // TODO: build "blob <byte length>" followed by ONE zero byte, put the content after it,
    //       and return sha1_hex of that string. std::string can hold a zero byte safely.
    (void)content;
    return "";
}

int main() {
    string data((istreambuf_iterator<char>(cin)), istreambuf_iterator<char>());
    size_t start = 0;
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] == '\n') {
            cout << hash_blob(data.substr(start, i - start)) << "\n";
            start = i + 1;
        }
    }
    if (start < data.size()) cout << hash_blob(data.substr(start)) << "\n";
    return 0;
}
