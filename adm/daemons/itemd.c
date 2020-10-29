// This program is a part of NT MudLIB
// itemd.c

// #pragma optimize
// #pragma save_binary

#include <ansi.h>
#include <command.h>

void create() { seteuid(getuid()); }

int gift_point() { return 1; }
// 可以用来浸透的物品列表：必须是物品的base_name
string *imbue_list = ({
        "/d/shenlong/obj/hua4",
        "/clone/gift/puti-zi",
        "/clone/gift/xiandan",
        "/clone/gift/xisuidan",
        "/clone/gift/jiuzhuan",
        "/clone/gift/tianxiang",
        "/clone/gift/xuanhuang",
});

// 浸入的次数的随机界限：如果每次IMBUE以后取0-IMBUE次数的随机
// 数大于这个数值，则IMBUE最终成功。
#define RANDOM_IMBUE_OK         100

// 每次浸入需要圣化的次数
#define SAN_PER_IMBUE           5

// 杀了人以后的奖励
void killer_reward(object me, object victim, object item)
{
        int exp;
        mapping o;
        string my_id;

        if (!me || !victim)
                return;

        if( !query("can_speak", victim) )
                // only human does effect
                return;

        // record for this weapon
        if (victim->is_not_bad())  addn("combat/WPK_NOTBAD", 1, item);
        if (victim->is_not_good()) addn("combat/WPK_NOTGOOD", 1, item);
        if (victim->is_good())     addn("combat/WPK_GOOD", 1, item);
        if (victim->is_bad())      addn("combat/WPK_BAD", 1, item);

        if (userp(victim))
                addn("combat/PKS", 1, item);
        else
                addn("combat/MKS", 1, item);

        exp=query("combat_exp", victim);
        if( exp<10000 || query("combat_exp", me)<exp*4/5 )
                return;

        exp /= 10000;
        if (exp > 250) exp = 100 + (exp - 250) / 16; else
        if (exp > 50) exp = 50 + (exp - 50) / 4;
        my_id=query("id", me);
        o=query("owner", item);
        if (!o) o = ([ ]);
        if (!undefinedp(o[my_id]) || sizeof(o) < 12)
                o[my_id] += exp;
        else
        {
                // Too much owner, I must remove one owner
                int i;
                int lowest;
                string *ks;

                lowest = 0;
                ks = keys(o);
                for (i = 1; i < sizeof(ks); i++)
                        if (o[ks[lowest]] > o[ks[i]])
                                lowest = i;
                map_delete(o, ks[lowest]);
                o += ([ my_id : exp ]);
        }
        set("owner", o, item);

        if (my_id == item->item_owner() && !random(10))
                addn("magic/blood", 1, item);
}

// 召唤物品
int receive_summon(object me, object item)
{
        object env;
        object temp;
        int type;

        if ((env = environment(item)) && env == me)
        {
                tell_object(me, item->name() + "不就在你身上"
                            "嘛？你召唤个什么劲？\n");
                return 1;
        }

        if( query("jingli", me)<200 )
        {
                tell_object(me, "你试图呼唤" + item->name() +
                            "，可是难以进入境界，看来是精力不济。\n");
                return 0;
        }
        addn("jingli", -200, me);

        if( query("id", me) == "lonely" )
        {
              message_sort(HIM "\n只见四周金光散布，祥云朵朵，远处有凤凰盘绕，麒麟逐戏。耳边"
                           "传来阵阵梵音。$N"HIM"一声长啸，"+query("name", item)+HIM
                           "破空而来 ……。\n\n" NOR, me);
        }
        else

              message_vision(HIW "$N" HIW "突然大喝一声，伸出右手凌空"
                             "一抓，忽然乌云密布，雷声隐隐。\n\n" NOR, me);

        if (env == environment(me))
        {
                message_vision(HIW "只见地上的" + item->name() +
                               HIW "应声而起，飞跃至$N" HIW
                               "的掌中！\n\n" NOR, me);
        } else
        {
                type = random(3);
                if (env)
                {
                        if (env->is_character() && environment(env))
                                        env = environment(env);

                        switch (type)
                        {
                        case 0:
                                message("vision", HIW "天空中传来隐隐的雷声"
                                        "，忽然电闪雷鸣，" + item->name() +
                                        HIW "腾空而起，"
                                        "消失不见！\n\n" NOR, env);
                                break;
                        case 1:
                                message("vision", HIC "一道神光从天而降"
                                        "，罩定了" + item->name() + HIC "，只见" +
                                        item->name() + HIC "化作长虹破空而"
                                        "走。\n\n" NOR, env);
                                break;
                        default:
                                message("vision", HIY "忽然间麝香遍地，氤氲弥漫，" +
                                        item->name() + HIY "叮呤呤的抖动数下，化作一"
                                        "道金光转瞬不见！\n\n" NOR, env);
                                break;
                        }

                        if (interactive(env = environment(item)))
                        {
                                tell_object(env, HIM + item->name() +
                                                 HIM "忽然离你而去了！\n" NOR);
                        }
                }

                switch (type)
                {
                case 0:
                        message_vision(HIW "一声" HIR "霹雳" HIW "，"
                                       "闪电划破长空，" + item->name() + HIW
                                       "从天而降，飞入$N" HIW "的手中！\n\n" NOR, me);
                        break;
                case 1:
                        if( query("id", item) == "lonely")break;

                        message_vision(HIW "一道" HIY "长虹" HIW "扫过"
                                       "天空，只见" + item->name() + HIW
                                        "落入了$N" HIW "的掌中！\n\n" NOR, me);
                        break;
                default:
                        message_vision(HIW "只见" + item->name() + HIW "呤呤作响，大"
                                       "放异彩，挟云带雾，突现在$N"
                                       HIW "的掌中！\n\n" NOR, me);
                        break;
                }
        }

        // 取消no_get属性
        delete_temp("stab_by", item);
        delete("no_get", item);

        item->move(me, 1);
        if (environment(item) != me)
                return 1;

        if( query("armor_type", item) )
        {
                // is armor
                temp = query_temp("armor/" + query("armor_type", item), me);
                if (temp) temp->unequip();
                WEAR_CMD->do_wear(me, item);
        } else
        if( query("skill_type", item) )
        {
                if( query("skill_type", item) == "throwing" )
                {
                        HAND_CMD->main(me,query("id", item));
                        return 1;
                }
                if( temp=query_temp("weapon", me) )
                        temp->unequip();
                if( temp=query_temp("secondary_weapon", me) )
                        temp->unequip();
                WIELD_CMD->do_wield(me, item);
        }

        return 1;
}

// 隐藏物品
int hide_anywhere(object me, object item)
{
        if( item->item_owner() != query("id", me) &&
            query("item_owner", item) != query("id", me) )
                return 0;

        if( query("jingli", me)<100 )
        {
                tell_object(me, "你试图令" + item->name() +
                            "遁去，可是精力不济，难以发挥它的能力。\n");
                return 0;
        }
        addn("jingli", -100, me);

        message_vision(HIM "$N" HIM "轻轻一旋" + item->name() +
                       HIM "，已然了无踪迹。\n", me);
        destruct(item);
        return 1;
}

// 追寻物品
int receive_miss(object me, object item)
{
        object env;

        env = environment(item);

        if (env == environment(me))
        {
                write("你瞪着" + item->name() + "，看啥？\n");
                return 0;
        }

        if (env == me)
        {
                write("你摸着" + item->name() + "，发了半天的呆。\n");
                return 0;
        }

        if (!objectp(env) || userp(env) || environment(env))
        {
                write("你试图感应" + item->name() + "，但是感觉非常的渺茫。\n");
                return 0;
        }

        if( !wizardp(me) && (!query("outdoors", env) || query("no_magic", env) ||
            query("maze", env) || query("penglai", env)) )
        {
                write("冥冥中你感应到" + item->name() + "，但是似乎难以到达那里。\n");
                return 0;
        }

        if( sscanf(base_name(env), "/d/dongtian/%*s") )
        {
                write("冥冥中你感应到" + item->name() + "，但是似乎难以到达那里。\n");
                return 0;
        }

        message("vision", me->name() + "在凝神思索，不知道要做些什么。\n",
                environment(me), ({ me }));
        if( query("jingli", me)<400 )
        {
                write("你觉得" + item->name() + "的感觉相当"
                      "飘忽，看来精力不济，难以感应。\n");
                return 0;
        }

        // 消耗精力
        addn("jingli", -300-random(100), me);
        message_vision(HIM "$N" HIM "口中念念有词，转瞬天际一道长虹划"
                       "过，$N" HIM "驾彩虹而走。\n" NOR, me);
        tell_object(me, "你追寻" + item->name() + "而去。\n");
        me->move(environment(item));
        message("vision", HIM "一道彩虹划过天际，" + me->name() +
                HIM "飘然落下，有若神仙。\n" NOR, environment(me), ({ me }));
        tell_object(me, HIM "你追寻到了" + item->name() +
                    HIM "，落下遁光。\n" NOR);
        return 1;
}

