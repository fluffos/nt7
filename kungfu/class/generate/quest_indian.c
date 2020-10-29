// indian.c 印度高手

#include <ansi.h>

inherit NPC;

string *all_jiuming = ({
        "$n狠狠地给了$N一个大嘴巴，瞪红了眼睛，一副要拼命的样子。\n",
        "$N一把揪住$n的衣领，挥舞着兵器大声的吼叫，$n吓得话都说不出来。\n",
        "$n偷偷从$N脑后狠命敲了一木棍，$N吼叫着回转身，摇摇晃晃的朝$n扑去。\n",
        "$N一脚踹开大门，冲进$n家里，翻箱倒柜到处乱搜。\n",
        "$n被$N一刀砍中胳膊，惊怒交加，疼痛之下更是不由的大声惨呼！\n",
        "$n一路奔跑，企图甩开身后追杀自己的$N，一边扯着嗓子大喊『救命！』\n",
        "$N杀气腾腾地提着滴血的兵器，一个跨步就冲到$n面前，劈头盖脸地砍将上去。\n",
        "$n和$N打作一团，体力不支渐落下风，牙齿紧咬，怒目圆睁。\n",
        "$N刚从门口消失，$n就从桌子底下爬起来，冲到窗口就大喊：『救命啊！』\n",
        "$N高举兵器冲着$n吼叫：『把你所有的钱财通通给我交出来，否则我就一刀砍死你！』\n",
        "$N挥舞着兵器高声叫嚣：『想活命的就把钱财都交出来！别让我等烦了！』\n",
        "$n带着哭腔大声喊叫：『救命啊，谁来救救我啊！』\n",
        "$N奸笑着一巴掌将$n打飞出去，抢过了包裹迫不及待的翻过来寻找财物。\n",
        "$N一脚踹开$n，满脸贪婪的朝钱箱扑了过去。\n",
        "$N一刀将$n砍伤在地，回手一刀又将一只大狼狗给劈成两半。\n",
        "$n一边躲闪着$N的攻击，一边后退，气喘吁吁，眼看快支撑不住了。\n",
});

string *woman_jiuming = ({
        "$N奸笑着冲$n说：『你叫啊，你叫啊，叫破喉咙也没人救得了你！』\n",
        "$N一把搂住$n，色迷迷的上下到处乱摸，$n哭叫得声嘶力竭。\n",
        "$N满脸淫笑，逼近$n，$n吓得尖声惊叫...\n",
        "$N眯着双眼上下打量$n，一步一步地逼近上前...\n",
        "$n双拳乱舞，拼命想阻住$N，脚下一滑，摔倒在地，尖声惊叫起来。\n",
        "$n声嘶力竭地喊叫：『救命啊，快来救救我啊！』\n",
        "$N一个巴掌将$n抽倒在地，淫笑着扑了上去。\n",
        "$N收起兵器，朝$n飞身扑去，$n吓得大声喊叫，四处躲闪。\n",
});

void random_move();
void destruct_me();
int is_stay_in_room() { return 1; }
void jiuming(object npc,object enemy);

void create()
{
       set_name("天竺人", ({ "indian" }));
        set("long", "一个天竺人，长得非常瘦小。\n");
        set("gender", "男性");
        set("age", 20);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);

        // the follow 5 setting has no use
        set("max_qi", 100);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 100);
        set("shen", -1000);

        set("combat_exp", 3000000);
        set("scale", 100);

        set_skill("force", 1);
        set_skill("yujiashu", 1);
        set_skill("dodge", 1);
        set_skill("yujiashu", 1);
        set_skill("parry", 1);
        set_skill("finger", 1);
        set_skill("nianhua-zhi", 1);
        set_skill("strike", 1);
        set_skill("sanhua-zhang", 1);

        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");
        map_skill("force", "yujiashu");
        map_skill("dodge", "yujiashu");
        map_skill("parry", "nianhua-zhi");

        prepare_skill("strike", "sanhua-zhang");
        prepare_skill("finger", "nianhua-zhi");

        set("class", "bonze");

        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("scale", 100);
         set_temp("born_time", time());
        add_money("silver",50);
        keep_heart_beat();

        set_temp("apply/strike", 50);
        set_temp("apply/finger", 50);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/parry", 50);
        set_temp("apply/dodge", 50);
        set_temp("apply/force", 50);

        setup();

        carry_object("/clone/cloth/seng-cloth")->wear();
}

int accept_fight(object ob)
{
        command("say 很好！那我就不客气了。");
        kill_ob(ob);
        return 1;
}

int accept_hit(object ob)
{
        command("say 哼！什么人？");
        kill_ob(ob);
        return 1;
}

void random_move()
{
        int all_enemy;
        object env,*inv,npc;

        if (time() - query_temp("born_time") > 600)
        {
                destruct_me();
                return;
        }

        all_enemy = GROUP_QUEST_D->query_enemy() + 1;
        if (all_enemy < 2) all_enemy = 2;

        if (!GROUP_QUEST_D->query_running_quest() &&
            objectp(env = environment(this_object())) &&
            random(all_enemy) == all_enemy/2)
        {
                inv = all_inventory(env);
                inv -= ({ this_object() });
                inv = filter_array(inv, (: living($1) :));
                if (inv)
                        inv=filter_array(inv,(:!userp($1) && query("race", $1) == "人类":));
                if (inv)
                        inv = filter_array(inv, (: strsrch(base_name($1),"/kungfu/class/generate/") == -1 :));
                if (inv)
                        inv=filter_array(inv,(:query("combat_exp", $1) <= 500000:));
                if (inv)
                        inv=filter_array(inv,(:!query("family", $1):));
                if (inv && sizeof(inv))
                {
                        npc = inv[random(sizeof(inv))];
                        jiuming(npc,this_object());
                }
                inv = 0;
        }
        GROUP_QUEST_D->random_move(this_object());
}

void destruct_me()
{
        message_vision("$N急急忙忙的走了。\n", this_object());
        destruct(this_object());
}

int filter_listener(object ob)
{
        if( !query("channels", ob))return 0;
        //if( member_array("task",query("channels", ob)) == -1)return 0;
        if( query("env/no_task", ob) )return 0;
        return 1;
}

void jiuming(object npc,object enemy)
{
        object *listeners;
        string msg;

        if (!npc || !enemy)
                return;

        if( query("gender", npc) == "女性" && random(2) )
                msg = woman_jiuming[random(sizeof(woman_jiuming))];
        else
                msg = all_jiuming[random(sizeof(all_jiuming))];

        msg = replace_string(msg,"$N",enemy->name());
        msg = replace_string(msg,"$n",npc->name());

        listeners = filter_array(users(), (: filter_listener :));

        message("group_quest",HIR "【外敌】" NOR + WHT + msg + NOR,listeners);
}
