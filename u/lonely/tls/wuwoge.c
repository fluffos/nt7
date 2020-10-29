inherit ROOM;

void create()
{
        set("short", "无我阁");
        set("long",@LONG
这是历代大理王侯前来进香还愿时休息的地方。阁内檀象宝炉，
软榻矮几，一应俱全，清静之中隐然透出一丝富贵之象。
LONG);
        set("no_fight",1);
        set("sleep_room", 1);
        set("exits", ([
		"south": __DIR__"men2",
        ]));
        set("coor/x",-360);
  set("coor/y",-310);
   set("coor/z",20);
   setup();
}
