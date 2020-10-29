// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

#define BONUS_IMPROVE_SKILL 6
#define BONUS_POT 65
#define T_INTERVAL 180  //连续不停24小时的静修，和允许baby静修是本意
#define MAX_DRUG 60000000

void create()
{
        set("short", "静修室");
        set("long", 
"这里是整个洞天唯一能全面修炼的地方，整个房间建立在一块先天冰魄\n"
"之上，刚刚靠近一些就感觉到连元神都能冻结的寒冷。据说这种奇物有助于\n"
"凝神静修("CYN"jx"NOR")。\n"
);
                //set("outdoors", "dongtian");
                set("exits",([ /* sizeof() == 1 */
                        "east" : __DIR__"zoulang14",
                ]));

        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_drift", 1);
        set("no_sleep_room", 1); 
        set("max_carry_user", 2);
        set("max_carry_exit", "go east");
        //set("owner_level", 1); 允许被外来者袭杀
        
        setup();
}

int halt_jingxiu(object me)
{
        write(NOR "你停止了静修。\n" NOR);
        me->set_short_desc(0);
        return 1;
}

int jingxiuing(object me)
{
        int i, isk, mylevel, kar, radd, rnd = 360;
        string spsk, sks, *bls, *basicskills = ({});
        int zhenbouns;

        if (environment(me)!=this_object()) {
                //tell_object(me, CYN "你跑到哪里去了？\n\n" + NOR);
                me->set_short_desc(0);
                me->command("halt");
                return 1;
        }
        
        if (me->is_fighting()) {
                tell_object(me, CYN "你被战斗打断了修炼。\n\n" + NOR);
                me->command("halt");
                return 1;
        }
        
        if (playerp(me) && (query("food", me) < 20 || query("water", me) < 20)) {
                tell_object(me, CYN "你突然觉得很饥渴，又不会辟谷干脆停止了修炼。\n\n" + NOR);
                me->command("halt");
                return 1;
        }

        mylevel = query("level",me);
        if (mylevel < 10) mylevel = 10;
        if (mylevel > 200) mylevel = 200;
        mylevel += random(mylevel / 10) * (random(2) ? 1 : -1);
        kar = me->query_kar();
        rnd -= kar;
        if (rnd < 260) rnd = 260;
        rnd = random(rnd);
        zhenbouns = (query("zhen_type") + 11) / 8;

        if (rnd < 5) {
                radd = BONUS_IMPROVE_SKILL * ((mylevel + kar * (random(2) + 3) / 9) * (zhenbouns));
                radd += random(radd / 10) * (random(2) ? 1 : -1);
                bls = ({"blade","sword","staff","whip","throwing","dagger","hammer"});
                foreach (sks in bls) {
                        if ( (me->query_skillo(sks, 1))>179 && (me->query_skill_mapped(sks)) && (me->query_skillo(me->query_skill_mapped(sks), 1))>179 ) {
                                basicskills += ({sks});
                        }
                }
                tell_object(me, NOR + HIC + "你潜心修炼兵器技能... \n" + NOR);
                if (basicskills && arrayp(basicskills) && sizeof(basicskills)) {
                        sks = basicskills[random(sizeof(basicskills))];
                        isk = me->query_skillo(sks, 1);
                        isk /= 50;
                        isk += 1;
                        if (isk > 20) isk = 20;
                        radd *= isk;    
                        tell_object(me, NOR + CYN + "你潜心修炼「" + NOR + HIC + to_chinese(sks) + NOR + CYN + "」.. " + HIK + "( +" + (string)radd + " )\n" + NOR);
                        me->improve_skill(sks, radd );
                        sks = me->query_skill_mapped(sks);
                        radd /= 2;
                        tell_object(me, NOR + CYN + "你潜心修炼「" + NOR + HIC + to_chinese(sks) + NOR + CYN + "」.. " + HIK + "( +" + (string)radd + " )\n" + NOR);
                        me->improve_skill(sks, radd);
                } else {
                        tell_object(me, NOR + CYN + "然而你什么也不会，或者没有激发和低于１８０级。 \n" + NOR);
                }
        }
        else if ( rnd < 12 && random(MAX_DRUG) > query("drug_addneili", me) ) {
                radd = random(kar / 3) + 10 + kar / 5 + zhenbouns * 2;
                addn("drug_addneili", radd, me);
                tell_object(me, HIY "你的内力上限额外提高了" + BLINK + HIG + chinese_number(radd) + NOR + HIY + "点。 " + NOR + HIK + "( =" + (string)query("drug_addneili", me) + " )\n" + NOR);
                if (!query("drug_addneili_chat", me)) set("drug_addneili_chat", 50000, me);
                if (query("drug_addneili_chat", me) < query("drug_addneili", me)) {
                        CHANNEL_D->channel_broadcast("dt", NOR + WHT + "据说" + me->name() + NOR + WHT + "在洞天仙府修炼内力，额外上限超过了" + NOR + HIY + chinese_number(query("drug_addneili_chat", me)/10000) + NOR + WHT + "万。\n" + NOR);
                        set("drug_addneili_chat", query("drug_addneili_chat", me) * 2, me);
                }
                
        }
        else if ( rnd < 19 && random(MAX_DRUG / 2) > query("drug_addjingli", me) ) {
                
                radd = random(kar / 3) + 5 + kar / 6 + zhenbouns;
                addn("drug_addjingli", radd, me);
                tell_object(me, HIY "你的精力上限额外提高了" + BLINK + HIG + chinese_number(radd) + NOR + HIY + "点。 " + NOR + HIK + "( =" + (string)query("drug_addjingli", me) + " )\n" + NOR);
                if (!query("drug_addjingli_chat", me)) set("drug_addjingli_chat", 50000, me);
                if (query("drug_addjingli_chat", me) < query("drug_addjingli", me)) {
                        CHANNEL_D->channel_broadcast("dt", NOR + WHT + "据说" + me->name() + NOR + WHT + "在洞天仙府修炼精力，额外上限超过了" + NOR + HIY + chinese_number(query("drug_addjingli_chat", me)/10000) + NOR + WHT + "万。\n" + NOR);
                        set("drug_addjingli_chat", query("drug_addjingli_chat", me) * 2, me);
                }
                
        }
        else if (rnd < 50) {
                radd = BONUS_IMPROVE_SKILL * ((mylevel + kar * (random(2) + 3) / 9) * (zhenbouns));
                radd += random(radd / 10) * (random(2) ? 1 : -1);
                bls = ({"unarmed","cuff","hand","claw","strike","finger"});
                foreach (sks in bls) {
                        if ( (me->query_skillo(sks, 1))>179 && (me->query_skill_mapped(sks)) && (me->query_skillo(me->query_skill_mapped(sks), 1))>179 ) {
                                basicskills += ({sks});
                        }
                }
                tell_object(me, NOR + HIC + "你潜心修炼空手技能... \n" + NOR);
                if (basicskills && arrayp(basicskills) && sizeof(basicskills)) {
                        sks = basicskills[random(sizeof(basicskills))];
                        isk = me->query_skillo(sks, 1);
                        isk /= 50;
                        isk += 1;
                        if (isk > 20) isk = 20;
                        radd *= isk;    
                        tell_object(me, NOR + CYN + "你潜心修炼「" + NOR + HIC + to_chinese(sks) + NOR + CYN + "」.. " + HIK + "( +" + (string)radd + " )\n" + NOR);
                        me->improve_skill(sks, radd );
                        sks = me->query_skill_mapped(sks);
                        radd /= 2;
                        tell_object(me, NOR + CYN + "你潜心修炼「" + NOR + HIC + to_chinese(sks) + NOR + CYN + "」.. " + HIK + "( +" + (string)radd + " )\n" + NOR);
                        me->improve_skill(sks, radd);
                } else {
                        tell_object(me, NOR + CYN + "然而你什么也不会，或者没有激发和低于１８０级。 \n" + NOR);
                }
        }
        else if (rnd < 100) {
                radd = BONUS_IMPROVE_SKILL * ((mylevel + kar * (random(2) + 3) / 9) * (zhenbouns));
                radd += random(radd / 10) * (random(2) ? 1 : -1);
                bls = ({"dodge","force","parry"});
                foreach (sks in bls) {
                        if ( (me->query_skillo(sks, 1))>179 && (me->query_skill_mapped(sks)) && (me->query_skillo(me->query_skill_mapped(sks), 1))>179 ) {
                                basicskills += ({sks});
                        }
                }
                tell_object(me, NOR + HIC + "你修炼轻功内功招架... \n" + NOR);
                if (basicskills && arrayp(basicskills) && sizeof(basicskills)) {
                        sks = basicskills[random(sizeof(basicskills))];
                        isk = me->query_skillo(sks, 1);
                        isk /= 50;
                        isk += 1;
                        if (isk > 20) isk = 20;
                        radd *= isk;    
                        tell_object(me, NOR + CYN + "你潜心修炼「" + NOR + HIC + to_chinese(sks) + NOR + CYN + "」.. " + HIK + "( +" + (string)radd + " )\n" + NOR);
                        me->improve_skill(sks, radd );
                        sks = me->query_skill_mapped(sks);
                        radd /= 2;
                        tell_object(me, NOR + CYN + "你潜心修炼「" + NOR + HIC + to_chinese(sks) + NOR + CYN + "」.. " + HIK + "( +" + (string)radd + " )\n" + NOR);
                        me->improve_skill(sks, radd);
                } else {
                        tell_object(me, NOR + CYN + "然而你什么也不会，或者没有激发和低于１８０级。 \n" + NOR);
                }
        }
        else if (rnd < 160) {
                radd = BONUS_POT;
                radd += BONUS_POT * (mylevel / 100);
                radd += random(BONUS_POT * (kar / 5) /2) + BONUS_POT * (kar / 5) /2;
                radd = radd * zhenbouns ;
                radd += random(radd / 10) * (random(2) ? 1 : -1);
                call_other(GIFT_D, "bonus", me, ([      "exp": (mylevel > 49 ? 1 : (radd * 4 / (mylevel/5))), 
                                                                                        "pot":radd , 
                                                                                        "mar":radd / 8, 
                                                                                        "prompt":"你在静修时"]));
        }
        
        if (!random(5)) addn("food", -1, me);
        if (!random(5)) addn("water", -1, me);
        
        return 1;
}

