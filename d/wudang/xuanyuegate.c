inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "玄岳门");
        set("long", @LONG
你的面前是一座林木繁茂的高山，几座山峰在云雾中隐约可见，
一条石阶向山上延伸，走着几个进香客。一个四柱三间五楼式的石坊
跨山而建，正面镌有「治世玄岳」四个大字，原来这就是天下闻名的
武当山。武当山一名太和山，为七十二福地之一，有二十七峰、三十
六岩、二十四涧、五台、五井、三潭、三天门、三洞天和一福地，百
里内密树森罗，蔽日参天景物幽绝。
LONG );
        set("objects", ([
                CLASS_D("wudang") + "/zhike": 1,
                CLASS_D("wudang") + "/daotong": 2,
        ]));
        set("outdoors", "wudang");
        set("exits", ([
                "east"     : __DIR__"slxl3",
                "southup"  : __DIR__"shijie1",
        ]));
        set("coor/x", -370);
        set("coor/y", -180);
        set("coor/z", 20);
        setup();
}