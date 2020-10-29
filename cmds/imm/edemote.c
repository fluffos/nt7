
#include <ansi.h>
#include <emotion.h>

inherit F_CLEAN_UP;

string help = @HELP
表情指令编辑器

edemote '表情指令'	- 编辑表情指令
edemote -d '表情指令'	- 删除表情指令

HELP;


int help(object me)
{
        write(help);
        return 1;
}
private int valid_emote_name(string emotion)
{
	return strsrch(emotion, " ") == -1;
}

private void choose_option(object me, string emotion, mapping modifying_emotion, string arg);
private void setup_emotion(object me, string emotion, mapping modifying_info, int option, string contiune_arg, string arg);

private string replace_keys(string description)
{
	if( !description ) return "尚未设定";

	description = replace_string(description, "$ME", 	HIC"你"NOR);
	description = replace_string(description, "$YOU", 	HIG"某人"NOR);
	description = replace_string(description, "$T", 	HIM"事物"NOR);

	return description;
}
private string emotion_detail_description(string emotion, mixed info)
{
	string msg = "---- 表情 "HIY+emotion+NOR+" 之详细叙述如下："+repeat_string("--", 13-(strlen(emotion)/2))+"\n";

	msg += NOR WHT"1.无对象无附加文字    ："NOR+replace_keys(info[NONE_ALL])+"\n";
	msg += NOR WHT"2.无对象有附加文字    ："NOR+replace_keys(info[NONE_ALL_ARG])+"\n";
	msg += NOR WHT"3.对象为自己无附加文字："NOR+replace_keys(info[ME_ALL])+"\n";
	msg += NOR WHT"4.对象为自己有附加文字："NOR+replace_keys(info[ME_ALL_ARG])+"\n";
	msg += NOR WHT"5.对象为某人无附加文字："NOR+replace_keys(info[YOU_ALL])+"\n";
	msg += NOR WHT"6.对象为某人有附加文字："NOR+replace_keys(info[YOU_ALL_ARG])+"\n";
	msg += NOR WHT"7.表情注解            ："NOR+(info[NOTE] || "尚未设定")+"\n";
	msg += NOR WHT"8.使用次数            ："NOR+info[USE]+" 次\n";
	msg += "------------------------------------------------------\n";
	return msg;
}

private void confirm_delete_emotion(object me, string emotion, string arg)
{
	if( lower_case(arg) == "y" )
	{
		if( EMOTE_D->delete_emotion(emotion) )
			tell(me, "删除表情指令 "+emotion+" 成功。\n");
		else
			tell(me, "删除失败，请通知巫师处理。\n");

		return me->finish_input();
	}
	else
	{
		tell(me, "取消删除。\n");
		return me->finish_input();
	}
}

private void setup_emotion(object me, string emotion, mapping modifying_info, int option, string multi_line_arg, string arg)
{
	if( !arg || !arg[0] )
	{
		multi_line_arg += "\n";
		tell(me, ">");
		input_to( (: setup_emotion, me, emotion, modifying_info, option, multi_line_arg :) );
	}

	switch(arg)
	{
		case "cancel":
			tell(me, "取消输入叙述。\n"+emotion_detail_description(emotion, modifying_info)+"请输入欲设定之项目(设定完毕 save, 取消设定 exit)：\n>");
			input_to( (: choose_option, me, emotion, modifying_info :) );
			break;

		case ".":
			// 最佳化叙述
			if(multi_line_arg[<1..] == "\n") multi_line_arg = multi_line_arg[0..<2];
			multi_line_arg = kill_repeat_ansi(trim(ansi(multi_line_arg)) + NOR);
			modifying_info[option-1] = multi_line_arg;

			tell(me, "设定完毕。\n"+emotion_detail_description(emotion, modifying_info)+"请输入欲设定之项目(设定完毕 save, 取消设定 exit)：\n>");
			input_to( (: choose_option, me, emotion, modifying_info :) );
			break;
		default:
			multi_line_arg += arg+"\n";
			tell(me, ">");
			input_to( (: setup_emotion, me, emotion, modifying_info, option, multi_line_arg :) );
	}
}

private void choose_option(object me, string emotion, mapping modifying_info, string arg)
{
	int option;

	switch(arg)
	{
		case "save":
			if( sizeof(modifying_info) != 8 )
			{
				tell(me, "必须设定完所有表情叙述才能储存设定。\n请输入欲设定之项目(设定完毕 save, 取消设定 exit)：\n>");
				input_to( (: choose_option, me, emotion, modifying_info :) );
				return;
			}
			else
			{
                           string *info = allocate(0);

				for(int i=0;i<8;i++)
					info += ({ modifying_info[i] });

				if( EMOTE_D->set_emotion(emotion, info) )
				{
					tell(me, "表情指令 "+emotion+" 设定储存成功。\n");
				}
				else
					tell(me, "表情指令 "+emotion+" 设定储存失败。\n");

				return me->finish_input();
			}
			break;

		case "exit":
			tell(me, "取消对 "+emotion+" 表情指令的设定。\n");
			return me->finish_input();

		default:break;
	}

	option = to_int(arg);

	if( option > 8 || option < 1 )
	{
		tell(me, "没有这个选项。\n请输入欲设定之项目(设定完毕 save, 取消设定 exit)：\n>");
		input_to( (: choose_option, me, emotion, modifying_info :) );
	}
	else if( option == USE+1 )
	{
		tell(me, "这个选项无法使用手动设定。\n请输入欲设定之项目(设定完毕 save, 取消设定 exit)：\n>");
		input_to( (: choose_option, me, emotion, modifying_info :) );
	}
	else
	{
		tell(me, "\n按 ENTER 可持续输入多行，输入 '.' 结束，输入 'cancel' 取消。\n请输入标准格式叙述 "HIC"$ME(代表自己) "HIG"$YOU(代表对象) "HIY"$T(代表附加文字)"NOR"：\n>");
		input_to( (: setup_emotion, me, emotion, modifying_info, option, "" :) );
	}
}

int main(object me, string arg)
{
	string *info;
	mapping modifying_info = allocate_mapping(8);

        if (! SECURITY_D->valid_grant(me, "(immortal)"))
                return 0;


	if( !arg ) {
		tell(me, pnoun(2, me)+"想要增加或修改哪个表情指令？\n");
		return 1;
	}

	arg = remove_ansi(arg);

	if( sscanf(arg, "-d %s", arg) == 1 )
	{
		if( !arrayp(info = EMOTE_D->query_emotion(arg)) ) {
			tell(me, "没有 "+arg+" 这个表情指令。\n");
			return 1;
		}

		tell(me, emotion_detail_description(arg, info)+"确定是否删除 "+arg+" 表情指令(Yes/No)？");
		input_to( (: confirm_delete_emotion, me, arg :) );
		return 1;
	}

	if( arrayp(info = EMOTE_D->query_emotion(arg)) )
	{
		for(int i=0;i<8;i++)
			modifying_info[i] = info[i];
	}
	else
	{
		if( !valid_emote_name(arg) ) {
			tell(me, "不合法的表情指令名称。\n");
			return 1;
		}

		modifying_info[NOTE] = 0;
		modifying_info[USE] = 0;
	}

	tell(me, emotion_detail_description(arg, modifying_info)+"请输入欲设定之项目(设定完毕 save, 取消设定 exit)：\n>");
	input_to( (: choose_option, me, arg, modifying_info :) );
	return 1;
}