int do_jingxiu()
{
        object me = this_player();
        
        if (me->is_busy() || me->is_fighting())
                return notify_fail(NOR "你还是忙完手头上的事情再说吧。\n" NOR);

        me->start_busy(2);
        
        if (playerp(me)) {
        
        if ((query("food", me) < 50 || query("water", me) < 50)) 
                return notify_fail(NOR "你最好吃饱喝足了再来静修。\n" NOR);

        if (query("dongtian/jingxiu/start_time", me) > time() && wiz_level(me) < 5)
                return notify_fail(NOR "你多运动运动吧，频繁地静修没有好处。\n" NOR);

        if (wiz_level(me) == 1)
                return notify_fail(NOR "你是新手导师，别来趟浑水。\n" NOR);
                
        }       
        //if (!playerp(me))
//              return 0;

    me->start_busy((: call_other, __FILE__, "jingxiuing" :),
                       (: call_other, __FILE__, "halt_jingxiu" :));
        
        me->set_short_desc("正在静心修炼。");
        write(NOR "你开始静心修炼。<halt>\n" NOR);
        set("dongtian/jingxiu/start_time", time() + T_INTERVAL, me);
        return 1;
}

void init()
{
        object me = this_player();
        //me->start_busy(3);
        set("zhen_type", query("zhen_type", get_object(__DIR__"guangchang")));
        set("max_carry_user", 2 + query("zhen_type") / 2);
        if ((playerp(me) && interactive(me)) || me->is_baby()) add_action("do_jingxiu", ({"jingxiu", "jx"})); 
        
        ::init();
}




