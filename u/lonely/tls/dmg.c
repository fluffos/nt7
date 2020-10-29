inherit ROOM;

void create()
{
        set("short", "斗母宫");
        set("long",@LONG
这里是天龙寺里最高的地方了，再往上都是险峻的悬崖了，这座
小殿依山而建，殿内灯火通明，你站在门口，远眺天龙寺，只见一片
殿堂连绵不绝，甚是浩大。
LONG);
        set("exits", ([
               "east" : __DIR__"road4",
//               "south" : __DIR__"yaofang",
               "north" : __DIR__"road6",
	]));
        set("coor/x",-360);
  set("coor/y",-280);
   set("coor/z",30);
   setup();
}
