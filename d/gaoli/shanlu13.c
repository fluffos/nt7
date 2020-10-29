// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一条山路上。这里地形崎岖，偶尔有几只野兔从你的身旁跑
过。北边就是高丽的北烽火台了。有几个官兵在那里监察情况。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"shanlu12",
                "northup":__DIR__"beifenghuotai",
        ]));
       setup();
        
}

