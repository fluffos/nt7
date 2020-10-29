// This program is a part of NITAN MudLIB 
// redl 2015/10
// 广成金船里掉落
inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(NOR CYN "乾坤"YEL"符昭"NOR, ({"qiankun fuzhao", "fu", "fuzhao"}));
        set("long",
                "这是张神秘的符纸，使用(use 数字序号)可以抽取虚弱的对手的魂魄，作为你在乾坤棋盘里的茶宠。\n");
        set("unit", "张");
        set("weight", 10);
        set("value", 100000000);
}

int random2 (int i)
{
        return (random(i)+uptime()) % i;
}

int rdm(object me, object target, int step)
{
        object p1, p2;
        object room = environment(me);
        int lv1, lv2;
        
        if (step && me && target) {
                if (step==1) {
                        p1 = me;
                        p2 = target;
                } else if (step==2) {
                        p1 = target;
                        p2 = me;
                } else if (step==3) {
                        p1 = me;
                        p2 = target;
                } else if (step==4) {
                        p1 = target;
                        p2 = me;
                } 
                
                if (step==1 || step==2) {
                        lv1 = p1->query_skillo("du-sheng", 1);
                        lv2 = p2->query_skillo("du-sheng", 1);
                        if (lv1 && !random(4)) {
                                tell_room(room, NOR + CYN + query("name", p1) + NOR + CYN + "桀桀桀地冒出几声阴笑，\n然后慢慢吐出口气道：赌～～啊～～～\n" + NOR);
                                if (random(lv2*3) > lv1) {
                                        tell_room(room, NOR + CYN + query("name", p2) + NOR + CYN + "中食指轻揉双太阳穴，猛地睁大眼睛冲着" + query("name", p1) + NOR + CYN + "一盯。\n" + NOR);
                                        tell_room(room, NOR + CYN + query("name", p1) + NOR + CYN + "噗地涌上一口鲜血，又强忍着内伤吞了回去。\n" + NOR);
                                        return random2(6);
                                } else {
                                        tell_room(room, NOR + CYN + query("name", p1) + NOR + CYN + "继续怪笑道：～啊～～～～圣～～\n" + NOR);
                                        return 6;
                                }
                        }
                } else if (step==3 || step==4) {
                        lv1 = p1->query_skillo("du-shen", 1);
                        lv2 = p2->query_skillo("du-shen", 1);
                        if (lv1 && !random(5)) {
                                tell_room(room, NOR + CYN + query("name", p1) + NOR + CYN + "悠闲地嚼着巧克力，\n手指上的戒指却偷偷对着骰子一晃...\n" + NOR);
                                if (random(lv2*3) > lv1) {
                                        tell_room(room, NOR + CYN + query("name", p2) + NOR + CYN + "皱皱眉，拿起嘴里衔着的大雪茄，对" + query("name", p1) + NOR + CYN + "劈脸一喷。\n" + NOR);
                                        tell_room(room, NOR + CYN + query("name", p1) + NOR + CYN + "被呛得咳嗽不止，气急指着" + query("name", p2) + NOR + CYN + "道：你～～\n" + NOR);
                                        return random2(6);
                                } else {
                                        tell_room(room, NOR + CYN + query("name", p1) + NOR + CYN + "脸上露出赌神一样的招牌微笑。\n" + NOR);
                                        if (step==3) return query("a_n1");
                                        if (step==4) return query("b_n1");
                                }
                        }
                }
        }
        
        return random2(6) + 1;
}

void display_bet(int i, int j)
{
        string str;
        object room = environment();
        switch (i)
        {
        case 1:
                str = ((j) ? RED : HIW) + 
"┌───┐\n"+
"│　　　│\n"+
"│　●　│\n"+
"│　　　│\n"+
"└───┘\n" + NOR;
                break;
        case 2:
                str = ((j) ? RED : HIW) + 
"┌───┐\n"+
"│　　　│\n"+
"│●　●│\n"+
"│　　　│\n"+
"└───┘\n" + NOR;
                break;
        case 3:
                str = ((j) ? RED : HIW) + 
"┌───┐\n"+
"│●　　│\n"+
"│　●　│\n"+
"│　　●│\n"+
"└───┘\n" + NOR;
                break;
        case 4:
                str = ((j) ? RED : HIW) + 
"┌───┐\n"+
"│●　●│\n"+
"│　　　│\n"+
"│●　●│\n"+
"└───┘\n" + NOR;
                break;
        case 5:
                str = ((j) ? RED : HIW) + 
"┌───┐\n"+
"│●　●│\n"+
"│　●　│\n"+
"│●　●│\n"+
"└───┘\n" + NOR;
                break;
        case 6:
                str = ((j) ? RED : HIW) + 
"┌───┐\n"+
"│●　●│\n"+
"│●　●│\n"+
"│●　●│\n"+
"└───┘\n" + NOR;
                break;
        }
        tell_room(room,str + "(" + (string)i + ")点\n" + NOR);
}

