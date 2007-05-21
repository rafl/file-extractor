#include "perl_extractor.h"

MODULE = File::Extractor	PACKAGE = File::Extractor	PREFIX = EXTRACTOR_

PROTOTYPES: DISABLE

void
EXTRACTOR_getDefaultLibraries (class)
	PREINIT:
		const char *libraries;
		char *copy, *pos, *token;
	PPCODE:
		libraries = EXTRACTOR_getDefaultLibraries ();

		if (!libraries) {
			XSRETURN_EMPTY;
		}

		copy = strdup (libraries);
		pos = copy;

		while ((token = strsep (&pos, ":"))) {
			mXPUSHp (token, strlen (token));
		}

		free (copy);

EXTRACTOR_ExtractorList *
EXTRACTOR_loadDefaultLibraries (class)
	C_ARGS:
		/* void */

void
EXTRACTOR_getKeywords (EXTRACTOR_ExtractorList *extractor, const char *filename)
	PREINIT:
		EXTRACTOR_KeywordList *list, *i;
	PPCODE:
		list = EXTRACTOR_getKeywords (extractor, filename);

		if (!list) {
			XSRETURN_EMPTY;
		}

		for (i = list; i; i = i->next) {
			XPUSHs (perl_extractor_keyword_list_to_sv (i));
		}
