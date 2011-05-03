#!/bin/bash

## TINT script
## -------------------------------------------------------------------------------
## Authors: Eugene Groshev, Nikita Englund
## Change history:
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


DATE=$(date '+%Y%m%d')

LOG_FILE=${LOG_DIR}/${DATE}.log
rm -f "${LOG_FILE}" #quotes because of the whitespaces in file path 



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


## Improved version of the source code pull function
## Function has to be call from the ${BUILD_DIR}
## Author: Eugene Groshev
git_pull()
{

PROJECT_CHANGED=0 # variable to store the change state of the project

# loop through local repos and pull from remotes
for REPO in ca cam conn moto nav proto sched stab ui
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

#echo $PROJECT_CHANGED

}


## Clean-up function for the main project directory
## Function has to be call from the ${BUILD_DIR}
## Author: Eugene Groshev 
clean_up()
{
cd main # cd to main project directory 
for REPO in ca cam conn moto nav proto sched stab ui
do
    if [ $REPO = "ca" ]
    then
        cd $REPO
        rm -rf ca/src/*
        rm -rf ca/lib/*
        rm -rf ca/include/*
        rm -rf ca/test/*
        rm -rf ca/Makefile
        rm -rf ca/README    
        rm -rf mov/src/*
        rm -rf mov/lib/*
        rm -rf mov/include/*
        rm -rf mov/test/*
        rm -rf mov/Makefile
        rm -rf mov/README  
        cd .. # cd back to main
    else
        cd $REPO
        rm -rf $(REPO)/src/*
        rm -rf $(REPO)/lib/*
        rm -rf $(REPO)/include/*
        rm -rf $(REPO)/test/*
        rm -rf $(REPO)/Makefile
        rm -rf $(REPO)/README
        cd .. # cd back to main
    fi
done
cd .. # cd back to ${BUILD_DIR}
}


## Initial version of the source code pull function
#get_src()
#{
# 
# #----Working dir------
#cd ..
#cd ..
##cd			${BUILD_DIR}
#echo "The script you are running has basename `basename $0`,  dirname `dirname $0`"
#echo "The present working directory is `pwd`"
#log "-----------------------"
#
#
#
## ----Pull Moto-----  
#  log "Pulling moto ..."
#  cd moto
#  echo "The present working directory is `pwd`"
#  log "    git pull moto"
#  git pull
#  log " 'git pull' "
#  GIT_RET=$?
#  log "   return $GIT_RET"
#  check_return_value $GIT_RET "git pull moto"
#  cd ..
#  log "Leaving dir...."
#  log "-------------------"
#
#
##-----Pull Sched-----  
#  log "Pulling Sched ..."
#  cd sched
#  echo "The present working directory is `pwd`"
#  log "    git pull Sched" 
#  git pull
#  GIT_RET=$?
#  log "   return $GIT_RET"
#  check_return_value $GIT_RET "git pull sched"
#  cd ..
#  log "Leaving dir...."
#  log "-------------------"
#  
# 
# #-----Pull Nav-----  
#  log "Pulling nav ..."
#  cd nav
#  echo "The present working directory is `pwd`"
#  log "    git pull nav" 
#  git pull
#  GIT_RET=$?
#  log "   return $GIT_RET"
#  check_return_value $GIT_RET "git pull nav"
#  cd ..
#  log "Leaving dir...."
#  log "-------------------" 
#  
#  
#   #-----Pull Conn-----  
#  log "Pulling conn ..."
#  cd conn
#  echo "The present working directory is `pwd`"
#  log "    git pull conn" 
#  git pull
#  GIT_RET=$?
#  log "   return $GIT_RET"
#  check_return_value $GIT_RET "git pull conn"
#  cd ..
#  log "Leaving dir...."
#  log "-------------------" 
#  
#  
#     #-----Pull Cam-----  
#  log "Pulling cam ..."
#  cd cam
#  echo "The present working directory is `pwd`"
#  log "    git pull cam" 
#  git pull
#  GIT_RET=$?
#  log "   return $GIT_RET"
#  check_return_value $GIT_RET "git pull cam"
#  cd ..
#  log "Leaving dir...."
#  log "-------------------" 
#  
#    #-----Pull Ca-----  
#  log "Pulling ca ..."
#  cd ca
#  echo "The present working directory is `pwd`"
#  log "    git pull ca" 
#  git pull
#  GIT_RET=$?
#  log "   return $GIT_RET"
#  check_return_value $GIT_RET "git pull ca"
#  cd ..
#  log "Leaving dir...."
#  log "-------------------" 
#  
#      #-----Pull proto-----  
#  log "Pulling proto ..."
#  cd proto
#  echo "The present working directory is `pwd`"
#  log "    git pull proto"
#  git pull
#  GIT_RET=$?
#  log "   return $GIT_RET"
#  check_return_value $GIT_RET "git pull proto"
#  cd ..
#  log "Leaving dir...."
#  log "-------------------" 
#  
#       #-----Pull UI-----  
#  log "Pulling ui ..."
#  cd ui
#  echo "The present working directory is `pwd`"
#  log "    git pull ui"
#  git pull
#  GIT_RET=$?
#  log "   return $GIT_RET"
#  check_return_value $GIT_RET "git pull ui"
#  cd ..
#  log "Leaving dir...."
#  log "-------------------" 
#  
#  #Git Pull ca,cam,conn,filter,main,moto,nav,proto,sched,stab,ui
#  #git remote add moto git@github.com:SEMB2011/moto.git
#
#  #log "Getting sources from git"
#  #log "   git  clone  git://github.com/SEMB2011/main.git"
#	#git  clone  git://github.com/SEMB2011/main.git
#  #GIT_RET=$?
#  #log "   return $GIT_RET"
#  #check_return_value $GIT_RET "git clone"
#  
##  log "Adding remote moto ..."
##  log "    git remote add moto git@github.com:SEMB2011/moto.git"
##  git remote add moto git@github.com:SEMB2011/moto.git
##  GIT_RET=$?
##  log "   return $GIT_RET"
##  check_return_value $GET_RET "git remote add"
#
#  
#}

#prep_src()
#{
#		log "Nothing to prepare...."
#}
#
#build_src()
#{
#		cd main
#    log "Building in dir $(pwd)"
#    make
#    check_return_value $? "make/build '$?'"
#}
#
#test_src()
#{
#    make check
#    check_return_value $? "make test"
#}

## Function has to be call from the ${BUILD_DIR}
copy_code()
{
#cd main # cd to main project directory 
#for REPO in ca cam conn moto nav proto sched stab ui
#do
#    cd $REPO/$REPO
#    rm -rf src/*
#    rm -rf lib/*
#    rm -rf include/*
#    rm -rf test/*
#    rm -rf Makefile
#    rm -rf README
#    cd .. # cd back to main
#done
#cd .. # cd back to ${BUILD_DIR}
    echo "bla"
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
cd main
BRANCH=test-$DATE
echolog  $BRANCH 
git checkout -b $BRANCH 
cd ..  # cd back to ${BUILD_DIR}

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
