// rewrited by Lonely@nitan3

#include <ansi.h>
#include <room.h>
#include <command.h>

inherit ITEM;

mapping bingfa = ([
        "fenzhan"    : "奋战",
        "fendou"     : "奋斗",
        "fenxun"     : "奋迅",
        "qishe"      : "骑射",
        "benshe"     : "奔射",
        "feishe"     : "飞射",
        "tupo"       : "突破",
        "tujin"      : "突进",
        "tuji"       : "突击",
/*
        "crossbow" : ([ "qishe"      : "齐射",
                        "lianshe"    : "连射",
                        "liannu"     : "连弩",
                     ]),
                     
        "siegecity": ([ "jinglan"    : "井阑",
                        "chongche"   : "冲车",
                        "fashi"      : "发石",
                        "xiangbing"  : "象兵",
                        "luoshi"     : "落石",
                        "leimu"      : "擂木",
                        "shetai"     : "射台",
                        "jianchui"   : "尖锤",
                     ]),
        "ruse"     : ([ "hunluan"    : "混乱",
                        "xianjing"   : "陷阱",
                        "gongxin"    : "攻心",
                        "huanshu"    : "幻术",
                        "yingzao"    : "营造",
                        "poxian"     : "破陷",
                        "jiaoyu"     : "教谕",
                        "ruma"       : "辱骂",
                     ]),
        "resource" : ([ "guwu"       : "鼓舞",
                        "zhiliao"    : "治疗",
                        "yaoshu"     : "妖术",
                     ]),
*/                     
]);

mapping zhenfa = ([
        "putong"   : "普通阵",
        "yulin"    : "鱼鳞阵",
        "fengshi"  : "锋矢阵",
        "heyi"     : "鹤翼阵",
        "yanyue"   : "偃月阵",
        "fangyuan" : "方圆阵",
        "yanxing"  : "雁行阵",
        "changshe" : "长蛇阵",
        "yunlong"  : "云龙阵",
]);

void create()
{
        set_name(HIY "兵符" NOR, ({"bing fu", "fu"}));
        set_weight(10);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "枚");
                set("long",HIY"一枚大宋元帅调兵遣将的虎头兵符。\n"NOR);
                set("material", "copper");
                set("no_get", 1);
                set("no_steal", 1);
                set("no_put", 1);
                set("no_drop", 1);
                set("no_sell", 1);
                set("no_store", 1);
        }
        set("master", "高處不勝寒");
        set("owner", "lonely");
        setup();
}

void init()
{
        object me, ob;

        me = this_player();
        ob = this_object();

        if( query("id", me) == query("owner", ob) )
        {
                add_action("do_stock", ({ "stock", "gouzhi" }));
                add_action("do_move", ({ "move", "yidong" }));
                add_action("do_train", ({ "drill", "xunlian", "train" }));
                add_action("do_attack", ({ "assault", "gongji", "attack", "tuji" }));
                add_action("do_order",  ({ "order", "mingling" }));
                add_action("do_inquiry", ({ "inquiry", "chakan" }));
                // add_action("do_exert", ({ "exert", "yun", "touch" }));
                add_action("do_exert", ({ "touch" }));
                add_action("do_kill",
                        ({ "team kill", "array kill", "touxi", "kill",
                           "hit", "fight", "steal", "beg", "persuade",
                           "perform", "yong", "exert", "yun", "throw",
                           "ansuan", "conjure", "recall" }));        
        }
}

int do_kill(string arg)
{
        string what, who;

        if (! arg) return 0;

        if (this_object()->id(arg))
        {
                write("有没有搞错，那是军队耶，还不快跑？！\n");
                return 1;
        } else
        if ((sscanf(arg, "%s from %s",what, who) == 2 ||
             sscanf(arg, "%s at %s", what, who) == 2 ||
             sscanf(arg, "%s on %s", what, who) == 2 ||
             sscanf(arg, "%s %s", what, who) == 2) &&
             this_object()->id(who)) {
                write("有没有搞错，那是军队耶，还不快跑？！\n");
                return 1;
        } else
        if (arg == "roar" || arg == "hou")
        {
                write("有没有搞错，那是军队耶，还不快跑？！\n");
                return 1;
        }

        return 0;
}

void attack_over(object me)
{
        if (objectp(me))
        {
                message_vision(HIW "$N手中令旗一挥，三军攻势一缓，重新"
                        + "开始列阵，准备发起新一轮的攻击！！\n" NOR, me); 
                delete_temp("warquest/attack", me);
        }
        return;
}      