int do_start_bet(object me, object target, int step)
{
                string jgmsg1, jgmsg2;
                int sklv1, sklv2, iaccept, itmp;
                float eff, efftmp;
        if (!me || !target) return 0;
        if (!environment(me) || !environment(target)) return 0;
        if (environment(me) != environment(target)) return 0;
        me->start_busy(2);
        target->start_busy(2);
        switch(step)
        {
                case 0:
                        set_temp("flag_bet", 1);
                                        message_vision(NOR "$N大声道：$n你可敢接下此符？\n" NOR, me, target);
                                        sklv1 = target->query_skillo("du-sheng", 1);
                                        sklv2 = target->query_skillo("du-shen", 1);
                                        eff = 1.00;
                                        efftmp = to_float(query("qi", target)) / to_float(query("max_qi", target));
                                        if (efftmp < eff) eff = efftmp;
                                        efftmp = to_float(query("eff_qi", target)) / to_float(query("max_qi", target));
                                        if (efftmp < eff) eff = efftmp;
                                        efftmp = to_float(query("jing", target)) / to_float(query("max_jing", target));
                                        if (efftmp < eff) eff = efftmp;
                                        efftmp = to_float(query("eff_jing", target)) / to_float(query("max_jing", target));
                                        if (efftmp < eff) eff = efftmp;
                                        iaccept = random(to_int(eff * 100)) + to_int(eff * 100)/10 - sklv1/10 - sklv2/5;
                                        //DEBUG_CHANNEL("iaccept:" + (string)iaccept + "\n");
                                        if ( iaccept < 15 ) {
                                                if (eff < 0.4) 
                                                        message_vision(NOR "$N大喜过望道：正当博取这一线生机。\n" NOR, target);
                                                else
                                                        message_vision(NOR "$N想也不想说道：吾有何不敢？\n" NOR, target);
                                        } else {
                                                message_vision(NOR "$n一把扯掉" + name() + NOR "，理都没理$N的挑衅。\n" NOR, me, target);
                                                delete_temp("flag_bet");
                                                return 0;
                                        }
                    break;
                case 1:
                        tell_room(environment(), RED + me->name() + NOR + "轻轻一扔，骰子滴溜溜一转：\n");
                        display_bet(itmp = rdm( me,  target,  step), 1);
                        set("a_n1", itmp);
                                                break;
                case 2:
                        tell_room(environment(), HIW + target->name() + NOR + "轻轻一扔，骰子滴溜溜一转：\n");
                        display_bet(itmp = rdm( me,  target,  step), 0);
                        set("b_n1", itmp);
                                                break;
                case 3:
                        tell_room(environment(), RED + me->name() + NOR + "对着骰子哈了口气，狠狠地一扔：\n");
                        display_bet(itmp = rdm( me,  target,  step), 1);
                        set("a_n2", itmp);
                                                break;
                case 4:
                        tell_room(environment(), HIW + target->name() + NOR + "对着骰子哈了口气，狠狠地一扔：\n");
                        display_bet(itmp = rdm( me,  target,  step), 0);
                        set("b_n2", itmp);
                                                break;
                                default:
                                if (query("a_n1") == query("a_n2")) {
                                        jgmsg1 = "\"" + "一对" + chinese_number(query("a_n1")) + "\"";
                                        set("a_n1", (query("a_n1") + query("a_n2")) * 100);
                                }
                                else {
                                        set("a_n1", query("a_n1") + query("a_n2"));
                                                                                jgmsg1 = "\"" + chinese_number(query("a_n1")) + "点" + "\"";
                                }
                                        
                                if (query("b_n1") == query("b_n2")) {
                                        jgmsg2 = "\"" + "一对" + chinese_number(query("b_n1")) + "\"";
                                        set("b_n1", (query("b_n1") + query("b_n2")) * 100);
                                }
                                else  {
                                        set("b_n1", query("b_n1") + query("b_n2"));
                                        jgmsg2 = "\"" + chinese_number(query("b_n1")) + "点" + "\"";
                                }

                                if (query("a_n1") > query("b_n1")) {
                                        message_vision(NOR + name() + "上一行字显示：" + jgmsg1 + "大于" + jgmsg2 + "，" +  "$N" + NOR + "得胜。\n" + NOR, me);
                                        return 1;
                                } else if (query("a_n1") < query("b_n1")) {
                                        message_vision(NOR + name() + "上一行字显示：" + jgmsg2 + "大于" + jgmsg1 + "，" +  "$N" + NOR + "得胜。\n" + NOR, target);
                                } else {
                                        message_vision(NOR + name() + "上一行字显示：" + jgmsg1 + "等于" + jgmsg2 + "，" +  "$N" NOR "和$n" + NOR + "平局。\n" + NOR, me, target);
                                }
                                return 0;
                }
        step += 1;
        return do_start_bet(me, target, step);
}

