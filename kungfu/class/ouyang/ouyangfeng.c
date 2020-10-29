// ouyangfeng.c

#include <ansi.h>
#include "ouyang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

//#define ZHANG "/d/baituo/obj/lingshezhang"
#define ZHANG "/clone/lonely/lingshe"

string ask_shenshe(string name);
mixed ask_me();
mixed ask_music_book();
mixed ask_skill1();
mixed ask_skill2();
string ask_lingshe();
mixed ask_shegu();

void create()
{
        set_name("欧阳锋", ({ "ouyang feng", "ouyang", "feng" }));
        set("long", "他就是白驼山庄主，号称“西毒”的欧阳锋。脸型瘦削，\n"
                    "身形剽悍，虽然受到郭靖欺骗误学习了「九阴真经」而走\n"
                    "火入魔，一度变得精神错乱，但是现在已然恢复，功力犹\n"
                    "胜往昔。\n");
        set("title", "西域白驼山庄主");
        set("gender", "男性");
        set("age", 53);
        set("nickname", HIR "西毒" NOR);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set("str", 32);
        set("int", 34);
        set("con", 34);
        set("dex", 32);

        set("qi", 6000);
        set("max_qi", 6000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 200);

        set("combat_exp", 4000000);

        set_skill("force", 640);
        set_skill("strike", 640);
        set_skill("dodge", 640);
        set_skill("parry", 640);
        set_skill("cuff", 640);
        set_skill("finger", 640);
        set_skill("staff", 640);
        set_skill("training", 640);
        set_skill("poison", 5000);
        set_skill("shedu-qiqiao", 640);
        set_skill("hamagong", 640);
        set_skill("chanchu-bufa", 640);
        set_skill("lingshe-quan", 640);
        set_skill("lingshe-zhangfa", 640);
        set_skill("shentuo-zhang", 640);
        set_skill("baibian-daxue", 640);
        set_skill("guzheng-jifa", 620);
        set_skill("xiyu-tiezheng", 620);
        set_skill("wushe-qu", 620);
        set_skill("literate", 680);
        set_skill("medical", 660);
        set_skill("baituo-michuan", 660);
        set_skill("jinchan-tunyue", 660);
        set_skill("martial-cognize", 620);

        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("cuff", "lingshe-quan");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("strike","hamagong");
        map_skill("staff", "lingshe-zhangfa");
        map_skill("finger", "shedu-qiqiao");
        map_skill("poison", "shedu-qiqiao");
        map_skill("medical", "baituo-michuan");
        map_skill("guzheng-jifa", "xiyu-tiezheng");

        prepare_skill("finger", "shedu-qiqiao");
        prepare_skill("cuff", "lingshe-quan");

        create_family("欧阳世家", 5, "掌门");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.chan" :),
                (: perform_action, "staff.qianshe" :),
                (: perform_action, "staff.wuji" :),
                (: perform_action, "cuff.rou" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set("inquiry", ([
                "绝招"     : (: ask_me :),
                "绝技"     : (: ask_me :),
                "千蛇出洞" : (: ask_me :),
                "引路神蛇" : (: ask_shenshe, "shenshe":),
                "灵蛇"     : (: ask_lingshe :),
                "蛇谷"     : (: ask_shegu :),
                "筝谱"     : (: ask_music_book :),
                "古筝技法" : (: ask_music_book :),
                "灵蛇缠身" : (: ask_skill1 :),
                "横行无忌" : (: ask_skill2 :),
        ]));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("music_book", 1);

        set("master_ob",5);
        setup();
        carry_object(__DIR__"obj/baipao")->wear();
        carry_object("/d/baituo/obj/shezhang")->wield();
        carry_object("d/baituo/obj/tiezheng");
        add_money("silver", 50);
}

int recognize_apprentice(object me, string skill)
{
        if (skill != "guzheng-jifa")
                return 0;

        if( query_temp("can_learn/ouyang/guzheng-jifa", me) )
                return 1;

        command("say 好吧，你愿意学我就传你一点古筝之道。");
        set_temp("can_learn/ouyang/guzheng-jifa", 1, me);
        return 1;
}

void attempt_apprentice(object ob)
{
        if(! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<200000 )
        {
                if (random(2))
                        command("smile");
                else
                        command("pat"+query("id", ob));

                command("say 你的经验还不够，先和我的侄儿欧阳克学习武功吧。");
                return ;
        }

        command("sigh");
        command("pat"+query("id", ob));
        command("recruit "+query("id", ob));
        command("say 不错，不错！我欧阳真是后继有人。");
        return;
}

mixed ask_skill1()
{
        object me=this_player();

        if( query("can_perform/lingshe-zhangfa/chan", me) )
                return "我不是已经教给你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return ("哪来的野小子敢在这里撒野！\n");

        if (me->query_skill("lingshe-zhangfa",1 ) < 100)
                return ("你的杖法还不到家，学不了「灵蛇缠身」！\n");

        command("say 好吧，你看好了。");
        tell_object(me, HIR"欧阳峰将「灵蛇缠身」演练了一遍，你心里默默暗记，心中惊叹不已。\n"NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lingshe-zhangfa/chan", 1, me);
        return 1;
}

mixed ask_skill2()
{
        object me;
        me = this_player();

        if( query("can_perform/lingshe-zhangfa/wuji", me) )
                return "你还不快去练功去？好好把我们欧阳家发扬光大！";

        if( query("family/family_name", me) != query("family/family_name") )
                return ("哪来的野小子敢在这里撒野！\n");

        if (me->query_skill("lingshe-zhangfa", 1) < 100)
                return ("你的杖法还不到家，学不了「横行无忌」！\n");

        command("say 好吧，你看好了。");
        tell_object(me, HIR"欧阳峰将「横行无忌」演练了一遍，你心里默默暗记，心中惊叹不已。\n"NOR);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/lingshe-zhangfa/wuji", 1, me);
        return 1;
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/lingshe-zhangfa/qian", me) )
                return "你还不快去练功去？好好把我们欧阳家发扬光大！";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你是哪儿来的？找死么？";

        if( query("shen", me)>-40000 )
                return "你这人手段不够狠毒，我现在还不能传你绝招！";

        if (me->query_skill("lingshe-zhangfa", 1) < 120)
                return "你先好好把灵蛇杖法练好了再说！";

        message_vision(HIY "$n" HIY "喝道：看仔细了！说把荡"
                       "臂横扫，伸伸缩缩，当真是变幻无穷！把$N"
                       HIY "的眼睛都看直了。\n" NOR,
                       me, this_object());
        command("heihei");
        command("say 我演示的这么清楚，你看懂了没有？");
        tell_object(me, HIG "你学会了千蛇出洞。\n" NOR);

        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("staff"))
                me->improve_skill("staff", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        if (me->can_improve_skill("lingshe-zhangfa"))
                me->improve_skill("lingshe-zhangfa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
           set("can_perform/lingshe-zhangfa/qian", 1, me); 
        return 1;
}

string ask_shenshe(string name)
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "欧阳世家" )
                return RANK_D->query_respect(this_player()) +
                "，你并不是本山庄的人，此话从何说起？";

        if (  present("shen she", this_player()) )
                return RANK_D->query_respect(this_player()) +
                "你身上不是有神蛇吗？怎么又来要？真是贪得无厌！";

        ob = new("/d/baituo/obj/" + name);
        ob->move(this_player());

        message_vision("欧阳锋给$N一条"+query("name", ob)+"。\n",this_player());
        return "此神蛇乃本山庄特有，切记不可给予他人！";
}

mixed ask_music_book()
{
        object me;
        object ob;

        me = this_player();
        if (query("music_book") < 1)
                return "我的筝谱已经借出去了。\n";

        ob = new("/clone/book/zhengpu");
        ob->move(me, 1);
        message_vision("$n把筝谱给了$N，道：你拿去自己好好琢磨吧。\n",
                       me, this_object());
        set("music_book", 0);
        return 1;
}

mixed ask_shegu()
{
        object me, staff;
        object owner;
        object ob;
int lv,cost;
        me = this_player();

        if( query("family/family_name", me) != "欧阳世家" && query("combat_exp", me)>100000){
                command("sneer"+query("id", me));
                command("say 白驼山蛇谷的秘密，岂能透露给外人知晓？"+RANK_D->query_rude(me)+"，你太多嘴了！");
                kill_ob(me);
                command("performbite"+query("id", me));//hasweapon
                command("performpuji"+query("id", me));//noweapon
                return 1;
        }

        if( query("family/family_name", me) != "欧阳世家"){
                command("sneer"+query("id", me));
                message_vision("$N没有回答$n。\n", this_object(), me);
                return 1;
        }

   if( query("family/first", me) ) cost = 250; 
             else cost = 500; 
             if( query("family/gongji", me) < cost ) 
                     return "你为我白驼山效力还不够，等你拥有足够的师门功绩再来兑换灵蛇杖使用时间吧。";
             ob = find_object(ZHANG);
             if (! ob) ob = load_object(ZHANG);
             owner = environment(ob);
             while (owner)
            {
                    if (owner->is_character() || ! environment(owner))
                            break;
                    owner = environment(owner);
            }

            if (owner == me)
                    return "灵蛇杖不是在你的手中么，怎么又来找我呢？";

             if (objectp(owner) && owner != this_object())
             {
                     if (! owner->is_character())
                             return "我已经把灵蛇杖已经借出去了。";

                     if( query("family/master_id", owner) == query("id") )
                             return "灵蛇杖现在在"+query("name", owner)+
                                    "手中，你要想用就去找他吧。";
                     else
                             return "灵蛇杖现在落在"+query("name", owner)+
                                    "手中，你去把他找回来吧。";
            }

        if( query("baituo/shegu_permit", me)){
//                command("say 蛇谷中的蛇儿，你可以随意捕捉。好好修炼毒技，莫要堕了西毒的威名！");
//        staff = new("/d/baituo/obj/lingshezhang");
//        staff->move(me);
             ob->move(this_object());

message_vision("$N点点头道：蛇谷中的蛇儿，你可以随意捕捉。好好修炼毒技，莫要堕了西毒的威名！\n", this_object(), me);
            command("give lingshe zhang to "+query("id", me));
addn("family/gongji", -cost, me); 
                ob->start_borrowing();
                return 1;
        }

        lv = (int)me->query_skill("poison", 1);

        if( lv < 80 ) {
                command("say 凭你这点使毒本事，想进蛇谷还早得很。乖乖的在庄里修炼！");
                return 1;
        }

        if( lv < 100 ) {
                command("pat "+query("id", me));
                command("say 你的毒技是有点火候了，不过想进蛇谷，还得多下点功夫琢磨。");
                return 1;
        }

        command("nod "+query("id", me));
        command("say 你用毒的能耐，似乎是进步多了。好，老夫就许你进蛇谷练练本领。");
        set("baituo/shegu_permit", 1, me);

//        staff = new("/d/baituo/obj/lingshezhang");
//        staff->move(me);
             ob->move(this_object());

//        message_vision("$N将一根"+staff->name()+"交给$n。\n",this_object(), me);
message_vision("$N点点头道：从今以後，你可以自由进出蛇谷。用心从中钻研，你的毒技还可以更上层楼！\n", this_object(), me);
            command("give lingshe zhang to "+query("id", me));
//        command("say 从今以後，你可以自由进出蛇谷。用心从中钻研，你的毒技还可以更上层楼。");

        return 1;
}


string ask_lingshe()
{
        mapping fam;
        object obj, me;

        me = this_player();
        if( query("family/master_name", me) != "欧阳锋"){
                return ("娃娃功力不够，还是别要为妙！");
        }
        if (query("lingshe_count") < 1) {
                return ("灵蛇驯养不易，现在没有！");
        }
        message_vision(CYN"$N撮唇作啸，袖中缓缓游出一条银色小蛇，对着$n摇头摆尾，似在示意问好。\n"NOR,
        this_object(), me);
        obj = new("/d/baituo/npc/lingshe.c");
        obj->move(environment());
        addn("lingshe_count", -1);
                  return ("灵蛇已显，娃娃不妨试试是否有缘成为它的主人。");
}

void reset()
{
        if (query("lingshe_count") < 3)
                addn("lingshe_count", 1);
        set("music_book", 1);
}

/*
void unconcious()
{
        die();
}
*/

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "历练" :
        case "历炼" :
        case "锻炼" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "蟾震九天" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hamagong/zhen",
                           "name"    : "蟾震九天",
                           "sk1"     : "hamagong",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 1000,
                           "shen"    : -24000, ]));
                break;

        case "蛤蟆扑击" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hamagong/puji",
                           "name"    : "蛤蟆扑击",
                           "sk1"     : "hamagong",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "neili"   : 1400,
                           "shen"    : -28000, ]));
                break;

        case "推天式" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hamagong/tui",
                           "name"    : "推天式",
                           "sk1"     : "hamagong",
                           "lv1"     : 60,
                           "force"   : 150,
                           "gongxian": 400,
                           "shen"    : -20000, ]));
                break;

        case "雪锁千山" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shentuo-zhang/suo",
                           "name"    : "雪锁千山",
                           "sk1"     : "shentuo-zhang",
                           "lv1"     : 120,
                           "gongxian": 400,
                           "shen"    : -10000, ]));
                break;

        case "柔字诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/lingshe-quan/rou",
                           "name"    : "柔字诀",
                           "sk1"     : "lingshe-quan",
                           "lv1"     : 120,
                           "gongxian": 400,
                           "shen"    : -10000, ]));
                break;

        case "点字诀" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/baibian-daxue/dian",
                           "name"    : "点字诀",
                           "sk1"     : "baibian-daxue",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : -10000, ]));
                break;

        case "灵蛇缠身" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/lingshe-zhangfa/chan",
                           "name"    : "灵蛇缠身",
                           "sk1"     : "lingshe-zhangfa",
                           "lv1"     : 140,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "shen"    : -30000, ]));
                break;

        default:
                return 0;
        }
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))
                return r;

        if (base_name(ob) != ZHANG)
        {
                command("say 你给我这种东西干什么？");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say 多谢这位" + RANK_D->query_respect(me) + "将灵蛇杖送回。");
        else
                command("say 很好，很好！");
        destruct(ob);
        return 1;
}
