#include <ansi.h>
inherit NPC;

#define gold_limit  100000
#define time_limit  900
#define level_limit 800

private void add_all_inquiry();
private void greeting(object me);
private int ask_test(object me, object ob);
private int ask_money(object me, object ob);
private int ask_faction(object me, object ob);
private int ask_all_faction(object me, object ob);
private int setskills(string arg, object me, object ob);

string *all_knowledge = ({
"literate",
"buddhism",
"taoism",
"qimen-wuxing",
"dacheng-fofa",
});

void create()
{
    set_name("荣荣", ({ "rong rong", "rong" }));
    set("nickname", HIG "ask rong about test" NOR);
    set("title", HIY "测试引导员" NOR);
    set("gender", "男性");
    set("shen", 0);
    set("age", 20);
    set("per", 20);
    set("no_get", 1);
    set("wiz_tester", 1);
    set("combat_exp", 10000000);
    set("attitude", "friendly");
    set("long", "这个人看上去永远是一副没有睡醒的样子。\n");

    setup();
    carry_object("/clone/misc/cloth")->wear();
    add_all_inquiry();
}

void init()
{
    add_action("setskills", "setskill");
    if(this_object()->is_livings() && !wizardp(this_player()))
    {
        remove_call_out("greeting");
        call_out("greeting", 1, this_player());
    }
    ::init();
}

private void greeting(object me)
{
    if(!me || environment(me) != environment())
        return;
    tell_object(me, this_object()->name(1) + "向你嘻皮笑脸的道：“这位"
                    + RANK_D->query_respect(me) + "也来参加测试("
                    HIY "ask rong about test" NOR")吧？！”\n");
}

private void add_all_inquiry()
{
    int i;
    string type;
    mapping *all_skill, all_inquiry;

    all_inquiry = ([]);
    all_skill   = FACTION_D->query_all_skill();
    for(i = 0; i < sizeof(all_skill); i++)
    {
        all_inquiry += ([ all_skill[i]["name"] : (: ask_faction :)]);
    }

    all_inquiry += ([

        "test"  : (: ask_test :),
        "money" : (: ask_money :),
        "skill" : (: ask_all_faction :),
    ]);

    this_object()->set("inquiry", all_inquiry);
}

private int ask_test(object me, object ob)
{
    me = this_player();
    ob = this_object();

    message("vision", ob->name(1) + "在" + me->name() + "耳边小声的"
                      "说了几句话。\n", environment(me), ({ me, ob }));
    tell_object(me, ob->name(1) + "干咳了两声，装腔作势的说道：\n");
    tell_object(me, HIW@TEXT

请按照下列关键字来向测试引导员进行查询：

    test  ：获取测试引导员帮助信息
    money ：获取供测试用的钱庄存款
    skill ：查询可供选择的武功技能

    指令格式：ask rong about <关键字>


    如果想更换供测试用的技能，请使用setskill指令

    指令格式：setskill <你的ID> use <技能名称>

    注意：更换技能将先会删除你身上原有的所有技能

TEXT NOR);
    return 1;
}

private int ask_money(object me, object ob)
{
    me = this_player();
    ob = this_object();

    if(wizardp(me))
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                       "耳边小声说了几句话。\n", environment(me),
                                                 ({ me, ob }));
        tell_object(me, YEL + ob->name(1) + "摇头道：你不是巫师吗？"
                                            "自己call就行了。\n" NOR);
        return 1;
    }

    if(time() - me->query("set_skill/money") < time_limit)
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                       "耳边小声说了几句话。\n", environment(me),
                                                 ({ me, ob }));
        tell_object(me, YEL + ob->name(1) + "摇头道：不要太贪心，前后两次"
                                            "获取测试用的金钱之间必须间隔"
                                            + chinese_number(time_limit/60) +
                                            "分钟以上。\n" NOR);
        return 1;
    }

    me->set("set_skill/money", time());
    me->set("bank/gold", gold_limit);
    message("vision", ob->name(1) + "点了点头，在" + me->name() +
                       "耳边小声说了几句话。\n", environment(me),
                                                 ({ me, ob }));
    tell_object(me, HIC + ob->name(1) + "点头道：供测试用的金钱"
                    HIY + chinese_number(gold_limit) + "两黄金"
                    HIC "已经打到你的钱庄帐户上了。\n" NOR);
    return 1;
}

