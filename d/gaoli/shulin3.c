// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "树林");
        set("long", @LONG
你走在一片树林之中。这里树木茂盛，参天蔽日，非常凉快。北边
是一个烽火台。再望南边走，就是高丽的朝阳门了。有几个官兵正在这
里检查来往的行人。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"shulin2",
                "northup":__DIR__"dongfenghuotai",
        ]));
       setup();
        replace_program(ROOM);
}        
