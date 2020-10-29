
#include <ansi.h>

inherit ITEM;

int is_zhangpeng() { return 1;}

void create()
{
        set_name(HIC "单人帐篷" NOR, ({ "danren zhangpeng", "danren", "zhangpeng"}) );
        set_weight(2000);
                set_max_encumbrance(1000000);
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("value", 1000000);
                set("long", HIC "这是一个单人帐篷，你可以打开帐篷来休息（指令：openzp)。\n" NOR);
                set("unit", "个");
                                set("no_hand", 1);
                                set("no_steal", 1);
                                set("no_clean_up", 1);
        }
        setup();
}

void init()
{
                add_action("do_open", "openzp");
                add_action("do_close", "closezp");
                add_action("do_out", "outzp");
                add_action("do_enter", "enterzp");
}

// 进入帐篷
int do_enter()
{
                object me, ob;

                me = this_player();
                ob = this_object();
                
                if (ob->query("opening") != me->query("id"))
                        return notify_fail("你目前无法进入这个帐篷。\n");

                if (environment(me) == ob)
                        return notify_fail("你不是已经进来了吗？\n");

                me->move(ob);
                
                message_vision(HIC "$N一头钻进" + ob->name() + HIC "。\n" NOR, me);

                return 1;
}

// 出帐篷
int do_out()
{
                object me, ob;

                me = this_player();
                ob = this_object();

                if (environment(me) != ob)
                        return notify_fail("你并没有在帐篷里啊。\n");

                if (! ob->query("out"))
                        return notify_fail("目前无法出帐篷。\n");

                message_vision(HIC "$N钻出帐篷。\n" NOR, me);

                me->move(ob->query("out"));

                return 1;                        
}

// 打开帐篷
int do_open()
{
                object me;
                object env;
                object obt, obj;
                object *obs;

                me = this_player();

                if (environment(this_object()) != me)return 0;
                                
                if (me->query("danren_zhangpeng/flag"))
                {
                        return notify_fail("你已经有单人帐篷被打开了，不能再打开帐篷。\n");
                }
                
                if (this_object()->query("opening"))
                                return notify_fail("帐篷不是打开的么？\n");

                env = environment(me);

                if (env->is_zhangpeng())
                                return notify_fail("这个地方不能再打开单人帐篷了。\n");        

                if (! env->query("outdoors"))
                                return notify_fail("帐篷只能在户外打开。\n");
                
                if (me->is_busy() || me->is_fighting())
                                return notify_fail("你现在正忙于做其他事情，无法打开帐篷。\n");
                
                // 一个地点只能开一个帐篷
                obs = all_inventory(env);
                
                foreach(obj in obs)
                {
                        if (obj->is_zhangpeng())
                        {
                                return notify_fail("这个地方已经有人摆帐篷了，你还是换个地方吧。\n");
                        }
                }
                
                obt = new("/clone/fam/item/zhangpeng");

                // 设置主人
                obt->set("opening", me->query("id"));                
                obt->set("no_get", 1);
                
                // 设置描述
                obt->set("long", HIW "这是一个单人帐篷，你可以收起帐篷(指令：closezp）。\n"
                                 HIW "****如果觉得闷了可以到外面透透气(outzp），进入帐篷使用指令（enterzp）。\n" NOR);

                // 设置特殊属性
                obt->set("sleep_room", 1);
                obt->set("no_fight", 1);

                // 设置出口
                obt->set("out", file_name(env));

                message_vision(HIC "$N打开" + this_object()->name() + HIC "一头钻了进去。\n" NOR, me);

                me->move(obt);
                obt->move(env);

                // 设置特殊标志
                me->set("danren_zhangpeng/flag", 1);
                me->set("danren_zhangpeng/ob", obt);
                
                me->save();

                destruct(this_object());

                return 1;
}

int do_close(string arg)
{
                object me, obt;
                object *obs;
                object obj, newob;

                me = this_player();
                obt = this_object();

                if (! obt->query("opening"))
                                return notify_fail("单人帐篷不是关闭着的么？\n");

                if (obt->query("opening") != me->query("id"))
                                return notify_fail("你没有权利收起这个帐篷。\n");

                // 复制一个帐篷给该玩家
                newob = new("/clone/fam/item/zhangpeng");
                
                message_vision(HIW "$N将帐篷收了起来，装进行囊。\n" NOR, me);

                // 检查负重
             if (newob->query_weight() + me->query_encumbrance() >= me->query_max_encumbrance())
                {
                                tell_object(HIR "对不起，你的负重不足，无法收起这个帐篷。\n" NOR);
                                destruct(newob);
                                return 1;
                }

                // 想将帐篷里的人移出来，然后摧毁帐篷，最后复制一个帐篷给该玩家
                obs = all_inventory(obt);

            // 将帐篷里的人都移出来
                if (sizeof(obs))
                {
                        foreach(obj in obs)
                        {
                                obj->move(environment(obt));
                        }
                }

        // 将复制的帐篷给该玩家
                newob->move(me, 1);

                me->delete("danren_zhangpeng");

                me->save();
                // 摧毁这个帐篷
                destruct(this_object());

                return 1;
                
}

int query_autoload()
{
                return 1;
}