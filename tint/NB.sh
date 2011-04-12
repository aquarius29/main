#!/bin/bash

BUILD_DIR=${HOME}/emb-2011/test-cvs
DATE=$(date '+%Y%m%d')

#LOG_FILE=${HOME}/emb-2011/log/mybuild-${DATE}.lo#g
#rm -f ${LOG_FILE}

check_return_value()
{
    RET_VAL=$1
    COMMENT=$2
    
   if [ $RET_VAL -ne 0 ]
   then
   	echo "FAIL:  $COMMENT"
  	exit $RET_VAL
   fi
}

get_src()
{
  #rm -fr main/

	git  pull  origin
  GIT_RET=$?
  check_return_value $GET_RET "git pull"
}

#setup_src()
#{
#    ./configure --disable-gui --disable-gnome-ap#plet --disable-doc
#    check_return_value $? "./configure"
#}

#test_src()
#{
#    make check
#    check_return_value $? "make test"
#}

#
#  Clean up
#
rm -fr ${BUILD_DIR}
mkdir -p ${BUILD_DIR}
cd			${BUILD_DIR}


#
#  Get code from GIT
#
get_src



# Run the configure script
# setup_src   >> $LOG_FILE   2>&1

# and finally ... test it
#test_src   >> $LOG_FILE   2>&1



