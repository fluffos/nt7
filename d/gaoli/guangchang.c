// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "广场");
        set("long", @LONG
这里一个大广场。广场占地很大，估计可以容纳上千人。北边是高
丽的天台，是高丽求神祭天的地方。每次求神祭天，都有上千人来这里
祭拜，场面很是壮观。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southwest" : __DIR__"shanlu8",
                "northup":__DIR__"tiantai",
        ]));
       setup();
        
}

