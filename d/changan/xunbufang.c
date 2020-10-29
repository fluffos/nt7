//Room: xubufang.c

inherit ROOM;

void create ()
{
        set ("short", "巡捕房");
        set("long", @LONG
这里是长安城里维持治安的巡捕工作的地方。房门口放着两个青
铜狮，房内是一个大厅，墙上漆着白色的漆，漆得很厚，仿佛不愿人
看出这墙是石壁，是土，还是铜铁所做。有几个横眉立目，嘴脸凶顽
的巡捕坐在一起，似乎在商量着什么。南边有一个小门，似乎上了锁。
LONG );
        set("exits", ([
                "west" : "/d/changan/fengxu5",
        ]));
        set("objects", ([
                "/d/changan/npc/butou"  : 1,
                "/d/changan/npc/guanbing" : 2,
        ]));

        set("coor/x", -10690);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_open", "open");
}

int do_open(string arg)
{
        object me, key, nroom;
        me = this_player();
        if (! arg || arg != "door")
                return notify_fail("你要打开什么？\n");

        if (! (key = present("laofang key", me)))
                return notify_fail("你没有开这道门的钥匙。\n");

        if (! (nroom = find_object("/d/changan/laofang")))
                      nroom = load_object("/d/changan/laofang");

        set("exits/south", "/d/changan/laofang");
        set("exits/north", __FILE__, nroom);
        message("vision", "只听喀嚓！一声，钥匙断了。好"
                "在牢门已经开了。\n", this_object() );
        set_temp("used_laofang_key", 1, me);
        destruct(key);
        call_out("close_door",60);
        return 1;
}

void close_door()
{
        delete("exits/south");
        }