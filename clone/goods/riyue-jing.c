#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "日" HIY "月" NOR + WHT "镜" NOR, ({ "riyue jing", "riyue", "jing" }) );
        set_weight(3000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/
        {
                set("unit", "面");
                set("long", HIC "传说女娲创造生灵的时候，为了时刻监视生灵的一举一动，\n"
                                "于是请求上天赐予了她一面宝镜，名曰日月镜，拥有日月\n"
                                "镜的人可以随时查看到游戏中的生物、玩家及NPC的位置。\n"
                                "每次使用消耗黄金一两，即从银行扣除。\n" HIY
                                "指令： echo 生物英文ID\n" NOR);
                set("value", 800000);
                
        }
        set("can_summon", 1);
        setup();
}

void init()
{
        add_action("do_echo", "echo");
}

int do_echo(string arg)
{

        object me, target;
        string where;
        
        me = this_player();

        if (environment(this_object()) != me)return 0;

        if (! arg)return notify_fail("指令格式： echo 生物英文ID\n");

        target = find_living(arg);

        if (! objectp(target))
                return notify_fail(HIG "日月镜发出一道亮光：没有找到目标生物，可能该生物不存在或未被更新！\n" NOR);
                
        // 不能查看隐身ID及巫师
        if (wizardp(target))
                return notify_fail(HIG "日月镜发出一道亮光：没有找到目标生物，可能该生物不存在或未被更新！\n" NOR);
                
        // 扣除YSG
        if( query("balance", me)<10000 )
                return notify_fail("对不起，你的银行存款不足，无法使用日月镜！\n");        
        
        if( (query_temp("apply/invisible", target) && !me->query_condition("niuyanlei")) || query("env/invisible", target) )
                return notify_fail(HIG "日月镜发出一道亮光：没有找到目标生物，可能该生物不存在或未被更新！\n" NOR);

        addn("balance", -10000, me);

        if (! environment(target))
                return notify_fail("对不起，该对象无法查询到具体位置。\n");

        where = query("short", environment(target)) ? query("short", environment(target)) 
                                                                 : environment(target)->short();

        tell_object(me, HIG "日月镜发出一道亮光：" + target->name() + "(" + arg + ")现在在" + 
                         where + HIG "。\n" NOR);

        return 1;
}

int query_autoload()
{
        return 1;
}
