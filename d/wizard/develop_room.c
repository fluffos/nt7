// /d/wizard/guest_room.c

#include <ansi.h>
#include <room.h>
inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", HIM "游戏开发室" NOR);
        set("long", @LONG
这里是巫师和玩家交流的地方，为便于巫师统一管理，这里只能
发表(post)关于玩家对本游戏的见解以及开发建议或者对游戏中某些
问题的疑问，以供巫师参考。不能发表非该主题以外的闲杂话题，如
果发现经过多次提醒仍然继续者，将一律删除档案。其他问题请到「
巫师会客室」发表，这样便于巫师和玩家交流，也便于统一管理，提
高效率！玩家可以在此发表任何符合该主题的文章，巫师也将尽力回
复之，并定期公布开发进度和计划以供玩家参考，欢迎提出意见！  
                                  ==泥潭Ⅱ全体巫师==
LONG );

        set("exits", ([
                "north": __DIR__"guest_room",               
        ]));

        set("no_fight", 1);

        set("coor/x", 10000);
        set("coor/y", 9990);
        set("coor/z", 9990);
        setup();
        "/clone/board/develop_b"->foo();
}