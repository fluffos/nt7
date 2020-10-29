// baichi.c

inherit ROOM;

void create()
{
        set("short", "百尺峡");
        set("long", @LONG
走过千尺幢，前面又见另一要命的百尺峡，百尺峡不似千尺幢般
险峻，但亦十分陡峭，岩壁两侧设有铁索以作扶拦。百尺峡又称百丈
崖，是一座壁立千仞的悬崖。崖底到上面的最低的垭口处约百尺，故
有是名。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "northdown" : __DIR__"qianchi",
            "eastup"    : __DIR__"pingxinshi",
        ]));

        set("outdoors", "huashan" );
        set("objects", ([ 
            "/clone/npc/walker" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
 