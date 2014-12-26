#pragma once
#include <code16.h>

/**
 * \fn          void puts16(const char *s)
 * \param s     NULL-terminated string to be putsed
 * \brief       prints a string to the screen 
 */
void __attribute__((noinline)) __attribute__((regparm(3))) puts16(const char *s);

/**
 * \fn          void putc16(const char c);
 * \param c     character to be putsed.
 * \brief       putss a character to the screen 
 */
void __attribute__((noinline)) putc16(const char c);
/**
 * \fn          char getc16()
 * \brief       gets a keypress
 * \note        non-blocking
 * \return      character pressed
 */
char __attribute__((noinline)) getc16();
