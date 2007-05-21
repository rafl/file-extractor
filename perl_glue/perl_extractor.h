#include <EXTERN.h>
#include <perl.h>
#include <XSUB.h>
#include <proto.h>

#include "ppport.h"

#define PERL_EXTRACTOR_CALL_BOOT(name) \
	{ \
		EXTERN_C XS(name); \
		_perl_extractor_call_xs (aTHX_ name, cv, mark); \
	}

void _perl_extractor_call_xs (pTHX_ void (*subaddr) (pTHX_ CV *cv), CV *cv, SV **mark);
