#ifndef __PERL_EXTRACTOR_H__
#define __PERL_EXTRACTOR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <EXTERN.h>
#include <perl.h>
#include <XSUB.h>
#include <proto.h>

#include "ppport.h"

#include <string.h>
#include <extractor.h>

#define PERL_EXTRACTOR_CALL_BOOT(name) \
	{ \
		EXTERN_C XS(name); \
		_perl_extractor_call_xs (aTHX_ name, cv, mark); \
	}

#define EXTRACTOR_ExtractorList_or_null EXTRACTOR_ExtractorList

void _perl_extractor_call_xs (pTHX_ void (*subaddr) (pTHX_ CV *cv), CV *cv, SV **mark);

SV *perl_extractor_new_sv_from_ptr (void *ptr, const char *class);

void *perl_extractor_get_ptr_from_sv (SV *sv, const char *class);

SV *perl_extractor_keyword_list_to_sv (EXTRACTOR_KeywordList *list);

SV *perl_extractor_keyword_type_to_sv (EXTRACTOR_KeywordType type);

char *perl_extractor_slurp_from_handle (SV *handle, STRLEN *len);

#ifdef __cplusplus
}
#endif

#endif
