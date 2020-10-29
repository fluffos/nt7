// /d/wizard/guest_room.c

#include <room.h>
#include <ansi.h>

inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", HIR "匿名留言室" NOR);
        set("long", @LONG
如果您有问题留言给泥潭巫师但又不想其他玩家看到，那么您可
以在这里(post)，其他玩家将不能看到您的留言，在这里您可以举报
有问题的id和其他作弊行为，泥潭巫师将为您的留言完全保密。    
                                    ==泥潭制作群==
LONG );

        set("exits", ([
                "south": __DIR__"guest_room",              
        ]));

        set("no_fight", 1);

        set("coor/x", 10000);
        set("coor/y", 10010);
        set("coor/z", 9990);
        setup();
        "/clone/board/noname_b"->foo();
}

int valid_leave(object me, string dir)
{
        if (dir == "west" && ! wizardp(me))
                return notify_fail("只有巫师才能进去！\n");

        return ::valid_leave(me, dir);
}