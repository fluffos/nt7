// This program is a part of NITAN MudLIB 
// redl 2012/12/1 
// 攻击型
#include <ansi.h>
#include <transmsg.h>

#define CHANL_NAME "news"

#define BONUS_INTERVAL 8        //每间隔几层获得一次奖励机会
#define TIME_KICK 90            //每层过关的基础战斗时间
#define CAN_USEKNIFE 3          //限制每轮闯关可以使用飞刀灵符的次数
#define CAN_USECRYSTAL 3        //限制每轮闯关可以使用塔灵水晶的次数，每块延长30秒，使用后的所有层都有效
#define BONUS_EXPADD 2100       
#define BONUS_EXPADD_J 180

inherit ROOM;

#define TOWERNAME "正"
int tower_type() { return 1;}

int clean_up() { return 1;}

void pass(object me);

object objboss;

void remove_no_fight()
{
        delete("no_fight");
}

void fullnow(object me)
{
    mapping my;
    object boss;

        me->remove_call_out("revive");
        me->remove_call_out("unconcious");
        remove_call_out("remove_no_fight");

        me->remove_all_enemy(1);
        //boss = query("boss", find_object(__DIR__"lgtd"));
        //if (objectp(boss)) boss->remove_all_enemy(1);
        set("no_fight", "1"); 

        my = me->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"]; 
        my["jingli"] = my["eff_jingli"] = my["max_jingli"]; 
        my["qi"]     = my["eff_qi"]     = my["max_qi"]; 
        my["neili"]  = my["max_neili"];
        me->clear_condition();
        me->stop_busy();
        me->clear_weak();
        me->full_self();

        if( query_temp("block_msg/all", me) ) {
                        tell_object(me, HIR "你终于抹掉了眼前的鲜血，能看见了。\n" NOR);
                        delete_temp("block_msg/all", me);
        }

        call_out("remove_no_fight", 2);
}

int kickdown2(object me)
{
        object boss;//yang, ding,
        int ngold;
        
        fullnow(me);
        remove_call_out("kickdown");
//        boss = query("boss", find_object(__DIR__"lgtd"));
                boss = objboss;
        
        if (query("lgt/can_die", me) > 0) {
                tell_object(me, YEL + "你情急之下大喝一声掏出一张灵符扔了出去...\n" + NOR);
                tell_object(me, HIY + query("short") + HIY + "轰得一震，空气复散清明。\n" + NOR);
                addn("lgt/can_die", -1, me);
                if (query("lgt/can_die", me) > 0) 
                        tell_object(me, YEL + "你怔怔地望着剩余的" + HIG + chinese_number(query("lgt/can_die", me)) + "张灵符" + NOR + YEL + "，大口喘息着，不知道该不该继续......\n" + NOR);
                set("entertime", time());
                call_out("kickdown", 10, me);
                if (!objboss || !objectp(objboss)) pass(me);
                return 1;
        }

        tell_object(me, YEL + "你大喝一声五官齐齐"+HIR+"溢血"+NOR+YEL+"，扑到窗户边挣扎着，一头从塔上栽了下去...\n" + NOR);

                if (objectp(boss)) {
                                CHANNEL_D->channel_broadcast(CHANL_NAME, 
                                        NOR + query("name", me) + NOR + "被" + query("short") + NOR + "的"+ query("title", boss) + NOR + "击败了！\n" + NOR
                                        );
                }
        
        me->move(__DIR__"lgtd");
        
        ngold = find_object(__DIR__"lgtd")->pay_gold(me);//愿赌服输

        message_vision(YEL + "突然只见" +HIC+query("short")+ NOR + YEL+"的窗户里弹出一个黑影，迅速由小变大..\n然后“噗通”一声栽落在地上。原来是$N"+ NOR + YEL+"，半死不活的好可怜啊……\n" NOR, me);
        delete_temp("lgt", me);

        //独占式的任务，必须扯眼球突出，激发人气和欲望
        CHANNEL_D->channel_broadcast("news", HIC + "杨小邪(yang xiaoxie)突然以非常机车的姿势非常机车的对著" + HIC + query("name", me) + HIC + "(" + HIC + query("id", me) + HIC + ")" + HIC + "大声笑著『哇哈哈 ~~~』。\n" + NOR);
        CHANNEL_D->channel_broadcast("news", HIC + "小丁(xiao ding)掩著嘴吃吃地对" + HIC + query("name", me) + HIC + "(" + HIC + query("id", me) + HIC + ")" + HIC + "笑著。\n" + NOR);
        CHANNEL_D->channel_broadcast("news", HIC + "杨小邪(yang xiaoxie)对小丁(xiao ding)得意的作出胜利的手势！！ 「 V 」 说：「 " + HIC + chinese_number(ngold) + HIC + "两黄金...」\n" + NOR);
        CHANNEL_D->channel_broadcast("news", HIC + "小丁(xiao ding)在杨小邪(yang xiaoxie)的额头上轻轻地吻了一下... \n" + NOR);
        
        if (objboss && objectp(objboss)) destruct(objboss); 
        return 1;
}