// 插在地上
int do_stab(object me, object item)
{
        if( query("no_magic", environment(me)) )
                return notify_fail("在这里乱弄什么！\n");

        if (!item->is_weapon() && !item->is_unarmed_weapon())
                return notify_fail(item->name() + "也能插在地上？\n");

        if( !query("outdoors", environment(me)) &&
            !wizardp(me))
                return notify_fail("在这里乱弄什么！\n");

        set("no_get", bind((:call_other,__FILE__,"do_get_item",item:),item), item);
        set_temp("stab_by",query("id",  me), item);

        message_vision(WHT "\n$N" WHT "随手将" + item->name() + NOR +
                       WHT "往地上一插，发出「嚓愣」一声脆响。\n\n" NOR, me);
        item->move(environment(me));
        return 1;
}

// 把取物品时检查
mixed do_get_item(object item)
{
        object me;

        if (!objectp(me = this_player()))
                return 1;

        if( query("id", me) != query_temp("stab_by", item) &&
            query("id", me) != item->item_owner() )
                return "你试图将" + item->name() + "拔起，却"
                       "发现它仿佛是生长在这里一般，无法撼动。\n";

        message_vision(HIW "\n$N" HIW "随手拂过" + item->name() +
                       HIW "脊处，顿时只听「嗤」的一声，扬起一阵"
                       "尘土。\n\n" NOR, me);
        delete_temp("stab_by", item);
        delete("no_get", item);
        return 0;
}

// 发挥特殊功能
mixed do_touch(object me, object item)
{
        string msg;
        object ob;
        object *obs;
        mapping my;

        if( query("id", me) != item->item_owner() ||
            (me->query_condition("killer") &&
            (query("no_fight", environment(me)) ||
            query("room_owner_id", environment(me)))) )
        {
                message_vision(HIR "\n$N轻轻触碰" + item->name() +
                               HIR "，突然间全身一震，连退数步，如"
                               "遭受电击。\n" NOR, me);
                me->receive_damage("qi", 50 + random(50));
                return 1;
        }

        if( query("jingli", me)<100 )
        {
                set("jingli", 0, me);
                return notify_fail(CYN "\n你凝视" + item->name() +
                                   CYN "许久，悠悠一声长叹。\n" NOR);
        }

        addn("jingli", -80-random(20), me);
        switch (random(3))
        {
        case 0:
                msg = CYN "\n$N" CYN "轻轻一弹$n" CYN "，长吟"
                      "道：「别来无恙乎？」\n" NOR;
                break;
        case 1:
                msg = CYN "\n$N" CYN "轻轻抚过$n" CYN "，作古"
                      "风一首，$n" CYN "铃铃作响，似以和之。\n" NOR;
                break;
        default:
                msg = CYN "\n$N" CYN "悠然一声长叹，轻抚$n"
                      CYN "，沉思良久，不禁感慨万千。\n" NOR;
                break;
        }

        switch (random(3))
        {
        case 0:
                msg += HIM "忽然只见$n" HIM "闪过一道光华，"
                       "飞跃而起，散作千百流离。\n" NOR;
                break;
        case 1:
                msg += HIM "顿听$n" HIM "一声龙吟，悠悠不绝"
                       "，直沁入到你的心肺中去。\n" NOR;
                break;
        default:
                msg += HIM "霎时间$n" HIM "光芒四射，如蕴琉"
                       "璃异彩，逼得你难以目视。\n" NOR;
                break;
        }

        msg = replace_string(msg, "$n", item->name());
        msg = replace_string(msg, "$N", "你");
        // message_vision(msg, me);
        tell_object(me, msg);

        if (random(1000) == 1 || wizardp(me))
        {
                obs = filter_array(all_inventory(environment(me)), (: userp :));
                foreach (ob in obs)
                {
                        my = ob->query_entire_dbase();
                        my["jing"]   = my["eff_jing"] = my["max_jing"];
                        my["qi"]     = my["eff_qi"]   = my["max_qi"];
                        my["neili"]  = my["max_neili"];
                        my["jingli"] = my["max_jingli"];
                        set_temp("nopoison", 1, ob);
                }
                tell_object(obs, HIC "你感到一股温和的热浪袭来，便似"
                                "获得重生一般。\n" NOR);
        } else
        if( query("neili", me)<query("max_neili", me) )
        {
                set("neili",query("max_neili",  me), me);
                tell_object(me, HIC "你只觉一股热气至丹田冉冉升起，"
                                "说不出的舒服。\n" NOR);
        }
        if (me->is_fighting() && !me->is_busy())
                me->start_busy(10);
        return 1;
}

// 圣化物品
int do_san(object me, object item)
{
        string my_id;
        int count;
        int san;

        if( !item->is_weapon() && !item->is_unarmed_weapon() )
        {
                // 是装备类？
                return notify_fail("防具无需圣化...\n");
        }

        // 武器类的圣化
        if( query("magic/power", item)>0 )
                return notify_fail("现在" + item->name() + "的威力"
                                   "已经得到了充分的发挥了。\n");

        if( query("magic/imbue_ok", item) )
                return notify_fail("现在" + item->name() + "的潜力"
                                   "已经充分挖掘了，现在只是需要最"
                                   "后一步融合。\n");

        my_id=query("id", me);

        count=sizeof(query("magic/do_san", item));
        if( query("magic/imbue_ob", item) )
                return notify_fail("现在" + item->name() + "已经被充分的圣"
                                   "化了，需要浸入神物以进一步磨练。\n");

        if( query("magic/do_san/"+my_id, item) )
                return notify_fail("你已经为" + item->name() + "圣化过了，"
                                   "非凡的能力还无法被它完全吸收。\n你"
                                   "有必要寻求他人帮助以继续圣化。\n");

        if( item->item_owner() == my_id )
        {
                if( !count )
                        return notify_fail("你应该先寻求四位高手协助你先行圣化" +
                                           item->name() + "。\n");

                if( count < SAN_PER_IMBUE - 1 )
                        return notify_fail("你应该再寻求" +
                                           chinese_number(SAN_PER_IMBUE - 1 - count) +
                                           "位高手先行圣化" + item->name() + "。\n");
        } else
        {
                if( count >= SAN_PER_IMBUE - 1 )
                        return notify_fail("最后需要他的主人为它圣化，不劳你费心了。\n");
        }

        if( query("neili", me)<query("max_neili", me)*9/10 )
                return notify_fail("你现在内力并不充沛，怎敢贸然运用？\n");

        if( query("jingli", me)<query("max_jingli", me)*9/10 )
                return notify_fail("你现在精力不济，怎敢贸然运用？\n");

        if( me->query_skillo("force", 1) < 300 )
                return notify_fail("你的内功根基不够扎实，不能贸然圣化。\n");

        if( query("max_neili", me)<8000 )
                return notify_fail("你尝试运了一下内力，无法顺"
                                   "利运足一个周天，难以施展你的能力。\n");

        if( query("max_jingli", me)<1000 )
                return notify_fail("你试图凝神运用精力，但是感觉尚有欠缺。\n");

        message_sort(HIM "$N" HIM "轻轻抚过$n" HIM "，两指点于其上，同"
                     "时运转丹田内力，经由奇经\n八脉源源由体内流出，注"
                     "入$n" HIM "。\n忽的只见氤氲紫气从$n" HIM
                     "上腾然升起，弥漫在四周。\n" NOR, me, item);

        if( query("max_neili", me)<me->query_neili_limit()-400 )
        {
                if (random(2) == 1)
                {
                        // 内力未满警告
                        message_vision(HIR "$N" HIR "脸色忽然变了变。\n" NOR,
                                       me);
                        tell_object(me, HIC "你忽然觉得丹田气息有些错乱。\n" NOR);
                } else
                {
                        message_vision(HIR "$N" HIR "忽然闷哼一声，脸"
                                       "上刹时大汗淋漓！\n" NOR, me);
                        tell_object(me, HIC "你感到可能是你的内力尚未锻炼"
                                    "到极至，结果损伤了你的内功根基。\n" NOR);
                        tell_object(me, HIC "你的基本内功下降了。\n");
                        me->set_skill("force", me->query_skillo("force", 1) - 10 - random(5));
                        return 1;
                }
        }

        // 统计IMBUE过的次数，并用来计算本次MAX_NEILI/JINGLI的消耗
        san = query("magic/imbue", item);

        addn("max_neili", -(san+5), me);
        addn("neili", -(san*10+100), me);
        addn("max_jingli", -(san*5+50), me);
        addn("jingli", -(san*5+50), me);
        set("magic/do_san/"+my_id, me->name(1), item);
        me->start_busy(1);

        if (item->item_owner() == my_id ||
            sizeof(query("magic/do_san", item)) == SAN_PER_IMBUE )
        {
                tell_object(me, HIW "你凝神片刻，觉得" + item->name() +
                            HIW "似乎有了灵性，跳跃不休，不禁微微一笑。\n" NOR);
                message("vision", HIW + me->name() + HIW "忽然"
                        "微微一笑。\n" HIW, environment(me), ({ me }));

                // 选定一个需要imbue的物品
                set("magic/imbue_ob", imbue_list[random(sizeof(imbue_list))], item);
        }
        return 1;
}

