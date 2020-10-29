// shishan.c 石山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", HIW"石山"NOR);
        set("long", @LONG
这是一座山石，山石周围到处是奇花异树，异树丛中传来阵阵的
奇香，皆由不知名之花朵传出。山脚下露出一个石洞(dong)，西面是
通住火山之路，东边半里处有一小石山，北边是一片片深不见底的大
丛林。
LONG );
	set("outdoors","冰火岛");
	set("exits",([
		"west"  :  __DIR__"ysroad1",
		"east"  :  __DIR__"shishan1",
                "south" :  __DIR__"pingyan2",
                "north" :  __DIR__"cling",
	]));

        set("item_desc", ([
                "dong" : "这是一个很大的熊洞，里面不知道有些什么古怪。\n",
        ]));
	setup();
}

void init()
{
        if(!this_player()->query_condition("cold_wind") && !wizardp(this_player()))
        this_player()->apply_condition("cold_wind", 1);
        add_action("do_enter", "enter");
}

int do_enter(string arg)
{
        object me;
        me = this_player();
        if( arg=="dong" ) {
            message("vision",me->name()+"一弯腰往洞里走了进去。\n",environment(me),({me}));
            me->move(__DIR__"xiongdong");
            message("vision",me->name()+"从洞外走了进来。\n",environment(me), ({me}));
            return 1;
        }
}       
