inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
这是间僧人们的睡房，因门窗常闭着，光线很昏暗，静静的，只
有微微的酣声。房里别无他物，非常简朴，靠墙摆着很多张木板床，
你悄悄的走过去，找了张空床躺了下来。
LONG);
        set("exits", ([
               "south" : __DIR__"road4",
               "west" : __DIR__"sroom1",
               "east" : __DIR__"sroom2",
        ]));
        set("no_fight",1);
        set("sleep_room", 1);
        set("coor/x",-350);
  set("coor/y",-270);
   set("coor/z",30);
   setup();
}