// 浸透物品
int do_imbue(object me, object item, object imbue)
{
        if( query("magic/power", item)>0 )
                return notify_fail("现在" + item->name() + "的威力"
                                   "已经得到了充分的发挥了。\n");

        if( query("magic/imbue_ok", item) )
                return notify_fail("现在" + item->name() + "的潜力"
                                   "已经充分挖掘了，现在只是需要最"
                                   "后一步融合。\n");

        if( sizeof(query("magic/do_san", item))<SAN_PER_IMBUE )
                return notify_fail("你必须先对" + item->name() +
                                   "进行充分的圣化才行。\n");

        if( base_name(imbue) != query("magic/imbue_ob", item) )
                return notify_fail(item->name() + "现在不需要用" +
                                   imbue->name() + "来浸入。\n");

        message_sort(HIM "$N" HIM "深吸一口气，面上笼罩了一层白霜，只手握住$n" +
                     imbue->name() +
                     HIM "，忽然间融化在掌心，晶莹欲透！$N"
                     HIM "随手一挥，将一汪清液洒在$n" HIM
                     "上，登时化做雾气，须臾成五彩，奇光闪烁。\n" NOR,
                     me, item);

        tell_object(me, "你将" + imbue->name() + "的效力浸入了" +
                    item->name() + "。\n");
        delete("magic/do_san", item);
        delete("magic/imbue_ob", item);

        if( imbue->query_amount() )
                imbue->add_amount(-1);
        else
                destruct(imbue);
        me->start_busy(1);

        addn("magic/imbue", 1, item);
        if( random(query("magic/imbue", item)) >= RANDOM_IMBUE_OK
        ||  query("magic/imbue", item) >= 150 )
        {
                        // 浸透完成
                tell_object(me, HIG "你忽然发现手中的" + item->name() +
                                HIG "有一种跃跃欲试的感觉，似乎期待着什么。\n" NOR);
                set("magic/imbue_ok", 1, item);
        }

        return 1;
}

