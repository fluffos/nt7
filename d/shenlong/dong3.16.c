inherit ROOM;

void create()
{
        set("short", "火焰洞外");
        set("long",@LONG
这是神龙岛火焰洞外，据说洞内长满各种毒虫，传说洞内住着一
只火焰巨兽，但是没有人见过。
LONG);

	set("exits", ([
		"enter"   : __DIR__"huodong1",
		"west"   : __DIR__"dong3.15",

	]));

	// 未确保100%安全，在这里也设置免死
	set("no_die", 1);
	
        setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        object env;

	// 检查是否已经开始麒麟战斗
        if (dir == "enter")
        {
                //return notify_fail("对不起，巫师还没有下令开放，你暂时不能参加对抗火麒麟的战斗。\n");

        	ob = find_living("huo qilin");
        	
        	if (objectp(ob) && environment(ob))
        	{
        		if (base_name(environment(ob)) == "/d/shenlong/huodong1")
        		{
        			write("对不起，里面已经开始了对抗火麒麟的战斗。\n");
        			return 0;
        		}
        	}
        	
        	if (! objectp(env = find_object(__DIR__"huodong1")))
        		env = load_object(__DIR__"huodong1");
        		
        	// 正在清场则不能进入
        	if( query("doing", env) )
       		{
       			write("火麒麟BOSS已经挑战结束，正在等待清场，请稍后再试！\n");
       			return 0;
       		}
        }

        return 1;
}
