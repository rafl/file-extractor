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
perl_extractor_keyword_list_to_sv (EXTRACTOR_KeywordList *list) {
	SV *ret;
	HV *hv;

	hv = newHV ();

	hv_store (hv, "type", 4, perl_extractor_keyword_type_to_sv (list->keywordType), 0);
	hv_store (hv, "keyword", 7, newSVpv (list->keyword, 0), 0);

	ret = newRV_noinc ((SV *)hv);
	return ret;
}

SV *
perl_extractor_keyword_type_to_sv (EXTRACTOR_KeywordType type) {
	SV *ret;

	switch (type) {
		case EXTRACTOR_UNKNOWN:
			ret = newSVpv ("unknown", 0);
			break;
		case EXTRACTOR_FILENAME:
			ret = newSVpv ("filename", 0);
			break;
		case EXTRACTOR_MIMETYPE:
			ret = newSVpv ("mimetype", 0);
			break;
		case EXTRACTOR_TITLE:
			ret = newSVpv ("title", 0);
			break;
		case EXTRACTOR_AUTHOR:
			ret = newSVpv ("author", 0);
			break;
		case EXTRACTOR_ARTIST:
			ret = newSVpv ("artist", 0);
			break;
		case EXTRACTOR_DESCRIPTION:
			ret = newSVpv ("description", 0);
			break;
		case EXTRACTOR_COMMENT:
			ret = newSVpv ("comment", 0);
			break;
		case EXTRACTOR_DATE:
			ret = newSVpv ("date", 0);
			break;
		case EXTRACTOR_PUBLISHER:
			ret = newSVpv ("publisher", 0);
			break;
		case EXTRACTOR_LANGUAGE:
			ret = newSVpv ("language", 0);
			break;
		case EXTRACTOR_ALBUM:
			ret = newSVpv ("album", 0);
			break;
		case EXTRACTOR_GENRE:
			ret = newSVpv ("genre", 0);
			break;
		case EXTRACTOR_LOCATION:
			ret = newSVpv ("location", 0);
			break;
		case EXTRACTOR_VERSIONNUMBER:
			ret = newSVpv ("versionnumber", 0);
			break;
		case EXTRACTOR_ORGANIZATION:
			ret = newSVpv ("organization", 0);
			break;
		case EXTRACTOR_COPYRIGHT:
			ret = newSVpv ("copyright", 0);
			break;
		case EXTRACTOR_SUBJECT:
			ret = newSVpv ("subject", 0);
			break;
		case EXTRACTOR_KEYWORDS:
			ret = newSVpv ("keywords", 0);
			break;
		case EXTRACTOR_CONTRIBUTOR:
			ret = newSVpv ("contributor", 0);
			break;
		case EXTRACTOR_RESOURCE_TYPE:
			ret = newSVpv ("type", 0);
			break;
		case EXTRACTOR_FORMAT:
			ret = newSVpv ("format", 0);
			break;
		case EXTRACTOR_RESOURCE_IDENTIFIER:
			ret = newSVpv ("resource-identifier", 0);
			break;
		case EXTRACTOR_SOURCE:
			ret = newSVpv ("source", 0);
			break;
		case EXTRACTOR_RELATION:
			ret = newSVpv ("relation", 0);
			break;
		case EXTRACTOR_COVERAGE:
			ret = newSVpv ("coverage", 0);
			break;
		case EXTRACTOR_SOFTWARE:
			ret = newSVpv ("software", 0);
			break;
		case EXTRACTOR_DISCLAIMER:
			ret = newSVpv ("disclaimer", 0);
			break;
		case EXTRACTOR_WARNING:
			ret = newSVpv ("warning", 0);
			break;
		case EXTRACTOR_TRANSLATED:
			ret = newSVpv ("translated", 0);
			break;
		case EXTRACTOR_CREATION_DATE:
			ret = newSVpv ("creation-date", 0);
			break;
		case EXTRACTOR_MODIFICATION_DATE:
			ret = newSVpv ("modification-date", 0);
			break;
		case EXTRACTOR_CREATOR:
			ret = newSVpv ("creator", 0);
			break;
		case EXTRACTOR_PRODUCER:
			ret = newSVpv ("producer", 0);
			break;
		case EXTRACTOR_PAGE_COUNT:
			ret = newSVpv ("page-count", 0);
			break;
		case EXTRACTOR_PAGE_ORIENTATION:
			ret = newSVpv ("page-orientation", 0);
			break;
		case EXTRACTOR_PAPER_SIZE:
			ret = newSVpv ("paper-size", 0);
			break;
		case EXTRACTOR_USED_FONTS:
			ret = newSVpv ("used-fonts", 0);
			break;
		case EXTRACTOR_PAGE_ORDER:
			ret = newSVpv ("page-order", 0);
			break;
		case EXTRACTOR_CREATED_FOR:
			ret = newSVpv ("created-for", 0);
			break;
		case EXTRACTOR_MAGNIFICATION:
			ret = newSVpv ("magnification", 0);
			break;
		case EXTRACTOR_RELEASE:
			ret = newSVpv ("release", 0);
			break;
		case EXTRACTOR_GROUP:
			ret = newSVpv ("group", 0);
			break;
		case EXTRACTOR_SIZE:
			ret = newSVpv ("size", 0);
			break;
		case EXTRACTOR_SUMMARY:
			ret = newSVpv ("summary", 0);
			break;
		case EXTRACTOR_PACKAGER:
			ret = newSVpv ("packager", 0);
			break;
		case EXTRACTOR_VENDOR:
			ret = newSVpv ("vendor", 0);
			break;
		case EXTRACTOR_LICENSE:
			ret = newSVpv ("license", 0);
			break;
		case EXTRACTOR_DISTRIBUTION:
			ret = newSVpv ("distribution", 0);
			break;
		case EXTRACTOR_BUILDHOST:
			ret = newSVpv ("buildhost", 0);
			break;
		case EXTRACTOR_OS:
			ret = newSVpv ("os", 0);
			break;
		case EXTRACTOR_DEPENDENCY:
			ret = newSVpv ("dependency", 0);
			break;
		case EXTRACTOR_HASH_MD4:
			ret = newSVpv ("hash-md4", 0);
			break;
		case EXTRACTOR_HASH_MD5:
			ret = newSVpv ("hash-md5", 0);
			break;
		case EXTRACTOR_HASH_SHA0:
			ret = newSVpv ("hash-sha0", 0);
			break;
		case EXTRACTOR_HASH_SHA1:
			ret = newSVpv ("hash-sha1", 0);
			break;
		case EXTRACTOR_HASH_RMD160:
			ret = newSVpv ("hash-rmd160", 0);
			break;
		case EXTRACTOR_RESOLUTION:
			ret = newSVpv ("resolution", 0);
			break;
		case EXTRACTOR_CATEGORY:
			ret = newSVpv ("category", 0);
			break;
		case EXTRACTOR_BOOKTITLE:
			ret = newSVpv ("booktitle", 0);
			break;
		case EXTRACTOR_PRIORITY:
			ret = newSVpv ("priority", 0);
			break;
		case EXTRACTOR_CONFLICTS:
			ret = newSVpv ("conflicts", 0);
			break;
		case EXTRACTOR_REPLACES:
			ret = newSVpv ("replaces", 0);
			break;
		case EXTRACTOR_PROVIDES:
			ret = newSVpv ("provides", 0);
			break;
		case EXTRACTOR_CONDUCTOR:
			ret = newSVpv ("conductor", 0);
			break;
		case EXTRACTOR_INTERPRET:
			ret = newSVpv ("interpret", 0);
			break;
		case EXTRACTOR_OWNER:
			ret = newSVpv ("owner", 0);
			break;
		case EXTRACTOR_LYRICS:
			ret = newSVpv ("lyrics", 0);
			break;
		case EXTRACTOR_MEDIA_TYPE:
			ret = newSVpv ("media-type", 0);
			break;
		case EXTRACTOR_CONTACT:
			ret = newSVpv ("contact", 0);
			break;
		case EXTRACTOR_THUMBNAIL_DATA:
			ret = newSVpv ("thumbnail-data", 0);
			break;
		case EXTRACTOR_PUBLICATION_DATE:
			ret = newSVpv ("publication-date", 0);
			break;
		case EXTRACTOR_CAMERA_MAKE:
			ret = newSVpv ("camera-make", 0);
			break;
		case EXTRACTOR_CAMERA_MODEL:
			ret = newSVpv ("camera-model", 0);
			break;
		case EXTRACTOR_EXPOSURE:
			ret = newSVpv ("exposure", 0);
			break;
		case EXTRACTOR_APERTURE:
			ret = newSVpv ("aperture", 0);
			break;
		case EXTRACTOR_EXPOSURE_BIAS:
			ret = newSVpv ("exposure-bias", 0);
			break;
		case EXTRACTOR_FLASH:
			ret = newSVpv ("flash", 0);
			break;
		case EXTRACTOR_FLASH_BIAS:
			ret = newSVpv ("flash-bias", 0);
			break;
		case EXTRACTOR_FOCAL_LENGTH:
			ret = newSVpv ("focal-length", 0);
			break;
		case EXTRACTOR_FOCAL_LENGTH_35MM:
			ret = newSVpv ("focal-length-35mm", 0);
			break;
		case EXTRACTOR_ISO_SPEED:
			ret = newSVpv ("iso-speed", 0);
			break;
		case EXTRACTOR_EXPOSURE_MODE:
			ret = newSVpv ("exposure-mode", 0);
			break;
		case EXTRACTOR_METERING_MODE:
			ret = newSVpv ("metering-mode", 0);
			break;
		case EXTRACTOR_MACRO_MODE:
			ret = newSVpv ("macro-mode", 0);
			break;
		case EXTRACTOR_IMAGE_QUALITY:
			ret = newSVpv ("image-quality", 0);
			break;
		case EXTRACTOR_WHITE_BALANCE:
			ret = newSVpv ("white-balance", 0);
			break;
		case EXTRACTOR_ORIENTATION:
			ret = newSVpv ("orientation", 0);
			break;
		case EXTRACTOR_TEMPLATE:
			ret = newSVpv ("template", 0);
			break;
		case EXTRACTOR_SPLIT:
			ret = newSVpv ("split", 0);
			break;
		case EXTRACTOR_PRODUCTVERSION:
			ret = newSVpv ("productversion", 0);
			break;
		case EXTRACTOR_LAST_SAVED_BY:
			ret = newSVpv ("last-saved-by", 0);
			break;
		case EXTRACTOR_LAST_PRINTED:
			ret = newSVpv ("last-printed", 0);
			break;
		case EXTRACTOR_WORD_COUNT:
			ret = newSVpv ("word-count", 0);
			break;
		case EXTRACTOR_CHARACTER_COUNT:
			ret = newSVpv ("character-count", 0);
			break;
		case EXTRACTOR_TOTAL_EDITING_TIME:
			ret = newSVpv ("total-editing-time", 0);
			break;
		case EXTRACTOR_THUMBNAILS:
			ret = newSVpv ("thumbnails", 0);
			break;
		case EXTRACTOR_SECURITY:
			ret = newSVpv ("security", 0);
			break;
		case EXTRACTOR_CREATED_BY_SOFTWARE:
			ret = newSVpv ("created-by-software", 0);
			break;
		case EXTRACTOR_MODIFIED_BY_SOFTWARE:
			ret = newSVpv ("modified-by-software", 0);
			break;
		case EXTRACTOR_REVISION_HISTORY:
			ret = newSVpv ("revision-history", 0);
			break;
		case EXTRACTOR_LOWERCASE:
			ret = newSVpv ("lowercase", 0);
			break;
		case EXTRACTOR_COMPANY:
			ret = newSVpv ("company", 0);
			break;
		case EXTRACTOR_GENERATOR:
			ret = newSVpv ("generator", 0);
			break;
		case EXTRACTOR_CHARACTER_SET:
			ret = newSVpv ("character-set", 0);
			break;
		case EXTRACTOR_LINE_COUNT:
			ret = newSVpv ("line-count", 0);
			break;
		case EXTRACTOR_PARAGRAPH_COUNT:
			ret = newSVpv ("paragraph-count", 0);
			break;
		case EXTRACTOR_EDITING_CYCLES:
			ret = newSVpv ("editing-cycles", 0);
			break;
		case EXTRACTOR_SCALE:
			ret = newSVpv ("scale", 0);
			break;
		case EXTRACTOR_MANAGER:
			ret = newSVpv ("manager", 0);
			break;
		case EXTRACTOR_MOVIE_DIRECTOR:
			ret = newSVpv ("movie-director", 0);
			break;
		case EXTRACTOR_DURATION:
			ret = newSVpv ("duration", 0);
			break;
		case EXTRACTOR_INFORMATION:
			ret = newSVpv ("information", 0);
			break;
		case EXTRACTOR_FULL_NAME:
			ret = newSVpv ("full-name", 0);
			break;
		case EXTRACTOR_CHAPTER:
			ret = newSVpv ("chapter", 0);
			break;
		case EXTRACTOR_YEAR:
			ret = newSVpv ("year", 0);
			break;
		case EXTRACTOR_LINK:
			ret = newSVpv ("link", 0);
			break;
		case EXTRACTOR_MUSIC_CD_IDENTIFIER:
			ret = newSVpv ("music-cd-identifier", 0);
			break;
		case EXTRACTOR_PLAY_COUNTER:
			ret = newSVpv ("play-counter", 0);
			break;
		case EXTRACTOR_POPULARITY_METER:
			ret = newSVpv ("popularity-meter", 0);
			break;
		case EXTRACTOR_CONTENT_TYPE:
			ret = newSVpv ("content-type", 0);
			break;
		case EXTRACTOR_ENCODED_BY:
			ret = newSVpv ("encoded-by", 0);
			break;
		case EXTRACTOR_TIME:
			ret = newSVpv ("time", 0);
			break;
		case EXTRACTOR_MUSICIAN_CREDITS_LIST:
			ret = newSVpv ("musician-credits-list", 0);
			break;
		case EXTRACTOR_MOOD:
			ret = newSVpv ("mood", 0);
			break;
		case EXTRACTOR_FORMAT_VERSION:
			ret = newSVpv ("format-version", 0);
			break;
		case EXTRACTOR_TELEVISION_SYSTEM:
			ret = newSVpv ("television-system", 0);
			break;
		case EXTRACTOR_SONG_COUNT:
			ret = newSVpv ("song-count", 0);
			break;
		case EXTRACTOR_STARTING_SONG:
			ret = newSVpv ("starting-song", 0);
			break;
		case EXTRACTOR_HARDWARE_DEPENDENCY:
			ret = newSVpv ("hardware-dependency", 0);
			break;
		case EXTRACTOR_RIPPER:
			ret = newSVpv ("ripper", 0);
			break;
		case EXTRACTOR_FILE_SIZE:
			ret = newSVpv ("file-size", 0);
			break;
		default:
			croak ("unknown keyword type");
	}

	return ret;
}
