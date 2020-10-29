#include <room.h>
inherit ROOM;

void create()
{
        set("short", "东长安街");
        set("long", @LONG
热闹的东长安大街是紫禁城的交通要道，宽阔的青石大道向东西
两头延伸，路边有个狗洞(dong)，几只懒狗正在那里探头。街道上行
人不断，繁华的盛世景象不言而喻。在这里可以远远望见西边那一堵
堵高大厚实的古城墙，便是著名的天安门广场了。北面是京城最为繁
华热闹的王府井大街。
LONG );
       set("exits", ([
                "east" : "/d/beijing/caroad_e2",
                "west" : "/d/beijing/cagc_e",
                "north" : "/d/beijing/wang_1",
        ]));
        set("objects", ([
                "/d/beijing/npc/girl4" : 1,
                "/d/beijing/npc/jumin1" : 1,
        ]));
        set("item_desc", ([
            "dong" : "黑呼呼的狗洞，不知道有多深。\n",
        ]));
	set("coor/x", -2780);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
}
void init()
{
        add_action("do_enter", "enter");
        add_action("do_enter", "zuan");
}

int do_enter(string arg)
{
        object me;
        mapping fam;

        me = this_player();
        if( !arg || arg=="" ) return 0;
        if( arg=="dong" )
        {
           if( (fam=query("family", me)) && fam["family_name"] == "丐帮" )
           {
               message("vision",
                        me->name() + "运起丐帮缩骨功，一弯腰往狗洞里钻了进去。",
                        environment(me), ({me}) );
               me->move("/d/gaibang/underbj");
               message("vision",
                        me->name() + "从洞里走了进来。\n",
                        environment(me), ({me}) );
                        return 1;
           }
           else  return notify_fail("这么小的洞，你钻得进去吗？\n");
       }
}