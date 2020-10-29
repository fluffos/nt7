#include <ansi.h>

inherit ITEM;

void start_heart_beat()
{
        // 默认为心跳1
                set_heart_beat(1);
}

void create()
{
        set_name(HIW "巨型帆船（开往未知地点）" NOR, ({ "china918"}));
        set_weight(200000);
        set_max_encumbrance(1000000);
        /*if (clonep())
        {
                set_default_object(__FILE__);
        }
        else*/
        {
                set("value", 1);
                                
                                if (query("running"))
                                    set("long", HIR "\n船夫(chuanfu)吆喝道：我们的船正在行使中，请耐心等候。\n" NOR);
                                else
                                        set("long", HIC "\n船夫(chuanfu)吆喝道：我们的船正在等待中，你可以先在船上休息（enter）。\n" NOR);

                                set("item_desc", ([
                                        "chuanfu" : "这是一位经验丰富船夫，正忙得不可开焦。\n",
                                ]));
                                set("no_flyto", 1);
                                set("no_clean_up", 1);

                                set("stop_time", time()); // 靠岸的时间
                                set("waiting_time", 600); // 默认等船时间
                                set("running_time", 600); // 默认行使时间为十分钟

                                set("source_place", "/d/shenlong/haitan"); // 出发地
                                set("dest_place", "/b/tulong/haigang"); // 目的地
                                set("dest_place_name", "日本岛");
                                set("source_place_name", "东海之滨");

                set("unit", "艘");
                set("material", "wood");
                set("no_get", "船夫(chuanfu)喝道：好家伙，这你也想扛在肩上？\n");
                                
        }
        setup();        
                start_heart_beat();
}

void init()
{
        add_action("do_enter", "enter");
                add_action("do_out", "out");
}

int do_enter ( string arg )
{
        object ob;
        string dir;

        ob = this_player();
        if (arg != this_object()->query("id"))
        {
                tell_object(ob , "你要 enter 哪儿？\n");
                return 1 ;
        }

                if (environment(ob) == this_object())
                        return notify_fail("船夫(chuanfu)道：你已经在船上了。\n");
                
        ob ->move(this_object());

                tell_object(ob, HIG "船夫(chuanfu)对你说道：要下船请输入 out 。\n" NOR);

        return 1 ;
}

int do_out()
{
                object me = this_player();

                if (environment(me) != this_object())return 0;
                
                if (query("running"))
                        return notify_fail("已经开船了！\n");
                
                me->move(environment(this_object()));
                
                return 1;
}

void heart_beat()
{
                //object me = find_player("rcwiz");
                object *inv, *obs;
                object ob;
                string now_place_name;
                int left_time;

                if (! environment(this_object()))return;

                set_name(HIW "巨型帆船（开往" + query("dest_place_name") + "）" NOR, query("id"));

                left_time = query("waiting") - (time() - query("stop_time"));
                left_time /= 60;
                if (query("running"))
                {
                        if (time() - query("start_time") >= query("running_time") / 2 )                        
                                set("long", HIR "\n船夫(chuanfu)吆喝道：我们的船正在行使中，已行使超过路程的一半，请耐心等候。\n" NOR);                        
                        else
                                set("long", HIR "\n船夫(chuanfu)吆喝道：我们的船正在行使中，请耐心等候。\n" NOR);
                }
                else
                        set("long", HIC "\n船夫(chuanfu)吆喝道：我们的船正在等待中(开船剩余" + sprintf("%d", left_time) + "分钟)，你可以先在船上休息（enter）。\n" NOR);
                
                inv = all_inventory(this_object());
                obs = filter_array(inv, (: userp($1) :)); // 过滤掉非玩家物件

                // 正在行使中计算靠岸时间是否达到
                if (query("running"))
                {
                        // 到站了
                        if (time() - query("start_time") >= query("running_time"))
                        {
                                        set("stop_time", time()); // 设置到站时间
                                        this_object()->move(query("dest_place"));
                                        delete("running");
                                        message_vision(HIC "船夫(chuanfu)吆喝道：客官们小心哟，船靠岸了 ……\n" NOR, this_object());
                                        foreach(ob in obs)
                                        {
                                                ob->move(environment(this_object()));                                                
                                        }
                                        // 重新设置名称和源，目的地点
                                        now_place_name = query("dest_place_name");
                                        set("dest_place", query("source_place"));
                                        set("dest_place_name", query("source_place_name"));

                                        set("source_place", base_name(environment(this_object())));
                                        set("source_place_name", now_place_name);

                                        // 靠岸时间
                                        set("stop_time", time());                                        
                                        
                        }
                        return;
                }
                else // ! running
                {
                        // 开船了
                        if (time() - query("stop_time") >= query("waiting_time"))
                        {
                                set("start_time", time());
                                set("running", 1);
                                message_vision(HIC "船夫(chuanfu)吆喝道：小心啦，船起航了 ……\n" NOR, this_object());
                                this_object()->move("/clone/misc/sea");
                        }
                        return;
                }
                

}
