// This program is a part of NT MudLIB

#include <ansi.h>
#include "xiaoyao.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;
inherit F_QUESTER;

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
string ask_me();
string ask_book();
int ask_job();
int ask_fail();

void create()
{
        set_name("苏星河", ({"su xinghe", "su", "xinghe"}));
        set("gender", "男性" );
        set("nickname", HIW "聪辩老人" NOR);
        set("long", @LONG
此人就是号称聪辩老人的苏星河，据说他能言
善辩，是武林中颇为传神的一位智者，而他的
武功也是无人能知。
LONG );
        set("class", "scholar");
        set("age", 60);
        set("str", 29);
        set("con", 30);
        set("int", 45);
        set("dex", 37);
        set("level", 20);
        set("combat_exp", 2000000);
        set("attitude", "peaceful");

        set("max_qi", 5000);
        set("max_jing", 3000);
        set("neili", 5500);
        set("max_neili", 5500);
        set("jiali", 120);

        set_skill("force", 260);
        set_skill("xiaowuxiang", 240);
        set_skill("dodge", 240);
        set_skill("feiyan-zoubi", 240);
        set_skill("strike", 240);
        // set_skill("panyang-zhang", 240);
        set_skill("liuyang-zhang", 240);
        set_skill("hand", 240);
        set_skill("qingyun-shou", 240);
        set_skill("zhemei-shou", 240);
        set_skill("parry", 240);
        set_skill("blade", 240);
        set_skill("ruyi-dao", 240);
        set_skill("literate", 280);
        set_skill("medical", 260);
        set_skill("xiaoyao-qixue", 260);
        set_skill("mathematics", 240);
        set_skill("drawing",   240);
        set_skill("chuixiao-jifa", 240);
        set_skill("tanqin-jifa", 240);
        set_skill("chess", 280);
        set_skill("calligraphy", 240);
        set_skill("martial-cognize", 240);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("hand", "zhemei-shou");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "zhemei-jian");
        map_skill("blade", "ruyi-dao");
        map_skill("medical", "xiaoyao-qixue");

        prepare_skill("hand", "zhemei-shou");
        prepare_skill("strike", "liuyang-zhang");

        set("no_teach", ([
                "zhemei-shou"   : "逍遥折梅手乃本门神功，只能由掌门人传授。",
                // "liuyang-zhang" : "这天山六阳掌向来只能由逍遥派掌门传功，我不便教授。",
        ]));

        create_family("逍遥派", 2, "掌门弟子");

        set("inquiry", ([
                "捕风捉影" : (: ask_skill1 :),
                // "攀阳邀月" : (: ask_skill2 :),
                "如意六刀" : (: ask_skill3 :),
                "秘密地道" : (: ask_me :),
                "秘籍"     : (: ask_book :),
                "任务" : (: ask_job() :),
                "job" : (: ask_job() :),
                "失败" : (: ask_fail() :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.zhe" :),
                (: perform_action, "hand.hai" :),
                (: perform_action, "strike.huan" :),
                (: perform_action, "strike.zhong" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }));

        set("coagents", ({
                ([ "startroom" : "/d/xiaoyao/shishi",
                   "id"        : "wuya zi" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "对$n" CYN "冷喝道："
                                "阁下请留步，此处乃本门禁地，旁人"
                                "不得入内。" NOR,
                "refuse_carry": CYN "$N" CYN "对$n" CYN "喝道：你"
                                "背负的是什么人，还不快快给我放下"
                                "！" NOR,
        ]));

        set("master_ob", 4);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}


void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 30)
        {
                command("say " + RANK_D->query_respect(ob) + "是否还应该在学"
                        "问上多下点功夫，笨人可逍遥不了！");
                return;
        }

        if( query("combat_exp", ob)<200000 )
        {
                command("say 你现在经验尚浅，不能领会高深的武功，先锻炼要紧。");
                return;
        }

        if (ob->query_skill("force", 1) < 100)
        {
                command("sigh");
                command("say 我们逍遥派的武功都要以内功为基础，你先把"
                        "基础内功学扎实吧。");
                return;
        }

        if (ob->query_skill("xiaowuxiang", 1) < 100)
        {
                command("sigh");
                command("say 你连本门的入门心法都没有学好，还想学本门"
                        "的上乘武学？");
                return;
        }

        command("say 好吧，我就收下你了，今后要多加努力啊！");
        command("recruit "+query("id", ob));
}

int permit_pass(object me, string dir)
{
        if (! ::permit_pass(me, dir))
                return 0;

        if( query("family/master_id", me) == "xiaoyao zi" )
                return 1;

        if( query("combat_exp", me)<300000 )
        {
                command("say 你这种身手不要去那里，好好学我们逍遥派武功。");
                return 0;
        }

        if (me->query_skill("xiaowuxiang", 1) < 120)
        {
                command("say 连我们逍遥心法都学不好，乱走什么？");
                return 0;
        }

        command("sigh");
        command("say 去吧，去吧！有缘者事竟成。");
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/qingyun-shou/zhuo", me) )
                return "我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素无瓜葛，何出此言？";

        if (me->query_skill("qingyun-shou", 1) < 1)
                return "你连青云手都未曾学过，何来绝招？";

        if( query("family/gongji", me)<50 )
                return "你虽在我逍遥门下，却甚无作为，这招我先不忙传你。";

        if (me->query_skill("force") < 100)
                return "你的内功火候不足，学不成这招。";

        if (me->query_skill("qingyun-shou", 1) < 50)
                return "你的青云手火候未到，还得多练习练习。";

        message_vision(HIY "$n" HIY "点了点头，伸手将$N" HIY "招至"
                       "身边，在耳旁低声细说良久，$N" HIY "听"
                       "后会\n心的一笑，看来大有所悟。\n" NOR, me,
                       this_object());

        command("nod");
        command("say 明白了？");
        tell_object(me, HIC "你学会了「捕风捉影」。\n" NOR);

        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("qingyun-shou"))
                me->improve_skill("qingyun-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/qingyun-shou/zhuo", 1, me);
        addn("family/gongji", -50, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/panyang-zhang/pan", me) )
                return "我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素无瓜葛，何出此言？";

        if (me->query_skill("panyang-zhang", 1) < 1)
                return "你连攀阳掌都未曾学过，何来绝招？";

        if( query("family/gongji", me)<100 )
                return "你虽在我逍遥门下，却甚无作为，这招我先不忙传你。";

        if (me->query_skill("force") < 100)
                return "你的内功火候不足，学不成这招。";

        if (me->query_skill("panyang-zhang", 1) < 60)
                return "你的攀阳掌火候未到，还得多练习练习。";

        message_vision(HIY "$n" HIY "略微点了点头，说道：“我给你演示"
                      "一遍，可瞧仔细了！”随即\n一声清啸，双掌纷飞贯"
                      "出，掌影重重叠叠虚实难辨，全全笼罩$N" HIY "全身"
                      "。\n" NOR, me, this_object());

        command("nod");
        command("say 看清楚了就自己下去练吧。");
        tell_object(me, HIC "你学会了「攀阳邀月」。\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("panyang-zhang"))
                me->improve_skill("panyang-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/panyang-zhang/pan", 1, me);
        addn("family/gongji", -100, me);
        return 1;
}

mixed ask_skill3()
{
        object me;

        me = this_player();

        if( query("can_perform/ruyi-dao/ruyi", me) )
                return "我不是已经教过你了吗？";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "和本派素无瓜葛，何出此言？";

        if (me->query_skill("ruyi-dao", 1) < 1)
                return "你连如意刀法都未曾学过，何来绝招？";

        if( query("family/gongji", me)<200 )
                return "你虽在我逍遥门下，却甚无作为，这招我先不忙传你。";

        if (me->query_skill("force") < 150)
                return "你的内功火候不足，学不成这招。";

        if (me->query_skill("ruyi-dao", 1) < 100)
                return "你的如意刀法火候未到，还得多练习练习。";

        message_vision(HIY "$n" HIY "点点头，微笑着示意赞许，伸手将$N"
                       HIY "招到身前，低声在$N" HIY "耳旁嘀\n咕了半天"
                       "。不时还拔出腰刀挥舞几下，似乎是一种颇为神妙的"
                       "刀诀。\n" NOR, me, this_object());

        command("smile");
        command("say 这招很简单，只需稍加练习便成。");
        tell_object(me, HIC "你学会了「如意六刀」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("ruyi-dao"))
                me->improve_skill("ruyi-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/ruyi-dao/ruyi", 1, me);
        addn("family/gongji", -200, me);
        return 1;
}

string ask_book()
{
        object me,ob;
        mapping fam;

        ob = this_player();
        if( !(fam=query("family", ob) )
                || fam["family_name"] != "逍遥派")
        {
                return "想要秘籍就得加入逍遥派。";
        }

        command("sigh");
        return "本派的武功秘籍藏在一个很秘密的地方，我也没去过。";
}
string ask_me()
{
        object me,ob;
        mapping fam;

        ob = this_player();
        if( !(fam=query("family", ob) )
                || fam["family_name"] != "逍遥派")
        {
                return "想要知道密道就得加入逍遥派。";
        }

        command("sigh");
        return "本派的密道在华山之上，很是艰险。你有兴趣可以去看看。";
}

int ask_job()
{

        object me = this_player();
        object ob;
        mapping quest;
        mapping skl;
        string *sname, place;
        int i, skill = 0;
        quest = ("/d/xiaoyao/npc/lagjob")->query_quest();

        skl = me->query_skills();
        if ( !skl ) {
                tell_object(me, "你去学一些本事先吧！\n");
                return 1;
                }
        sname  = sort_array( keys(skl), (: strcmp :) );
        for(i=0; i<sizeof(skl); i++)
                if (skl[sname[i]] >= skill && sname[i] != "literate" && sname[i] != "taoism")

                        skill = skl[sname[i]];

        if (skill < 80) skill = 80;


        if( query("family/family_name", me) != "逍遥派" )
           {
                      message_vision("$N对着$n大喝一声：本派弟子才能做任务。你是哪来的奸细？\n", this_object(), me);
                      return 1;
            }

        if( query("combat_exp", me)<100000){
                command("say " + RANK_D->query_respect(me) + "找本派的掌门信物是很难的，你还是练高经验再来吧");
                return 1;
}
        if ((int)me->query_condition("menpai_busy"))
            {
                      message_vision("$N对着$n摇了摇头说：你办事不利,等会再来!\n", this_object(), me);
                      return 1;
            }

        if( query("potential", me)<200 || query("combat_exp", me)<300){
                command("say 你连本钱都没有，我怎么放心要你去找本派的掌门信物？");
                return 1;
        }

        if( query("kill_xiaoyao", me) == 1){

                command("kick"+query("id", me));
                command("say 我不是给了你任务了吗？");
                return 1;
                }
        else {
                command("nod"+query("id", me));
                command("say " + RANK_D->query_respect(me) + "能为逍遥派出力，真是太好了。");
                command("say"+query("id", me)+"七宝指环在在『"+quest["short"]+"』出现，快去吧！\n"NOR);
                set("kill_xiaoyao", 1, me);
                set("task_time", time()+300, me);
                ob = new("/d/xiaoyao/npc/qiangdao",1);
                if( query("combat_exp", me)>2000000){
                ob = new("/d/xiaoyao/npc/qiangdao2",1);
                }
                ob->move(quest["place"]);
                set_temp("owner/id",query("id",  me), ob);
                set("combat_exp",query("combat_exp",  me), ob);
                set("max_force",query("max_force",  me), ob);
/*
                set("eff_kee",query("max_kee",  me), ob);
                set("max_kee",query("max_kee",  me), ob);
                set("kee",query("max_kee",  me), ob);
*/
                ob->set_skill("dodge", skill);
                ob->set_skill("force", skill);
                ob->set_skill("parry", skill);

                set("force_factor", random(10), ob);
                return 1;
               }
}


int ask_fail()
{
        object me = this_player();

        if( query("kill_xiaoyao", me) == 1){
                command("sigh");
                command("say 你这身手也来找本派的七宝指环,扣你50点POT.");
                addn("potential", -50, me);
               delete("kill_xiaoyao", me);
                me->apply_condition("menpai_busy",10);
//                call_out("delete", 1);
                return 1;
                }
}

int accept_object(object me, object obj)
{
        int r;
   object ob=this_object();
        if (r = ::accept_object(me, obj))
                return r;
   if(!me || environment(me) != environment()) return 0;
   if(!objectp(obj)) return 0;
   if(!present(obj, me)) return notify_fail("你没有这件东西。");
   if(userp(obj) || obj->is_item_make()){
       command("consider"+query("id", me));
       command("say 你拿个快死的人来骗我？");
       return 0;
       }
   if( query("id", obj) == "zhihuan" && query("kill_xiaoyao", me) == 1 )
   {
       command("nod"+query("id", me));
       command("say 干得好！\n");
       remove_call_out("destroying");
       call_out("destroying", 5, obj, ob, me);
       return 1;
       }

   if( query("money_id", obj)){
       command("pat"+query("id", me));
       command("say 我要钱干什么?");
       return 0;
       }
   if( query("kill_xiaoyao", me) == 0){
       command("hehe"+query("id", me));
       command("say 不错啊，但这活我没叫你干啊。");
       return 1;
       }
   else return 0;
}

void destroying(object obj, object ob, object me)
{
   object n_money;
   int kar, exp, pot, gj;
   kar=random(query("kar", me))*15;
   exp = 100 + kar;
   pot = random(exp-80);  //   pot = random(exp)-80;
   gj = random(8)+4;

   if(obj) destruct(obj);

   if(!ob) return;
   if(!me || environment(me) != environment()){
      command("say 咦，人呢？");
      return;
      }
   command("pat"+query("id", me));
   message_vision(HIY"$N对$n说道：你这次做得极为出色！我就指点你两手功夫吧.\n"NOR,ob, me);
                  message_vision(HIC "\n由于$N成功的找回七宝指环，被奖励：\n"
                + chinese_number(exp / 3) + "点实战经验，\n"
               + chinese_number(pot / 2) + "点潜能，\n"
                + chinese_number(gj) + "点功绩作为答谢。\n" NOR, me);
                addn("combat_exp", exp/3, me);
                addn("family/gongji", gj, me);
                if( query("potential", me)>me->query_potential_limit() )
                        addn("potential", pot/2, me);
                else
                        addn("potential", 1, me);
                delete("kill_xiaoyao", me);
        return;
}



/*
void unconcious()
{
        die();
}
*/
