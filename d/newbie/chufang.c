inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "厨房");
        set("long", @LONG
这里是村长家的厨房，平常弟子们饿了可以到这里要 （输入指
令 yao）些食物。房中灶火正旺，一个大厨师正忙的满头大汗。屋角
放着一个大水缸。  
LONG);

        set("exits", ([
                "east" : __DIR__"cunzhangjia",
        ]));

        set("objects", ([
                __DIR__"npc/chushi" : 1,
        ]));

        set("ricewater", 1000);
        set("xinshoucun", 1); 
        set("no_fight", 1);
        set("no_pk", 1);
	setup();
}

void init()
{
        add_action("do_yao", "yao");
}

int do_yao()
{
        object me;
        object food;
        object water;
        me = this_player();

        if (present("man tou", this_player())) 
                return notify_fail(CYN "厨师眉头一皱，说道：吃完了再拿，别浪费食物。\n" NOR);

        if (present("water", this_object())) 
                return notify_fail(CYN "厨师眉头一皱，说道：吃完了再拿，别浪费食物。\n" NOR);

        if( time()-query_temp("last_yao_food", me)<30 )
                return notify_fail(CYN "厨师眉头一皱，说道：你刚要过食物了，留点口粮给别人吧！\n" NOR);

        if (query("ricewater") > 0)
        {
                message_vision(CYN "厨师将一个馒头和一碗清水递到$N手中，笑"
                               "道：你慢用。\n" NOR, me);
                food = new("/d/henshan/obj/mantou");
                water = new("/d/henshan/obj/water");
                food->move(me);
                water->move(me);
                addn("ricewater", -1);
                set_temp("last_yao_food", time(),                 me);
        }
        else 
                message_vision(CYN "厨师对$N" CYN "歉声道：嗨，吃的喝的都"
                               "没了。\n" NOR,me);
        return 1; 

}