// 镶嵌物品
int do_enchase(object me, object item, object tessera)
{
        mapping *ins;
        mapping data, enchase_prop, temp;
        string  *apply;
        string  str, type;
        object  obj;
        int     i, n, level, wash, addsn;
        int my_vip;
int xpn;

        if( query("equipped", item) )
                return notify_fail("你先解除" + item->name() + "的装备再说！\n");

        if( !query("enchase/flute", item) )
                return notify_fail(item->name() + "上并没有凹槽可用来镶嵌。\n");

        if( query("enchase/used", item) >= query("enchase/flute", item) )
                return notify_fail(item->name() + "上的凹槽已经镶满了。\n");

        if( (type = query("magic/type", item)) && query("can_be_tessera", tessera) )
                return notify_fail(item->name() + "上已经拥有灵力物品了。\n");

        if( !tessera->is_tessera() || !mapp(query("enchase", tessera)) )
                return notify_fail(tessera->name() + "不能发挥魔力，没有必要镶嵌在" + item->name() + "上面。\n");

        if( query("can_be_qiling", tessera) )
        {
                if( query("status", item) < 6 )
                        return notify_fail(item->name() + "还不具备发挥启灵宝石作用的灵智。\n");

                if( item->is_weapon() || item->is_unarmed_weapon() )
                {
                        if( query("enchase/flute", item) < 10 )
                                return notify_fail(item->name() + "必须拥有最大凹槽数才能激发启灵宝石的能力。\n");
                } else
                {
                        if( query("enchase/flute", item) < 8 )
                                return notify_fail(item->name() + "必须拥有最大凹槽数才能激发启灵宝石的能力。\n");
                }

                if( query("enchase/used", item)+1 < query("enchase/flute", item) )
                        return notify_fail("用来启灵的宝石必须是镶嵌最后一个凹槽。\n");
        }

        if( !query("can_be_qiling", tessera) && type && query("magic/type", tessera) != type )
                write(item->name() + "上已经拥有五行灵力属性和镶嵌物的五行灵力属性不一致，影响融合。\n");

        if( (level = me->query_skill("certosina", 1)) < 200 )
                return notify_fail("你觉得你的镶嵌技艺还不够娴熟，不敢贸然动手。\n");

        if( tessera->is_rune() && query("enchase/rune" + query("enchase/SN", tessera), item) )
                return notify_fail(item->name() + "上的凹槽里已经镶嵌此符文,再镶嵌会产生魔性冲突。\n");

        if( query("status", item) == 6 ) // 启灵的装备
        {
                if( !type && !query("can_be_tessera", tessera) ) // 没有镶嵌10LV
                {
                        if( query("enchase/used", item)+2 >= query("enchase/flute", item) )
                               return notify_fail(item->name() + "上的剩下的二个的凹槽是用来镶嵌一个具有灵力和一个启灵的物品。\n");
                }
                if( !query("can_be_qiling", tessera) )
                if( query("enchase/used", item)+1 >= query("enchase/flute", item) )
                        return notify_fail(item->name() + "上的剩下的唯一的凹槽是用来镶嵌启灵宝石的。\n");
        } else
        {
                if( !type && !query("can_be_tessera", tessera) )
                {
                        if( query("enchase/used", item)+1 >= query("enchase/flute", item) )
                                return notify_fail(item->name() + "上的剩下的一个的凹槽是用来镶嵌具有灵力的物品。\n");
                }
        }

        temp = query("enchase", tessera);
        if( undefinedp(temp["type"]) )
                return notify_fail(tessera->name() + "的类型属性不适合镶嵌在" + item->name() + "上。\n");
        else
        {
                if( query("can_be_qiling", tessera) )
                {
                        if( item->is_weapon() || item->is_unarmed_weapon() )
                        {
                                if( temp["type"] != "weapon" )
                                        return notify_fail(tessera->name() + "的类型属性不适合镶嵌在" + item->name() + "上。\n");
                        } else
                        {
                                if( temp["type"] != query("armor_type", item) )
                                        return notify_fail(tessera->name() + "的类型属性不适合镶嵌在" + item->name() + "上。\n");
                        }
                } else {
                if (temp["type"] != "all" &&
                    temp["type"] != query("skill_type", item) &&
                    temp["type"] != query("armor_type", item) )
                        return notify_fail(tessera->name() + "的类型属性不适合镶嵌在" + item->name() + "上。\n");
                }
        }

        if( tessera->is_rune() && (query("armor_type", item) == "rings" ||
            query("armor_type", item) == "neck" || query("armor_type", item) == "charm") )
                return notify_fail("符文不适合镶嵌在" + item->name() + "上。\n");

        if( level < 400 && random(level) < 180 && !(obj = present("enchase symbol", me)) )
        {
                message_vision(HIM "听得“喀啦”一声，只见" + tessera->name() + HIM "撞在$n" +
                               HIM "上，片片裂开。\n" NOR, me, item);
                tell_object(me, HIC "你镶嵌" + tessera->name() + CYN "失败了。\n" NOR);
                destruct(tessera);
                me->start_busy(1);
                return 1;
        }
        if( objectp(obj) ) destruct(obj);

        message_vision( HIM "听得“喀啦”一声，$N" HIM "将" + tessera->name() + NOR HIM"镶嵌到了$n" HIM "上面，\n只见上面$n"
                        HIM "隐隐的显过了一道奇异的光芒，随即变得平静，说不出的平凡。\n\n" NOR, me, item);
        tell_object(me, HIC "你感受" + item->name() + HIC "发生了不可言喻的变化。\n" NOR);

        if( query("can_be_tessera", tessera) )
        {
                //CHANNEL_D->do_channel(this_object(), "rumor", "听说神品" + item->name() + HIM + "来到了人间。");

                set("magic/type", query("magic/type", tessera), item);
                set("magic/power", query("magic/power", tessera), item);
                set("magic/tessera", tessera->name(), item);
        } else
        {
                // 先镶嵌10lv物品，则可吸收后镶嵌同类物品的能量
                if( type && query("magic/type", tessera) == type )
                        addn("magic/power", query("magic/power", tessera), item);
        }

        if( query("can_be_qiling", tessera) )
        {
                if( !query("magic/heart", item) )
                        set("magic/heart", remove_ansi(tessera->name()), item);

                ins = query("insert", item);
                if (!ins ) ins = ({ });
                ins += ({ ([ "name" : query("name", tessera),
                     "id"   : query("id", tessera),
                     "file" : base_name(tessera),
                     "SN"   : query("enchase/SN", tessera),
                     "apply_prop" : enchase_prop ])
                });
                set("insert", ins, item);

                addn("enchase/used", 1, item);
                item->save();
                destruct(tessera);
                if( !wizardp(me) )
                        me->start_busy(1);
                return 1;
        }

        if( intp(query("enchase/wash", item)) )
                wash=query("enchase/wash", item);
        else
                wash = 0;

        addsn = 0;
        if (item->is_xpzhu())
        {
                if (strsrch(base_name(tessera), "/inherit/template/gem/") != -1)
                        xpn = query("level", tessera) * 2;
                        if (xpn < 1) xpn = 1;
                                enchase_prop = ([]);
                enchase_prop+=query("enchase/weapon_prop", tessera);
                enchase_prop+=query("enchase/armor_prop", tessera);
                        while (xpn--) {
                                for( int xpi=0; xpi<sizeof(keys(query("enchase/weapon_prop", tessera)));xpi++ ) {
                                        enchase_prop[keys(query("enchase/weapon_prop", tessera))[xpi]] += values(query("enchase/weapon_prop", tessera))[xpi];
                                }
                                for( int xpi=0; xpi<sizeof(keys(query("enchase/armor_prop", tessera)));xpi++ ) {
                                        enchase_prop[keys(query("enchase/armor_prop", tessera))[xpi]] += values(query("enchase/armor_prop", tessera))[xpi];
                                }
            }
        } else
        if (item->is_weapon() || item->is_unarmed_weapon())
        {
                if (wash >= 180) addsn = 4;
                else if (wash >= 150) addsn = 3;
                else if (wash >= 120) addsn = 2;
                else if (wash >= 40) addsn = 1;

                enchase_prop=query("enchase/weapon_prop", tessera);
        } else
        if( query("armor_type", item) == "rings" || query("armor_type", item) == "neck" || query("armor_type", item) == "charm" )
        {
                if (wash >= 80) addsn = 3;
                else if (wash >= 50) addsn = 2;
                else if (wash >= 20) addsn = 1;
                else if (wash < 15) addsn = -1;

                enchase_prop=query("enchase/rings_prop", tessera);
        } else
        {
                if (wash >= 100) addsn = 3;
                else if (wash >= 80) addsn = 2;
                else if (wash >= 30) addsn = 1;
                else if (wash < 15) addsn = -1;

                enchase_prop=query("enchase/armor_prop", tessera);
        }

        if (!mapp(enchase_prop)) enchase_prop = ([]);
        apply = keys(enchase_prop);

        data=query("enchase/apply_prop", item);
        if (!mapp(data) ) data = ([]);

        for (i = 0; i<sizeof(apply); i++)
        {
                if ( undefinedp(data[apply[i]]) )
                        data[apply[i]] = enchase_prop[apply[i]];
                else
                        data[apply[i]] += enchase_prop[apply[i]];
        }

        set("enchase/apply_prop", data, item);

        ins = query("insert", item);
        if (!ins ) ins = ({ });
        ins += ({ ([ "name" : query("name", tessera),
                     "id"   : query("id", tessera),
                     "file" : base_name(tessera),
                     "SN"   : query("enchase/SN", tessera),
                     "apply_prop" : enchase_prop ])
                });

        set("insert", ins, item);

        addn("enchase/used", 1, item);
        if( tessera->is_rune() ) {
                if( !query("enchase/rune", item) ){
                        addn("enchase/SN", query("enchase/SN", tessera), item);
                        set("enchase/rune", 1, item);
                }
                set("enchase/rune"+query("enchase/SN", tessera), 1, item);
        } else {
                /*
                if( query("can_be_tessera", tessera) )
                        //addn("enchase/SN", 5+random(5), item);
                        addn("enchase/SN",query("enchase/SN", tessera), item);
                else
                */
                //if( !query("can_be_qiling", tessera) )
                {
                        //addsn += random(query("enchase/SN", tessera))+1;
                        addsn += query("enchase/SN", tessera);
                        my_vip = me->query_viplevel();
                        if( my_vip >= 6 ) addsn += 1;
                        if (addsn > 9 ) addsn = 9;
                        if (addsn < 1 ) addsn = 1;

                        addn("enchase/SN", addsn, item);
                }
        }

        item->add_weight(tessera->query_weight());

        if( IDENTIFY_D->identify_ultimate_ob(item) )
                tell_object(me, BLINK HBMAG + tessera->name() + BLINK HBMAG "与" + item->name() +
                                BLINK HBMAG "的魔力充分融合相生使" + item->name() +
                                BLINK HBMAG "发生了不可思议的突变。\n\n" NOR);

        item->save();
        destruct(tessera);
        if( !wizardp(me) )
                me->start_busy(1);
        return 1;
}