void do_beepobj(object obj)
{
        if (! obj) return; 
        tell_object(obj, "\a", 0);
}

void kickdown(object me)
{
        int i, j;
        if (!this_object() || !me) return;
        if (environment(me) != this_object()) return;
        
        if (!query_temp("lgt/knock2", me)) {
                i = (query("no_magic")) ? (TIME_KICK+query_temp("lgt/tlcrystal", me)*30) : 30;
                j = time() - query("entertime");
                if (j > i ) {
                                if (objboss && objectp(objboss) && objectp(environment(objboss))) {
                                        tell_object(me, CYN + query("name", objboss) + NOR + CYN + "重重地" + ((random(2)) ? "对你哼了一声" : "往地上啐了一口") + "，" 
                                                + ((random(2)) ? "转身" : "闪身") + ((random(2)) ? "一跃" : "一跳") + "消失了。\n" + NOR); 
                                                objboss->die(me);
                                } else {
                                //pass(me);
                                tell_object(me, CYN + "一个空洞的声音在你耳边响起：" + HIR + "你在磨蹭什么？！\n" + NOR);
                                kickdown2(me);
                        }
                        return;
                } else if ( j > to_int(i * 0.9) ) {
                         write(YEL + "你听到无数天魔在耳边吟唱嘶吼，莫大的压力使你开始神智迷糊了...\n" + NOR);
                        if (query("lgt/beep", me)) {
                                do_beepobj(me);
                                call_out("do_beepobj", 1, me);
                        }
                } else if ( j > to_int(i * 0.8) ) {
                        write(YEL + "佛塔内的景色开始慢慢扭曲，像水波纹一样不停变幻...\n" + NOR);
                        if (query("lgt/beep", me)) {
                                do_beepobj(me);
                                call_out("do_beepobj", 1, me);
                        }
                } else if ( j > to_int(i * 0.5) ) {
                        write(YEL + "佛塔内的空气渐渐变得稀薄起来...\n" + NOR);
                        if (query("lgt/beep", me)) do_beepobj(me);
                }
        }
        //write ("test time:" + ctime(time()) + "\n");
        call_out("kickdown", 2, me);
        return;
}

string look_zhong(object me)
{
    return "这是一个可以敲(knock)响的黄铜古钟(zhong)。\n如果有礼佛的诚意的话，你应该会有一些收获的吧。\n";
}

int user_cant_die(object me)
{
                if (!playerp(me)) {
                //destruct(me); 
                return 0;
        }
        if (userp(me)) {
                tell_object(me, CYN + "一个空洞的声音在你耳边响起：" + HIR + "你被杀死一次！\n" + NOR);
                fullnow(me);
                kickdown2(me);
        }
        return 1;
}

int user_cant_unconcious(object me)
{
                if (!playerp(me)) {
                //destruct(me); 
                return 0;
        }
        if (userp(me)) {
                tell_object(me, CYN + "一个空洞的声音在你耳边响起：" + HIR + "你被击晕一次！\n" + NOR);
                fullnow(me);
                user_cant_die(me);
        }
        return 1;
}



