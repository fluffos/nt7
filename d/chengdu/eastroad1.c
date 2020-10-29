// Room: eastroad1.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "东大街");
        set("long", @LONG
你走在东大街坚实的青石板地面上。南边可以通向东城门，路边
有一个简陋的茶摊，一块洗得发白了的旧帆布正顶着头顶火辣辣的阳
光，一张长几上放着几只大号粗瓷碗 (Wan)。碗中盛满着可口的茶水。
    往西北通往北大街，东北方一座大店面里传出阵阵划拳的喧闹。
LONG );
        set("outdoors", "chengdu");
        set("resource/water", 1);
        set("item_desc", ([
                "wan" : "香喷喷的大碗茶，来一碗吧！\n",
        ]));
        set("exits", ([
                    "northeast" : __DIR__"jiudian",
                    "northwest" : __DIR__"northroad3",
                    "south"     : __DIR__"eastroad2",
        ]));
        set("objects", ([
                    __DIR__"npc/xiaozei" : 1,
        ]));
        set("coor/x", -15200);
	set("coor/y", -1820);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_drink","drink");
}

int do_drink(string arg)
{
        int current_water;
        int max_water;
        object me;

        me = this_player();
        current_water=query("water", me);
        max_water=query("str", me)*10+100;
        if (current_water<max_water)
        {
                set("water", current_water+60, me);
                message("vision", me->name() +
                        "端起一碗茶水来.... \n", environment(me), ({me}));
                write("你端起一碗茶水来.咕噜.咕噜..喝了个干净。真解渴呀！\n");
        }
        else write("你实在是喝不下了。\n");
        return 1;
}