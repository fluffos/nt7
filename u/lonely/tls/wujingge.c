inherit ROOM;

void create()
{
        set("short", "无净阁");
        set("long",@LONG
这是历代大理王侯女眷前来进香还愿时休息的地方。阁内檀象
宝炉，软榻矮几，一应俱全，清静之中隐然透出一丝富贵之象。
LONG);
        set("sleep_room", "1");
        set("no_fight", "1");
        set("exits", ([
		"south": __DIR__"men1",    			
        ]));
        set("coor/x",-340);
  set("coor/y",-310);
   set("coor/z",30);
   setup();
}
