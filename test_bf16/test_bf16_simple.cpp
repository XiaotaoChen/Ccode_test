#include <x86intrin.h>
#include <stdio.h>

__m256i cvt_f32_b16(__m512i x)
{
  x = _mm512_bsrli_epi128(x, 2);
  return _mm512_cvtepi32_epi16(x);
}

__m512i cvt_b16_f32(__m256i x)
{
  __m512i y = _mm512_cvtepu16_epi32(x);
  return _mm512_bslli_epi128(y, 2);
}

int main() {

  alignas(64) unsigned int a0[16] = { 0x7aaa7bbb, 0x8aaabbbb, 0xaaaabbbb, 0xaaaabbbb,
    0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb,
    0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb, 0xaaaabbbb };
  alignas(64) short a1[16];
  alignas(64) int a2[16];

  __m512i f32 = *(__m512i *)a0;
  __m256i b16 = cvt_f32_b16(f32);
  *(__m256i *)a1 = b16;

  __m512i f32_new = cvt_b16_f32(b16);
  *(__m512i *)a2 = f32_new;

  for (auto i = 0; i < 16; i++) {
    printf("a1[%d]=%x\n", i, a0[i]);
    printf("a2[%d]=%x\n", i, a2[i]);
  }

  return 0;
}

