#include <ansi.h>

inherit DEMONROOM;

void create()
{
        set("short", "九头蛇领地");
        set("long",@LONG
这是九头蛇的领地，周围尽是潮湿阴深的湿地，恐怖之极。
LONG);


	set("exits", ([
		"east"  : __DIR__"jiutou1.23",		
		"west"   : __DIR__"jiutou1.21",
		"out"    : __DIR__"haitan",
		
	]));
        	set("no_rideto", 1);         // 设置不能骑马到其他地方
       		set("no_flyto", 1);          // 设置不能从起来地方骑马来这里
		set("n_time", 30);
		set("n_npc",1); 
		set("n_max_npc", 2);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/jiutoushe");

        setup();
}


// 判断玩家是否付费，未付费则不能进入
void init()
{
	object me = this_player();
	int i;
	object *inv;
	
	if (! objectp(me))
	{
		me->move(__DIR__"haitan");
	}
	
	if (! playerp(me))return;
	
	if( !me->enter_jtshe_srv() )
	{
		tell_object(me, HIR "\n对不起，你没有进入九头蛇领地的特权，不能进入！\n\n" NOR);
		me->move(__DIR__"haitan");
	}

	// 把背起的用户放下来
        inv = deep_inventory(me);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! playerp(inv[i])) continue;

                // 被人背起的用户
                inv[i]->move(__DIR__"haitan");                
        }	
	
	// 允许进入
	return;
}
