// make.c

#include <ansi.h>
#include <medical.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object qm;
        object hob;
        string med;
        mapping make;
        mapping req;
        mapping herb;
        string *ks;
        object *hlist;
        string msg;
        int only_list;
        int i;
        object hob2;

        if (! arg)
        {
                make=query("can_make", me);
                if (! mapp(make))
                        return notify_fail("你现在不会制任何药物。\n");

                ks = keys(make);
                msg = "你现在已经会制";
                if (sizeof(ks) >= 2)
                        msg += implode(ks[0..sizeof(ks) - 2], "、") +
                                "和" + ks[sizeof(ks) - 1] + "了。\n";
                else
                        msg += ks[0] + "了。\n";
                msg = sort_string(msg, 64);
                write(msg);
                return 1;
        }

        // only for list?
        only_list = sscanf(arg, "%s ?", arg);

        if( !stringp(med=query("can_make/"+arg, me)) )
                return notify_fail("你还不会配这种药啊！\n");

        // The player can only make the medicine under the /clone/medicine,
        // nothing, but for save memory.
        med = MEDICINE(med);
        if (file_size(med + ".c") < 0)
                return notify_fail("这种药方好像已经失传了？你还是问问巫师吧。\n");
                
        //tell_object(me, "test:" + med + "\n");
        if (med == "/clone/medicine/yuqing") {
/*
                        if( (query("online_time", me) > 86400 * 31) ) {
                                if (!sscanf(base_name(environment(me)), "/d/dongtian/%*s/liandanfang"))
                                return notify_fail("你不是新人了，找个洞天炼丹房去炼制吧。\n");
                } else {        
                        if (!sscanf(base_name(environment(me)), "/d/dongtian/%*s/liandanfang") && 
                                !sscanf(base_name(environment(me)), "/temp/qroom/%*s"))
                                return notify_fail("这种丹药从飞星法阵进入天生石梁最里面可以炼制。\n");
                }
*/
                if (query("doing", me) && !interactive(me))
                        "/cmds/usr/scheme.c"->cancel_schedule(me);
        }

        if (! mapp(req = query("mixture", get_object(med))))
                return notify_fail(med->name() + "好像无法配制...\n");

        if (! mapp(herb = req["herb"]))
                return notify_fail(med->name() + "需要什么原料呢...\n");

        if (only_list)
        {
                // show herb
                write("炼制" + arg + "需要以下这些药材：\n");
                ks = keys(herb);
                for (i = 0; i < sizeof(ks); i++)
                {
                        write(chinese_number(herb[ks[i]]) + query("base_unit", get_object(HERB(ks[i]))) +
                              HERB(ks[i])->name() + "\n");
                }
                return 1;
        }

        if (me->is_fighting())
                return notify_fail("打架的时候你还有闲工夫配药？\n");

        if (me->is_busy())
                return notify_fail("还是先把手头的事情忙完吧。\n");

        if( query("no_fight", environment(me)) && 0 )
                return notify_fail("你在这里制药只怕要打扰到别人。\n");

        qm=query_temp("handing", me);
        if (! qm)
                return notify_fail("你的先把能够磨药的研钵拿(hand)在手上才行。\n");

        if (! qm->can_make_medicine())
                return notify_fail(qm->name() + "好像无法发挥研钵的作用吧。\n");

        if (sizeof(all_inventory(qm)) > 0)
                return notify_fail("你还是先把" + qm->name() + "里面的东西拿出来再说。\n");

        if( query("jing", me)<query("max_jing", me)*7/10 )
                return notify_fail("你现在精神难以集中，无法配药。\n");

        ks = keys(req) - ({ "herb", "neili", "jing", "jingli", "min_level", "time" });

        // check skills
        for (i = 0; i < sizeof(ks); i++)
                if (me->query_skillo(ks[i], 1) < req[ks[i]])
                        return notify_fail("你的" + to_chinese(ks[i]) +
                                           "水平不够，还无法调剂" +
                                           med->name() + "。\n");
    
    //血脉丹以外可以不耗药材                                       
        if ((!get_object(med)->is_xuemai_dan()) && base_name(qm)=="/clone/goods/tiandilu") {
                        switch(random(3))
                                {
                                        case 0:
                                                hob2 = present("sheli zi", me);
                                                if ((!hob2) || base_name(hob2)!="/clone/fam/pill/sheli1")
                                                        hob2 = 0;
                                                set_temp("tiandilu/type", 1, me);       
                                                break;
                                        case 1:
                                                hob2 = present("xue puti", me);
                                                if ((!hob2) || base_name(hob2)!="/clone/fam/pill/puti1")
                                                        hob2 = 0;
                                                set_temp("tiandilu/type", 2, me);       
                                                break;
                                        case 2:
                                                hob2 = present("haotian guo", me);
                                                if ((!hob2) || base_name(hob2)!="/clone/fam/pill/linghui1")
                                                        hob2 = 0;
                                                set_temp("tiandilu/type", 3, me);
                                                break;
                                }
        }
        if (hob2) {// && 
                //query_temp("tiandilu/cdtime", me) < time()) {
                        //set_temp("tiandilu/cdtime", time() + 21 + random(10), me);
                        message_vision(NOR CYN "$N拿出一" + query("base_unit", hob2) + hob2->name() + NOR CYN "塞进嘴里几把嚼烂，\n紧跟着喷出一口灵气灌注到$n" NOR CYN "里代替药材。\n" NOR, me, qm);
                        hob2->add_amount(-1);
        } else {
                delete_temp("tiandilu/type", me);

        // check herb
        ks = keys(herb);
        hlist = allocate(sizeof(ks));
        for (i = 0; i < sizeof(ks); i++)
        {
                hob = present("herb_" + ks[i], me);
                            if (! hob || (hob->query_amount() < herb[ks[i]] && (base_name(hob)!="/clone/herb/dimai" && base_name(hob)!="/clone/herb/yulu" )) )
                {
                        if (file_size(HERB(ks[i]) + ".c") < 0)
                        {
                                write("没有(" + ks[i] + ")这种药材啊！"
                                      "怎么回事？\n");
                                return 1;
                        }
                        return notify_fail("你点了点药材，发现" +
                                           HERB(ks[i])->name() +
                                           "的分量还不够。\n");
                }
                hlist[i] = hob;
        }

        // decrease herb
        msg = "你选出";
        for (i = 0; i < sizeof(ks); i++)
        {
                if (i) msg += "、";
                msg += chinese_number(herb[ks[i]]) +
                       query("base_unit", hlist[i])+
                       hlist[i]->name();
                hlist[i]->add_amount(-herb[ks[i]]);
              if( base_name(hlist[i])=="/clone/herb/dimai" || base_name(hlist[i])=="/clone/herb/yulu")
              destruct(hlist[i]);
        }
        msg += "，然后小心翼翼的把它们放到" + qm->name() + "里面，开始制药。\n";
        msg = sort_string(msg, 64);
        write(msg);
    }
    
        message("vision", me->name() + "东摸摸，西弄弄，不知道在干啥。\n",
                environment(me), ({ me }));
        me->start_busy(bind((:call_other, __FILE__, "making" :), me),
                       bind((:call_other, __FILE__, "halt_make" :), me));
        me->set_short_desc("正在专心致志的炼制药物。");
        set_temp("pending/making", 0, me);
        set_temp("making/medicine", med, me);
        if (base_name(qm)=="/clone/goods/tiandilu") 
                set_temp("making/time", req["time"] / 2, me);
        else
                set_temp("making/time", req["time"], me);
        set_temp("making/require", req, me);
        set_temp("making/container", qm, me);
        return 1;
}

