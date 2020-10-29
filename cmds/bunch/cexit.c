// cexit.c

#include <ansi.h>
#include <bunch.h>

protected void decide_action_do(string str, object who, object env, mapping exits);
protected void get_del_dir(string str, object who, object env, mapping exits);
protected void get_add_dir(string str, object who, object env, mapping exits);
protected void do_add_exit(string str, object who, object env, mapping exits, string dir);

int main(object me, string arg)
{
	mapping exits;
	object env;
	string out;

	if(!me || (me != this_player(1)) || !objectp(env = environment(me)))
		return 0;

	seteuid(getuid(this_object()));

	if(!BUNCH_D->valid_modify_room(me, env))
		return 0;

	if( !env = BUNCH_D->update_room(env) )
	{
		tell_object(me, "无法目的载入房间，修改失败。\n");
		return 1;
	}
	exits = env->query("exits");

	if(!exits || !sizeof(exits))
	{
		write("目前这里没有任何出口。\n请输入要加入出口的方向(q 退出)：");
		input_to( (: get_add_dir :), me, env, exits);
		return 1;
	}

	out = "目前这里已存在的出口：\n";

	foreach(string dir, string dest in exits)
	{
		out += sprintf("  %s 通往 %s\n", dir, explode(dest, "/")[<1]);
	}

	out += "请选择你要进行的操作：
(1) 删除一个已存在的出口。\n";

	if(sizeof(exits) >= max_exits)
		out += "(q) 退出。\n";
	else
		out += "(2) 加入一个新出口。\n(q) 退出。\n";

	write(out);
	input_to( (: decide_action_do :), me, env, exits );
	return 1;
}

protected void decide_action_do(string str, object who, object env, mapping exits)
{
	string out;

	if(!objectp(who) || !objectp(env))
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')) )
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(sizeof(str) && (str[0] == '1'))	// 删除
	{
		tell_object(who, "请输入要删除出口的方向(q 退出)：");
		input_to( (: get_del_dir :), who, env, exits);
		return;
	}

	if(sizeof(str) && (str[0] == '2'))	// 加入
	{
		if(mapp(exits) && (sizeof(exits) >= max_exits))
		{
			tell_object(who, sprintf("每个房间最多只能有%s个出口。\n非法操作错误。\n", chinese_number(max_exits)));
			return;
		}
		tell_object(who, "请输入要加入出口的方向(q 退出)：");
		input_to( (: get_add_dir :), who, env, exits);
		return;
	}

	out = "请选择你要进行的操作：\n(1) 删除一个已存在的出口。\n";

	if(mapp(exits) && (sizeof(exits) >= max_exits))
		out += "(q) 退出。\n";
	else
		out += "(2) 加入一个新出口。\n(q) 退出。\n";

	tell_object(who, out);
	input_to( (: decide_action_do :), who, env, exits );
}

protected void get_del_dir(string str, object who, object env, mapping exits)
{
	if(!objectp(who) || !objectp(env))
		return;

	if(environment(who) != env)
	{
		tell_object(who, "你的位置发生了变化，修改被停止。\n");
		return;
	}

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(who, "请输入要删除出口的方向(q 退出)：");
		input_to( (: get_del_dir :), who, env, exits);
		return;
	}

	if((str[0] == 'q') || (str[0] == 'Q'))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!mapp(exits) || !sizeof(exits))
	{
		tell_object(who, "出现异常错误。\n删除失败。\n");
		return;
	}

	if(undefinedp(exits[str]))
	{
		tell_object(who, sprintf("没有 %s 这个出口。\n请输入要删除出口的方向(q 退出)：", str));
		input_to( (: get_del_dir :), who, env, exits);
		return;
	}

	if(BUNCH_D->break_an_exit(who, env, str))
		tell_object(who, "删除出口成功。\n");
}

protected void get_add_dir(string str, object who, object env, mapping exits)
{
	if(!objectp(who) || !objectp(env))
		return;

	if(environment(who) != env)
	{
		tell_object(who, "你的位置发生了变化，修改被停止。\n");
		return;
	}

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(who, "请输入要加入出口的方向(q 退出)：");
		input_to( (: get_add_dir :), who, env, exits);
		return;
	}

	if((str[0] == 'q') || (str[0] == 'Q'))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(undefinedp(r_dir[str]))
	{
		tell_object(who, sprintf("房间的出口只能从以下方向种选择：\n%s\n修改失败。\n",vdirs));
		return;
	}

	if(mapp(exits) && sizeof(exits) && !undefinedp(exits[str]))
	{
		tell_object(who, "此出口已存在。\n修改失败。\n");
		return;
	}

	if(mapp(exits) && (sizeof(exits) >= max_exits))
	{
		tell_object(who, sprintf("每个房间最多只能有%s个出口。\n操作失败。\n", chinese_number(max_exits)));
		return;
	}

	tell_object(who, "请确定此出口的目的房间名(q 退出)：");
	input_to( (: do_add_exit :), who, env, exits, str);
}

protected void do_add_exit(string str, object who, object env, mapping exits, string dir)
{
	if(!objectp(who) || !objectp(env))
		return;

	if(environment(who) != env)
	{
		tell_object(who, "你的位置发生了变化，修改被停止。\n");
		return;
	}

	if(!stringp(str) || !sizeof(str))
	{
		tell_object(who, "请确定此出口的目的房间名(q 退出)：");
		input_to( (: do_add_exit :), who, env, exits, dir);
		return;
	}

	if((str[0] == 'q') || (str[0] == 'Q'))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!regexp(str, "^[a-z0-9_]+$"))
	{
		tell_object(who, "房间名里包含错误字符。\n修改失败。\n");
		return;
	}

	if(BUNCH_D->add_one_exit(who, env, dir, str))
		tell_object(who, "增加出口成功。\n");
}
