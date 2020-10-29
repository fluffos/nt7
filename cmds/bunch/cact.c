// cact.c
// 一个动作函数只能由一个唯一的动词引导
// 要不分析命令阵列太麻烦，也没什么实际意义。
// by Find.

#include <ansi.h>
#include <bunch.h>

protected void decide_action_do(string str, object who, object env, mixed *acts);
protected void delete_action(string str, object who, object env, mixed *acts);
protected void set_action_verb(string str, object who, object env, mixed *acts);
protected void select_action_class(string str, object who, object env, string verb);
protected void move_get_limit(string str, object who, object env, string verb, mapping actarg, mapping exits);
protected void move_get_arg(string str, object who, object env, string verb, mapping actarg, mapping exits);
protected void move_get_fail_msg(string str, object who, object env, string verb, mapping actarg, mapping exits);
protected void move_get_dest(string str, object who, object env, string verb, mapping actarg, mapping exits);
protected void move_get_here_msg(string str, object who, object env, string verb, mapping actarg, mapping exits, string dir);
protected void move_get_dest_msg(string str, object who, object env, string verb, mapping actarg, mapping exits, string dir);

protected string list_msg(mixed * acts)
{
	string *cmds = ({});
	int n;

	if(!n = sizeof(acts))
		return "";

	for(int i=0;i<n;i++)
		cmds += ({ acts[i][0] });

	return implode(cmds, ",") + "\n";
}

int main(object me, string arg)
{
	object env;
	mixed *acts;
	string out;
	int n;

	if(!me || (me != this_player(1)) || !objectp(env = environment(me)))
		return 0;

	seteuid(getuid(this_object()));

	if(!BUNCH_D->valid_modify_room(me, env))
		return 0;

	acts = filter_array(me->query_commands(), (: $1[2] == $(env) :));

	if(!n = sizeof(acts))
	{
		tell_object(me, "请设你要加入动作的动词[3-10英文字母](q 退出)：\n");
		input_to( (: set_action_verb :), me, env, acts);
		return 1;
	}

	out = "目前此地已经定义的动作：\n";

	out += list_msg(acts);

	out += "请选择操作：\n(1). 删除一个动作。\n";

	if(n < max_action_per_room)
		out += "(2). 加入一个动作。\n(q). 退出：";
	else
		out += "(q). 退出：";

	write(out);
	input_to((: decide_action_do :), me, env, acts);
	return 1;
}

