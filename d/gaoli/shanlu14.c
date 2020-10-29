// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一条山路上。再往西边走就是高丽的北城监狱了。那里关押
着高丽的重要犯人，平时有很多官兵在那里把守。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "east" : __DIR__"shanlu12",
                       "west":__DIR__"shanlu15",
        ]));
       setup();
        
}

