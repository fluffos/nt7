// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// warcraft.c
// 魔兽系统
        // 智慧型（青龙.木）     可增加主人回避率及冥思速度
        // 攻击型（白虎.金）     可增加主人命中率及体会上限
        // 防御型（玄武.水）     可增加主人防御力及内力上限
        // 灵动型（朱雀.火）     可增加主人攻击力及潜能上限
        // 均衡型（麒麟.土）     可增加主人攻击力及精力上限

// 金的明亮、木的深沉、水的清冷、火的炙热、土的厚实。
/*
金  系  中级防御（描述：你的身上金光乱舞，使对手攻击无处着手
        。）
木  系  中级防御（描述：眼见就要打在你的身上，却发现象打在木
        头上，被强大的弹力震的身形不稳，在原地打了几个圈。）
水  系  中级防御（描述：对手的攻击打在身上就象石牛入海，不知
        所终。）
火  系  中级防御（描述：熊熊的火焰使对手浑身灼热，攻击还未递
        到身前就自己缩了回去。）
土  系  中级防御（描述：对手的攻击打在身上，却象以卵击石般攻
        击到厚实的大地上软弱无力。）
神  兽  高级防御（有战斗中自动气血恢复功能，对手无从攻击。）
兽  王  太初、太始，太初是攻击系，在防御的同时有自动攻击功能，
        太始是防御系，可防护任何属性的攻击。
*/

#include <ansi.h>
#include <name.h>
#include <command.h>
#include <combat.h>

inherit NPC;
inherit F_NOCLONE;
inherit F_OBSAVE;
inherit F_SSERVER;

#define RIDE_CMD              "/cmds/std/ride"

void remove(string euid)
{
        object env;

        if( is_fighting() ) remove_all_enemy(1);
        env = environment();
        if( objectp(env) && interactive(env) ) delete_temp("is_riding", env);
        save();
}

int is_warcraft() { return 1; }
int is_stay_in_room() { return 1; }

int is_owner(object me) { return query_temp("owner") == query("id", me); }
string chinese_s(mixed arg)
{
      if (arg == "白虎")  return HIY "金" NOR;
      if (arg == "青龙")  return WHT "木" NOR;
      if (arg == "玄武")  return HIG "水" NOR;
      if (arg == "朱雀")  return HIR "火" NOR;
      if (arg == "麒麟")  return YEL "土" NOR;
}

void create()
{
        seteuid(getuid());

        set_name("魔幻兽", ({ "warcraft" }));
        set("long", "玩家可以骑上它去指定的地方(rideto)。\n");
        set("race", "野兽");
        set("race_type", WHT "青龙" NOR);
        set("unit", "只");
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("no_sell", "这你也要卖？你忘记当初与它的血之盟约吗？");
        set("owner", "lonely");
        set("owner_name", "高处不胜寒");
        set("limbs", ({ "头部", "身体", "前心", "後背", "尾巴" }) );
        set("verbs", ({ "bite", "hoof" }) );

        set("qi", 300);
        set("max_qi", 300);
        set("jing", 100);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("jingli", 100);
        set("max_jingli", 100);
        set("shen_type", 0);
        set("combat_exp", 50000);
        set("attitude", "peaceful");
        set("obedience", 2);
        set("ridable", 1);

        set_skill("dodge", 100);
        set_skill("unarmed", 100);
        set_skill("parry", 100);
        set_skill("force", 100);

        set_temp("apply/attack", 1000);
        set_temp("apply/unarmed_damage", 1000);
        set_temp("apply/defence",1000);
        set_temp("apply/armor", 2000);
        set_temp("apply/dodge", 1000);
        set_temp("apply/parry", 1000);
        if (! check_clone()) return 0;
        restore();
        setup();

        keep_heart_beat();
}

varargs string short(int raw)
{
        string str;

        str = ::short();
        str += " ≈" + query("race_type") + "≈";
        return str;
}

