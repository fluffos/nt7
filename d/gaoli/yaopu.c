// /d/gaoli/yaopu
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "药铺");
        set("long", @LONG
走进这里一股药香扑面而来，另你精神为之一振。只见药铺四壁摆
满了药柜，几个小伙计正在忙碌的招待着客人。原来这里的药材来自五
湖四海，可谓应有尽有，光顾这里的大多是有钱人与江湖中人。
LONG
        );
set("exits", ([
               "east":__DIR__"xuanwu-2", 
        ]));
       set("objects", ([
                "/d/gaoli/npc/jia" : 1,
                __DIR__"npc/lifuren":1,
        ]));
       setup();
        replace_program(ROOM);
}        
