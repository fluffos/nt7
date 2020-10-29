inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
这里是山中的一片丛林，灌木中夹杂着一些野花，被高大的树木
遮住了阳光。一块巨大的石头倚树而卧。
LONG );
        set("exits", ([
                "eastdown" : "/d/beijing/shanlu2",
        ]));
         set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7630);
	set("coor/z", 30);
	setup();
        (CLASS_D("ultra") + "/kuihua")->come_here();
}

string long()
{
        object ob;
        string msg;

        msg = query("long");
        if (! objectp(ob = present("kuihua taijian", this_object())))
                return sort_string(msg, 70, 4);

        if (! ob->is_fighting())
                msg += "有一个黄衫人靠在石上，痴痴的望着远方，一动不动"
                       "的，也不知道他在这里究竟待了多久。";
        else
                msg += "只见一黄衫人身形诡秘，进退疾若闪电，正在与" +
                       (ob->is_fighting(this_player()) ? "你" : "人") +
                       "激战。";

        return sort_string(msg, 70, 4);
}