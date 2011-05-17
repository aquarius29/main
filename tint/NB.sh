#!/bin/bash

## TINT script
## -------------------------------------------------------------------------------
## Authors: Eugene Groshev, Nikita Englund
## Change history:
##		 2011-05-16, Nikita:
##				 - comment code, removing un-used code.
##     2011-05-12, Eugene:
##         - fixed REPOS array initialization and traversing problems (works!)
##         - added 3rd runtime parameter, allowing to skip pulling code from GitHub
##     2011-05-11, Eugene:
##         - added 2nd runtime parameter (Movement implementation)
##     2011-05-10, Eugene:
##         - added handling of README.txt files (before only README were recognized)
##         - added sections to clean_up() and copy_code() for handling the Panda scheduler (sched/psched)
##     2011-05-04, Eugene:
##         - added create_branch() function for creating new test branch in 'main'
##         - finalized copy_code() function
##     2011-05-03, Eugene:
##         - added clean_up() function which cleans src/, lib/ and include/ folders in 
##           group subfolders of the 'main' working directory  
##         - added copy_code() function, which copies code from groups' repos to
##           group subfolders of the 'main' working directory
##     2011-04-28, Eugene:
##         - added echolog() function which both print outs and logs passed arguments
##         - made $1 a compulsory argument to specify script run mode
##     2011-04-26, Eugene:
##         - $1 now specifies sript run mode (server or izimbra (Eugene's local))
##         - git pull now done in a loop
##         - git pull results are assigned to STATUS variable 
##         - overall status of the project assigned to PROJECT_CHANGED
##     changes before that: Nikita
##


# "==========================================================" - 58 characters
# "----------------------------------------------------------"






## -------------------------------------------------------------------------------
## 1. Script initialization section
## -------------------------------------------------------------------------------

