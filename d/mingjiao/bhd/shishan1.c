// shishan1.c 小石山
// Modify By River@SJ 99.06
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", YEL"小石山"NOR);
        set("long", @LONG
这是一座小山石，比之西面的石山要小多了。山石周围到处都是
奇花异树，异树丛中传来阵阵的奇香，皆由不知名之花朵传出。山脚
下露出一个小小的石洞(dong)，西边有一座石山。
LONG );
	set("outdoors","冰火岛");
        set("resource/water", 1);
	set("exits",([
		"west"  :  __DIR__"shishan",
	]));
        set("item_desc", ([
                "dong" : "这是一个山洞，里面不知道有些什么古怪。\n",
        ]));
	setup();
}

void init()
{
        add_action("do_enter", "enter");
}

int do_enter(string arg)
{
        object me;
        me = this_player();
        if( arg=="dong") {
            message("vision",me->name()+"一弯腰往洞里走了进去。\n",environment(me), ({me}) );
            me->move(__DIR__"xdong");
            message("vision",me->name()+"从洞外走了进来。\n",environment(me), ({me}) );
            return 1;
        }
}       
