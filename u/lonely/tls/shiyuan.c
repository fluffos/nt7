inherit ROOM;

void create()
{
        set("short", "兜率大士院");
        set("long",@LONG
兜率大士院供奉的是八部天龙、五百阿罗、三千揭啼。这里烟雾
弥漫，都是香客门所进的天竺檀香。几个知客僧正忙得不亦乐乎。由
此向南是三无宫，西往清音阁，北至后山。
LONG);
        set("exits", ([              
              "southdown" : __DIR__"3wg",
              "west" : __DIR__"qxg",
              "north" : __DIR__"road5",
	]));	
        set("coor/x",-390);
  set("coor/y",-310);
   set("coor/z",30);
   setup();
}
