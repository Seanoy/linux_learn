#!/bin/sh
#上面这句话用于指定脚本的解释器路径

#$1代表传入的第一个参数，（$0表示脚本文件名）-z是判断后面的参数是否为零
if [ -z $1 ]
then	
#如果无传入参数，则输出错误信息并退出脚本
   echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
   echo "Please use correct make config.for example make SCP_1GDDR for SCP 1G DDR CoreBoard linux,android OS"
   echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
   exit 0
fi
#如果输入参数$1的值是字符串"SCP_1GDDR"|"SCP_2GDDR"|"SCP_1GDDR_Ubuntu"|"SCP_2GDDR_Ubuntu"则执行下一步
if   [ "$1" = "SCP_1GDDR" ] ||   [ "$1" = "SCP_2GDDR" ] || [ "$1" = "SCP_1GDDR_Ubuntu" ] ||   [ "$1" = "SCP_2GDDR_Ubuntu" ]
then 
	#根据传入参数设置对应的sec路径和核心板类型，这部分程序是三星提供的加密相关的文件
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

#获取CPU的核心数
#指令grep processor /proc/cpuinfo 输出
#processor	: 0
#processor	: 1
#processor	: 2
#processor	: 3
#$NF表示最后一个列（field），即输出最后一个字段的内容，即field=3，然后打印field+1
CPU_JOB_NUM=$(grep processor /proc/cpuinfo | awk '{field=$NF};END{print field+1}')
#获取当前目录
ROOT_DIR=$(pwd)
# '##*/'指的是ROOT_DIR目录最右面的/，即当前路径名。 另外'#/'指的是最左面的/
CUR_DIR=${ROOT_DIR##*/}


#清除所有生成的文件
make distclean

#删除板子和CPU相关的链接文件
rm ${ROOT_DIR}/board/samsung/smdkc210/lowlevel_init.S	
rm ${ROOT_DIR}/cpu/arm_cortexa9/s5pc210/cpu_init.S

#判断传入参数$1是哪种情况
case "$1" in
#执行清除指令
	clean)
		#删除大多数的编译生成文件，但是会保留内核的配置文件.config
		echo make clean
		#删除所有的编译生成文件、内核配置文件(.config文件)和各种备份文件
		make mrproper
		;;
#除了clean以外	
	*)
		#判断是否存在三星提供的加密解密目录(directory)$sec_path
		if [ ! -d $sec_path ]
		#不存在该目录
		then
			echo "**********************************************"
			echo "[ERR]please get the CodeSign4SecureBoot first"
			echo "**********************************************"
			return
		#存在该目录
		fi
			#判断是何种输入参数，从而执行相关编译配置指令
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
		
		#这部分使用上面获取的最大cpu核心数进行编译(最快速度)
		make -j$CPU_JOB_NUM
		
		#判断是否存在文件(file)BL2校验和文件
		if [ ! -f checksum_bl2_14k.bin ]
		then
			echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
			echo "There are some error(s) while building uboot, please use command make to check."
			echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
			exit 0
		fi
		
		#复制BL2校验和文件、u-boot文件
		cp -rf checksum_bl2_14k.bin $sec_path
		cp -rf u-boot.bin $sec_path
		#删除BL2校验和文件
		rm checksum_bl2_14k.bin
		
		#进入安全启动文件目录
		cd $sec_path
		#./codesigner_v21 -v2.1 checksum_bl2_14k.bin BL2.bin.signed.4412 Exynos4412_V21.prv -STAGE2
		
		#gernerate the uboot bin file support trust zone
		#cat E4412.S.BL1.SSCR.EVT1.1.bin E4412.BL2.TZ.SSCR.EVT1.1.bin all00_padding.bin u-boot.bin E4412.TZ.SSCR.EVT1.1.bin > u-boot-iTOP-4412.bin
		#根据核心板类型，将几个二进制文件连接起来 BL1+BL2+padding+u-boou.bin+TZSW = u-boot-iTOP-4412.bin

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
		#移动u-boot-iTOP-4412.bin文件到uboot目录下
		mv u-boot-iTOP-4412.bin $ROOT_DIR
		
		#移除校验和文件和u-boot.bin文件
		rm checksum_bl2_14k.bin
		#rm BL2.bin.signed.4412
		rm u-boot.bin

		echo 
		echo 
		;;
		
esac