void create()
{
        set("short", "灵感" + TOWERNAME + "塔.第二层");
        set("long",
"这里是灵感塔内，四周宏伟的壁砖上刻绘着许多地狱魔神样的图腾。\n"
"无量的金黄色佛经文字悬浮在空中，映射出炫目的光芒，似乎镇压着这里\n"
"自成一界。\n"
"    中央是一座巨大的佛像，佛像前的香桌上倒置放着一个"+CYN+"铜钟"+NOR+"。\n"
);

        set("item_desc", ([
                "钟": (: look_zhong :),
                "铜钟": (: look_zhong :),
                "zhong": (: look_zhong :),
        ]) );
        set("exits", ([
                "up"   : __FILE__,
        ]));
        set("tlv", 2);
                set("no_protect", 1); //断线不能消除战斗
                set("no_rideto", 1);
                set("no_flyto", 1);
                set("no_fly", 1);//禁止招马，否则有bug
                set("no_sleep_room", 1); //禁止睡觉，bug
                set("no_magic", 1); 
                                set("trans_msg_to", "/u/redl/teleport/tower");
        setup();
}

void do_beep()
{
        object me = this_player();
        if (!query("lgt/beep", me)) {
                set("lgt/beep", 1, me);
                tell_object(me, HIC + "你打开了塔灵的超时报警功能！\n" + NOR);
        } else {
                delete("lgt/beep", me);
                tell_object(me, HIC + "你关闭了塔灵的超时报警功能！\n" + NOR);
        }
}

int do_passnext()//切换对手
{
        object me, obb;
        me = this_player();
        
        if(me->is_fighting()) return notify_fail("你还是先解决目前的敌人吧！\n");
        if(me->is_busy()) return notify_fail("你正忙着，没空使用灵符。\n");
        if (query("no_magic"))  return notify_fail("你先想办法通过这一层再说吧。\n");
        if (objectp(present("qiu tu", this_object())))  return notify_fail("你先想办法通过这一层再说吧。\n");
        if (objectp(present("wu chi", this_object())))  return notify_fail("你先想办法通过这一层再说吧。\n");
        
                if (query("lgt/can_die", me) > 0) {
                            if (!random(3)) {
                                tell_object(me, NOR "你损失一张飞刀灵符。\n" NOR);
                                addn("lgt/can_die", -1, me); 
                            }
                        me->start_busy(999);//等待pass2()的stop_busy
                        tell_object(me, CYN + "你拈起一张灵符一晃，符纸无风自燃。\n符纸突然化作一片透明的" + YEL + "飞刀" + CYN + "，往楼上一窜一闪，消失了...\n楼上传来“啊”的一声惨叫......" + NOR); //故意不\n的 
                        remove_call_out("kickdown");
                                                call_out("pass2", 2, me);
                } else
                        return notify_fail("你没有灵符可用了！\n");
                        
        return 1;
}


void pass2(object me)
{
        object boss, *inv;
        
        if (!me || !objectp(me)) {
                inv = all_inventory(this_object());
                if( sizeof(inv) > 0 ) {
                    foreach( object ob3 in inv ) {
                                if( playerp(ob3) ) {
                                        me = ob3;
                                        break;
                                }
                        }
                }
        }
        
        tell_object(me, HIY + query("short") + HIY + "轰得一震，空气复散清明。\n" + NOR);
        
        remove_call_out("pass2");
        remove_call_out("kickdown");
        set("entertime", time());
        call_out("kickdown", 10, me);

        remove_call_out("remove_no_fight");
        me->remove_all_enemy(1);
        set("no_fight", "1");
        call_out("remove_no_fight", 1);

        //让玩家可以驱毒疗伤思考切换什么武功去战斗等等
        delete("no_magic");
        boss = new(__DIR__"npc/boss");
        boss->setlv(query("tlv")+1,-1,-1);
        tell_object(me, HIG + "杨小邪(yang xiaoxie)偷偷告诉你：" + query("wmsg", boss) + NOR);
        tell_object(me, NOR + "(你还有" + query("lgt/can_die", me) + "张灵符)\n" + NOR);
        objboss = boss;
        set("objboss", boss);

        me->stop_busy();
        me->start_busy(2);//留时间强制让玩家看清楚提示！
}