int do_use(string arg)
{
        int i, need;
        object *enemies, enemy;
        object chong, me = this_player();
        if (!environment() || environment()!=me) return 0;
        if (!arg) return notify_fail("参数为数字1-9。\n");
        if (strlen(arg)!=1) return notify_fail("参数为数字1-9。\n");
        if (arg[0] < '1' || arg[0] > '9') return notify_fail("参数为数字1-9。\n");
        if (me->is_busy()) {
                write (NOR BUSY_MESSAGE NOR);
                return 1;
        }
        if (!me->is_fighting()) {
                write (NOR "你必须在战斗里才能使用。" NOR);
                return 1;
        }
        me->start_busy(1);
        i = to_int(arg);
        need = i*i*i/2 + 1;//到第9颗需要365枚棋子，约18万泥潭币
/*参数为数字1-9。
你的乾坤白棋子数量不足以支持这么多茶宠(需要1枚棋子)。
你的乾坤白棋子数量不足以支持这么多茶宠(需要5枚棋子)。
你的乾坤白棋子数量不足以支持这么多茶宠(需要14枚棋子)。
你的乾坤白棋子数量不足以支持这么多茶宠(需要33枚棋子)。
你的乾坤白棋子数量不足以支持这么多茶宠(需要63枚棋子)。
你的乾坤白棋子数量不足以支持这么多茶宠(需要109枚棋子)。
你的乾坤白棋子数量不足以支持这么多茶宠(需要172枚棋子)。
你的乾坤白棋子数量不足以支持这么多茶宠(需要257枚棋子)。
你的乾坤白棋子数量不足以支持这么多茶宠(需要365枚棋子)。*/
        if ( need > query("qiankunqipan/limit_guest", me)) {
                write(NOR "你的乾坤白棋子数量不足以支持这么多茶宠(需要"+(string)need+"枚棋子)。\n" NOR); 
                return 1;
        }
        enemies = me->query_enemy();
        if( !enemies || sizeof(enemies) < 1 ) {
                write (NOR "你目前没有敌人。" NOR);
                return 1;
        }
        enemy = enemies[random(sizeof(enemies))];
        if (!enemy) {
                write (NOR "你目前没有敌人。" NOR);
                return 1;
        }
        if (!enemy->is_character() || !query("can_speak", enemy)) {
                write (NOR "你没法和" + enemy->name() + NOR "签订茶宠契约。" NOR);
                return 1;
        }
        if (query_temp("is_qkfz", enemy)) {
                write (NOR + enemy->name() + NOR "已经签订过茶宠契约。" NOR);
                return 1;
        }       
        if (playerp(enemy) && !query_temp("in_pkd", enemy)) {
                write (NOR + "只有在屠人场才能逼玩家约。" NOR);
                return 1;
        }       
        message_vision(NOR YEL "$N" NOR YEL  "扬手祭出一张" + name() + NOR YEL "飘过去，正好“pia ~”地贴在$n" NOR YEL  "的额头上。\n" NOR, me, enemy);
        if (do_start_bet(me, enemy, 0)) {
                message_vision(NOR YEL "$N" NOR YEL  "抽走了$n" NOR YEL  "的一魂二魄。\n" NOR, me, enemy);
                set_temp("is_qkfz", 1, enemy);
                chong = new("/u/redl/teleport/npc/chachong");
                chong->do_copy(enemy, me, i);
                destruct(chong);
                enemy->die(me);
        }
        else {
                message_vision(NOR YEL "$N" NOR YEL  "想约$n" NOR YEL  "已然失败。\n" NOR, me, enemy);
                if (query_temp("flag_bet")) {
                        set_temp("die_reason", NOR + "想约"+enemy->name()+"失败而亡" + NOR, me);
                        me->die(enemy);//平局算发起人死亡
                }
        }
        destruct(this_object());
        //write("ok\n");
        return 1; 
}


void init()
{
        object me = this_player();
        if (playerp(me)) {
                add_action("do_use", "use");
        }
}


