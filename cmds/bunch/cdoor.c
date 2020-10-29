// cdoor.c

#include <ansi.h>
#include <bunch.h>

protected void decide_action_do(string str, object who, object env, string *ye, string *yd);
protected void get_door_cname(string str, object who, object env, string *ye, string *yd);
protected void add_door(string str, object who, object env, string *ye, string *yd, string cname);
protected void del_door(string str, object who, object env, string *ye, string *yd);

int main(object me, string arg)
{
	mapping exits, doors;
	object env;
	string out, *yd, *ye;

	if(!me || (me != this_player(1)) || !objectp(env = environment(me)))
		return 0;

	seteuid(getuid(this_object()));

	if(!BUNCH_D->valid_modify_room(me, env))
		return 0;

	exits = env->query("exits");

	if(!mapp(exits) || !sizeof(exits))
		return notify_fail("这里没有可用于创建门的出口。\n");

	ye = keys(exits);

	if(!mapp(doors = env->query_doors()) || !sizeof(doors))
	{
		out = sprintf("这里可用于创建门的出口有：\n%s\n请设定欲创建门的中文名[1-5个汉字](q 退出)：\n",
			implode(ye,",") );
		write(out);
		input_to( (: get_door_cname :), me, env, ye, yd);
		return 1;
	}

	yd = keys(doors);
	out = "这里的出口情况：\n";

	foreach(string tmp in ye)
		out += sprintf("  %s%s\n", tmp, (member_array(tmp,yd) == -1)?"":" [有门]");

	out += "请选择操作：\n(1). 删除一扇门。\n";
	if(sizeof(ye) > sizeof(yd))
		out += "(2). 创建一扇门。\n";

	out += "(q). 退出。\n";

	write(out);
	input_to( (: decide_action_do :), me, env, ye, yd);
	return 1;
}

