// This program is a part of NT MudLIB
// redl 2014
// 余英男

#include <ansi.h>

inherit BOSS;

void del_busy();
int hand_throw();

int get_helpkill()
{
        object me = this_player(), ob = this_object();

                if (time() - query("jldong/killshu_time", me) < 600) {
                        message_vision(CYN + query("name") + NOR + CYN + "愤怒地对$N说道：几分钟前才见你杀害我的同门姐妹，贼子，拿命来！\n"+ NOR, me); 
                        ob->kill_ob(me);
                        if (!me->is_busy()) me->start_busy(3);
                return 1;
                }
                
                if (ob->is_fighting() || ob->is_busy()) {
                tell_object(me,CYN + query("name") + NOR + CYN + "慢悠悠地对你说道：没见我正在忙吗？\n"+ NOR); 
                return 1;
                }
        
        if( query("shen", me) < 2000000){
                        tell_object(me,CYN + query("name") + NOR + CYN + "傲慢地说：你非我大峨眉的正道人士...\n"+ NOR); 
                return 1;
        }      

        if( query("level", me) < 50){
                        tell_object(me,CYN + query("name") + NOR + CYN + "面孔扭曲地说：就阁下这小身板也想配？...\n"+ NOR); 
                return 1;
        }      

        if( !query_temp("xue/xin/killed", me) ){
                        tell_object(me,CYN + query("name") + NOR + CYN + "悄悄对你说：你去除掉辛辰子，我就将这齐师姐的秘法传授与你。\n"+ NOR); 
                return 1;
        }      

                if( query("can_perform/yitian-jian/zhen", me) ) {
                        tell_object(me,CYN + query("name") + NOR + CYN + "悄悄对你说：这招我不是已经教过你了吗？自己下去多练吧！\n"+ NOR); 
                        return 1;
                }
                if( query("family/family_name", me) != "峨嵋派" ) {
                        tell_object(me,CYN + query("name") + NOR + CYN + "悄悄对你说：你是哪里来的？快给我滚开！\n"+ NOR); 
                        return 1;
                }
                if( me->query_skill("yitian-jian", 1) < 300 ) {
                        tell_object(me,CYN + query("name") + NOR + CYN + "悄悄对你说：你连倚天剑法都没学好，还谈什么九天伏魔剑阵？\n"+ NOR); 
                        return 1;
                }
                if( query("family/gongji", me)< 1000000 ) {
                        tell_object(me,CYN + query("name") + NOR + CYN + "悄悄对你说：你在本派中无所作为，这一招我暂时还不能传你。\n"+ NOR); 
                        return 1;
                }

      
             message_sort(HIY "\n$n" HIY "微微点了点头，不露半点声色，将$N" HIY 
                          "招至跟前，在耳边秘密的说了些什么。$N" HIY "听后会心的" 
                          "一笑，似乎明白了什么。\n\n" NOR, me, this_object()); 
      
             command("say 以后对那些妖人不要手软，一上来就用这招！"); 
             tell_object(me, HIC "你学会了「九天伏魔剑阵」。\n" NOR); 
             if (me->can_improve_skill("sword")) 
                     me->improve_skill("sword", 1500000); 
             if (me->can_improve_skill("yitian-jian")) 
                     me->improve_skill("yitian-jian", 1500000); 
             me->improve_skill("martial-cognize", 1500000); 
             set("can_perform/yitian-jian/zhen", 1, me); 
             addn("family/gongji", -1000000, me); 

        return 1;
}      

int accept_object(object me, object obj)
{
        int amount;
        object sword, ob = this_object();

                if (ob->is_fighting() || ob->is_busy()) {
                tell_object(me,CYN + query("name") + NOR + CYN + "慢悠悠地对你说道：没见我正在忙吗？\n"+ NOR); 
                return 1;
                }
        
        switch (query("id", obj))
        {                       
         case "no name":
                if (base_name(obj) == "/clone/goods/noname") {
                        if (query("give_sword")) {
                                tell_object(me,CYN + query("name") + NOR + CYN + "慢悠悠地对你说道：我已经收到有缘人的赠予了。\n"+ NOR); 
                                return 0;
                        }
                        sword = query("my_sword");
                        if (!sword) {
                                tell_object(me,CYN + query("name") + NOR + CYN + "慢悠悠地对你说道：我给不了你什么。\n"+ NOR); 
                                return 0;
                        }
                        sword->unequip();
                        if (sword->move(me)) {
                                set("give_sword", 1);
                                set("owner_ob", me, sword);
                                message_vision(CYN + query("name") + NOR + CYN + "接过$N的无名之物，递还了一个剑匣子作为答谢。\n"+ NOR, me); 
                                return 1;
                        }
                        tell_object(me,CYN + query("name") + NOR + CYN + "慢悠悠地对你说道：我给不了你什么。\n"+ NOR); 
                        return 0;
                } else {
                        tell_object(me,CYN + query("name") + NOR + CYN + "慢悠悠地对你说道：这个东西是高仿的吗？\n"+ NOR); 
                        return 0;
                }
         default:
                return 0;
        }
        
}

