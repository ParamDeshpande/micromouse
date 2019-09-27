#ifndef SEN_FUSION_H
#define SEN_FUSION_H

#include <stddef.h>
#include <stdlib.h>
#include "../include/rtwtypes.h"
#include "../include/kalman6d_types.h"

#include "../include/kalman6d.h"
#include "../include/kalman6d_terminate.h"
#include "../include/kalman6d_initialize.h"


void init_STATES(void);
void kalman_Magic(void);
void display_states(void);

#endif // !SEN_FUSION_H#define SEN_FUSION_H

