// xiuxi.c 玉女心经修习exert
// by April 01/08/09
// update April 01/09/22

#include <ansi.h>

/*
$N同$n修习玉女心经一会的时间，头上的热气渐渐增多。
$N一边给$n输送真气一边将自己体内真气运行全身，热汗从头顶一点一点渗了出来！
$n受$N真气的帮助，玉女心经的境界又有了提高，身体被不停产生的白雾渐渐包围了！
*/

string *phases_me = ({
        "你正在修炼玉女心经，真气运行至“少阴”经“太阴”走“少阳” \n",
        "你终于功至“阳明”，头上产生微微白气正是内功到了火候之象！\n",
        "你修炼玉女心经已经有了一段时候，周身白雾丝丝缕缕，渐渐集聚。\n",
        "你加紧运功，真气行遍全身，练功时发出的热量变成的白气渐渐将你笼罩了起来，好象腾云驾雾一般！\n",
        "你修习玉女心经时间越来越长，头顶凝聚白气也越来越多，如同置身于蒸笼之中！\n",
        "你的真气运行得越来越畅快，身体所发的热气也越来越多，已将身体包围了起来！\n",
        "你只觉得一股股暖流自内而外缓缓发散，心底更加沉寂，无欲无喜。\n",
});

int xiuxi(object me);
int halt_xiuxi(object me);

