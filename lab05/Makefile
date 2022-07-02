###########################################################################
##                  Makefile for Lab 5 (Professor Evil)                  ##
###########################################################################

#
# The "make" Unix program is a powerful tool that is used to build
# software.  It can be used for lots of other things, too, but building
# programs was the main problem it was designed to solve.
# It automates the compilation and linking commands you would have to type
# by hand, which is a big help with a large program with many components!
#
# To use make, you will usually write a Makefile, like this one.  It
# contains 2 kinds of things:  variable definitions and rules.
#
# We'll first define some variables.  You can define any variables you
# like, but there are some variables that have conventional meanings.
#
# CXX is conventionally used for the C++ compiler you want to use.  
# We use clang++ in CS 15, because it tends to have better error
# messages than the alternative (g++).  In case you're wondering,
# CPP wasn't used for C++, because it was already in use for something 
# else by the time C++ was invented (make predates C++ itself).
#
# CXXFLAGS is conventionally used for the parameters (flags) you want 
# to use whenever you compile a C++ program.  In this case, we're
# telling the compiler to leave all the debugging information it can
# in the resulting file (g3), to give us all the standard warnings
# (Wall), and to give us even MORE warnings (Wextra).  We're also
# specifying the C++ standard we'd like to use.
#
# LDFLAGS is conventionally used for the parameters (flags) you want
# to use when you link a bunch of program components together to make
# an executable program.  In this case, we're asking for all the
# debugging information again.
#
CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++14
LDFLAGS  = -g3

# To use a variable, you write something like this:  ${CXX}
# It's an awkward notation, but you have to put either braces or
# parentheses around any variable that has more than one character in
# its name, which is practically all of them.  It's not wrong even for
# 1-letter variables, so just always put the braces.
# make will take any variable reference, like ${CXX} in the rules
# below and replace it with the text to the right of the equals sign
# in the variable definition.  So, ${CXX} will turn into clang++
# below. 

#
# Here are the rules!  Each rule has a "target" followed by a colon.
# After the colon, is a list of "dependencies" (also called
# "prerequisites") all on one line.  These are files that must already
# exist and be up-to-date before you can make the target.  So, the
# first rule below says that you'd like to define how to make a thing
# called "evil", and to make an "evil" you need a number of .o files.
# The target and dependencies must be all on one line (though there is
# a trick --- you can put a back slash before a newline to tell make
# to treat the line as continued on the next line in your file).
#
# The target/prerequesite line is followed by a "recipe."  A recipe is
# a series zero or more one-line commands indented with a tab
# character (yes, it must be a tab character!).  In this first rule,
# if you have all the .o files up-to-date, you make the evil
# executable by running clang++ with the flags specified above giving
# it all the .o files and producing the executable output in a
# file named "evil".
# 
# TODO: Replace the blanks [] with the list of object files we need to link
#       together to create our "evil" executable.  Remember that object files
#       are those that correspond to a cpp file.
evil: evil.o roster.o 
	${CXX} ${LDFLAGS} -o evil $^

# Note that we have specified that our target is an executable called "evil".
# Thus, we can create that executable using the command "make evil", just as
# later we will be able to clean things up using "make clean" or the like.
# However, we can also simply just type "make" and for this file, it will
# do the same thing.  This is because, by default, make will treat the first
# target defined in the Makefile as the one to build if not told otherwise.
# That means that "make" and "make evil" do the same thing, because evil is
# our first target.  Later targets, like "clean" require us to actually specify
# when we want them to be executed, using commands like "make clean".

#
# Here is a rule to make evil.o
#
# TODO: Replace the blanks [] with the list of files that evil.o will need
#       access to in order to know all the information it must include to work.
evil.o:  evil.cpp roster.h
	${CXX} ${CXXFLAGS} -c evil.cpp

# Note the -c, which tells clang++ to stop after the compilation step.
# Otherwise, clang++ would attempt to link the file and make a
# program, which would fail.  Why?
# 
# Consider the above rule.  Note that every .cpp file can be turned
# into a .o file in exactly the same way, by compiling that .cpp file,
# using its matching .h file if one exists, and then producing a .o
# file with the same name, too.
#
# Because of this, make already has a bunch of built-in rules, including 
# the one just described, and for those, you can omit the recipes if you like.  
# Furthermore, if the conventionally known variables CXX and CXXFLAGS are 
# defined, make will use them!  What make *does not* know is what files 
# besides the .cpp file itself the program module  might depend on.  
# So, we only specify the target and dependencies here.
#
# TODO: Replace the blanks [] with the list of files that roster.o will need
#       access to in order to know all the information it must include to work.
roster.o:  roster.cpp roster.h
	${CXX} ${CXXFLAGS} -c roster.cpp

# The above rule for roster.o will do exactly the same thing as the
# rule for evil.o (except for using different files, of course).
#
# TRY: In the above rule, we did not include any line to call the actual 
#      compilation command, unlike with evil.o  This rule simply uses the
#      things make knows how to do on its own.  You can test this by:
#         (a) Adding the command here for roster.o and confirming that 
#             'make evil' does the same thing as before.
#         (b) Removing the command from the evil.o recipe and confirming that
#             'make evil' does the same thing as before.
#
# TRY: In the above rule for roster.o, did you include the roster.h dependency?
#      It turns out that this is optional as well, since make knows that any
#      file like roster.cpp that has a matching roster.h file will use it, 
#      whereas a file live evil.cpp without a matching .h file will not.
#      You can confirm this by checking that the 'make evil' command does
#      the same thing whether or not we have included roster.h in our recipe.


# The following rules show how you can use make to automate things
# besides program building.
#
# Makefiles traditionally have a "clean" target.  The purpose is to
# clean up everything that is automatically built by make.  It's
# useful for when you want to save disk space and also when you've
# messed things up and just want to rebuild everything from scratch.
# The clean target doesn't have any prerequisites, because you don't
# need anything to be there in order to clean up!
#
# .dSYM directories are something that gets make in the Mac
# environment for debugging data, and so I delete them when cleaning
# up.
# The -f flag to rm means "don't report errors," so if there is no
# .dSYM or .o files you won't hear anything.
# The -r flag to rm means "recursively" delete any directories.
#
# *** This is a very dangerous command!!! ***
# It will delete all the listed items, recursively descending into
# directories, and not give any warnings or error messages.  Be VERY
# CAREFUL!  For example, if you put a space between the * and the . in
# *.o, then the * will match ALL files in the current directory, and
# you will lose everything from this directory on down.  Quadruple
# check this command!
#
# TODO: Replace the blanks [] with the name of the executable program that
#       the Makefile generates.  After running the 'make clean' command, 
#       that executable and all other .o files produced during that command.
clean:
	rm -rf evil *.o *.dSYM

done:
	rm -rf *.o *.dSYM
#
# TRY: define another rule that removes all the same things as clean,
#      *except for* the executable.  Confirm that running this command
#      after making the project leaves you with code you can still run,
#      but gets rid of the other things like .o files we don't need.
#      Make sure to give this rule its own distinct name.