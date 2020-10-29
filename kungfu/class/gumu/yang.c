// yang.c 杨过

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_GUARDER;

#include <ansi.h>
#include "gumu.h"

string ask_yunv();
int not_to_learn_ss(object ob);
mixed teach_sad();
string ask_sword();
int ask_youju();
mixed ask_me();
string ask_nuhai();

void create()
{
        set_name("杨过", ({"yang guo", "yang"}));
        set("gender", "男性");
        set("age", 26);
        set("long", @LONG
他看上去眉目之间有一股清秀之气，然而隐隐约约却让人感到一阵哀伤之情，
左袖空荡荡的，显然已是残疾。
LONG );
        set("attitude", "friendly");

        set("str", 35);
        set("int", 36);
        set("con", 34);
        set("dex", 32);

        set("qi", 7800);
        set("max_qi", 7800);
        set("jing", 6900);
        set("max_jing", 6900);
        set("neili", 8500);
        set("max_neili", 8500);
        set("jiali", 120);
        set("no_get", 1);

        set("combat_exp", 5750000);

        set("couple/id", "xiao longnv");
        set("couple/name", "小龙女");

        set_skill("force", 690);
        set_skill("yunv-xinfa", 690);
        set_skill("surge-force", 690);
        set_skill("sword", 680);
        set_skill("yunv-jian", 680);
        set_skill("quanzhen-jian", 680);
        set_skill("xuantie-jian", 680);
        set_skill("dodge", 650);
        set_skill("yunv-shenfa", 650);
        set_skill("parry", 680);
        set_skill("unarmed", 680);
        set_skill("meinv-quan", 670);
        set_skill("strike", 680);
        set_skill("sad-strike", 680);
        set_skill("fireice-strike", 680);
        set_skill("tianluo-diwang", 660);
        set_skill("literate", 600);
        set_skill("taoism", 600);
        set_skill("medical", 680);
        set_skill("array", 680);
        set_skill("yunv-xinjing", 680);
        set_skill("throwing", 640);
        set_skill("yufeng-zhen", 640);
        set_skill("hebi-jianzhen", 640);
        set_skill("martial-cognize", 600);
        set_skill("taishang-wangqing", 600); 

        map_skill("force", "surge-force");
        map_skill("sword", "xuantie-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "sad-strike");
        map_skill("unarmed", "sad-strike");
        map_skill("strike", "tianluo-diwang");

        prepare_skill("unarmed", "sad-strike");

        create_family("古墓派", 3, "弟子");

        set("inquiry", ([
                "王重阳" : "嘿...嘿！",
                "郭靖"   : "他可真是真正的大侠。",
                "黄蓉"   : "黄师叔么...真不好说啊。",
                "小龙女" : "你打听我妻子干什么？",
                "杨康"   : "算了，不替他也罢。",
                "玉蜂针" : "我手头可没有，很久没有用它了。",
                "黯然销魂掌" : (: teach_sad :),
                "玄铁剑法"   : "那是独孤前辈所创绝学，在下有幸到是习得！\n",
                "玄铁剑" :   (: ask_sword :),
                "玄铁剑法" : (: ask_sword :),
                "古墓幽居" : (: ask_youju :),
                "怒海狂涛"   : (: ask_nuhai :),
        ]));

        set("guarder", ([
                "refuse_home" : "$N对$n冷冷道：滚！",
                "refuse_other": "$N对$n道：后面是古墓弟子练功的地方，你少要打扰！",
                "refuse_carry": "$N对$n喝道：把你身上得人给我撂下！",
        ]));

        set("no_teach/sad_strike", (: not_to_learn_ss :));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.wang" :),
                (: perform_action, "unarmed.xiao" :),
                (: perform_action, "unarmed.tuo" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/attack", 150);
        set_temp("apply/defense", 150);
        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();

        carry_object("/clone/cloth/qingyi")->wear();
}

void init()
{
        ::init();
        add_action("do_yuanyi", "yuanyi");
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) == query("family/family_name") )
        {
                if (query_skill(skill, 1) < 1 ||
                    SKILL_D(skill)->type() != "martial")
                        return 0;

                if( query("int", ob)<24 )
                {
                        command("say 你这人资质不佳，我教起来太累。");
                        return -1;
                }

                return 1;
        }

        if (skill == "unarmed" &&
            this_player()->query_skill("sad-strike", 1) > 0 &&
            this_player()->query_skill(skill, 1) < 200)
                return 1;

        if (skill != "sad-strike")
        {
                command("say 你还是找你的师傅去学习吧！");
                return 0;
        }

        if (not_to_learn_ss(ob))
                return -1;

        if (this_player()->query_skill(skill, 1) > 600)
                return 0;

        return 1;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 32)
        {
                command("say 你的资质不够，难以领会上乘武功。");
                return;
        }

        if ((int)ob->query_skill("force") < 150)
        {
                command("say 想拜我为师么？你把内功练好了再来吧！");
                return;
        }

        if( query("max_neili", ob)<1000 )
        {
                command("say 你把内力锻炼好了再来也不迟啊！");
                return;
        }

        command("say 好吧，看你也是性情中人，我就收下你这个徒弟了。");
        command("recruit "+query("id", ob));
}

