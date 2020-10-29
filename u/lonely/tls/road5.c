inherit ROOM;

void create()
{
	set("short", "石板路");
	set("long", @LONG
你走在一条长长的石板路上，道旁古树参天，鸟鸣不绝，前面是
一片大松林，这条路一直通向百丈桥，路上冷冷清请，偶尔见几个僧
人从松林中穿出来。
LONG);
	set("exits", ([
           "north" : __DIR__"bzqs",
           "south" : __DIR__"shiyuan",   
        ]));
	set("outdoors", "天龙寺");
	set("coor/x",-390);
  set("coor/y",-300);
   set("coor/z",30);
   setup();
}
