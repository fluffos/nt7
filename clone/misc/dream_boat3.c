#include <ansi.h>
#define MEMBER_D "/adm/daemons/memberd"

inherit ITEM;

int last_update_boss;

string *nature_message = ({
        "远处传来阵阵海浪声，船身轻轻地摇晃了几下，随即风平浪静。\n",
        "天空传来数声雷鸣，风云突变，乌云黑压压的一片笼罩着上空。\n",
        "你放眼望去，一群海豚尾随着船，正在跳跃嬉戏，海面波光粼粼，甚是美丽。\n",
        "几声惊雷过后，天空突然下起雨来，海浪滔天，船身剧烈地摇晃着。\n",
        "风雨过后，天空突然放晴，一群海鸥从天边飞来，映衬着远出的彩虹，真是人间美景。\n",
        "你站在船头，一阵海风吹过，清新扑面，闭上双眼，感觉浑身舒泰无比。\n",
        "周围依然是无边的海洋，海浪拍打着帆船，海风吹过，将帆鼓得满满地。\n",
        });

void start_heart_beat()
{
        // 默认为心跳1
        set_heart_beat(1);
}

void create()
{
        set_name(HIW "仙境号帆船（开往未知地点）" NOR, ({ "penglai boat"}));
        set_weight(2000);
        set_max_encumbrance(10000000);
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
                set("no_rideto", 1);
                set("no_clean_up", 1);

                set("stop_time", time()); // 靠岸的时间
                set("waiting_time", 300); // 默认等船时间
                set("running_time", 300); // 默认行使时间为十五分钟

                set("source_place", "/d/xiakedao/haibin"); // 出发地
                set("dest_place", "/d/penglai/haitan"); // 目的地
                set("dest_place_name", "蓬莱仙岛");
                set("source_place_name", "南海之滨");

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
        object *inv;
        object horse, person;
        int i;

        ob = this_player();
        if( arg != query("id", this_object()) )
        {
                tell_object(ob , "你要 enter 哪儿？\n");
                return 1 ;
        }

        if (ob->is_busy())
                return notify_fail("你正忙。\n");
                
        // 所有骑马的人必须下马
        if (objectp(horse = query_temp("is_riding", ob)))
        {
                if( objectp(person=query_temp("is_rided_follow", horse)) )
                        delete_temp("is_riding_follow", person);

                delete_temp("is_rided_follow", horse);
                delete_temp("is_rided_by", horse);
                delete_temp("is_riding_follow", ob);
                delete_temp("is_riding", ob);
                

                message_vision(HIR "\n$N的" + horse->name() + HIR " 似乎无法跃上帆船，前蹄一扬，所有人"
                               "被迫跳下马。\n\n" NOR, ob);

                return 1;
        }

        // 把背起的用户放下来
        inv = deep_inventory(ob);
        for (i = 0; i < sizeof(inv); i++)
        {
                if (! playerp(inv[i])) continue;

                // 被人背起的用户
                inv[i]->move(environment(this_object()));                
        }

/*
        // 暂时只对500万EXP以下的非转世会员开放
        if( (!MEMBER_D->is_valib_member(query("id", ob)) || 
            query("scborn/ok", ob)) && !wizardp(ob) )
                return notify_fail("船夫(chuanfu)道：公开测试期间，这船暂时只针对非转世会员开放。\n");
*/                                
        if (environment(ob) == this_object())
                return notify_fail("船夫(chuanfu)道：你已经在船上了，怎么，想跳下海？\n");

        if (! ob->move(this_object()))return notify_fail("这位客官，船已经坐不下了，等下班吧！\n");

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
                object *inv, *obs;
                object ob, ob_boss;
                string now_place_name;
                int left_time;

                //keep_heart_beat(1);

                if (! environment(this_object()))return;

                set_name(HIW "仙境号帆船（开往" + query("dest_place_name") + "）" NOR, query("id"));

                left_time = query("waiting_time") - (time() - query("stop_time"));
                left_time /= 60;
                if (query("running"))
                {
                        // 随机出现描述
                        if (random(30) == 1)
                        {
                                message_vision(HIC + nature_message[random(sizeof(nature_message))] + NOR, this_object()); 
                        }
                        
                        if (time() - query("start_time") >= query("running_time") / 2 )        
                        {                
                                set("long", HIR "\n船夫(chuanfu)吆喝道：我们的船正在行使中，已行使超过路程的一半，请耐心等候。\n" NOR);                        
                                if ((time() - last_update_boss >= 1800) && random(4) == 7 )
                                {
                                        ob_boss = new("/d/penglai/npc/qingmianshou");
                                        if (ob_boss->move(this_object()))        
                                        {
                                                message_vision(HIB "突然，风起浪涌，只见天空一团黑雾飘过，船身剧烈晃动，恍惚间，一只巨兽已经站在"
                                                               "你面前。\n" NOR, this_object()); 
                                                       CHANNEL_D->do_channel(this_object(), "rumor", "听说" HIG "青面兽" + HIM "从蓬莱仙岛逃出，上了仙境号帆船。" NOR);
                                        }
                                        last_update_boss = time();
                                }
                                
                        }
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
/*
                                        if (ob_boss = find_living("qingmian shou"))
                                        {
                                                destruct(ob_boss);
                                        }
*/
                                        // 到岸并设置玩家startroom
                                        foreach(ob in obs)
                                        {
                                                //if (ob->query("id") == "qingmian shou")destruct(ob);
                                                ob->move(environment(this_object()));
                                                //set("startroom", base_name(environment(this_object())), ob);
                                                ob->save();
                                        }
                                        // 重新设置名称和源，目的地点
                                        now_place_name = query("dest_place_name");
                                        set("dest_place", query("source_place"));
                                        set("dest_place_name", query("source_place_name"));

                                        set("source_place", base_name(environment(this_object())));
                                        set("source_place_name", now_place_name);

                                        
                                        // 靠岸时间
                                        set("stop_time", time());                                        
                                        addn("runtimes", 1);
                                        
                        }
                        return;
                }
                else // ! running
                {
                        if( query("runtimes") >= 4 )
                        {
                                message_vision(HIC "船夫(chuanfu)吆喝道：停航了，停航了，终于可以回家抱媳妇去了 ……\n" NOR, this_object());
                                destruct(this_object());
                                return;
                        }
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
