inherit ROOM;
void create()
{
        set("short", "瑞鹤门");
        set("long",@LONG
由光佛殿出此门，可向东行过无相宝塔、幌天门、清都瑶台、无
无境、雨花院而至般若台。这一路房屋都是寺中僧人清修养之地，你
悄声行走，不敢发出丝毫声响。北面通向无净阁。
LONG);
	set("outdoors","天龙寺");
        set("exits", ([
             "north" : __DIR__"wujingge",
	       "west": __DIR__"gfd",
	       "east": __DIR__"yz4",
	]));
        set("coor/x",-340);
  set("coor/y",-320);
   set("coor/z",30);
   setup();
}
int valid_leave(object me, string dir)
{
        if (me->query("gender") != "女性" && dir =="north")
           return notify_fail("无净阁乃是王侯夫人小姐们进香还愿时的休息之处，你要进去恐怕不太好吧？\n");
        return ::valid_leave(me, dir);
}
