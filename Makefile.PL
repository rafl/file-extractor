#!perl

use strict;
use warnings;
use lib 'ext';
use inc::Module::Install;

name 'File-Extractor';
all_from 'lib/File/Extractor.pm';

build_requires 'ExtUtils::PkgConfig' => 0;
build_requires 'Test::More' => 0;

extractor;

no_index directory => 'ext';

auto_install;
WriteAll;
