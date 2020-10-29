inherit ROOM;
void create()
{
        set("short", "清心阁");
        set("long",@LONG
这是寺中诸僧参修清心净欲的地方。阁中只有地面放有几个蒲团，
角落里摆了一张桌子，上面并排立着五支点燃的蜡烛(candle)。除此之
外别无它物，确然是个清静之处。
LONG);
        set("exits", ([
		"east": __DIR__"shiyuan",
        ]));
        set("item_desc",([
                "candle" : "五支点燃了的长蜡烛，跳跃的火焰似乎温暖了整个房间。\n",
        ]) );
        set("no_fight",1);
        set("coor/x",-400);
  set("coor/y",-310);
   set("coor/z",30);
   setup();
}
void init()
{
        add_action("do_shoot", ({"shoot", "she"}));
}

int do_shoot(string arg)
{
        object me = this_player();
        int level, jinglicost;

        level = me->query_skill("finger", 1);
        if (arg == "candle" || arg == "zhu" || arg == "lazhu") {
                jinglicost = level / 3 + random(level / 3);
                if (me->query("jingli") <= jinglicost) {
                        write("你太累了，先歇歇吧！\n");
                        return 1;
                }
                if (level < 30) {
                        write("你将手指对准蜡烛，试图运气于指对蜡烛射去，却怎么也挤不出指风来。\n");
                        return 1;
                }
                me->receive_damage("jingli", jinglicost);
                if (level <= 100) {
                        write("你运气于指，一缕指风对准蜡烛射去，");
                        if (level < 40) write("蜡烛的火苗微微晃了一晃。\n");
                        else if (level < 50) write("蜡烛的火苗晃了一晃。\n");
                        else if (level < 60) write("蜡烛的火苗晃了几晃。\n");
                        else if (level < 70) write("蜡烛的火苗狠狠地晃了几晃才稳下来。\n");
                        else if (level < 80) write("蜡烛的火苗被射得东倒西歪，停了一下又跳跃起来。\n");
                        else if (level < 90) write("蜡烛的火苗被射得东倒西歪，过了半天才又跳跃起来。\n");
                        else write("“嗤”地一声轻响，蜡烛的火苗几乎灭了，挣扎了几下才又重新跳跃起来。\n");
                        me->improve_skill("finger", me->query("int"));
                        if (!random(5)) message("vision", "$N对着蜡烛指指点点，不知在做什么。\n", me, ({ me }));
                }
                else {
                        write("“噗”地一声，蜡烛被你的指风射灭了！\n");
                        write("黑暗中有人大叫：“哪个混蛋干的？！”，你赶忙跑过去把蜡烛重新点燃。\n");
                }
                return 1;
        }
        return notify_fail("你要谋杀谁？\n");
}
