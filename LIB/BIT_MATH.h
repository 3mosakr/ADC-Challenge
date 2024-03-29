#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define REGISTER_SIZE 8

#define SET_BIT(REG, BIT_POSN) ((REG) |= (1 << BIT_POSN))
#define CLR_BIT(REG, BIT_POSN) ((REG) &= ~(1 << BIT_POSN))
#define GET_BIT(REG, BIT_POSN) ((REG >> BIT_POSN) & 1)
#define TOG_BIT(REG, BIT_POSN) ((REG) ^= (1 << BIT_POSN))

#define ROR_BIT(REG, NUM) ((REG >> NUM) | (REG << (REGISTER_SIZE - NUM)))
#define ROL_BIT(REG, NUM) ((REG << NUM) | (REG >> (REGISTER_SIZE - NUM)))

#endif // BIT_MATH_H_