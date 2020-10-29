// cdesc.c

#include <ansi.h>
#include <bunch.h>

protected void decide_action_do(string str, object who, object env, mapping desc);
protected void delete_desc(string str, object who, object env, mapping desc);
protected void add_desc_short(string str, object who, object env, mapping desc);
protected void add_desc_long(string str, object who, object env, mapping desc, string ishort, string ilong);
protected void make_item_desc(object who, object env, mapping desc);

protected string list_desc_msg(mapping desc)
{
	string out = "";

	if(!desc || !sizeof(desc))
		return "";

	foreach(string a, mixed b in desc)
	{
		if(stringp(b))
			out += sprintf("%s\n%s\n%s\n%s\n----------------------------------------------\n",
				HBCYN HIG"提示词："NOR, a, HBCYN HIG"提示信息："NOR, b);
		else
			out += sprintf("%s\n%s\n%s\n%O\n----------------------------------------------\n",
				HBCYN HIG"提示词："NOR, a, HBCYN HIG"提示信息："NOR, b);
	}

	return out;
}

int main(object me, string arg)
{
	object env;
	mapping desc;
	string out;

	if(!me || (me != this_player(1)) || !objectp(env = environment(me)))
		return 0;

	seteuid(getuid(this_object()));

	if(!BUNCH_D->valid_modify_room(me, env))
		return 0;

	desc = env->query("item_desc");

	if(!mapp(desc) || !sizeof(desc))
	{
		out = "
「目前这里没有任何特殊提示」
请选择你要进行的操作：
(1) 加入一条新的特殊提示。
(q) 退出。
";
		write(out);
		input_to( (: decide_action_do :), me, env, desc );
		return 1;
	}

	out = "
            「目前这里已有的特殊提示」
-------------------------------------------------
";
	out += list_desc_msg(desc);

	out += "请选择你要进行的操作：
(1) 加入一条新的特殊提示。
(2) 删除一条已存在的提示。
(q) 退出。
";
	write(out);
	input_to( (: decide_action_do :), me, env, desc );
	return 1;
}