int exert(object me, object target)
{
        object         where = environment(me);
        int xj_lvl_me = (int)me->query_skill("yunu-xinjing", 1);        //玉女心经等级me
        int force_lvl_me = (int)me->query_skill("force", 1);                //基本内功等级me
        int xj_lvl_target;         //玉女心经等级target
        int force_lvl_target;                //基本内功等级target
        int v,i,j,k;                // 临时变量
        string *sname;        // skill名字
        object *inv;        // 身上带的东西
        mapping skl;        // 所有skill

        seteuid(getuid());

        return notify_fail("本功能暂时没有开放！\n");
                
        if( !objectp(target) || target == me )
                return notify_fail("你要和谁一起练功啊？\n");

        //非婚男女只能在花房树屋练功
        if( query("gender", target) != query("gender", me )
                && !me->is_spouse_of(target)
                 && query("short", where) != "花房树屋" )
                return notify_fail("你们俩在一起练功？羞不羞啊！\n");

        xj_lvl_target = (int)target->query_skill("yunu-xinjing", 1);        //玉女心经等级
        force_lvl_target = (int)target->query_skill("force", 1);                //基本内功等级

        if( query("pigging", where) )
                return notify_fail("你还是专心拱猪吧！\n");

        if( query("sleep_room", where) )
                return notify_fail("在睡房里不能练玉女心经，这会影响他人。\n");

        if( query("no_fight", where) )
                return notify_fail("在这里练玉女心经，你始终心烦意乱，无法克制，只得作罢。\n");

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("你现在正忙着呢。\n");
        if( target->is_busy() || query_temp("pending/exercising", target) )
                return notify_fail("你的伙伴现在正忙着呢。\n");

        if( me->is_fighting() )
                return notify_fail("战斗中不能练玉女心经，会走火入魔。\n");
        if( target->is_fighting() )
                return notify_fail("等你的伙伴打完架再说吧。\n");

        if( !stringp(me->query_skill_mapped("force")) )
                return notify_fail("你必须先用 enable 选择你要用的内功心法。\n");
        if( !stringp(target->query_skill_mapped("force")) )
                return notify_fail("你的伙伴好像不喜欢玉女心经。\n");

        if( objectp(query_temp("is_riding", me)) )
                return notify_fail("在坐骑上运功，会走火入魔的。\n");
        if( objectp(query_temp("id_riding", target)) )
                return notify_fail("还是先让你的伙伴从坐骑上下来吧。\n");

        // 基本内功小于玉女心经60%不能练
        if( force_lvl_me < xj_lvl_me*60/100)
                return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");
        if( force_lvl_target < xj_lvl_target*60/100)
                return notify_fail("你的伙伴基本功太差了。\n");

        // lvl小于30不能练
        if (xj_lvl_me<30)
                return notify_fail("你试着运了一下体内真气，显然玉女心经修为不够，真气无法运转。\n");
        if (xj_lvl_target<30)
                return notify_fail("你的伙伴功力还不够。\n");

        // 必须空手
        if( query_temp("weapon", me) )
        return notify_fail("练习玉女心经必须空手，静坐诚心方可。\n");
        if( query_temp("weapon", target) )
        return notify_fail("先让你的伙伴把兵器放下吧。\n");

        // 必须裸体
        inv = all_inventory(me);
        for(i=0; i<sizeof(inv); i++)
                if( query("equipped", inv[i] )
                         && query("armor_type", inv[i]) == "cloth" )
                        i = sizeof(inv)+1;
        if (i==sizeof(inv)+2)
        return notify_fail("练习玉女心经必须衣襟敞开方能及时散发热气。\n");
        inv = all_inventory(target);
        for(i=0; i<sizeof(inv); i++)
                if( query("equipped", inv[i] )
                         && query("armor_type", inv[i]) == "cloth" )
                        i = sizeof(inv)+1;
        if (i==sizeof(inv)+2)
        return notify_fail("你的伙伴看来还不打算练功。\n");

        // 四周必须无异性
        inv = all_inventory(environment(me));
        for (i=0; i<sizeof(inv); i++) 
                if( query("race", inv[i]) == "人类"
                        && inv[i] != me && inv[i] != target
                        && !me->is_spouse_of(inv[i]) 
                         && query("gender", inv[i]) != query("gender", me) )
                return notify_fail("众目睽睽之下脱光衣裳练功，你不嫌害臊吗？！\n");

        // 内功要纯，否则大伤元气
        k=0;
        skl=me->query_skills();
        sname=sort_array( keys(skl), (: strcmp :) );
        for(v=0; v<sizeof(skl); v++) {
                if (SKILL_D(sname[v])->check() == "force")
                        k++;  
        }
        if ( k >=2 ) {
                return notify_fail("你感觉体内不同内力互相冲撞，只得作罢。\n");
        }
        k=0;
        skl=target->query_skills();
        sname=sort_array( keys(skl), (: strcmp :) );
        for(v=0; v<sizeof(skl); v++) {
                if (SKILL_D(sname[v])->check() == "force")
                        k++;  
        }
        if ( k >=2 ) {
                return notify_fail("你的伙伴内功不太纯啊!\n");
        }

        if( query("neili", me)<query("max_neili", me)*60/100 )
                return notify_fail("你体内的真气不够修习玉女心经。\n");
        if( query("neili", target)<query("max_neili", target)*60/100 )
                return notify_fail("你的伙伴真气不足。\n");

        if( query("eff_qi", me)<query("max_qi", me) )
                return notify_fail("你身受内伤，只怕一运真气便有生命危险！\n");
        if( query("eff_qi", target)<query("max_qi", target) )
                return notify_fail("你的伙伴身受内伤，先帮他疗伤吧！\n");

        if( query("eff_jing", me)<query("max_jing", me) )
                return notify_fail("你中的毒没完全好，只怕一运真气便有生命危险！\n");
        if( query("eff_jing", target)<query("max_jing", target) )
                return notify_fail("你的伙伴中的毒没完全好！\n");

        if( query("jing", me)<query("max_jing", me)*90/100 )
                return notify_fail("你现在精不够，无法控制内息的流动！\n");
        if( query("jing", target)<query("max_jing", target)*90/100 )
                return notify_fail("你的伙伴现在精不够，无法控制内息的流动！\n");

        if( query("jingli", me)<query("max_jingli", me)*60/100 )
                return notify_fail("你现在精力不够，无法控制内息的流动！\n");
        if( query("jingli", target)<query("max_jingli", target)*60/100 )
                return notify_fail("你的伙伴现在精力不够，无法控制内息的流动！\n");

        if( query("qi", me)<query("max_qi", me)*60/100 )
                return notify_fail("你现在的气太少了，无法产生内息运行全身经脉。\n");
        if( query("qi", target)<query("max_qi", target)*60/100 )
                return notify_fail("你的伙伴现在的气太少了，无法产生内息运行全身经脉。\n");

        // 不能靠练习过关 ---- 30n-1时必须过关
        if ( (xj_lvl_me<270) && ((xj_lvl_me+1)/30*30 == xj_lvl_me + 1) )
                return notify_fail("你继续练习着玉女心经，忽然体内真气一滞... \n"
                        +"你似乎遇到了无法突破瓶颈，看来是时候过关了。 \n");
        if ( (xj_lvl_target<270) && ((xj_lvl_target+1)/30*30 == xj_lvl_target +1 ) )
                return notify_fail("你的伙伴该过关了。\n");

        if( query_temp("pending/xiuxi", target) != me )
        {
                set_temp("pending/xiuxi", target, me);
                message_vision("\n$N对著$n说道：" 
                        + RANK_D->query_self(me) 
                        + me->name() + "，请问能和"
                        + RANK_D->query_respect(target) + "一起修习玉女心经吗？\n\n", me, target);
                tell_object(target,YEL"如果你愿意和对方一起修习玉女心经，请你也对"+me->name()+"("+query("id", me)+")"+"下一次yunxiuxi2指令。\n"NOR);
                write(YEL "由于对方是由玩家控制的人物，你必须等对方同意才能共同修习玉女心经。\n" NOR);
                return 1;
        }
        else
        {
                message_vision("\n$N和$n解开衣衫，盘膝坐下，四掌相对，开始共同修习玉女心经。\n" , me, target);
                set_temp("pending/target", target, me);
                set_temp("pending/xiuxi", 2, me);
                me->start_busy((: xiuxi :), (:halt_xiuxi:));
                set_temp("pending/xiuxi", 2, target);
                set_temp("pending/target", me, target);
                target->start_busy((: xiuxi :), (:halt_xiuxi:));
        }
        
        return 1;
}

