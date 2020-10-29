// shewu.c 蛇舞
#include <ansi.h>
#include <skill.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me)
{
    int skill,n;
    object ob,snake;
    me=this_player();
    skill = me->query_skill("xiyu-tiezheng",1);

    if( query("neili", me)<500 )
        return notify_fail("你的内力不够充沛,无法弹出「蛇舞」。\n");
    
    if( query("jingli", me)<50 )
        return notify_fail("你的精力不够,无法专心弹琴。\n");

    if (me->query_skill("guzheng-jifa",1)<100)
        return notify_fail("你的古筝技法不够。\n");
    
    if (skill < 100)
        return notify_fail("你的家传筝曲不够娴熟。\n");

    if( !objectp(ob=query_temp("handing", me)) || !ob->valid_as_zheng() )
        return notify_fail("你不拿出筝来，怎么弹奏？\n"); 

//    if(!environment(me)->query("can_perform_shewu"))  
//        return notify_fail("在这里弹奏似乎不太适合吧。\n"); 

    if( query("sleep_room", environment(me)) )
        return notify_fail("在这里弹奏似乎不太适合吧。\n");  

    if( query("no_fight", environment(me)) )
        return notify_fail("在这里弹奏似乎不太适合吧。\n");  

    if(me->is_busy())
        return notify_fail("你现在正忙着呢！\n");


    message_vision(HIB"$N盘膝而坐，双手拂琴，时而快疾，时而缓慢，可似乎并未弹出声音。\n"NOR,me); 
    
    if(skill >= 100 && skill <= 150)  n =10; 
    else if(skill > 150 && skill <= 200) n = 8;
    else if(skill > 200 && skill <= 250) n = 6;
    else if(skill > 250 && skill <= 300) n = 4;
    else if(skill > 300) n = 2;  
//    if (random(n) <10 && random(n) >1 )
    if (random(n) <=2 )
    {
        switch(random(4))
        {
            case 0:
            message_vision("突然，$N感觉身边黑影闪动，只见一条毒蛇正吐着信子，昂首随着$N双手的节奏舞动。\n",me); 
            snake=new("/clone/beast/dushe");
            snake->move(environment(me));
            break;
        
            case 1:
            message_vision("突然，$N感觉身边黑影闪动，只见一条金环蛇正吐着信子，昂首随着$N双手的节奏舞动。\n",me);
            snake=new("/clone/beast/jinshe");
            snake->move(environment(me));
            break;
        
            case 2:
            message_vision("突然，$N感觉身边黑影闪动，只见一条五步蛇正吐着信子，昂首随着$N双手的节奏舞动。\n",me);
            snake=new("/clone/beast/wubushe");        
            snake->move(environment(me));
            break;
        
            case 3:
            message_vision("突然，$N感觉身边黑影闪动，只见一条竹叶青蛇正吐着信子，昂首随着$N双手的节奏舞动。\n",me);
            snake=new("/clone/beast/qingshe");        
            snake->move(environment(me));
            break;
        }
        addn("neili", -100, me);
        addn("jingli", -200, me);
        me->start_busy(5);
    }
    else
    {
        message_vision(GRN"$N心绪纷杂，弹了一会便感血气翻涌，收功站了起来。\n"NOR,me);
        addn("neili", -100, me);
        addn("jingli", -50, me);
        me->start_busy(3);
    }
    return 1;    
}