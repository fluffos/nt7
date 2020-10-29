#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "浓密树林");
        set("long", @LONG
这里是一片浓密的树林，参天的大树遮天蔽日，偶尔有几缕
光线透进来。地上满是枯枝败叶，空气中弥漫着让人不安的气氛。
LONG
        );

        set("outdoors", "yaowang");
        setup();
}

void init()
{
        object me = this_player();

        if( (random(10) < 7)
        || !userp(me)
         || (query("family/family_name", me) == "yaowang" )
         || query_temp("been_recommend_to_yaowang", me) )
                return;

        call_out("do_ansuan", 2, me);
}

protected void do_ansuan(object me)
{
        int flag = random(10)<5?1:0, n;
        string *limbs;

        if( !me || (environment(me) != this_object()) )
                return;

        tell_object(me, sprintf(HIB"\n突然“嗖”的一声，树后打来一只飞镖。\n%s\n\n"NOR,
                flag?"你赶紧一侧身躲了过去，下出了一身冷汗。":
                sprintf("一下钉在了你的%s上。",(n=sizeof(limbs=query("limbs", me)))?
                limbs[random(n)]:"身")));

        if(!flag)
        {
                me->receive_damage("qi", 10);
                if(random(10) < 2)
                        me->apply_condition("yaowang_du", 2);
        }
}