void pass(object me)//通关，准备下一轮
{
        me->start_busy(3+random(2));
        me->remove_all_enemy(1);
        remove_call_out("kickdown");
        set("entertime", time());
        remove_call_out("pass2");
        call_out("pass2", 2, me);
}

      
void init() 
{ 
        int nbonus;
        object me, boss;
        me = this_player();
        
                if (!playerp(me))
                {
                        return;
                }
        
        if (query("env/invisible", me)) 
        {
                return;
        }
        
        set("trans_msg_id", query("id", me));
        
                        if (random(2))
                        {
                        me->start_busy(2+random(2));//防止玩家用 do u,19 pfm抢招
                }
                
                set("no_magic", 1); 
                remove_call_out("kickdown");
                set("entertime", time());
                call_out("kickdown", 10, me);
                delete("no_fight");//防止no_fight被利用
        
        if (query("tlv") < 3) {
                if (!query("lgt/upd", me)) {
                        set("lgt/upd", 1, me);
                        tell_object(me, CYN + 
"一个空洞的声音在你耳边响起...\n" + 
"    这位" + RANK_D->query_respect(me) + "，我是塔灵，刚才你上来之前，杨小邪给了你几张鬼画符是吧？\n" +
"    其实那是他的飞刀，这小子是有些鬼门道和手段，所以至今唯有那小子曾经登顶过我头上的全部九百九十九层灵感塔。\n" + 
"    这杨小邪除了恶作剧一些，其实心地不坏。你如果听到他提供的情报，告诉你对手的实力后，根据你自己的情况，\n" + 
"  该选择(pass)的，就(pass)，千万别逞强。如果觉得有把握，就直接上去战斗吧！\n" + 
"    如果看到塔内的空气开始稀薄，甚至扭曲，你得当心了，超时也算失败的。目前每层的战斗时间限制在" + chinese_number(TIME_KICK) + "秒内完成！\n" + 
"    我现在已经帮你打开了超时的声音报警，你可以使用(beep)来关闭它，再次使用则可以打开它。\n" +
"    最后一点，你在脱离战斗后，觉得没有把握继续下去。选择敲钟，拜祭完大佛后，方算挑战完成。如果失败掉下塔去。是会被那小子黑钱的。\n" + 
HIY + "\n9秒后开始计时……" 
                        + NOR); 
                        set("lgt/beep", 1, me);
                        me->start_busy(999);//等待pass2()的stop_busy
                        call_out("pass", 9, me);
                } else 
                        pass(me);
        } else {
                boss = objboss;
                if (!objectp(boss)) {
                        boss = query("objboss");
                        objboss = query("objboss");
                }
                if (objectp(boss)) {
                        tell_object(me, CYN + "你眼神凝滞处，一个黑影闪出挡在你的面前！\n" + NOR); 
                        boss->move(this_object());
                        if (query("tlv")>=30 && (query("tlv") % 10 == 0 || !random( (1000 - query("tlv")) / 50 ))) {
                                //30层后, 每到10字层绝对给个武痴，或者几率的机会任意层给个武痴. 150lv=1/17, 300lv=1/14, 600lv=1/8, 900lv=1/2
                                tell_object(me, CYN + "在一阵狂笑声里，楼梯口旋风般地跳下来个老头，后发先至跑到你跟前！\n" + NOR); 
                                if (!random(20)) {//5%缩回
                                        tell_object(me, CYN + "你正大吃一惊，却见老头连连冲你摆手，嘴里“哈哈哈...” 的跑上塔去了。\n" + NOR); 
                                } else {
                                        new(__DIR__"npc/wuchi")->move(this_object());
                                }
                        }
                }
        }

        if (query("tlv")>=10 && query("tlv") % 25 ==0) {//每10层给予奖励
                nbonus = to_int(query("tlv") * 20);//聊以自慰，主要是打广告说明有人在活动中，引起关注
                addn("weiwang", nbonus, me);
                if (query("family", me)) addn("family/gongji", nbonus/10, me);
                                CHANNEL_D->channel_broadcast(CHANL_NAME, 
                        HIG + "听说" + query("name", me) + HIG + "登上" + HIC + query("short")  + HIG +  "，江湖威望上升" + chinese_number(nbonus) + "点" + ((!query("family", me)) ? "" : "，师门奖励功绩" + chinese_number(nbonus/10) + "点") + "！\n" + NOR
                );
        }

        remove_action("do_knock", "knock");
        remove_action("do_passnext", "pass");
        remove_action("do_beep", "beep");
        remove_action("do_use", "use");
        add_action("do_knock", "knock");
        add_action("do_passnext", "pass");
        add_action("do_beep", "beep");
        add_action("do_use", "use");
} 



