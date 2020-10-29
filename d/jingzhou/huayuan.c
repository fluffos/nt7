// This program is a part of NT MudLIB

inherit ROOM;

void create()
{
        set("short", "花园");
        set("long", @LONG
这里是翰林府的花园。院子里种了各色名贵的菊花。黄菊有都胜、
金芍药、报君知。白菊有月下白、一团雪、貂蝉拜月。紫菊有双飞燕、
紫玉莲、玛瑙盘。红菊有美人红、醉贵妃、绣芙蓉。。。院中有几盆
颜色特别娇艳的黄花，花瓣黄得像金子一样，花朵的样子很像荷花。
那就是从天竺传来的金波旬花。
LONG );
        set("outdoors", "jingzhou");
        set("region", "jingzhou");

        set("exits", ([
                "north" : __DIR__"houyuan",
                "west" : __DIR__"loudi",
                "east" : __DIR__"shufang",
        ]));
        set("objects", ([
                //__DIR__"npc/obj/juhua1" : 1,
                __DIR__"obj/jinboxunhua" : 2,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
}

void init()
{
        object me = this_player();

        if( !query_temp("jinboxunhua", me) && !wizardp(me) && playerp(me)){
                me->receive_damage("qi", 1000);
                me->receive_damage("jing", 800);
                set_temp("die_reason", "中了金波旬花毒而死", me);
                tell_object(me, "你突然头晕目旋。\n");
                return;
        }
}