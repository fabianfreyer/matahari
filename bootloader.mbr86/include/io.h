#pragma once
#include <code16.h>

/**
 * \fn          void puts(const char *s)
 * \param s     NULL-terminated string to be putsed
 * \brief       prints a string to the screen 
 */
void __attribute__((noinline)) __attribute__((regparm(3))) puts(const char *s);

/**
 * \fn          void putc(const char c);
 * \param c     character to be putsed.
 * \brief       putss a character to the screen 
 */
void __attribute__((noinline)) putc(const char c);
/**
 * \fn          char getc()
 * \brief       gets a keypress
 * \note        non-blocking
 * \return      character pressed
 */
char __attribute__((noinline)) getc();
