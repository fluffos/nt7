inherit ROOM;
void create()
{
        set("short", "翔鹤门");
        set("long",@LONG
由光佛殿出此门，可向西行过无住宝塔、三元宫、兜率大士院。
这一路房屋都是寺中僧人清修养之地，你悄声行走，不敢发出丝毫声
响。北面通向无我阁。
LONG);
	set("outdoors","天龙寺");
        set("exits", ([
		"north" : __DIR__"wuwoge",
                "west": __DIR__"yz5",
                "east": __DIR__"gfd",
	]));
        set("coor/x",-360);
  set("coor/y",-320);
   set("coor/z",20);
   setup();
}
int valid_leave(object me, string dir)
{
        if (me->query("gender") == "女性" && dir =="north")
           return notify_fail("无我阁乃是王侯们进香还愿时的休息之处，你一介女子要进去恐怕不太好吧？\n");
        return ::valid_leave(me, dir);
}


