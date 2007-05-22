#include "perl_extractor.h"

void
_perl_extractor_call_xs (pTHX_ void (*subaddr) (pTHX_ CV *), CV *cv, SV **mark) {
	dSP;
	PUSHMARK (mark);
	(*subaddr) (aTHX_ cv);
	PUTBACK;
}

SV *
perl_extractor_new_sv_from_ptr (void *ptr, const char *class) {
	SV *obj, *sv;
	HV *stash;

	obj = (SV *)newHV ();
	sv_magic (obj, 0, PERL_MAGIC_ext, (const char *)ptr, 0);

	sv = newRV_noinc (obj);
	stash = gv_stashpv (class, 0);
	sv_bless (sv, stash);

	return sv;
}

void *
perl_extractor_get_ptr_from_sv (SV *sv, const char *class) {
	MAGIC *mg;

	if (!sv || !SvOK (sv) || !SvROK (sv)
	 || (class && !sv_derived_from (sv, class))
	 || !(mg = mg_find (SvRV (sv), PERL_MAGIC_ext))) {
		croak ("invalid object");
	}

	return (void *)mg->mg_ptr;
}

SV *
perl_extractor_keyword_type_to_sv (EXTRACTOR_KeywordType type) {
	SV *ret;

	ret = newSVpv (EXTRACTOR_getKeywordTypeAsString (type), 0);

	return ret;
}

char *
perl_extractor_slurp_from_handle (SV *handle, STRLEN *len) {
	char *ret;
	SV *sv;
	PerlIO *io;
	int got;
	char buf[4096];

	io = IoIFP (sv_2io (handle));
	sv = sv_2mortal (newSV (0));

	while ((got = PerlIO_read (io, &buf, sizeof (buf))) > 0) {
		sv_catpvn (sv, (const char *)&buf, got);
	}

	ret = SvPV (sv, *len);

	return ret;
}
