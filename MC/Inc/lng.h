#ifndef _LNG_H
#define _LNG_H

#define psz_savestate	"保存最后路径"
#define psz_backexit	"回到根目录退出"
#define psz_sconchk		"标示后下移光标"
#define psz_loopnav		"允许光标循环"

#define psz_scspeed		"长文件名滚动速度"
#define psz_scwait		"滚动等待时间"
#define psz_useboldf	"使用加粗字体"

#define psz_loadicons	"载入mcfileico.cfg"
#define psz_loadkeys	"载入mckeys.cfg"
#define psz_loadmui		"载入default.mclg"
#define psz_loadcs		"载入default.mccs"
#define psz_configpath	"mcconfig.cfg路径"

#define psz_showhiddrv	"显示隐藏磁盘"
#define psz_showmmc		"显示MMC"
#define psz_showhidden	"显示隐藏文件"
#define psz_showsystem	"显示系统文件"

#define psz_confirmexit	"退出"
#define psz_confirmdel	"删除"
#define psz_confirmdelr	"删除只读"
#define psz_confirmcopy	"复制"
#define psz_confirmmove	"移动"
#define psz_confirmrepl	"替换"

#define psz_autoexit_after			"自动退出(min)"
#define psz_autoexit_on_background	"后台自动退出"

#define psz_zip_enable		"ZIP支持"
#define psz_zip_detect_by	"检测zip通过"
#define psz_temppath		"ZIP缓存"
#define psz_cleartemp		"退出删除缓存文件"

#define psz_about		"mc v"version" \n(c) 2007 weclnt, greengo7\nThanks for efficient advices: Aru55, 1nvisible, captain_SISka"

#define psz_no			"否"
#define psz_yes			"是"

#define psz_content		"文件内容"
#define psz_extension	"扩展名"

#define psz_drv_0		"Data"
#define psz_drv_1		"Cache"
#define psz_drv_2		"Config"
#define psz_drv_4		"MMC"

#define psz_mcvol		"MC"
#define psz_zipvol		"ZIP"

#define psz_errfile		"?"

#define psz_sm_common	"常规"
#define psz_sm_confirms	"提示"
#define psz_sm_configs	"配置"
#define psz_sm_disks	"文件和磁盘"
#define psz_sm_gui		"界面"
#define psz_sm_autoexit	"自动退出"
#define psz_sm_zip		"Zip支持"


#define sz_no			"否"
#define sz_yes			"是"

#define sz_byte			"B"
#define sz_kbyte		"KB"
#define sz_mbyte		"MB"

#define sz_reconfig		"MC配置更新!"
#define sz_lng			"语言"
#define sz_lngname		"简体中文"

#define sz_dirmking		"正在创建文件夹"
#define sz_copying		"正在复制"
#define sz_moveing		"正在移动"
#define sz_deling		"正在删除"

#define sz_mcmenu		"MC菜单"
#define sz_select		"选择"
#define sz_back			"返回"

#define sz_open			"打开"
#define sz_file_m		"文件..."
#define sz_chk				"标示/取消标示"
#define sz_chkall			"标示所有"
#define sz_invchk			"取消所有标示"
#define sz_unchall			"反标示所有"
#define sz_oper_m		"操作..."
#define sz_past				"粘贴"
#define sz_cancel			"取消"
#define sz_copy				"复制"
#define sz_move				"移动"
#define sz_del				"删除"
#define sz_rename			"重命名"
#define sz_newdir			"新建文件夹"
#define sz_newfile			"新建文件"
#define sz_prop			"属性"
#define sz_view_m		"查看..."
#define sz_sort_m			"排序..."
#define sz_sortn				"文件名"
#define sz_sorte				"类型"
#define sz_sorts				"大小"
#define sz_sortd				"时间"
#define sz_sortr				"反向排序"
#define sz_filter			"过滤"
#define sz_refresh			"刷新"
#define sz_misc_m		"其它..."
#define sz_bm_m				"快捷方式..."
#define sz_add					"添加"
#define sz_bml					"列表"
#define sz_drvinf			"磁盘信息"
#define sz_settings			"选项设置"
#define sz_about_m			"关于ELF..."
#define sz_exit			"退出"

#define sz_bm			"快捷方式"

#define sz_name			"名称"
#define sz_fullname		"全名"
#define sz_size			"大小"
#define sz_global		"全部"
#define sz_folders		"文件夹"
#define sz_files		"文件数"
#define sz_date			"创建日期"
#define sz_attr			"属性"
#define sz_readonly		"只读"
#define sz_hidden		"隐藏"
#define sz_system		"系统"
#define sz_arh			"存档"
#define sz_subdirs		"子目录相同属性"
#define sz_ncsize		"未压缩"
#define sz_csize		"已压缩"
#define sz_cglobal		"全部已压缩"

#define sz_pmt_del		"删除?"
#define sz_pmt_rodel	"文件%s为只读.删除?"
#define sz_pmt_copy		"复制?"
#define sz_pmt_move		"移动?"
#define sz_pmt_stop		"暂停?"
#define sz_pmt_cancel	"取消?"
#define sz_pmt_exists	"文件已存在,替换? "
#define sz_pmt_exit		"退出MC?"
#define sz_pmt_impcs	"应用皮肤?"
#define sz_pmt_implg	"应用语言包?"

#define sz_err_attrset		"设置属性出错!"
#define sz_err_makedir		"创建文件夹出错!"
#define sz_err_rename		"重命名出错!"
#define sz_err_delete		"删除出错!"
#define sz_err_badname_t	"错误的文件名: %t"
#define sz_err_baddrv_t		"错误的磁盘! %t"
#define sz_err_resnok		"执行错误!"
#define sz_err_nofiles		"没有文件!"
#define sz_err_badname		"错误的文件名!"
#define sz_err_badkey		"按键配置错误!"
#define sz_err_badformat	"格式错误或文件已经损坏!"
#define sz_err_nomemory		"内存已耗尽!"
#define sz_err_makefile		"创建文件出错!"
#define sz_err_ziperr		"ZIP出错: %d/%t!"

#define sz_msg_zreading			"正在读取..."
#define sz_msg_showhid_files	"显示隐藏文件"
#define sz_msg_showsys_files	"显示系统文件"
#define sz_msg_showhidsys_files	"显示系统隐藏文件"
#define sz_msg_showhid_drv		"显示隐藏磁盘"

#endif
