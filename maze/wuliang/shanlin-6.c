// Modify By River 98/12
inherit ROOM;

void create()
{
	set("short", "森林");
	set("long", @LONG
你费了九牛二虎之力，从密密麻麻的树林中钻进了这里，却发现眼前已没
有了去路,前面一株株古树互相挤在一起，便如一堵大墙（wall)相似，再也无
法向前进一步了。
LONG
	);
        set("outdoors", "大理");

	set("exits", ([
             "south" : __DIR__"shanlin-5",
	]));

	setup();
}

void init()
{       
       add_action("do_jump", "jump");
       add_action("do_tiao", "tiao");
}

int do_jump(string arg)
{
       object me;
       me = this_player();
       if (!arg || arg !="wall") 
           return notify_fail("你要跳到那去？\n");
       if (random(me->query_skill("dodge",1)) < 60){ 
           write("你吸气奋力一跳，无奈运气不好，没跳过树墙，摔了下来。\n");
           write("你受了点伤!\n");
addn("qi", -100, 	me);
           addn("jingli", -80, me);
           me->receive_wound("qi", 50);
	   return 1;
           }
       else {
           write("你一吸气，轻轻巧巧的跳过了大树墙。\n");
           message("vision",me->name() + "一纵身跳过了树墙。\n",environment(me), ({me}) );            
           me->move(__DIR__"muwu1");
           me->start_busy(1);
           message("vision",me->name() + "从树墙后面跳了过来。\n",environment(me), ({me}) );
           return 1;
           }
}