string get_level()
{
        string level;

        if( query("level")/10 < 9 )
                level = CHINESE_D->chinese_number(query("level")/10+1) + "级" + CHINESE_D->chinese_number(query("level")%10) + "阶";
        else
        if( query("level")/10 == 9 )
                level = HIM "上古神兽" NOR;
        else
                level = HIY "远古圣兽" NOR;

        // 太始、太初
        return level;
}

string long()
{
        string result;
        string level;

        result = query("long");

        level = get_level();

        result += "\n";
        result += HIW "幻兽等级：" + level + "\n" NOR;
        result += HIW "魔力属性：" + chinese_s(query("race_type")) + "\n" NOR;
        result += HIW "魔力数值：" + query("magic/power")  + "\n" NOR;
        result += "\n";

        return result;
}

void init()
{
        if( query("id", this_player()) == query("owner") ) {
                add_action("do_modify", "modify");
                add_action("do_teach", "teach");
                add_action("do_shape", "shape");
        }

}

void del_hiding(object me, object target)
{

        if( !objectp(me) && !objectp(target) ) return;

        if( objectp(me) )
                delete_temp("hiding_kuihua", me);

        if( objectp(target) )
                target->clear_condition("no_perform");

        return;
}

void del_protect(object me)
{
        if( !objectp(me) ) return;

        delete_temp("protect_xuanwu", me);

        addn_temp("reduce_damage", -60, me);

        return;
}