protected void decide_action_do(string str, object who, object env, string *ye, string *yd)
{
	string out;

	if( sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')) )
	{
		tell_object(who,"ok.\n");
		return;
	}

	if(sizeof(str) && (str[0] == '1'))	// 删除
	{
		tell_object(who, "请选择删除门的方向(q 退出)：\n");
		input_to( (: del_door :), who, env, ye, yd);
		return;
	}

	if(sizeof(str) && (str[0] == '2'))
	{
		if(sizeof(yd) >= sizeof(ye))
		{
			tell_object(who, "这里已经没有可用于创建门的出口。\n非法操作。\n");
			return;
		}
		tell_object(who, "请设定欲创建门的中文名[1-5个汉字](q 退出)：\n");
		input_to( (: get_door_cname :), who, env, ye, yd);
		return;
	}

	out = "这里的出口情况：\n";

	foreach(string tmp in ye)
		out += sprintf("  %s%s\n", tmp, member_array(tmp,yd) == -1?"":" [有门]");

	out += "请选择操作：\n(1). 删除一扇门。\n";
	if(sizeof(ye) > sizeof(yd))
		out += "(2). 创建一扇门。\n";

	out += "(q). 退出。\n";

	tell_object(who, out);
	input_to( (: decide_action_do :), who, env, ye, yd);
}

protected void get_door_cname(string str, object who, object env, string *ye, string *yd)
{
	int l;

	if(!who || !env)
		return;

	if(!stringp(str) || (str == ""))
	{
		tell_object(who, "请设定欲创建门的中文名[1-5个汉字](q 退出)：\n");
		input_to( (: get_door_cname :), who, env, ye, yd);
		return;
	}

	if( (str[0] == 'q')
	|| (str[0] == 'Q') )
	{
		tell_object(who, "ok.\n");
		return;
	}

	if( ((l = strlen(str)) < 2) || (l > 10) )
	{
		tell_object(who, "门的名称必须为1-5个汉字，输入('q'退出)：\n");
		input_to( (: get_door_cname :), who, env, ye, yd);
		return;
	}

	while(l--)
	{
		int section;

                if( str[l]<128 )
		{
			tell_object(who, "门的名称必须使用中文，输入('q'退出)：\n");
			input_to( (: get_door_cname :), who, env, ye, yd);
			return;
                }

		if( l%2==0 )
		{
			section = str[l] - 160;

			if( (section < 16)
			|| (section > 87) )
			{
				tell_object(who,"\n门的名称必须使用常用「汉字」，输入(q 退出)：\n");
				input_to( (: get_door_cname :), who, env, ye, yd);
				return;
			}
		}
	}

	tell_object(who, "请选择创建门的方向(q 退出)：\n");
	input_to( (: add_door :), who, env, ye, yd, str);
}

protected void add_door(string str, object who, object env, string *ye, string *yd, string cname)
{
	object dest;
	string fname, content, dstr, f_sect, e_sect, m_sect, result;
	string dfname, dcontent, ddstr, df_sect, de_sect, dm_sect, dresult;
	mapping dexits,ddoors;

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(who, "请选择创建门的方向(q 退出)：\n");
		input_to( (: add_door :), who, env, ye, yd, cname);
		return;
	}

	if( (str[0] == 'q') || (str[0] == 'Q') )
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!sizeof(ye) || (member_array(str, ye) == -1))
	{
		tell_object(who, "没有这个出口，选择错误。\n");
		return;
	}

	if(sizeof(yd) && (member_array(str, yd) != -1))
	{
		tell_object(who, "这个方向的出口已经有门，选择错误。\n");
		return;
	}

	if(undefinedp(r_dir[str]))
	{
		tell_object(who, "这个出口为非标准出口，不能创建门。\n");
		return;
	}

	if(environment(who) != env)
	{
		tell_object(who, "你的位置发生了变化，修改被停止。\n");
		return;
	}

	if(!dfname = env->query("exits/"+str))
	{
		tell_object(who, "出口记录有错误，修改被停止。\n");
		return;
	}

	if(!objectp(dest = find_object(dfname)))
		dest = load_object(dfname);
	if(!dest)
	{
		tell_object(who, "无法载入目的房间，修改被停止。\n");
		return;
	}

	if(!mapp(dexits = dest->query("exits")) || !sizeof(dexits) || undefinedp(dexits[r_dir[str]]))
	{
		tell_object(who, "目的房间出口出现错误，修改被停止。\n");
		return;
	}

	fname = base_name(env);
	if(dexits[r_dir[str]] != fname)
	{
		tell_object(who, "目的房间的对应出口错误，修改被停止。\n");
		return;
	}

	if(!in_same_dir(fname, dfname))
	{
		tell_object(who, "你没有权利修改目的房间。\n修改失败。\n");
		return;
	}

	if(mapp(ddoors = dest->query_doors()) && !undefinedp(ddoors[r_dir[str]]))
	{
		tell_object(who, "目的房间在对应出口上已有门，修改被停止。\n");
		return;
	}

	dfname += ".c";

	if(!(dcontent = read_file(dfname)))
	{
		tell_object(who, "无法读入目的房间档案，修改被停止。\n");
		return;
	}

	if(!BUNCH_D->parse_function_body(ref dcontent, "void", "create", ref df_sect, ref dm_sect, ref de_sect, 0))
	{
		tell_object(who, "无法剖析目的房间档案，修改被停止。\n");
		return;
	}

	fname += ".c";

	if(!(content = read_file(fname)))
	{
		tell_object(who, "无法读入房间档案，修改被停止。\n");
		return;
	}

	if(!BUNCH_D->parse_function_body(ref content, "void", "create", ref f_sect, ref m_sect, ref e_sect, 0))
	{
		tell_object(who, "无法剖析房间档案，修改被停止。\n");
		return;
	}

	dstr = sprintf("\tcreate_door(\"%s\", \"%s\", \"%s\", DOOR_CLOSED);",
		str, cname, r_dir[str]);

	ddstr = sprintf("\tcreate_door(\"%s\", \"%s\", \"%s\", DOOR_CLOSED);",
		r_dir[str], cname, str);

	result = sprintf("// Room: %s\n\n", fname);
	if(!BUNCH_D->check_include(ref f_sect, "<room.h>"))
		result += "#include <room.h>\n";

	result += sprintf("%s\n%s\n%s\n%s\n",f_sect, m_sect, dstr, e_sect);

	dresult = sprintf("// Room: %s\n\n", dfname);
	if(!BUNCH_D->check_include(ref df_sect, "<room.h>"))
		dresult += "#include <room.h>\n";

	dresult += sprintf("%s\n%s\n%s\n%s\n",df_sect, dm_sect, ddstr, de_sect);

	if(!write_file(dfname, dresult, 1))
	{
		tell_object(who, "无法写入目的房间档案，操作失败。\n");
		return;
	}

	if(!write_file(fname, result, 1))
	{
		tell_object(who, "无法写入房间档案，操作失败。\n");
		return;
	}

	if( !BUNCH_D->update_room(env) )
	{
		tell_object(who, "无法载入房间，修改失败。\n");
		return;
	}

	if( !BUNCH_D->update_room(dest) )
	{
		tell_object(who, "无法载入目的房间，修改失败。\n");
		return;
	}

	tell_object(who, sprintf("%s创建成功。\n", cname));
}

