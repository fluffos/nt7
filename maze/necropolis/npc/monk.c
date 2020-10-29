#include <ansi.h> 
inherit NPC;

int is_undead() {
        return 0;
}

void create()
{
        set_name("心武", ({ "xing wu","xing"}) );
        set("gender", "男性" );

        set("str", 50);
        set("con", 120);
        set("dex", 22); 
        set("int", 50);
        set("class","shaolin");     
        set("long",
        ""
        );
        //set("force_factor", 150);
        set("auto_perform", 2); 
        set("max_qi", 8000000);
        set("eff_qi", 480000);        
        set("max_jing", 8500000);
        set("eff_jing",850000);
        set("neili", 8000000);
        set("max_neili", 4500000);
        set("max_jingli", 500000);
        set("combat_exp", 300000000);

        set_skill("buddhism", 1200);
        set_skill("literate", 1200);

        set_skill("blade", 1200);
        set_skill("claw", 1200);
        set_skill("club", 1200);
        set_skill("cuff", 1200);
        set_skill("dodge", 1200);
        set_skill("finger", 1200);
        set_skill("force", 1200);
        set_skill("hand", 1200);
        set_skill("parry", 1200);
        set_skill("staff", 1200);
        set_skill("strike", 1200);
        set_skill("sword", 1200);
        set_skill("whip", 1200);
        set_skill("unarmed", 1200);

        set_skill("banruo-zhang", 1200);
        set_skill("cibei-dao", 1200);
        set_skill("damo-jian", 1200);
        set_skill("fengyun-shou", 1200);
        set_skill("fumo-jian", 1200);
        set_skill("hunyuan-yiqi", 1200);
        set_skill("jingang-quan", 1200);
        set_skill("longzhua-gong", 1200);
        set_skill("luohan-quan", 1200);
        set_skill("nianhua-zhi", 1200);
        set_skill("pudu-zhang", 1200);
        set_skill("qianye-shou", 1200);
        set_skill("sanhua-zhang", 1200);
        set_skill("riyue-bian", 1200);
        set_skill("shaolin-shenfa", 1200);
        set_skill("weituo-gun", 1200);
        set_skill("wuchang-zhang", 1200);
        set_skill("xiuluo-dao", 1200);
        set_skill("yingzhua-gong", 1200);
        set_skill("yijinjing", 1200);
        set_skill("yizhi-chan", 1200);
        set_skill("zui-gun", 1200);

        map_skill("blade", "cibei-dao");
        map_skill("claw", "longzhua-gong");
        map_skill("club", "wuchang-zhang");
        map_skill("cuff", "luohan-quan");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "nianhua-zhi");
        map_skill("force", "yijinjing");
        map_skill("hand", "fengyun-shou");
        map_skill("parry", "nianhua-zhi");
        map_skill("staff", "weituo-gun");
        map_skill("strike", "sanhua-zhang");
        map_skill("sword", "fumo-jian");
        map_skill("whip", "riyue-bian");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");
        set_temp("apply/attack", 3000);
        set_temp("apply/defense", 3000);
        set_temp("apply/armor", 5000);
        set_temp("apply/damage", 1500);
        set_temp("apply/unarmed_damage", 1500);
        set_temp("apply/add_weak", 60);
        set_temp("apply/reduce_damage", 80);
        set_temp("apply/reduce_busy", 20);
        set_temp("apply/add_busy", 5);

        set("drops", ([
                 "RA&RARE40" : 70, 
                 "RA&RARE40" : 70, 
                 "RA&RARE50" : 30, 
                 "RA&RARE50" : 30, 
                 "FI&/clone/goods/enchant-scroll" : 20, 
        ]));

        setup();

        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/spirit_tower");
}  


void unconcious()
{
        object ob;

        if (objectp(ob = previous_object(0)) && 
            sscanf(base_name(ob), "/kungfu/skill/%*s"))
        {
                this_object()->recover();
                return;
        }
        
        return ::unconcious();
}

varargs void die(object killer)
{
        object *inv,item,mazeobj;
        int count,finished;
        string name;
        object me, ob;
        me = this_object();

        if (objectp(ob = previous_object(0)) && 
            sscanf(base_name(ob), "/kungfu/skill/%*s"))
        {
                me->recover();
                return;
        }
        //death_msg
        if(query("death_msg"))
                        message_vision(query("death_msg"),this_object());
        else
                        message_vision("\n$N死了。\n\n",this_object());
        //check quest
        if (! killer)
        killer = query_last_damage_from();

        if(killer && userp(killer)) {
                mazeobj = FUBEN_D->query_maze_mainobj(this_object());
                if(!mazeobj) mazeobj = FUBEN_D->query_maze_mainobj(killer);
                if(query("quest/to_kill/"+name(), mazeobj)) { 
                        count = query("quest/to_kill/"+name(), mazeobj); 
                        finished = query("quest/killed/"+name(), mazeobj); 
                        finished++;
                        if(finished>count)
                                        finished = count;
                        set("quest/killed/"+name(), finished, mazeobj);
                        tell_object(killer,HIW"杀死 "+name()+": "+finished+"/"+count+"。\n"NOR);
                }
                //第6个任务，守卫丁一，杀二十个亡灵
                if( query("quest/quest_index", mazeobj) == 6 && is_undead() && 
                   environment() && query("short", environment()) == HIY"聚灵法阵"NOR){
                                count=query("quest/to_kill/亡灵", mazeobj);
                                if(count>0) {
                                        finished=query("quest/killed/亡灵", mazeobj);
                                        finished++;
                                        if(finished>count)
                                                finished = count;
                                        set("quest/killed/亡灵", finished, mazeobj);
                                        tell_object(killer,HIW"超度 亡灵: "+finished+"/"+count+" 。\n"NOR);
                                }
                }
        }
        //put all thing to ground
        inv = all_inventory(this_object());
        foreach(item in inv) {
                if(item)
                        item->move(environment());
        }
        ::die();
}

