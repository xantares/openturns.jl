# ArchLinux image with Julia dependencies

FROM openturns/archlinux-base
MAINTAINER jschueller

# Install packages from AUR
RUN aurman -Syu --noconfirm --noedit --pgp_fetch libcxxwrap-julia
RUN julia -e 'import Pkg; Pkg.add("CxxWrap")'
