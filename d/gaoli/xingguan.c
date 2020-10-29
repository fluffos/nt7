// /d/gaoli/xingguan
// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "武士行馆");
        set("long", @LONG
这里是行馆的大厅，厅中摆着一张杉木圆桌和几张椅子，桌上是一
套精致的宜兴瓷器。对门立着一座玉石屏风，据说是高丽皇帝所赐。
LONG
        );
set("exits", ([
                "east":__DIR__"yudao5",
                "enter":__DIR__"neitang",
        ]));
set("objects", ([
                "/d/gaoli/npc/shi1" : 4,
        ]));
       setup();
     //"/obj/board/party_yj_b.c"->foo();
}        
