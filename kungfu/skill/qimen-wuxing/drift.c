// drift_sense.c
#include <ansi.h>
//inherit SSERVER;

int conjure(object me, object target)
{
        object ob;
        int i;
        
        return notify_fail("奇门遁甲暂时不开放。\n");
        if ( !query("yuanshen", me) ) return notify_fail("你还没有悟道，无法掌握奇门遁甲。\n");

        if ( !wizardp(me) && me->query_family() != "桃花岛" && member_array("桃花岛", query("reborn/fams", me)) == -1 )
                return notify_fail("只有桃花岛的玩家才能领悟奇门遁甲。\n");

        if ( me->is_fighting() ) return notify_fail("战斗中你没有时间打洞,呵呵！\n");
          
        if ( !query("outdoors", environment(me)) ) return notify_fail("嘣！嘣！嘣！这里的地板，似乎好硬哟！\n");

        ob = first_inventory(me);
        while ( ob )
        {
                if (ob->is_character() && !ob->is_corpse() )
                        return notify_fail(ob->name()+"不能和你一起钻洞！\n");
                ob = next_inventory(ob);
        }
        if ( query("jing", me) < 30 ) return notify_fail("你的精力不够！\n");
        if ( target ) return notify_fail("奇门遁术只能自己使用！\n");

        if ( virtualp(environment(me)) ) return notify_fail("这里无法使用神通!\n");
        write("你要钻到哪一个人身边？");
        input_to( (: call_other, __FILE__, "select_target", me :));
        return 1;
}

void select_target(object me, string name)
{
        object ob, env;
        mapping exits;
        int i;
        
        if ( !name || name=="" ) 
        {
                write("中止施法。\n");
                return;
        }
        ob = find_player(name);
        if ( !ob || !me->visible(ob) || wizardp(ob) ) ob = find_living(name);
        if ( !ob || !me->visible(ob) || !living(ob) || wizardp(ob) ) 
        {
                write("你无法感受到这个人的精力 ....\n");
                return;
        }
        if ( !objectp(env=environment(ob)) )
        {
                write("你无法感受到这个人的精力 ....\n");
                return;
        }
        if ( random(query("jing",me))<30 )
        {
                write("你无法感觉到对方的存在\n");
                return;
        }
        /*
        if ( query("quest/quest_type",me)=="杀"
                && (string)query("quest/quest",me)==ob->short()
                && query("quest/task_time",me)<time() )
        {
                write("你无法感受到这个人的精力 ....\n");
                return;
        }
        */
        if ( me->is_fighting() ) 
        {
                write("战斗中你没有时间打洞,呵呵！\n");
                return;
        } 

        me->receive_damage("jing", 30);
        if ( query("jingli",ob) > random(query("jingli",me)) 
                || !random(4)
                || time() - query_temp("do_flee",me) < 3 ) 
        {
                message_vision( HIY "$N飞快地在地上扒了个洞，钻了进去 ....\n" NOR, me);
                write("咚咚几声，你挖到几块大石头，哇，没门！\n");
                message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),({me}));
                return;
        }
        set_temp("do_flee",time(),me);
        if ( !environment(ob) || query("no_magic",environment(ob)) 
                || query("no_fight", environment(ob)) 
                || random(me->query_skill("qimen-wuxing",1)) < 30 ) 
        {
                write("你手指都磨破了，才挖出个老鼠洞，MY GOD，怎么钻呀！\n");
                message( "vision",HIY+me->name()+"使劲把脸往土里蹭了几下，真无聊。\n" NOR, environment(me),({me}));
                return;
        }
        exits=query("exits", environment(ob));
        if (!mapp(exits) || !sizeof(exits) )
        {
                write("你挖到一堵石墙，不得不退了回来！\n");
                message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),({me}));
                return;
        }
        if ( domain_file(base_name(environment(ob)))=="shaolin" 
                || domain_file(base_name(environment(ob)))=="newbie" 
                || domain_file(base_name(environment(ob)))=="mingjiao" 
                || domain_file(base_name(environment(ob)))=="shenlong" 
                || domain_file(base_name(environment(ob)))=="wizard" 
                || domain_file(base_name(environment(ob)))=="death" ){
                write("那里佛气好重，非道术所能及！\n");
                message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),({me}));           
                return;         
        }               

        if ( domain_file(base_name(environment(ob)))=="taohua" || domain_file(base_name(environment(ob)))=="binghuo"){
                write("恭喜你，你挖到了泉水哩！\n");
                message( "vision",HIY+me->name()+"从口了吐出几口水大叫：好咸呀！\n" NOR, environment(me),({me}));
                return;
        }

        if ( domain_file(base_name(environment(ob)))=="xiakedao" ){
                write("恭喜你，你挖到了茅坑哩！\n");
                message( "vision",HIY+me->name()+"从口了吐出几口大粪大叫：好臭呀！好臭呀！\n" NOR, environment(me),({me}));
                return;
        }

        if ( domain_file(base_name(environment(ob)))=="gaochang" ) {
                write("那里太遥远了。\n");
                message( 
                        "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),({me}));
                return;
        }

        if ( sscanf(base_name(environment(ob)), "/data/%*s") ){
                write(HIM "那里是人家的私宅，想进去偷东西啊?\n" NOR);
                message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),({me}));
        }

        if ( !environment(ob) || wizardp(ob) ){
                 message_vision( HIY "$N飞快地在地上扒了个洞，钻了进去 ....\n" NOR, me);
                write("你在地底钻了半天，发现"+ob->name()+"似乎在天上 ....\n");
                message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),({me}));
                return;
        }
        
        /*
        if( userp(ob) )
        {
                message_vision( HIY "$N飞快地在地上扒了个洞，钻了进去 ....\n" NOR, me);
                write("你在地底钻了半天，发现似乎不着边际 ....\n");
                message( "vision",HIY+me->name()+"一脸气急败坏，灰头灰脸地从洞里又钻了回来。\n" NOR, environment(me),({me}));
                return;
        }
        */
        message_vision( HIY "$N飞快地在地上扒了个洞，钻了进去 ....\n" NOR, me);
        message( "vision", HIY "\n很快，洞口又封了起来，" + me->name() + "不见了！\n\n" NOR, environment(me), ({ me }) );


        if( file_size(file_name(environment(ob))+".c")<=0 )
        {
                write(HIY"但是，很快地你发现那里似乎并不存在，于是又灰头土脸地退了回来。\n"NOR);        
                return;
        } else 
                me->move(environment(ob));
        message( "vision", HIY "\n一个黑影突然从地下冒了出来，喷了你满脸的灰！\n\n" NOR,
                environment(ob), ({ me }) );
        
        /*
        if( me->query_skill("taoism",1) > me->query_skill("qimen-wuxing", 1) )
                me->improve_skill("qimen-wuxing", random(me->query_skill("taoism")), 0);
        else    
                me->improve_skill("qimen-wuxing", random(me->query_skill("taoism")), 1);
        */
}


