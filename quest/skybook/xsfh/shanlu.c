#include <ansi.h>
inherit ROOM;
#define QUESTDIR2 "quest/雪山飞狐/复仇篇/"

void create()
{
        set("short","山路");
        set("long", @LONG
一条被捕蛇人踏出的小道，弯弯曲曲的向西北方向的山幽伸展。道旁的杂
草(grass) 高达五尺，遮住了天光。山幽中的一切都显的阴森幽暗。几乎使你
分不清前方的道路。
LONG
        );

        set("exits", ([
                "southeast" : __DIR__"slu1",
        ]));
        set("item_desc", ([
                "grass": "这里杂草(grass)很密，但你似乎可以拨开(push)它们。\n",
                "杂草": "这里的杂草(grass)很密，但你似乎可以拨开(push)它们。\n"
        ]));
        setup();
}
void init()
{
        add_action("do_push", "push");
}
int do_push(string arg)
{
	  object me=this_player();
        if( arg == "grass" || arg == "茅草" || arg == "草")
        {
        message_vision("$N拨开路边的杂草，发现了一条向西北的路。\n", this_player());
        if(me->query(QUESTDIR2+"start")&& me->query_temp(QUESTDIR2+"zhenxiang") && !random(3))
        {
           set("exits/northwest", __DIR__"houshan_copy");
           remove_call_out("close_path");
           call_out("close_path", 5);
        }
        else if( !query("exits/northwest") )
        {
        set("exits/northwest", __DIR__"houshan");
        remove_call_out("close_path");
        call_out("close_path", 5);
        }
        return 1;
        }
}
void close_path()
{
        if( !query("exits/northwest") ) return;
        message("vision",
"一阵风吹过，杂草晃了晃，又淹没了向西北的路。\n",
                this_object() );
                delete("exits/northwest");
}
