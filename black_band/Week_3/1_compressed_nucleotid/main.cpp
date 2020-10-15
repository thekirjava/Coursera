#include <iostream>
#include <cstddef>
#include "test_runner.h"


struct Nucleotide {
    char Symbol;
    size_t Position;
    int ChromosomeNum;
    int GeneNum;
    bool IsMarked;
    char ServiceInfo;
};

const std::array<char, 4> symbols = {'A', 'T', 'G', 'C'};
struct CompactNucleotide {
    uint64_t Symbol:2;
    uint64_t Position:32;
    uint64_t ChromosomeNum:6;
    uint64_t GeneNum:15;
    uint64_t IsMarked:1;
    uint64_t ServiceInfo:8;
};

bool operator == (const Nucleotide& lhs, const Nucleotide& rhs) {
    return (lhs.Symbol == rhs.Symbol)
           && (lhs.Position == rhs.Position)
           && (lhs.ChromosomeNum == rhs.ChromosomeNum)
           && (lhs.GeneNum == rhs.GeneNum)
           && (lhs.IsMarked == rhs.IsMarked)
           && (lhs.ServiceInfo == rhs.ServiceInfo);
}


CompactNucleotide Compress(const Nucleotide& n) {
    int pos = 0;
    switch (n.Symbol) {
        case 'A':
            pos = 0;
            break;;
        case 'T':
            pos = 1;
            break;
        case 'G':
            pos = 2;
            break;
        case 'C':
            pos = 3;
            break;
    }
    return {static_cast<uint64_t>(pos), n.Position, static_cast<uint64_t>(n.ChromosomeNum), static_cast<uint64_t>(n.GeneNum), n.IsMarked, static_cast<uint64_t>(n.ServiceInfo)};
};


Nucleotide Decompress(const CompactNucleotide& cn) {
    return {symbols[cn.Symbol], cn.Position, cn.ChromosomeNum, cn.GeneNum, static_cast<bool>(cn.IsMarked), static_cast<char>(cn.ServiceInfo)};
}

void TestSize() {
    ASSERT(sizeof(CompactNucleotide) <= 8);
}

void TestCompressDecompress() {
    Nucleotide source;

    source.Symbol = 'T';
    source.Position = 1'000'000'000;
    source.ChromosomeNum = 48;
    source.GeneNum = 1'000;
    source.IsMarked = true;
    source.ServiceInfo = 'Test';

    CompactNucleotide compressedSource = Compress(source);
    Nucleotide decompressedSource = Decompress(compressedSource);

    ASSERT(source == decompressedSource);
}

int main() {
    TestRunner tr;

    RUN_TEST(tr, TestSize);
    RUN_TEST(tr, TestCompressDecompress);

    return 0;
}