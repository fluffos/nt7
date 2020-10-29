// This program is a part of NT MudLIB
// jinshe.c 金蛇郎君

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

#define QUESTDIR "skybook/bixue/"

void dest(object ob);
int ask_fuchou();
int ask_jinshe();
string ask_skill1(object me,string arg);
string ask_skill2(object me,string arg);
string ask_skill3(object me,string arg);
void create()
{
        set_name("夏雪宜", ({"xia xueyi", "xia", "xueyi"}));
        set("nickname", HIY"金蛇郎君"NOR);
        set("gender", "男性");
        set("age", 25);
        set("long", 
                "他就是人称“金蛇郎君”的一代怪杰——夏雪宜。\n"
                "他做事全凭好恶，时正时邪，端地是独来独往，好不潇洒！\n"
                "听说他的身世很惨，人也变得偏激起来。\n"
                "看起来他好象受了点伤，脸色很难看。\n");
         set("attitude", "peaceful");
        
        set("str", 100);
        set("int", 20);
        set("con", 30);
        set("dex", 25);
        set("chat_chance", 15);
        set("chat_msg", ({
                "夏雪宜突然恶狠狠地说道：仪儿，你到底为什么要害我！？\n",
                "夏雪宜眼中仿佛要喷出火来。\n",
                "突然，夏雪宜“哇”地一声，吐出一大口带黑的血。\n",
        }));
        set("inquiry", ([
                "温仪"    : "她....她..... \n",
                "复仇"    : (: ask_fuchou :),
/*
                "锁剑诀"  :        (: ask_skill1 :),
                "附骨缠身":        (: ask_skill2 :),
                "金蛇吐雾":        (: ask_skill3 :),
*/
                "心得"    : (: ask_jinshe :),
                "金蛇剑法": (: ask_jinshe :),
                "秘诀"    : (: ask_jinshe :),
        ]));
        set("qi", 10000);
        set("max_qi", 10000);
        set("jing", 5000);
        set("max_jing", 5000);
        set("neili", 9000);
        set("max_neili", 9000);
        set("jiali", 100);
        set("no_get",1);
        set(QUESTDIR+"pass", 1);
        
        set("combat_exp", 10000000);
         
        set_skill("force", 200);                // 基本内功
        set_skill("huntian-qigong", 200);       // 混天气功
        set_skill("unarmed", 220);              // 基本拳脚
        set_skill("dodge", 200);                // 基本躲闪
        set_skill("parry", 200);                // 基本招架
        set_skill("sword", 200);                // 基本剑法
        set_skill("jinshe-jian",200);           // 金蛇剑法
        set_skill("strike", 200);
        set_skill("jinshe-zhang", 200);
        set_skill("throwing", 200);
        set_skill("jinshe-zhui", 200);
        set_skill("martial-cognize", 200);
        
        map_skill("force", "huntian-qigong");
        map_skill("sword", "jinshe-jian");
        map_skill("parry", "jinshe-jian");
        map_skill("strike", "jinshe-zhang");
        
        setup();
        
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

int accept_object(object who, object ob)
{
        object obn;
        if( !who || environment(who) != environment() ) return 0;
        if( !objectp(ob) ) return 0;
        if( !present(ob, who) ) return notify_fail("你没有这件东西。\n");
        if( query("id", ob) != "wen shoupa" )
                return notify_fail("夏雪宜不需要这件东西。\n");
        write(HIY "夏雪宜接过手帕，呆呆地出神，突然间潸然泪下。 \n" NOR);
        write(HIR "夏雪宜喃喃道：仪儿啊，我知道你的心意，其实就算是真的，我也不在乎的。\n" NOR);         
        write(HIY "夏雪宜转过头来对你说：我该怎样感谢你呢？\n" NOR);
        write(HIY "他背转身去，沉默不语，好象在思考着什么。\n" NOR);
        write(HIY "夏雪宜突然象下了很大决心似地对你说：我看\n" NOR);
        write(HIY "你也是武林中人，这里有三我毕身心血的《金蛇秘芨》，\n" NOR);
        write(HIY "现在它对我来说已经没有什么用了，你就拿去吧。\n" NOR);
        write(HIY "夏雪宜叹了口气道：你是锄恶扬善也好，我行我素也好，胡作非为也好，通通与我无关。\n" NOR);
        write(HIY "夏雪宜挥了挥手：好了，你可以走了。\n" NOR);

        obn = new("/clone/book/jinshe1");
        obn->move(who);
        obn = new("/clone/book/jinshe2");
        obn->move(who);
        obn = new("/clone/book/jinshe3");
        obn->move(who);
        write(HIR "夏雪宜回首按了墙上的一个机关，只听得隆隆几声巨响，石壁之上露出一个四方的洞口来。\n"NOR);
        set("exits/east","/d/shiliang/jinshedong1", get_object("/d/shiliang/jinshedong"));
        destruct(ob);
        return 1;
}
void dest(object ob)
{
        destruct(ob);
}
/*
string ask_skill1(object me,string arg)
{
        return teach_perform(this_player(),this_object(),([
                "perform"        : "suo",        //pfm的代码
                "name"                : "锁剑诀",        //pfm的名称
                "sk1"                : "jinshe-jian",//主要的武功的id
                "lv1"                : 100,                //主要的武功的等级
                "sk2"                : "sword",        //需要武功sk2的id
                "lv2"                : 100,                //需要武功sk2 的等级
                "neili"                : 300,                //需要基本内功等级
                "free"                : 1,                 //free=1不需要同一门派
                "msg1"                : "$N哈哈一笑：要学其实这招并不难，天下人都以常理出招。\n"+
                                "而我金蛇剑法反其道而行，剑诀要旨在于意境，不在招式。\n"+
                                "$n听了$N的指导，恍然大悟。",
                "msg2"                : "好了，你自己继续练习吧。",
                ]));
}
string ask_skill2(object me,string arg)
{
        return teach_perform(this_player(),this_object(),([
                "perform"        : "fugu",        //pfm的代码
                "name"                : "附骨缠身",        //pfm的名称
                "sk1"                : "jinshe-zhang",//主要的武功的id
                "lv1"                : 100,                //主要的武功的等级
                "sk2"                : "strike",        //需要武功sk2的id
                "lv2"                : 100,                //需要武功sk2 的等级
                "neili"                : 300,                //需要基本内功等级
                "free"                : 1,                 //free=1不需要同一门派
                ]));
}
string ask_skill3(object me,string arg)
{
        return teach_perform(this_player(),this_object(),([
                "perform"         : "tuwu",        //pfm的代码
                "name"                : "金蛇吐雾",        //pfm的名称
                "sk1"                : "jinshe-zhui",//主要的武功的id
                "lv1"                : 100,                //主要的武功的等级
                "sk2"                : "throwing",        //需要武功sk2的id
                "lv2"                : 100,                //需要武功sk2 的等级
                "force"                : 100,                //需要基本内功等级
                "neili"                : 300,                //需要最大内力多少
                "free"                : 1,                 //free=1不需要同一门派
                ]));
}
*/

int ask_fuchou() 
{
        object me = this_player();

        if( me->query_skill("jinshe-jian",1) <200 )
                   return 1;

        if( me->query_condition("killer") )
        {
                command("fear "+query("id", me));
                command("say 小心官府通缉！");
                return 1;
        }

        if( query_temp(QUESTDIR+"start", me) )
        {
                command("shake "+query("id", me));
                command("say 你不是说要帮我复仇的吗，怎么还在这里？");
                return 1;
        } 
        
        if( query(QUESTDIR+"over", me) )
        {
                command("thank "+query("id", me));
                command("say 你已经杀了温家五老帮我复仇了，真是太感谢了！");
                return 1;
        } 
        //非vip玩家，只能失败三次
        if( query(QUESTDIR+"fail", me) >= 3 && query("registered", me)<3 )
        {
                command("shake "+query("id", me));
                command("say 现在时间紧急，这复仇的事情还是以后再说吧。");
                return 1;
        }
        //需要间隔一天，经验需要间隔500k

        if( query(QUESTDIR+"start/time", me) && time()-query(QUESTDIR+"start/time", me)<86400 )
        {
                command("shake "+query("id", me));
                command("say 今天先这里吧，有什么事情明天再说吧。");
                return 1;
        }
        if( query(QUESTDIR+"combat_exp", me) && query("combat_exp", me)-query(QUESTDIR+"combat_exp", me)<500000 )
        {
                command("look "+query("id", me));
                command("say 以你当前的经验恐怕还是难以帮我复仇，还是抓紧去练功去吧。");
                return 1;
        }
        
        command("look "+query("id", me));
        command("say 好吧，你去帮我杀掉温家五老，我定有重谢。");
        command("say 你只要和温家五老的老大提起“金蛇郎君”即可。");

        set_temp(QUESTDIR+"start", 1, me);//开始标志
         //标记开始时间和经验
        set(QUESTDIR+"time", time(), me);
        set(QUESTDIR+"combat_exp",query("combat_exp", me), me);
        return 1;
}

int ask_jinshe() 
{
        object me = this_player();      
        int exp, neili;
     
        //相关武功等级必须在250以上
        if( me->query_skill("jinshe-zhui",1) <250 )
                   return 1;
                   
        if( me->query_skill("jinshe-zhang",1) <250 )
                   return 1;
                   
        //必须杀死过温家五老
        if( !query(QUESTDIR+"over", me) )
                   return 1;

        if( me->query_condition("killer"))
        {
                command("fear "+query("id", me));
                command("say 小心官府通缉！");
                return 1;
        }

        //非vip玩家，只能失败三次
        if( query(QUESTDIR+"fail", me) >= 3 && query("registered", me)<3 )
        {
                command("shake "+query("id", me));
                command("say 我不是都告诉你了吗，领悟不了可是你自己的事情了。");
                return 1;
        }
        //武功学习之间需要间隔一天，经验需要间隔500k

        if( query(QUESTDIR+"time", me) && time()-query(QUESTDIR+"time", me)<86400 )
        {
                command("shake "+query("id", me));
                command("say 今天先这里吧，有什么事情明天再说吧。");
                return 1;
        }
        if( query(QUESTDIR+"combat_exp", me) && query("combat_exp", me)-query(QUESTDIR+"combat_exp", me)<500000 )
        {
                command("look "+query("id", me));
                command("say 以你当前的经验恐怕还是难以领悟要诀，还是抓紧去练功去吧。");
                return 1;
        }
        exp=7000+random(3000);
        neili=200+random(300);
        command("look "+query("id", me));
        command("say 既然你帮我报了大仇，我就将我对金蛇秘籍的研究心得告诉你吧。");
        //标记武功的时间和标志
        set(QUESTDIR+"time", time(), me);
        set(QUESTDIR+"combat_exp",query("combat_exp",  me), me);
        if( random(query("kar", me)) > 22 )
        {
                set(QUESTDIR+"pass", 1, me);
                tell_object(me,HIG"\n你听了夏雪宜的指点，再与金蛇秘笈中不解之处一加参照，登时豁然贯通，果然妙用无穷。\n\n"NOR);
                tell_object(me,HIC"\n你闭目冥思，《金蛇秘笈》中种种武功秘奥，有如一道澄澈的小溪，缓缓在心中流过，\n"NOR);
                tell_object(me,HIC"清可见底，更先半分渣滓，直到许久才醒觉。经此一阵苦思，不但通解了金蛇郎君的\n"NOR);
                tell_object(me,HIC"\n武学秘诀，对师父所授诸般上乘武功，也有更深一层体会。\n"NOR);
                command("wa "+query("id", me));
                tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"得到夏雪宜的指点，武学修为精进，获得"+exp+"点经验奖励、"+neili+"点最大内力。\n"NOR);
                addn("combat_exp", exp, me);
                addn("max_neili", neili, me);
                me->improve_skill("jinshe-jian", 2000000);
                log_file("quest/jinshequest",sprintf("%s(%s)失败%d次后得到夏雪宜的指点，武学修为精进。奖励：%d点经验，%d点最大内力。\n",me->name(1),query("id", me),query("skybook/bixue/fail", me),exp,neili));

                return 1;
        }
        tell_object(me,HIR"\n苦思冥想，发现自己依然无法理解夏雪宜所传秘诀。\n\n"NOR);
        command("sigh "+query("id", me));
        addn(QUESTDIR+"fail", 1, me);
        log_file("quest/jinshequest",sprintf("%s(%s)第%d次向夏雪宜求教，但是依然无法理解其中诀窍。\n",me->name(1),query("id", me),query("skybook/bixue/fail", me)));

        return 1;
}