int do_use(string arg)
{
        object me, obb;
        me = this_player();

        if(!arg) return notify_fail("你到底想用什么？\n");
        if(me->is_fighting()) return notify_fail("你还是先解决目前的敌人吧！\n");
        if(me->is_busy()) return notify_fail("你正忙着，没空使用物品。\n");
        
        if(arg == "knife" || arg == "fly knife" || arg == "fei dao") {
                obb = present("fly knife", me);
                        if (!objectp(obb)) return notify_fail("你身上已经没有灵符可用了。\n");        
                        if (base_name(obb) != "/d/kaifeng/linggt/npc/obj/feidao") return notify_fail("你身上已经没有灵符可用了。\n");
                if(query_temp("lgt/knife", me) >= CAN_USEKNIFE) return notify_fail(NOR + "你本轮闯关已经使用过"+chinese_number(CAN_USEKNIFE)+"次"+query("name", obb)+ NOR + "了。\n");
                        if (obb->query_amount() > 0) obb->add_amount(-1);
                        addn_temp("lgt/knife", 1, me);
                        addn("lgt/can_die", 1, me);
                        tell_object(me, CYN + "你从身上拿出一张" + query("name", obb) + NOR + CYN + "夹在手指间...\n" + NOR); 
                        tell_object(me, NOR + "(你还有" + query("lgt/can_die", me) + "张灵符)\n" + NOR);
                return 1;
        } else if(arg == "crystal" || arg == "tower crystal" || arg == "tower") {
                obb = present("tower crystal", me);
                        if (!objectp(obb)) return notify_fail("你身上已经没有塔灵水晶可用了。\n");        
                        if (base_name(obb) != "/d/kaifeng/linggt/npc/obj/tlcrystal") return notify_fail("你身上已经没有塔灵水晶可用了。\n");
                if(query_temp("lgt/tlcrystal", me) >= CAN_USECRYSTAL) return notify_fail(NOR + "你本轮闯关已经使用过"+chinese_number(CAN_USECRYSTAL)+"次"+query("name", obb)+ NOR + "了。\n");
                        if (obb->query_amount() > 0) obb->add_amount(-1);
                        addn_temp("lgt/tlcrystal", 1, me);
                        tell_object(me, CYN + "你拿出一块" + query("name", obb) + NOR + CYN + "捏成粉碎，梦幻泡影般的紫青迷雾挥发，时间流逝变慢了...\n" + NOR); 
                return 1;
        }
        
        return notify_fail("你到底想用什么？\n");
}

int do_knock(string arg)
{
        object me, obb;
//        int i, blv;
        me = this_player();
        
        if(me->is_fighting()) return notify_fail("你还是先解决目前的敌人吧！\n");
        if(me->is_busy()) return notify_fail("你正忙着，没空敲钟。\n");
        if(!arg) return notify_fail("你到底想要敲什么？\n");
        if(arg != "zhong") return notify_fail("你到底想要敲什么？\n");
        if (query_temp("lgt/knock2", me)) return notify_fail("你已经在敲钟念佛了！\n");
        if (query("tlv") < 3) return notify_fail("你至少也要往上爬一层啊，这么胆怯？！\n");

        //50%几率未杀不可敲
        if ((random(2)) && objectp(present("qiu tu", this_object())))
        {
                tell_object(me, NOR + query("title", objboss) + NOR + YEL "大急，扑过来和你抢夺铜钟...\n" + NOR); 
                objboss->kill_ob(me);
                return notify_fail("你还是先解决目前的敌人吧！\n");
        }        
                
                me->start_busy(2);
                remove_call_out("knock2");
        
        set_temp("lgt/knock2", 1, me);
        call_out("knock2", 1, me, 1, query("tlv"));
        
                fullnow(me);
        return 1;
}

int get_show_giftexp(object me, int exp)//在news频道用来显示的经验奖励值
{
        int quest_times;
        if (MEMBER_D->is_double_reward(me)) exp *= 2;
        quest_times = "/adm/daemons/actiond"->query_action("quest_reward");
        if (quest_times) exp *= quest_times;
        if( me->query_bunch() && BUNCH_D->query_bunch_efficient(me->query_bunch(), "exp") ) exp *= 2;        
        else if( me->query_family() && FAMILY_D->query_family_efficient(me->query_family(), "exp") ) exp *= 2;
        return exp;
}