protected void decide_action_do(string str, object who, object env, mixed *acts)
{
	string out;

	if(!who || !env)
		return;

	if( sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')) )
	{
		tell_object(who,"ok.\n");
		return;
	}

	if(sizeof(str) && (str[0] == '1'))	// 删除
	{
		tell_object(who, "请输入欲删除动作的动词(q 退出)：\n");
		input_to( (: delete_action :), who, env, acts);
		return;
	}

	if(sizeof(str) && (str[0] == '2'))
	{
		if(sizeof(acts) >= max_action_per_room)
		{
			tell_object(who, sprintf("这里已经设定了%s个动作，不能再设定了。\n非法操作错误。\n", chinese_number(max_action_per_room)));
			return;
		}
		tell_object(who, "请设你要加入动作的动词[3-10英文字母](q 退出)：\n");
		input_to( (: set_action_verb :), who, env, acts);
		return;
	}

	out = "目前此地已经定义的动作：\n";

	out += list_msg(acts);

	out += "请选择操作：\n(1). 删除一个动作。\n";

	if(sizeof(acts) < max_action_per_room)
		out += "(2). 加入一个动作。\n(q). 退出：";
	else
		out += "(q). 退出：";

	input_to((: decide_action_do :), who, env, acts);
}

// 删除动作
protected void delete_action(string str, object who, object env, mixed *acts)
{
	string func, fname, content, f_sect, m_sect, e_sect, result, sf_sect, se_sect;
	int i, n;

	if(!who || !env)
		return;

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(who, "请输入欲删除动作的动词(q 退出)：\n");
		input_to( (: delete_action :), who, env, acts);
		return;
	}

	if(!n = sizeof(acts))
	{
		tell_object(who, "此地没有定义任何动作。\n异常错误。\n");
		return;
	}

	if((str[0] == 'q') || (str[0] == 'Q'))
	{
		tell_object(who,"ok.\n");
		return;
	}

	for(i=0;i<n;i++)
	{
		if(acts[i][0] == str)
		{
			func = acts[i][3];
			break;
		}
	}

	if(!func)
	{
		tell_object(who, "此地没有定义这个动作。\n");
		return;
	}

	if(environment(who) != env)
	{
		tell_object(who, "你的位置发生了变化，修改被停止。\n");
		return;
	}

	if(!content = read_file(fname = base_name(env) +".c"))
	{
		tell_object(who, "无法读入档案文件。\n");
		return;
	}

	if(!BUNCH_D->parse_function_body(ref content, "int", func, ref f_sect, ref m_sect, ref e_sect, 1))
	{
		tell_object(who, "无法剖析目的房间档案，修改被停止。\n");
		return;
	}

	content = sprintf("%s\n%s\n", f_sect, e_sect);

	if(!BUNCH_D->parse_function_body(ref content, "void", "init", ref f_sect, ref m_sect, ref e_sect, 0))
	{
		tell_object(who, "无法剖析目的房间档案(2)，修改被停止。\n");
		return;
	}

	if(!BUNCH_D->parse_set_value(ref m_sect, func, ref sf_sect, ref se_sect, "add_action"))
	{
		tell_object(who, "无法剖析目的房间档案(3)，修改被停止。\n");
		return;
	}

	if((sf_sect == "") && (se_sect == ""))
	{
		content = sprintf("%s\n%s\n", f_sect, e_sect);
		if(!BUNCH_D->parse_function_body(ref content, "void", "init", ref f_sect, ref m_sect, ref e_sect, 1))
		{
			tell_object(who, "无法剖析目的房间档案(2)，修改被停止。\n");
			return;
		}

		content = sprintf("%s\n%s\n", f_sect, e_sect);
	}
	else
		content = sprintf("%s\n%s%s%s\n",
			f_sect, sf_sect==""?"":sf_sect+"\n",
			se_sect==""?"":se_sect+"\n", e_sect);

	if(!BUNCH_D->parse_set_value(ref content, sprintf("%s_action_func", str), ref f_sect, ref e_sect))
	{
		tell_object(who, "无法剖析目的房间档案(4)，修改被停止。\n");
		return;
	}

	result = sprintf("// Room: %s\n\n%s\n%s\n", fname, f_sect, e_sect);

	if(!write_file(fname, result, 1))
	{
		tell_object(who, "无法写入文件内容，修改失败。\n");
		return;
	}

	if( !BUNCH_D->update_room(env) )
	{
		tell_object(who, "无法载入房间，修改失败。\n");
		return;
	}

	tell_object(who, "删除成功。\n");
}

// 增加 move 类动作
protected void set_action_verb(string str, object who, object env, mixed *acts)
{
	if(!who || !env)
		return;

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(who, "请设你要加入动作的动词[3-10英文字母](q 退出)：\n");
		input_to( (: set_action_verb :), who, env, acts);
	}

	if(!regexp(str, "^[a-z]+$"))
	{
		tell_object(who, "动作的动词只能用小写英文字母。\n操作被终止。\n");
		return;
	}

	if((str[0] == 'q') || (str[0] == 'Q'))
	{
		tell_object(who,"ok.\n");
		return;
	}

	if((sizeof(str) < 3) || (sizeof(str) > 10))
	{
		tell_object(who, "动作的动词只能3-10个英文字母。\n操作被终止。\n");
		return;
	}

	if(sizeof(acts))
	{
		for(int i=0;i<sizeof(acts);i++)
			if(acts[i][0] == str)
			{
				tell_object(who, "这个动词已经在这里存在了。\n非法操作。\n");
				return;
			}
	}

	tell_object(who, "可设定的动作类型：
  1. 移动类动作。
  2. 开出口类动作
  3. 发现物品类动作
请选择(q 退出)：\n");

	input_to((: select_action_class :), who, env, str);
}

