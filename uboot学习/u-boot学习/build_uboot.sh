#!/bin/sh
#������仰����ָ���ű��Ľ�����·��

#$1������ĵ�һ����������$0��ʾ�ű��ļ�����-z���жϺ���Ĳ����Ƿ�Ϊ��
if [ -z $1 ]
then	
#����޴�������������������Ϣ���˳��ű�
   echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
   echo "Please use correct make config.for example make SCP_1GDDR for SCP 1G DDR CoreBoard linux,android OS"
   echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
   exit 0
fi
#����������$1��ֵ���ַ���"SCP_1GDDR"|"SCP_2GDDR"|"SCP_1GDDR_Ubuntu"|"SCP_2GDDR_Ubuntu"��ִ����һ��
if   [ "$1" = "SCP_1GDDR" ] ||   [ "$1" = "SCP_2GDDR" ] || [ "$1" = "SCP_1GDDR_Ubuntu" ] ||   [ "$1" = "SCP_2GDDR_Ubuntu" ]
then 
	#���ݴ���������ö�Ӧ��sec·���ͺ��İ����ͣ��ⲿ�ֳ����������ṩ�ļ�����ص��ļ�
      sec_path="../CodeSign4SecureBoot_SCP/"
      CoreBoard_type="SCP"

elif [ "$1" = "POP_1GDDR" ] || [ "$1" = "POP_1GDDR_Ubuntu" ]
then
      sec_path="../CodeSign4SecureBoot_POP/"
      CoreBoard_type="POP"

elif [ "$1" = "POP_2GDDR" ] ||  [ "$1" = "POP_2GDDR_Ubuntu" ]
then
     sec_path="../CodeSign4SecureBoot_POP/"
     CoreBoard_type="POP2G"
else
      echo "make config error,please use correct params......"
      exit 0
fi

#��ȡCPU�ĺ�����
#ָ��grep processor /proc/cpuinfo ���
#processor	: 0
#processor	: 1
#processor	: 2
#processor	: 3
#$NF��ʾ���һ���У�field������������һ���ֶε����ݣ���field=3��Ȼ���ӡfield+1
CPU_JOB_NUM=$(grep processor /proc/cpuinfo | awk '{field=$NF};END{print field+1}')
#��ȡ��ǰĿ¼
ROOT_DIR=$(pwd)
# '##*/'ָ����ROOT_DIRĿ¼�������/������ǰ·������ ����'#/'ָ�����������/
CUR_DIR=${ROOT_DIR##*/}


#����������ɵ��ļ�
make distclean

#ɾ�����Ӻ�CPU��ص������ļ�
rm ${ROOT_DIR}/board/samsung/smdkc210/lowlevel_init.S	
rm ${ROOT_DIR}/cpu/arm_cortexa9/s5pc210/cpu_init.S

#�жϴ������$1���������
case "$1" in
#ִ�����ָ��
	clean)
		#ɾ��������ı��������ļ������ǻᱣ���ں˵������ļ�.config
		echo make clean
		#ɾ�����еı��������ļ����ں������ļ�(.config�ļ�)�͸��ֱ����ļ�
		make mrproper
		;;
#����clean����	
	*)
		#�ж��Ƿ���������ṩ�ļ��ܽ���Ŀ¼(directory)$sec_path
		if [ ! -d $sec_path ]
		#�����ڸ�Ŀ¼
		then
			echo "**********************************************"
			echo "[ERR]please get the CodeSign4SecureBoot first"
			echo "**********************************************"
			return
		#���ڸ�Ŀ¼
		fi
			#�ж��Ǻ�������������Ӷ�ִ����ر�������ָ��
                if [ "$1" = "SCP_1GDDR" ]
                then
                	make itop_4412_android_config_scp_1GDDR

                elif [ "$1" = "SCP_2GDDR" ]
                then
                       make itop_4412_android_config_scp_2GDDR

                elif [ "$1" = "POP_1GDDR" ]
                then
                       make itop_4412_android_config_pop_1GDDR

                elif [ "$1" = "POP_2GDDR" ]
                then
                       make itop_4412_android_config_pop_2GDDR

                elif [ "$1" = "SCP_1GDDR_Ubuntu" ]	
                then
                       make itop_4412_ubuntu_config_scp_1GDDR

                elif [ "$1" = "SCP_2GDDR_Ubuntu" ]
                then
                       make itop_4412_ubuntu_config_scp_2GDDR

                elif [ "$1" = "POP_1GDDR_Ubuntu" ]
                then
                       make itop_4412_ubuntu_config_pop_1GDDR

                elif [ "$1" = "POP_2GDDR_Ubuntu" ]
                then
                       make itop_4412_ubuntu_config_pop_2GDDR
		fi	
		
		#�ⲿ��ʹ�������ȡ�����cpu���������б���(����ٶ�)
		make -j$CPU_JOB_NUM
		
		#�ж��Ƿ�����ļ�(file)BL2У����ļ�
		if [ ! -f checksum_bl2_14k.bin ]
		then
			echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
			echo "There are some error(s) while building uboot, please use command make to check."
			echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
			exit 0
		fi
		
		#����BL2У����ļ���u-boot�ļ�
		cp -rf checksum_bl2_14k.bin $sec_path
		cp -rf u-boot.bin $sec_path
		#ɾ��BL2У����ļ�
		rm checksum_bl2_14k.bin
		
		#���밲ȫ�����ļ�Ŀ¼
		cd $sec_path
		#./codesigner_v21 -v2.1 checksum_bl2_14k.bin BL2.bin.signed.4412 Exynos4412_V21.prv -STAGE2
		
		#gernerate the uboot bin file support trust zone
		#cat E4412.S.BL1.SSCR.EVT1.1.bin E4412.BL2.TZ.SSCR.EVT1.1.bin all00_padding.bin u-boot.bin E4412.TZ.SSCR.EVT1.1.bin > u-boot-iTOP-4412.bin
		#���ݺ��İ����ͣ��������������ļ��������� BL1+BL2+padding+u-boou.bin+TZSW = u-boot-iTOP-4412.bin

                if  [ "$CoreBoard_type" = "SCP" ]
                then
		        cat E4412_N.bl1.SCP2G.bin bl2.bin all00_padding.bin u-boot.bin tzsw_SMDK4412_SCP_2GB.bin > u-boot-iTOP-4412.bin

                elif [ "$CoreBoard_type" = "POP" ]
                then
                   cat E4412.S.BL1.SSCR.EVT1.1.bin E4412.BL2.TZ.SSCR.EVT1.1.bin all00_padding.bin u-boot.bin E4412.TZ.SSCR.EVT1.1.bin > u-boot-iTOP-4412.bin

                elif [ "$CoreBoard_type" = "POP2G"  ]
                then
                   cat bl2.bin u-boot.bin E4412.TZ.SSCR.EVT1.1.bin > u-boot-iTOP-4412.bin

                else
                   echo  "make uboot image error......" 
                fi
		#�ƶ�u-boot-iTOP-4412.bin�ļ���ubootĿ¼��
		mv u-boot-iTOP-4412.bin $ROOT_DIR
		
		#�Ƴ�У����ļ���u-boot.bin�ļ�
		rm checksum_bl2_14k.bin
		#rm BL2.bin.signed.4412
		rm u-boot.bin

		echo 
		echo 
		;;
		
esac