# If no mode is specified, script exits with an error message
if [ $# -lt 2 ]
then
    echo "Please specify parameters: NB.sh MODE MOV [PULL]"
    echo "    MODE - chooses the script running mode:"
    echo "        server - runs script in server mode"
    echo "        izimbra - runs script in Eugene's local mode" 
    echo "    MOV - chooses implementation of the Movement task:"
    echo "        mv - Jin & Amber"
    echo "        mov_dev - Sepideh & Maryam"
    echo "        aydan_mov - Aydan (CA code is not used!)"
    echo "    PULL - tells the script if the code has to be pulled"
    echo "        nopull - skips pulling code from GitHub"
    exit -1
fi

# Setting build directory for server mode
if [ $1 = "server" ]
then
    BUILD_DIR=${HOME}/emb-test
    LOG_DIR=${HOME}/emb-test/log
fi

# Setting build directory for Eugene's local mode
if [ $1 = "izimbra" ]
then
    BUILD_DIR=$SEMB
    LOG_DIR=$SEMB/log
fi

# 2nd srcipt parameter specifies which branch of 'mov' repo to use
MOV_BRANCH=$2

# Optional Nikita mode here

# Setting log file of they day 
DATE=$(date '+%Y%m%d')
LOG_FILE=${LOG_DIR}/${DATE}.log
rm -f "${LOG_FILE}" #quotes because of the whitespaces in file path 

# Specifying list of groups to be processed by the script
declare -a REPOS=( sched ca moto proto stab ) #conn nav cam ui - exclude UI and Panda groups for now 


## -------------------------------------------------------------------------------
## 2. Local functions used below in the script
## -------------------------------------------------------------------------------


## Writes all passed arguments to a log file
log()
{
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $*"  >> "${LOG_FILE}" #quotes because of the whitespaces in file path  
}

## First prints out, then writes all passed arguments to a log file
echolog()
{
    echo "$*"
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $*"  >> "${LOG_FILE}" #quotes because of the whitespaces in file path 
}

#check_return_value()
#{
#    RET_VAL=$1
#    COMMENT=$2
#    #cd emb-2011
#   if [ $RET_VAL -ne 0 ]
#   then
#   	echo "FAIL:  $COMMENT"
#  	exit $RET_VAL
#   fi
#}




## Initial version of the source code pull function
## Author: Nikita Englund
## -----------------------------------------------------------------
get_src()
{
 
 #Check what the working dir is.
 #----Working dir------
cd ..
cd ..
#cd			${BUILD_DIR}
echo "The script you are running has basename `basename $0`,  dirname `dirname $0`"
echo "The present working directory is `pwd`"
log "-----------------------"


#
#Go to the right dir, pull from repo, check_return, leave dir.
# ----Pull Moto-----  
  log "Pulling moto ..."
  cd moto
  echo "The present working directory is `pwd`"
  log "    git pull moto"
  git pull
  log " 'git pull' "
  GIT_RET=$?
  log "   return $GIT_RET"
  check_return_value $GIT_RET "git pull moto"
  cd ..
  log "Leaving dir...."
  log "-------------------"

#
#Go to the right dir, pull from repo, check_return, leave dir.
#-----Pull Sched-----  
  log "Pulling Sched ..."
  cd sched
  echo "The present working directory is `pwd`"
  log "    git pull Sched" 
  git pull
  GIT_RET=$?
  log "   return $GIT_RET"
  check_return_value $GIT_RET "git pull sched"
  cd ..
  log "Leaving dir...."
  log "-------------------"
  
 
#
#Go to the right dir, pull from repo, check_return, leave dir.
 #-----Pull Nav-----  
  log "Pulling nav ..."
  cd nav
  echo "The present working directory is `pwd`"
  log "    git pull nav" 
  git pull
  GIT_RET=$?
  log "   return $GIT_RET"
  check_return_value $GIT_RET "git pull nav"
  cd ..
  log "Leaving dir...."
  log "-------------------" 
  
  
#
#Go to the right dir, pull from repo, check_return, leave dir.
   #-----Pull Conn-----  
  log "Pulling conn ..."
  cd conn
  echo "The present working directory is `pwd`"
  log "    git pull conn" 
  git pull
  GIT_RET=$?
  log "   return $GIT_RET"
  check_return_value $GIT_RET "git pull conn"
  cd ..
  log "Leaving dir...."
  log "-------------------" 
  
  
#
#Go to the right dir, pull from repo, check_return, leave dir.
     #-----Pull Cam-----  
  log "Pulling cam ..."
  cd cam
  echo "The present working directory is `pwd`"
  log "    git pull cam" 
  git pull
  GIT_RET=$?
  log "   return $GIT_RET"
  check_return_value $GIT_RET "git pull cam"
  cd ..
  log "Leaving dir...."
  log "-------------------" 
  
  
#
#Go to the right dir, pull from repo, check_return, leave dir.
    #-----Pull Ca-----  
  log "Pulling ca ..."
  cd ca
  echo "The present working directory is `pwd`"
  log "    git pull ca" 
  git pull
  GIT_RET=$?
  log "   return $GIT_RET"
  check_return_value $GIT_RET "git pull ca"
  cd ..
  log "Leaving dir...."
  log "-------------------" 
  
#
#Go to the right dir, pull from repo, check_return, leave dir.
      #-----Pull proto-----  
  log "Pulling proto ..."
  cd proto
  echo "The present working directory is `pwd`"
  log "    git pull proto"
  git pull
  GIT_RET=$?
  log "   return $GIT_RET"
  check_return_value $GIT_RET "git pull proto"
  cd ..
  log "Leaving dir...."
  log "-------------------" 
  
#
#Go to the right dir, pull from repo, check_return, leave dir.
       #-----Pull UI-----  
  log "Pulling ui ..."
  cd ui
  echo "The present working directory is `pwd`"
  log "    git pull ui"
  git pull
  GIT_RET=$?
  log "   return $GIT_RET"
  check_return_value $GIT_RET "git pull ui"
  cd ..
  log "Leaving dir...."
  log "-------------------" 
  
}


prep_src()
{
		log "Nothing to prepare...."
}


build_src()
{
		cd main
    log "Building in dir $(pwd)"
    make
    check_return_value $? "make/build '$?'"
}


test_src()
{
    make check
    check_return_value $? "make test"
}


## Improved version of the source code pull function
## Function has to be call from the ${BUILD_DIR}
## Author: Eugene Groshev
## -----------------------------------------------------------------
git_pull()
{

PROJECT_CHANGED=0 # variable to store the change state of the project

# loop through local repos and pull from remotes
#for REPO in ca cam conn moto nav proto sched stab ui
for REPO in ${REPOS[@]}
do
    log "----------------------------------------------------------"
	log "Pulling $REPO"
    if [ $REPO = ca ]
    then
        cd $MOV_BRANCH
        STATUS=`git pull origin $MOV_BRANCH`
    else    
    	cd $REPO
        STATUS=`git pull origin master`
    fi
    log $STATUS 
    if [ "$STATUS" != "Already up-to-date." ]
    then
        PROJECT_CHANGED=1
    fi
    cd .. # cd back to ${BUILD_DIR}
done

#echo $PROJECT_CHANGED

}


## Clean-up function for the main project directory
## Function has to be call from the ${BUILD_DIR}
## Author: Eugene Groshev 
## -----------------------------------------------------------------
clean_up()
{
cd main # cd to main project directory 
for REPO in ${REPOS[@]}
do
#    if [ $REPO = "ca" ]
#    then
    case $REPO in
        ca)  # 'ca' have both CA and Movement code
            # clean up CA code
            cd ca
            rm -rf src/*
            rm -rf lib/*
            rm -rf include/*
            rm -rf test/*
            rm -rf Makefile
            rm -rf README  
            rm -rf README.txt
            cd .. # cd back to main   
            # clean up Movement code 
            cd mov
            rm -rf src/*
            rm -rf lib/*
            rm -rf include/*
            rm -rf test/*
            rm -rf Makefile
            rm -rf README  
            rm -rf README.txt
            cd .. # cd back to main
            ;;
            
        proto)  # 'proto' repo have code for both Arduino and Panda
            # clean up Arduino code
            cd proto_mega
            rm -rf src/*
            rm -rf lib/*
            rm -rf include/*
            rm -rf test/*
            rm -rf Makefile
            rm -rf README  
            rm -rf README.txt
            cd .. # cd back to main   
            # clean up Panda code
            cd proto_panda
            rm -rf src/*
            rm -rf lib/*
            rm -rf include/*
            rm -rf test/*
            rm -rf Makefile
            rm -rf README  
            rm -rf README.txt
            cd .. # cd back to main            
            ;;
        sched)  # 'sched' repo have code for both Arduino and Panda
            # clean up Arduino code
            cd sched
            rm -rf src/*
            rm -rf lib/*
            rm -rf include/*
            rm -rf test/*
            rm -rf Makefile
            rm -rf README  
            rm -rf README.txt  
            cd .. # cd back to main   
            # clean up Panda code
            cd psched
            rm -rf src/*
            rm -rf lib/*
            rm -rf include/*
            rm -rf test/*
            rm -rf Makefile
            rm -rf README  
            rm -rf README.txt  
            cd .. # cd back to main            
            ;;
            
        *)  # all other repos have only one folder of original code 
            echo ${REPO}
            cd ${REPO}
            rm -rf src/*
            rm -rf lib/*
            rm -rf include/*
            rm -rf test/*
            rm -rf Makefile
            rm -rf README
            rm -rf README.txt  
            cd .. # cd back to main
            ;;
    esac

done
cd .. # cd back to ${BUILD_DIR}
}


## Function has to be call from the ${BUILD_DIR}
## Author: Eugene Groshev
## -----------------------------------------------------------------
copy_code()
{     
for REPO in ${REPOS[@]}
do
#    if [ $REPO = "ca" ]
#    then
    case $REPO in
        ca)  # 'ca' have both CA and Movement code
            # copy CA code
            # /src
            cp -p ${MOV_BRANCH}/ca/src/*.c main/ca/src
            cp -p ${MOV_BRANCH}/ca/src/*.h main/ca/src
            cp -p ${MOV_BRANCH}/ca/src/Makefile main/ca/src
            cp -p ${MOV_BRANCH}/ca/src/README main/ca/src
            cp -p ${MOV_BRANCH}/ca/src/README.txt main/ca/src

            # /lib
            cp -p ${MOV_BRANCH}/ca/lib/*.a main/ca/lib
            cp -p ${MOV_BRANCH}/ca/lib/README main/ca/lib
            cp -p ${MOV_BRANCH}/ca/lib/README.txt main/ca/lib
            # /include
            cp -p ${MOV_BRANCH}/ca/include/*.h main/ca/include
            cp -p ${MOV_BRANCH}/ca/include/README main/ca/include
            cp -p ${MOV_BRANCH}/ca/include/README.txt main/ca/include
            # /test
            cp -p ${MOV_BRANCH}/ca/test/*.c main/ca/test
            cp -p ${MOV_BRANCH}/ca/test/*.h main/ca/test
            cp -p ${MOV_BRANCH}/ca/test/Makefile main/ca/test
            cp -p ${MOV_BRANCH}/ca/test/README main/ca/test
            cp -p ${MOV_BRANCH}/ca/test/README.txt main/ca/test
            # Makefile and README
            cp -p ${MOV_BRANCH}/ca/Makefile main/ca
            cp -p ${MOV_BRANCH}/ca/README main/ca
            cp -p ${MOV_BRANCH}/ca/README.txt main/ca
            
            # copy Movement code 
            # /src
            cp -p ${MOV_BRANCH}/mov/src/*.c main/mov/src
            cp -p ${MOV_BRANCH}/mov/src/*.h main/mov/src
            cp -p ${MOV_BRANCH}/mov/src/Makefile main/mov/src
            cp -p ${MOV_BRANCH}/mov/src/README main/mov/src
            cp -p ${MOV_BRANCH}/mov/src/README.txt main/mov/src
            # /lib
            cp -p ${MOV_BRANCH}/mov/lib/*.a main/mov/lib
            cp -p ${MOV_BRANCH}/mov/lib/README main/mov/lib
            cp -p ${MOV_BRANCH}/mov/lib/README.txt main/mov/lib
            # /include
            cp -p ${MOV_BRANCH}/mov/include/*.h main/mov/include
            cp -p ${MOV_BRANCH}/mov/include/README main/mov/include
            cp -p ${MOV_BRANCH}/mov/include/README.txt main/mov/include
            # /test
            cp -p ${MOV_BRANCH}/mov/test/*.c main/mov/test
            cp -p ${MOV_BRANCH}/mov/test/*.h main/mov/test
            cp -p ${MOV_BRANCH}/mov/test/Makefile main/mov/test
            cp -p ${MOV_BRANCH}/mov/test/README main/mov/test
            cp -p ${MOV_BRANCH}/mov/test/README.txt main/mov/test
            # Makefile and README
            cp -p ${MOV_BRANCH}/mov/Makefile main/mov
            cp -p ${MOV_BRANCH}/mov/README main/mov
            cp -p ${MOV_BRANCH}/mov/README.txt main/mov
            ;;
            
        proto)  # 'proto' repo have code for both Arduino and Panda
            # copy Arduino code:
            # /src
            cp -p ${REPO}/proto_mega/src/*.c main/proto_mega/src
            cp -p ${REPO}/proto_mega/src/*.h main/proto_mega/src
            cp -p ${REPO}/proto_mega/src/Makefile main/proto_mega/src
            cp -p ${REPO}/proto_mega/src/README main/proto_mega/src
            cp -p ${REPO}/proto_mega/src/README.txt main/proto_mega/src
            # /lib
            cp -p ${REPO}/proto_mega/lib/*.a main/proto_mega/lib
            cp -p ${REPO}/proto_mega/lib/README main/proto_mega/lib
            cp -p ${REPO}/proto_mega/lib/README.txt main/proto_mega/lib
            # /include
            cp -p ${REPO}/proto_mega/include/*.h main/proto_mega/include
            cp -p ${REPO}/proto_mega/include/README main/proto_mega/include
            cp -p ${REPO}/proto_mega/include/README.txt main/proto_mega/include
            # /test
            cp -p ${REPO}/proto_mega/test/*.c main/proto_mega/test
            cp -p ${REPO}/proto_mega/test/*.h main/proto_mega/test
            cp -p ${REPO}/proto_mega/test/Makefile main/proto_mega/test
            cp -p ${REPO}/proto_mega/test/README main/proto_mega/test
            cp -p ${REPO}/proto_mega/test/README.txt main/proto_mega/test
            # Makefile and README
            cp -p ${REPO}/proto_mega/Makefile main/proto_mega
            cp -p ${REPO}/proto_mega/README main/proto_mega
            cp -p ${REPO}/proto_mega/README.txt main/proto_mega
             
            # copy Panda code:
            # /src
            cp -p ${REPO}/proto_panda/src/*.c main/proto_panda/src
            cp -p ${REPO}/proto_panda/src/*.h main/proto_panda/src
            cp -p ${REPO}/proto_panda/src/Makefile main/proto_panda/src
            cp -p ${REPO}/proto_panda/src/README main/proto_panda/src
            cp -p ${REPO}/proto_panda/src/README.txt main/proto_panda/src
            # /lib
            cp -p ${REPO}/proto_panda/lib/*.a main/proto_panda/lib
            cp -p ${REPO}/proto_panda/lib/README main/proto_panda/lib
            cp -p ${REPO}/proto_panda/lib/README.txt main/proto_panda/lib
            # /include
            cp -p ${REPO}/proto_panda/include/*.h main/proto_panda/include
            cp -p ${REPO}/proto_panda/include/README main/proto_panda/include
            cp -p ${REPO}/proto_panda/include/README.txt main/proto_panda/include
            # /test
            cp -p ${REPO}/proto_panda/test/*.c main/proto_panda/test
            cp -p ${REPO}/proto_panda/test/*.h main/proto_panda/test
            cp -p ${REPO}/proto_panda/test/Makefile main/proto_panda/test
            cp -p ${REPO}/proto_panda/test/README main/proto_panda/test
            cp -p ${REPO}/proto_panda/test/README.txt main/proto_panda/test
            # Makefile and README
            cp -p ${REPO}/proto_panda/Makefile main/proto_panda
            cp -p ${REPO}/proto_panda/README main/proto_panda
            cp -p ${REPO}/proto_panda/README.txt main/proto_panda
            ;;
        
        sched)  # 'sched' repo have code for both Arduino and Panda
            # copy Arduino code:
            # /src
            cp -p ${REPO}/sched/src/*.c main/sched/src
            cp -p ${REPO}/sched/src/*.h main/sched/src
            cp -p ${REPO}/sched/src/Makefile main/sched/src
            cp -p ${REPO}/sched/src/README main/sched/src
            cp -p ${REPO}/sched/src/README.txt main/sched/src
            # /lib
            cp -p ${REPO}/sched/lib/*.a main/sched/lib
            cp -p ${REPO}/sched/lib/README main/sched/lib
            cp -p ${REPO}/sched/lib/README.txt main/sched/lib
            # /include
            cp -p ${REPO}/sched/include/*.h main/sched/include
            cp -p ${REPO}/sched/include/README main/sched/include
            cp -p ${REPO}/sched/include/README.txt main/sched/include
            # /test
            cp -p ${REPO}/sched/test/*.c main/sched/test
            cp -p ${REPO}/sched/test/*.h main/sched/test
            cp -p ${REPO}/sched/test/Makefile main/sched/test
            cp -p ${REPO}/sched/test/README main/sched/test
            cp -p ${REPO}/sched/test/README.txt main/sched/test
            # Makefile and README
            cp -p ${REPO}/sched/Makefile main/sched
            cp -p ${REPO}/sched/README main/sched
            cp -p ${REPO}/sched/README.txt main/sched
             
            # copy Panda code:
            # /src
            cp -p ${REPO}/psched/src/*.c main/psched/src
            cp -p ${REPO}/psched/src/*.h main/psched/src
            cp -p ${REPO}/psched/src/Makefile main/psched/src
            cp -p ${REPO}/psched/src/README main/psched/src
            cp -p ${REPO}/psched/src/README.txt main/psched/src
            # /lib
            cp -p ${REPO}/psched/lib/*.a main/psched/lib
            cp -p ${REPO}/psched/lib/README main/psched/lib
            cp -p ${REPO}/psched/lib/README.txt main/psched/lib
            # /include
            cp -p ${REPO}/psched/include/*.h main/psched/include
            cp -p ${REPO}/psched/include/README main/psched/include
            cp -p ${REPO}/psched/include/README.txt main/psched/include
            # /test
            cp -p ${REPO}/psched/test/*.c main/psched/test
            cp -p ${REPO}/psched/test/*.h main/psched/test
            cp -p ${REPO}/psched/test/Makefile main/psched/test
            cp -p ${REPO}/psched/test/README main/psched/test
            cp -p ${REPO}/psched/test/README.txt main/psched/test
            # Makefile and README
            cp -p ${REPO}/psched/Makefile main/psched
            cp -p ${REPO}/psched/README main/psched
            cp -p ${REPO}/psched/README.txt main/psched
            ;;
                
        *)  # all other repos have only one folder of original code 
            # /src
            cp -p ${REPO}/${REPO}/src/*.c main/${REPO}/src
            cp -p ${REPO}/${REPO}/src/*.h main/${REPO}/src
            cp -p ${REPO}/${REPO}/src/Makefile main/${REPO}/src
            cp -p ${REPO}/${REPO}/src/README main/${REPO}/src
            cp -p ${REPO}/${REPO}/src/README.txt main/${REPO}/src
            # /lib
            cp -p ${REPO}/${REPO}/lib/*.a main/${REPO}/lib
            cp -p ${REPO}/${REPO}/lib/README main/${REPO}/lib
            cp -p ${REPO}/${REPO}/lib/README.txt main/${REPO}/lib
            # /include
            cp -p ${REPO}/${REPO}/include/*.h main/${REPO}/include
            cp -p ${REPO}/${REPO}/include/README main/${REPO}/include
            cp -p ${REPO}/${REPO}/include/README.txt main/${REPO}/include
            # /test
            cp -p ${REPO}/${REPO}/test/*.c main/${REPO}/test
            cp -p ${REPO}/${REPO}/test/*.h main/${REPO}/test
            cp -p ${REPO}/${REPO}/test/Makefile main/${REPO}/test
            cp -p ${REPO}/${REPO}/test/README main/${REPO}/test
            cp -p ${REPO}/${REPO}/test/README.txt main/${REPO}/test
            # Makefile and README
            cp -p ${REPO}/${REPO}/Makefile main/${REPO}
            cp -p ${REPO}/${REPO}/README main/${REPO}
            cp -p ${REPO}/${REPO}/README.txt main/${REPO}
            ;;
    esac

done

}


## Creates a new test branch in the local copy of 'main' repository
## The branch is date- and timestamped
## Function has to be call from the ${BUILD_DIR}
## Author: Eugene Groshev
## -----------------------------------------------------------------
create_branch()
{
cd main
BRANCH=test-$(date '+%Y%m%d-%H%M')-$MOV_BRANCH
echolog  $BRANCH 
git checkout -b $BRANCH 
cd ..  # cd back to ${BUILD_DIR}
}


## -------------------------------------------------------------------------------
## 3. Main section of the script
## -------------------------------------------------------------------------------

# Echo & log script initialization data
echolog " Running TINT script in _$1_ mode"
echolog " Movement implementation is taken from ca/${MOV_BRANCH} branch" 
echolog " Build directory is: $BUILD_DIR"
echolog " Log directory is: $LOG_DIR"
echolog " Log file is: $LOG_FILE"
echo "   "
echolog " Groups to be integrated: ${REPOS[*]}" 

# cd to build dir
cd "${BUILD_DIR}"
#cd ..
#cd ..


#
#  Get code from GIT
#
if [ $3 = "nopull" ]
then
    log "=========================================================="
    log " Skipping pulling code from GitHub "
    log "=========================================================="
else
    log "=========================================================="
    log " Pulling code from GitHub "
    log "=========================================================="
    git_pull # if new code is present, the function will set $PROJECT_CHANGED to 1  
    # Eventual exit, if no code has been changed
    if [ $PROJECT_CHANGED = 0 ]
    then
        log "=========================================================="
        echolog " EXIT: No new code"
        log "=========================================================="
        exit $PROJECT_CHANGED
    fi
fi



#
#  If project has changed, first create and switch to new git branch
#  in the 'main' repo
#
create_branch

#
# After that, clean up the 'main' working direcotory
#
log "=========================================================="
log " Cleaning up group subfolders of the 'main' directory "
log "=========================================================="


clean_up


#
# Copy code from group's repos to 'main' working directory
#
log "=========================================================="
log " Copying updated code from groups' repos "
log "=========================================================="

copy_code

# Create the configure script
#prep_src


# Build it
#build_src

# Test it
#test_src # unit tests, gcov, lcov, quickcheck

# Generate docs and copy them to www



#Mail it to me
#cat /tmp/mybuild-20110406.log  | mailx -s "Build #results from $(date)" testintegration@googlegroups.com

# git tag & git describe - tagging a release
# git archive - making a tar
# upload tar to web directory
