// This program is a part of NITAN MudLIB 
// redl 2012/11/1 
inherit NPC;
#include <ansi.h>
int ask_makesan();
int ask_begdan();

void add_dan()
{
        set("guiyuan_dan", 1);
        call_out("add_dan", 3600);//每小时能领1颗临寂归元丹
}

void create()
{
        set_name(NOR "沈芝毓" NOR, ({ "shen zhiyu","shen" }) );
        set("title", HIG"秘药师"NOR);
        set("nickname", HIM "化乐天女" NOR);
        set("gender", "女性");
        set("age", 25);
        set("long", "她是一个浑身散发着神秘气息的女人，据说身兼各门旷世的炼药之术。\n"
                                "只见有朵小小的"+HIR+"血红花儿"+NOR+"被她缠在纤纤玉指间不停拨弄着...\n");
        set("attitude", "friendly");
        set("str", 21);
        set("con", 19);
        set("int", 36);
        set("dex", 25);
        set("per", 29);
        set("kar", 30);
        set("level",50);
        set("medical_book", 100);
        
        set("max_qi", 100000);
        set("eff_qi", 100000);
        set("qi", 100000);
        set("max_jing", 100000);
        set("eff_jing", 100000);
        set("jing", 100000);
        set("max_neili", 1);
        set("neili", 1);
        set("max_jingli", 1);
        set("jingli", 1);
        

        set("chat_chance", 3);
        set("chat_msg", ({
                        //(: random_move :) , 
                CYN"沈芝毓微笑着说：武当派玉清散的效力甚奇，但服用方法太繁琐。\n"NOR ,
                CYN"沈芝毓微笑着说：武当派玉清散的效力甚奇，但服用方法太繁琐。\n"NOR ,
                CYN"沈芝毓微笑着说：武当派玉清散的效力甚奇，但服用方法太繁琐。\n"NOR ,
                CYN"沈芝毓微笑着说：武当派玉清散的效力甚奇，但服用方法太繁琐。\n"NOR ,
                CYN"沈芝毓微笑着说：武当派玉清散的效力甚奇，但服用方法太繁琐。\n"NOR ,
                CYN"沈芝毓嬉笑着说：火炼玉清散之法固是卓绝常理，我水炼之法将之提纯却是更上层楼。\n"NOR ,
                CYN"沈芝毓嬉笑着说：火炼玉清散之法固是卓绝常理，我水炼之法将之提纯却是更上层楼。\n"NOR ,
                CYN"沈芝毓纤指微捻间呢喃道：这么冷僻的洗象池，薄霜浓雾峰沁雪，此花怎生就结的出？\n"NOR ,
                CYN"沈芝毓蹙眉沉思道：既为故人所钟，峨眉弟子有求于我时自当照拂一二...\n"NOR ,
        }) );

        set("combat_exp", 300000000);

        set_skill("liandan-shu", 2500);
        
        set("inquiry", ([
                "玉清散"   : (: ask_makesan :),
                "归元丹"   : (: ask_begdan :),
                "玉清丸"     : "你的水准不够，把大量的玉清散交给我，我帮你炼炼玉清丸吧。\n"+NOR,
                "炼丹术"     : "我是可以传授炼丹术(liandan-shu)的，好好学习吧..\n"+NOR,
                "波陀摩"     : "你也知道那种花儿吗？我可喜欢他了，下次见到帮我摘一朵好吗？\n"+NOR,
                "麻薯"     : "Hmm..谁告诉你我贪吃的？我可从来不喜欢吃零食的哦！\n"+NOR,
        ]));
        

        setup();
        carry_object("/d/city/npc/cloth/moon-dress")->wear();
        this_object()->apply_condition("die_guard", 999999999);
        set_temp("nopoison", 3, this_object()); 
                add_dan();
}



void fight_ob(object ob)
{
       ob->remove_enemy(this_object());
       this_object()->remove_enemy(ob);
       tell_object(ob,CYN + "沈芝毓用一双无辜的媚眼望着你，眼泪都快要掉下来了。\n" + NOR + "你赶紧手忙脚乱地停了下来。\n" + NOR); 
       return;
}

int accept_kill(object who)
{
       who->remove_enemy(this_object());
       this_object()->remove_enemy(who);
       return notify_fail(CYN + "沈芝毓对著你眨眨眼，露出神秘的微笑 ... \n" + NOR + "你发现自己怎么也舍不得下手！\n" + NOR); 
}

int accept_fight(object who)
{
       who->remove_enemy(this_object());
       this_object()->remove_enemy(who);
       return notify_fail(CYN + "沈芝毓对著你眨眨眼，露出神秘的微笑 ... \n" + NOR + "你发现自己怎么也舍不得下手！\n" + NOR); 
}

int accept_ansuan(object who)
{
       who->remove_enemy(this_object());
       this_object()->remove_enemy(who);
       return notify_fail(CYN + "沈芝毓在远处对你眨眼，露出神秘的微笑 ... \n" + NOR + "你发现自己怎么也舍不得下手！\n" + NOR);
}

