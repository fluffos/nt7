// Room: /d/mingjiao/xingtang.c

#include <ansi.h>
#include <login.h>

inherit ROOM;

void create()
{
        set("short", "刑堂");
        set("long", @LONG
整个刑堂门户紧闭，密不透风。即便是在白昼，也犹如黑夜一般，
每隔几步的墙上，点燃着几枝牛油巨烛。中间是一个大火盆，烈焰腾
腾。下方摆着一排排烙铁、水牛皮鞭、穿孔竹板及狼牙棒等刑具。四
周站满了手持兵刃的执法教众。他们正用冷酷的眼神打量着你，令你
不禁浑身哆嗦起来。    冷谦执掌明教刑堂。
LONG );
        set("no_fight", 0);
        set("exits", ([
                "west" : __DIR__"square",
        ]));
        set("objects",([
                __DIR__"npc/lengqian" : 1
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
