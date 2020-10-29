// perform.c

#include <ansi.h>

inherit F_CLEAN_UP;

protected int do_perform(object me, string arg);

int main(object me, string arg)
{
        string and;
        int result;
        int busy;
        int lvl;
        string msg;
        string *fams;

        seteuid(getuid());

        if (me->is_busy())
                return notify_fail("( 你上一个动作还没有完成，不能施用外功。)\n");

        if (! arg) return notify_fail("你要用外功做什麽？\n");

        if (query_temp("forget", me)) 
                return notify_fail(HIR "你发现自己遗忘了绝招如何使用。\n" NOR);

        if (me->query_condition("no_perform"))
                return notify_fail(HIR "你只觉全身力道竟似涣散了一般，全然无法控制。\n" NOR);

        if (query_temp("freeze", me) && time()-query_temp("last_perform_time", me) < 1)
                return notify_fail(HIR "你处于冰冻不良的状态下，动作缓慢，无法如此快速连续使用绝招。\n" NOR);

        if (sscanf(arg, "%s and %s", arg, and) == 2 ||
            sscanf(arg, "%s twice", arg) == 1 && (and = arg))
        {
                lvl = me->query_skill("zuoyou-hubo", 1);
                if (! lvl)
                        return notify_fail("你要干什么？以为自己有三头六臂啊！\n");

      if (playerp(me))
{
                if( me->query_skill("count",1) && !query("special_skill/capture", me) )
                        return notify_fail("你杂学太多，心头烦乱，难以分心二用。\n");

                if (lvl <= 100)
                        return notify_fail("你的左右互搏修为太浅，难以分心二用。\n");

                if( query("int", me)>24 && query("int", me)<40 )
                        return notify_fail("你试图分心二用，但是手就是不听使唤。\n");

                if( (!arrayp(fams = query("reborn/fams", me)) || 
                    (member_array("全真教", fams) == -1 &&
                    member_array("古墓派", fams) == -1)) && 
                    (! me->query_family() ||
                    ( me->query_family() != "全真教" &&
                      me->query_family() != "古墓派" )))
                        return notify_fail("你试图分心二用，但是手就是不听使唤。\n");
}

                if (! me->is_fighting())
                        return notify_fail("只有战斗中才能施展左右互搏。\n");

                if (lvl < 360 && random(lvl) < 100)
                {
                        me->start_busy(1);
                        write("你试图分心二用，但是手就是不听使唤。\n");
                        return 1;
                }
        }

        if (and) set_temp("use_hubo", 1, me);

        result = do_perform(me, arg);
        if (! and)
                return result;

        if (! result)
                write(query_notify_fail());
        else
        {
                switch (random(4))
                {
                case 0:
                        msg = HIY "$N" HIY "大喝一声，双手分"
                              "使两招，一起攻出。\n" NOR;
                        break;

                case 1:
                        msg = HIY "$N" HIY "双手齐出，分使不"
                              "同招式，令人眼花缭乱。\n" NOR;
                        break;

                case 2:
                        msg = HIY "$N" HIY "左右手分使两招，"
                              "毫不停滞，宛如两人同时攻出。\n" NOR;
                        break;

                case 3:
                        msg = HIY "$N" HIY "左手一招，右手一"
                              "招，两招来路各异，令人难以低档！\n" NOR;
                        break;
                }

                message_combatd(msg, me);
        }

        busy = me->query_busy();
        me->interrupt_busy(0);

        result = do_perform(me, and);
        if (! result)
                write(query_notify_fail());

        if (intp(busy) && intp(me->query_busy()) &&
            busy > me->query_busy())
        {
                me->interrupt_busy(0);
                me->start_busy();
        }
        delete_temp("use_hubo", me);
        return 1;
}

