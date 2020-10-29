// /d/gaoli/jefang
// Room in 高丽
inherit ROOM;

void create()
{
        set("short", "客房");
        set("long", @LONG
这是一间很大的客房，陈设十分华丽。靠墙放了几张大床，客人们
盖着大被子睡的正香，满屋子都是呼呼的打酣声。西边有张床是空的，你
蹑手蹑脚地走了过去。
LONG
        );

        set("sleep_room", "1");
        set("no_fight", "1");
        set("hotel",1);

        set("exits", ([
        "down" : __DIR__"yingbinguan",
        ]));

        setup();
}

int valid_leave(object ob,string dir)
{
   ob->delete_temp("rent_paid");
   return ::valid_leave(ob,dir);
}