string ask_sword()
{
        object ob = this_player();
        mapping fam=query("family", ob);
        if (! fam || fam["family_name"] != "古墓派")
                return RANK_D->query_respect(ob) + "非我古墓传人，不知道此话怎讲？";
        if (fam["generation"] > 4)
                return RANK_D->query_respect(ob) + "非我神雕侠侣传人，还是等以后再说吧。";
        if( query("ygpass", ob) )
                return "我不是已经告诉你玄铁剑法的运气之道了么？";
        if( query("gender", ob) == "男性" )
        {
                command("pat"+query("id", ob));
                command("say 当年我在襄阳城南，得遇神雕的相助，于独孤大侠墓前练成玄铁剑法。");
                set("ygpass", 1, ob);
                return "屏气具息，凝气守中，意守丹田，这就是在洪水中运气的诀窍，你好好去领悟一下吧。";
        }
        if( query("gender", ob) == "女性"){
        if ((int)ob->query_str() < 35)
                return "这位" + RANK_D->query_respect(ob) + "，玄铁剑法需要极高的膂力，你还是再努力一翻吧。";
        if ((int)ob->query_dex() < 35)
                return "这位" + RANK_D->query_respect(ob) + "，在洪水中练习玄铁剑法需要极高的身法，你还是再努力一翻吧。";
        if ((int)ob->query_skill("sword", 1) < 200)
                return "这位" + RANK_D->query_respect(ob) + "的基本剑法还需继续修炼，否则难以抵挡洪水的冲击。";
        if ((int)ob->query_int() < 35)
                return "这位" + RANK_D->query_respect(ob) + "的悟性还不够高，难以理解我所要讲的口诀。";
                  command("pat"+query("id", ob));
                  command("say 当年我在襄阳城南，得遇神雕的相助，于独孤大侠墓前练成玄铁剑法。");
                  set("ygpass", 1, ob);
                  return "屏气具息，凝气守中，意守丹田，这就是在洪水中运气的诀窍，你好好去领悟一下吧。";
        }
}

int ask_youju()
{
        object ob = this_player();

        if( query("family/family_name", ob) != "古墓派"){
                command("say 这是“美女拳法”最后一招的收式，是我所自创的。");
                return 1;
        }
        if( query("family/master_name", ob) == "李莫愁"){
                command("say 这是“美女拳法”最后一招的收式，是我所自创的。");
                command("say 你是我师伯李莫愁的弟子，我本不该指点于你。");
                command("say 既然一场来到，如果你愿意让我为化去你身上的邪气，指点你这招“古墓幽居”。你愿意(yuanyi)否？");
                set_temp("mark/youju", 1, ob);
                return 1;
                }
        if( query("can_perform/meinv-quan/you", ob)>0){
                command("say 你不是已经学会了吗？");
                return 1;
        }
        if ((int)ob->query_skill("unarmed", 1) < 120) {
                command("say 要使用这样的绝招需要高深的拳法，你还是多练习练习“美女拳法”再说吧。");
                return 1;
        }
        command("say 这是“美女拳法”最后一招的收式，是我所自创的。");
        command("say 好，既然一场来到，你我可谓有缘，待我指点你这招“古墓幽居”。");
        message_vision( "$N仔细给$n讲解了“古墓幽居”的精要所在。\n",this_object(), ob );
        set("can_perform/meinv-quan/you", 1, ob);
        return 1;
}
int do_yuanyi()
{
        object me = this_player();

        if( !query_temp("mark/youju", me) )
                return 0;

        message_vision("$n伸手在$N身上几处命门大穴连拍数下。\n", me, this_object() );
        write("你感到头脑中一阵通泰。\n");
        set("shen", 0, me);
        command("say 好，孺子可教，我就指点你这招“古墓幽居”。");
        message_vision( "$N仔细给$n讲解了“古墓幽居”的精要所在。\n",this_object(), me );
        delete_temp("mark/youju", me);
        set("can_perform/meinv-quan/you", 1, me);
        return 1;
}