protected void decide_action_do(string str, object who, object env, mapping desc)
{
	if(!objectp(who) || !objectp(env))
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')) )
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(sizeof(str) && (str[0] == '1'))
	{
		tell_object(who, HBCYN HIG"请输入设定的提示词[1-6个汉字](q 退出)：\n"NOR);
		input_to( (: add_desc_short :), who, env, desc );
		return;
	}

	if(sizeof(str) && (str[0] == '2'))
	{
		if(!desc || !sizeof(desc))
		{
			tell_object(who, "功能选择错误。\n");
			return;
		}
		tell_object(who, HBCYN HIG"请输入要删除特殊提示的提示词：\n"NOR);
		input_to( (: delete_desc :), who, env, desc );
		return;
	}

	if(!desc || !sizeof(desc))
		tell_object(who, "
请选择你要进行的操作：
(1) 加入一条新的特殊提示。
(q) 退出。
");
	else
		tell_object(who, "
请选择你要进行的操作：
(1) 加入一条新的特殊提示。
(2) 删除一条已存在的提示。
(q) 退出。
");
	input_to( (: decide_action_do :), who, env, desc );
}

protected void delete_desc(string str, object who, object env, mapping desc)
{
	string content, f_sect, e_sect, fname, result;

	if(!objectp(who) || !objectp(env))
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!stringp(str) || (sizeof(str) < 2) || (sizeof(str) > 12))
	{
		tell_object(who, "提示词输入错误。\n");
		return;
	}

	if(undefinedp(desc[str]))
	{
		tell_object(who, "没有这个提示词。\n");
		return;
	}

	if(environment(who) != env)
	{
		tell_object(who, "你的位置发生了变化，修改被停止。\n");
		return;
	}

	if(!content = read_file(fname = base_name(env) + ".c"))
	{
		tell_object(who, "无法读取文件内容，修改失败。\n");
		return;
	}

	if(!BUNCH_D->parse_set_value(ref content, "item_desc", ref f_sect, ref e_sect))
	{
		tell_object(who, "无法剖析文件内容，修改失败。\n");
		return;
	}

	map_delete(desc, str);

	result = sprintf("// Room: %s\n\n", fname);
	if(!sizeof(desc))
		result += sprintf("%s\n%s\n", f_sect, e_sect);
	else
		result += sprintf("%s\n\tset(\"item_desc\", %O);\n%s\n", f_sect, desc, e_sect);

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

protected void add_desc_short(string str, object who, object env, mapping desc)
{
	if(!who || !env)
		return;

	if(sizeof(str) && ((str[0] == 'q') || (str[0] == 'Q')))
	{
		tell_object(who, "ok.\n");
		return;
	}

	if(!str || (sizeof(str) <= 2))
	{
		tell_object(who, HBCYN HIG"请输入设定的提示词[1-6个汉字](q 退出)：\n"NOR);
		input_to( (: add_desc_short :), who, env, desc );
		return;
	}

	if(sizeof(str) > 12)
	{
		tell_object(who, HBCYN HIG"提示词的长度不能超过6个汉字，请输入(q 退出)：\n"NOR);
		input_to( (: add_desc_short :), who, env, desc );
		return;
	}

	tell_object(who, "请输入提示信息：\n·信息内容不能超过六行\n·每行不超过25个汉字
请输入('.'结束输入，'q'退出)：\n------------------------------------------------------\n");
	input_to((: add_desc_long :), who, env, desc, str, "");
}

protected void add_desc_long(string str, object who, object env, mapping desc, string ishort, string ilong)
{
	if(!who || !env || !ishort)
		return 0;


	if(!stringp(str) || (str == ""))
	{
		input_to((: add_desc_long :), who, env, desc, ishort, ilong);
		return;
	}

	if( (str[0] == 'q')
	|| (str[0] == 'Q') )
	{
		tell_object(who, "终止房间修改。\n");
		return;
	}

	if(str[0] == '.')	// 结束输入
	{
		if( !sizeof(ilong) )
		{
			tell_object(who, "你没有特殊提示设定足够的提示信息\n增加特殊提示失败。\n");
			return;
		}

		if( sizeof(explode(ilong, "\n")) > 6)
		{
			tell_object(who, HBCYN HIG"·提示信息内容不能超过六行\n增加特殊提示失败。\n"NOR);
			return;
		}

		if(!desc)
			desc = ([]);
		desc += ([ ishort : ilong ]);
		make_item_desc(who, env, desc);
		return;
	}

	if(strsrch(str, '\n'))
	{
		int n;
		string *tmp;

		n = sizeof(tmp = explode(str, "\n"));
		for(int i=0; i<n; i++)
			if(strlen(tmp[i]) > 50)
			{
				tell_object(who, HBCYN HIG"每一行不能超过二十五个中文字，请重新输入刚才输入的内容：\n");
				input_to((: add_desc_long :), who, env, desc, ishort, ilong);
				return;
			}

		if((n + sizeof(explode(ilong, "\n"))) > 6)
		{
			tell_object(who, HBCYN HIG"·提示信息内容不能超过六行\n增加特殊提示失败。\n"NOR);
			return;
		}
	}

	else
	{
		if(strlen(str) > 50)
		{
			tell_object(who, HBCYN HIG"每一行不能超过二十五个中文字，请重新输入上一次输入的内容：\n");
			input_to((: add_desc_long :), who, env, desc, ishort, ilong);
			return;
		}

		if( sizeof(explode(ilong, "\n")) > 5 )
		{
			tell_object(who, HBCYN HIG"·提示信息内容不能超过六行\n增加特殊提示失败。\n"NOR);
			return;
		}
	}

	ilong += str + "\n";
	input_to((: add_desc_long :), who, env, desc, ishort, ilong);
}

protected void make_item_desc(object who, object env, mapping desc)
{
	string content, f_sect, m_sect, e_sect, fname, result;

	if(!who || !env)
		return;

	if(!mapp(desc) || !sizeof(desc))
	{
		tell_object(who, "无加入项目。\n");
		return;
	}

	if(environment(who) != env)
	{
		tell_object(who, "你的位置发生了变化，加入操作被停止。\n");
		return;
	}

	if(!content = read_file(fname = base_name(env) + ".c"))
	{
		tell_object(who, "无法读取文件内容，修改失败。\n");
		return;
	}

	result = sprintf("// Room: %s\n\n", fname);

	if(!BUNCH_D->parse_set_value(ref content, "item_desc", ref f_sect, ref e_sect))
	{
		if(!BUNCH_D->parse_function_body(ref content, "void", "create", ref f_sect, ref m_sect, ref e_sect, 0))
		{
			tell_object(who, "无法剖析文件内容，修改失败。\n");
			return;
		}

		result += sprintf("%s\n\tset(\"item_desc\", %O);\n%s\n%s\n",
			f_sect, desc, m_sect, e_sect);
	}
	else
		result += sprintf("%s\n\tset(\"item_desc\", %O);\n%s\n", f_sect, desc, e_sect);

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

	tell_object(who, "特殊提示加入成功。\n");
}
