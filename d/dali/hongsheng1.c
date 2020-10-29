//Room: /d/dali/hongsheng1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","塔基");
        set("long", @LONG
宏圣寺塔基座系用石板砌成，与千寻塔基为砖砌不同。基座西面
有塔门，可入内攀登而上。
LONG );
        set("exits",([ /* sizeof() == 1 */
            "out"    : "/d/dali/hongsheng",
            "up"     : "/d/dali/hongsheng2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19151);
	set("coor/y", -6821);
	set("coor/z", 19);
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