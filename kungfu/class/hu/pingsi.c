#include <ansi.h>

inherit NPC;
inherit F_GUARDER;

int ask_job();
int ask_fail();
mixed ask_me();

void create()
{
        set_name("平四", ({ "ping si", "ping", "si" }));
        set("gender", "男性");
        set("age", 65);
        set("title", "胡家仆佣");
        set("long", "他是胡家忠心耿耿的仆役。\n");
        set("attitude", "peaceful");
        set("str", 20);
        set("int", 20);
        set("con", 24);
        set("dex", 20);

        set("max_qi", 4000);
        set("max_jing", 1000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("combat_exp", 150000);

        set_skill("force", 40);
        set_skill("blade", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("unarmed", 40);

        create_family("关外胡家", 0, "仆佣");

        set("inquiry",([
                "阎基"   : "阎基…哼…这个狗贼。",
                "胡一刀" : "那……那是老主人，唉。",
                "苗人凤" : "苗大侠可不是坏人。",
                "赵半山" : "他对我家主人的交情那是没得说的。",
                "出关"   : (: ask_me :),
                "办事"   : (: ask_me :),
                "出去"   : (: ask_me :),
                "job" : (: ask_job() :),
                "失败" : (: ask_fail() :),
        ]));
        set("coagents", ({
                ([ "startroom" : "/d/guanwai/xiaowu",
                   "id"        : "hu fei" ]),
        }));

        setup();
        set("startroom", "/d/guanwai/xiaoyuan");
        carry_object("/clone/cloth/cloth")->wear();
}

mixed ask_me()
{
        object ob, me;
        me = this_player();

        if( query("family/family_name", me) != "关外胡家" )
                return "你自己没长腿么？";

        if (find_object(query("startroom")) != environment())
                return "我这里还有事，你就自己走回去吧。";

        command("nod");
        command("say 要出去办事么？那我叫几个朋友送你一程吧。");

        message_sort(HIC "\n平四朝远方一招手，顿时几个参客赶着马车驶了"
                     "过来。平四笑道「我家小主人要出关办点事，今趟就劳"
                     "驾你们送送。」参客听后连忙陪笑着答应，$N" HIC "见"
                     "状急忙钻进车中，只听一阵清脆的鞭响，马车绝尘而去"
                     "。\n\n" NOR, me);

        ob = load_object("/d/beijing/majiu");
        ob = find_object("/d/beijing/majiu");
        me->move("/d/beijing/majiu");

        message("vision", HIC "\n远处一辆马车急驶而来，车门一开" +
                          query("name", me)+HIC"从里面钻了出"
                          "来。\n\n" NOR, environment(me), ({me}));

        tell_object(me, CYN "\n参客笑道：这位" + RANK_D->query_respect(me) +
                        CYN "已经到了，请下车吧。\n参客说道：我要"
                        "在这里办些事情，如果打算" HIC "入关" NOR +
                        CYN "的话，我还可以找人送你。\n\n" NOR);
        return 1;

}

int ask_job()
{

        object me = this_player();
        object ob;
        mapping quest;
        mapping skl;
        string *sname, place;
        int i, skill = 0;
        quest = ("/d/guanwai/npc/lagjob")->query_quest();

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

        if( query("family/family_name", me) != "关外胡家" )
        {
                message_vision("$N对着$n说道。你是哪里来的奸细？\n", this_object(), me);
                return 1;
        }

        if( query("combat_exp", me)<100000){
                command("say " + RANK_D->query_respect(me) + "救反清义士的事没那么容易，你还是练高经验再来吧");
                return 1;
        }
        if( query("potential", me)<200){
                command("say 你的潜能太少了!!");
                return 1;
        }

        if (sizeof(children("/d/guanwai/npc/shangdui")) > 10 ||
              !get_object(quest["place"])) {
                command("say 暂时没有任务给你，请稍后再来!!");
                return 1;
        }
        if( query("kill_yunlong", me) == 1){

                command("kick"+query("id", me));
                command("say 我不是给了你任务了吗？");
                return 1;
                }
        else {
                command("nod"+query("id", me));
                command("say " + RANK_D->query_respect(me) + "反清复明，就要坚贞志士，你去吧!");
                command("say"+query("id", me)+"有一个反清义士被抓了，要送往京城，要在『"+quest["short"]+"』路过，快去救人吧！\n"NOR);
                set("kill_yunlong", 1, me);
                set("task_time", time()+300, me);
                ob = new("/d/guanwai/npc/shangdui",1);
                ob->move(quest["place"]);
                set_temp("owner/id",query("id",  me), ob);
                set("combat_exp",query("combat_exp",  me), ob);
                set("max_force",query("max_force",  me), ob);

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

        if( query("kill_yunlong", me) == 1){
                command("pk1");
                command("say 我看错你了，我只能派别人去救反清义士。");

                delete("kill_yunlong", me);
                addn("potential", -50, me);
                tell_object(me, "扣除你的潜能50点。\n");
                return 1;
        }
}