int stop_making(object me)
{
        object qm;
        delete_temp("making", me);
        delete_temp("pending/making", me);
        me->set_short_desc(0);
        if (qm = query_temp("tiandilu/bomb", me)) {
                        message_vision(NOR BLINK HIY "\n$N手中的" + qm->name() + NOR BLINK HIY "“嘭~~”地一声，爆炸了。\n\n" NOR , me);
                        if (!random(100)) {
                                set_temp("die_reason", "被"+ qm->name() +"炸得四分五裂了", me);
                                me->die(qm);
                        }
                        destruct(qm);
        }
        return 0;
}

int making(object me)
{
        int step;
        int level;
        mapping req;
        string msg_me, msg_out;
        string med, obname;
        object ob, ob2;
        object qm;
                int flag_jiu;

        step=query_temp("pending/making", me);
        req=query_temp("making/require", me);
        med=query_temp("making/medicine", me);
        qm=query_temp("making/container", me);
        if( qm != query_temp("handing", me) )
        {
                write("嗯？研钵呢...？我的研钵！\n");
                return stop_making(me);
        }
        if (base_name(qm)=="/clone/goods/jiulonglu") flag_jiu = 1;
        if (base_name(qm)=="/clone/goods/tiandilu") flag_jiu = 2;
        
        if (flag_jiu>1 && step>0 && step<3 && (!random(15)) && random(me->query_kar())>10 && 
                query_temp("tiandilu/cdtime", me) < time() ) {
                set_temp("tiandilu/cdtime", time() + 11 + random(25), me);
                step = 8;
                message_vision(NOR CYN "天空无数紫电降下，$N" NOR CYN "的" + HIC "天" HIK "地" HIR "洪炉" + NOR CYN "“嗡嗡~~”地透出声声龙吟。\n" , me);
        }

        switch (step)
        {
        default:
                step = 0;
                msg_me = "你拿起棒杵，慢慢的捣着" + qm->name() + "里面的药材。\n";
                msg_out = "$N拿起棒杵叮咣叮咣的捣得很起劲。\n";
                break;
        case 1:
                msg_me = "扑哧扑哧，药材眼见变成了一块块小碎块。\n";
                msg_out = "$N没完没了的捣鼓。\n";
                break;
        case 2:
                msg_me = "你轻轻的研磨着药材，让它越来越细。\n";
                msg_out = "$N紧张的磨着东西。\n";
                break;
        case 3:
                msg_me = "你接着把那些残留的大块儿一点的药材捣碎。\n";
                msg_out = "$N突然又叮咣叮咣的捣个不停。\n";
                break;
        case 4:
                msg_me = "你细细的将所有的药材磨成了粉末。\n";
                msg_out = "$N拿着棒杵磨来磨去。\n";
                break;
        case 5:
                msg_me = "你轻轻的合上" + qm->name() +
                         "，默默的运用内力，烘培里面的药材。\n";
                msg_out = "$N合上" + qm->name() + "，双手抱着，不知道在干什么。\n";
                break;
        case 6:
                if( query("jing", me)<req["jing"] )
                {
                        write("你觉得精神不济，看来难以继续调剂「" +
                              med->name() + "」。\n");
                        return stop_making(me);
                }
                        
        
                if( query("neili", me)<req["neili"] )
                {
                        write("你觉得内力不济，看来难以继续调剂「" +
                              med->name() + "」。\n");
                        return stop_making(me);
                }
        
                if( query("jingli", me)<req["jingli"] )
                {
                        write("你觉得精力不济，看来难以继续调剂「" +
                              med->name() + "」。\n");
                        return stop_making(me);
                }
        
                me->receive_damage("jing", req["jing"]);
                addn("neili", -req["neili"], me);
                addn("jingli", -req["jingli"], me);

                if( me->add_temp("making/time",-1)>0 )
                {
                        // when time > 0, next busy stage will
                        // still at 6, becuase the step will be
                        // increase by 1 later, so I decrase it
                        // first
                        step--;
                }

                msg_me = random(2) ? "你觉得" + qm->name() + "慢慢的热了起来，感"
                                     "觉到里面的药材似乎已经融化了。\n"
                                   : "你不断的将内力传入" + qm->name() + "，发热"
                                     "使里面的药材融化合一。\n";
                msg_out = random(2) ? "$N像老和尚一样闭目冥神坐在那里。\n"
                                    : "$N手里握着" + qm->name() + "没完没了的转来转去。\n";

                break;
        case 7:
                msg_me = "你运用内力，隔着" + qm->name() + "使里面的药材彻底的融合。\n";
                msg_out = "$N眉毛动了动，接着又像老和尚一样闭目冥神坐在那里。\n";
                break;
        case 8:
                msg_me = "你长吁了一口气，慢慢的把手拿开，打开了" + qm->name() + "。\n";
                msg_out = "$N长吁了一口气，慢慢的把手拿开，打开了" + qm->name() + "。\n";
                break;
        case 9:
                if ((random(me->query_skill("medical", 1) +
                     query("item_prop/medical", qm)) >= req["min_level"]) ||
                    (me->query_skillo("liandan-shu", 1) + query("item_prop/liandan-shu", qm)) >= req["liandan-shu"]+100 )
                {
                        //level = req["liandan-shu"]/300;
                        ob = new(med);
                        obname = ob->name();
                        //set("drug_grade", level, ob);
                        ob->move(qm, 1);
                        if (flag_jiu && 
                                ((!random(8)) || (random(me->query_skillo("liandan-shu", 1) + query("item_prop/liandan-shu", qm)) > 5000) ) && 
                                sscanf(base_name(environment(me)),"/d/dongtian/%*s/liandanfang")) {
                                new(med)->move(qm, 1);
                                message_vision(NOR CYN "炼丹房里" YEL "金龙" NOR CYN "虚影游动吞吐，大量灵气聚集在$N手中的" + qm->name() + NOR CYN "上。\n" , me);
                                tell_object(me, NOR + " (" HIG + "你手里的" + NOR + qm->name() + NOR + HIG + "一阵剧烈震动，" + obname + NOR + HIG + "的数量＋１。" NOR ")\n");
                                if (flag_jiu>1 && random(2)) {
                                        new(med)->move(qm, 1);
                                        message_vision(NOR CYN "炼丹房里" YEL "金龙" NOR CYN "虚影游动吞吐，大量灵气聚集在$N手中的" + qm->name() + NOR CYN "上。\n" , me);
                                    tell_object(me, NOR + " (" HIG + "你手里的" + NOR + qm->name() + NOR + HIG + "一阵剧烈震动，" + obname + NOR + HIG + "的数量＋１。" NOR ")\n");
                                        if (random(me->query_skillo("liandan-shu", 1) + query("item_prop/liandan-shu", qm))>7500 && random(me->query_kar())>26 && random(2)) {
                                                new(med)->move(qm, 1);
                                                message_vision(NOR CYN "炼丹房里" YEL "金龙" NOR CYN "虚影游动吞吐，大量灵气聚集在$N手中的" + qm->name() + NOR CYN "上。\n" , me);
                                            tell_object(me, NOR + " (" HIG + "你手里的" + NOR + qm->name() + NOR + HIG + "一阵剧烈震动，" + obname + NOR + HIG + "的数量＋１。" NOR ")\n");
                                        }
                                        if (random(me->query_skillo("liandan-shu", 1) + query("item_prop/liandan-shu", qm))>10000 && random(2)) {
                                                new(med)->move(qm, 1);
                                                message_vision(NOR CYN "炼丹房里" YEL "金龙" NOR CYN "虚影游动吞吐，大量灵气聚集在$N手中的" + qm->name() + NOR CYN "上。\n" , me);
                                            tell_object(me, NOR + " (" HIG + "你手里的" + NOR + qm->name() + NOR + HIG + "一阵剧烈震动，" + obname + NOR + HIG + "的数量＋１。" NOR ")\n");
                                        }
                                }
                        }
                        if (random(4) && query_temp("tiandilu/type", me)) {
                                                        switch(query_temp("tiandilu/type", me))
                                                {
                                                        case 1:
                                                                ob2 = new("/clone/medicine/yuqing");
                                                                break;
                                                        case 2:
                                                                ob2 = new("/clone/gift/puti-zi");
                                                                break;
                                                        case 3:
                                                                ob2 = new("/clone/gift/jiuzhuan");
                                                                break;
                                                }
                                                        delete_temp("tiandilu/type", me);
                                        message_vision(NOR HIC "$N手中的" + qm->name() + NOR HIC "里额外凝聚出了" + ob2->name() + NOR HIC "。\n" NOR , me);
                                        ob2->move(qm, 1);
                                        if (!random(200000)) {
                                                set_temp("tiandilu/bomb", qm, me);
                                        }
                        }
                        msg_me = HIM "你把「" + obname + HIM "」成功的制好了！\n" NOR;
                        msg_out = HIM "$N" HIM "嘴角露出一丝微笑。\n" NOR;
                        me->improve_skill("liandan-shu", me->query_int()*100+100); 
                }else if( !query("special_skill/lucky", me) || random(2) == 0 )
                {
                        msg_me = HIG "真令人沮丧！居然失败了，真是可惜了。\n" NOR;
                        msg_out = HIG "$N" HIG "一脸沮丧，不"
                                  "知道发生了什么倒霉事。\n" NOR;
                }else
                {
                        ob = new(med);
                        ob->move(qm, 1);
                        msg_me = HIM "你感觉似乎有什么地方没有做对，然而你的运气实在太好了！\n你把「" + ob->name() + HIM "」成功的制好了！\n" NOR;
                        msg_out = HIM "$N" HIM "嘴角露出一丝微笑。\n" NOR;
                        me->improve_skill("liandan-shu", me->query_int()*10+10); 
                }
                break;
        }

        msg_out = replace_string(msg_out, "$N", me->name());
        message("vision", msg_me, me);
        message("vision", msg_out, environment(me), ({ me }));
        step++;
        if (step >= 10)
                // end of making
                return stop_making(me);

        set_temp("pending/making", step, me);
        return 1;
}

int halt_make(object me)
{
        message_vision("$N把手中的研钵一翻个，东西"
                       "全都倒了出来。\n", me);
        stop_making(me);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : make [<药品>] [?]

这个指令可以让你炼制某样药品，如果没有指明药品则会列出当前
你会炼制的药品。如果在指明的药品后面添加一个"?" 则会列出炼
制这种药品需要的材料。

HELP );
    return 1;
}