// 用内力将镶嵌物品溶化掉 melt
int do_wash(object me, object item)
{
        mapping enchase, insert, applied_prop;
        mapping mod_prop;
        string *apply, *ks;
        int i, j, f, n;

        if( query("neili", me)<query("max_neili", me)*9/10 )
                return notify_fail("你现在内力并不充沛，怎敢贸然运用？\n");

        if( query("jingli", me)<query("max_jingli", me)*9/10 )
                return notify_fail("你现在精力不济，怎敢贸然运用？\n");

        if( me->query_skill("force") < 200 )
                return notify_fail("你的内功根基不够扎实，不能贸然运功。\n");

        if( query("max_neili", me)<8000 )
                return notify_fail("你尝试运了一下内力，无法顺"
                                   "利运足一个周天，难以施展你的能力。\n");

        if( query("max_jingli", me)<1000 )
                return notify_fail("你试图凝神运用精力，但是感觉尚有欠缺。\n");

        message_vision(HIM "$N" HIM "将$n" HIM "握于掌中，默默运转内力，注入$n" HIM "凹槽。\n只见$n" HIM
                       "白雾蒸腾，弥漫在四周。\n" NOR, me, item);


        message_vision(HIC"忽的却见$n"HIC"上面"HIY+chinese_number(query("enchase/flute", item))+
                       HIC "个凹槽内物品嗤的化作一股青烟，\n$n"HIC "凹槽内已空无一物，犹如新出。\n" NOR,
                       me, item);

        if( query("enchase/rune30", item) || query("enchase/rune31", item) ||
            query("enchase/rune32", item) || query("enchase/rune33", item) )
        {
                if (item->is_weapon() || item->is_unarmed_weapon())
                {
                        if( query("enchase/used", item) >= 7 )
                                addn("enchase/wash", 1, item);
                }
                else
                {
                        if( query("enchase/used", item) >= 5 )
                                addn("enchase/wash", 1, item);
                }
        }

        f = query("enchase/flute", item);
        n = query("enchase/wash", item);
        applied_prop = copy(query("enchase/apply_prop", item));
        mod_prop = copy(query("enchase/mod_prop", item));
        /*
        insert = copy(query("insert", item));
        ks = keys(insert);
        for( i=0; i<sizeof(ks);i++ )
        {
                enchase = copy(insert[ks[i]]["apply_prop"]);
                apply = keys(enchase);
                for( j=0;j<sizeof(apply);j++ )
                {
                        applied_prop[apply[j]] -= enchase[apply[j]];
                        if( applied_prop[apply[j]] <= 0 )
                                map_delete(applied_prop, apply[j]);
                }
        }
        */
        delete("enchase", item);
        delete("insert", item);
        delete("magic/power", item);
        delete("magic/type", item);
        delete("magic/tessera", item);
        delete("ultimate/69", item);
        delete("ultimate/87", item);
        delete("ultimate/105", item);
        delete("ultimate/121", item);
        delete("ultimate/ob", item);
        delete("rare", item);
        delete("qianghua", item);
        set("enchase/flute", f, item);
        set("enchase/wash", n, item);
        //set("enchase/apply_prop", applied_prop, item);
        if( mapp(mod_prop) ) set("enchase/mod_prop", mod_prop, item);

        switch(query("material", item))
        {
        case "tian jing":
                set("enchase/SN", 8, item);
                break;
        case "no name"  :
                set("enchase/SN", 16, item);
                break;
        default         :
                break;
        }

        /*
        switch(query("quality_level", item) )
        {
        case 2 :
                set("enchase/SN", 4, item);  // 精制
                break;
        case 3 :
                set("enchase/SN", 8, item);  // 珍稀
                break;
        case 4 :
                set("enchase/SN", 12, item); // 史诗
                break;
        case 5 :
                set("enchase/SN", 16, item); // 传说
                break;
        case 6 :
                set("enchase/SN", 25, item); // 神器
                break;
        default         :
                break;
        }
        */

        item->save();
        if( !wizardp(me) )
                me->start_busy(1);
        return 1;
}

// 锻造防具升级
int do_forge(object me, object item)
{
        int n, level;

        if( item->armor_level() >= 9 )
                return notify_fail(item->name()+"已经达到9lv了，无需继续锻造。\n");

        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("你的内功修为不足。\n");

        if( query("qi", me)*100/query("max_qi", me)<90 )
                return notify_fail("你现在的气太少了。\n");

        if( query("jing", me)*100/query("max_jing", me)<90 )
                return notify_fail("你现在的精太少了。\n");

        if( query("max_neili", me) < 5000 )
                return notify_fail("你觉得内力颇有不足。\n");

        if( query("neili", me)*100/query("max_neili", me)<90 )
                return notify_fail("你现在的内力太少了。\n");

        if( (query("potential", me)-query("learned_points", me)) < 20 )
                return notify_fail("你的潜能不够，无法锻炼兵器！\n");

        message_vision(HIM "$N" HIM "手握$n"+ HIM "，一股内力丝丝的传了进去，\n"
                       HIM "$n" HIM "犹如烈火中重生一般，散发出绚目的光彩！\n" NOR,
                     me, item);

        addn("max_neili", -100, me);
        set("neili", query("max_neili", me), me);
        addn("qi", -50, me);
        addn("eff_qi", -30, me);
        addn("eff_jing", -30, me);
        addn("potential", -20, me);

        addn("forge", 1, item);
        n = query("forge", item);
        level = n / 10;

        if( !(n % 10) )
        {
                if( level == 9 )
                        set("magic/imbue_ok", 1, item);

                message_vision(HIY +item->name()+ HIY "忽的一亮，一道金光隐入$N" HIY "的" +item->name()+ HIY "，不见了！\n" NOR +
                               HIG "$N" HIG "的" +item->name()+ HIG "的等级提高了！\n" NOR, me);
        }

        item->save();
        message_vision(RED "$N" RED "的" +item->name()+ RED "的质地改善了!\n" NOR, me);
        if( !wizardp(me) )
                me->start_busy(1);

        return 1;
}