private int ask_faction(object me, object ob)
{
    string topic;

    me = this_player();
    ob = this_object();

    message("vision", ob->name(1) + "在" + me->name() + "耳边小声的"
                      "说了几句话。\n", environment(me), ({ me, ob }));
    tell_object(me, ob->name(1) + "干咳了两声，装腔作势的说道：\n");

    topic = me->query_temp("last_ask/topic");
    if(me->query_temp("ask_all_faction"))
    {
        topic = "";
        FACTION_D->show_skill(me, 0);
    }
    else
    {
        FACTION_D->show_skill(me, topic);
    }

    if(me->query_temp("ask_all_faction"))
        me->delete_temp("ask_all_faction");

    return 1;
}

private int ask_all_faction(object me, object ob)
{
    me = this_player();
    ob = this_object();

    me->set_temp("ask_all_faction", 1);
    ask_faction(me, ob);
    tell_object(me, HIC + ob->name(1) + "悄声道：可用某项技能的名称"
                                        "作为关键字向我查询，以获取"
                                        "进一步的信息。\n" NOR);
    return 1;
}

private int setskills(string arg, object me, object ob)
{
    int i;
    object obj;
    string who, skill;

    me = this_player();
    ob = this_object();

    if(!arg || sscanf(arg, "%s use %s", who, skill) != 2)
        return notify_fail(HIW "指令格式：setskill <你的ID> "
                               "use <技能名称>\n" NOR);

    obj = present(who, environment(me));
    if(!objectp(obj))
        return notify_fail(YEL + ob->name(1) + "疑惑的道：你要设定"
                                               "谁的技能？\n" NOR);

    if(obj != me)
        return notify_fail(YEL + ob->name(1) + "摇头道：你只能更换"
                                               "自己的测试用技能。\n" NOR);

    if(wizardp(me))
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                       "耳边小声说了几句话。\n", environment(me),
                                                 ({ me, ob }));
        tell_object(me, YEL + ob->name(1) + "摇头道：你不是巫师吗？"
                                            "自己call就行了。\n" NOR);
        return 1;
    }

    if(time() - me->query("set_skill/time") < time_limit)
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                       "耳边小声说了几句话。\n", environment(me),
                                                 ({ me, ob }));
        tell_object(me, YEL + ob->name(1) + "摇头道：不要太频繁，前后两次"
                                            "更换测试用的技能之间必须间隔"
                                            + chinese_number(time_limit/60) +
                                            "分钟以上。\n" NOR);
        return 1;
    }

    if(me->query("generation_skill/name") == skill)
        return notify_fail(YEL + ob->name(1) + "摇头道：你当前使用的技能正是「"
                               + skill + "」，无须重复设定。\n" NOR);

    me->set("str", 30);
    me->set("int", 10);
    me->set("con", 60);
    me->set("dex", 30);
    me->set("con_improve_time", 50);
    me->set("food", (int)me->max_food_capacity());
    me->set("water", (int)me->max_water_capacity());

    me->set("set_skill/level", level_limit);
    FACTION_D->gen_npc(me, skill);

    for(i = 0; i < sizeof(all_knowledge); i++)
    {
        me->set_skill(all_knowledge[i], level_limit);
    }

    if(me->query("generation_skill/name") == skill)
    {
        me->set("set_skill/owner", "TEST_D");
        me->set("set_skill/time", time());
        message("vision", ob->name(1) + "点了点头，在" + me->name() +
                           "耳边小声说了几句话。\n", environment(me),
                                                     ({ me, ob }));
        tell_object(me, HIC + ob->name(1) + "点头道：你供测试用的技能被设定为『"
                        HIW + skill + HIC "』，等级为"
                        HIY + chinese_number(level_limit) +
                        HIC "级。\n" NOR);
        return 1;
    }
    else
    {
        message("vision", ob->name(1) + "摇了摇头，在" + me->name() +
                       "耳边小声说了几句话。\n", environment(me),
                                                 ({ me, ob }));
        tell_object(me, YEL + ob->name(1) + "疑惑的道：你是不是搞错了啊，有『"
                                          + skill + "』这种技能可选吗？\n" NOR);
        return 1;
    }
}
