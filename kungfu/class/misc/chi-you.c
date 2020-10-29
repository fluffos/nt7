inherit BOSS;
#include <ansi.h>

void check_weapon();

void create()
{
        object staff;
        
        set_name("蚩尤巨像", ({ "chi you", "chiyou" }) );
        set("race", "人类");
        set("gender", "男性");
        set("age", 10000);
        set("long", "蚩尤，与黄帝涿鹿中原的一代大神，鬓如剑戟，头有利角，铜头铁额，诛杀 
无道，乃古往今来睥睨天下之第一凶魔！他的头顶，有一根放射出万道金华
的[37m法杖[32m没顶而插\n");
        set("title", "不世战神");
        set("nickname", HIR"万古凶魔"NOR);
        
        set("NO_KILL","你无法攻击一具石像。\n"); 
        set("attitude", "peaceful");

        set("per", 21);
        set("str", 300);
        set("int", 300);
        set("con", 300);
        set("dex", 300);

        set("qi", 20000000000);
        set("max_qi", 20000000000);
        set("jing", 10000000000);
        set("max_jing", 10000000000);
        set("neili", 130000000000);
        set("max_neili", 130000000000);
        set("jiali", 30000);

        set("combat_exp", 15000000000);
        set("score", 0);
        set_skill("force", 4800);
        set_skill("moshen-xinfa", 4800);
        set_skill("chiyou-kuangzhanjue", 4800);
        set_skill("dodge", 4800);
        set_skill("moshen-bufa", 4800);
        set_skill("jiutian-xiaoyaobu", 4800);
        set_skill("strike", 4800);
        set_skill("moshen-zhangfa", 4800);
        set_skill("cuff", 4800);
        set_skill("moshen-quanfa", 4800);
        set_skill("sword", 4800);
        set_skill("moshen-jianfa", 4800);
        set_skill("liuxing-jianfa", 4800);
        set_skill("blade", 4800);
        set_skill("moshen-daofa", 4800);
        set_skill("moon-blade", 4800);
        set_skill("parry", 4800);
        set_skill("literate", 4800);
        set_skill("medical", 4800);
        set_skill("mojiao-medical", 4800);
        set_skill("motun-tianxia", 4800);
        set_skill("martial-cognize", 4800);

        map_skill("force", "chiyou-kuangzhanjue");
        map_skill("dodge", "jiutian-xiaoyaobu");
        map_skill("strike", "moshen-zhangfa");
        map_skill("cuff", "moshen-quanfa");
        map_skill("sword", "liuxing-jianfa");
        map_skill("blade", "moon-blade");
        map_skill("parry", "moon-blade");

        prepare_skill("strike", "moshen-zhangfa");

        set("no_nuoyi", 1); // 不被挪移影响
        
        set("my_life", 1); // 当气血低于10%的时候补满一次，设置该参数为0
        set("staff", 1);
        
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.ting" :),
                (: perform_action, "blade.yue" :),
                (: exert_function, "recover" :),
        }) );
        
        set("rewards", ([
                "exp"   : 800000,
                "pot"   : 400000,
                "mar"   : 80000,
                "weiwang" : 10000,
                "score" : 10000,
                "gold"  : 3000,
        ]));

        set("drops", ([
                "FI&/clone/tessera/rune29"      : 10,
                "FI&/clone/tessera/rune30"      : 1,
                "FI&/clone/goods/luck_ring"      : 1,
                "FI&/clone/goods/luck_charm"      : 1,
                "FI&/clone/goods/luck_neck"      : 1,
                "FI&/clone/tongren/tongren"+(1+random(2)) : 500,
        ]));
        
        set_temp("apply/attack", 1000000);
        set_temp("apply/unarmed_damage", 100000);
        set_temp("apply/damage", 100000);
        set_temp("apply/armor", 60000);

        set_temp("apply/reduce_damage", 80);
        set_temp("apply/avoid_busy", 66);
        set_temp("apply/reduce_busy", 66);
        set_temp("apply/add_busy", 25);
        set_temp("apply/reduce_poison", 80);
                                
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/kungfu/class/mojiao/obj/blade")->wield();
}