void receive_damage(string type, int n)
{
        full_self();
        return;
}

void receive_wound(string type, int n)
{
        return;
}

void unconcious()
{
        return;
}

void die(object killer)
{
        return;
}

void eat_mashu()
{
        this_object()->command("set careful");
        set("food", 0, this_object());
        this_object()->command("eat ma shu");
}

int accept_object(object me, object obj)
{
        int amount;
        object obz;
        
        if (me->is_busy())
        {
                tell_object(me,CYN + "沈芝毓掩著嘴吃吃地笑著对你说：你先把你的事儿忙完再说好不？ \n" + NOR); 
                return 0;
        }
        else 
                me->start_busy(3);

        if (query_temp("shenzy/givewan", me))
        {
                tell_object(me,CYN + "沈芝毓掩著嘴吃吃地笑著对你说：别这么心急好不好？我的宝贝葫芦忙着呢... \n" + NOR); 
                 return 0;
        }
                
        switch (query("id", obj))
        {                       
         case "ma shu":
            if( stringp(query("food_race", obj)) || !query("food_remaining", obj) ) {
                tell_object(me,CYN "沈芝毓摇头对你说道：咦..你这是给我的啥玩意儿？\n" NOR); 
                return 0;
                }
            if( query("decay", obj) > 1 ) {
                tell_object(me,CYN "沈芝毓摇头对你说道：已经变质了，你留着自个儿吃吧。\n" NOR); 
                return 0;
                }
                tell_object(me,CYN "沈芝毓对你嘻嘻笑道：谢谢你这么有心了。\n" NOR); 
                addn("shenzy/mashu", 1, me);
                obj = new("/clone/medicine/yuqingwan");
                obj->set_amount(1);
        obj->move(me);
        message_vision(YEL + "沈芝毓一挥衣袖拂过$N的手心时悄悄塞入了一颗"+HIB+"蓝色小药丸"+YEL+"。\n" + NOR, me);
        call_out("eat_mashu", 2 + random(6));
                return 1;
         case "yuqing san":
                if (!function_exists("query_amount",obj) || !query("only_do_effect", obj))
                {
                tell_object(me,CYN "沈芝毓摇头对你说道：咦..你这是给我的啥玩意儿？\n" NOR); 
                return 0;
                }

        if( query("family/master_name", me) != "张三丰" && query("family/family_name", me) != "峨嵋派")
        {
                tell_object(me,CYN "沈芝毓摇头对你说道：我只帮峨嵋派和武当张真人弟子，你还是回去吧。\n" NOR); 
                return 0;
        }
        
                if( !query("is_alchemy", me) )
                {
                tell_object(me,CYN "沈芝毓摇头对你说道：你先去平大夫那里加入炼药师协会再来找我吧。\n" NOR); 
                return 0;
                }
  
                obz = present("yaoshi zheng", me);
                if( !objectp(obz))
                {
                tell_object(me,CYN "沈芝毓摇头对你说道：炼药师协会的平大夫颁发给你的炼药师证呢？\n" NOR); 
                return 0;
                }
                if (query("level", obz) < 3)//炼药师证小于3品，即900炼丹术，+sk的装备不影响
                {
                tell_object(me,CYN "沈芝毓摇头对你说道：你这炼药水平也太次了些吧？三品境界以下的庸才别来烦我。\n" NOR); 
                return 0;
                }
                
                amount = obj->query_amount();
                amount /= 1000;
                
                if (amount < 1)
                {
                tell_object(me,CYN "沈芝毓轻蔑地对你说道：这点玉清散太少，还不值得我出手...\n" NOR); 
                return 0;
                }
         
                set_temp("shenzy/givewan", 1, me);
                amount *= 1000;
         
                if (obj->query_amount() > amount)
                {
                        obj->add_amount(- amount);
                        tell_object(me,CYN "沈芝毓对你点头道：行了，零头拿回去，马上兑给你。\n" NOR); 
                        call_out("delay_givewan", 2, me, new("/clone/medicine/yuqingwan"), amount);
                        return 0;//多退少补
                }
                else
                {
                        destruct(obj);
                        tell_object(me,CYN "沈芝毓对你点头道：好吧，耐心等等，这就兑给你。\n" NOR); 
                        call_out("delay_givewan", 2, me, new("/clone/medicine/yuqingwan"), amount);
                        return 1;
                }
                
         default:
                return 0;
        }
}

