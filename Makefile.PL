use strict;
use warnings;
use ExtUtils::MakeMaker;

WriteMakefile(
    NAME                => 'File::Extractor',
    AUTHOR              => 'Florian Ragwitz <rafl@debian.org>',
    VERSION_FROM        => 'lib/File/Extractor.pm',
    ABSTRACT_FROM       => 'lib/File/Extractor.pm',
    PL_FILES            => {},
    PREREQ_PM => {
        'Test::More' => 0,
    },
    dist                => { COMPRESS => 'gzip -9f', SUFFIX => 'gz', },
    clean               => { FILES => 'File-Extractor-*' },
);