int do_attack(string arg)
{
        object me, ob;
        object env, room;
        string who, dir;
        string zhen, craft;

        me = this_player();
        env = environment(me);

        if (! arg) return notify_fail("你要指挥部队朝谁发起进攻？\n");

        // if (me->query("env/auto_contruel"))
        if( query("env/auto_war", me) )
                return notify_fail("你已经设置为由系统自动指挥作战！如想自己操作，请修改设置。\n");

        if( query_temp("warquest/attack", me) )
                return notify_fail("你的队伍正在列阵进攻，不要乱发号令了！\n");

        if( !query_temp("warquest/train", me) )
                return notify_fail("你未带一兵一卒，指挥个什么呀？\n");

        if( query_temp("warquest/group", me)<1 )
                return notify_fail("你的队伍已经损失殆尽，无法列阵冲锋了！\n");

        if( query("no_fight", env) )
                return notify_fail("这里不许战斗！！\n");

        if (sscanf(arg, "%s with %s & %s", who, zhen, craft, dir) < 3)
                return notify_fail("指令格式错误，请用 attack <sb.> with <array> & <craft> 指挥你的队伍！\n");

        if (! objectp(ob = present(who, env)))
                return notify_fail("无法找到目标，请用 attack <sb.> with <array> & <craft> 指挥你的队伍！\n");

        if( !query_temp("warquest", ob) || query_temp("warquest/party", ob) != "meng" )
                return notify_fail("你军务在身，还是不要轻易招惹是非的好！\n");

        if( !query("array/"+zhen, me) && zhen != "putong" )
                return notify_fail("你目前还没有通晓「" + zhenfa[zhen] + "」这种阵法！\n");

        if( !query("craft/infantry/"+craft, me) )
                return notify_fail("你目前还没有通晓「" + bingfa[craft] + "」这种兵法！\n");

        message_vision(HIY "$N将手中宝剑一挥，大喝道：三军列阵「" + zhenfa[zhen] +
                "」，准备向敌军发起冲锋——>" + bingfa[craft] + "！！\n" NOR, me, ob);

        set_temp("warquest/attack", 1, me);
        set_temp("warquest/array", zhenfa[zhen], me);
        // me->start_call_out((: call_other, WAR_D, "attack_over", me :), 10);
        call_out("attack_over", 10, me);    
        WAR_D->do_attack(me, ob, zhenfa[zhen], bingfa[craft], env);
        return 1;
}

int do_exert(string arg)
{
        tell_object(this_player(),
                "你现在是三军之统帅了，一举一动请三思！\n");
        return 1;
}

int do_stock(string arg)
{
        object me;
        
        me = this_player();

        if (base_name(environment(me)) != "/d/city2/sying1")
                return notify_fail("请先回你的帐营调派军马，否则将有碍行程！\n");

        if (! arg || arg == "")
                return notify_fail("你想要命令部队去干什么?\n");
              
        set_temp("warquest/purchase", arg, me);
                                
        if( query_temp("warquest/move", me) )
                return notify_fail("号令已经发布下去了！\n");
                
        switch(query_temp("warquest/purchase", me) )
        {
        case "weapon" :
                message_vision(HIW "$N大声喝道：左右军马即刻随本帅" +
                        "开赴襄阳城购置兵甲，不得有误！！\n" NOR, me);
                break;
        case "horse"  :
                message_vision(HIW "$N大声喝道：左右军马即刻随本帅" +
                        "开赴襄阳城购买战马，不得有误！！\n" NOR, me);
                break;
        case "stone"  :
                message_vision(HIW "$N大声喝道：左右军马即刻随本帅" +
                        "开赴襄阳城购置石木，不得有误！！\n" NOR, me);
                break;
        case "arrow"  :
                message_vision(HIW "$N大声喝道：左右军马即刻随本帅" +
                        "开赴襄阳城购置羽箭，不得有误！！\n" NOR, me);
                break;
        case "enlist" :
                message_vision(HIW "$N大声喝道：左右军马即刻随本帅" +
                        "开赴襄阳城招募新兵，不得有误！！\n" NOR, me);
                break;
        case "forage" :
                message_vision(HIW "$N大声喝道：左右军马即刻随本帅" +
                        "开赴京师押解粮草，不得有误！！\n" NOR, me);
                break;
        default :
                tell_object(me, "你想要命令部队去干什么?\n");
                delete_temp("warquest/purchase", me);
                return 1;
                break;
        }

        set_temp("warquest/move", "forward", me);
        set_temp("warquest/move_from", "/d/city2/sying1", me);
                
        return 1;
}

int do_train(string arg)
{
        object me, env;

        me = this_player();
        env = environment(me);

        if (base_name(environment(me)) != "/d/city2/sying1")
                return notify_fail("请先回你的帐营才能调派训练的军马！\n");

        if( query_temp("warquest/train_begin", me) )
                return notify_fail("你不是正在训练队伍吗？！\n");

        message_vision(HIW "$N大声喝道：左右军马，即刻随本帅" +
                "前去操练人马，不得有误！！\n" NOR, me);

        set_temp("warquest/train", "infantry", me);
        me->move("/d/city2/sying2");
        set_temp("warquest/train_begin", 1, me);
        return 1;
}


