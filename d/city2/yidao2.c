
inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "城外驿道");
        set("long", @LONG
这里是通往大宋京城的驿道，由于连年来战火不止，显得格外地
荒凉，不时有来往的马匹飞奔而过，溅起一土尘烟，沿途不时有土匪
大盗出现，还是少作停留的好。
LONG );
        set("outdoors", "xiangyang");
        set("no_fly", 1);
        set("no_rideto", 1);
        set("no_magic", 1);

        set("exits", ([
                "east"  : __DIR__"yidao2", 
                "west"  : __DIR__"yidao2",
        ]));

        setup();
}

void init()
{
        object me=this_player();

        if (! me->is_busy())
                me->start_busy(random(2));

        tell_object(me,YEL"你快马加鞭，一路飞驰在驿道上......\n"NOR);
}

int valid_leave(object me,string dir)
{
        object dadao,*env;
        int i,flag;
        int n;
  
        /*
        env=all_inventory(environment(me));   
        n = sizeof(filter_array(env, (: query("id", $1) == "jiangyang dadao" :)));
        flag=0;

        for(i=0;i<sizeof(env);i++)
        {
                if( objectp(env[i]) && query("id", env[i]) == "jiangyang dadao"
                &&  query("killer", env[i]) == query("id", me) )
                        flag=1;
        }

        if( query_temp("warquest/purchase", me) && n < 20 && random(12)>10 )
        {
                dadao=new(__DIR__"npc/dadao");
                dadao->set_from_me(me);
                set_temp("warquest/party", "meng", dadao);
                dadao->move(environment(me));
                dadao->kill_ob(me);
                me->kill_ob(dadao);
                return notify_fail("忽然从路边丛林中杀出一路人马！\n");
        } else
        if(flag)
                return notify_fail("江阳大盗挡住了你的去路。\n");
        */

        if( dir == "east" )
                addn_temp("yidao/mark_steps", -random(2), me);
        if(  dir == "west" )
                addn_temp("yidao/mark_steps", random(2), me);

        if( query_temp("yidao/mark_steps", me)>11 )
        {
                me->move(__DIR__"yidao3");
                delete_temp("yidao", me);
                tell_object(me,YEL"一路风尘仆仆之后，汴梁已经近在眼前了......\n"NOR);
                return -1;
        } 

        if( query_temp("yidao/mark_steps", me)<-11 )
        {
                me->move(__DIR__"yidao1");
                delete_temp("yidao", me);
                tell_object(me,YEL"一路风尘仆仆之后，襄阳已经近在眼前了......\n"NOR); 
                return -1;
        }
        
        if (! me->is_busy())
                me->start_busy(random(2));

        tell_object(me,YEL"你快马加鞭，一路飞驰在驿道上......\n"NOR);
        return -1;
        
        return ::valid_leave(me,dir);
}

