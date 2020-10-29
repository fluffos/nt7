// mroom.c

#include <ansi.h>
#include <bunch.h>

protected void get_room_short(string sdesc, object who, object env, string dir);
protected void get_room_long(string str, object who, object env, string dir, string sdesc, string ldesc);
protected void build_up(object who, object env, string dir, string sdesc, string ldesc, int outdoor);
protected void get_room_outdoor(string str, object who, object env, string dir, string sdesc, string ldesc);

int main(object me, string arg)
{
	object env;

	if(!me || (me != this_player(1)))
		return 0;

	if(!objectp(env = environment(me)))
		return 0;

	seteuid(getuid(this_object()));

	if(!BUNCH_D->valid_modify_room(me, env))
		return 0;

	if(!stringp(arg) || (arg == ""))
		return 0;

	if(undefinedp(r_dir[arg]))
		return notify_fail(sprintf("房间的出口只能从以下方向种选择：\n%s\n",vdirs));

	if(env->query("exits/"+arg) || env->query("hide_exits/"+arg))
		return notify_fail(sprintf("这里已经有了 %s 出口。\n",arg));

	write("请输入新建房间的名称[2-6个汉字]('q'退出)：\n");
	input_to( (: get_room_short :), me, env, arg);

	return 1;
}

protected void get_room_short(string sdesc, object who, object env, string dir)
{
	int l;

	if(!who || !env || !dir)
		return;

	if(!stringp(sdesc) || (sdesc == ""))
	{
		tell_object(who, "请输入新建房间的名称[2-6个汉字]，输入('q'退出)：\n");
		input_to( (: get_room_short :), who, env, dir);
		return;
	}

	if( (sdesc[0] == 'q')
	|| (sdesc[0] == 'Q') )
	{
		tell_object(who, "终止房间创建。\n");
		return;
	}

	if( ((l = strlen(sdesc)) < 4) || (l > 12) )
	{
		tell_object(who, "新建房间的名称必须为2-6个汉字，输入('q'退出)：\n");
		input_to( (: get_room_short :), who, env, dir);
		return;
	}

	while(l--)
	{
		int section;

                if( sdesc[l]<128 )
		{
			tell_object(who, "新建房间的名称必须使用中文，输入('q'退出)：\n");
			input_to( (: get_room_short :), who, env, dir);
			return;
                }

		if( l%2==0 )
		{
			section = sdesc[l] - 160;

			if( (section < 16)
			|| (section > 87) )
			{
				tell_object(who,"\n新建房间的名称必须使用常用「汉字」，输入('q'退出)：\n");
				input_to( (: get_room_short :), who, env, dir);
				return;
			}
		}
	}

	tell_object(who, sprintf("新房间名称为：%s\n请为%s设定描述：
·为了房间的美观，每一行请不要超过%s个中文字
·第一行的内容长度比其它行的长度少两个中文字宽才能对齐
·描述内容不能超过%s行\n请输入('.'结束输入，'q'退出)：\n------------------------------------------------------\n",
		sdesc, sdesc, chinese_number(room_desc_l/2), chinese_number(room_desc_h)));

	input_to( (: get_room_long :), who, env, dir, sdesc, "" );
}

protected void get_room_long(string str, object who, object env, string dir, string sdesc, string ldesc)
{
	if(!who || !env || !dir || !sdesc)
		return;

	if(!stringp(str) || (str == ""))
	{
		input_to( (: get_room_long :), who, env, dir, sdesc, ldesc );
		return;
	}

	if( (str[0] == 'q')
	|| (str[0] == 'Q') )
	{
		tell_object(who, "终止房间创建。\n");
		return;
	}

	if(str[0] == '.')	// 结束输入
	{
		if( (ldesc == "") || (sizeof(ldesc) < 10) )
		{
			tell_object(who, sprintf("你没有为%s的描述设定足够的内容\n房屋创建失败\n", sdesc));
			return;
		}

		if( sizeof(explode(ldesc, "\n")) > room_desc_h)
		{
			tell_object(who, sprintf(HBCYN HIG"·描述内容不能超过%s行\n房屋创建失败。\n"NOR, chinese_number(room_desc_h)));
			return;
		}

		tell_object(who,sprintf("%s是否为户外房间？\n(户外房间可以看到气候变化的描述)\n请选择[y/n](q退出)：", sdesc));
		input_to( (: get_room_outdoor :), who, env, dir, sdesc, ldesc );
		return;
	}

	if(strsrch(str, '\n'))
	{
		int n;
		string *tmp;

		n = sizeof(tmp = explode(str, "\n"));
		for(int i=0; i<n; i++)
			if(strlen(tmp[i]) > room_desc_l)
			{
				tell_object(who, sprintf(HBCYN HIG"每一行不能超过%s个中文字，请重新输入上一次输入的内容：\n"NOR, chinese_number(room_desc_l/2)));
				input_to( (: get_room_long :), who, env, dir, sdesc, ldesc );
				return;
			}

		if((n + sizeof(explode(ldesc, "\n"))) > room_desc_h)
		{
			tell_object(who, sprintf(HBCYN HIG"·描述内容不能超过%s行\n房屋创建失败。\n"NOR, chinese_number(room_desc_h)));
			return;
		}
	}

	else
	{
		if(strlen(str) > room_desc_l)
		{
			tell_object(who, sprintf(HBCYN HIG"每一行不能超过%s个中文字，请重新输入上一次输入的内容：\n"NOR, chinese_number(room_desc_l/2)));
			input_to( (: get_room_long :), who, env, dir, sdesc, ldesc );
			return;
		}

		if( sizeof(explode(ldesc, "\n")) > (room_desc_h -1) )
		{
			tell_object(who, sprintf(HBCYN HIG"·描述内容不能超过%s行\n房屋创建失败。\n"NOR, chinese_number(room_desc_h)));
			return;
		}
	}

	ldesc += str + "\n";
	input_to( (: get_room_long :), who, env, dir, sdesc, ldesc );
}