protected void select_action_class(string str, object who, object env, string verb)
{
	mapping actarg;
	string id;

	if(!who || !env)
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!id = who->query_banghui_id())
	{
		tell_object(who, "你的帮派记录错乱。\n修改失败。\n");
		return;
	}

	if(sizeof(str) && (str[0] == '1'))	// 移动类
	{
		mapping exits;

		if(!env = BUNCH_D->update_room(env))
		{
			tell_object(who, "无法载入当前房间。\n操作失败。\n");
			return;
		}

		if(!mapp(exits = env->query("exits")) || !sizeof(exits))
		{
			tell_object(who, "当前房间没有出口连向其他的房间。\n没有可设定移动的出口。\n");
			return;
		}
		actarg = allocate_mapping(8);
		actarg["action_class"] = "move";
		actarg["banghui_id"] = id;
		tell_object(who, "对可以使用此动作人的限制：
  1. 只有本帮派的人可以。
  2. 任何人都可以。
请选择(q 退出)：
");
		input_to((: move_get_limit :), who, env, verb, actarg, exits);
		return;
	}

	if(sizeof(str) && (str[0] == '2'))	// 开出口
	{
		mapping exits;

		if(!env = BUNCH_D->update_room(env))
		{
			tell_object(who, "无法载入当前房间。\n操作失败。\n");
			return;
		}

		if(!mapp(exits = env->query("exits")) || !sizeof(exits))
		{
			tell_object(who, "当前房间没有出口连向其他的房间。\n没有可设定移动的出口。\n");
			return;
		}
		tell_object(who, "目前不行。\n");
		return;
	}

	if(sizeof(str) && (str[0] == '3'))	// 找到物品
	{
		tell_object(who, "目前不行。\n");
		return;
	}

	tell_object(who, "可设定的动作类型：
  1. 移动类动作。
  2. 开出口类动作
  3. 发现物品类动作
请选择(q 退出)：\n");

	input_to((: select_action_class :), who, env, str);
}

protected void move_get_limit(string str, object who, object env, string verb, mapping actarg, mapping exits)
{
	if(!who || !env)
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(sizeof(str) && (str[0] == '1'))
	{
		actarg["player_limit"] = 1;
		tell_object(who, "请设定此动作必须的参数：
( 0 没有参数, q 退出)
");
		input_to((: move_get_arg :), who, env, verb, actarg, exits);
		return;
	}

	if(sizeof(str) && (str[0] == '2'))
	{
		actarg["player_limit"] = 2;
		tell_object(who, "请设定此动作必须的参数：
( 0 没有参数, q 退出)
");
		input_to((: move_get_arg :), who, env, verb, actarg, exits);
		return;
	}

	tell_object(who, "对可以使用此动作人的限制：
  1. 只有本帮派的人可以。
  2. 任何人都可以。
请选择(q 退出)：
");
	input_to((: move_get_limit :), who, env, verb, actarg, exits);
}

protected void move_get_arg(string str, object who, object env, string verb, mapping actarg, mapping exits)
{
	if(!who || !env)
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(sizeof(str) && (str[0] == '0'))
	{
		string out = "目前这里的出口：\n";
		actarg["action_arg"] = 0;
		actarg["fail_msg"] = 0;

		foreach(string dir, string dest in exits)
		{
			if(!stringp(dest) || !sizeof(dest))
				continue;
			out += sprintf("  %s 通往 %s\n", dir, explode(dest,"/")[<1]);
		}
		out += "请选择此动作目的地为哪个出口的目的地？(q 退出)：\n";
		tell_object(who, out);
		input_to((: move_get_dest :), who, env, verb, actarg, exits);
		return;
	}

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(who, "请设定此动作必须的参数：
( 0 没有参数, q 退出)
");
		input_to((: move_get_arg :), who, env, verb, actarg, exits);
		return;
	}

	actarg["action_arg"] = str;
	tell_object(who, "请设定没有使用正确的参数的错误提示信息[最多15个汉字]\n请输入(q 退出)：\n");
	input_to((: move_get_fail_msg :), who, env, verb, actarg, exits);
}

protected void move_get_fail_msg(string str, object who, object env, string verb, mapping actarg, mapping exits)
{
	string out;

	if(!who || !env)
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!stringp(str) || !sizeof(str) || (sizeof(str) > 30))
	{
		tell_object(who, "请设定没有使用正确的参数的错误提示信息[最多15个汉字]\n请输入(q 退出)：\n");
		input_to((: move_get_fail_msg :), who, env, verb, actarg, exits);
		return;
	}

	actarg["fail_msg"] = str[<1]=='\n'?str:str+"\n";
	out = "目前这里的出口：\n";
	foreach(string dir, string dest in exits)
	{
		if(!stringp(dest) || !sizeof(dest))
			continue;
		out += sprintf("  %s 通往 %s\n", dir, explode(dest,"/")[<1]);
	}
	out += "请选择此动作目的地为哪个出口的目的地？(q 退出)：\n";
	tell_object(who, out);
	input_to((: move_get_dest :), who, env, verb, actarg, exits);
}

protected void move_get_dest(string str, object who, object env, string verb, mapping actarg, mapping exits)
{
	if(!who || !env)
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}
	
	if(!stringp(str) || !sizeof(str))
	{
		string out;

		out = "目前这里的出口：\n";
		foreach(string dir, string dest in exits)
		{
			if(!stringp(dest) || !sizeof(dest))
				continue;
			out += sprintf("  %s 通往 %s\n", dir, explode(dest,"/")[<1]);
		}
		out += "请选择此动作目的地为哪个出口的目的地？(q 退出)：\n";
		tell_object(who, out);
		input_to((: move_get_dest :), who, env, verb, actarg, exits);
		return;
	}

	if(undefinedp(exits[str]))
	{
		tell_object(who, "没有这个出口。\n操作失败。\n");
		return;
	}

	if(!in_same_dir(base_name(env), exits[str]))
	{
		tell_object(who, "你没有修改目的档案的权利。\n修改失败。\n");
		return;
	}

	actarg["move_dest"] = exits[str];
	tell_object(who, "请设定动作人离开这个房间的信息['$N' 代表动作人](q 退出)：\n");

	input_to((: move_get_here_msg :), who, env, verb, actarg, exits, str);
}

protected void move_get_here_msg(string str, object who, object env, string verb, mapping actarg, mapping exits, string dir)
{
	if(!who || !env)
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!stringp(str) || (sizeof(str) < 10))
	{
		tell_object(who, "<显示信息至少要有 5 个汉字长>\n请设定动作人离开这个房间的信息['$N' 代表动作人](q 退出)：\n");
		input_to((: move_get_here_msg :), who, env, verb, actarg, exits, dir);
		return;
	}


	if(sizeof(str) > 50)
	{
		tell_object(who, "<显示信息不能超过 25 个汉字长>\n请设定动作人离开这个房间的信息['$N' 代表动作人](q 退出)：\n");
		input_to((: move_get_here_msg :), who, env, verb, actarg, exits, dir);
		return;
	}

	actarg["here_msg"] = str[<1]=='\n'?str:str+"\n";

	tell_object(who, "请设定动作人到达目的房间的信息['$N' 代表动作人](q 退出)：\n");

	input_to((: move_get_dest_msg :), who, env, verb, actarg, exits, dir);
}

protected void move_get_dest_msg(string str, object who, object env, string verb, mapping actarg, mapping exits, string dir)
{
	string adac_str, func_str, fname, content, result, f_sect, m_sect, e_sect;

	if(!who || !env)
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!stringp(str) || (sizeof(str) < 10))
	{
		tell_object(who, "<显示信息至少要有 5 个汉字长>\n请设定动作人到达目的房间的信息['$N' 代表动作人](q 退出)：\n");
		input_to((: move_get_here_msg :), who, env, verb, actarg, exits, dir);
		return;
	}


	if(sizeof(str) > 50)
	{
		tell_object(who, "<显示信息不能超过 25 个汉字长>\n请设定动作人到达目的房间的信息['$N' 代表动作人](q 退出)：\n");
		input_to((: move_get_here_msg :), who, env, verb, actarg, exits, dir);
		return;
	}

	actarg["dest_msg"] = str[<1]=='\n'?str:str+"\n";

	if(environment(who) != env)
	{
		tell_object(who, "你的位置发生了变化，操作终止。\n");
		return;
	}

	adac_str = sprintf("\tadd_action(\"%s_action_func\", \"%s\");", verb, verb);
	func_str = sprintf("int %s_action_func(string arg)
{
	object me = this_player();
	mapping act_arg;
	if(!mapp(act_arg = query(\"%s_action_func\")) || !sizeof(act_arg))
		return notify_fail(\"出现错误。\n\");
	if( (act_arg[\"player_limit\"] == 1)
	&& (me->query_banghui_id() != act_arg[\"banghui_id\"]) )
		return 0;
	if(act_arg[\"action_arg\"] && (arg != act_arg[\"action_arg\"]))
	{
		write(act_arg[\"fail_msg\"]);
		return 1;
	}
	message_vision(act_arg[\"here_msg\"], me);
	if(!me->move(act_arg[\"move_dest\"]))
		return notify_fail(\"过不去。\n\");
	message_vision(act_arg[\"dest_msg\"], me);
	return 1;
}", verb, verb);

	if(!content = read_file(fname = base_name(env) + ".c"))
	{
		tell_object(who, "无法读取档案内容。\n操作失败。\n");
		return;
	}

	if(!BUNCH_D->parse_function_body(ref content, "void", "init", ref f_sect, ref m_sect, ref e_sect, 0))
	{
		if(!BUNCH_D->parse_function_body(ref content, "void", "create", ref f_sect, ref m_sect, ref e_sect, 0))
		{
			tell_object(who, "无法剖析文件内容，修改失败。\n");
			return;
		}

		result = sprintf("// Room: %s\n\n%s\n\tset(\"%s_action_func\", %O);\n%s\n%s\nvoid init()\n{\n%s\n}\n%s\n",
			fname, f_sect, verb, actarg, m_sect, e_sect, adac_str, func_str);
	}
	else
	{
		content = sprintf("%s\n%s\n%s\n%s\n", f_sect, adac_str, m_sect, e_sect);
		if(!BUNCH_D->parse_function_body(ref content, "void", "create", ref f_sect, ref m_sect, ref e_sect, 0))
		{
			tell_object(who, "无法剖析文件内容，修改失败。\n");
			return;
		}
		result = sprintf("// Room: %s\n\n%s\n\tset(\"%s_action_func\", %O);\n%s\n%s\n%s\n",
			fname, f_sect, adac_str, m_sect, e_sect, func_str);
	}

	if(!write_file(fname, result, 1))
	{
		tell_object(who, "无法写入文件内容，修改失败。\n");
		return;
	}

	if( !env = BUNCH_D->update_room(env) )
	{
		tell_object(who, "无法载入房间，修改失败。\n");
		return;
	}

	if(BUNCH_D->break_an_exit(who, env, dir))
		tell_object(who, "动作加入成功。\n");
}

// 开出口类动作
