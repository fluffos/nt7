inherit ROOM;

void create()
{
        set("short", "慈悲院");
        set("long",@LONG
这是僧人们点化顽徒的地方。不少江湖豪客由于厌倦了打打杀杀
的日子，来到此处落发为僧，叛依佛门。墙上一幅佛祖神像，两边各
有一条幅，上书：放下屠刀，立地成佛。此处东面是个兵器房，北面
是物品房。
LONG);
        set("exits", ([
                "east" : __DIR__"bingqi",
		"west" : __DIR__"road4",
		"north" : __DIR__"wuping",
	]));    
        set("coor/x",-340);
  set("coor/y",-280);
   set("coor/z",30);
   setup();
}
