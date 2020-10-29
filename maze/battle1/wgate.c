// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void death_stage(object ob, int stage);
void setup_weishi(object weishi,object ob);

void create()
{
        set("short", HIR"战场入口"NOR);
        set("long", @LONG
这里是战场的入口。。。
LONG);
        set("outdoors", "battle");
        set("invalid_startroom", 1);

        //set("no_fight", 1);

        set("exits", ([
                "enter" : __DIR__"wgarden",
        ]));

        setup();
}

void init()
{
        object me = this_player();
        call_out( "death_stage", 1, me, 0 );
}

void death_stage(object ob, int stage)
{
        object weishi, *weishis;
        int nMyWeiShi=0, nOtherWeiShi=0;
        int i;

        if( !ob || !objectp(ob) || !userp(ob) ) return;

        weishis = filter_array(children(__DIR__"npc/weishi.c"), (: clonep :));

        for( i = 0; i < sizeof(weishis); i++)
        {
                weishi = weishis[i];
                if( query_temp("battle/team_name", weishi) == query_temp("battle/team_name", ob) )
                        nMyWeiShi++;
                else nOtherWeiShi++;
        }


        if( nMyWeiShi > nOtherWeiShi+3 || nMyWeiShi >8  ) return;
        else
        {
                weishi = new (__DIR__"npc/weishi.c");
                if( !weishi )return;
                weishi->move(__DIR__"wtang");
                setup_weishi(weishi,ob);
                message("vision", "你忽然发现前面多了一个人影。\n", environment(weishi), weishi);
        }

}

void setup_weishi(object me,object obj)
{
        mapping skills;
        string *names;
        int level,i;
        mixed exp;

        if( !objectp(me) || !objectp(obj) )return;

        exp=query("combat_exp", obj)-10000000;
        if( exp < 0 ) exp = 1000000;

        set("combat_exp", exp, me);

        level = pow( exp*10.,0.33333 );
        if( level < 100 ) level = 100;

        if( query("combat_exp", obj)<3000000 )
        {
                level = level/2 + random(level*2/3);
        }
        else if( query("combat_exp", obj)<5000000 )
        {
                level = level/2 + random(level/2);
        }
        else if( query("combat_exp", obj)<8000000 )
        {
                level = level/2 + random(level/3);
        }
        else if( query("combat_exp", obj)<10000000 )
        {
                level = level/2 + random(level/4);
        }
        else
                level = level/2 + random(level/5);

        skills = me->query_skills();
        names = keys(skills);

        for( i=0; i<sizeof(names); i++ )
                me->set_skill(names[i], level);

        set_temp("battle/team_name",query_temp("battle/team_name",  obj), me);
        if( exp>80000000)set("name", "特级武士", me);
        else if( exp>60000000)set("name", "一级武士", me);
        else if( exp>40000000)set("name", "二级武士", me);
        else if( exp>20000000)set("name", "三级武士", me);
        else if( exp>5000000)set("name", "四级武士", me);
        else set("name", "五级武士", me);

        set_temp("apply/short", ({HIW""+query_temp("battle/team_name", obj)+""NOR+me->name()+"(wushi)"}), me);
}