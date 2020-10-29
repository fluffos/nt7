// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "中军大帐");
        set("long", @LONG
        
这是百济驻军所在的兵营的中军大帐，正中一张帅案，上面放着十
二把令箭，后面坐着一位老将军，两旁的的将士各个盔明甲亮。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"yuanmen",
        ]));
       setup();
        replace_program(ROOM);
}        
