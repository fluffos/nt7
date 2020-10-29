// xiuxi.c 玉女心经修习exert
// by April 01/08/09
// update April 01/09/22

string *phases = ({
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

int exert(object me)
{
        object         where = environment(me);
        int xj_lvl = (int)me->query_skill("yunv-xinfa", 1);        //玉女心经等级
        int force_lvl = (int)me->query_skill("force", 1);                //基本内功等级
        int v,i,j,k;                // 临时变量
        string *sname;        // skill名字
        object *inv;
        mapping skl;        // 所有skill

        seteuid(getuid());

        return notify_fail("本功能暂时没有开放！\n");
        
        if( query("pigging", where) )
                return notify_fail("你还是专心拱猪吧！\n");

        if( query("sleep_room", where) )
                return notify_fail("在睡房里不能练玉女心经，这会影响他人。\n");

        if( query("no_fight", where) )
                return notify_fail("在这里练玉女心经，你始终心烦意乱，无法克制，只得作罢。\n");

        if( me->is_busy() || query_temp("pending/exercising", me) )
                return notify_fail("你现在正忙着呢。\n");

        if( me->is_fighting() )
                return notify_fail("战斗中不能练玉女心经，会走火入魔。\n");

        if( !stringp(me->query_skill_mapped("force")) )
                return notify_fail("你必须先用 enable 选择你要用的内功心法。\n");

        if( query_temp("is_riding", me) )
                return notify_fail("在坐骑上运功，会走火入魔的。\n");

        // 基本内功小于玉女心经60%不能练
        if( force_lvl < xj_lvl*60/100)
                return notify_fail("你的基本功火候未到，必须先打好基础才能继续提高。\n");

        if( me->query_skill_mapped("force") != "yunv-xinfa" )
                return 0;

        // lvl小于25不能练
        if (xj_lvl<25)
                return notify_fail("你试着运了一下体内真气，显然玉女心经修为不够，真气无法运转。\n");

        // 必须空手
        if( query_temp("weapon", me) )
        return notify_fail("练习玉女心经必须空手，静坐诚心方可。\n");

        // 必须裸体
        inv = all_inventory(me);
        for(i=0; i<sizeof(inv); i++)
                if( query("equipped", inv[i] )
                         && query("armor_type", inv[i]) == "cloth" )
                        i = sizeof(inv)+1;
        if (i==sizeof(inv)+2)
        return notify_fail("练习玉女心经必须衣襟敞开方能及时散发热气。\n");

        // 四周必须无异性
        inv = all_inventory(environment(me));
        for (i=0; i<sizeof(inv); i++) 
                if( query("race", inv[i]) == "人类"
                        && inv[i] != me && !me->is_spouse_of(inv[i]) 
                         && query("gender", inv[i]) != query("gender", me) )
                return notify_fail("众目睽睽之下脱光衣裳练功，你不嫌害臊吗？！\n");

        // 内功要纯，否则大伤元气
        skl=this_player()->query_skills();
        sname=sort_array( keys(skl), (: strcmp :) );
        for(v=0; v<sizeof(skl); v++) {
                if (SKILL_D(sname[v])->check() == "force")
                        k++;
        }
        if ( k >=2 ) {
                // 这里加伤害
        set("neili", 0, me);
        set("jingli", 50, me);
        set("qi", 50, me);
                i=(query("max_jing", me)*65/100);
                set("eff_jing", i, me);
                return notify_fail("你体内不同内力互相冲撞，翻江倒海，难以克制。 \n"
                        +"你猛一咬牙，狂喷一口热血，才不至于走火入魔。\n");
        }

        if( query("neili", me)<query("max_neili", me)*60/100 )
                return notify_fail("你体内的真气不够修习玉女心经。\n");

        if( query("eff_qi", me)<query("max_qi", me) )
                return notify_fail("你身受内伤，只怕一运真气便有生命危险！\n");

        if( query("eff_jing", me)<query("max_jing", me) )
                return notify_fail("你中的毒没完全好，只怕一运真气便有生命危险！\n");

        if( query("jing", me)<query("max_jing", me)*90/100 )
                return notify_fail("你现在精不够，无法控制内息的流动！\n");

        if( query("qi", me)<query("max_qi", me)*60/100 )
                return notify_fail("你现在的气太少了，无法产生内息运行全身经脉。\n");

        // 不能靠练习过关 ---- 30n-1时必须过关
        if ( (xj_lvl<270) && ((xj_lvl+1)/30*30 == xj_lvl + 1) )
                return notify_fail("你继续练习着玉女心经，忽然体内真气一滞... \n"
                        +"你似乎遇到了无法突破瓶颈，看来是时候过关了。 \n");

        write("你盘膝坐下，缓缓地长舒一口气，一股暖流开始在体内流动。\n");

        set_temp("pending/xiuxi", 1, me);
        message_vision("$N盘膝坐下，开始修炼上乘内功。\n", me);
        me->start_busy((: xiuxi :), (:halt_xiuxi:));
        
        return 1;
}

int xiuxi(object me)
{
        int qi_cost;        //气消耗
        int jingli_cost;        //精力消耗
        int neili_gain;                //内力报酬
        int xj_gain;        //心经报酬
        int sx_gain;        //素心诀报酬
        int xj_lvl = (int)me->query_skill("yunv-xinfa",1);        //心经级别
        int force_lvl = (int)me->query_skill("force",1);        //基本内功级别
        object  where = environment(me);
        object *inv;
        int i;

        if( me->query_skill_mapped("force") != "yunv-xinfa" ){
                set_temp("pending/xiuxi", 0, me);
                return 0;
        }

        if( me->is_fighting() ){
                set_temp("pending/xiuxi", 0, me);
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
                return 0;
        }

        // 四周必须无人
        inv = all_inventory(environment(me));
        for (i=0; i<sizeof(inv); i++) 
                if( query("race", inv[i]) == "人类"
                        && inv[i] != me && !me->is_spouse_of(inv[i])
                         && query("gender", inv[i]) != query("gender", me)){
                        write("突然，你发现有人走了过来！\n你慌忙中止练功。\n");
                        set_temp("pending/xiuxi", 0, me);
                        return 0;
                }

        //计算消耗
        neili_gain = 1 + (int)me->query_skill("force") / 8;
        jingli_cost = to_int(sqrt(xj_lvl/to_float(150))*60);
        qi_cost = jingli_cost + neili_gain;

        if( query("qi", me)>query("max_qi", me)*30/100
                 && query("jingli", me)>query("max_jingli", me)*30/100
                && (xj_lvl>270 || (xj_lvl+1)/30*30 != xj_lvl+1) )
        {
                addn("neili", neili_gain, me);
                if( random(2))addn("combat_exp", 1, me);
                xj_gain = to_int(pow(force_lvl/4+1,1.1));
                sx_gain = xj_gain;
                if (!me->is_married()) sx_gain = sx_gain * (1+to_int(sqrt(me->query_skill("lovingness",1)/xj_lvl)));
                me->improve_skill("yunv-xinfa", xj_gain, 0);
                me->improve_skill("suxin-jue", sx_gain, 0);
                write(phases[random(6)]);
                me->receive_damage("qi", qi_cost, "练内功走火入魔死了");
                me->receive_damage("jingli", jingli_cost, "练内功走火入魔死了");

                  if( wizardp(me) ) tell_object(me, "每次得"+chinese_number(neili_gain)+"点内力，"
                        +chinese_number(xj_gain)+"点玉女心经，"
                        +chinese_number(sx_gain)+"点素心诀；\n"
                        +"消耗"+chinese_number(qi_cost)+"点气，"
                        +chinese_number(jingli_cost)+"点精力。\n");

                return 1;
        }
        else {
                set_temp("pending/xiuxi", 0, me);
                message_vision("$N运功完毕，内息轻吐，神情冷漠地站了起来。\n", me);
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
}

int halt_xiuxi(object me)
{
        if( query("neili", me)>query("max_neili", me)*2 )
        set("neili",query("max_neili",  me)*2, me);
        set_temp("pending/xiuxi", 0, me);
        message_vision("$N把正在运行的真气强行压回丹田，中止了修炼。\n", me);
        return 1;
}