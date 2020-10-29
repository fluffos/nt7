
#include <ansi.h>

#define HUA "「" MAG "虚空之痕" NOR "」"

inherit F_SSERVER;

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        object landie;
        object *obs, wanjia, env;
        string msg;
        
        if (! objectp(me))return 1;
        
        // 只有剑灵可以用
        if (base_name(me) != "/kungfu/class/misc/jianling")
                return notify_fail("你所使用的外功中没有这个功能。\n");

        // 蓝蝶仙子还存在时候不能用
        landie=query("mylandie", me);
        if (objectp(landie))return 1;
        
        // 距离上次蓝蝶消失不足3分钟无法施展
        if( query("first_landie", me))//已经召唤过蓝蝶才受此限制
        {
                if( time()-query("last_summon_landie", me)<180 )
                        return 1; 
        }

        msg = HIC "$N" HIC "深吸一口气，手中蓝蝶宝剑顿时光芒暴现，在天空划出一道美丽的弧线 ……"
              "顿时，天空之中撕开一条裂缝，犹如女娲补天时的虚空之痕！一道蓝光从裂缝中蔓出，万千"
              "光芒笼罩，一位美丽的仙子从天而降，守护着剑灵！\n" NOR;

        // 记录本次是否是第一次召唤蓝蝶
        if( !query("first_landie", me) )
                set("first_landie", 1, me);

        env = environment(me);
        // 初始化蓝蝶仙子
        landie = new("/kungfu/class/misc/landie-xianzi");
        // 随机选择当前房间一名玩家
        obs = all_inventory(env);
        obs = filter_array(obs, (: userp($1) :));
        
        if (! sizeof(obs))
        {
                destruct(landie);
                write("没有找到玩家！\n");
                return 1;
        }

        wanjia = obs[random(sizeof(obs))];      
        if( !objectp(obs) )
        {
                destruct(landie);
                return 1;
        }
        landie->init_me(me, wanjia);
        landie->move(env);
        
        set("mylandie", landie, me);

        msg += HIY "\n$n" HIY "凝神观望，似乎看破了蓝蝶仙子的破绽。\n" NOR;
        
        message_vision(sort_msg(msg), me, wanjia);
        
        return 1;
}
