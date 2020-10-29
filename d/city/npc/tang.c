#define TASK_DIR        "/task/"
#define TASK_OB_DIR     TASK_DIR + "obj/"
#define DEBUG(x)        tell_object(find_player("lonely"), x)
#define RATE 4


#include <ansi.h>

inherit BUNCHER;

mixed ask_back();

mapping *big_task;
string  *all_trade;

mixed   trade_task(int index);
string  ask_task(int index, string name);
mapping *query_big_task() { return big_task; }
string  *query_all_trade() { return all_trade; }

void create()
{
        set_name("唐楠", ({ "tang nan", "tang", "nan" }));
        set("title", "当铺老板");
        set("shen_type", 0);
        set("gender", "男性");
        set("age", 35);
        set("str", 1000);
        set("long", "据说唐楠是四川唐家的后代。\n");
        set("no_get_from", 1);

        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/attack", 30);
        set_temp("apply/damage", 15);

        set("combat_exp", 50000);
        set("attitude", "friendly");

        set("inquiry", ([
                "金轮九转" : (: ask_back :),
        ]));

        set_max_encumbrance(800000000000);
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

mixed ask_back()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) != "雪山寺" )
        {
                message_vision(CYN "$N" CYN "一脸茫然道：啥？刚才你说啥？\n" NOR,
                               this_object(), me);
                return -1;
        }

        message_sort(HIY "\n$N" HIY "看了看$n" HIY "，阴笑两声，随即在$n"
                     HIY "耳边低声说道：“小的早就为您老人家准备好了，就"
                     "在柜台后面，您快跟我来吧。”说罢$N" HIY "便领着$n"
                     HIY "快步朝后厅走去。\n\n" NOR, this_object(), me);
        me->move("/d/xueshan/midao");
        tell_object(me, CYN + name() + "说道：就是这里，你一直走南就行了。\n"
                        HIC + name() + "说完便急急忙忙赶了回去。\n" NOR);
        return -1;
}

void unconcious()
{
        die();
}

void die()
{
        message_vision("\n$N死了。\n", this_object());
        destruct(this_object());
}

string ask_task(int index, string name)
{
        string* trades = keys(big_task[index]["trade"]);
        string msg = "如果你能够给我";
        for(int i = 0; i < sizeof(trades); i++)
                msg += trades[i] + ((i < (sizeof(trades) - 2)) ?
                        "、" : ((i < (sizeof(trades) - 1)) ?
                        HIC "和" NOR : HIC "的话，我就把" + name + HIC + "给你。" NOR));
        return msg;
}

mixed trade_task(int index)
{
        object who = this_player();
        object me = this_object();
        object ob;
        string* trades = keys(big_task[index]["trade"]);
        string file_name;

        for(int i = 0; i < sizeof(trades); i++) {
                   ob = present(big_task[index]["trade"][trades[i]], who);
                   //if( !objectp(ob) || !query("task_ob", ob) )
                   if( !objectp(ob) || !ob->is_task() )
                        return "等你拿到了" + trades[i] + "再说吧。";
        }

        for(int i = 0; i < sizeof(trades); i++) {
                message_vision("$N拿出" + trades[i] + "给$n。\n", who, me);
                TASK_D->finish(present(big_task[index]["trade"][trades[i]], who), who);
                destruct(present(big_task[index]["trade"][trades[i]], who));
        }
        file_name = big_task[index]["file_name"];
        ob = find_object(TASK_OB_DIR + file_name);
        if(!objectp(ob)) ob = load_object(TASK_OB_DIR + file_name);
        ob->move(who);
        set("big_task", 1, ob);
        set("task_ob", 1, ob);
        message_vision("$N拿出" + ob->name() + "给$n。\n", me, who);

        return -1;
}

void add_big(string arg, int i)
{
        string name;
        object task_ob;

        task_ob = find_object(TASK_OB_DIR + arg);
        if(!objectp(task_ob)) task_ob = load_object(TASK_OB_DIR + arg);
        name=query("name", task_ob);

        big_task[i] = (["file_name" : arg,
                        "name" : name,
                        "trade" : 0,
                ]);

        set("inquiry/" + filter_color(name), (: ask_task, i, name :));
        set("inquiry/兑换" + filter_color(name), (: trade_task, i :));
        all_trade[sizeof(all_trade)-i-1]=query("id", task_ob);
        destruct(task_ob);
}

void task_announce()
{
        string msg = "近日得到：";
        mapping *task = TASK_D->query_task();
        int k, task_s = sizeof(task);

        for(int i = 0; i < sizeof(big_task); i++) {
                for(int j = 0; j < RATE; j++) {
                        k = random(task_s);
                        if(member_array(task[k]["id"], all_trade) != -1) {
                                j--;
                                continue;
                        }
                        if(!mapp(big_task[i]["trade"])) big_task[i]["trade"] = ([task[k]["name"] : task[k]["id"]]);
                        else big_task[i]["trade"] += ([task[k]["name"] : task[k]["id"]]);
                        all_trade[i * RATE + j] = task[k]["id"];
                }
                msg += big_task[i]["name"] + ((i < (sizeof(big_task) - 2)) ?
                        "、" : ((i < (sizeof(big_task) - 1)) ?
                        HIC "和" NOR : HIC "，不知哪位江湖朋友需要。" NOR));
        }
        set("inquiry/兑换", "我这里有" + msg[10..<34] + "可以和你交换。");
        command("chat " + msg);
}

void clean_big_task(int n)
{
        delete("inquiry");
        set("inquiry/金轮九转", (: ask_back :));
        big_task = allocate(n);
        all_trade = allocate(n*RATE + n);
}