void init() 
{
        if (query("staff"))
                add_action("do_pull", "pull");
        if (interactive(this_player()) && !query("NO_KILL")){
                kill_ob(this_player()); 
                this_player()->kill_ob(this_object());
        }
}

string staff()
{
        object me;
        me = this_player();
        if(query("staff")){
                tell_object(me, YEL"\n
一柄由万载菩提木制成的法杖，一大半已深深插入蚩尤巨像头顶，但露出的一部分
依旧光华夺目，不知道是否能拔出来（pull)；据传上古时黄帝斩杀蚩尤巨凶后，
唯恐其亡魂不散，特向佛祖借来这万年菩提杖插入蚩尤石像，以镇住这不世之凶，
万世不得翻身。\n\n"NOR);
        } else {
                tell_object(me, "大神蚩尤像头顶的法杖已然不见，只剩一个空洞。\n");
        }
        return "";
}

int do_pull(string arg)
{
        object me, staff;
        int damage;
        me = this_player();
        
        if(!arg || (arg != "staff" && arg != "法杖")) {
                return notify_fail("你要拔什么？\n");
        }
        if(!query("staff")) {
                return notify_fail("已经没有法杖了。\n");
        }
        if(query("qi",me) < 100) {
                return notify_fail("你没有足够的气血。\n");
        }
        if(query("jiali",me) > 80 && me->query_str() > 30 ) {
                message_vision("$N双手紧紧握住菩提法杖，牙关一咬，虎口鲜血迸射，怒喝一声：起！！\n", me);
                message_vision(HIY"\n菩提法杖突然放出万道金华，七色彩晕，山摇地动之间，法杖应声而起，冲天而出！\n"NOR,
                                me);  
        set("long", "蚩尤，与黄帝涿鹿中原的一代大神，鬓如剑戟，头有利角，铜头铁额，诛杀 
无道，乃古往今来睥睨天下之第一凶魔！\n");
                set("staff", 0);
                me->start_busy(3);
                call_out("stone_fall", 3, me);
        } else {
                message_vision("$N双手紧紧握住菩提法杖，牙关一咬，虎口鲜血迸射，怒喝一声：起！！\n", me);
                message_vision("菩提法杖纹丝不动。\n", me);
                me->start_busy(3);
                damage = query("qi",me) / 5;
                me->receive_damage("qi", damage);
        }
        return 1;
}

void stone_fall(object me)
{
        object *all, *inv, room, obj;
        int i;
        
        all = all_inventory(environment(this_object()));
        
        message_vision("\n突然之间蚩尤秘窟有如天崩地裂般，浓云翻滚，电闪雷鸣，山石又如疾风暴雨般\n", me);        
        message_vision("漫天砸下！\n", me); 
        message_vision("\n$N神色大变，奋起全力在乱石风暴中苦苦寻求一线生机。\n", me);
        
        inv = filter_array(all, (: interactive($1):));
        for(i=0; i<sizeof(inv); i++) {
                message_vision(HIY"$N被这突如其来的变化惊的目瞪口呆，只见无数巨石狠狠地砸了过来，\n"NOR, inv[i]);
                message_vision(HIY"当真是挡无可挡躲无可躲。\n"NOR, inv[i]);
                if(inv[i]->query_skill("dodge",1)>=1500 && inv[i]->query_skill("parry",1)>=1500){
                        message_vision(HIG"\n在这间不容发的情况下$N躲过了巨石的攻击。\n"NOR, inv[i]);
                } else {
                        tell_object(inv[i], "你左挡右躲向前奔跑期望躲过巨石的袭击。\n");
                        me->start_busy(3);
                        
                        message_vision(RED"\n$N一个躲闪不及，无数巨石狠狠地砸了过来。。。\n"NOR, inv[i]);          
                        inv[i]->unconcious(me);
                }
        }
        
        remove_call_out("chiyou");
        call_out("chiyou", 3, me);
        
}

void chiyou(object ob)
{
        object *all, *inv;
        int i;
        
        if(!interactive(ob) && environment(ob) != this_object()){
                set("staff",1);
                return;
        }
        message_vision(HIB"\n漫天乱石中，狂风乍起，天色变得一片狰狞，仿佛无数厉鬼野兽在咆哮怒吼！\n"NOR, ob);
        message_vision(HIR"\n鲜红如血般的大火熊熊燃起，一片火海中升起一个高达百尺，有如天神般的巨汉！\n"NOR,ob); 
        message_vision(HIR"远处，近处，空气中每一处地方无数的凶灵邪兽齐声膜拜，狂呼！！\n\n"NOR, ob);
        message_vision(HIY"              －－不－世－战－神－－蚩－尤－重－生－－  \n\n"NOR, ob);
        
        delete("NO_KILL");      
        set("name","蚩尤");
        
        all = all_inventory(environment(this_object()));
        inv = filter_array(all, (: interactive($1):));
        for(i=0; i<sizeof(inv); i++) {
                kill_ob(inv[i]);
                inv[i]->kill_ob(this_object());
                }
}

void heart_beat()
{
        // 解除不能perform yun的限制
        if (random(3) == 1)
        {
                delete_temp("no_perform");
                delete_temp("no_exert");
        }

        if (random(3) == 1)check_weapon();

        return ::heart_beat();
}

// 检查武器
void check_weapon()
{
        object me, ob;

        me = this_object();

        // 同时补充内力
        set("neili", query("max_neili"));

        if (me->is_busy()) me->stop_busy();

        if (! query_temp("weapon"))
        {
                if( !objectp(ob = present("springrain blade", environment(me))) )
                ob = new("/kungfu/class/mojiao/obj/blade.c");
                ob->move(me);
                ob->wield();
        }

        if (random(5) >= 0) // 百分百
        {
                delete_temp("no_perform");
                delete_temp("no_exert");

                addn_temp("apply/damage", 50000);
                if (random(5) == 1)
                        command("perform balde.ting");
                else
                        command("perform blade.yue");
                addn_temp("apply/damage", -50000);

                if (random(2))
                {
                        delete_temp("eff/jiuyin-shengong/xin");
                }
        }

        if (random(10) == 1)
        {
                me->clear_condition();
        }

        // 很小几率恢复气血
        if (random(1000) == 1)
        {
                if (query("eff_qi") < query("max_qi") / 3) addn("eff_qi", query("max_qi") / 5);
                if (query("qi") < query("max_qi") / 3) addn("qi", query("max_qi") / 5);
        }

        if (! me->is_fighting() || random(5) == 1)
        {
                command("yun powerup");
        }

        return;
}

int accept_hit(object me)
{
        if( query("NO_KILL") ) return 0;
        this_object()->kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        if( query("NO_KILL") ) return 0;
        this_object()->kill_ob(me);
        return 1;
}

int accept_kill(object me)
{
        if( query("NO_KILL") ) return 0;
        this_object()->kill_ob(me);
        return 1;
}

int accept_ansuan(object me) 
{     
        if( query("NO_KILL") ) return 0;
        return notify_fail("那人警惕性好高，你难以下手。\n"); 
}

int accept_touxi(object who) 
{
        if( query("NO_KILL") ) return 0;
        return notify_fail("那人警惕性好高，你难以下手。\n"); 
}
        
void new_life()
{
        full_self(); // 补满气血

        delete_temp("no_perform");
        delete_temp("no_exert");

        set_temp("apply/attack", 1200000);
        set_temp("apply/unarmed_damage", 150000);
        set_temp("apply/damage", 150000);
        set_temp("apply/armor", 100000);

        delete("my_life");

        message_vision(HIG "\n$N" HIG "大喝一声，目光顿时充满杀意！\n\n" NOR, this_object());

        return;
}

void die(object killer)
{
        string prop, name;
        mapping data;
        object ob, where;
        string *apply = ({ "reduce_busy", "avoid_busy", "def_damage", "avoid_weak",
                "add_locked", "reduce_damage", "add_busy", "add_weak", "avoid_locked",
                "add_damage", "add_skill" });

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

        message_vision(HIR"\n$N嘶叫道：“可恶的。。。。我会再回来的。”"NOR, this_object());
        message_vision(HIR"$N那庞大身躯突然化为一股浓烟消失不见了。\n"NOR, this_object());

        return ::die(killer);
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