protected void del_door(string str, object who, object env, string *ye, string *yd)
{
	object dest;
	string fname, content, f_sect, e_sect, result;
	string dfname, dcontent, df_sect, de_sect, dresult;
	mapping dexits;

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(who, "请选择删除门的方向(q 退出)：\n");
		input_to( (: del_door :), who, env, ye, yd);
		return;
	}

	if( (str[0] == 'q') || (str[0] == 'Q') )
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!sizeof(ye) || (member_array(str, ye) == -1))
	{
		tell_object(who,"这个方向没有出口，修失败。\n");
		return;
	}

	if(!sizeof(yd) || (member_array(str, yd) == -1))
	{
		tell_object(who,"这个方向没有门，修失败。\n");
		return;
	}

	if(environment(who) != env)
	{
		tell_object(who, "你的位置发生了变化，修改被停止。\n");
		return;
	}

	if(undefinedp(r_dir[str]))
	{
		tell_object(who, "这个出口为非标准出口，不能修改。\n");
		return;
	}

	if(!dfname = env->query("exits/" + str))
	{
		tell_object(who, "出口记录有错误，修改被停止。\n");
		return;
	}

	if(!objectp(dest = find_object(dfname)))
		dest = load_object(dfname);
	if(!dest)
	{
		tell_object(who, "无法载入目的房间，修改被停止。\n");
		return;
	}

	if(!mapp(dexits = dest->query("exits")) || !sizeof(dexits) || undefinedp(dexits[r_dir[str]]))
	{
		tell_object(who, "目的房间出口出现错误，修改被停止。\n");
		return;
	}

	fname = base_name(env);
	if(dexits[r_dir[str]] != fname)
	{
		tell_object(who, "目的房间的对应出口错误，修改被停止。\n");
		return;
	}

	if(!in_same_dir(fname, dfname))
	{
		tell_object(who, "你没有权利修改目的房间。\n修改失败。\n");
		return;
	}

	dfname += ".c";

	if(!dcontent = read_file(dfname))
	{
		tell_object(who, "无法读入目的档案文件，修改失败。\n");
		return;
	}

	if(!BUNCH_D->parse_set_value(ref dcontent, r_dir[str], ref df_sect, ref de_sect, "create_door"))
	{
		tell_object(who, "无法剖析目的档案文件，修改失败。\n");
		return;
	}

	dresult = sprintf("// Room: %s\n\n%s\n%s\n", dfname, df_sect, de_sect);

	fname += ".c";

	if(!content = read_file(fname))
	{
		tell_object(who, "无法读入档案文件，修改失败。\n");
		return;
	}

	if(!BUNCH_D->parse_set_value(ref content, str, ref f_sect, ref e_sect, "create_door"))
	{
		tell_object(who, "无法剖析档案文件，修改失败。\n");
		return;
	}

	result = sprintf("// Room: %s\n\n%s\n%s\n", fname, f_sect, e_sect);

	if(!write_file(dfname, dresult, 1))
	{
		tell_object(who, "无法写入目的房间档案，操作失败。\n");
		return;
	}

	if(!write_file(fname, result, 1))
	{
		tell_object(who, "无法写入房间档案，操作失败。\n");
		return;
	}

	if( !BUNCH_D->update_room(env) )
	{
		tell_object(who, "无法载入房间，修改失败。\n");
		return;
	}

	if( !BUNCH_D->update_room(dest) )
	{
		tell_object(who, "无法载入目的房间，修改失败。\n");
		return;
	}

	tell_object(who, "删除成功。\n");
}