// 10级兵器攻击对手
mixed weapon10lv_hit_ob(object me, object victim, object weapon, int damage_bonus)
{
        mapping magic;
        int jingjia;
        int power, resistance;
        int damage;
        int add, reduce;
        string msg;

        // 计算魔法效果
        magic=query("magic", weapon);
        if( !mapp(magic) ) return;
        power = magic["power"];
        damage = 0;
        resistance = 0;
        //jingjia = me->query("jiajing");
        jingjia=query("jiali", me)/3;

        switch (magic["type"])
        {
        case "lighting":
                // 闪电攻击：伤害内力++和气+
                resistance=victim->query_all_buff("resistance_lighting");
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=me->query_all_buff("add_lighting");
                reduce=victim->query_all_buff("reduce_lighting");
                damage += damage * random(add + 1) / 100;
                damage -= damage * random(reduce + 1) / 100;

                if (damage < 0) return;

                switch (random(6))
                {
                case 0:
                        msg = HIY + weapon->name() + HIY "迸发出几道明亮的闪光，兹兹作响，让$n"
                              HIY "不由为之酥麻。\n" NOR;
                        break;
                case 1:
                        msg = HIY "一道电光闪过，" + weapon->name() + HIY
                              "变得耀眼夺目，令$n" HIY "无法正视，心神俱废。\n" NOR;
                        break;
                case 2:
                        msg=HIY+query("name", weapon)+HIY"喷出一团炽白的光球，直奔$n"
                              HIY "而去，$n" HIY "被打了个正着，受伤不轻。\n" NOR;
                        break;
                case 3:
                        msg = HIY "一圈炽白的光环围绕" + weapon->name() + HIY
                             "不断扩散开来，所到之处亮如白昼，$n" HIY "立刻魂飞魄散。\n" NOR;
                        break;
                case 4:
                        msg=HIY+query("name", weapon)+HIY"暴出漫天夹杂响雷的闪电直击而来，$n"
                              HIY "被闪电悉数直穿身体而过，顿时软弱无力。\n" NOR;
                        break;
                default:
                        msg = HIY "天际隐隐响起几声闷雷，紧接着一道霹雳直下，" +
                              weapon->name() + HIY "忽明忽暗，五彩缤纷，震得$n"
                              HIY "酸软无力。\n" NOR;
                        break;
                }

                if( query("neili", victim)>damage )
                        addn("neili", -damage, victim);
                else
                        set("neili", 0, victim);

                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 2);
                break;

        case "water":
                // 冷冻攻击：伤害精++和气+
                resistance=victim->query_all_buff("resistance_water");
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=me->query_all_buff("add_water");
                reduce=victim->query_all_buff("reduce_water");
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 3);
                victim->receive_wound("jing", damage / 6);
                victim->receive_damage("qi", damage / 2);
                victim->receive_wound("qi", damage / 4);
                switch (random(6))
                {
                case 0:
                        msg = HIB + weapon->name() + HIB "闪过一道冷涩的蓝光，让$n"
                              HIB "不寒而栗。\n" NOR;
                        break;
                case 1:
                        msg = HIB "忽然间" + weapon->name() + HIB
                              "变得透体通蓝，一道道冰冷的寒光迸发出来，$n"
                              HIB "浑身只是一冷。\n" NOR;
                        break;
                case 2:
                        msg = HIB "一圈晶莹的冰光环围绕" + weapon->name() + HIB
                              "不断扩散开来，所到之处万物皆凝。$n" HIB
                              "只觉自己气血凝滞。\n" NOR;
                        break;
                case 3:
                        msg=HIB+query("name", weapon)+HIB"暴出漫天冰锥直射而来，$n"
                              HIB "转眼间已然成了蜂窝。\n" NOR;
                        break;
                case 4:
                        msg = HIB "忽然间" + weapon->name() + HIB
                              "变得透体通蓝，周围空气忽然急速凝结，一面淡蓝的冰墙把$n"
                              HIB "冰封在了里面。\n" NOR;
                        break;
                default:
                        msg = HIB "一道光圈由" + weapon->name() + HIB "射出，"
                              "森然盘旋在$n" HIB "四周，悄然无息。\n" NOR;
                        break;
                }
                break;

        case "fire":
                // 火焰攻击：伤害精+和气++
                resistance=victim->query_all_buff("resistance_fire");
                damage = (power + jingjia) * 300 / (100 + resistance);
                add=me->query_all_buff("add_fire");
                reduce=victim->query_all_buff("reduce_fire");
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 5);
                victim->receive_wound("jing", damage / 8);
                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 2);
                switch (random(6))
                {
                case 0:
                        msg = HIR + weapon->name() + HIR "蓦的腾起一串火焰，将$n"
                              HIR "接连逼退了数步，惨叫连连。\n" NOR;
                        break;
                case 1:
                        msg = HIR "一道火光从" + weapon->name() + HIR
                              "上迸出，迅捷无伦的击中$n" HIR "，令人避无可避！\n" NOR;
                        break;
                case 2:
                        msg = HIR "一圈通红的火光从" + weapon->name() + HIR
                              "上迸出扩散开来，所到之处万物皆灰，将$n"
                              HIR "身体烧出了一个焦黑的窟窿。\n" NOR;
                        break;
                case 3:
                        msg=HIR+query("name", weapon)+HIB"暴出漫天通红的火球直击而来，$n"
                              HIR "被置身一片火海，惨叫连连。\n" NOR;
                        break;
                case 4:
                        msg = HIR "忽然间" + weapon->name() + HIR
                              "变得透体通红，周围空气忽然异常干燥，$n"
                              HIR "眨眼功夫周身竟然被熊熊烈火团团围住，被烧的体无完肤。\n" NOR;
                        break;
                default:
                        msg = HIR "一串串火焰从" + weapon->name() + HIR "上飞溅射出，"
                              "四下散开，接连击中$n" HIR "！\n" NOR;
                        break;
                }
                break;

        case "metal":
                // 冷冻攻击：伤害精++和气+
                resistance=victim->query_all_buff("resistance_metal");
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=me->query_all_buff("add_metal");
                reduce=victim->query_all_buff("reduce_metal");
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 3);
                victim->receive_wound("jing", damage / 6);
                victim->receive_damage("qi", damage / 2);
                victim->receive_wound("qi", damage / 4);
                switch (random(4))
                {
                case 0:
                        msg = HIY + weapon->name()+HIY"顿时金光四射，纵横交错，布满了整个空间，$n"HIY"已难以醒目。\n"NOR;
                        break;
                case 1:
                        msg = HIY + weapon->name()+HIY"一飞冲天，片刻时间化作无数的"HIY + weapon->name()+HIY"金钱撒地般的射向$n。\n"NOR;
                        break;
                default:
                        msg = HIY + weapon->name()+HIY"通体变的金黄耀目，伴鸣响天地的撕裂声直击$n"HIY"要害之处。\n"NOR;
                        break;
                }
                break;

        case "wood":
                // 冷冻攻击：伤害精++和气+
                resistance=victim->query_all_buff("resistance_wood");
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=me->query_all_buff("add_wood");
                reduce=victim->query_all_buff("reduce_wood");
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 3);
                victim->receive_wound("jing", damage / 6);
                victim->receive_damage("qi", damage / 2);
                victim->receive_wound("qi", damage / 4);
                switch (random(4))
                {
                case 0:
                        msg =  HIG"霎时间"HIG + weapon->name()+HIG"之影暴长 ，似乎变幻出无数枝干，将$N紧紧抓住。\n" NOR;
                        break;
                case 1:
                        msg =  HIG + weapon->name()+HIG"在$n"HIG"周身盘旋，将$n"HIG"带入翡翠梦境，令$n迷失不已。\n" NOR;
                        break;
                default:
                        msg =  HIG  + weapon->name()+HIG"闪出无数条亮影，如枯木回春般蔓延了$n"HIG"全身。\n" NOR;
                        break;
                }
                break;

        case "earth":
                // 冷冻攻击：伤害精++和气+
                resistance=victim->query_all_buff("resistance_earth");
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=me->query_all_buff("add_earth");
                reduce=victim->query_all_buff("reduce_earth");
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 3);
                victim->receive_wound("jing", damage / 6);
                victim->receive_damage("qi", damage / 2);
                victim->receive_wound("qi", damage / 4);
                switch (random(4))
                {
                case 0:
                        msg = YEL + weapon->name()+ YEL"突然颤抖，音声低沉凝重，引山摇地动之式，$n"YEL"以不能自已！\n" NOR;
                        break;
                case 1:
                        msg = YEL + weapon->name()+ YEL"急速的划过土石之缘，带动山石之雨，咆哮着令人心胆俱裂的震天怒响击向$n。 \n"NOR;
                        break;
                default:
                        msg = YEL + weapon->name()+ YEL"汲取天地万物之灵气发起攻击，刹那间天地苍苍，飞沙走石。\n" NOR;
                        break;
                }
                break;

        case "poison":
                // 毒系魔法：打内力或者忙乱
                resistance=victim->query_all_buff("resistance_poison");
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=me->query_all_buff("add_poison");
                reduce=victim->query_all_buff("reduce_poison");
                damage += damage * random(add + 1) / 100;
                damage -= damage * random(reduce + 1) / 100;

                if (damage < 0) return;

                if( query("neili", victim)>damage )
                        addn("neili", -damage, victim);
                else
                        set("neili", 0, victim);

                if (!victim->is_busy())
                        victim->start_busy(2 + random(3));

                switch (random(6))
                {
                case 0:
                        msg = HIG + weapon->name() + HIG "蓦的冒出丝丝白烟扩散开来，$n"
                              HIG "顿时浑身慢慢酸软起来。\n" NOR;
                        break;
                case 1:
                        msg=HIG+query("name", weapon)+HIG"喷出股股黄烟快速围绕过来，$n"
                              HIG "顿时感觉头重脚轻，竟然险些拿不动兵器。\n" NOR;
                        break;
                case 2:
                        msg=HIG+query("name", weapon)+HIG"喷出漫天五彩迷雾扑面而来，$n"
                              HIG "周身被五彩迷雾围在其中，手无敷鸡之力。\n" NOR;
                        break;
                case 3:
                        msg = HIG + weapon->name() + HIG "蓦的冒出几丝略带清香的白烟飘然而过，$n"
                              HIG "顿时全身无力。\n" NOR;
                        break;
                case 4:
                        msg = HIG + weapon->name() + HIG "蓦的一圈略带幽香的黄色烟雾不断扩散开来，所到之处万物皆枯，$n"
                              HIG "只觉自己飘飘欲仙，全身使不出力量来。\n" NOR;
                        break;
                default:
                        msg=HIG+query("name", weapon)+HIG"喷出漫天浓香的五彩雾气，$n"
                              HIG "只觉醉生梦死，全身使不出力量来。\n" NOR;
                        break;
                }
                break;

        case "wind":
                // 风系魔法：打法力或者加命中
                resistance=victim->query_all_buff("resistance_wind");
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=me->query_all_buff("add_wind");
                reduce=victim->query_all_buff("reduce_wind");
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("jing", damage / 5);
                victim->receive_wound("jing", damage / 8);
                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 2);

                switch (random(6))
                {
                case 0:
                        msg = HIW + weapon->name() + HIW "吹出一阵强风，直吹的$n"
                              HIW "东倒西歪连站稳住都有些困难。\n" NOR;
                        break;
                case 1:
                        msg = HIW + weapon->name() + HIW "刮出一阵旋风，夹杂黄沙的旋风如万把风刀向$n"
                              HIW "袭来，吹的$n" HIW "天旋地转，竟然险些拿不动兵器。\n" NOR;
                        break;
                case 2:
                        msg = HIW + weapon->name() + HIW "周围空气忽然急速旋转，$n"
                              HIW "躲闪不及眨眼功夫周身竟然被强烈的龙卷风围在其中，被折腾的手无敷鸡之力。\n" NOR;
                        break;
                case 3:
                        msg = HIW + weapon->name() + HIW "刮出强风破，一阵狂风铺面过后，$n"
                              HIW "似乎失去了些许防备能力。\n" NOR;
                        break;
                case 4:
                        msg = HIW + weapon->name() + HIW "刮出一股气流迅速旋转并不断扩散开来，所到之处万物皆损，$n"
                              HIW "只觉自己天旋地转，受伤不轻。\n" NOR;
                        break;
                default:
                        msg = HIW + weapon->name() + HIW "刮出强大的龙卷风夹杂黄沙其中从各处向$n"+HIG+"迅速袭来，$n"
                              HIW "身体向短线风筝在旋风中旋转，全身体无完肤。\n" NOR;
                        break;
                }
                break;

        case "magic":
                // 魔法攻击：吸取气+
                resistance=victim->query_all_buff("resistance_magic");
                damage = (power + jingjia) * 200 / (100 + resistance);
                add=me->query_all_buff("add_magic");
                reduce=victim->query_all_buff("reduce_magic");
                damage += damage * add / 100;
                damage -= damage * reduce / 100;

                if (damage < 0) return;

                victim->receive_damage("qi", damage);
                victim->receive_wound("qi", damage / 2);

                if( query("neili", victim)>damage )
                        addn("neili", -damage, victim);
                else
                        set("neili", 0, victim);

                switch (random(3))
                {
                case 0:
                        msg = HIM + weapon->name() + HIM "响起一阵奇异的声音，犹如龙吟，令$n"
                              HIM "心神不定，神情恍惚。\n" NOR;
                        break;
                case 1:
                        msg = HIM "“啵”的一声，" + weapon->name() + HIM
                              "如击败革，却见$n" HIM "闷哼一声，摇晃不定！\n" NOR;
                        break;
                default:
                        msg = HIM + weapon->name() + HIM "上旋出一道道五彩缤纷的"
                              "光圈，笼罩了$n" HIM "，四下飞舞。\n" NOR;
                        break;
                }
                break;
        default:
                msg = "";
                break;
        }

        // 使用perform
        if( random(2) && random(query("magic/blood", weapon)) < 2100 ) return msg;
        damage = power + jingjia;

        switch (random(6))
        {
        case 0:
                victim->receive_wound("jing", damage / 6 + random(damage / 6), me);
                return msg + HIM "$N" HIM "嘿然冷笑，抖动" + weapon->name() +
                       HIM "，数道光华一起射出，将$n" HIM "困在当中，无法自拔。\n" NOR;

        case 1:
                victim->receive_wound("jing", damage / 5 + random(damage / 5), me);
                return msg + HIC "$N" HIC "手中的" + weapon->name() + HIC "射出各种光芒，"
                       "眩目夺人，一道道神采映射得天地尽情失色，让$n"
                       HIC "目瞪口呆！\n" NOR;
        case 2:
                victim->receive_wound("qi", damage / 4 + random(damage / 4), me);
                return msg + HIY "$N" HIY "举起" + weapon->name() +
                       HIY "，只见天空一道亮光闪过，$n" HIY "连吐几口鲜血！\n" NOR;

        case 3:
                victim->receive_wound("qi", damage / 3 + random(damage / 3), me);
                return msg + HIG "$N" HIG "随手划动" + weapon->name() + HIG "，一圈圈碧芒"
                       "围向$n" HIG "，震得$n吐血连连！\n" NOR;

        case 4:
                victim->receive_wound("qi", damage / 2 + random(damage / 2), me);
                return msg + HIW "$N" HIW "一声长叹，" + weapon->name() + HIW "轻轻递出，"
                       "霎时万籁俱静，$n" HIW "只觉得整个人都跌进了地狱中去！\n" NOR;

        default:

                return msg;
                if( query_temp("weapon_performing", me) )
                        break;
                me->start_call_out(bind((: call_other, __FILE__, "continue_attack",
                                           me, victim, weapon, 10 + random(4) :), me), 0);
        }
}

