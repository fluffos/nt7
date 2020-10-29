// dgb_book.c

#include <ansi.h>
inherit ITEM;
inherit F_UNIQUE;

int do_start(object me);


void create()
{
        set_name("打狗棒谱", ({ "dgb book", "book" }));
        set_weight(600);
        /*if( clonep() )
                set_default_object(__FILE__);
        else*/ {
                set("unit", "本");
        set("long", "打狗棒的口诀向来都是口传，这个册子记载着打狗棒的最后一招天下无狗的详解。\n");
                set("material", "paper");
                                set("no_drop","这样东西不能离开你。\n");
                                set("no_get",1);
                                set("no_steal",1);
                set("value", 300000);

        }
}
void init()
{
  add_action("do_lingwu","lingwu");
  
}
int do_lingwu(string arg)
{
        object me;
        int cost;
        object *ob;
        object weapon;
        int i;
        me=this_player();
         if (me->is_busy())
            return notify_fail("你正忙着呢!\n");

        
        if( arg != query("id", this_object()))return notify_fail("你要领悟什么?\n");
        if(me->query_skill("dagou-bang", 1) <250)
        return notify_fail("你连打狗棒法最基本的招式还未娴熟呢？\n");
        if( query("wugou", me)>500 )
        {
            set("can_perform/dagou-bang/tian", 1, me);
        return notify_fail("你已经完全领悟了打狗棒的绝招。\n");
        }
        if( query("no_fight", environment(me)))return notify_fail("这里空气不好，无法专心领悟。\n");
        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++) {
            if( query("race", ob[i]) == "人类" && ob[i] != me )
            return notify_fail("打狗棒的绝招可不能轻易让人看的哦。\n");
        }
        if( !objectp(weapon=query_temp("weapon", me)) )
        return notify_fail("你手中无打狗棒如何领悟绝招!\n");
        
        if( query("skill_type", weapon) != "staff" )
        return notify_fail("手中拿着竹杖才能领悟打狗棒法的绝招!\n");
        if( query("qi", me)<query("max_qi", me) || query("jing", me)<query("max_jing", me) )
        return notify_fail("你的身体状况不佳！\n");
        if( query("neili", me)<query("max_neili", me) || query("jingli", me)<query("max_jingli", me) )
        return notify_fail("你的精力，内力还未充盈，无法领悟！\n");
        if( query("max_neili", me)<1000 )
                return notify_fail("你的内力不够深厚，无法领悟打狗棒法！\n");
        if( query("master", this_object()) != query("id", me) )
        {
        if( query("max_neili", me)<20 )
                return notify_fail("你觉得浑身无力，似乎一身内功已经尽数散去。\n");
        addn("max_neili", -20, me);
        return notify_fail(HIR"你不知口诀，强行领悟招式，突然心口有说不出的难受。\n"NOR);

        }
if (wizardp(me)) printf("int = %d\n",me->query_int());
        message_vision(HIY"$N默念口诀，手拿打狗棒，按照书中的姿势比划着......\n"NOR,me);
        if (random(me->query_int())>35 || random(10)==3)
        {
                 addn("wugou", 1, me);
                if( query("wugou", me)<60 )
                 tell_object  (me,HIR"你似乎对打狗棒最后一招有一丝领悟。\n"NOR);
                 else if( query("wugou", me) == 60 )
                 tell_object  (me,HIR"你领悟出六式天下无狗中的三式，也许你该试验试验了。\n"NOR);
                 else if( query("wugou", me)>500 )
                 {
                         set("can_perform/dagou-bang/tian", 1, me);
             if (me->can_improve_skill("staff")) 
                     me->improve_skill("staff", 1500000); 
             if (me->can_improve_skill("staff")) 
                     me->improve_skill("staff", 1500000); 
             if (me->can_improve_skill("staff")) 
                     me->improve_skill("staff", 1500000); 
             if (me->can_improve_skill("dagou-bang")) 
                     me->improve_skill("dagou-bang", 1500000); 
             if (me->can_improve_skill("dagou-bang")) 
                     me->improve_skill("dagou-bang", 1500000); 
             if (me->can_improve_skill("dagou-bang")) 
                     me->improve_skill("dagou-bang", 1500000); 
             me->improve_skill("martial-cognize", 1500000); 
                 tell_object  (me,HIR"你终于领悟出天下无狗的所有的绝招。\n"NOR);
             }
                 else
                 tell_object  (me,HIR"你对天下无狗这招有了更深的了解。\n"NOR);
        }
        else
        {
                tell_object(me,HIR"你心烦意乱，费尽心神也难以领悟。\n"NOR);
        }
        addn("qi", -100, me);
        addn("jing", -100, me);
        addn("neili", -100, me);
        addn("jingli", -100, me);
        if (!wizardp(me)) me->start_busy(2+random(5));
        return 1;

}