void heart_beat()
{
        object owner, ob, target;
        object env, env1, env2;

        ob = this_object();

        // 自动回复状态
        if( !is_fighting() && (query("qi") < query("max_qi") ||
            query("jing") < query("max_jing") ||
            query("eff_qi") < query("max_qi") ||
            query("eff_jing") < query("max_jing")) )
                    full_self();

        // 如果主人下线则自动保存后离开
        if( !(env1=environment()) || !objectp(owner = find_player(query("owner", ob))) ) {
                message_vision("$N一闪就不见了。\n", ob);
                destruct(ob);
                return;
        }

        if( !(env2=environment(owner)) ) return;
        // 如果主人不在同一地图则移动主人面前
        // 动作状态；仅仅跟随(follow)、保护(guard)
        if( living(ob) && (query_temp("comedby", owner) == ob || query("actions", ob)) &&
            env1 != env2 && env1 != owner && !query("no_magic", env2) ) {
                if( is_fighting() ) remove_all_enemy(1);
                ob->move(env2);
                message_vision("忽然一阵旋风袭过，$n" NOR "已出现在这里。\n", owner, ob);

                // 自动跟随
                ob->set_leader(owner);

                // 自动保护，如果是仅跟随状态则不保护
                if( query("actions", ob) == "guard" ) {
                        GUARD_CMD->main(ob, owner);
                }
        }

        env = environment();
        if( env != owner && env != env2 )
                ;
        else {

        // 气血小于保护限制则隐藏
        if( query("env/wimpy") > 0 && query("env/wimpy") < 100 ) {
                if (query("qi") * 100 / query("max_qi") <= query("env/wimpy") ) {
                        if( env == owner ) {
                                delete_temp("is_riding", owner);
                                delete_temp("is_rided_by");
                        }
                        // 隐藏
                        message_vision(HIR "\n$N" HIR "迅速移动到" + owner->name() + HIR "身后，躲了起来。\n" NOR, ob);
                        destruct(ob);

                        return;
                }
        }

        // 同伴技能=========
        // 疗伤，扰乱，清醒，震慑，防护
        // 加生命、加杀气、加命中闪避
        // A、护卫战斗B、减少伤害C、增加伤害D、伤害豁免E、虚弱状态

        // 麒麟--治疗
        if( (query("max_qi", owner) > query("qi", owner) || query("max_qi", owner) > query("eff_qi", owner))
            && query("race_type") == "麒麟" ) {
                if( random(15) < query("level")/10 ) {
                        tell_object(owner, HIY + ob->name() + HIY "全身闪出火红般的光芒照向你，你感觉气血有所恢复。\n" NOR);
                        addn("qi", 500 + random(query("magic/power"))*200, owner);
                        addn("eff_qi", 200 + random(query("magic/power"))*80, owner);
                        if( query("eff_qi", owner) > query("max_qi", owner) ) set("eff_qi", query("max_qi", owner), owner);
                        if( query("qi", owner) > query("max_qi", owner) ) set("qi", query("max_qi", owner), owner);
                }
        }

        // 白虎--令对手忙乱
        if( query("race_type") == "白虎" && owner->is_fighting() ) {
                int time_busy;
                target = offensive_target(owner);
                if( objectp(target) && random(15) < query("level")/10 && !target->is_busy() ) {
                        message_vision(HIG "$N" HIG "长嘶一声，震耳欲聋，冲天而起，直扑向$n" HIG "$n" HIG
                                       "被这突如其来的变故弄得手忙脚乱。\n" NOR, ob, target);
                        time_busy = 1 + random(1 + query("level")/10);
                        if( time_busy > 5 ) time_busy = 5;
                        target->start_busy(time_busy);
                }
        }

        // 朱雀--降低主人忙乱时间
        if( query("race_type") == "朱雀" && owner->is_fighting() ) {
                int int_busy;
                if( owner->is_busy() && random(15) < query("level")/10 ) {
                        tell_object(owner, HIM + ob->name() + HIM "扇动着巨大的翅膀，狂风四起，你感觉突然见轻松了许多。\n" NOR);

                        int_busy = 1 + random(1 + query("level")/10);
                        owner->interrupt_me(owner, int_busy);
                }
        }

        // 青龙--震慑对手，令其暂时无法攻击，此效果时间随机为3-7秒
        if( query("race_type") == "青龙" && owner->is_fighting() ) {
                target = offensive_target(owner);
                if( objectp(target) && random(15) < query("level")/10 && !query_temp("hiding_kuihua", owner) ) {
                        message_vision(HIR "$N" HIR "对着$n" HIR"一声长啸，$n" HIR "突觉心神俱裂，难受无比。\n" NOR,
                                       ob, target);

                        set_temp("hiding_kuihua", 1, owner);
                        target->apply_condition("no_perform", 7);
                        remove_call_out("del_hiding");
                        call_out("del_hiding", 3 + random(5), owner, target);
                }
        }

        // 玄武--防护
        // 玄武--减少主人伤害
        if( query("race_type") == "玄武" && owner->is_fighting() ) {
                if( random(15) < query("level")/10 && !query_temp("protect_xuanwu", owner) ) {
                        tell_object(owner, HIM + ob->name() + HIM "发出一道耀眼的光芒，将你全身笼罩在内，你感觉到全身表面有层龟壳般保护。\n" NOR);
                        addn_temp("reduce_damage", 60, owner);
                        set_temp("protect_xuanwu", 1, owner);
                        remove_call_out("del_protect");
                        call_out("del_protect", 3 + random(5), owner);
                }
        }
        }

        ::heart_beat();
}