// 领取怒海狂涛任务
string ask_nuhai()
{
        object me;
        string msg;
        
        
        me = this_player();
        
        if( query("can_perform/surge-force/new", me) )
                return "这怒海狂涛的绝学已经掌握了，还来打搅我干什么？";
                
        //如果已经领取任务
        if( query("can_perform/surge-force/quest/step", me) )
                return "如果你能帮我找到龙儿，这怒海狂涛的绝学我便传你。";
        
        msg = HIC "怒海狂涛是我多年来在与海浪搏击中领悟而出的惊世绝学，其中融入了多种顶级武学\n"
                  "的精髓。可惜，目前龙儿被金轮法王掳走，下落不明，如果你能协助我找回龙儿，这\n"
                  "套绝学我便传你。\n" NOR;
        
        tell_object(me, msg);

        set("can_perform/surge-force/quest/step", 1, me);
        me->save();
        
        return "听说金轮法王最近在绝情谷出没，你可以上那去看看。\n";    
}
mixed teach_sad()
{
        object ob = this_player();

        if (ob->query_skill("sad-strike", 1) >= 1)
        {
                command("say 你不是已经会了吗？");
                return 1;
        }

        if( query("gender", ob) != "男性" )
        {
                command("say 我这门武功只适合男性修炼，你还是算了吧！");
                return 1;
        }

        if( query("static/sadly", ob)<3 )
        {
                command("say 你体会不到那种思念妻子的情怀，"
                        "无法领会我的黯然销魂掌！");
                return 1;
        }

        if( query("character", ob) == "阴险奸诈" || 
            query("character", ob) == "心狠手辣" )
        {
                command("say 你一心想着去害人，无法领悟黯然销魂的境界！");
                return 1;
        }

        if( query("int", ob)<24 )
        {
                command("say 你先天悟性不足，无法领悟黯然销魂掌。");
                return 1;
        }

        if( query("str", ob)<28 )
        {
                command("say 你先天臂力不足，无法修炼黯然销魂掌。");
                return 1;
        }

        if( query("max_neili", ob)<3000 )
        {
                command("say 你的内力修为不足，无法练黯然销魂掌。");
                return 1;
        }

        if (ob->query_skill("force") < 320)
        {
                command("say 你内功修为不足，无法修炼黯然销魂掌。");
                return 1;
        }

        if ((int)ob->query_skill("unarmed", 1) < 200)
        {
                command("say 你的基本拳脚不够娴熟，无法练黯然销魂掌。");
                return 1;

        }

        if (ob->query_skill("martial-cognize", 1) < 200)
        {
                command("say 你武学修养不足，无法领悟炼黯然销魂掌。");

                return 1;
        }

        message_vision(HIW "$n" HIW "看了看$N" HIW "，道：好！你我也算是颇有"
                       "渊源，我就传你黯然销魂掌！\n" NOR, ob, this_object());

        ob->set_skill("sad-strike", 10);

        tell_object(ob, HIG "你学会了「黯然销魂掌」。\n" NOR);

        command("tan");
        command("say 下去练习吧，记得要好好对待你的妻子！");

        return 1;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "历练" :
        case "历炼" :
        case "锻炼" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "卷字诀" :
       return MASTER_D->teach_pfm(this_player(), this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/juan",
                           "free"    : 1,
                           "name"    : "卷字诀",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 100,
                           "neili"   : 3000,
                           "force"   : 600,
                        ]));
                break;

        case "迅雷" :
       return MASTER_D->teach_pfm(this_player(), this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/lei",
                           "name"    : "迅雷",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 200,
                           "sk2"     : "force",
                           "lv2"     : 200,
                           "sk3"     : "surge-force",
                           "lv3"     : 200,
                           "gongxian": 600, ])); 
                break;

        case "大江东去" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/dong",
                           "free"    : 1,
                           "name"    : "大江东去",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 200,
                           "neili"   : 5000,
                           "force"   : 600,
                         ]));
                break;

        case "力荡群魔" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/dang",
                           "name"    : "力荡群魔",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 70,
                           "sk2"     : "force",
                           "lv2"     : 90,
                           "gongxian": 600, ]));
                break;

        case "海潮汹涌" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/hai",
                           "name"    : "海潮汹涌",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 130,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "sk3"     : "dodge",
                           "lv3"     : 100,
                           "gongxian": 600, ]));

                break;

        case "千均一击" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xuantie-jian/ji",
                           "name"    : "千均一击",
                           "sk1"     : "xuantie-jian",
                           "lv1"     : 130,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "sk3"     : "dodge",
                           "lv3"     : 100,
                           "gongxian": 600, ]));

                break;

        case "黯然销魂" :
                return MASTER_D->teach_pfm(me, this_object(),
                          ([ "perform" : "can_perform/sad-strike/xiao",
                           "free"    : 1,
                           "name"    : "黯然销魂",
                           "sk1"     : "sad-strike",
                           "lv1"     : 150,
                           "neili"   : 3200,
                           "force"   : 320,
                         ]));
                break;

        case "拖泥带水" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/sad-strike/tuo",
                           "free"    : 1,
                           "name"    : "拖泥带水",
                           "sk1"     : "sad-strike",
                           "lv1"     : 180,
                           "neili"   : 6000,
                           "force"   : 360,
                         ]));
                break;

            case "怒海惊涛" :
                  return MASTER_D->teach_pfm(me, this_object(),
                          ([ "perform" : "can_perform/sad-strike/tao",
                             "free"    : 1,
                               "name"    : "怒海惊涛",
                             "sk1"     : "sad-strike",
                             "lv1"     : 280,
                             "neili"   : 6000,
                             "force"   : 560,
                           ]));
                  break;

        default:
                return 0;
        }
}

