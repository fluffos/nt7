//Room: /d/dali/hongsheng2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","宏圣寺塔");
        set("long", @LONG
这里是宏圣寺塔内部，四面墙壁上都辟有佛龛，龛内置佛像。抬
头上望，可以看到中心柱、葫芦顶、伞盖、相轮及莲花座托等。伞盖
成八角形，角上挂有风铎。
LONG );
        set("exits",([ /* sizeof() == 1 */
            "down"   : "/d/dali/hongsheng1",
            "up"     : "/d/dali/hongsheng3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19151);
	set("coor/y", -6821);
	set("coor/z", 29);
	setup();
}

int valid_leave(object me, string dir)
{
        int c_exp;
        int c_skill;
        if (dir == "up" )
        {
                c_exp=query("combat_exp", me);
                c_skill = (int)me->query_skill("dodge",1);
                if( query("qi", me)>20 )
                {
                        me->receive_damage("qi", 20);
                        if (c_skill*c_skill*c_skill/10 < c_exp && c_skill<101)
                                me->improve_skill("dodge", (int)me->query_skill("dodge", 1) / 5);
                        tell_object(me,"你爬上一层楼，有些累了。\n");
                } else
                {
                        set("qi", 0, me);
                        tell_object(me,"你是在爬不动了。\n");
                        return 0;
                }
        }
        return 1;
}