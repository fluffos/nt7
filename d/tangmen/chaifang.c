//chaifang.c                四川唐门—柴房

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "柴房");
        set("long",
"这里是后院的柴房，屋中堆满了劈好的柴火，满屋都是木材的香味，\n"
"在山也似的柴堆旁一扇小门通向后山，听说那里出没着豺狼虎豹和蜈蚣蛇\n"
"蝎，工夫不够高可不要乱跑呀！西边就是厨房了！\n"
);
        set("exits", ([
                "northeast" : __DIR__"houzhai",
                "west" : __DIR__"chufang",
                "south" : __DIR__"nzlange1",
                "north" : __DIR__"exiaolu1",
        ]));
        create_door("northeast","木门","southwest",DOOR_CLOSED);
        set("objects", ([
                CLASS_D("tangmen") + "/tangpeng" : 1,
        ]));
        set("area", "tangmen");
        setup();
}
int valid_leave(object me, string dir)
{
        if( (dir == "north") && (query("family/family_name", me) != "唐门世家") && 
                !wizardp(me) && (objectp( present("tang peng", environment(me)) ) ))
                return notify_fail("唐朋一伸手，说道：“你不是唐门中人，不能再向前走了！”\n");
        else
                return ::valid_leave(me, dir);
}
