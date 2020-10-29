//biaotou.c
//镖头.c 

inherit NPC;

#include <ansi.h>
void init();
int ask_start();
int ask_arrived();

mapping default_dirs = ([ //root:在此定义移动方向。
        "north":                "北",
        "south":                "南",
        "east":                 "东",
        "west":                 "西",
        "northup":              "北边",
        "southup":              "南边",
        "eastup":               "东边",
        "westup":               "西边",
        "northdown":            "北边",
        "southdown":            "南边",
        "eastdown":             "东边",
        "westdown":             "西边",
        "northeast":            "东北",
        "northwest":            "西北",
        "southeast":            "东南",
        "southwest":            "西南",
        "up":                   "上",
        "down":                 "下",
        "enter":                "里",
        "out":                  "外",
]);

void create()
{
        set("title","运镖天下");
        set_name(HIC "镖头" NOR, ({ "biao tou", "tou" }));
        set("nickname",HIW "一招毕命" NOR);
        set("long","他是一个驰骋江湖数十年的老镖师。\n");
        set("gender", "男性");
        set("age", 54);
        
        set("food",250);
        set("water",250);

        set("no_get",1);

        set("inquiry", ([
                "出发" : (: ask_start :),
                "抵达" : (: ask_arrived :),
        ]));
        set("chat_chance_combat", 60);

        setup();

        carry_object(__DIR__"obj/pixue")->wear();
        carry_object(__DIR__"obj/tiejia")->wear();
        carry_object(__DIR__"obj/gangjian")->wield();
}
int accept_hit(object ob)
{
        command("say 毛都没长齐学人劫镖？去死吧！");
        command("perform sword.lian");
        kill_ob(ob);
        return 1;
}
int accept_kill(object ob)
{
        command("say 毛都没长齐学人劫镖？去死吧！");
        command("yun recover");
        return 1;
}


void init()
{
        add_action("do_move","move");
}

int do_move(string arg)
{
        object me, ob, env;
        mapping exit;
        int busy, kar, i;
        me = this_player();
        ob = this_object();
        env = environment(me);
        kar = 20 + random(10);

        if( !living(ob) )
              return notify_fail("嗯....你得先把" + ob->name() + "弄醒再说。\n");

        if (ob->query_temp("owner/id") != me->query("id")) {
                command("? " + me->query("id"));
                return notify_fail("\n");
                }
        
        if (!arg) {
                command("kick " + me->query("id"));
                command("say 你要我赶到哪儿去？");
                return notify_fail("\n");
                }

        if( !mapp(exit = env->query("exits")) || undefinedp(exit[arg]) ) {
                command("?");
                command("say 这个方向没有路呃。");
                return notify_fail("\n");
                }

        if (ob->is_busy()) {
                command("say 我这儿正忙着呢！");
                return notify_fail("\n");
                }

        if (me->is_busy()) {
                command("say 你自己都忙不过来，还催我干什么？");
                return notify_fail("\n");
                }

        if (ob->is_fighting()) {
                command("say 请你先把我的对手料理了吧！\n");
                return notify_fail("\n");
                }

        command("go " + arg); 
        ob->start_busy(2 + random(2));
        me->move(environment(ob));
        message_vision(HIC "镖头用警惕的眼光观察着四周。\n" NOR,me);
        busy = 2 + random(30 - kar);
        if (busy > 3) busy = 3;
        me->start_busy(busy);
//        i = 30;
//        if ( random(i) < 15){
        ob = new(__DIR__"robber");
        ob->invocation(me);
        
        call_out("robber", 1);

        message_vision(HIR "突然，一个劫匪从暗处窜了出来！！！\n\n" NOR,me);

        ob->move(environment(me));
                 
        return 1;
        } 


int ask_start()
{
        object ob = this_object(), me = this_player();

        if (ob->query_temp("started")) {
                command("say 不是已经在路上了吗？");
                return 1;
                }

        if (me->query("quest/yunbiao") ==1) {
                ob->set_temp("started",1);
                ob->set_temp("owner/id",me->query("id"));
                command("say 好吧，我们出发！");
                return 1;
                }
        
        if (ob->query_temp("owner/id") != me->query("id")) {
                command("slap " + me->query("id"));
                command("say 又没有让你护镖，来瞎闹什么？");
                return 1;
                }
        call_out("leave", 600);
        me->set("task_time", 600);
        return 1;
}

int ask_arrived()
{
        object me, ob;
        int exp, pot, ww;
        
        me = this_player();
        ob = this_object();

        if (ob->query_temp("owner/id") != me->query("id")) {
                command("say " + me->query("name") + "你并没有护这趟镖，凭什么来领取奖励？");
                command("grin " + me->query("id"));
                return 1;
                }

        if (ob->is_busy()) {
                command("say 我这儿正忙着呢！");
                return notify_fail("\n");
                }

        if (ob->is_fighting()) {
                command("say 请你先把我的对手料理了吧！\n");
                return notify_fail("\n");
                }

        if (ob->query_temp("fuzhou") ==1){
                 if (file_name(environment(ob)) !="/d/fuzhou/biaojuzt") {
                         command("say 你想半途而废？");
                       return 1;
                       }

                if (!present("lin zhennan", environment(ob))) {
                       command("say 总镖头不在，不好交差啊！");
                       return 1;
                       }

   }
   else {
                if (file_name(environment(ob)) !="/d/city/qianzhuang") {
                command("say 你想半途而废？");
                return 1;
                }

                if (!present("qian yankai", environment(ob))) {
                        command("say 钱老板不在，不好交差啊！");
                        return 1;
                           }
        }
        me->set("quest2/yunbiao",0);
        ww = (50 + random(50));
        exp = (100 + random(30)) * 10;
        pot = (500 + random(exp)) * 6 / 10;
        message_vision(HIW "$N被奖励了：\n"
                + HIG + chinese_number(exp) + "点实战经验，\n"  
                + HIC + chinese_number(pot) + "点潜能，\n"
                + HIY + chinese_number(exp * pot / 500000) + "两黄金，\n" 
                + HIW + chinese_number(ww) + "点江湖威望，\n"NOR,me); 

        me->add("combat_exp",exp);
        me->add("potential",pot);
        me->add("balance",(exp * pot/50));
        me->add("weiwang",ww);

        message_vision(CYN "镖师往钱庄里间离去了。\n" NOR,me);
        destruct(ob);

        return 1;
}

