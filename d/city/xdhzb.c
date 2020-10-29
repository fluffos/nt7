#include <ansi.h>

inherit ROOM;

#define PLACE "yz"
#define TYPE  "bad"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "小刀会扬州总部");
        set("long", @LONG
这里是小刀会扬州总部，外面的房间里传出来吆五喝六的赌博声。
小刀会是扬州本地的一个黑帮势力，帮主鞠老大擅长飞刀绝技，在打
败了扬州所有地痞流氓之后，创立了小刀会，乃远近赫赫有名的地头
蛇。在房间的墙上有一块牌子(look paizi)。加入小刀会的玩家，可
以在这里选择任务去完成。
LONG );

        set("objects", ([
               "/d/city/npc/boss-ju" : 1,
               "/d/city/npc/toumu"   : 2,
        ]));

      set("no_fight",1);

        set("exits", ([
                "out" : "/d/city/shulin1",
        ]));

        setup();
}
#include <bang_bad.h>