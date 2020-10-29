// This program is a part of NT MudLIB
#include <ansi.h>
inherit NPC;

int auto_perform();
void you_out();
void create()
{
        set_name("萧峰", ({"xiao feng", "xiao", "feng"}));
        set("nickname", "大侠");
        set("gender", "男性");
        set("age", 35);
        set("long",
"身材甚是魁伟，三十来岁年纪，身穿灰色旧布袍，已微有破烂，浓眉大眼，
高鼻阔口，一张四方的国字脸，颇有风霜之色，顾盼之际，极有威势。\n");
        set("attitude", "peaceful");

        set("str", 30);
        set("int", 24);
        set("con", 40);
        set("dex", 40);

        set("max_qi", 10000);
        set("max_jing", 3000);
        set("neili", 10000);
        set("max_neili", 10000);
        set("jingli", 10000);
        set("max_jingli", 9000);
        set("eff_jingli", 9000);
        set("jiali", 100);

        set("combat_exp", 5400000);
        set("auto_perform",1);

        set("score", 200000);
        set("death_times",200);

        set_skill("force", 200);             // 基本内功
        set_skill("huntian-qigong", 200);    // 混天气功
        set_skill("strike", 200);            // 基本掌法
        set_skill("dragon-strike", 200);   // 降龙十八掌
        set_skill("dodge", 200);             // 基本躲闪
        set_skill("xiaoyaoyou", 200);        // 逍遥游
        set_skill("parry", 200);             // 基本招架

        map_skill("force", "huntian-qigong");
        map_skill("strike","dragon-strike");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "dragon-strike");
        prepare_skill("strike", "dragon-strike");
        create_family("丐帮", 13, "帮主");
        setup();

        carry_object("/clone/cloth/cloth")->wear();
}

int accept_kill(object victim)
{
        object *ob;
        int i;
        object me=this_object();
        if (!living(me)) return 1;
        if( query_temp("azi/killer", victim) != 1 && query_temp("azi/killer2", victim) != 1 )
        {
                command("say 臭贼有帮手，但我萧某何时怕过人多！\n");
                message_vision(HIY "萧峰见来了帮手，豪气顿增,把降龙十八掌发挥到极致,只见萧峰双臂划圈推出，正是一招「亢龙有悔」!\n" NOR,me);
                command("halt");
                ob = all_inventory(environment(me));
                for(i=0; i<sizeof(ob); i++) {
                        if( living(ob[i]) && query_temp("azi/killer2", ob[i]) == 1){
                                tell_object(ob[i], "你感到一阵强烈的气流涌向胸口，胸口一闷。\n");
                                            ob[i]->unconcious();
                        }
                }
                tell_object(victim, "你感到一阵强烈的气流涌向胸口，胸口登时一闷。\n");
                if (victim) victim->unconcious();
                call_out("destruct_me",1,me);
                me->start_busy(5);
        }
        return 1;
}

void die()
{
        object  me =this_object();
        object  ob;
        ob = me->query_last_damage_from();
        if( ob)set_temp("xiaofeng/done", 1, ob);
        message_vision(HIR"萧峰道:阿紫,姐夫无能,保护不了你了！\n" NOR,this_object());
        you_out();
        ::die();
}

void destruct_me(object me)
{
        object obj;
        obj=find_object("a zi");
        if (!obj) obj = present("a zi", me);
        if (!obj) obj = present("a zi", environment(me));
        if (obj)
        {
               destruct(obj);
               message_vision(HIY"萧峰哈哈大笑，道:今天饶尔等不死。抱住阿紫，几个起落，便已不见！\n" NOR,this_object());
               destruct(me);
        }
}

void you_out()
{
        object ob1,ob2,player;
        object me=this_object();
        ob1=present("you tanzhi");
        if (!ob1)
        {
                seteuid(getuid());
                ob1=new("/kungfu/class/xingxiu/you.c");
                ob1->move(environment());
        }
}
