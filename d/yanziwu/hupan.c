#include <ansi.h>
#include <room.h>
inherit RIVER;

void create()
{
        set("short", "太湖湖畔");
        set("long", @LONG
太湖处江浙之间。她襟带三江，东南之水尽汇于此，周行五百里，
古称五湖。矗立湖 (river)岸，唯见长天远波，放眼皆碧，七十二峰
苍翠挺立在三万六千顷波涛之中，使人心襟大开直欲仰天长啸，方能
表此喜乐。
LONG );
        //set("arrive_room", "/d/yanziwu/bozhou");
        set("to", __DIR__"bozhou");
        set("exits", ([
                "northeast" : "/d/suzhou/road5",
        ]));
        set("objects", ([  
                __DIR__"npc/yufu" : 1,
        ]));  

        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

        set("outdoors", "yanziwu");
        setup();
        replace_program(RIVER);
}
