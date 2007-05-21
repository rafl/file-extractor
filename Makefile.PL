#!perl

use strict;
use warnings;
use lib 'ext';
use inc::Module::Install;

name 'File-Extractor';
all_from 'lib/File/Extractor.pm';

extractor;

no_index directory => 'ext';

auto_install;
WriteAll;
