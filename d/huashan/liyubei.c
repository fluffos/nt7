inherit ROOM;

void create()
{
        set("short", "鲤鱼脊");
        set("long", @LONG
这是华山著名的险地『鲤鱼脊』。只见一条长约二十余丈，宽仅
数尺的小径直达对峰，两旁皆是云雾萦绕，深不见底的峡谷，罡风吹
过，使人飘飘若起，武林高手平时也不敢冒险越过此处。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "south"   : __DIR__"laojun",
                "northup" : __DIR__"houzhiwangyu",
        ]));
        set("objects", ([ 
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "huashan" );
        setup();
        replace_program(ROOM);
}