// 9级兵器攻击对手
mixed weapon_hit_ob(object me, object victim, object weapon, int damage_bonus)
{
        int ap;
        int dp;
        int damage;
        string msg;

        if (random(2)) return;

        msg = "";

        // 计算damage：不论是空手武器还是普通兵器，统一计算
        if (weapon->is_weapon())
                damage=me->query_all_buff("damage");
        else
                damage=me->query_all_buff("unarmed_damage");

        if (damage < 1) return;
        switch (random(8))
        {
        case 0:
                victim->receive_wound("jing", damage / 5 + random(damage / 5), me);
                msg += HIY "$N" HIY "抖动手中的" + weapon->name() + HIY
                       "，幻化成夜空流星，数道" HIM "紫芒" HIY "划破星"
                       "空袭向$n" HIY "。\n" NOR;
                break;
        case 1:
                victim->receive_wound("qi", damage / 3 + random(damage / 3), me);
                msg += HIR "$N" HIR "大喝一声，手中" + weapon->name() +
                       HIR "遥指$n" HIR "，一道杀气登时将$n" HIR "震退"
                       "数步。\n" NOR;
                break;
        case 2:
                victim->receive_wound("qi", damage / 6 + random(damage / 6), me);
                victim->receive_wound("jing", damage / 10 + random(damage / 10), me);
                msg += HIG "$N" HIG "蓦地回转" + weapon->name() + HIG
                       "，漾起层层碧波，宛若" NOR + HIB "星河" HIG "气"
                       "旋，将$n" HIG "圈裹其中。\n" NOR;
                break;
        case 3:
        case 4:
        case 5:
        case 6:
                break;

        default:
                return msg;
                if( query_temp("weapon_performing", me) )
                        break;
                me->start_call_out(bind((: call_other, __FILE__, "continue_attack",
                                           me, victim, weapon, 5 + random(4) :), me), 0);
        }
        return msg;
}

// 绝招：12连环攻击
void continue_attack(object me, object victim, object weapon, int times)
{
        int i;
        string msg;
        int ap, dp;

        if (!me || !victim || !weapon || !me->is_fighting(victim) ||
            environment(me) != environment(victim))
                return;

        if (!living(me) || !living(victim) )
                return;

        /*
        msg  = HIC "\n$N" HIC "一声冷笑，人与" + weapon->name() +
               HIC "合而为一，飞也似的扑向$n" HIC "！\n" NOR;
        */
        msg  = HIW "霎时只听$N" HIW "纵声长啸，人与" + weapon->name() +
               HIW "融为一体，霎时间寒芒飞散，向$n" HIW "射去。\n" NOR;

        ap = me->query_skill("martial-cognize");
        dp = victim->query_skill("parry");

        if (ap / 2 + random(ap) > dp / 2)
                /*
                msg += HIR "$n" HIR "大骇之下慌忙后退，却哪里躲避得开？一时不禁破绽迭出！\n"
                       HIY "$N" HIY "抓住$n" HIY "露出的破绽，急挥手中的" +
                       weapon->name() + HIY "，连续" + chinese_number(times) +
                       "招全部指向$n" HIY "的要害！\n" NOR;
                */
                msg += HIR "$n" HIR "大骇之下连忙后退，可已然不及闪避，慌乱"
                       "中不禁破绽迭出。\n" HIW "$N" HIW "盯住$n" HIW "招中"
                       "破绽，疾速旋转手中" + weapon->name() + HIW "，电光火"
                       "石间已朝$n" HIW "攻出" + chinese_number(times) + HIW
                       "招！\n" NOR;
        else
        {
                /*
                msg += HIC "$n" HIC "冥神抵挡，将$N" HIC "这必杀一击的所有变化全然封住！\n" NOR;
                */
                msg += CYN "可是$n" CYN "冥神抵挡，将$N"
                       CYN "此招的所有变化全然封住。\n" NOR;
                message_combatd(msg, me, victim);
                return;
        }
        message_combatd(msg, me, victim);

        set_temp("weapon_performing", 1, me);
        i = times;
        while (i--)
        {
                if (!me->is_fighting(victim))
                        break;

                if (!victim->is_busy() && random(2))
                        victim->start_busy(1);

               COMBAT_D->do_attack(me,victim,query_temp("weapon", me),3);
        }
        delete_temp("weapon_performing", me);
}

