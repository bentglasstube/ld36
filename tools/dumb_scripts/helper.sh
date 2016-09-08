#!/bin/bash
#######################################################################
#
# This dumb script helps create the BUILD files and wrapper scripts
# to make mingw-on-linux for 32-bit and 64-bit toolchains.
#
# This script is awful and will overwrite files without asking.  Make
# sure you understand it before running it.
#
# From the project root:
#
# ./tools/dumb_scripts/helper.sh \
#     mxe-i686-w64-mingw32.shared-binutils_2.25.1.tar.xz \
#     mingw_compiler_win32 win32
#
# ./tools/dumb_scripts/helper.sh \
#     mxe-x86_64-w64-mingw32.shared-binutils_2.25.1.tar.xz \
#     mingw_compiler_win64 win64
#
# After it's done, you'll still need to do a bunch of manual
# cleanup to the generated BUILD files.
#
# Good Luck.
#
#######################################################################

ARCHIVE=$1
NAME=$2
SHORTNAME=$3

BINARIES=$(tar Jtvvf $ARCHIVE | awk '/usr\/bin/ {print $6}')
BUILD="${NAME}.BUILD"
TOOLS=tools/windows/$SHORTNAME

mkdir -p $TOOLS
#echo "package(default_visibility = ['//visibility:public'])" > $BUILD

for bin in $BINARIES
do
    name=${bin##*-}
    base=${bin##*/}
    PIECES="${PIECES}${name} "


#    cat >> $BUILD <<EOT
#filegroup(
#    name = '${name}',
#    srcs = ['${bin}'],
#)
#
#EOT
    cat >> $TOOLS/BUILD <<EOT
filegroup(
  name = '${name}',
  srcs = [
    '@mingw_compiler//:${name}',
    '${base}',
  ],
)

EOT

    cat > ${TOOLS}/${base} <<EOT
#!/bin/bash --norc

exec -a ${base} \\
    external/${NAME}/usr/bin/${base} \\
    "\$@"
EOT
    chmod +x ${TOOLS}/${base}
done

#cat >> $BUILD <<EOT
#filegroup(
#    name = 'compiler_components',
#    srcs = [
#EOT
#
#for p in $PIECES
#do
#    echo "        ':${p}'," >> $BUILD
#done
#cat >> $BUILD <<EOT
#    ],
#)
#EOT
