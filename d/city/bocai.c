//Room: bocai.c

inherit ROOM;

void create ()
{
        set ("short", "博彩店");
        set("long", @LONG
这里是提供彩票服务的博彩娱乐场所。墙上挂着曾开出过的历史
号码。店内人声鼎沸，人们相互交流着下次的中奖号码。有人脸上挂
着浅笑，也有人面目通红，激动不已。喜欢博彩的玩家在这里可以向
店老板询问。
LONG );
        set("exits",  ([
                "south" : "/d/city/daxiao",
        ]));

        set("objects", ([
                // "/adm/npc/lottery" : 1,
        ]));
        set("no_fight", 1);

	set("coor/x", -20);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_getnum", "getnum");
}

int do_getnum()
{
        object me = this_player();
        int i, n;
        string num = "机选号码：";

        if (me->is_busy())
              return notify_fail("你正在分析号码。\n");

        for (i = 0; i < 5; i++)
        {
              n = random(10);
              num += sprintf("%d", n);
        }
        num += "\n";
        tell_object(me, num);
        me->start_busy(1);
        return 1;
}