int knock_end(object me)
{
        int i, j, k = 50;
        int pot, mar, yuanshen_level, yuanshen_exp;
        string msg;
        //通告全服，回到塔底
        if (query("tlv")>=10) find_object(__DIR__"lgtd")->log_hero(me, query("tlv"));//十层以上才能当地主
        message_vision(YEL + "天空上传来一声长啸……\n只见$N"+YEL+"潇洒地从"+HIC+query("short")+ NOR + YEL+"的窗户闪电般射出，\n凌空几个后空翻，再连接两个拉拉提难度系数1080，稳稳飘飞落到地上。\n" NOR, me);
        i = query("tlv");
        set("lgt/upd", i, me);//最后一次的成功层数
                j = BONUS_EXPADD_J;
                while (k < 1000) {
                        if (i>k) {
                                j -= 4;
                        }
                        k += 50;
                }
        i *= j;
        i *= BONUS_EXPADD;
        i += (query("lgt/texp", me)/8);
        if (i<500000) i = 500000;//新人每天可以来领50w
        
#ifdef DB_SAVE
        if (MEMBER_D->is_double_reward(me)) 
                i *= 2;
#endif

                set("lgt/bonus/exp_lastjump", i, me);
                addn("lgt/bonus/exp_lastjump_count", i, me);

        //甩开各种双倍奖励，特别是帮会双
        pot = i / 3;
        mar = i / 6;
        addn("potential", pot, me);
        addn("experience", mar, me);
        // 元神
        if( i > 100 && (yuanshen_level = query("yuanshen_level", me)) && yuanshen_level < 100 )
        {
                if( yuanshen_level > 40 ) yuanshen_exp = i * 25 / 100;
                else if( yuanshen_level > 30 ) yuanshen_exp = i * 20 / 100;
                else if( yuanshen_level > 20 ) yuanshen_exp = i * 15 / 100;
                else if( yuanshen_level > 10 ) yuanshen_exp = i * 10 / 100;
                else yuanshen_exp = i * 5 / 100;
                addn("yuanshen_exp", yuanshen_exp, me);
                i -= yuanshen_exp;
        }
        addn("combat_exp", i, me);
        
                msg = HIG + "你在灵感" + TOWERNAME + "塔上成功敲钟之后，你获得了";
        if (i > 0) msg += chinese_number(i) + "点经验、";
        if (pot > 0) msg += chinese_number(pot) + "点潜能、";
        if (mar > 0) msg += chinese_number(mar) + "点实战体会、";
        if( yuanshen_exp ) msg += "元神获得经验" + chinese_number(yuanshen_exp) + "点、";
        msg += "能力得到了提升。\n" + NOR;
        tell_object(me, sort_msg(msg));
        
        /*
        if (query("reborn/times", me)) i *= 2;//如果有转世，抵消转世的奖励惩罚
        call_other(GIFT_D, "bonus", me, ([ "exp":i, "pot":i/4, "mar":i/8, "prompt":"你在灵感塔上成功敲钟之后"]));
        if (query("reborn/times", me)) i /= 2;//如果有转世，抵消转世的奖励惩罚
        i = get_show_giftexp(me, i);//计算活动额外
        i += query("lgt/texp", me);
        */
        if (query("tlv")>=100) CHANNEL_D->channel_broadcast("news",
                                        HIC + "杨小邪(yang xiaoxie)双拳一抱，高声对" + HIC + me->query_idname() + HIC + "说道：“恭喜！恭喜！\n"+
                                        //"        听说您到"HIC + query("short") + HIC + "累计获得了" + HIC + chinese_number(i) + HIC + "点经验，小邪在此恭喜你了！” \n" + NOR
                                        "        听说您到"HIC + query("short") + HIC + "，小邪在此恭喜你了！” \n" + NOR
                                        );
        delete_temp("lgt", me);
        if (objboss && objectp(objboss)) destruct(objboss); 
        me->move(__DIR__"lgtd");
        return 1;
}


