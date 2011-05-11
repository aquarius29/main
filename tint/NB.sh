#!/bin/bash

## TINT script
## -------------------------------------------------------------------------------
## Authors: Eugene Groshev, Nikita Englund
## Change history:
##     2011-04-10, Eugene:
##         - added sections to clean_up() and copy_code() for handling the Panda scheduler (sched/psched)
##     2011-05-10, Nikita:
##         - Commented code
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
if [ $# -lt 1 ]
then
    echo "Please specify script mode:"
    echo "    NB.sh server - runs script in server mode"
    echo "    NB.sh izimbra - runs script in Eugene's local mode" 
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

# Optional Nikita mode here

# Setting log file of they day 
DATE=$(date '+%Y%m%d')
LOG_FILE=${LOG_DIR}/${DATE}.log
rm -f "${LOG_FILE}" #quotes because of the whitespaces in file path 

# Specifying list of groups to be processed by the script
typeset -ra GROUPS=(sched ca moto proto stab) #conn nav cam ui - exclude UI and Panda groups for now 


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


#
#Author: Nikita Englund
check_return_value()
{
    RET_VAL=$1
    COMMENT=$2
    #cd emb-2011
   if [ $RET_VAL -ne 0 ]
   then
   	echo "FAIL:  $COMMENT"
  	exit $RET_VAL
   fi
}



## Initial version of the source code pull function
## -----------------------------------------------------------------
#
#Author: Nikita Englund
get_src()
{
 
 #Checks if the working directory is right
 #----Working dir------
cd ..
cd ..
#cd			${BUILD_DIR}
echo "The script you are running has basename `basename $0`,  dirname `dirname $0`"
echo "The present working directory is `pwd`"
log "-----------------------"


#Changes directory and pulls, then leaves that directory

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
  
  #Git Pull ca,cam,conn,filter,main,moto,nav,proto,sched,stab,ui
  #git remote add moto git@github.com:SEMB2011/moto.git

  #log "Getting sources from git"
  #log "   git  clone  git://github.com/SEMB2011/main.git"
	#git  clone  git://github.com/SEMB2011/main.git
  #GIT_RET=$?
  #log "   return $GIT_RET"
  #check_return_value $GIT_RET "git clone"
  
#  log "Adding remote moto ..."
#  log "    git remote add moto git@github.com:SEMB2011/moto.git"
#  git remote add moto git@github.com:SEMB2011/moto.git
#  GIT_RET=$?
#  log "   return $GIT_RET"
#  check_return_value $GET_RET "git remote add"  
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

<<<<<<< HEAD
# Setting build directory for server mode
if [ $1 = "server" ]
then
    BUILD_DIR=${HOME}/emb-test
    LOG_DIR=${HOME}/log
fi
=======
# loop through local repos and pull from remotes
#for REPO in ca cam conn moto nav proto sched stab ui
for REPO in $GROUPS
do
    log "----------------------------------------------------------"
	log "Pulling $REPO"
    cd $REPO
    STATUS=`git pull origin master`
    log $STATUS 
    if [ "$STATUS" != "Already up-to-date." ]
    then
        PROJECT_CHANGED=1
    fi
    cd .. # cd back to ${BUILD_DIR}
done
>>>>>>> d4c6d132d92fb9328a668a65dfdcec01bbd4fa95

#echo $PROJECT_CHANGED

}


## Clean-up function for the main project directory
## Function has to be call from the ${BUILD_DIR}
## Author: Eugene Groshev 
## -----------------------------------------------------------------
clean_up()
{
cd main # cd to main project directory 
for REPO in $GROUPS
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
            cd .. # cd back to main   
            # clean up Movement code 
            cd mov
            rm -rf src/*
            rm -rf lib/*
            rm -rf include/*
            rm -rf test/*
            rm -rf Makefile
            rm -rf README  
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
            cd .. # cd back to main   
            # clean up Panda code
            cd proto_panda
            rm -rf src/*
            rm -rf lib/*
            rm -rf include/*
            rm -rf test/*
            rm -rf Makefile
            rm -rf README  
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
            cd .. # cd back to main   
            # clean up Panda code
            cd psched
            rm -rf src/*
            rm -rf lib/*
            rm -rf include/*
            rm -rf test/*
            rm -rf Makefile
            rm -rf README  
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
for REPO in $GROUPS
do
#    if [ $REPO = "ca" ]
#    then
    case $REPO in
        ca)  # 'ca' have both CA and Movement code
            # copy CA code
            # /src
            cp -p ${REPO}/ca/src/*.c main/ca/src
            cp -p ${REPO}/ca/src/*.h main/ca/src
            cp -p ${REPO}/ca/src/Makefile main/ca/src
            cp -p ${REPO}/ca/src/README main/ca/src
            # /lib
            cp -p ${REPO}/ca/lib/*.a main/ca/lib
            cp -p ${REPO}/ca/lib/README main/ca/lib
            # /include
            cp -p ${REPO}/ca/include/*.h main/ca/include
            cp -p ${REPO}/ca/include/README main/ca/include
            # /test
            cp -p ${REPO}/ca/test/*.c main/ca/test
            cp -p ${REPO}/ca/test/*.h main/ca/test
            cp -p ${REPO}/ca/test/Makefile main/ca/test
            cp -p ${REPO}/ca/test/README main/ca/test
            # Makefile and README
            cp -p ${REPO}/ca/Makefile main/ca
            cp -p ${REPO}/ca/README main/ca
            
            # copy Movement code 
            # /src
            cp -p ${REPO}/mov/src/*.c main/mov/src
            cp -p ${REPO}/mov/src/*.h main/mov/src
            cp -p ${REPO}/mov/src/Makefile main/mov/src
            cp -p ${REPO}/mov/src/README main/mov/src
            # /lib
            cp -p ${REPO}/mov/lib/*.a main/mov/lib
            cp -p ${REPO}/mov/lib/README main/mov/lib
            # /include
            cp -p ${REPO}/mov/include/*.h main/mov/include
            cp -p ${REPO}/mov/include/README main/mov/include
            # /test
            cp -p ${REPO}/mov/test/*.c main/mov/test
            cp -p ${REPO}/mov/test/*.h main/mov/test
            cp -p ${REPO}/mov/test/Makefile main/mov/test
            cp -p ${REPO}/mov/test/README main/mov/test
            # Makefile and README
            cp -p ${REPO}/mov/Makefile main/mov
            cp -p ${REPO}/mov/README main/mov
            ;;
            
        proto)  # 'proto' repo have code for both Arduino and Panda
            # copy Arduino code:
            # /src
            cp -p ${REPO}/proto_mega/src/*.c main/proto_mega/src
            cp -p ${REPO}/proto_mega/src/*.h main/proto_mega/src
            cp -p ${REPO}/proto_mega/src/Makefile main/proto_mega/src
            cp -p ${REPO}/proto_mega/src/README main/proto_mega/src
            # /lib
            cp -p ${REPO}/proto_mega/lib/*.a main/proto_mega/lib
            cp -p ${REPO}/proto_mega/lib/README main/proto_mega/lib
            # /include
            cp -p ${REPO}/proto_mega/include/*.h main/proto_mega/include
            cp -p ${REPO}/proto_mega/include/README main/proto_mega/include
            # /test
            cp -p ${REPO}/proto_mega/test/*.c main/proto_mega/test
            cp -p ${REPO}/proto_mega/test/*.h main/proto_mega/test
            cp -p ${REPO}/proto_mega/test/Makefile main/proto_mega/test
            cp -p ${REPO}/proto_mega/test/README main/proto_mega/test
            # Makefile and README
            cp -p ${REPO}/proto_mega/Makefile main/proto_mega
            cp -p ${REPO}/proto_mega/README main/proto_mega
             
            # copy Panda code:
            # /src
            cp -p ${REPO}/proto_panda/src/*.c main/proto_panda/src
            cp -p ${REPO}/proto_panda/src/*.h main/proto_panda/src
            cp -p ${REPO}/proto_panda/src/Makefile main/proto_panda/src
            cp -p ${REPO}/proto_panda/src/README main/proto_panda/src
            # /lib
            cp -p ${REPO}/proto_panda/lib/*.a main/proto_panda/lib
            cp -p ${REPO}/proto_panda/lib/README main/proto_panda/lib
            # /include
            cp -p ${REPO}/proto_panda/include/*.h main/proto_panda/include
            cp -p ${REPO}/proto_panda/include/README main/proto_panda/include
            # /test
            cp -p ${REPO}/proto_panda/test/*.c main/proto_panda/test
            cp -p ${REPO}/proto_panda/test/*.h main/proto_panda/test
            cp -p ${REPO}/proto_panda/test/Makefile main/proto_panda/test
            cp -p ${REPO}/proto_panda/test/README main/proto_panda/test
            # Makefile and README
            cp -p ${REPO}/proto_panda/Makefile main/proto_panda
            cp -p ${REPO}/proto_panda/README main/proto_panda
            ;;
        
        sched)  # 'sched' repo have code for both Arduino and Panda
            # copy Arduino code:
            # /src
            cp -p ${REPO}/sched/src/*.c main/sched/src
            cp -p ${REPO}/sched/src/*.h main/sched/src
            cp -p ${REPO}/sched/src/Makefile main/sched/src
            cp -p ${REPO}/sched/src/README main/sched/src
            # /lib
            cp -p ${REPO}/sched/lib/*.a main/sched/lib
            cp -p ${REPO}/sched/lib/README main/sched/lib
            # /include
            cp -p ${REPO}/sched/include/*.h main/sched/include
            cp -p ${REPO}/sched/include/README main/sched/include
            # /test
            cp -p ${REPO}/sched/test/*.c main/sched/test
            cp -p ${REPO}/sched/test/*.h main/sched/test
            cp -p ${REPO}/sched/test/Makefile main/sched/test
            cp -p ${REPO}/sched/test/README main/sched/test
            # Makefile and README
            cp -p ${REPO}/sched/Makefile main/sched
            cp -p ${REPO}/sched/README main/sched
             
            # copy Panda code:
            # /src
            cp -p ${REPO}/psched/src/*.c main/psched/src
            cp -p ${REPO}/psched/src/*.h main/psched/src
            cp -p ${REPO}/psched/src/Makefile main/psched/src
            cp -p ${REPO}/psched/src/README main/psched/src
            # /lib
            cp -p ${REPO}/psched/lib/*.a main/psched/lib
            cp -p ${REPO}/psched/lib/README main/psched/lib
            # /include
            cp -p ${REPO}/psched/include/*.h main/psched/include
            cp -p ${REPO}/psched/include/README main/psched/include
            # /test
            cp -p ${REPO}/psched/test/*.c main/psched/test
            cp -p ${REPO}/psched/test/*.h main/psched/test
            cp -p ${REPO}/psched/test/Makefile main/psched/test
            cp -p ${REPO}/psched/test/README main/psched/test
            # Makefile and README
            cp -p ${REPO}/psched/Makefile main/psched
            cp -p ${REPO}/psched/README main/psched
            ;;
                
        *)  # all other repos have only one folder of original code 
            # /src
            cp -p ${REPO}/${REPO}/src/*.c main/${REPO}/src
            cp -p ${REPO}/${REPO}/src/*.h main/${REPO}/src
            cp -p ${REPO}/${REPO}/src/Makefile main/${REPO}/src
            cp -p ${REPO}/${REPO}/src/README main/${REPO}/src
            # /lib
            cp -p ${REPO}/${REPO}/lib/*.a main/${REPO}/lib
            cp -p ${REPO}/${REPO}/lib/README main/${REPO}/lib
            # /include
            cp -p ${REPO}/${REPO}/include/*.h main/${REPO}/include
            cp -p ${REPO}/${REPO}/include/README main/${REPO}/include
            # /test
            cp -p ${REPO}/${REPO}/test/*.c main/${REPO}/test
            cp -p ${REPO}/${REPO}/test/*.h main/${REPO}/test
            cp -p ${REPO}/${REPO}/test/Makefile main/${REPO}/test
            cp -p ${REPO}/${REPO}/test/README main/${REPO}/test
            # Makefile and README
            cp -p ${REPO}/${REPO}/Makefile main/${REPO}
            cp -p ${REPO}/${REPO}/README main/${REPO}
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
BRANCH=test-$(date '+%Y%m%d-%H%M')
echolog  $BRANCH 
git checkout -b $BRANCH 
cd ..  # cd back to ${BUILD_DIR}
}


## -------------------------------------------------------------------------------
## 3. Main section of the script
## -------------------------------------------------------------------------------

# Echo & log script initialization data
echolog " Starting TINT script in _$1_ mode"
echolog " Build directory is: $BUILD_DIR"
echolog " Log directory is: $LOG_DIR"
echolog " Log file is: $LOG_FILE"
echo "   "

# cd to build dir
cd "${BUILD_DIR}"
#cd ..
#cd ..


#
#  Get code from GIT
#
log "=========================================================="
log " Pulling code "
log "=========================================================="

#git_pull # if new code is present, the function will set $PROJECT_CHANGED to 1  
#
## Eventual exit, if no code has been changed
#if [ $PROJECT_CHANGED = 0 ]
#then
#    log "=========================================================="
#    log " EXIT: No new code"
#    log "=========================================================="
#    exit $PROJECT_CHANGED
#fi


#
#  If project has changed, first create and switch to new git branch
#  in the 'main' repo
#
#create_branch

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
