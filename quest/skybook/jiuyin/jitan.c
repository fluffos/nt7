// Room: /d/huashan/jitan.c
// Date: Look 99/03/25

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "祭坛");
	set("long",@long
这里是华山绝顶上人们祭祀上天的祭坛，华山弟子都要下山行侠仗义，以
换取上苍对华山百姓的保佑。
long);
	set("exits", ([
		"out" : __DIR__"yunuci",
	]));
	set("objects", ([
		__DIR__"npc/lingshan" : 1,
		__DIR__"npc/shitong" : 1,
	]));
	setup();
}

void init()
{
//        add_action("do_jitan", "jitan");
}

int do_jitan(string arg)
{
	object me, ob, ling;
	int addskill;
	string* quest_skill = ({ "jiuyin-zhengong","hamagong", "kuihua-xinfa" });

	me = this_player();
	ob = this_object();
	ling = present("ling pai", me);

	if( !living(me) ) return 0;
	
	if(!ling)
		return notify_fail("你身上没有令牌如何告慰英烈的在天之灵？\n");

	if (me->is_busy() || me->is_fighting())
		return notify_fail("你正忙着哪！\n");

	if( !me->query_temp("jitan") )
		return notify_fail("你要干什么？\n");

	if ( !arg ) return notify_fail("你要干什么？\n");
	switch (arg){
		case "strike":	break;
		case "hand":	break;
		case "claw":	break;
		case "force":	break;
		case "cuff":	break;
		case "finger":	break;
		case "leg":	break;
		default:	return notify_fail("你要干什么？\n");
	}

	message_vision("$N恭敬地从侍童手中接过蒙面人，摆放在祭坛前，恭敬地磕了三个响头。\n", me);
	write(HIW"突然天空中降下一道闪电，劈向蒙面人。只听蒙面人一声惨叫，就此西去。\n"NOR, me);

	addskill = (int)me->query("int",1) * 2;
	addskill += (int)me->query("kar",1) * 2;
	addskill += random(me->query_skill(arg, 1) /10);

	addskill = random(addskill) + 1;
	if (arg != "force") {
		me->improve_skill( arg , addskill);
		write("你的"+to_chinese(arg)+"得到了"+CHINESE_D->chinese_number(addskill)+"点提高。\n", me);
	}
	else {
		addskill=random(addskill/10) + 2;
		while( member_array(me->query_skill_mapped("force"),quest_skill)== -1 )
		{
			me->improve_skill( me->query_skill_mapped("force") , addskill);
			write("你的"+to_chinese(me->query_skill_mapped("force"))+"得到了"+CHINESE_D->chinese_number(addskill)+"点提高。\n", me);
		}
	}
	ling->add_temp("done", 1);
	me->delete_temp("jitan");
	return 1;
}
