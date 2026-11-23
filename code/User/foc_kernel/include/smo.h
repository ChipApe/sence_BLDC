#include "lks32mc03x_lib.h"
#include "config.h"
#include "mc_type.h"
#include "string.h"

typedef struct
{
    stru_CurrAlphBeta Ialfa_beta;
    stru_VoltAlphBeta Valfa_beta;
} stru_SMO_InputsDef;

void SMO_clear(stru_SMODef *this);
int16_t SMO_CalcElAngle(stru_SMODef *this, stru_CurrAlphBeta Ialfa_beta, stru_VoltAlphBeta Valfa_beta);
s16 HL_PI_AntiDump(s32 InputError, stru_PIparams *pParams);
void SMO_init(stru_SMODef *this);