int not_to_learn_ss(object ob)
{
        if( query("gender", ob) == "女性" )
        {
                command("say 我这门武功不适合女孩子学习，还是算了吧！");
                return 1;
        }

        if( query_temp("can_learn/yang/sad-strike", ob) )
                return 0;

        if( query("family/family_name", ob) != query("family/family_name") )
        {
                command("say " + RANK_D->query_respect(ob) + "你不是我的亲传弟子，找我何干？");
                return 1;
        }

        if( query("static/sadly", ob)<3 )
        {
                command("say 你体会不到那种思念妻子的情怀，"
                        "无法领会我的黯然销魂掌！");
                return 1;
        }

        message_vision("$n看了看$N，道：好！你我也算是颇有"
                       "渊源，我就传你黯然销魂掌！\n",
                       ob, this_object());
        set_temp("can_learn/yang/sad-strike", 1, ob);
        return 0;
}

/*
mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/sad-strike/wannian", me) )
                return "自己好好多练习吧！";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "你不是我的亲传弟子，何出此言？";

        if( query("shen", me)<200000 )
                return "你行侠仗义的事情做的还很不够，我不能传你这一招！";

        if (me->query_skill("sad-strike", 1) < 180)
                return "你的黯然销魂掌还不够熟练，我还不能教你这一招！";

        message_vision(HIM "$n" HIM "慢慢运起内功，然后以疾风般的速度向$N"HIM"挥出一掌！\n"
                       HIM "$n" HIM "这一掌虽然奇快无比，但是$N"HIM"确把一招的来势看得很透澈，然后轻而易举的避开了！\n"
                       "正当$N" HIM "奇怪为什么这一招这么差的时候，$n"HIM"的掌势突然向旁边一转，正好打在了$N"HIM"的胸口上！！！\n"
                       "$N"HIM"大吃一惊，躲避已经不行，连忙动起内功硬生生的受了这一招，但是......\n" NOR,
                       me, this_object());
        command("sigh");
        command("say 你就先躺一下吧。");
        tell_object(me, HIG "你学会了万念俱灰。\n" NOR);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 160000);
        set("can_perform/sad-strike/wannian", 1, me);
        me->unconcious();
        return 1;
}
*/
// 接受绝情丹
int accept_object(object me, object ob)
{
        int r;
        
        if (r = ::accept_object(me, ob)) 
                return r;
                
        if (! objectp(me) || ! objectp(ob))return 0;
        
        if( query("id", ob) != "jueqing dan" )
        {
                return 0;
        }

        if( query("can_perform/surge-force/new", me) )
        {
                tell_object(me, HIG "杨过告诉你：多谢阁下上次仗义相助，这东西还是你自己留着吧。\n" NOR);
                return 0;
        }
        
             if( query("family/family_name", me) != "古墓派"){ 
                     tell_object(me, HIG "杨过告诉你：你是何方屑小，居然想偷学我的绝学。\n" NOR); 
                     return 0;
             } 
        if( query("can_perform/surge-force/quest/step", me)<3 )
                return 0;
        
        if( query("yuanshen_level", me) < 1 )
        {               
                tell_object(me, HIG "杨过告诉你：你还未经历轮回转世的磨练，恐怕难以学成怒海狂涛。这丹我要不得。\n" NOR);
                return 0;
        }
                
        if( query("int", me)<40 || query("con", me)<30 )
        {               
                tell_object(me, HIG "杨过告诉你：你先天属性不足，难以学成怒海狂涛。这丹我要不得。\n" NOR);
                return 0;
        }
                
        if (me->query_skill("force", 1) < 1000)
        {
                tell_object(me, HIG "杨过告诉你：你基本内功修为不足，无法修炼怒海狂涛。这丹我要不得。\n" NOR);
                return 0;
        }               
        if( query("max_neili", me)<35000 )
        {
                tell_object(me, HIG "杨过告诉你：你内力修为不足，无法修炼怒海狂涛。这丹我要不得。\n" NOR);
                return 0;
        }       
        if (me->query_skill("taoism", 1) < 1)
        {
                tell_object(me, HIG "杨过告诉你：你道学心法修为不足，无法修炼怒海狂涛。这丹我要不得。\n" NOR);  
                return 0;
        }               
        if (me->query_skill("xuantie-jian", 1) < 1)
        {
                tell_object(me, HIG "杨过告诉你：你玄铁剑法修为不足，无法修炼怒海狂涛。这丹我要不得。\n" NOR);  
                return 0;                               
        }               
        if (me->query_skill("martial-cognize", 1) < 1200)
        {
                tell_object(me, HIG "杨过告诉你：你武学修养不足，无法修炼怒海狂涛。这丹我要不得。\n" NOR);              
                return 0;
        }               
        if (me->query_skill("jiuyin-shengong", 1) < 1 && 
            me->query_skill("jiuyin-hamagong", 1))
        {
                tell_object(me, HIG "杨过告诉你：你未曾练成过九阴真经，无法修炼怒海狂涛。这丹我要不得。\n" NOR);
                return 0;       
        }               

        command("thank "+query("id", me));
        
        message_sort(HIM "\n$N" HIM "对$n说道：多亏了阁下仗义相助，龙儿这下有救了，杨某无以为谢，便"
                     "将这怒海狂涛绝学传授于你，你可听好了 ...\n\n" NOR, this_object(), me);

                                
        tell_object(me, HIG "杨过将怒海狂涛绝学修炼要决一一传授于你...\n" NOR);

        tell_object(me, HIC "\n恭喜你！领悟了怒海狂涛（新）。\n");

        CHANNEL_D->do_channel(this_object(), "rumor", "听说杨过将怒海狂涛绝学传授给了" HIY + me->name() + HIM "。" NOR);

        me->set_skill("surge-force", 200);
        set("can_perform/surge-force/new", 1, me);
        
        destruct(ob);
        
        me->save();     

        return 1;
}
/*
void unconcious()
{
        die();
}
*/