int do_modify(string arg)
{
        string item, msg;
        object me = this_player();

        if( !arg || sscanf(arg,"%s %s", item, msg) != 2 )
                return notify_fail("SYNTAX: modify 款项 内容\n");

        if( item == "flee" ) {
                set("env/wimpy", atoi(msg));
                write("ＯＫ\n");
                save();
                return 1;
        }

        if( item == "actions" ) {
                if( msg != "follow" && msg != "guard" )
                        return notify_fail("你只可以设置为follow或者guard状态。\n");

                set("actions", msg);
                set_temp("comedby", this_object(), me);
                write("ＯＫ\n");
                save();
                return 1;
        }

        if( CHINESE_D->check_control(msg) )
                return notify_fail("描述不可有控制符！\n");

        if( CHINESE_D->check_space(msg) )
                return notify_fail("描述必需不含空格！\n");

        if( CHINESE_D->check_return(msg) )
                return notify_fail("描述必需不含回车键！\n");

        msg = trans_color(msg, 3);
        switch(item)
        {
        case "desc":
                if( CHINESE_D->check_length(msg) > 100 )
                        return notify_fail("描述太长！\n");
                set("long", msg+NOR"\n");
                write("ＯＫ\n");
                save();
                return 1;
        case "nickname" :
                if( CHINESE_D->check_length(msg) > 20 )
                        return notify_fail("描述太长！\n");
                set("nickname",msg+NOR);
                write("ＯＫ\n");
                save();
                return 1;
        case "title" :
                if( CHINESE_D->check_length(msg) > 20 )
                        return notify_fail("描述太长！\n");
                set("title",msg+NOR);
                write("ＯＫ\n");
                save();
                return 1;
        case "arrive_msg" :
                if( CHINESE_D->check_length(msg) > 60 )
                        return notify_fail("描述太长！\n");
                set("arrive_msg",msg+NOR);
                write("ＯＫ\n");
                save();
                return 1;
        case "leave_msg" :
                if( CHINESE_D->check_length(msg) > 60 )
                        return notify_fail("描述太长！\n");
                set("leave_msg",msg+NOR);
                write("ＯＫ\n");
                save();
                return 1;

        }
        return notify_fail("你要修改什么？\n");

}

int do_teach(string arg)
{
        object me;
        int gin_cost,amount;
        int myskill, itskill;

        me = this_player();

        if( !myskill = me->query_skill(arg, 1) )
                return notify_fail("这项技能你好象还不会呢！\n");

        if( arg != "unarmed" && arg != "parry" && arg != "dodge" && arg != "force" )
                return notify_fail("它学不会这项技能的！\n");

        itskill = query_skill(arg,1);
        if( myskill <= itskill )
                return notify_fail(name()+"以嘲笑的目光望着你。\n");

        if( query("potential", me) - query("learned_points", me) < 1 )
                return notify_fail("你的潜能不够！\n");

        gin_cost = 100/ (int) query_int();
        if( (int)query("jing", me) < gin_cost )
                return notify_fail("你显然太累了没有办法教！\n");

        me->receive_damage("jing", gin_cost);
        addn("potential", -1, me);
        amount = (int)me->query_int() * (int) query_int();
        message_vision(sprintf("$N不厌其烦地教$n「%s」。\n", to_chinese(arg)), me, this_object());

        if( random(100) < query("obedience") )
                command("emote 很不情愿地哼了一声。");
        else
        {
                improve_skill(arg, amount);
                message_vision(sprintf("$N似乎真的学会了一些「%s」！\n", to_chinese(arg)), this_object());
        }
        return 1;

}

string status_color(int current, int max)
{
        int percent;

        if( max>0 ) percent = current * 100 / max;
                else percent = 100;
        if( percent > 100 ) return HIC;
        if( percent >= 90 ) return HIG;
        if( percent >= 60 ) return HIY;
        if( percent >= 30 ) return YEL;
        if( percent >= 10 ) return HIR;
        return RED;
}
/*
int do_shape(string arg)
{
        mapping my;
        string shape;
        mixed at_pt, pa_pt, do_pt;

        my = query_entire_dbase();

        printf("精气： %s%3d/ %3d %s(%3d%%)"NOR"  气血： %s%3d/ %3d %s(%3d%%)\n"+NOR,
                status_color(my["jing"], my["eff_jing"]), my["jing"],my["eff_jing"],
                status_color(my["eff_jing"], my["max_jing"]),     my["eff_jing"] * 100 / my["max_jing"],
                status_color(my["qi"], my["eff_qi"]), my["qi"], my["eff_qi"],
                status_color(my["eff_qi"], my["max_qi"]),     my["eff_qi"] * 100 / my["max_qi"]
        );

        printf("食物： %d\t\t饮水： %d\n",
        my["food"], my["water"]);
        printf("主人： %s\t\t等级： %s\n",
        my["owner"],get_level());
        printf("经验： %d\t\t杀气： %d\n",
        my["combat_exp"],my["bellicosity"]
        );
        printf("智慧： %d\t\t体质： %d\n",
        query_int(), query_con()
        );
        printf("速度： %d\t\t力量： %d\n",
        query_dex(), query_str()
        );

        at_pt= COMBAT_D->skill_power(this_object(), "unarmed", SKILL_USAGE_ATTACK);
        pa_pt= COMBAT_D->skill_power(this_object(), "parry", SKILL_USAGE_DEFENSE);
        do_pt= COMBAT_D->skill_power(this_object(), "dodge", SKILL_USAGE_DEFENSE);
        printf("攻击： %d\t\t防御： %d\n\n",
        at_pt+1, pa_pt/2+do_pt/2+1
        );
        return 1;
}
*/