// 待扩充效果
int qianghua_effect(object item, int p)
{
        int level;

        level = query("qianghua/level", item);
        if( level < 5 )
                p += p*level/10;
        if( level < 8 )
                p += p*level/3;
        else
                p += p*level/2;

        return p;
}

// 降低耐久度
void reduce_consistence(object item, object me, object victim, int damage)
{
        int st;
        int con;

        // 调用镶嵌物品攻击特效
        if( !objectp(item) ) return;

        st=query("stable", item);

        if (st < 2)
                return;

        con=query("consistence", item);

        // 寰宇天晶炼制的武器永不磨损
        if( query("material", item) == "tian jing" )
                return;

        if( query("material", item) == "no name" )
                return;

        if (random(st) > (100 - con) / 12)
                return;

        if( addn("consistence",-1, item)>0 )
                return;

        set("consistence", 0, item);

        if (environment(item))
                tell_object(environment(item), HIG "你的" +
                            item->name() + HIG "已经彻底损坏了。\n");

        item->unequip();
}

// 构造物品缺省的耐久度信息
void equip_setup(object item)
{
        int stable;
        mapping dbase;
        int max_consistence;

        dbase = item->query_entire_dbase();
        if (!undefinedp(dbase["max_consistence"]))
                max_consistence = dbase["max_consistence"];
        else
                max_consistence = 100;
        if (undefinedp(dbase["consistence"]))
               dbase["consistence"] = max_consistence;

        if( undefinedp(query("stable", item)) )
        {
                switch(query("material", item) )
                {
                case "cloth":
                        // 永远不会损坏
                        stable = 0;
                        break;

                case "paper":
                        stable = 3;
                        set("no_repair", "这东西我可没法修理。\n", item);
                        break;

                case "bone":
                        stable = 8;
                        set("no_repear", "修理这个？可别拿我寻开心。\n", item);
                        break;

                case "bamboo":
                case "wood":
                        stable = 10;
                        set("no_repair", "这东西我咋修理？\n", item);
                        break;

                case "stone":
                        stable = 20;
//                        item->set("no_repair", "这个坏了就坏了，可修不了。\n");
                        break;

                case "copper":
                        stable = 40;
                        break;

                case "silver":
                        stable = 40;
                        break;

                case "iron":
                        stable = 45;
                        break;

                case "gold":
                        stable = 50;
                        break;

                case "steel":
                        stable = 75;
                        break;

                default:
                        stable = 100;
                        break;
                }

                if (!item->is_item_make())
                        stable /= 2;

                set("stable", stable, item);
        }
}

// 兵器镶嵌的宝石攻击
void enchase_attack(object item, object me, object victim, int damage)
{
        mapping enchase,buff;
        string *apply;
        string msg, desc;
        object *inv;
        object shenlong;
        int a1, a2, a3, a4;
        int extra, avoid, i, j, n;
        int dam;

        if( !me || !victim ) return;

        //if( !item->is_item_make() ) return;

        if( !query("skill_type", item) && query("armor_type", item) != "hands" &&
             query("armor_type", item) != "finger" ) return;

        // 没有镶嵌则返回
        enchase = query("enchase/apply_prop", item);

        if( !mapp(enchase) || sizeof(enchase) < 1 )
                return;

        apply = keys(enchase);
        n = sizeof(apply);
        for( i=0;i<n;i++ )
        {
                // 发出特效
                switch( apply[i] )
                {
                case "leech_qi":
                        extra = enchase[apply[i]]; // 偷取生命%
                        if( random(100) > 70 ) break;
                        extra = damage*extra/100;
                        if( query("qi", victim) < extra ) extra = query("qi", victim);
                        if( extra < 1 ) break;
                        message_combatd(HIG + "$N" HIG "的「" + item->name() + HIG "」发出一道奇异的光芒！\n" NOR, me);

                        victim->receive_damage("qi", extra, me);
                        me->receive_heal("qi", extra);
                        msg = HIR +victim->name()+ HIR "感到自己的气血被" + item->name() + HIR "吸干了似的。\n" NOR;
                        tell_object(victim, msg);
                        msg = HIY "「" + item->name() + HIY "」吸取「" + victim->name() + HIY + "」气血：" + sprintf("%d", extra) + "点\n" NOR;
                        tell_object(me, msg);
                        break;

                case "leech_neili":
                        extra = enchase[apply[i]]; // 偷取内力%
                        if( random(100) > 70 ) break;
                        extra = damage*extra/100;
                        if( query("neili", victim) < extra ) extra = query("neili", victim);
                        if( extra < 1 ) break;
                        message_combatd(HIG + "$N" HIG "的「" + item->name() + HIG "」发出一道奇异的光芒！\n" NOR, me);

                        addn("neili", -extra, victim);
                        addn("neili", extra, me);
                        if( query("neili", me) > query("max_neili", me))
                                set("neili", query("max_neili", me), me);
                        msg = HIG +victim->name()+ HIG "感到自己的内力被" + item->name() + HIG "吸干了似的。\n" NOR;
                        tell_object(victim, msg);
                        msg = HIY "「" + item->name() + HIY "」吸取「" + victim->name() + HIY + "」内力：" + sprintf("%d", extra) + "点\n" NOR;
                        tell_object(me, msg);
                        break;

                case "add_blind":
                        extra = enchase[apply[i]]; // 致盲
                        if( random(100) > extra ) break;
                        avoid = victim->query_all_buff("avoid_blind");
                        if( avoid > 60 ) avoid = 60;
                        if( random(100) < avoid ) break;
                        message_combatd(HIG + "$N" HIG "的「" + item->name() + HIG "」发出一道奇异的光芒！\n" NOR, me);

                        msg = HIR "$N" HIR "只觉双目一阵剧痛，眼前一黑，就什么也看不见了，顿时长声痛极而呼。\n" NOR;

                        buff = ([
                                "caster":me,
                                "target":victim,
                                "type":"freeze",
                                "attr":"curse",
                                "time":5,
                                "block_msg":"all",
                                "buff_msg": msg,
                                "disa_msg":HIR "你终于抹掉了眼前的鲜血，能看见了。\n" NOR,
                        ]);
                        BUFF_D->buffup(buff);
                        break;

/*
                case "add_freeze":
                        extra = enchase[apply[i]]; // 冰冻
                        if( random(100) > extra ) break;
                        avoid = victim->query_all_buff("avoid_freeze");
                        if( avoid > 60 ) avoid = 60;
                        if( random(100) < avoid ) break;
                        message_combatd(HIG + "$N" HIG "的「" + item->name() + HIG "」发出一道奇异的光芒！\n" NOR, me);

                        msg = HIB "$N" HIB "只觉四肢僵硬，身体开始凝冻，行动迟缓，动作困难，像一个冰人似的。\n" NOR;

                        buff = ([
                                "caster":me,
                                "target":victim,
                                "type":"freeze",
                                "attr":"curse",
                                "time":5,
                                "buff_data":"freeze",
                                "buff_msg": msg,
                                "disa_msg":HIR "你终于全身开始解冻，恢复了正常。\n" NOR,
                        ]);
                        BUFF_D->buffup(buff);
                        break;
*/

                // 召唤神龙
                case "summon_shenlong":
                        extra = enchase[apply[i]];
                        if( random(100) > extra ) break;
                        if( time() - query_temp("last_summon_shenlong", me) < 180 ) break;

                        message_combatd(HIG + "$N" HIG "的「" + item->name() + HIG "」发出一道奇异的光芒！\n" NOR, me);

                        msg = HIG "「" + item->name() + HIG "」光芒万丈，一条神龙伴随着光芒从天而降。\n" NOR;
                        message_combatd(msg, me);

                        shenlong = new("/kungfu/class/misc/shenlong");

                        if( !objectp(shenlong) ) break;

                        set_temp("last_summon_shenlong", time(), me);

                        shenlong->move(environment(me));
                        set("long", HIC + me->name() + HIC "的宝物龙女·碧海神龙的力量所召唤的神龙，威风无比。\n" NOR, shenlong);
                        shenlong->kill_ob(victim);
                        shenlong->force_me("guard " + query("id", me) );
                        break;
                default :
                        break;
                }
        }
        return;
}
