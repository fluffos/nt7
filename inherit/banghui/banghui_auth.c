// banghui_auth.c
// BANGHUI_MASTER
// by Find.

// 按权限等级定义

#include <banghui.h>

// bid, bname 一次设定不能再更改。
protected string bname, out_room, dir;
protected nosave string bid;
protected mapping
 
protected nosave string *banghui_levels = ({
"a_master",
"b_master",
"c_master",
"z_master",
});

protected mapping chinese_banghui_level = ([
"a_master" : "帮主",
"b_master" : "护法",
"c_master" : "香主",
"z_master" : "帮众",
]);

string query_chinese_banghui_level(string level)
{
	if(!undefinedp(chinese_banghui_level[level]))
		return chinese_banghui_level[level];
	else
		return "帮众";
}

string query_player_bh_level(string id)
{


}

protected void get_banghui_id()	// 建立的时候由 create() 呼叫
{
	string id;

	if(bid || clonep())
		return;

	if(sscanf(base_name(this_object()), BANGHUI_DIR"%s/%*s", id ) != 2)
		return;

	bid = id;
}

protected int set_banghui_name(string name)
{
	int i;
	string tmp;

	if( clonep() || bname || !stringp(name) || !(i = sizeof(name)) )
		return 0;

	tmp = clr_ansi(name);

	if((i < 2) || (i > 12))
		return notify_fail("帮会的名字必须使用 1-6 个汉字。\n");

	while(i--)
	{
		int section;

                if( tmp[i]<128 )
			return notify_fail("帮会的名字必须使用 *汉字*。\n");

		if( i%2==0 )
		{
			section = tmp[i] - 160;

			if( (section < 16)
			|| (section > 87) )
				return notify_fail("帮会的名字必须使用 *常用* 汉字。\n");
		}
	}

	if(!BANGHUI_D->register_banghui_name(tmp))
		return notify_fail("这个名字已经有人使用了，请另起一个。\n");

	bname = name;
	save();

	return 1;
}

string query_banghui_id() { return bid; }
string query_banghui_name() { return bname; }

/*
varargs protected int set_banghui_id(string id, string ref err)
{
	if(!stringp(id) || !sizeof(id))
		return 0;

	if(!regexp(id, "^[a-zA-Z]+$"))
	{
		err = "帮会的 ID 只能由小写英文单词组成。\n";
		return 0;
	}

	id = lower_case(id);

	if(file_size(dir_pre+id) != -1)
	{
		err = sprintf("[%s] 这个 ID 已经有人使用了，请另选一个。\n", id);
		return 0;
	}
}
*/