// 显示同伴状态
int do_shape(string arg)
{
        object ob;
        string line = HIC "=-------------------------------------=\n" NOR;
        string str;
        mixed at_pt, pa_pt, do_pt;
        string actions;

        ob = this_object();


        actions = query("actions", ob);
        if( !stringp(actions) )

                actions = "自由";
        else
                actions == "follow" ? "仅跟随" : "保护";

	str = HIY + ob->name() + HIY "状态属性如下(" + HIR + actions + HIY + ")：\n" NOR;
        str += line;

        str += HIR "等级：" + sprintf("%s",get_level()) + "\n" NOR;
        str += HIR "属性：" + sprintf("%s",chinese_s(query("race_type"))) + "\n" NOR;
        str += HIR "魔值：" + sprintf("%d",query("magic/power")) + "\n" NOR;

        str += HIW "经验：" + sprintf("%d", query("combat_exp")) + "\n" + NOR;
        str += HIW "悟性：" + sprintf("%-22d速度：%d", query("int"), query("dex")) + "\n" + NOR;
        str += HIW "臂力：" + sprintf("%-22d根骨：%d", query("str"), query("con")) + "\n" + NOR;

        str += HIC "生命：" + sprintf("%d", query("qi")) + "/" + sprintf("%d", query("eff_qi")) + "\n" NOR;
        str += HIC "内力：" + sprintf("%d", query("neili")) + "/" + sprintf("%d", query("max_neili")) + "\n" NOR;
        str += HIC "精气：" + sprintf("%d", query("jing")) + "/" + sprintf("%d", query("eff_jing")) + "\n" NOR;
        str += HIC "精力：" + sprintf("%d", query("jingli")) + "/" + sprintf("%d", query("max_jingli")) + "\n" NOR;

        at_pt= COMBAT_D->skill_power(this_object(), "unarmed", SKILL_USAGE_ATTACK);
        pa_pt= COMBAT_D->skill_power(this_object(), "parry", SKILL_USAGE_DEFENSE);
        do_pt= COMBAT_D->skill_power(this_object(), "dodge", SKILL_USAGE_DEFENSE);

        str += HIM "攻击：" + sprintf("%d", at_pt+1) + "\n" NOR;
        str += HIM "防御：" + sprintf("%d", pa_pt/2+do_pt/2+1) + "\n" NOR;

        str+= line;

        write(str);
        return 1;
}

varargs mixed set(string idx, mixed para, object ob)
{
        int i, j, lvl, level;

        if( !ob )
                ob = this_object();

        if( idx == "combat_exp" && para ) {
                if( para > query("combat_exp") ) {
                        level = query("level");
                        if( !level || level < 1 ) level = 1;

                        for (i = level; ;i++) {
                                if( (i + 1) * (i + 1) * (i + 1) > (para / 10000) ) {
                                        lvl = i;
                                        break;
                                }
                        }

                        if( lvl > level ) {
                                j = lvl - level;
                                set("level", lvl);

                                addn("max_jingli", 100000*j);
                                addn("max_neili", 200000*j);
                                addn("max_jing", 50000*j);
                                addn("max_qi", 30000*j);
                                addn("int", j);
                                addn("str", j);
                                addn("con", j);
                                addn("dex", j);
                                set("magic/power", 10000*lvl);

                                add_skill("dodge", 50*j);
                                add_skill("parry", 50*j);
                                add_skill("unarmed", 50*j);
                                add_skill("force", 50*j);

                                message_vision(HIY "$N" HIY "身忽的泛起红光，无数道紫光隐入$N" HIY "的身体，不见了！\n" NOR, ob);
                                if( lvl%10 == 0 )
                                        message_vision(HIY "突然天空出现一道玄光与$N" HIY "身泛起的红光相接，$N" HIY "全体通红！\n" NOR, ob);
                                save();
                        }
                }
                return set_db(idx, para);
        } else
                return set_db(idx, para);
}