protected void get_room_outdoor(string str, object who, object env, string dir, string sdesc, string ldesc)
{
	int ot = 0;

	if(!who
	|| !env
	|| !sdesc
	|| !ldesc
	|| !dir )
		return;

	if(stringp(str) && sizeof(str) && ( (str[0] == 'y') || (str[0] == 'Y') ))
		ot = 1;

	build_up(who, env, dir, sdesc, ldesc, ot);
}

// 欲连接的房间必须已存在，并且可以正确载入内存
// 当前房间没有出口的情况不考虑，这在帮派系统中不会出现
protected int add_exit(object room, string link_to, string dir, string room_dir)
{
	string fname, fcn, f_sect, e_sect, m_sect, content, estr;
	mapping exits;

	if(!objectp(room) || !room->is_room())
		return 0;

	fname = base_name(room)+".c";

	if(file_size(fname) <= 0)
		return 0;

	if(file_size(link_to+".c") <= 0)
		return 0;

	if(!fcn = read_file(fname))
		return 0;

	if(!find_object(link_to))
		load_object(link_to);
	if(!find_object(link_to))
		return 0;

	if(!BUNCH_D->parse_set_value(ref fcn, "exits", ref f_sect, ref e_sect))
		return 0;

	exits = room->query("exits");

	if(!mapp(exits) || !sizeof(exits))
		exits = ([ dir : link_to ]);
	else
		exits += ([ dir : link_to ]);

	estr = sprintf("%O", exits);
	estr = replace_string(estr, "\""+room_dir, "__DIR__\"");

	if(!BUNCH_D->parse_set_value(ref fcn, "exits", ref f_sect, ref e_sect))
	{
		if(!BUNCH_D->parse_function_body(ref fcn, "void", "create", ref f_sect, ref m_sect, ref e_sect, 0))
			return 0;
		content = sprintf("// Room: %s\n\n%s\n\tset(\"exits\", %s);\n%s\n%s\n",
			fname, f_sect, estr, m_sect, e_sect);
	}
	else
		content = sprintf("// Room: %s\n\n%s\n\tset(\"exits\", %s);\n%s\n",
			fname, f_sect, estr, e_sect);

	if(!write_file(fname, content, 1))
		return 0;
	if( !BUNCH_D->update_room(room) )
		return 0;
	return 1;
}

protected string valid_room_position(string fname)
{
	int l;
	string *f1, *f2;

	if(!stringp(fname))
		return 0;

	if( strlen(fname) <= (l = strlen(dir_pre)) )
		return 0;

	if(fname[0..l-1] != dir_pre)
		return 0;

	f1 = explode(dir_pre, "/");
	f2 = explode(fname, "/");

	if(sizeof(f2) - sizeof(f1) - 2 != 0)
		return 0;

	return f2[sizeof(f1)];
}

protected void build_up(object who, object env, string dir, string sdesc, string ldesc, int outdoor)
{
	string room_dir,fname,bname,nname, roomtext;
	int number;

	if(!who
	|| !env
	|| !sdesc
	|| !ldesc
	|| !dir
	|| (environment(who) != env))
		return;

	// 确定新房间文件名
	fname = base_name(env);

	if(!bname = who->query_banghui_id())
	{
		tell_object(who, "你的帮派记录错乱。\n修改失败。\n");
		return;
	}

	if(undefinedp(r_dir[dir]))
	{
		tell_object(who, "房间出口选择错误。\n创建房屋失败。\n");
		return;
	}

	room_dir = sprintf("%s%s/", dir_pre, bname);

	number = sizeof(get_dir(room_dir)) + 1;

	while(file_size(nname = sprintf("%s%s_room%d.c", room_dir, bname, number)) > 0)
	{
		number++;
	}

	if(!in_same_dir(fname, nname))
	{
		tell_object(who, "房间目录对应错误。\n修改失败。\n");
		return;
	}

	fname = replace_string(fname, room_dir, "__DIR__\"");
	// 建新房

	roomtext = sprintf("// Room: %s\n\ninherit ROOM;\nvoid create()\n{\n",nname);
	roomtext += sprintf("\tset(\"short\", \"%s\");\n\tset(\"long\", @LONG\n%sLONG\n);\n", sdesc, ldesc);
	roomtext += sprintf("\tset(\"exits\", ([\n\t\"%s\" : %s\",\n]));\n", r_dir[dir], fname);
	if(outdoor)
		roomtext += sprintf("\tset(\"outdoors\", \"%s\");\n", bname);
	roomtext += "\tsetup();\n}\n";

	if(!write_file(nname, roomtext, 1))
	{
		tell_object(who, "保存房屋发生错误。\n创建房屋失败。\n");
		return;
	}

	// 开出口
	if(!add_exit(env, nname[0..<3], dir, room_dir))
	{
		tell_object(who, "无法开辟出口。\n创建房屋失败。\n");
		return;
	}

	tell_object(who, sprintf("%s建造成功。\n",sdesc));
}
