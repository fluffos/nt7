inherit ROOM;
void create()
{
        set("short", "城外空地");
        set("long", @LONG
这是城外的空地，一些蒙古兵的奸细和箭手常在这带游弋，以寻
找他们感兴趣的猎物，不时有几枚冷箭从头顶嗖地飞过，令人防不胜
防。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);
        set("step",2);
        set("no_fly", 1);
	set("no_task", 1);     
        set("exits", ([
               "east" : __DIR__"east_out4", 
               "west" : __DIR__"east_out2", 
        ]));
        set("coor/x", -7830);
	set("coor/y", -770);
	set("coor/z", 0);
	setup();
}