mixed add(string prop, mixed data)
{
        string para;
        mixed old;
        int level;

        if( prop == "combat_exp" ) {
                if( !(old = query(prop)) )
                        return set(prop, data);

                if( data < 1 )
                        return set(prop, old + data);

                level = query("level");
                if( !level || level < 1 ) level = 1;

                return set(prop, old + data);
        } else
                return addn(prop, data);
}

// 召唤接口
varargs int receive_whistle(object me, int flag)
{
        object env, follower;
        int    period;

        if( (env = environment()) && env == me )
        {
                write(name() + "你不是正骑着吗？你召唤个什么劲？\n");
                return 1;
        }

        if( env == environment(me) )
        {
                if( is_fighting() )
                        remove_all_enemy(1);

                if( flag )
                {
                        RIDE_CMD->do_ride(me, this_object());
                        return 1;
                }
                message_vision(name() + "一闪就不见了。\n", me);
                /*
                period = time() - ((int) query("last_save"));
                if( period < 0 || period > 900 )
                {
                        set("last_save", time());
                        save();
                }
                */
                destruct(this_object());
                return 1;
        }
        else
        {
                if( env )
                {
                        if( env->is_character() && environment(env) )
                                env = environment(env);

                        message("vision", HIG "突然" + name() + HIG "化作一道光芒，"
                                HIG "瞬间消失了！\n\n" NOR, env);

                        if( interactive(env = environment()) )
                        {
                                delete_temp("is_riding", env);
                                delete_temp("is_rided_by");
                                tell_object(env, HIM + name() +
                                        HIM "忽然离你而去了！\n" NOR);
                                // 让所有的人也下马
                                if (objectp(follower = query_temp("is_rided_follow", this_object())))
                                {
                                        delete_temp("is_riding_follow", follower);
                                        delete_temp("is_rided_follow");
                                        tell_object(follower, HIM + name() + HIM "忽然离你而去了！\n" NOR);
                                }
                        }
                }
                message_vision(HIG "$n" HIG "不知从哪里窜到$N" HIG "面前！\n\n" NOR,
                        me, this_object());
        }

        move(environment(me));

        if( environment() != environment(me) )
                return 1;

        RIDE_CMD->main(me, query("id"));

        return 1;
}

varargs void die(object killer)
{
        object owner;
        int exp;


        owner = UPDATE_D->global_find_player(query("owner"));

        if( !objectp(owner) )
                return ::die(killer);

        message_vision(HIR "$N" HIR "哀伤地说道：对不起，主人，我不能再保护你了，珍重！\n" NOR, this_object());
        tell_object(owner, HIG "你的魔兽死亡了，请到张天师处［ask zhang about 魔兽复活］来复活你的魔兽！\n" NOR);
        set("warcraft/status", "died", owner);

        UPDATE_D->global_destruct_player(owner, 1);

        // 死亡掉经验2%
        exp = query("combat_exp");
        add("combat_exp", -exp*2/100);

        // 状态复原
        full_self();

        destruct(this_object());

        return;
}

