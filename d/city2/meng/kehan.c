#include <ansi.h>
inherit BOSS;

int do_kill(string arg);
int is_stay_in_room() { return 1; }

void create()
{
        int skill, nl;
        int exp;

        set_name("蒙古可汗",({ "menggu kehan", "kehan"  }));
        set("gender", "男性" );
        set("long", "这就是此次领兵南侵的蒙古可汗。\n");

        set("int", 30);
        set("str", 60 + random(20));
        set("con", 20 + random(20));
        set("dex", 20 + random(20));
        set("age", 20 + random(30));
        set("per", 20 + random(10));
        set("no_get", 1);
        set("env/auto_war", 1);

        exp = UPDATE_D->query_max_exp();
        skill = to_int(pow(to_float(exp/100), 1.0 / 3)) * 10;
        skill += 200;
        nl = skill * 10 + (exp / 10000);

        set("combat_exp", exp);
        set("max_neili", nl*10);
        set("neili", query("max_neili") * 3 / 2);
        set("max_jingli", nl);
        set("jingli", query("max_jingli"));
        set("max_qi", nl * 100);
        set("eff_qi", query("max_qi"));
        set("qi", query("eff_qi"));
        set("max_jing", nl);
        set("eff_jing", query("max_jing"));
        set("jiali", skill / 2);

        set_skill("longxiang-gong", skill);
        set_skill("xuedao-daofa", skill);
        set_skill("shenkong-xing", skill);
        set_skill("dashou-yin", skill);
        set_skill("hand", skill);
        set_skill("force", skill);
        set_skill("dodge", skill);
        set_skill("blade", skill);
        set_skill("parry", skill);
        set_skill("arrow", skill*2/3);

        map_skill("force", "longxiang-gong");
        map_skill("dodge", "shenkong-xing");
        map_skill("hand",  "dashou-yin");
        map_skill("parry", "xuedao-daofa");
        map_skill("blade", "xuedao-daofa");

        prepare_skill("hand", "dashou-yin");

        set("my_life", 200000);
        set_temp("warquest/party", "meng");

        addn_temp("apply/armor", 6000);
        addn_temp("apply/defense", 1000);
        addn_temp("apply/attack", 1000);
        addn_temp("apply/damage", 2000);
        addn_temp("apply/unarmed_damage", 2000);
        setup();

        carry_object("/clone/weapon/bow8");
        carry_object("/clone/weapon/bow8");
        carry_object("/clone/weapon/bow8");
        carry_object("/clone/weapon/bow8");
        carry_object("/clone/weapon/bow8");
        carry_object(__DIR__"obj/wandao");
        carry_object(__DIR__"obj/wandao");
        carry_object(__DIR__"obj/wandao");
        carry_object(__DIR__"obj/wandao");
        carry_object(__DIR__"obj/wandao")->wield();
        carry_object(__DIR__"obj/tiejia")->wear();
        carry_object(__DIR__"obj/pifeng")->wear();
}

void init()
{
        ::init();
        
        add_action("do_kill",
                ({ "team kill", "array kill", "touxi", "kill",
                   "hit", "fight", "steal", "beg", "persuade",
                   "perform", "yong", "exert", "yun", "throw",
                   "conjure", "recall" }));
}

int do_kill(string arg)
{
        string what, who;

        if (! arg) return 0;

        if (this_object()->id(arg))
        {
                write("有没有搞错，那是蒙古兵耶，还不快跑？！\n");
                return 1;
        } else
        if ((sscanf(arg, "%s from %s",what, who) == 2 ||
             sscanf(arg, "%s at %s", what, who) == 2 ||
             sscanf(arg, "%s on %s", what, who) == 2 ||
             sscanf(arg, "%s %s", what, who) == 2) &&
             this_object()->id(who)) {
                write("有没有搞错，那是蒙古兵耶，还不快跑？！\n");
                return 1;
        } else
        if (arg == "roar" || arg == "hou")
        {
                write("有没有搞错，那是蒙古兵耶，还不快跑？！\n");
                return 1;
        }

        return 0;
}

void new_life()
{
        object me = this_object();

        full_self(); // 补满气血

        delete_temp("no_perform");
        delete_temp("no_exert");

        me->clear_condition();

        me->interrupt_me(this_object());

        set_temp("apply/attack", 1200000);
        set_temp("apply/unarmed_damage", 150000);
        set_temp("apply/damage", 150000);
        set_temp("apply/armor", 100000);
        addn("my_life", -1, me);

        message_vision(HIG "\n$N" HIG "大喝一声，目光顿时充满杀意！\n\n" NOR, me);

        return;
}
varargs void die(object killer) 
{
        int i;
        object ob, obj;

        if (! objectp(ob = query_last_damage_from())) return;
        if( query_temp("warquest/party", ob) != "song")return ;

        // 如果还未重生，则重生一次
        if (query("my_life") > 0)
        {
                new_life();
                return;
        }

        message_vision("$N率领的蒙古骑兵在几经顽抗后，终于被彻底" +
                        HIR "消灭了" NOR "！\n",
                        this_object());
                        
        addn_temp("warquest/reward", 50, ob);

        if( MEMBER_D->is_valid_member(ob) && query("quest_tuteng/start", ob) && random(100) < 2 ) 
        {
                obj = new("/clone/tuteng/diwang-suipian"+(47+random(3)));
                message_vision(HIR "叮~~一声，从$N" HIR "掉出一样东西，$n" HIR
                	           "赶紧拣了起来。\n" NOR, this_object(), ob);
                tell_object(ob, BLINK + HIG "你得到了" + obj->name() + BLINK + HIG "。\n" NOR);
                obj->move(ob, 1);
        }

        WAR_D->win_kingwar();
        
        destruct(this_object());
}