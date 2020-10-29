// /d/gaoli/xuanwumen
// Room in 高丽
inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
这里是一条山路。西边就是高丽的西烽火台了。有几个官兵在那里
检查来往的行人。现在时局混乱，所以这里的戒备也是很严格。
LONG
        );

        set("exits", ([
                "southdown" : __DIR__"shanlu4",
                "westup":__DIR__"xifenghuotai",
        ]));

         set("outdoors", "gaoli");
        setup();
        replace_program(ROOM);
}