int xiuxi(object me)
{
        int qi_cost;        //气消耗
        int jingli_cost;        //精力消耗
        int neili_gain;                //内力报酬
        int xj_gain;        //心经报酬
        int love_gain;        //lovingness报酬
        int xj_lvl = (int)me->query_skill("yunu-xinjing",1);        //心经级别
        int force_lvl = (int)me->query_skill("force",1);        //基本内功级别
        float f,g,h;        //可变参数
        string wiz_report;        //巫师报告
        object where = environment(me);        //地理环境
        object target=query_temp("pending/target", me);//伙伴
        int xj_lvl_target = (int)target->query_skill("yunu-xinjing",1);        //伙伴心经级别
        object *inv;
        int i;

        //伙伴停就停
        if( query_temp("pending/xiuxi", target) != 2 )
        {
                message_vision("$N把正在运行的真气强行压回丹田，中止了修炼。\n", me);
                set_temp("pending/xiuxi", 0, me);
                set_temp("pending/target", me, me);
                if( query("neili", me)<query("max_neili", me)*2);
                else {
                        if( query("max_neili", me)>me->query_skill("force")*query("con", me)*2/3){
                                write("你的内力修为似乎已经达到了瓶颈。\n");
                                set("neili",query("max_neili",  me), me);
                        }
                        else {
                                addn("max_neili", 1, me);
                                set("neili",query("max_neili",  me), me);
                                write("你的内力增加了！！\n");
                        }
                }
                return 0;
        }

        if( me->query_skill_mapped("force") != "yunu-xinjing" ){
                set_temp("pending/xiuxi", 0, me);
                set_temp("pending/target", me, me);
                return 0;
        }

        if( me->is_fighting() ){
                set_temp("pending/xiuxi", 0, me);
                set_temp("pending/target", me, me);
                return 0;
        }

        // 必须裸体
        inv = all_inventory(me);
        for(i=0; i<sizeof(inv); i++)
                if( query("equipped", inv[i] )
                         && query("armor_type", inv[i]) == "cloth" )
                        i = sizeof(inv)+1;
        if (i==sizeof(inv)+2){
        set("neili", 0, me);
        set("jingli", 50, me);
        set("qi", 50, me);
                i=(query("max_jing", me)*65/100);
                set("eff_jing", i, me);
                write("突然，你体内热气逐渐积聚，无法发散！热气顿时在五脏六腑翻江倒海，难以克制。 \n"
                        +"你猛一咬牙，狂喷一口热血，才不至于走火入魔。\n");
                set_temp("pending/xiuxi", 0, me);
                set_temp("pending/target", me, me);
                return 0;
        }

        inv = all_inventory(environment(me));
        for (i=0; i<sizeof(inv); i++) 
                if( query("race", inv[i]) == "人类"
                        && inv[i] != me && inv[i] != target
                        && !me->is_spouse_of(inv[i]) 
                         && query("gender", inv[i]) != query("gender", me)){
                                write("突然，你发现有人走了过来！\n你们慌忙中止练功。\n");
                                set_temp("pending/xiuxi", 0, me);
                                set_temp("pending/target", me, me);
                                return 0;
                }

        //计算消耗和所得，这是复杂的算法
        neili_gain = 1 + (int)me->query_skill("force") / 8;
        jingli_cost = to_int(sqrt((xj_lvl/to_float(150)))*60);
        qi_cost = jingli_cost + neili_gain;

        if( query("qi", me)>query("max_qi", me)*30/100
                 && query("jingli", me)>query("max_jingli", me)*30/100
                &&         ((xj_lvl>270) || ((xj_lvl+1)/30*30 != xj_lvl+1)))
        {
                addn("neili", neili_gain, me);
                addn("combat_exp", 1, me);
/*
                f=to_float(query("combat_exp", target))/to_float(query("combat_exp", me));
                if (f>=2) f=2;
                else if (f>=0.5) f = to_float(1.8*pow(f-0.5,0.25));
                else f=0;
                xj_gain = to_int(pow(force_lvl/4+1,1.1)*f);
*/
                if (xj_lvl_target > xj_lvl * 2/3 ) xj_gain = to_int(pow(force_lvl/4+1,1.1)*1.5);
                else xj_gain = to_int(pow(force_lvl/4+1,1.1)*1.2);

                if (me->is_spouse_of(target)){
                        xj_gain *= 1.5;
                        love_gain =xj_gain*2;
                }
                else if( query("gender", me) != query("gender", target))xj_gain*=1.2;
                me->improve_skill("yunu-xinjing", xj_gain, 0);
                write(phases_me[random(6)]);
                me->receive_damage("qi", qi_cost, "练内功走火入魔死了");
                me->receive_damage("jingli", jingli_cost, "练内功走火入魔死了");

                wiz_report = "每次得"+chinese_number(neili_gain)+"点内力，"
                        +chinese_number(xj_gain)+"点玉女心经";
                if (me->is_spouse_of(target)){
                        wiz_report = wiz_report+chinese_number(love_gain)+"点双栖双飞";
                        me->improve_skill("lovingness", love_gain, 0);
                }
                wiz_report = wiz_report + "; \n 消耗" + chinese_number(qi_cost) + "点气，"
                        +chinese_number(jingli_cost)+"点精力。\n";

                  if( wizardp(me) ) tell_object(me, wiz_report);

                return 1;
        }
        else {
                set_temp("pending/xiuxi", 0, me);
                message_vision("$N和$n运功完毕，内息轻吐，神态轻松地站了起来。\n", me,target);
                if( query("neili", me)<query("max_neili", me)*2);
                else {
                        if( query("max_neili", me)>me->query_skill("force")*query("con", me)*2/3){
                                write("你的内力修为似乎已经达到了瓶颈。\n");
                                set("neili",query("max_neili",  me), me);
                        }
                        else {
                                addn("max_neili", 1, me);
                                set("neili",query("max_neili",  me), me);
                                write("你的内力增加了！！\n");
                        }
                }
                set_temp("pending/xiuxi", 0, me);
                set_temp("pending/target", me, me);
                return 0;
        }
}

int halt_xiuxi(object me)
{
        if( query("neili", me)>query("max_neili", me)*2 )
        set("neili",query("max_neili",  me)*2, me);
        set_temp("pending/xiuxi", 0, me);
        set_temp("pending/target", me, me);
        message_vision("$N把正在运行的真气强行压回丹田，中止了修炼。\n", me);
        return 1;
}
