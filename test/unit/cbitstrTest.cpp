#include "bandit_base.h"
#include "cbitstr.h"

go_bandit([&]() {

#define BITSTR_64W "01010000" "00010001" "01000111" "11111111" "11100001" "00000000" "00000010" "00010001"
//                  32109876   54321098   76543210   98765432   10987654   32109876   54321098   76543210
//                     6            5            4               3            2            1            0
//                  byte 8     byte 7     byte 6     byte 5     byte 4     byte 3     byte 2     byte 1
    describe("bits_from_str", [&]() {
        it("checks byte1", []() {
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(0), "byte 1");
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(4), "byte 1");
        });
        it("checks byte2", []() {
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(9), "byte 2");
        });
        it("checks byte4", []() {
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(24), "byte 4");
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(29), "byte 4");
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(30), "byte 4");
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(31), "byte 4");
        });
        it("checks byte5", []() {
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(32), "byte 5");
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(33), "byte 5");
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(34), "byte 5");
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(35), "byte 5");
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(36), "byte 5");
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(37), "byte 5");
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(38), "byte 5");
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(39), "byte 5");
        });
        it("checks byte6", []() {
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(40), "byte 6");
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(41), "byte 6");
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(42), "byte 6");
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(46), "byte 6");
        });
        it("checks byte7", []() {
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(48), "byte 7");
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(52), "byte 7");
        });
        it("checks byte8", []() {
            static_assert(bits_from_str(cstr(BITSTR_64W)) & bit_at(60,62), "byte 8 of");
        });
    });

    describe("str_from_bits", [&]() {
        it("", [&]() {
            AssertThat(
                str_from_bits(bit_at(0,4,9,24,29,30,31,32,33,34,35,36,37,38,39,40,41,42,46,48,52,60,62)),
                Equals(std::string(BITSTR_64W))
            );
        });
    });
});
