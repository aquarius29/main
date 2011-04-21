#!/bin/bash

LOG_DIR=${HOME}/logg/logg

BUILD_DIR=${HOME}/emb-test
DATE=$(date '+%Y%m%d')

LOG_FILE=${LOG_DIR}-${DATE}.log
rm -f ${LOG_FILE}


log()
{
  echo "$*" 
	echo "[$(date)] $*"  >> $LOG_FILE
}

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

get_src()
{
 
 #----Working dir------
cd ..
cd ..
#cd			${BUILD_DIR}
echo "The script you are running has basename `basename $0`,  dirname `dirname $0`"
echo "The present working directory is `pwd`"
log "-----------------------"



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


#
#
#
#   ---|MAIN|--- 
#
#
#



#
#  Clean up
#

#rm -fr ${BUILD_DIR}
#mkdir -p ${BUILD_DIR}


#
#  Get code from GIT
#

get_src



# Create the configure script
prep_src


# Build it
build_src

# Test it
test_src


#Mail it to me
#cat /tmp/mybuild-20110406.log  | mailx -s "Build #results from $(date)" testintegration@googlegroups.com

# git tag & git describe - tagging a release
# git archive - making a tar
# upload tar to web directory