void create()
{
        set_name(CYN "余英男" NOR, ({ "yu yingnan", "yu", "yingnan" }) );
        set("title", HIG "蜀山" HIC "剑侠" NOR);
        set("long", HIR "这是传说中的蜀山第三代精英弟子，此来是为了除魔修炼，顺带寻访无名之物铸剑。\n" NOR);

        set("gender", "女性");
        set("age", 25);

        set("str", 900);
        set("int", 900);
        set("con", 900);
        set("dex", 1000);
        set("shen", 7000000);
        set_temp("apply/attack", 1200000);
        set_temp("apply/unarmed_damage", 150000);
        set_temp("apply/damage", 150000);
        set_temp("apply/armor", 50000);

        set("max_qi", 30000000000);
        set("eff_qi", 30000000000);
        set("qi", 30000000000);
        set("max_jing", 15000000000);
        set("jing", 15000000000);
        set("eff_jing", 15000000000);
        set("max_jingli", 500000000);
        set("jingli", 500000000);
        set("max_neili", 2500000000);
        set("neili", 2500000000);
        set("jiali", 10000);
        set("combat_exp", 5000000000);
        set("level", 120 + random(30));

        set_skill("unarmed", 22000);
        set_skill("finger", 22000);
        set_skill("claw", 22000);
        set_skill("strike", 22000);
        set_skill("hand", 22000);
        set_skill("cuff", 22000);
        set_skill("parry", 22000);
        set_skill("dodge", 22000);
        set_skill("force", 22000);
        set_skill("sword", 22000);
        set_skill("blade", 22000);
        set_skill("throwing", 22000);
        set_skill("zuoyou-hubo", 1000);

        set_skill("lonely-sword", 15000 + random(9999));
        set_skill("jiuyang-shengong", 15000 + random(9999));
        set_skill("yinyang-shiertian", 15000 + random(9999));
        set_skill("tanzhi-shentong", 15000 + random(9999));
        set_skill("qiankun-danuoyi", 13000 + random(4000));
        set_skill("martial-cognize", 15000 + random(5000));
        set_skill("count", 6000 + random(3000));
        set_skill("lingbo-weibu", 15000 + random(9999));
        set_skill("literate", 5000);
        set_skill("huajia-su", 1500);

        set_skill("jingluo-xue", 5000);
        set_skill("qimen-wuxing", 1000);

        set("no_nuoyi", 1); // 不被挪移影响
        set("yuanshen", 1); //无招
        set("lonely-sword/nothing", 1); //无招
        set("yinyang-shiertian/shier", 12);
        set("yinyang-shiertian/yinyang", 12);
        set("yinyang-shiertian/qiankun", 12);

        map_skill("parry", "qiankun-danuoyi");
        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "lingbo-weibu");
        map_skill("unarmed", "yinyang-shiertian");
        map_skill("finger", "tanzhi-shentong");
        map_skill("throwing", "tanzhi-shentong");
        map_skill("strike", "yinyang-shiertian");
        map_skill("hand", "yinyang-shiertian");
        map_skill("cuff", "yinyang-shiertian");
        map_skill("claw", "yinyang-shiertian");
        map_skill("sword", "lonely-sword");

        prepare_skill("finger", "tanzhi-shentong");

        set("can_perform/qiankun-danuoyi/yi", 1);
        set("can_perform/lonely-sword/yi", 1);
        set("can_perform/lonely-sword/po", 1);
        set("can_perform/lonely-sword/jian", 1);
        set("can_perform/lonely-sword/qi", 1);
        set("can_perform/tanzhi-shentong/ding", 1);
        set("can_perform/tanzhi-shentong/dian", 1);
        set("can_perform/tanzhi-shentong/po", 1);

