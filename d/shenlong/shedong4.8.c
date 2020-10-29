inherit ROOM;

void create()
{
        set("short", "蛇精洞外");
        set("long",@LONG
这是蛇精洞外，再往前走就要进入蛇精洞了，据说，还没有人能活着
走出蛇精洞。
LONG);


	set("exits", ([
		"north"  : __DIR__"shedong4.7",		
		"enter"   : __DIR__"shejingdong",
	]));

	// 为确保100%安全，这里也设置免死
	set("no_die", 1);
	
        setup();
}

int valid_leave(object me, string dir)
{
        object ob;
        object env;

	// 检查是否已经开始蛇精战斗
        if (dir == "enter")
        {
                //return notify_fail("对不起，巫师还没有下令开放，你暂时不能参加对抗蛇精的战斗。\n");
        	
        	ob = find_living("jiutou shejing");
        	
        	if (objectp(ob) && environment(ob))
        	{
        		if (base_name(environment(ob)) == "/d/shenlong/shejingdong")
        		{
        			write("对不起，里面已经开始了对抗蛇精的战斗。\n");
        			return 0;
        		}
        	}
        	
        	if (! objectp(env = find_object(__DIR__"shejingdong")))
        		env = load_object(__DIR__"shejingdong");
        		
        	// 正在清场则不能进入
        	if( query("doing", env) )
       		{
       			write("蛇精BOSS已经挑战结束，正在等待清场，请稍后再试！\n");
       			return 0;
       		}
        	
        }

        return 1;
}
