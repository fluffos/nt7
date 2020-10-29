// /d/gaoli/xuanwumen
// Room in 高丽
inherit ROOM;

void create()

{
set("short", "山路");

        set("long", @LONG
你正走在一条崎岖不平的山路上，偶尔听到一阵阵的野兽叫声，头
顶有一些不知名的小鸟在跳来跳去，四周丛林密布，鲜花绿草若隐若现，
随着山谷里吹来的阵阵清风，传来哗哗的松涛声和一些淡淡的花香，身
临其境，古朴、幽静之感油然而生。
LONG
        );
        

set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"xuanwumen",
                  "northup" : __DIR__"shanlu2",
        ]));
       setup();
        replace_program(ROOM);
}
