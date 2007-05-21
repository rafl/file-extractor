package Module::Install::PRIVATE::File::Extractor;

use strict;
use warnings;
use Module::Install::Base;

use vars qw{$VERSION @ISA};
BEGIN {
    $VERSION = '0.01';
    @ISA     = qw{Module::Install::Base};
}

sub extractor {
    my ($self) = @_;

    $self->makemaker_args(INC     => '-Iperl_glue');
    $self->makemaker_args(LIBS    => '');
    $self->makemaker_args(CCFLAGS => '');

    $self->makemaker_args(OPTIMIZE => '-Wall -O0 -g');

    $self->xs_files;
}

sub xs_files {
    my ($self) = @_;

    my @clean;
    my @OBJECT;
    my %XS;

    for my $xs (<xs/*.xs>) {
        (my $c = $xs) =~ s/\.xs$/\.c/i;
        (my $o = $xs) =~ s/\.xs$/\$(OBJ_EXT)/i;

        $XS{$xs} = $c;
        push @OBJECT, $o;
        push @clean, $o;
    }

    for my $c (<perl_glue/*.c>) {
        (my $o = $c) =~ s/\.c$/\$(OBJ_EXT)/i;

        push @OBJECT, $o;
        push @clean, $o;
    }

    $self->makemaker_args( clean  => { FILES => join(q{ }, @clean) } );
    $self->makemaker_args( OBJECT => join(q{ }, @OBJECT)             );
    $self->makemaker_args( XS     => \%XS                            );
}

package MY;

use strict;
use warnings;
use Config;

sub const_cccmd {
    my $self = shift;

    my $inherited = $self->SUPER::const_cccmd(@_);
    return '' unless $inherited;

    if ($Config{cc} eq 'cl') {
        warn 'you are using MSVC... my condolences.';
        $inherited .= ' /Fo$@';
    }
    else {
        $inherited .= ' -o $@';
    }

    return $inherited;
}

1;
