//Room: /d/dali/lushui.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","泸水沿岸");
        set("long", @LONG
一条土路沿着泸水纵贯谷地南北，脚下泸水滔滔流去，长年累月
冲刷着谷中大地，东面碧罗雪山、西面的高黎山皆高耸蔽日。土路北
通此谷中心大镇巴的甸，南连数个乌夷小部落。
LONG );
        set("outdoors", "daliw");
        set("exits",([ /* sizeof() == 1 */
            "north"      : "/d/dali/badidian",
            "south"      : "/d/dali/atoubu",
        ]));
	set("coor/x", -19210);
	set("coor/y", -6880);
	set("coor/z", 20);
	setup();
        (CLASS_D("ultra") + "/huang")->come_here();
}

string long()
{
        object ob;
        string msg;

        msg = query("long");
        if (! objectp(ob = present("huang shang", this_object())))
                return sort_string(msg, 60, 4);

        if (! ob->is_fighting())
                msg += "有一人沿江来回踱步，时而低头冥思，时而举头远"
                       "望，似乎在想什么要紧的问题。";
        else
                msg += "只见一人正在与" +
                       (ob->is_fighting(this_player()) ? "你" : "人") +
                       "激战，进退之间，干净利索，没有一点花巧。";

        return sort_string(msg, 60, 4);
}