varargs void unconcious(object defeater)
{
        die(defeater);
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;

        result = ([ "damage": -query("magic/power") ]);

        result += (["msg" :   HIC "$N" HIC "的攻击打在$n"
                              HIC "厚实的护甲上。\n" NOR ]);

        return result;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{

        ob->receive_wound("qi", 200 + query("magic/power"), me);

        return sort_msg(HIR "$N" HIR "张嘴朝着$n，" HIR "喉咙深处微"
               "微闪出光芒，一团约十公分大小的火球，自$N"
               HIR "嘴中射出，飞快的击中$n" HIR "的胸口，"
               "$n" HIR "蹬蹬蹬的倒退了几步，跪了下来。\n" NOR);
}

/*
int do_look(string target)
{
        object ob, me;

        string msg;

        ob = this_object();


        if (! id(target))
                return notify_fail("你要看什么？");

        if (! stringp(msg = query("look_msg", ob)) ) return 1;

        message_sort(HIC + "\n" + msg + "\n" NOR, this_object());

        return 1;
}

int accept_ask(object who, string topic)
{
        // 设置的回答列表
        object ob;

        mapping ans;
        string *key_ans;
        string msg;

        if (! sizeof(topic))return 0;

        ob = this_object();
        ans = query("answer", ob);

        if (! sizeof(ans))return 0;

        key_ans = keys(ans);

        if (! sizeof(key_ans))return 0;

        if (member_array(topic, key_ans) == -1)return 0;

        return ans[topic];

}

// whichask 指令返回的列表
mixed whichask()
{
        object ob;

        mapping ans;
        string *key_ans;
        string msg;
        int i;

        ob = this_object();
        ans = query("answer", ob);

        if (! sizeof(ans))return 0;

        key_ans = keys(ans);

        if (! sizeof(key_ans))return 0;

        msg = "";
        for (i = 0; i < sizeof(key_ans); i ++)
        {
                if (i < 10)
                        msg = msg + sprintf(" %d", i + 1) + ". " + key_ans[i] + "\n";
                else
                        msg = msg + sprintf("%d", i + 1) + ". " + key_ans[i] + "\n";
        }


        return msg;
}

// 查询设置的对话列表
mixed answer_list()
{
        object ob;

        mapping ans;
        string *key_ans;
        string msg;
        int i;

        ob = this_object();
        ans = query("answer", ob);

        if (! sizeof(ans))return 0;

        key_ans = keys(ans);

        if (! sizeof(key_ans))return 0;

        msg = "";
        for (i = 0; i < sizeof(key_ans); i ++)
        {
                if (i < 10)
                {
                        msg += HIG + sprintf(" %d", i + 1) + ". " + "ask    : " + key_ans[i] + "。\n" NOR;
                        msg += HIR "    answer : " + ans[key_ans[i]] + "\n\n" NOR;
                }
                else
                {
                        msg += HIG + sprintf("%d", i + 1) + ". " + "ask    : " + key_ans[i] + "。\n" NOR;
                        msg += HIR "   answer : " + ans[key_ans[i]] + "\n\n" NOR;
                }
        }


        return msg;
}

int delete_answer(int n)
{
        object ob;

        mapping ans;
        string *key_ans;
        int i;

        ob = this_object();

        ans = query("answer", ob);

        if (! sizeof(ans)) return notify_fail("（A）无法删除该信息。\n");

        key_ans = keys(ans);

        if (! sizeof(key_ans)) return notify_fail("（B）无法删除该信息。\n");

        if (n > sizeof(key_ans) + 1)
                return notify_fail("（C）无法删除该信息。\n");

        if (n < 1)
                return notify_fail("（D）无法删除该信息。\n");

        // 开始删除
        map_delete(ans, key_ans[n - 1]);
        set("answer", ans, ob);
        write("删除完毕！\n");
        return 1;
}
*/

// 接受存盘数据的接口函数
int receive_dbase_data(mixed data)
{
        mapping temp;
        if( !mapp(data) )
                return 0;

        temp = DATABASE_D->db_restore_skill(this_object());
        this_object()->set_SKILL(temp);
        this_object()->set_dbase(data);

        return 1;
}

// 进行保存数据的接口函数
mixed save_dbase_data()
{
        mapping data;
        mapping temp;

        temp = this_object()->query_SKILL();
        DATABASE_D->db_save_skill(this_object(), temp);
        data = this_object()->query_entire_dbase();

        return data;
}
