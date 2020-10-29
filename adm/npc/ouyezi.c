// Written by Lonely@mud123.com

#include <ansi.h>
inherit NPC;

int ask_qiling();
void create()
{
        set_name("欧冶子", ({ "ouye zi", "zi" }) );
        set("nickname", RED "赤心剑胆" NOR );
        set("gender", "男性" );
        set("age", 60);
        set("long",
                "他头上包着头巾，三缕长髯飘洒胸前，面目清瘦但红晕有光，\n"
                "二目炯炯有神，烁烁闪着竟似是凛凛的剑光，浑身似乎都包围\n"
                "在一股剑气之中。\n");
        set("str", 25);
        set("dex", 20);
        set("con", 17);
        set("int", 30);
        set("shen_type", 0);
        set("max_neli",5000);
        set("jiali",50);
        set_skill("unarmed", 100);
        set_skill("dodge", 100);
        set_skill("jiuyin-baiguzhao",200);
        set_skill("force",150);
        set_skill("sword",150);
        set_skill("bibo-shengong",100);
        set_skill("luoying-shenjian",100);
        set_skill("parry",90);
        set_skill("anying-fuxiang",100);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage",50);
        
        set("combat_exp", 25000000);

        map_skill("force","bibo-shengong");
        map_skill("parry","luoying-shenjian");
        map_skill("sword","luoying-shenjian");
        map_skill("unarmed","jiuyin-baiguzhao");
        map_skill("dodge","anying-fuxiang");

        set("attitude", "peaceful");
        create_family("玄天派", 1, "弟子");
        
        set("inquiry", ([
                "铸剑" : "我已经很久很久没有铸剑了，你还是找我徒弟干将吧。\n",
                "启灵" : (: ask_qiling() :),
        ]) );
        setup();
        set("chat_chance", 3);
        set("chat_msg", ({
                "欧冶子抚剑而歌：巨阙神兵兮，人铸就。盖世宝剑兮，配英雄！\n",
                "欧冶子低头沉吟，似乎在思考什么。\n",
                "欧冶子低头沉思：我深信，每一把武器中都存在著一丝灵智。\n",
                "欧冶子叹了一口气：神兵配英雄，可英雄。。。。。。\n",
        }) );
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
        add_action("do_qiling", "qiling");
}

int ask_qiling()
{
        object me = this_player();
        object ob = this_object();

        message_vision(CYN "$N对$n" CYN "说道：每一把装备中都存在著一丝灵智，装备启灵需要以下物品。\n"
                "       1、银行存款黄金十万两\n"
                "       2、超能力水晶或装备之魂 1 个\n"
                "       3、无名之物或寰宇天晶 1 个（使用超能力水晶则不需要无名和天晶）\n"
                "       qiling <装备id> with <装备之魂>\n" NOR, ob, me);
        return 1;
}

