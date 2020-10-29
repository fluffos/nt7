#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "城东桥");
        set("long", @LONG
此桥高跨洛阳护城河之上，气势非凡。站在桥上向两侧望去，一条人
工开掘的护城河将洛阳城围在当中，桥身以汉白玉造就，既美观又很坚固。
桥上车水马龙，川流不息。桥下的护城河水清澈见底，时有游鱼跃起。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"dongdoor",
                //"eastdown" : __DIR__"guandaoe1",
                "eastdown" : __DIR__"road2",
        ]));

	set("coor/x", -6920);
	set("coor/y", 2150);
	set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}

void init()
{
        object me;
        object ob;

        if( interactive(me = this_player()) && !me->is_fighting() )
        {
                if( query_temp("juxianzhuang_step", me) == 11 )
                {
                        ob = new("/maze/juxianzhuang/npc/qiaofeng");
                        ob->move(environment(me));
                        message_vision(HIW "$N走了过来，后面跟着一辆马车。\n", ob);
                }
        }
}