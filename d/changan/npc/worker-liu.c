// worker-liu.c

inherit NPC;

#include <ansi.h>

// 接收的货物
#define CHECK_GOODS     "cuprum_ore"

void create()
{
        set_name("刘工匠", ({ "liu gongjiang", "liu", "worker" }) );
        set("title", HIY "天国大匠" NOR);
        set("gender", "男性" );
        set("age", 52);
        set("str", 33);
        set("long", @LONG
一个毫不起眼的老匠人，但是却有着难以言喻的威严。从旁边学徒工
人们的眼神中你感觉他不是一般的人物。
LONG);
        set("attitude", "friendly");

        setup();

        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        set_heart_beat(1);
}

int filter_ob(object ob)
{
        object owner;

        if (! ob->is_transport())
                return 0;

        owner = ob->query_owner();
        if (! objectp(owner))
                // 该车无主
                return 0;

        if (environment(owner) != environment())
                // 主人不在
                return 0;

        if( query_temp("goods/id", ob) != CHECK_GOODS )
                // 没有装载铜矿石
                return 0;

        if( query_temp("goods/amount", ob)<1 )
                // 没有货
                return 0;

        return 1;
}

void heart_beat()
{
        object *obs;
        object ob;
        object owner;
        string startroom;
        int amount;
//      mapping job;
        mapping goods;
//      object bonus;

        ::heart_beat();
        if (! environment())
                return;

        if (! stringp(startroom = query("startroom")) ||
            find_object(startroom) != environment())
                // 不在出生地点
                return;

        obs = all_inventory(environment());
        obs = filter_array(obs, (: filter_ob :));
        if (sizeof(obs) < 1)
        {
                // 没有到达合适的车辆，停止心跳
                set_heart_beat(0);
                return;
        }

        // 到达了合适的车辆
        ob = obs[0];
        owner = ob->query_owner();
        message_vision("$N看到$n押货而来，连连点头道：“很"
                       "好！很好！就卸到这里吧！”\n",
                       this_object(), owner);
        tell_object(owner,"你卸下"+query_temp("goods/name", ob)+
                    "，将" + ob->name() + "交给学徒拉走。\n");

        // 卸下铜矿石
        goods=query_temp("goods", ob);
        amount = goods["amount"];
        environment()->improve_product_amount(goods["id"], amount);

        // 给与奖励
        MONEY_D->pay_player(owner, amount * 10);
        tell_object(owner, "你领到了一些工钱。\n");
        if( query_temp("job/owner", ob) == owner )
        {
                // 这个是本人领的工作，获得奖励
                GIFT_D->work_bonus(owner, ([ "exp" : 10000 + random(5000),
                                        "pot" : 5000 + random(3000),
                                        "score" : 30 + random(50),
                                        "prompt" : "通过这次押送" + goods["name"] + HIG ]));

                // 去掉我做这个工作的信息
                delete("job/"+query_temp("job/info", ob), owner);
        }
        destruct(ob);

        if (sizeof(obs) < 2)
        {
                // 已经处理完毕，没有新的车辆到达，停止心跳
                set_heart_beat(0);
        }
}