int yc_perform(object me, string martial, string skill, string arg)//by redl 2015
{
        int l, flag = 0;
        string dir;
        string file;
        string taoism_skill, tname;
        int taoism_skill_lv;
        mixed *all_file, *allfile2 = ({});
        object target, *enemies;
        int /*busy,*/ pn;

                if (random(4)) return 0;
                if (query_temp("yc_perform/time", me) > time()) return 0;
                if (!stringp(taoism_skill = me->query_skill_mapped("taoism")) || !strlen(taoism_skill)) return 0;
                if ((taoism_skill_lv = me->query_skill(taoism_skill, 1)) < 200) return 0;
                
        if( !stringp(dir = SKILL_D(skill) + "/") ||
            file_size(dir) != -2 )
                return 0;

        if( file_size(dir + "perform/") == -2 ) {
                all_file = get_dir(dir + "perform/");
                if( !sizeof(all_file) )
                        all_file = get_dir(dir);
                else
                        dir += "perform/";
        } else
                all_file = get_dir(dir);

        if( !sizeof(all_file) )
                return 0;

        all_file = filter_array(all_file, (: is_c_file($1) :));
        
        foreach(string af in all_file) 
                if (strsrch(af, arg + ".c")<0) allfile2 += ({af});
                //DEBUG_CHANNEL("af:" + (string)(strsrch(af, arg + ".c")>-1) + "\n");
        all_file = allfile2;
        if( !sizeof(all_file) )
                return 0;

        file = all_file[random(sizeof(all_file))];
        //DEBUG_CHANNEL("file:" + file + "\n");
        l = strlen(file);
        file = dir + file[0..l-3];
        
                enemies = me->query_enemy();
                if (!enemies || !sizeof(enemies)) return 0;
                target = enemies[random(sizeof(enemies))];
                if (!target) return 0;
                
                tname = SKILL_D(taoism_skill)->name();
                switch( martial ) {
                        case "blade"    :
                                if (taoism_skill=="xuanli-daogang") {
                                        if (random(taoism_skill_lv) < 150) return 0;
//                                      pn = taoism_skill_lv / 2000 + 1;
//                                      if (pn > 2) pn = 2;
//                                      for ( int i = 0; i < pn; i++ ) {
//                                              message_combatd(HIW "$N" HIW "运起" + tname + HIW "，反手之间又向$n" HIW "劈出一招..\n" NOR, me, target);
//                                              call_other(file, "perform", me, target);
//                                      }
                                        if (playerp(me)) set_temp("yc_perform/time", time() + 35, me);
                                        message_combatd(HIW "$N" HIW "运起" + tname + HIW "，顺手向$n" HIW "又劈出一招..\n" NOR, me, target);
                                        call_other(file, "perform", me, target);
                                        if (random(taoism_skill_lv) > 1000) {
                                                message_combatd(HIW "$N" HIW "运起" + tname + HIW "，反手又向$n" HIW "劈出一招..\n" NOR, me, target);
                                                call_other(file, "perform", me, target);
                                        }
                                }
                                break;
                        case "sword"    :
                                if (taoism_skill=="baijin-jianqi") {
                                        if (random(taoism_skill_lv) < 200) return 0;
                                        if (playerp(me)) set_temp("yc_perform/time", time() + 30, me);
                                        message_combatd(HIW "$N" HIW "运起" + tname + HIW "，化作缕缕透明丝线割向$n" HIW "..\n" NOR, me, target);
                                        pn = random(taoism_skill_lv / 500) + 8;
                                        if (pn > 18) pn = 18;
                                        if (taoism_skill_lv > 600 && !target->is_weak()) {
                                                target->set_weak(pn, 0);
                                                flag = 1;
                                                message_combatd(HIW "$N" HIW "身体变得极度虚弱。\n" NOR, target);
                                        }
                                        else if (taoism_skill_lv > 1000 && !random(3) && !target->is_freeze()) {
                                                target->set_freeze(pn, 0);
                                                flag = 1;
                                                message_combatd(HIW "$N" HIW "身体冷地像冰块儿。\n" NOR, target);
                                        }
                                        else if (taoism_skill_lv > 1400 && !random(6) && !target->is_busy()) {
                                                target->start_busy(pn/2);
                                                flag = 1;
                                                message_combatd(HIW "$N" HIW "被捆得无法动弹。\n" NOR, target);
                                        }
                                        pn = (playerp(target) ? 42 : 21) - taoism_skill_lv / 1000;
                                        if (pn < 16 && playerp(target)) pn = 16;
                                        if (pn < 8) pn = 8;
                                        if (!random(pn)) {
                                                message_combatd(HIW "$N" HIW "一层层地被剑丝包裹起来..\n$N" HIW "突然全身透芒，轰然垮塌在地上，碎成了堆雪花肥牛卷。\n" NOR, target);
                                                set_temp("die_reason", NOR + "被" + me->name() + "的" + tname + "斩了" + NOR, target);
                                                flag = 1;
                                                target->die(me);
                                        }
                                        
                                        if (!flag) message_combatd(HIW "然而对$N" HIW "并没起什么卵的作用。\n" NOR, target);
                                }
                                break;
                }
        return 1;
}

protected int do_perform(object me, string arg)
{
        object weapon;
        string martial, skill, argt;
//      int result;

        if (sscanf(arg, "%s.%s", martial, arg) != 2)
        {
                if( weapon=query_temp("weapon", me) )
                        martial=query("skill_type", weapon);
                else
                        martial = "unarmed";
        }

        me->clean_up_enemy();
        if (stringp(skill = me->query_skill_mapped(martial)))
        {
                notify_fail("你所使用的外功中没有这种功能。\n");
                if (SKILL_D(skill)->perform_action(me, arg))
                {
                        set_temp("last_perform_time", time(), me);
                        //if (wiz_level(me)>3) {
                                if (!query_temp("use_hubo", me)) {
                                        if (sscanf(arg, "%s %*s", argt)) arg = argt;
                                        yc_perform(me, martial, skill, arg);
                                }
                        //}
                        //if (random(120) < (int)me->query_skill(skill))
                                //me->improve_skill(skill, 1, 1);
                        return 1;
                } else
                if (SKILL_D(martial)->perform_action(me, arg))
                {
                        set_temp("last_perform_time", time(), me);
                        //if (random(120) < (int)me->query_skill(martial, 1))
                                //me->improve_skill(martial, 1, 1);
                        return 1;
                }
                return 0;
        }

        if( !martial ) return 0;
        return notify_fail("你现在的" + to_chinese(martial)[4..7] +
                           "(" + martial + ")中并没有这种外功。\n");
}

int help (object me)
{
        write(@HELP
指令格式：perform | yong [<武功种类>.]<招式名称> [<施用对象>]
          perform | yong 招式1 [<对象1>] and 招式2 [<对象2>]
          perform | yong 招式1 [<对象1>] twice

如果你所学的外功(拳脚、剑法、刀法....)有一些特殊的攻击方式或
招式，可以用这个指令来使用，你必须先用 enable 指令指定你使用
的武功，不指定武功种类时，空手的外功是指你的拳脚功夫，使用武
器时则是兵刃的武功。

若是你的外功中有种类不同，但是招式名称相同的，或者不属於拳脚
跟武器技能的武功(如轻功)，可以用 <武功>.<招式>  的方式指定，
如：

perform sword.chan

换句话说，只要是 enable 中的武功有特殊招式的，都可以用这个指
令使用。

如果你精通左右互搏，可以同时使用两个招式攻击同一对手或则分别
攻击两人。左右互搏修炼的越是精深，则成功率越高。

使用 twice 参数表示左右手使用同样的招式。
HELP );
        return 1;
}