/*         set("chat_chance", random(7) + 3);
         set("chat_msg", ({
                (: random_move :),
                (: random_move :),
                (: command("kill xixue bianfu") :),
                (: command("kill xixue bianfu") :),
                (: command("kill xixue bianfu") :),
                (: command("say 如果我有充足的天师符，对上那老魔时倒也稳当了许多。") :),
         }));*/

        // yun perform
        set("chat_chance_combat", 115);
        set("chat_msg_combat", ({
              (: command("perform sword.jian") :),
              (: command("perform sword.qi and sword.yi") :),
              (: command("perform sword.po and sword.yi") :),

              (: command("perform sword.po and sword.qi") :),
              (: command("perform finger.dian and finger.ding") :),
              (: command("perform finger.po and finger.ding") :),
              (: command("perform finger.po and finger.dian") :),
                          (: command("perform finger.po and parry.yi") :),
                          (: command("perform parry.yi and parry.yi") :),
              (: exert_function, "powerup" :),
              (: exert_function, "shield" :),
              (: exert_function, "recover" :),
              (: exert_function, "dispel" :),
              (: del_busy :),
              //(: command("kill xixue bianfu " + (string)(random(9)+1)) :),
        }));

        set("my_life", 3); // 当气血低于10%的时候补满一次，设置该参数为0

        //set("auto_perform", 1);
        //set("end_time", 60);  // 必须战斗不少于60秒后死亡
        set("rewards", ([
                "exp"   : 500000,
                "pot"   : 250000,
                "mar"   : 100000,
                "weiwang" : 20000,
                "score" : 20000,
                "gold"  : 10000,
        ]));

/*        set("drops", ([
                "FI&/clone/medal/diamond_xunzhang"       : 1,
                "FI&/clone/medal/yongshi_xunzhang"      : 10,
                "FI&/clone/fam/max/longjia"       : 100,
        ]));*/

        set_temp("apply/reduce_damage", 78);
        set_temp("apply/reduce_busy", 35);
        set_temp("apply/add_busy", 10);
        set_temp("apply/add_poison", 60);

        set("inquiry", ([
                "九天伏魔剑阵" : (: get_helpkill :),
        ]));

        set("n_flee", 7200);
        setup();

                set("hand_throwing", "/d/chengdu/npc/obj/flower-leaf");
        carry_object("/kungfu/class/quanzhen/obj/greyrobe")->wear();
        carry_object(__DIR__"obj/hairpin")->wear();
        //carry_object(__DIR__"obj/tnmjian")->wield();
        set("my_sword", new(__DIR__"obj/tnmjian"));
        set("owner_ob", this_object(), query("my_sword"));
        //query("my_sword")->move(this_object(), 1);
        //query("my_sword")->wield();
        set("give_sword", 0);
        hand_throw();

//        set("startroom", "/d/jianzhong/maigu");
}

int hand_throw()
{
        object ob, me = this_object();
        
        if (query_temp("handing")) return 1;
        if (!query("hand_throwing")) return 1;

        ob = new(query("hand_throwing"));
        if( ob->query_amount() ) {
                ob->set_amount(999);
        }
        
        ob->move(me, 1);
        command("hand " + query("id", ob));
        return 1;
}

void heart_beat()
{
                object sword, me = this_object();
        if( query("n_flee") < 1 ){
                        message_vision(CYN + query("name") + NOR + CYN + "仰天长叹：看来此番魔道气数未尽，罢了，罢了...\n"+ NOR + 
                                                                                query("name") + NOR + YEL + "说完掐了个剑诀，紧抿嘴皮用力顿足，乘着一道剑光冲天而去。\n" + NOR, me); 
                                destruct(this_object());                                                                            
                return;
        }      
        addn("n_flee", -1);
        if (random(3) == 1)
        {
            delete_temp("no_perform");
            delete_temp("no_exert");
                    hand_throw();
                    if (this_object()->is_fighting() && !random(100)) {
                        command("unwield lihuo jian");
                        command("drop lihuo jian");
                        command("perform finger.zhuan");//call die()绝杀一次
                    }
        }
                if (!this_object()->is_fighting() && !random(10)) {
                        me->stop_busy();
                        command("halt");
                        me->stop_busy();
            command("yun powerup");
            me->stop_busy();
                        full_self(); // 补满气血
                }
        return ::heart_beat();
}

