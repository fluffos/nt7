#include <ansi.h>

inherit ROOM;

#define PLACE "cd"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "修罗门分坛");
        set("long", @LONG
这里是黑道组织修罗门的成都分坛，这是一间阴森恐怖的房间，
到不是因为他的名字可怕，而是左右两旁的那两尊修罗王的塑像，形
态诡异，让人感觉仿佛和世界隔离了一般。墙上挂着修罗门的任务牌
（paizi）。
LONG );

        set("objects", ([
               __DIR__"npc/boss-leng"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "out" : __DIR__"qingyanggong",
        ]));

        setup();
}
#include <bang_bad.h>
