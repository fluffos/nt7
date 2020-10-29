//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "汉正街");
        set ("long", @LONG
这是武汉最繁华的街道。从大江南北来的各色人等，熙熙攘攘，摩
肩接踵。西边一个大棚子里摆放了许多菊花，姹紫嫣红，令人叹为观止。
东边是有名的琴台。
LONG);
        set("outdoors", "wuchang");
        set("exits", ([
                "east" : __DIR__"qintai",
                "west" : __DIR__"juhuahui",
                "south": __DIR__"hzjie5",
                "north": __DIR__"zhongxin",
        ]));
  
        set("no_clean_up", 0);
	set("coor/x", -5090);
	set("coor/y", -1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}