int knock2(object me, int i, int imax)
{
        object obb;
        int blv;
        string unit;
        
        me->start_busy(2);
        if (imax < 10 || i > imax) return knock_end(me);
        
        tell_object(me,YEL"你埋首合什虔诚地向大佛祷告......\n"NOR); 

                blv = random(10000);
                if (blv < 1) obb = new("/clone/goods/tianjing");                                                //寰宇天晶
                        else if (blv < 20) obb = new("/d/kaifeng/linggt/npc/obj/tlcrystal");               //塔灵水晶
                        else if (blv < 60) obb = new("/d/kaifeng/linggt/npc/obj/feidao");                  //飞刀灵符
                        else if (blv < 140) obb = new("/d/kaifeng/npc/obj/mashu");                                 //麻薯，拿给洗象池的沈芝毓换玉清丸
                        else if (blv < 300) obb = new("/clone/tongren/tongren2");                               //无名大铜人
                        else if (blv < 460) obb = new("/clone/tongren/tongren1");                               //无名小铜人
                        else if (blv < 780) obb = new("/clone/tessera/rune" + to_string(20 + random(5)));       //符文20-24
                        else if (blv < 1100) obb = new("/clone/tessera/rune" + to_string(15 + random(5)));      //符文15~19
                        else if (blv < 1740) obb = new("/clone/gift/jiuzhuan");                                 //九转金丹
                        else if (blv < 2380) obb = new("/clone/gift/tianxiang");                                        //天香玉露
                        else if (blv < 3660) obb = new("/clone/gift/puti-zi");                                  //菩提子
                        else if (blv < 6220) obb = new("/clone/money/yuanbao");                                 //金票=百两黄金
                        else obb = new("/clone/money/cash");                                                                    //银票=十两黄金
                        unit = query("base_unit", obb);
                        if (!unit) unit = query("unit", obb);
/*                        //故意如此加强登塔人的成就感，独占性任务不算刷屏!
                        CHANNEL_D->channel_broadcast(CHANL_NAME, query("name", me) + HIG + "在灵感" + TOWERNAME + "塔获得了一" + unit + query("name", obb)+ HIG + "的奖励！\n" + NOR);
                        */
                        tell_object(me,
                                query("name", me) + HIG + "在灵感" + TOWERNAME + "塔获得了一" + unit + query("name", obb)+ HIG + "的奖励！\n" + NOR
                                );
                        obb->move(me);
        i += BONUS_INTERVAL;
        call_out("knock2", 1, me, i, imax);
        return 1;
}


int valid_leave(object me, string dir)
{
        mapping ob; 
        object *obs;
        int tlv;
        
        //if (!wizardp(me)){
        //战斗不可逃
        if (me->is_fighting() || objectp(present("qiu tu", this_object())))
        {
                tell_object(me,NOR"你还是先解决目前的敌人吧！\n"NOR); 
                return 0;
        }
        
        tlv = query("tlv");
        
        if (tlv >= 1299) {
                tell_object(me,NOR"你无敌了，不用再上去了吧。\n"NOR); 
                return 0;
        }
        
        if ( objectp(query_temp("is_riding", me)) ) return notify_fail("你骑着马没法上灵感塔去！\n");
        
        if (query("no_magic"))  return notify_fail("你暂时还不能到上一层去！\n");
        
        if (playerp(me))
        {
                if (tlv < 3) {//电梯
                     //tlv = query("level", me) / 2 - 18;
                                                tlv = (query("level", me)<100) ? query("level", me) / 2 - 15 : query("level", me) * 2 / 3 + 5;//等级高了起点低,太慢
                                                if ( query("lgt/upd", me) && query("lgt/upd", me)>100 && (query("lgt/upd", me)-tlv)>99 ) tlv = query("lgt/upd", me) - 99;
                        if (tlv < 3)
                                tlv = 3;
                        else 
                                tell_object(me,YEL"你略一思忖，深吸口气纵身直接跃上了第" + chinese_number(tlv) + "层。\n"NOR); 
                } else {
                        tlv += 1;       
                }
                set("tlv", tlv);
        set("short", "灵感" + TOWERNAME + "塔.第" + chinese_number(tlv) + "层");
        //remove_action("do_passnext", "pass");
        }
        obs = all_inventory(); 
        if (sizeof(obs) > 0) 
        { 
                if (arrayp(query_temp("objects"))) 
                        obs -= query_temp("objects"); 
                //obs = filter_array(obs, (: ! living($1) && clonep($1) && ! $1->is_character() :)); 
                obs = filter_array(obs, (: (!$1->is_user()) && (!$1->is_worm2())  :)); //要驱逐宠物的帮助，只能留下玩家自己
                if (sizeof(obs) > 0) 
                { 
                        obs = obs[0..<1]; 
                        foreach (ob in obs) destruct(ob); 
                } 
        } 
        

        return ::valid_leave(me, dir);
}

