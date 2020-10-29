inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "城外驿道");
        set("long", @LONG
这里是通往襄阳守军军营的驿道，由于连年来战火不止，显得格
外地荒凉，不时有来往的马匹飞奔而过，溅起一土尘烟，沿途不时有
土匪大盗出现，还是少作停留的好。
LONG );
        set("outdoors", "xiangyang");
        set("no_magic",1);

        set("exits", ([
                "east"  : __DIR__"yidao", 
                "west"  : __DIR__"yidao",
        ]));

        setup();
}

void init()
{
        object me=this_player();

        if (! me->is_busy())
        me->start_busy(random(2));


        if( query_temp("yidao/mark_steps", me)>11 )
        {
         me->move("/maze/battle3/eastgate2");
         delete_temp("yidao", me);
         tell_object(me,YEL"一路风尘仆仆之后，襄阳已经近在眼前了......\n"NOR);
         return;
        } 

        if( query_temp("yidao/mark_steps", me)<-11 )
        {
         me->move(__DIR__"syuanmen2");
         delete_temp("yidao", me);
         tell_object(me,YEL"一路风尘仆仆之后，大宋军营已经近在眼前了......\n"NOR); 
         return;
        }

        tell_object(me,YEL"你快马加鞭，一路飞驰在驿道上......\n"NOR);

}

int valid_leave(object me,string dir)
{
        object dadao,*env;
        int i,flag;
  
        env=all_inventory(environment(me));   
        flag=0;

        for(i=0;i<sizeof(env);i++)
        {
         if( objectp(env[i]) && query("id", env[i]) == "jiangyangdadao"
             && query("killer", env[i]) == query("id", me) )
         flag=1;
        }

        if( query_temp("warquest/purchase", me) && random(12)>10 )
        {
                dadao=new("/maze/battle3/npc/dadao");
                dadao->set_from_me(me);
                set_temp("warquest/party", "meng", dadao);
                dadao->move(environment(me));
                dadao->kill_ob(me);
                me->kill_ob(dadao);
        return notify_fail("忽然从路边丛林中杀出一路人马！\n");
        } else
        if(flag)
        return notify_fail("江阳大盗挡住了你的去路。\n");

       if( dir == "east" )
       addn_temp("yidao/mark_steps", -random(2), me);
       if(  dir == "west" )
       addn_temp("yidao/mark_steps", random(2), me);
       return ::valid_leave(me,dir);
}