void del_busy()
{
        object me = this_object();
        if (random(8)) return;
        if (me->is_busy()) me->interrupt_busy(me, 1000);
        if (me->is_busy()) me->interrupt_me(me);
        if (me->is_busy()) me->stop_busy();
        if (me->is_busy()) me->interrupt_busy(me);
}

int accept_hit(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_kill(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

void new_life()
{
        full_self(); // 补满气血
                del_busy();
        delete_temp("no_perform");
        delete_temp("no_exert");

        addn_temp("apply/attack", query_temp("apply/attack") * 2);
        addn_temp("apply/unarmed_damage", query_temp("apply/unarmed_damage") / 2);
        addn_temp("apply/damage", query_temp("apply/damage") / 2);
        addn_temp("apply/armor", query_temp("apply/armor") * 2);

        addn("my_life", -1);
        message_vision(HIG "\n$N" HIG "娇呼一声燃起天师符，瞬间神光四湛！\n\n" NOR, this_object());
        return;
}

int receive_damage(string type, int damage, object who)
{
        object *ppl;

        if( !who ) who = this_object()->query_last_damage_from();
        if( !who ) return;
        ppl = query_temp("damage_from");
        if( !arrayp(ppl) || !sizeof(ppl) ) ppl = ({});
        if( userp(who) && member_array(who, ppl) == -1 )
        {
                ppl += ({ who });
                set_temp("damage_from", ppl);
        }

        if (query("my_life") && query("qi") < query("max_qi") / 10)
        {
                new_life(); // 重生一次
                return 0;
        }

        return ::receive_damage(type, damage, who);
}

void die(object killer)
{
        string prop, name;
        mapping data;
        object sword, ob, where;

/*        string *apply = ({ "reduce_busy", "avoid_busy", "def_damage", "avoid_weak",
                "add_locked", "reduce_damage", "add_busy", "add_weak", "avoid_locked",
                "add_damage", "add_skill" });*/

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                full_self();
                return;
        }

        if( !objectp(killer) ) killer = this_object()->query_last_damage_from();
        if( !objectp(killer) ) killer = query_temp("last_damage_from");

        // 如果还未重生，则重生一次
        if (query("my_life"))
        {
                new_life();
                return;
        }

        if( time() < query_temp("end_time") ) // 时间没有到，死亡不了
        {
                addn("jing", query("max_jing") / 10);
                if( query("jing") > query("max_jing") ) set("jing", query("max_jing"));
                addn("eff_jing", query("max_jing") / 10);
                if( query("eff_jing") > query("max_jing") ) set("eff_jing", query("max_jing"));
                addn("qi", query("max_qi") / 10);
                if( query("qi") > query("max_qi") ) set("qi", query("max_qi"));
                addn("eff_qi", query("max_qi") / 10);
                if( query("eff_qi") > query("max_qi") ) set("eff_qi", query("max_qi"));
                //message_vision(HIR "\n$N" HIR "大喝一声，运用秘法，气血有所回升！\n\n" NOR, this_object());
                return;
        }

/*              if (new(__DIR__"obj/tnmjian")->move(killer, 1)) {
                message_vision(HIR "叮~~一声，从$N" HIR "身上掉出一个剑匣子，$n" HIR
                                   "赶紧拣起来揣到怀里。\n" NOR, this_object(), killer);
                        set("jldong/killshu_time", time() , killer);
        }*/
        message_vision(CYN + query("name") + NOR + CYN + "捂住嘴角的" + NOR + HIR + "鲜血" + NOR + CYN + "道：看来此番魔道气数未尽，罢了，罢了...\n"+ NOR + 
                        query("name") + NOR + YEL + "说完掐了个剑诀，紧抿嘴皮用力顿足，乘着一道剑光冲天而去。\n" + NOR, this_object()); 

                        sword = query("my_sword");
                        if (killer && sword && !query("give_sword")) {
                                set("give_sword", 1);
                                set("owner_ob", killer, sword);
                                tell_object(killer, NOR + "你发现空中落下一个小小的剑匣子，赶紧捡了起来..\n"+ NOR); 
                                sword->reset_wield();
                        }

                destruct(this_object());                                                                                
                return;
        //return ::die(killer);
}

varargs void unconcious(object defeater)
{
        object ob;

        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
        die(defeater);
        return;
}

/*// 不会被busy
varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        return;
}*/
