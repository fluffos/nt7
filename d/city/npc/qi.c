// qi.c 戚长发

#include <ansi.h>
#include <command.h>

inherit NPC;
inherit F_DEALER;

int do_answer();

void create()
{
        set_name("戚长发", ({ "qi changfa", "qi" }));
        set("title", "躺尸剑门传人");
        set("nickname", HIR "宰人不用刀，" HIC "愿" HIR "者上钩" NOR);

        set("gender", "男性");
        set("age", 48);
        set("str", 100);
        set("long",
                "戚老板最近是爆发横财，所谓是三年不开张，开张管三年。\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("higgling", 800);
        set_temp("apply/damage", 15);

        set("combat_exp", 800000);
        set("attitude", "friendly");

        set("inquiry", ([
                "宝物" : (: do_answer :),
                "买卖" : (: do_answer :),
                "生意" : (: do_answer :),
                "东西" : "扔掉就没了！嘿嘿。",
                "还我钱"     : "哼！我这里是有进无出！",
                "我的钱"     : "什么你的钱，地上的就是我的！",
                "钱"         : "想钱啊？自己去挣！",
                "我的东西"   : "扔掉就没了！嘿嘿。",
                "赎"         : "赎？没得赎！",
                "天王保命丹" : "卖！卖！五百两黄金一粒！",
                "翡翠兰"     : "可治百毒啊！有气就能活！",
                "朱睛冰蟾"   : "虽然不象翡翠兰那样可起死回生，但是能解百毒！",
                "讨价还价"   : "和我学(higgling)... 我很穷啊！",
                "higgling"   : "和我学讨价还价么... 我很穷啊！",
        ]));

        set("vendor_goods", ([
                "/d/item/obj/xuantie"     : "3000000",
                "/d/item/obj/butian"      : "8000000",
                "/d/item/obj/wujins"      : "3000000",
                "/d/item/obj/tiancs"      : "8000000",
                //"/clone/medicine/baoming" : "3000000",
                //"/clone/medicine/jiuhua"  : "3000000",
                "/d/shenlong/obj/hua4"    : "30000000",
                "/clone/misc/zhujingchan" : "20000000",
                "/clone/gift/shenliwan"   : "100000000",
                "/clone/gift/xisuidan"    : "100000000",
                "/clone/gift/xiandan"     : "100000000",
                "/clone/gift/unknowdan"   : "100000000",
                "/clone/misc/dymo"        : "5000000",
                "/clone/item/magicfruit"  : "200000000",
                "/clone/gift/kardan"      : "5000000",
                "/clone/gift/perwan"      : "5000000",
                "/clone/gift/huirongwan"   : "50000000",
                "/clone/gift/htdan"   : "50000000",
                "/clone/fam/pill/food1"   : "100000",
                "/clone/goods/washgift"   : "10000",
                "/clone/goods/dizangshi"   : "10000",
                "/clone/goods/zhufu_sword"   : "1000000",
                "/clone/goods/zhufu_blade"   : "1000000",
                "/clone/goods/zhufu_staff"   : "1000000",
                "/clone/goods/zhufu_whip"   : "1000000",
                "/clone/goods/zhufu_hammer"  : "1000000",
                "/clone/goods/zhufu_finger"   : "1000000",
                "/clone/goods/zhufu_hand"   : "1000000",
                "/clone/goods/zhufu_armor"   : "1000000",
                "/clone/goods/zhufu_cloth"   : "1000000",
                "/clone/goods/zhufu_head"   : "1000000",
                "/clone/goods/zhufu_boots"   : "1000000",
                "/clone/goods/zhufu_surcoat"   : "1000000",
                "/clone/goods/zhufu_waist"   : "1000000",
                "/clone/goods/zhufu_wrists"   : "1000000",
                "/adm/npc/obj/gift"   : "1000000",
                "/clone/goods/jhunshi"   : "1000000",
                "/clone/goods/magic-silk"   : "1000000",
                "/adm/npc/obj/giftbox" : "10000",
                "/clone/goods/duihuanjuan" : "10000",
                "/adm/npc/obj/remove-symbol" : "10000",
        ]));

        setup();
        set_max_encumbrance(100000000);
        if (clonep()) keep_heart_beat();
}

void init()
{
        add_action("do_buy", "buy");
        add_action("do_list", "list");
        add_action("do_drop", "drop");
        add_action("do_look", ({"guankan", "kan"}));
}

void heart_beat()
{
        string start_room;
        object ob;

        if (stringp(start_room = query("startroom")) &&
            find_object(start_room) == environment())
        {
                foreach (ob in all_inventory(environment()))
                {
                        if (! ob->is_character() ||
                            interactive(ob) || playerp(ob) ||
                            query_temp("owner", ob) )
                                continue;

                        if( stringp(start_room=query("startroom", ob)) &&
                            find_object(start_room) == environment())
                                continue;

                        message_vision("$N皱了皱眉，把$n推了出去。\n",
                                       this_object(), ob);
                        ob->move("/d/city/beidajie1");
                }
        }

        ::heart_beat();
}

int do_drop(string arg)
{
        int i;
        object *obs;
        object ob;
        object me;

        if (! arg)
                return 0;

        me = this_player();
        if (objectp(ob = present(arg, me)) &&
            ob->is_character() && ! playerp(ob))
        {
                addn_temp("static/drop_npc", 1, me);
                if( query_temp("static/drop_npc", me)>1 &&
                    query("combat_exp", me) >= 50000 )
                {
                        message_vision("$N大怒道：：“好你个" +
                                       RANK_D->query_rude(ob) +
                                       "，还来添乱！”\n说罢只见$N"
                                       "飞起一脚，将$n和" + ob->name() +
                                       "一起踢出门外。\n", this_object(), me);
                        ob->move("/d/city/beidajie1");
                        me->move("/d/city/beidajie1");
                        message("vision", "只听叮叮咣光一阵向，" + me->name() +
                                          "被人一脚踢了出来。\n",
                                environment(me), me);
/*
                        me->receive_damage("qi", 1);
                        me->die();
*/
                        return 1;
                }

                message_vision("$N怒道：“滚开，少给我添乱，影响我的生意。”\n"
                               "说罢只见$N飞起一脚，将$n和" + ob->name() +
                               "一起踢出门外。\n", this_object(), me);
                ob->move("/d/city/beidajie1");
                me->move("/d/city/beidajie1");
                message("vision", "只听叮叮咣光一阵向，" + me->name() +
                                  "被人一脚踢了出来。\n",
                        environment(me), me);
/*
                me->receive_damage("qi", 1);
                me->unconcious();
*/
                return 1;
        }

/*
        if (! DROP_CMD->main(me, arg))
                return 0;

        if (! GET_CMD->main(this_object(), arg))
                return 1;
*/

        if (objectp(ob) && ! ob->is_character()) destruct(ob);
        obs = all_inventory(this_object());
        for (i = 0; i < sizeof(obs); i++)
                if (! obs[i]->is_character()) destruct(obs[i]);
        if (! random(5))
        {
                switch (random(4))
                {
                case 0:
                        command("say 日积月累，小康之路！");
                        break;
                case 1:
                        command("kok "+query("id", this_player()));
                        command("say 随地乱扔垃圾，罚款五元！");
                        break;
                case 2:
                        command("say 败家子，败家子！");
                        break;
                default:
                        command("heihei");
                        break;
                }
        }
        return 1;
}

int do_answer()
{
        write(name() + "在你耳边轻声说道：我");
        ::do_list();
        write("这可真是货真价实，童叟无欺啊！\n");
        return 1;
}

int accept_object(object who, object ob)
{
        if( query("money_id", ob) )
        {
                if( !query_temp("mark/戚", who) )
                        set_temp("mark/戚", 0, who);

                if( query("money_id", ob) && ob->value() >= 10000 )
                {
                        message_vision("$N同意指点$n一些讨价还价得的技巧。\n",
                                       this_object(), who);
                        addn_temp("mark/戚", ob->value()/100, who);
                        destruct(ob);
                        return 1;
                }
                command("say 你这点钱... 我虽然穷可还真看不上！");
                return -1;
        }

        switch (random(6))
        {
        case 0:
                command("say 好！好！");
                break;
        case 1:
                command("say 不要就给我！");
                break;
        }

        if (! ob->is_character())
        {
                destruct(ob);
                return -1;
        }

        return 1;
}

void unconcious()
{
        message_vision("\n$N哼哼两声，道：“困死了...哦！”\n",
                       this_object());
        full_self();
}

void die()
{
        message_vision("\n$N大叫一声，道：“痛死啦！”连忙掏出天王保命丹吃了两颗。\n",
                       this_object());
        full_self();
}

int recognize_apprentice(object ob, string skill)
{
        if( query_temp("mark/戚", ob)<1 )
                return 0;

        if (skill != "higgling")
                return 0;

        addn_temp("mark/戚", -1, ob);
        return 1;
}
