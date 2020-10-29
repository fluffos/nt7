// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一条山路上。再往西边走就是高丽的北城监狱了。这里基本
上没有什么行人，两旁是高高的围墙，看起来有些阴森。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "east" : __DIR__"shanlu14",
                       "northwest":__DIR__"shanlu16",
        ]));
       setup();
        
}