int do_qiling(string arg)
{
        mapping props, data = ([]);
        object me;
        object ob, ob1, ob2;
        string item, what, type;
        string *apply;
        int i, status, qlvl, success, value;
        
        me = this_player();
        
        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg || sscanf(arg, "%s with %s", item, what ) != 2 )
                return notify_fail("给装备启灵指令格式：qiling <装备> with <装备之魂> \n");

        if( !objectp(ob = present(item, me)) )
                return notify_fail("你身上没有这样装备用来启灵。\n");
        
        if( query("equipped", ob) )
                return notify_fail("你先解除" + ob->name() + "的装备再说！\n");
                
        if( !ob->is_item_make() )
                return notify_fail("这样物品不能启灵品质。\n");
        
        if( query("qianghua/level", ob) < 7 )
                return notify_fail(ob->name()+"必须达到强化 7 级才能启灵。\n");                
        /*
        if( ob->item_owner() != query("id", me) )
                return notify_fail("这个，好象不属于你吧，这样不大合适。\n");
        */
        
        qlvl = query("status", ob);
        if( !qlvl ) 
        {
                set("status", 1, ob);
                qlvl = 1;
        }
        if( qlvl == 6 )
                return notify_fail(ob->name()+"已经成功产生器魂了，不需要继续启灵了。\n");
        
        // 需要装备之魂或超能力水晶
        if( !objectp(ob1 = present(what, me)) || (!ob1->is_equip_soul() && !ob1->is_spe_crystal()) )
                return notify_fail("你身上没有启灵需要的超能力水晶或装备之魂吧？\n");
        
        if( ob1->is_spe_crystal() && query("qiling_level", ob1) <= qlvl )
                return notify_fail("超能力水晶的能力储备不足以给"+ob->name()+NOR"装备启灵！\n");
                     
        if( ob1->is_equip_soul() )
        {                   
                // 需要无名之物
                if( !objectp(ob2 = present("no name", me)) && !objectp(ob2 = present("tian jing", me)) 
                ||      !ob2->is_qiling_ob() )
                        return notify_fail("你好象还没备齐无名之物或寰宇天晶吧？\n");
                
                type = query("type", ob1); // 装备之魂部位

                if( ob->is_weapon() )
                {
                        if( type != "weapon" )
                                return notify_fail("启灵"+ob->name()+NOR"需要武器之魂！\n");
                }
                else
                {
                        if( type != query("armor_type", ob) )
                                return notify_fail("启灵"+ob->name()+NOR"需要"+query("armor_type", ob)+"之魂！\n");
                }
         
                status = query("status", ob1); // 装备之魂等级
        
                if( status <= qlvl )
                        return notify_fail("你的装备之魂等级不够，无法用来给"+ob->name()+NOR"启灵！\n");
        }
        
        if( query("balance", me) < 1000000000 )
                return notify_fail("你的银行存款不足，启灵费用需要十万两黄金。\n");
                
        if( ob1->is_spe_crystal() )
        {
                if( ob->is_weapon() ) type = "weapon";
                else type = query("armor_type", ob);
        }

        if( qlvl == 1 ) success = 80;
        else if( qlvl == 2 ) success = 70;
        else if( qlvl == 3 ) success = 40;
        else if( qlvl == 4 ) success = 20;
        else if( qlvl == 5 ) success = 10;
        
        success += (status - qlvl) * 10;
        
        if( objectp(ob2) && query("id", ob2) == "tian jing" )
                success += 20;

        else if( objectp(ob2) && query("id", ob2) == "no name" )
                success += 30;
        
        if( random(100) < success )
        {
                if( objectp(ob1) && ob1->is_spe_crystal() && query("qiling_level", ob1) == qlvl+1 )
                        delete("qiling_level", ob1); // 消除超能力水晶上启灵等级的记录
                        
                addn("qiling/apply_prop/max_jing", 1000*(qlvl+1), ob);     // 增加精
                addn("qiling/apply_prop/max_qi", 2000*(qlvl+1), ob);       // 增加气
                
                addn("status", 1, ob);

                if( type == "rings" || type == "neck" || type == "charm" )
                {
                        addn("qiling/apply_prop/research_effect", 5, ob);
                        addn("qiling/apply_prop/derive_effect", 5, ob);
                        addn("qiling/apply_prop/practice_effect", 5, ob);
                }

                tell_object(me, HIC "你感受" + ob->name() + HIC "发生了不可言喻的变化。\n" NOR); 
                if( query("status", ob) == 6 )
                {
                        if( type == "rings" || type == "neck" || type == "charm" )
                        {
                                addn("qiling/apply_prop/research_effect", 25, ob);
                                addn("qiling/apply_prop/derive_effect", 25, ob);
                                addn("qiling/apply_prop/practice_effect", 25, ob);
                                tell_object(me, HIC "成功开启"+ob->name()+"灵智，" + ob->name() + HIC "的研究、汲取、练习的效果提高了3%。\n" NOR); 
                        }
                        else if( ob->is_weapon() || ob->is_unarmed_weapon() )
                        {
                                data = query("qiling/apply_prop", ob);
                                data["fatal_blow"]   = 10;
                                data["leech_qi"]     = 20;
                                data["leech_neili"]  = 20;
                                set("qiling/apply_prop", data, ob);

                                tell_object(me, HIC "成功开启"+ob->name()+"灵智，" + ob->name() + HIC "拥有致命一击属性。\n" NOR); 
                        }
                        else
                        {
                                data = query("qiling/apply_prop", ob);
                                data["full_self"]    = 5;
                                data["avoid_die"]    = 5;
                                set("qiling/apply_prop", data, ob);

                                tell_object(me, HIC "成功开启"+ob->name()+"灵智，" + ob->name() + HIC "拥有战神附体和浴血重生属性。\n" NOR); 
                        }
                        /*
                        data=query("weapon_prop", ob);
                        if( !mapp(data) ) data = query("armor_prop", ob);
                        apply = keys(data);
                        for(i=0; i<sizeof(apply); i++)
                                set("qiling/apply_prop", data[apply[i]] * 2, ob); // 属性不重复
                        */
                        if( query("weapon_prop/damage", ob) )
                                set("qiling/apply_prop/damage", query("weapon_prop/damage", ob) * 2, ob); // 属性不重复
                        if( query("armor_prop/unarmed_damage", ob) )
                                set("qiling/apply_prop/unarmed_damage", query("armor_prop/unarmed_damage", ob) * 2, ob); // 属性不重复
                        if( query("armor_prop/armor", ob) )
                                set("qiling/apply_prop/armor", query("armor_prop/armor", ob) * 2, ob); // 属性不重复
                                
                        addn("enchase/flute", 1, ob);
                        CHANNEL_D->do_channel(this_object(), "chat", HIC "不想千年之后，终于见到传说中的具有灵智的神器，实在是死而无憾也！\n" NOR);
                }
                ob->save();
                MYGIFT_D->check_mygift(me, "newbie_mygift/qiling");      
        }
        else
                tell_object(me, HIW "很遗憾，启灵失败。\n" NOR);
        
        addn("balance", -1000000000, me);
   
        if( objectp(ob1) && !ob1->is_spe_crystal() ) 
        {
                destruct(ob1);
                if( objectp(ob2) ) destruct(ob2);
        }
        ob->save();
        return 1;
}

void kill_ob(object ob)
{
        ::kill_ob(ob);
        message_vision("$N冷笑一声，道：“这年头，什么人都有。”说完伸手一指$n。\n",
                       this_object(), ob);
        ob->unconcious();
}

int accept_fight(object who)
{
        command("say 没兴趣。");
        return 0;
}

int accept_ansuan(object who)
{
        return notify_fail("你刚想暗算，可是眼前一花，看不太清楚。\n");
}

void receive_damage(string type, int n)
{
        return;
}

void receive_wound(string type, int n)
{
        return;
}
