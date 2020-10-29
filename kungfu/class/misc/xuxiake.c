// xuxiake.c 徐霞客

#include <ansi.h>

inherit NPC;

mixed ask_map();

void create()
{
        set_name("徐霞客", ({ "xu xiake", "xu" }));

        set("gender", "男性");
        set("age", 45);
        set("long",
                "他早年走遍天下，见识了无数的美景奇观，对山川地理莫不了如指掌。\n");

        set("attitude", "friendly");
        set("inquiry", ([
                "地图" : (: ask_map :),
                "map"  : (: ask_map :),
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

mixed ask_map()
{
        object me, ob;
        mapping map;
        string *ks;
        string msg;
        string str;
        int n;
        object obn;

        ob = this_object();
        me = this_player();
        if( !query("out_family", me) )
        {
                message_vision("$N微微一笑，对$n道：“你身上带了地图册么？”\n",
                               ob, me);
                return 1;
        }

        if( query("map_all", me) )
        {
                message_vision("$N笑道：“" + RANK_D->query_respect(ob) +
                               "，你的地图册已经收录了全集了，不如到处多走走吧。”\n",
                               ob, me);
                return 1;
        }

        if( !mapp(map=query("map", me)) )
                return "哦？你这本地图册还全是白纸呢！";

        // 查看那些地方没有绘制
        ks = (string *) MAP_D->query_all_map_zone() - keys(map);
        if (sizeof(ks) < 1)
        {
                n = 0;
                foreach (str in keys(map))
                        n += sizeof(map[str]);
                if (n < 200)
                {
                        message_sort("$N接过$n的地图册，仔细翻了一会儿，叹道：“"
                                     "我看过你绘制的地图册了，收录的地点倒是满全"
                                     "的，可惜很多地方记载不祥，你自己好好再看看"
                                     "吧。”\n", ob, me);
                        return 1;
                }

                message_sort("$N接过$n的地图册，仔细翻了一会儿，凝思良久，又翻阅"
                             "了一阵，不由得喜上眉梢，对$n赞道：“实在不曾想到这"
                             "世上还有人能像我一样走遍名山大川，难得，难得！嗯，"
                             "我看你的地图册中还有少许缺漏，这就给你补全吧，日后"
                             "你或许还用得上。”说完，$N随手拿起笔，在$n的地图册"
                             "上补了几笔，还给了$n。\n", ob, me);
                delete("map", me);
                set("map_all", 1, me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                                      "听说"+me->name(1)+"("+query("id", me)+
                                      ")向徐霞客讨教地理山川知识，获得了地图全集。");
                addn("potential", 30000, me);
                addn("score", 20000, me);
                addn("weiwang", 20, me);
                obn = new("/clone/gift/xuanhuang");
                obn->move(me, 1);
                if (! query("zhufu_mod/cloth", me)) 
                {
                        message_vision("$n对$N微微一笑，道：干得不赖，有点" 
                                       "意思，这个神之祝福战衣就算是我送给你的礼物吧。\n",
                                       me, this_object());
                        obn = new("/clone/goods/zhufu_cloth"); 
                        obn->move(me, 1);
                        tell_object(me, HIM "\n你获得了一个" + obn->name() + HIM "！\n" NOR);
                        set("zhufu_mod/cloth", 1, me); 
                }
                tell_object(me, HIG "你仔细翻阅了地图全集，思索许久，收获良多，获"
                                "得了三万点潜能、两万点江湖阅历和一个练功仙丹。\n" NOR);
                return 1;
        }

        if (sizeof(ks) > 3) ks = ks[0..2];
        ks = map_array(ks, (: MAP_D->query_map_short($1) :));
        msg = "$N接过$n的地图册，仔细翻了一会儿，皱眉道：“以我看来，"
              "你这里面绘制的地图还相当不全呢，至少" +
              implode(ks, "、") + "就没有收录在内。”\n";
        message_sort(msg, ob, me);
        return 1;
}