void delay_givewan(object me, object obj, int amount)
{
                        obj->set_amount(amount / 1000);
                obj->move(me);
                message_vision(YEL + 
                "沈芝毓一挥腰间佩着的紫金小葫芦收走了$N的玉清散，\n" + 
                "随后衣袖拂过$N的手心时悄悄塞入了"+chinese_number(amount / 1000)+"颗"+HIB+"蓝色小药丸"+YEL+"。\n" + NOR, me);

                me->improve_skill("medical", amount * 25);
                me->improve_skill("liandan-shu", amount * 50);//增加炼丹术提高的机会，在目前的游戏里实在缺乏，先决条件限制了3品药师，则为后期大米了，100倍也不过分
                
/*              峨嵋派1000w exp后得到照拂，暂定1包玉清散获得5点exp，
                现在玉清散的计划产量大概在24小时1万包左右，那么10id每天可得50w exp。鼓励多建立武当造散大米来提高人气
                因为峨眉派本来就弱，如果不能转世，每天多成长50w~200w exp也不算什么，就不用封顶奖励等级了！ */
                
        if( query("family/family_name", me) == "峨嵋派" && query("level", me) >= 10 )
        {
                GIFT_D->work_bonus(me, ([ "exp" : amount*5, "pot" : amount ]));
                }
                
                delete_temp("shenzy/givewan", me);
                return;
}



int recognize_apprentice(object me, string skill)
{
        //峨眉无master会1000炼丹术，再此给予900支持，以保证能评上3品药师
        if (query("family/family_name", me) != "峨嵋派")
        {
        tell_object(me,CYN "沈芝毓向你扮了个鬼脸，嘻嘻一笑：我只想教授峨眉弟子一些炼丹知识哦..\n" NOR); 
        return -1;
        }

        if (skill != "liandan-shu")
        {
        tell_object(me,CYN "沈芝毓阴沉着小脸凑近你问道：你.确信..你想学的..不是炼丹术(liandan-shu)...吗？\n" NOR); 
        return -1;
        }
        
        if ( me->query_skillo("liandan-shu", 1) >= 450 && query("shenzy/mashu", me)>random(100) && !query("can_make/临寂归元丹", me) ) {
        tell_object(me,HIG "沈芝毓悄悄告诉你：如此如此，@*#^@^*#^@##$&**&\n" NOR); 
        tell_object(me,HIG "沈芝毓悄悄告诉你：这般那般，@!&#^%@&*$&#&&@&#@*$!^%@\n" NOR); 
                tell_object(me,YEL "你经过沈芝毓耐心点拨，学会了临寂归元丹的制作方法...\n" NOR); 
                set("can_make/临寂归元丹", "guiyuan", me);
        }
        
        
        if (me->query_skillo("liandan-shu", 1) >= 900)
        {
        tell_object(me,CYN "沈芝毓你用力拍著你的背，一副「干得好，你终于出师了！」的奸笑。\n" NOR); 
        return -1;
        }
        return 1;
}


int ask_makesan()
{
    object me = this_player();
    
        if (query("family/family_name", me) != "峨嵋派")
        {
        tell_object(me,CYN "沈芝毓阴沉着小脸凑近你问道：你.确信..真的想知道只有峨嵋弟子该知道的惊天秘密？\n" NOR); 
        return -1;
        }

        if (me->query_skillo("liandan-shu", 1) < 300)
        {
        tell_object(me,CYN "沈芝毓一巴掌拍你脑门上说道：你先好好学习炼丹术吧...\n" NOR); 
        return -1;
        }

        if (query("medical_book") < 1)
    {
                command("say 真是可惜，你来晚了，书我已经借出去了。");
                return -1;
        }
        
        if (query_temp("shenzy/givebook", me))
    {
        tell_object(me,CYN "沈芝毓劈头给了你一巴掌，叹道：当我是出版社呢？\n" NOR); 
                return -1;
        }
        
        //开放峨眉能制药玉清散，分散武当派人数
        addn("medical_book", -1);
        message_vision(CYN "$n翻出一本黄色小册子递给$N，叮嘱道：唔，你懂的，好好看。\n" NOR, me, this_object());
        new(__DIR__"obj/mbook")->move(me);
        set_temp("shenzy/givebook", 1, me);
        
        return 1;
}

int ask_begdan()
{
    object me = this_player();
    
        if (query("guiyuan_dan") < 1)
    {
                command("say 真是可惜，你来晚了，临寂归元丹我已经送出去了。");
                return -1;
        }
        
        if (query("family/family_name", me) != "峨嵋派")
        {
        tell_object(me,CYN "沈芝毓阴沉着小脸凑近你问道：你.确信..真的想知道只有峨嵋弟子该知道的惊天秘密？\n" NOR); 
        return -1;
        }

        if (query("level", me) >= query("level"))
        {
        tell_object(me,CYN "沈芝毓掩著嘴吃吃地笑著对你说：你脸皮怎么这么厚，等级比我还高了还到我这里来蹭东西咧！\n" NOR); 
        return -1;
        }

        addn("guiyuan_dan", -1);
        message_vision(CYN "$n抛给$N一颗淡蓝小药丸，挤眉弄眼道：接好，记得提前吃，千万别上瘾了啊。\n" NOR, me, this_object());
        new("/clone/medicine/guiyuan")->move(me);
        return 1;
}