int do_order(string arg)
{
        object me, env, ob, ling, obb;
        string who, what, dir;
        int i, n, flag;
        mapping jiang;

        me = this_player();
        env = environment(me);
        if (! arg || sscanf(arg, "%s to %s", who, what) != 2)
                return notify_fail("请用 order sb to do sth. 来发布号令！\n");

        if (! objectp(ob = present(who, env)))
                return notify_fail("这里没有你可以调度的这名将领！\n");

        if( query_temp("warquest/party", ob) != "song" )
                return notify_fail("对方不是宋军，如何供你调度？！\n");

        if( !query_temp("warquest/train", ob) || 
            query_temp("warquest/group", ob)<1 )
                return notify_fail("这支队伍尚未训练娴熟，难堪大用！\n");

        if( query_temp("warquest/purchase", ob) )
                return notify_fail("对方正在进行军备工作，最好不要调动他的军队！！\n");
                        
        if (ob == me) return notify_fail("自己命令自己？你不嫌累啊你？！\n");
        
        if (userp(ob)) notify_fail("你不能命令玩家将领！\n");

        switch(what)
        {
        case "follow":
                message_vision(HIY "$N略一沉思，而后果敢的下令道：“$n，" +
                        "本帅决定迎战蒙古大军，\n将军请即刻调派人马随同本帅出征！\n" NOR, me, ob);
                message_vision(HIW "$N大声应道：末将遵命！愿为将军效犬马之劳！\n" NOR, ob);
                ob->set_leader(me);
                break;

        case "stop":               
                message_vision(HIY "$N仔细查看了四周的地形，而后果敢的下令道：“$n听令，" +
                        "立即停止队伍行进！！\n" NOR, me, ob);
                message_vision(HIW "$N大声应道：末将遵命！！\n" NOR, ob);
                ob->command("move stop");
                break;

        default:                
                if (sscanf(what, "guard %s", dir) == 1
                 && query("exits/"+dir, env) )
                {
                        message_vision(HIY "$N仔细查看了四周的地形，而后果敢的下令道：“$n听令，" +
                                "此处地势险要，\n易守难攻，还烦请将军在此处加以扼守！\n" NOR, me, ob);
                        message_vision(HIW "$N大声应道：末将遵命！但存一兵一卒，决不失阵地！\n" NOR, ob);
                        ob->set_leader(0);
                        ob->command("guard " + dir);
                } else
                if (sscanf(what, "move %s", dir) == 1
                 && query("exits/"+dir, env) )
                {
                        message_vision(HIY "$N仔细查看了四周的地形，而后果敢的下令道：“$n听令，" +
                                "立即率领部队\n火速行进，不得有误！！\n" NOR, me, ob);
                        message_vision(HIW "$N大声应道：末将遵命！！\n" NOR, ob);
                        ob->set_leader(0);
                        ob->command("move " + dir);
                } else
                if( query("exits/"+what, env) )
                {
                        ob->set_leader(0);
                        GO_CMD->main(ob, what);
                } else
                        return notify_fail("身为一军之帅，请不要滥用你的军权！\n");
                break;
        }
        set_temp("warquest/battle", 1, ob);
        set_temp("warquest/quest", "军队出征，迎战蒙军", ob);
        return 1;
}

int do_inquiry(string arg)
{
        object me = this_player();
        
        return WAR_D->do_inquiry(me, arg);
}

int do_move(string dir)
{
        object me, env;

        me = this_player();
        env = environment(me);

        if (! dir || dir == "stop")
        {
                remove_call_out("on_move");
                write("部队行进终止！\n");
                return 1;
        }

        if( query("exits/"+dir, env) )
        {
                remove_call_out("on_move");
                call_out("on_move", 2, me, dir);
                write("部队开始行进！\n");
                return 1;
        }
        else
                write("无法移动，没有指定方向的出口！\n");

        return 1;
}

void on_move(object me, string dir)
{
        object env;

        if (! me) return;

        env = environment(me);
        if( !query("exits/"+dir, env) )
        {
                write("无法移动，没有指定方向的出口！\n");
                return;
        }

        if (me->is_fighting() ||
            query_temp("warquest/attack", me) )
        {
                remove_call_out("on_move");
                call_out("on_move", 4, me, dir);
                return;
        } else
        if (GO_CMD->main(me, dir))
        {
                remove_call_out("on_move");
                call_out("on_move", 2, me, dir);
                return;
        } else
        {
                write("无法移动，行进终止！\n");
                return;
        }
}

void owner_is_killed() { destruct(this_object()); }