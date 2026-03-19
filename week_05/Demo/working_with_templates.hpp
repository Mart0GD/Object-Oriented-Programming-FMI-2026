#pragma once

template<typename T1, typename T2>
inline void add(T1& a, const T2& b) { a += b;}

template<typename T>
inline void pow2(T& a) { a *= a; }

template<typename T = int, int num = 10>
inline void add_to_number(T& number) { number += num; }

template<typename T, void (*f_ptr)(T&)>
inline void apply_on_array(T* arr, int n) { for (int i = 0; i < n; i++) f_ptr(arr[i]); }